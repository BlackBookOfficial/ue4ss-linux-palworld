#pragma once

#include <bit>
#include <cstring>

#include <ASMHelper/ASMHelper.hpp>
#include <Zydis/Zydis.h>

#define PARAMS(...) __VA_ARGS__
#define ARGS(...)  __VA_ARGS__

// GCC doesn't support std::bit_cast with member function pointers (not trivially copyable)
// Use a union-based cast instead
#ifndef _MSC_VER
template <typename MemberFuncPtr>
static MemberFuncPtr bit_cast_mfp(void* ptr) {
    // On the Itanium ABI (Linux/GCC/Clang), a pointer-to-member-function is 16 bytes:
    //   bytes 0-7: function pointer (or vtable offset if low bit is set)
    //   bytes 8-15: 'this' adjustment offset
    // A union copy only initializes 8 bytes, leaving the adjustment field
    // uninitialized. If the adjustment field contains garbage, the 'this'
    // pointer gets corrupted, causing SIGSEGV in the called function.
    // Fix: zero-initialize the entire PMF before copying the function pointer.
    MemberFuncPtr out{};  // zero-initialize (both fields = 0)
    std::memcpy(&out, &ptr, sizeof(void*));
    return out;
}
#define BIT_CAST_MFP(MemberFuncPtr, expr) bit_cast_mfp<MemberFuncPtr>(expr)
#else
#define BIT_CAST_MFP(MemberFuncPtr, expr) std::bit_cast<MemberFuncPtr>(expr)
#endif

// Helper to resolve function address from potential JMP instruction
#define RESOLVE_JMP(ptr) ASM::resolve_function_address_from_potential_jmp(ptr)

#define IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_NO_PARAMS(class_name, function_name, return_type) \
static const auto offset = []() { \
    auto it = VTableLayoutMap.find(STR(#function_name)); \
    if (it == VTableLayoutMap.end())                                                         \
    {                                                                                              \
        throw std::runtime_error{"Virtual " #class_name "::" #function_name " is unavailable, possibly unsupported in engine version"}; \
    }                                                                                           \
    return it->second; \
}(); \
std::byte* vtable = std::bit_cast<std::byte*>(*std::bit_cast<std::byte**>(this)); \
auto func = BIT_CAST_MFP(return_type(class_name::*)() const, *std::bit_cast<void**>(vtable + offset));\
if (!func) \
{ \
throw std::runtime_error{"Function '" #function_name "' not available"}; \
}                                                                          \
return (this->*func)();

#define IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(class_name, function_name, return_type, params, args) \
static const auto offset = []() { \
    auto it = VTableLayoutMap.find(STR(#function_name)); \
    if (it == VTableLayoutMap.end())                                                         \
    {                                                                                              \
        throw std::runtime_error{"Virtual " #class_name "::" #function_name " is unavailable, possibly unsupported in engine version"}; \
    }\
    return it->second; \
}(); \
std::byte* vtable = std::bit_cast<std::byte*>(*std::bit_cast<std::byte**>(this)); \
auto func = BIT_CAST_MFP(return_type(class_name::*)(params) const, *std::bit_cast<void**>(vtable + offset)); \
if (!func) \
{ \
throw std::runtime_error{"Function '" #function_name "' not available"}; \
}                                                                          \
return (this->*func)(args);

#define IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_MULTI_NAME_NO_PARAMS(class_name, function_name, return_type, ...) \
static const auto offset = []() { \
    auto it = VTableLayoutMap.end(); \
    for (const auto& name : {STR(#function_name), __VA_ARGS__}) \
    { \
        it = VTableLayoutMap.find(name); \
        if (it != VTableLayoutMap.end()) break; \
    } \
    if (it == VTableLayoutMap.end()) \
    { \
        throw std::runtime_error{"Virtual " #class_name "::" #function_name " is unavailable, possibly unsupported in engine version"}; \
    } \
    return it->second; \
}(); \
std::byte* vtable = std::bit_cast<std::byte*>(*std::bit_cast<std::byte**>(this)); \
auto func = BIT_CAST_MFP(return_type(class_name::*)() const, *std::bit_cast<void**>(vtable + offset)); \
if (!func) \
{ \
    throw std::runtime_error{"Function '" #function_name "' not available"}; \
} \
return (this->*func)();

#define IMPLEMENT_UNREAL_VIRTUAL_WRAPPER_MULTI_NAME(class_name, function_name, return_type, params, args, ...) \
static const auto offset = []() { \
    auto it = VTableLayoutMap.end(); \
    for (const auto& name : {STR(#function_name), __VA_ARGS__}) \
    { \
        it = VTableLayoutMap.find(name); \
        if (it != VTableLayoutMap.end()) break; \
    } \
    if (it == VTableLayoutMap.end()) \
    { \
        throw std::runtime_error{"Virtual " #class_name "::" #function_name " is unavailable, possibly unsupported in engine version"}; \
    } \
    return it->second; \
}(); \
std::byte* vtable = std::bit_cast<std::byte*>(*std::bit_cast<std::byte**>(this)); \
auto func = BIT_CAST_MFP(return_type(class_name::*)(params) const, *std::bit_cast<void**>(vtable + offset)); \
if (!func) \
{ \
    throw std::runtime_error{"Function '" #function_name "' not available"}; \
} \
return (this->*func)(args);

#define GET_ADDRESS_OF_UNREAL_VIRTUAL(class_name, function_name, instance) \
[&instance]() -> void* {                                                   \
    static const auto offset = []() { \
        auto it = class_name::VTableLayoutMap.find(STR(#function_name));                        \
        if (it == class_name::VTableLayoutMap.end())                                       \
        {                                                                      \
            throw std::runtime_error{"Virtual " #class_name "::" #function_name " is unavailable, possibly unsupported in engine version"}; \
        }\
        return it->second; \
    }(); \
    std::byte* vtable = std::bit_cast<std::byte*>(*std::bit_cast<std::byte**>(instance)); \
    return RESOLVE_JMP(*std::bit_cast<void**>(vtable + offset));\
}()

#define OPTIONAL_GET_ADDRESS_OF_UNREAL_VIRTUAL(class_name, function_name, instance) \
[&instance]() -> void* {                                                   \
    static const auto offset = []() -> uint32_t { \
        auto it = class_name::VTableLayoutMap.find(STR(#function_name));                        \
        if (it == class_name::VTableLayoutMap.end())                                       \
        {                                                                      \
            return 0; \
        }\
        return it->second; \
    }(); \
    if (offset == 0) \
    { \
        return nullptr; \
    } \
    std::byte* vtable = std::bit_cast<std::byte*>(*std::bit_cast<std::byte**>(instance)); \
    return RESOLVE_JMP(*std::bit_cast<void**>(vtable + offset));\
}()

namespace RC::Unreal
{
    class UnrealVirtualBaseVC
    {
    public:
        virtual ~UnrealVirtualBaseVC() = default;

    public:
        virtual auto set_virtual_offsets() -> void = 0;
    };
}


