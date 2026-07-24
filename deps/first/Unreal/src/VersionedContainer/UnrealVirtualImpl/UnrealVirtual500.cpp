#include <Unreal/VersionedContainer/UnrealVirtualImpl/UnrealVirtual500.hpp>

#include <functional>

// These are all the structs that have virtuals that need to have their offset set
#include <Unreal/UObject.hpp>
#include <Unreal/UEngine.hpp>
#include <Unreal/CoreUObject/UObject/Class.hpp>
#include <Unreal/FOutputDevice.hpp>
#include <Unreal/FField.hpp>
#include <Unreal/CoreUObject/UObject/UnrealType.hpp>
#include <Unreal/Property/FEnumProperty.hpp>
#include <Unreal/Property/FFieldPathProperty.hpp>
#include <Unreal/World.hpp>
#include <Unreal/FWorldContext.hpp>
#include <Unreal/FArchive.hpp>
#include <Unreal/AGameModeBase.hpp>
#include <Unreal/AGameMode.hpp>
#include <Unreal/UPlayer.hpp>
#include <Unreal/ULocalPlayer.hpp>
#include <Unreal/ITextData.hpp>
#include <Unreal/UGameViewportClient.hpp>
#include <Unreal/Engine/UDataTable.hpp>

namespace RC::Unreal
{
    void UnrealVirtual500::set_virtual_offsets()
    {
#include <FunctionBodies/5_00_VTableOffsets_UObjectBase_FunctionBody.cpp>
#include <FunctionBodies/5_00_VTableOffsets_UObjectBaseUtility_FunctionBody.cpp>
#include <FunctionBodies/5_00_VTableOffsets_UObject_FunctionBody.cpp>
#include <FunctionBodies/5_00_VTableOffsets_UScriptStruct__ICppStructOps_FunctionBody.cpp>
#include <FunctionBodies/5_00_VTableOffsets_FOutputDevice_FunctionBody.cpp>
#include <FunctionBodies/5_00_VTableOffsets_UStruct_FunctionBody.cpp>
#include <FunctionBodies/5_00_VTableOffsets_UGameViewportClient_FunctionBody.cpp>
#include <FunctionBodies/5_00_VTableOffsets_FMalloc_FunctionBody.cpp>
#include <FunctionBodies/5_00_VTableOffsets_FArchive_FunctionBody.cpp>
#include <FunctionBodies/5_00_VTableOffsets_FArchiveState_FunctionBody.cpp>
#include <FunctionBodies/5_00_VTableOffsets_AGameModeBase_FunctionBody.cpp>
#include <FunctionBodies/5_00_VTableOffsets_AGameMode_FunctionBody.cpp>
#include <FunctionBodies/5_00_VTableOffsets_AActor_FunctionBody.cpp>
#include <FunctionBodies/5_00_VTableOffsets_UPlayer_FunctionBody.cpp>
#include <FunctionBodies/5_00_VTableOffsets_UEngine_FunctionBody.cpp>
#include <FunctionBodies/5_00_VTableOffsets_ULocalPlayer_FunctionBody.cpp>
#include <FunctionBodies/5_00_VTableOffsets_FField_FunctionBody.cpp>
#include <FunctionBodies/5_00_VTableOffsets_UField_FunctionBody.cpp>
#include <FunctionBodies/5_00_VTableOffsets_FProperty_FunctionBody.cpp>
#include <FunctionBodies/5_00_VTableOffsets_FNumericProperty_FunctionBody.cpp>
#include <FunctionBodies/5_00_VTableOffsets_FMulticastDelegateProperty_FunctionBody.cpp>
#include <FunctionBodies/5_00_VTableOffsets_FObjectPropertyBase_FunctionBody.cpp>
#include <FunctionBodies/5_00_VTableOffsets_ITextData_FunctionBody.cpp>
#include <FunctionBodies/5_00_VTableOffsets_UDataTable_FunctionBody.cpp>

#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_UObjectBase.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_UScriptStruct__ICppStructOps.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_FOutputDevice.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_UStruct.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_UGameViewportClient.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_FUObjectItem.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_FUObjectArray.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_TUObjectArray.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_FArchiveState.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_AGameModeBase.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_AGameMode.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_AActor.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_UPlayer.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_ULocalPlayer.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_FFieldClass.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_FField.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_UField.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_FProperty.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_FMulticastDelegateProperty.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_FObjectPropertyBase.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_FWorldContext.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_UScriptStruct.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_UWorld.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_UFunction.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_UClass.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_UEnum.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_FStructProperty.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_FArrayProperty.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_FMapProperty.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_FBoolProperty.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_FByteProperty.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_FEnumProperty.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_FClassProperty.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_FSoftClassProperty.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_FDelegateProperty.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_FInterfaceProperty.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_FFieldPathProperty.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_FSetProperty.cpp>
#include <FunctionBodies/5_00_MemberVariableLayout_DefaultSetter_UDataTable.cpp>
    }
}
