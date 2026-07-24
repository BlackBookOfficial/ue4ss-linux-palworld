#include <Unreal/CoreUObject/UObject/Class.hpp>
#include <Unreal/CoreUObject/UObject/UnrealType.hpp>
#include <Helpers/Casting.hpp>

namespace RC::Unreal
{
    IMPLEMENT_EXTERNAL_OBJECT_CLASS(UScriptStruct);

#include <MemberVariableLayout_SrcWrapper_UScriptStruct.hpp>

    std::unordered_map<File::StringType, uint32_t> UScriptStruct::ICppStructOps::VTableLayoutMap;

#include <MemberVariableLayout_SrcWrapper_UScriptStruct__ICppStructOps.hpp>

    void UScriptStruct::ICppStructOps::Construct(void* Dest)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UScriptStruct::ICppStructOps, Construct, void, PARAMS(void*), ARGS(Dest))
    }
    void UScriptStruct::ICppStructOps::Destruct(void* Dest)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UScriptStruct::ICppStructOps, Destruct, void, PARAMS(void*), ARGS(Dest))
    }

    bool UScriptStruct::ICppStructOps::Copy(void* Dest, void const* Src, int32 ArrayDim)
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(UScriptStruct::ICppStructOps, Copy, bool, PARAMS(void*, void const*, int32), ARGS(Dest, Src, ArrayDim));
    }

    int32 UScriptStruct::GetSize()
    {
        return GetPropertiesSize();
    }

    auto UScriptStruct::GetSuperScriptStruct() -> UScriptStruct*
    {
        return Cast<UScriptStruct>(GetSuperStruct());
    }

    void UScriptStruct::CopyScriptStruct(void* InDest, void const* InSrc, int32 ArrayDim)/* const*/
    {
        uint8* Dest = (uint8*)InDest;
        uint8 const* Src = (uint8 const*)InSrc;

        int32 Stride = GetStructureSize();

        if (HasAnyStructFlags(STRUCT_CopyNative) && !HasAnyStructFlags(STRUCT_IsPlainOldData))
        {
            // Casting away const here because our implementation for auto-generated getters is not correct.
            // This should be removed after the implementation is fixed.
            UScriptStruct::ICppStructOps* TheCppStructOps = std::bit_cast<ICppStructOps*>(GetCppStructOps());
            if (TheCppStructOps->Copy(Dest, Src, ArrayDim))
            {
                return;
            }
        }
        if (HasAnyStructFlags(STRUCT_IsPlainOldData))
        {
            FMemory::Memcpy(Dest, Src, ArrayDim * Stride);
        }
        else
        {
            for (FProperty* It : TFieldRange<FProperty>(this, EFieldIterationFlags::IncludeDeprecated)) 
            {
                for (int32 Index = 0; Index < ArrayDim; Index++)
                {
                    It->CopyCompleteValue_InContainer((uint8*)Dest + Index * Stride, (uint8*)Src + Index * Stride);
                }
            }
        }
    }
}