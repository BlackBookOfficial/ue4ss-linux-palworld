#include <bit>

#include <ASMHelper/ASMHelper.hpp>
#include <DynamicOutput/DynamicOutput.hpp>
#include <Zydis/Zydis.h>

namespace RC::ASM
{
    auto get_first_instruction_at_address(void* in_instruction_ptr) -> Instruction
    {
        auto instruction_ptr = static_cast<uint8_t*>(in_instruction_ptr);
        ZydisDecoder decoder{};
        ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);
        ZyanUSize offset = 0;
        ZydisDecodedInstruction instruction{};
        ZydisDecodedOperand operands[10]{};
        while (ZYAN_SUCCESS(ZydisDecoderDecodeFull(&decoder, instruction_ptr + offset, 16 - offset, &instruction, operands)))
        {
            break;
        }
        return {in_instruction_ptr, instruction, operands};
    }

    auto resolve_absolute_address(void* in_instruction_ptr) -> void*
    {
        auto instruction = get_first_instruction_at_address(in_instruction_ptr);
        ZyanU64 resolved_address{};
        if (ZYAN_SUCCESS(ZydisCalcAbsoluteAddress(&instruction.raw, &instruction.operands[0], std::bit_cast<ZyanU64>(in_instruction_ptr), &resolved_address)))
        {
            return std::bit_cast<void*>(resolved_address);
        }
        else
        {
            return nullptr;
        }
    }

    auto resolve_jmp(void* in_instruction_ptr) -> void*
    {
        return resolve_absolute_address(in_instruction_ptr);
    }

    auto resolve_call(void* in_instruction_ptr) -> void*
    {
        return resolve_absolute_address(in_instruction_ptr);
    }

    auto resolve_function_address_from_potential_jmp(void* function_ptr) -> void*
    {
        // Scan up to 8 instructions for a transfer of control out of the block.
        // If a JMP (or a leading CALL) appears before any RET, this is a jump
        // stub — or, on the Itanium ABI, a this-adjustment thunk (a short block
        // ending in `jmp rel32` to the real function) — so follow it. A RET
        // first means a real function body: return it unchanged. This matters
        // for vtable entries on Linux, where secondary-base slots point to
        // thunks rather than to the function itself.
        auto* base = static_cast<uint8_t*>(function_ptr);
        ZydisDecoder decoder{};
        ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);
        ZyanUSize offset = 0;
        for (int instruction_count = 0; instruction_count < 8; ++instruction_count)
        {
            ZydisDecodedInstruction instruction{};
            ZydisDecodedOperand operands[10]{};
            if (!ZYAN_SUCCESS(ZydisDecoderDecodeFull(&decoder, base + offset, 16, &instruction, operands)))
            {
                break;
            }
            if (instruction.mnemonic == ZYDIS_MNEMONIC_RET)
            {
                break;
            }
            if (instruction.mnemonic == ZYDIS_MNEMONIC_CALL && instruction_count > 0)
            {
                break; // CALL mid-block: real function body, not a stub
            }
            if (instruction.mnemonic == ZYDIS_MNEMONIC_JMP || instruction.mnemonic == ZYDIS_MNEMONIC_CALL)
            {
                ZyanU64 resolved_address{};
                if (ZYAN_SUCCESS(ZydisCalcAbsoluteAddress(&instruction, &operands[0], std::bit_cast<ZyanU64>(base + offset), &resolved_address)))
                {
                    return resolve_function_address_from_potential_jmp(std::bit_cast<void*>(resolved_address));
                }
                Output::send<LogLevel::Warning>(STR("Was unable to resolve JMP instruction @ {}\n"), std::bit_cast<void*>(base + offset));
                return nullptr;
            }
            offset += instruction.length;
        }
        return function_ptr;
    }
} // namespace RC::ASM
