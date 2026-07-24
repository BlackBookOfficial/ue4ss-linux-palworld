#pragma once

#include <malloc.h>
#include <stdexcept>
#include <format>

#ifdef __linux__
#include <alloca.h>
#define _malloca(size) alloca(size)
#define _freea(ptr) (void)0
#endif

#include <Unreal/CoreUObject/UObject/UnrealType.hpp>
#include <Unreal/CoreUObject/UObject/Class.hpp>

#define UE_BEGIN_FUNCTION_BODY_INTERNAL(FunctionPath) \
if (!Function) \
{ \
    throw std::runtime_error{"Unable to find '" FunctionPath "'"}; \
} \
static auto ParamStructSize = Function->GetParmsSize(); \
auto ParamData = static_cast<uint8*>(_malloca(ParamStructSize)); \
FMemory::Memzero(ParamData, ParamStructSize);

#define UE_FREE_PARAM_STRUCT_INTERNAL() \
_freea(ParamData);

#define UE_END_VOID_FUNCTION() \
UE_FREE_PARAM_STRUCT_INTERNAL()

#define UE_BEGIN_SCRIPT_FUNCTION_BODY(FunctionPath) \
auto Function = UObjectGlobals::StaticFindObject<UFunction*>(nullptr, nullptr, STR(FunctionPath)); \
UE_BEGIN_FUNCTION_BODY_INTERNAL(FunctionPath)

#define UE_BEGIN_NATIVE_FUNCTION_BODY(FunctionPath) \
static auto Function = UObjectGlobals::StaticFindObject<UFunction*>(nullptr, nullptr, STR(FunctionPath)); \
UE_BEGIN_FUNCTION_BODY_INTERNAL(FunctionPath)

#define UE_SET_STATIC_SELF(ObjectPath) \
static auto StaticSelf = UObjectGlobals::StaticFindObject<UObject*>(nullptr, nullptr, STR(ObjectPath));

#define UE_COPY_PROPERTY_INTERNAL(PropertyName) \
auto PropertyName##Property = Function->FindProperty(FName(STR(#PropertyName), FNAME_Find)); \
if (!PropertyName##Property) { throw std::runtime_error{"Property not found: '"#PropertyName"'"}; }

#define UE_COPY_PROPERTY(PropertyName, TypeName) \
UE_COPY_PROPERTY_INTERNAL(PropertyName) \
*std::bit_cast<TypeName*>(&ParamData[PropertyName##Property->GetOffset_Internal()]) = static_cast<TypeName>(PropertyName);

#define UE_COPY_STRUCT_PROPERTY_BEGIN(PropertyName) \
UE_COPY_PROPERTY_INTERNAL(PropertyName) \
auto PropertyName##Struct = static_cast<FStructProperty*>(PropertyName##Property)->GetStruct();

#define UE_COPY_STRUCT_INNER_PROPERTY(StructName, PropertyName, TypeName, CXXValue) \
auto StructName##PropertyName##Property = StructName##Struct->FindProperty(FName(STR(#PropertyName), FNAME_Find)); \
*std::bit_cast<TypeName*>(&ParamData[StructName##Property->GetOffset_Internal() + StructName##PropertyName##Property->GetOffset_Internal()]) = static_cast<TypeName>(CXXValue);

#define UE_COPY_OUT_PROPERTY(PropertyName, TypeName) \
auto Out##PropertyName##Property = Function->FindProperty(FName(STR(#PropertyName), FNAME_Find)); \
if (!Out##PropertyName##Property) { throw std::runtime_error{"Out property not found: '"#PropertyName"'"}; } \
PropertyName = *std::bit_cast<TypeName*>(&ParamData[Out##PropertyName##Property->GetOffset_Internal()]);

#define UE_COPY_PROPERTY_CUSTOM_INTERNAL(BPPropertyName, CXXPropertyName) \
auto CXXPropertyName##Property = Function->FindProperty(FName(STR(#BPPropertyName), FNAME_Find)); \
if (!CXXPropertyName##Property) { throw std::runtime_error{"Property not found: '"#BPPropertyName"'"}; }

#define UE_COPY_PROPERTY_CUSTOM(BPPropertyName, CXXPropertyName, TypeName) \
UE_COPY_PROPERTY_CUSTOM_INTERNAL(BPPropertyName, CXXPropertyName) \
*std::bit_cast<TypeName*>(&ParamData[CXXPropertyName##Property->GetOffset_Internal()]) = static_cast<TypeName>(CXXPropertyName);

#define UE_COPY_STRUCT_PROPERTY_CUSTOM_BEGIN(BPPropertyName, CXXPropertyName) \
UE_COPY_PROPERTY_CUSTOM_INTERNAL(BPPropertyName, CXXPropertyName) \
auto CXXPropertyName##Struct = static_cast<FStructProperty*>(CXXPropertyName##Property)->GetStruct();

#define UE_COPY_STRUCT_INNER_PROPERTY_CUSTOM(StructName, BPPropertyName, CXXPropertyName, TypeName, CXXValue) \
auto StructName##CXXPropertyName##Property = StructName##Struct->FindProperty(FName(STR(#BPPropertyName), FNAME_Find)); \
*std::bit_cast<TypeName*>(&ParamData[StructName##Property->GetOffset_Internal() + StructName##CXXPropertyName##Property->GetOffset_Internal()]) = static_cast<TypeName>(CXXValue);

#define UE_COPY_OUT_PROPERTY_CUSTOM(BPPropertyName, CXXPropertyName, TypeName) \
auto OutPropertyName##CXXPropertyName = Function->FindProperty(FName(STR(#BPPropertyName), FNAME_Find)); \
if (!OutPropertyName##CXXPropertyName) { throw std::runtime_error{"Out property not found: '"#BPPropertyName"'"}; } \
CXXPropertyName = *std::bit_cast<TypeName*>(&ParamData[OutPropertyName##CXXPropertyName->GetOffset_Internal()]);

#define UE_CALL_FUNCTION() \
ProcessEvent(Function, ParamData);

#define UE_CALL_STATIC_FUNCTION() \
StaticSelf->ProcessEvent(Function, ParamData);

#define UE_RETURN_PROPERTY_INTERNAL() \
auto ReturnProperty = Function->GetReturnProperty(); \
if (!ReturnProperty) { throw std::runtime_error{fmt::format("ReturnProperty is nullptr for '{}'", to_string(Function->GetFullName()))}; }

#define UE_RETURN_PROPERTY(TypeName) \
UE_RETURN_PROPERTY_INTERNAL() \
auto RetValue = *std::bit_cast<TypeName*>(&ParamData[ReturnProperty->GetOffset_Internal()]); \
UE_FREE_PARAM_STRUCT_INTERNAL() \
return RetValue;

#define UE_RETURN_PROPERTY_CUSTOM(TypeName, PropertyName) \
auto ReturnProperty = Function->FindProperty(FName(STR(#PropertyName), FNAME_Find)); \
if (!ReturnProperty) { throw std::runtime_error{fmt::format("ReturnProperty is nullptr for '{}'", to_string(Function->GetFullName()))}; } \
auto RetValue = *std::bit_cast<TypeName*>(&ParamData[ReturnProperty->GetOffset_Internal()]); \
UE_FREE_PARAM_STRUCT_INTERNAL() \
return RetValue;

#define UE_RETURN_VECTOR() \
UE_RETURN_PROPERTY_INTERNAL() \
auto RetValue = *std::bit_cast<FVector*>(&ParamData[ReturnProperty->GetOffset_Internal()]); \
UE_FREE_PARAM_STRUCT_INTERNAL() \
return RetValue;

#define UE_RETURN_STRING() \
UE_RETURN_PROPERTY_INTERNAL() \
auto RetValue = StringType{**std::bit_cast<FString*>(&ParamData[ReturnProperty->GetOffset_Internal()])}; \
UE_FREE_PARAM_STRUCT_INTERNAL() \
return RetValue;

#define UE_RETURN_STRING_CUSTOM(PropertyName) \
auto ReturnProperty = Function->FindProperty(FName(STR(#PropertyName), FNAME_Find)); \
if (!ReturnProperty) { throw std::runtime_error{fmt::format("ReturnProperty is nullptr for '{}'", to_string(Function->GetFullName()))}; } \
auto RetValue = StringType{**std::bit_cast<FString*>(&ParamData[ReturnProperty->GetOffset_Internal()])}; \
UE_FREE_PARAM_STRUCT_INTERNAL() \
return RetValue;

#define UE_COPY_VECTOR(FromName, ToName) \
if (Version::IsBelow(5, 0)) \
{ \
    UE_COPY_STRUCT_INNER_PROPERTY(ToName, X, float, FromName.X()) \
    UE_COPY_STRUCT_INNER_PROPERTY(ToName, Y, float, FromName.Y()) \
    UE_COPY_STRUCT_INNER_PROPERTY(ToName, Z, float, FromName.Z()) \
} \
else \
{ \
    UE_COPY_STRUCT_INNER_PROPERTY(ToName, X, double, FromName.X()) \
    UE_COPY_STRUCT_INNER_PROPERTY(ToName, Y, double, FromName.Y()) \
    UE_COPY_STRUCT_INNER_PROPERTY(ToName, Z, double, FromName.Z()) \
}

// IMPORTANT: MACRO NEEDS TESTING!
#define UE_COPY_STL_VECTOR_AS_TARRAY(PropertyName, ArrayInnerType, StlVariable) \
UE_COPY_PROPERTY_INTERNAL(PropertyName) \
auto& PropertyName##Value = *std::bit_cast<TArray<ArrayInnerType>*>(&ParamData[PropertyName##Property->GetOffset_Internal()]); \
PropertyName##Value = TArray<ArrayInnerType>(); \
for (const auto& StlElem : StlVariable) \
{\
    PropertyName##Value.Add(StlElem); \
}

#define WITH_OUTER(Outer, ...) Outer<__VA_ARGS__>
