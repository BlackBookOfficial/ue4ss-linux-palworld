#include <algorithm>

#include <DynamicOutput/DynamicOutput.hpp>
#include <Helpers/Casting.hpp>
#include <Unreal/TypeChecker.hpp>
#include <Unreal/UObject.hpp>
#include <Unreal/AActor.hpp>
#include <Unreal/FField.hpp>
#include <Unreal/CoreUObject/UObject/Class.hpp>
#include <Unreal/CoreUObject/UObject/UnrealType.hpp>
#include <Unreal/FAssetData.hpp>
#include <Unreal/UInterface.hpp>
#include <Unreal/UActorComponent.hpp>
#include <Unreal/UGameViewportClient.hpp>
#include <Unreal/Engine/UDataTable.hpp>
#include <Unreal/UPackage.hpp>
#include <Unreal/CanvasPanel.hpp>
#include <Unreal/World.hpp>
#include <Unreal/Property/FEnumProperty.hpp>
#include <Unreal/Property/FTextProperty.hpp>
#include <Unreal/CoreUObject/UObject/FStrProperty.hpp>
#include <Unreal/Property/FFieldPathProperty.hpp>
#include <Unreal/Property/FOptionalProperty.hpp>
#include <Unreal/CoreUObject/UObject/FUtf8StrProperty.hpp>
#include <Unreal/CoreUObject/UObject/FAnsiStrProperty.hpp>
#include <Unreal/UnrealVersion.hpp>
#include <String/StringType.hpp>

namespace RC::Unreal
{
    FName GWorldName{};
    FName GLevelName{};
    FName GPackageName{};
    FName GPropertyName{};
    FName GFunctionName{};

    auto TypeChecker::get_world_name() -> FName
    {
        return GWorldName;
    }

    auto TypeChecker::get_level_name() -> FName
    {
        return GLevelName;
    }

    auto TypeChecker::store_all_object_names() -> void
    {
        //@formatter:off
        // Misc
        GWorldName    =FName(STR("World"), FNAME_Find);
        GLevelName    =FName(STR("Level"), FNAME_Find);
        GPackageName  =FName(STR("Package"), FNAME_Find);
        GPropertyName =FName(STR("Property"), FNAME_Find);
        GFunctionName =FName(STR("Function"), FNAME_Find);
        //@formatter:on
    }

    auto TypeChecker::store_all_object_types() -> bool
    {
       //StaticFindObject_InternalSlow is used for compatability reasons.
        UObject::StaticClassStorage = static_cast<UClass*>(UObjectGlobals::StaticFindObject_InternalSlow(nullptr, nullptr, STR("/Script/CoreUObject.Object")));
        UField::StaticClassStorage = static_cast<UClass*>(UObjectGlobals::StaticFindObject_InternalSlow(nullptr, nullptr, STR("/Script/CoreUObject.Field")));
        UStruct::StaticClassStorage = static_cast<UClass*>(UObjectGlobals::StaticFindObject_InternalSlow(nullptr, nullptr, STR("/Script/CoreUObject.Struct")));

        AActor::StaticClassStorage = static_cast<UClass*>(UObjectGlobals::StaticFindObject_InternalSlow(nullptr, nullptr, STR("/Script/Engine.Actor")));
        UWorld::StaticClassStorage = static_cast<UClass*>(UObjectGlobals::StaticFindObject_InternalSlow(nullptr, nullptr, STR("/Script/Engine.World")));

        UClass* enum_ptr = static_cast<UClass*>(UObjectGlobals::StaticFindObject_InternalSlow(nullptr, nullptr, STR("/Script/CoreUObject.Enum")));
        UEnum::StaticClassStorage = enum_ptr;

        UClass* user_defined_enum_ptr = static_cast<UClass*>(UObjectGlobals::StaticFindObject_InternalSlow(nullptr, nullptr, STR("/Script/Engine.UserDefinedEnum")));
        UUserDefinedEnum::StaticClassStorage = user_defined_enum_ptr;

        UClass* class_ptr = static_cast<UClass*>(UObjectGlobals::StaticFindObject_InternalSlow(nullptr, nullptr, STR("/Script/CoreUObject.Class")));
        UClass::StaticClassStorage = class_ptr;

        UClass* bp_generated_class_ptr = static_cast<UClass*>(UObjectGlobals::StaticFindObject_InternalSlow(nullptr, nullptr, STR("/Script/Engine.BlueprintGeneratedClass")));
        UBlueprintGeneratedClass::StaticClassStorage = bp_generated_class_ptr;

        UClass* widget_bp_generated_class_ptr = static_cast<UClass*>(UObjectGlobals::StaticFindObject_InternalSlow(nullptr, nullptr, STR("/Script/UMG.WidgetBlueprintGeneratedClass")));
        UWidgetBlueprintGeneratedClass::StaticClassStorage = widget_bp_generated_class_ptr;

        UClass* anim_bp_generated_class_ptr = static_cast<UClass*>(UObjectGlobals::StaticFindObject_InternalSlow(nullptr, nullptr, STR("/Script/Engine.AnimBlueprintGeneratedClass")));
        UAnimBlueprintGeneratedClass::StaticClassStorage = anim_bp_generated_class_ptr;

        UClass* canvas_panel_ptr = static_cast<UClass*>(UObjectGlobals::StaticFindObject_InternalSlow(nullptr, nullptr, STR("/Script/UMG.CanvasPanel")));
        UCanvasPanel::StaticClassStorage = canvas_panel_ptr;

        // Not available in 4.12 (I've not checked exactly when it starts being available)
        UClass* asset_data_ptr = static_cast<UClass*>(UObjectGlobals::StaticFindObject_InternalSlow(nullptr, nullptr, STR("/Script/AssetRegistry.AssetData")));
        if (!asset_data_ptr)
        {
            // In 4.26, they moved it from the 'AssetRegistry' package to the 'CoreUObject' package
            asset_data_ptr = static_cast<UClass*>(UObjectGlobals::StaticFindObject_InternalSlow(nullptr, nullptr, STR("/Script/CoreUObject.AssetData")));
        }
        FAssetData::StaticClassStorage = asset_data_ptr;

        UPackage::StaticClassStorage = static_cast<UClass*>(UObjectGlobals::StaticFindObject_InternalSlow(nullptr, nullptr, STR("/Script/CoreUObject.Package")));
        UInterface::StaticClassStorage = static_cast<UClass*>(UObjectGlobals::StaticFindObject_InternalSlow(nullptr, nullptr, STR("/Script/CoreUObject.Interface")));
        UActorComponent::StaticClassStorage = static_cast<UClass*>(UObjectGlobals::StaticFindObject_InternalSlow(nullptr, nullptr, STR("/Script/Engine.ActorComponent")));
        USceneComponent::StaticClassStorage = static_cast<UClass*>(UObjectGlobals::StaticFindObject_InternalSlow(nullptr, nullptr, STR("/Script/Engine.SceneComponent")));
        UGameViewportClient::StaticClassStorage = static_cast<UClass*>(UObjectGlobals::StaticFindObject_InternalSlow(nullptr, nullptr, STR("/Script/Engine.GameViewportClient")));
        UDataTable::StaticClassStorage = static_cast<UClass*>(UObjectGlobals::StaticFindObject_InternalSlow(nullptr, nullptr, STR("/Script/Engine.UDataTable")));

        UFunction::StaticClassStorage = static_cast<UClass*>(UObjectGlobals::StaticFindObject_InternalSlow(nullptr, nullptr, STR("/Script/CoreUObject.Function")));
        UDelegateFunction::StaticClassStorage = static_cast<UClass*>(UObjectGlobals::StaticFindObject_InternalSlow(nullptr, nullptr, STR("/Script/CoreUObject.DelegateFunction")));

        if (Version::IsAtLeast(4, 23))
        {
            USparseDelegateFunction::StaticClassStorage = static_cast<UClass*>(UObjectGlobals::StaticFindObject_InternalSlow(nullptr, nullptr, STR("/Script/CoreUObject.SparseDelegateFunction")));
        }

        UClass* script_struct_ptr = static_cast<UClass*>(UObjectGlobals::StaticFindObject_InternalSlow(nullptr, nullptr, STR("/Script/CoreUObject.ScriptStruct")));
        UScriptStruct::StaticClassStorage = script_struct_ptr;

        /*
        FProperty::m_static_obj = UObjectGlobals::static_find_object<UClass*>(nullptr, nullptr, STR("/Script/CoreUObject.Property"));
        FNumericProperty::m_static_obj = UObjectGlobals::static_find_object<UClass*>(nullptr, nullptr, STR("/Script/CoreUObject.NumericProperty"));
        FInt8Property::m_static_obj = UObjectGlobals::static_find_object<UClass*>(nullptr, nullptr, STR("/Script/CoreUObject.Int8Property"));
        FInt16Property::m_static_obj = UObjectGlobals::static_find_object<UClass*>(nullptr, nullptr, STR("/Script/CoreUObject.Int16Property"));
        FIntProperty::m_static_obj = UObjectGlobals::static_find_object<UClass*>(nullptr, nullptr, STR("/Script/CoreUObject.IntProperty"));
        FInt64Property::m_static_obj = UObjectGlobals::static_find_object<UClass*>(nullptr, nullptr, STR("/Script/CoreUObject.Int64Property"));
        FFloatProperty::m_static_obj = UObjectGlobals::static_find_object<UClass*>(nullptr, nullptr, STR("/Script/CoreUObject.FloatProperty"));
        FDoubleProperty::m_static_obj = UObjectGlobals::static_find_object<UClass*>(nullptr, nullptr, STR("/Script/CoreUObject.DoubleProperty"));
        FByteProperty::m_static_obj = UObjectGlobals::static_find_object<UClass*>(nullptr, nullptr, STR("/Script/CoreUObject.ByteProperty"));
        FUInt16Property::m_static_obj = UObjectGlobals::static_find_object<UClass*>(nullptr, nullptr, STR("/Script/CoreUObject.UInt16Property"));
        FUInt32Property::m_static_obj = UObjectGlobals::static_find_object<UClass*>(nullptr, nullptr, STR("/Script/CoreUObject.UInt32Property"));
        FUInt64Property::m_static_obj = UObjectGlobals::static_find_object<UClass*>(nullptr, nullptr, STR("/Script/CoreUObject.UInt64Property"));
        FObjectProperty::m_static_obj = UObjectGlobals::static_find_object<UClass*>(nullptr, nullptr, STR("/Script/CoreUObject.ObjectProperty"));
        FClassProperty::m_static_obj = UObjectGlobals::static_find_object<UClass*>(nullptr, nullptr, STR("/Script/CoreUObject.ClassProperty"));
        FSoftClassProperty::m_static_obj = UObjectGlobals::static_find_object<UClass*>(nullptr, nullptr, STR("/Script/CoreUObject.SoftClassProperty"));
        FEnumProperty<uint8_t>::m_static_obj = UObjectGlobals::static_find_object<UClass*>(nullptr, nullptr, STR("/Script/CoreUObject.EnumProperty"));
        FArrayProperty::m_static_obj = UObjectGlobals::static_find_object<UClass*>(nullptr, nullptr, STR("/Script/CoreUObject.ArrayProperty"));
        FStructProperty::m_static_obj = UObjectGlobals::static_find_object<UClass*>(nullptr, nullptr, STR("/Script/CoreUObject.StructProperty"));
        FNameProperty::m_static_obj = UObjectGlobals::static_find_object<UClass*>(nullptr, nullptr, STR("/Script/CoreUObject.NameProperty"));
        XBoolProperty::m_static_obj = UObjectGlobals::static_find_object<UClass*>(nullptr, nullptr, STR("/Script/CoreUObject.BoolProperty"));
        FMapProperty::m_static_obj = UObjectGlobals::static_find_object<UClass*>(nullptr, nullptr, STR("/Script/CoreUObject.MapProperty"));
        FWeakObjectProperty::m_static_obj = UObjectGlobals::static_find_object<UClass*>(nullptr, nullptr, STR("/Script/CoreUObject.WeakObjectProperty"));
        FLazyObjectProperty::m_static_obj = UObjectGlobals::static_find_object<UClass*>(nullptr, nullptr, STR("/Script/CoreUObject.LazyObjectProperty"));
        FSoftObjectProperty::m_static_obj = UObjectGlobals::static_find_object<UClass*>(nullptr, nullptr, STR("/Script/CoreUObject.SoftObjectProperty"));
        FTextProperty::m_static_obj = UObjectGlobals::static_find_object<UClass*>(nullptr, nullptr, STR("/Script/CoreUObject.TextProperty"));
        FStrProperty::m_static_obj = UObjectGlobals::static_find_object<UClass*>(nullptr, nullptr, STR("/Script/CoreUObject.StrProperty"));
        FInterfaceProperty::m_static_obj = UObjectGlobals::static_find_object<UClass*>(nullptr, nullptr, STR("/Script/CoreUObject.InterfaceProperty"));
        FFieldPathProperty::m_static_obj = UObjectGlobals::static_find_object<UClass*>(nullptr, nullptr, STR("/Script/CoreUObject.FieldPathProperty"));
        //*/

        // FField / FProperty Types
        if (Version::IsAtLeast(4, 25))
        {
            auto find_all_property_types = [](const StringType& obj_string) -> void {
                UStruct* actor_obj = static_cast<UClass*>(UObjectGlobals::StaticFindObject_InternalSlow(nullptr, nullptr, obj_string.c_str()));
                if (!actor_obj) { return; }

                // Manually iterating fields here because 'ForEachProperty' isn't ready until after this function is done
                FField* field = actor_obj->GetChildProperties();
                while (field)
                {
                    // Hard-coded offset cast here because 'FField::GetClass' is not ready until after this function is done
                    FFieldClass* ffield_class = Helper::Casting::ptr_cast_deref<FFieldClass*>(field, FFieldClassOffset);
                    if (!ffield_class)
                    {
                        field = field->GetNextFFieldUnsafe();
                        continue;
                    }

                    FName type_name = ffield_class->GetFName();

                    // Populate the global FFieldClass maps for dynamic type lookup
                    if (!FFieldClass::GetNameToFieldClassMap().Contains(type_name))
                    {
                        FFieldClass::GetNameToFieldClassMap().Add(type_name, ffield_class);
                        FFieldClass::GetAllFieldClasses().Add(ffield_class);
                    }

                    // TODO: Look at the dumped objects and put every single FField type in here
                    // At the moment there are probably some missing types

                    // Fully supported
                    if (type_name == FName(STR("ObjectProperty"), FNAME_Find))
                    {
                        if ((ffield_class->GetCastFlags() & static_cast<uint64>(EClassCastFlags::CASTCLASS_FObjectPtrProperty)) != 0)
                        {
                            FObjectPtrProperty::StaticClassStorage = ffield_class;
                        }
                        else
                        {
                            FObjectProperty::StaticClassStorage = ffield_class;
                        }
                        FFieldClass* object_property_base_class = ffield_class->GetSuperClass();
                        FObjectPropertyBase::StaticClassStorage = object_property_base_class;

                        // Add FObjectPropertyBase to the map
                        if (object_property_base_class)
                        {
                            FName base_type_name = object_property_base_class->GetFName();
                            if (!FFieldClass::GetNameToFieldClassMap().Contains(base_type_name))
                            {
                                FFieldClass::GetNameToFieldClassMap().Add(base_type_name, object_property_base_class);
                                FFieldClass::GetAllFieldClasses().Add(object_property_base_class);
                            }
                        }
                    }
                    if (type_name == FName(STR("ObjectPtrProperty"), FNAME_Find))
                    {
                        // I don't think this is ever hit anymore, but I'm not entirely sure.
                        // It seems that FObjectPtrProperty uses the 'ObjectProperty FName in the final UE5.0 release.
                        FObjectPtrProperty::StaticClassStorage = ffield_class;
                    }
                    if (type_name == FName(STR("Int8Property"), FNAME_Find))
                    {
                        FInt8Property::StaticClassStorage = ffield_class;

                        // This doesn't need to be in 'Int8Property', it can be in any property
                        FFieldClass* ffield_super_class = ffield_class->GetSuperClass();
                        if (ffield_super_class)
                        {
                            do
                            {
                                FName super_type_name = ffield_super_class->GetFName();

                                // Add superclasses to the map as well
                                if (!FFieldClass::GetNameToFieldClassMap().Contains(super_type_name))
                                {
                                    FFieldClass::GetNameToFieldClassMap().Add(super_type_name, ffield_super_class);
                                    FFieldClass::GetAllFieldClasses().Add(ffield_super_class);
                                }

                                if (super_type_name == GPropertyName)
                                {
                                    FProperty::StaticClassStorage = ffield_super_class;
                                    FFieldClass* ffield_base_class = ffield_super_class->GetSuperClass();
                                    FField::StaticClassStorage = ffield_base_class;

                                    // Add FField base class to map
                                    if (ffield_base_class)
                                    {
                                        FName base_type_name = ffield_base_class->GetFName();
                                        if (!FFieldClass::GetNameToFieldClassMap().Contains(base_type_name))
                                        {
                                            FFieldClass::GetNameToFieldClassMap().Add(base_type_name, ffield_base_class);
                                            FFieldClass::GetAllFieldClasses().Add(ffield_base_class);
                                        }
                                    }
                                    break;
                                }

                                ffield_super_class = ffield_super_class->GetSuperClass();
                            } while (ffield_super_class);
                        }
                    }
                    if (type_name == FName(STR("Int16Property"), FNAME_Find))
                    {
                        FInt16Property::StaticClassStorage = ffield_class;
                    }
                    if (type_name == FName(STR("IntProperty"), FNAME_Find))
                    {
                        FIntProperty::StaticClassStorage = ffield_class;
                    }
                    if (type_name == FName(STR("Int64Property"), FNAME_Find))
                    {
                        FInt64Property::StaticClassStorage = ffield_class;
                    }
                    if (type_name == FName(STR("NameProperty"), FNAME_Find))
                    {
                        FNameProperty::StaticClassStorage = ffield_class;
                    }
                    if (type_name == FName(STR("FloatProperty"), FNAME_Find))
                    {
                        FFloatProperty::StaticClassStorage = static_cast<FFieldClass*>(ffield_class);

                        // 'NumericProperty' doesn't appear as the direct type for any properties
                        // Because of this, we need to use a property that we know has 'NumericProperty' in its super chain
                        // We're using 'FFloatProperty' here for no particular reason other than that it has 'NumericProperty' as it's super
                        FFieldClass* numeric_property_class = ffield_class->GetSuperClass();
                        FNumericProperty::StaticClassStorage = numeric_property_class;

                        // Add NumericProperty to the map
                        if (numeric_property_class)
                        {
                            FName numeric_type_name = numeric_property_class->GetFName();
                            if (!FFieldClass::GetNameToFieldClassMap().Contains(numeric_type_name))
                            {
                                FFieldClass::GetNameToFieldClassMap().Add(numeric_type_name, numeric_property_class);
                                FFieldClass::GetAllFieldClasses().Add(numeric_property_class);
                            }
                        }
                    }
                    if (type_name == FName(STR("DoubleProperty"), FNAME_Find))
                    {
                        FDoubleProperty::StaticClassStorage = ffield_class;
                    }
                    if (type_name == FName(STR("ByteProperty"), FNAME_Find))
                    {
                        FByteProperty::StaticClassStorage = ffield_class;
                    }
                    if (type_name == FName(STR("UInt16Property"), FNAME_Find))
                    {
                        FUInt16Property::StaticClassStorage = ffield_class;
                    }
                    if (type_name == FName(STR("UInt32Property"), FNAME_Find))
                    {
                        FUInt32Property::StaticClassStorage = ffield_class;
                    }
                    if (type_name == FName(STR("UInt64Property"), FNAME_Find))
                    {
                        FUInt64Property::StaticClassStorage = ffield_class;
                    }
                    if (type_name == FName(STR("BoolProperty"), FNAME_Find))
                    {
                        FBoolProperty::StaticClassStorage = ffield_class;
                    }
                    if (type_name == FName(STR("ArrayProperty"), FNAME_Find))
                    {
                        FArrayProperty::StaticClassStorage = ffield_class;

                        // Check inner element property for its type (e.g., AnsiStrProperty in arrays)
                        if (Version::IsAtLeast(5, 6))
                        {
                            FArrayProperty* array_prop = static_cast<FArrayProperty*>(field);
                            if (array_prop)
                            {
                                FProperty* inner_prop = array_prop->GetInner();
                                if (inner_prop)
                                {
                                    FFieldClass* inner_class = Helper::Casting::ptr_cast_deref<FFieldClass*>(inner_prop, FFieldClassOffset);
                                    if (inner_class)
                                    {
                                        FName inner_type_name = inner_class->GetFName();
                                        if (inner_type_name == FName(STR("AnsiStrProperty"), FNAME_Find))
                                        {
                                            FAnsiStrProperty::StaticClassStorage = inner_class;
                                        }
                                        else if (inner_type_name == FName(STR("Utf8StrProperty"), FNAME_Find))
                                        {
                                            FUtf8StrProperty::StaticClassStorage = inner_class;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if (type_name == FName(STR("SetProperty"), FNAME_Find))
                    {
                        FSetProperty::StaticClassStorage = ffield_class;

                        // Check inner element property for its type (e.g., AnsiStrProperty in sets)
                        if (Version::IsAtLeast(5, 6))
                        {
                            FSetProperty* set_prop = static_cast<FSetProperty*>(field);
                            if (set_prop)
                            {
                                FProperty* element_prop = set_prop->GetElementProp();
                                if (element_prop)
                                {
                                    FFieldClass* element_class = Helper::Casting::ptr_cast_deref<FFieldClass*>(element_prop, FFieldClassOffset);
                                    if (element_class)
                                    {
                                        FName element_type_name = element_class->GetFName();
                                        if (element_type_name == FName(STR("AnsiStrProperty"), FNAME_Find))
                                        {
                                            FAnsiStrProperty::StaticClassStorage = element_class;
                                        }
                                        else if (element_type_name == FName(STR("Utf8StrProperty"), FNAME_Find))
                                        {
                                            FUtf8StrProperty::StaticClassStorage = element_class;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if (type_name == FName(STR("MapProperty"), FNAME_Find))
                    {
                        FMapProperty::StaticClassStorage = ffield_class;

                        // Check inner key/value properties for their types (e.g., AnsiStrProperty in map keys)
                        if (Version::IsAtLeast(5, 6))
                        {
                            FMapProperty* map_prop = static_cast<FMapProperty*>(field);
                            if (map_prop)
                            {
                                // Check key property type
                                FProperty* key_prop = map_prop->GetKeyProp();
                                if (key_prop)
                                {
                                    FFieldClass* key_class = Helper::Casting::ptr_cast_deref<FFieldClass*>(key_prop, FFieldClassOffset);
                                    if (key_class)
                                    {
                                        FName key_type_name = key_class->GetFName();
                                        if (key_type_name == FName(STR("AnsiStrProperty"), FNAME_Find))
                                        {
                                            FAnsiStrProperty::StaticClassStorage = key_class;
                                        }
                                        else if (key_type_name == FName(STR("Utf8StrProperty"), FNAME_Find))
                                        {
                                            FUtf8StrProperty::StaticClassStorage = key_class;
                                        }
                                    }
                                }

                                // Check value property type
                                FProperty* value_prop = map_prop->GetValueProp();
                                if (value_prop)
                                {
                                    FFieldClass* value_class = Helper::Casting::ptr_cast_deref<FFieldClass*>(value_prop, FFieldClassOffset);
                                    if (value_class)
                                    {
                                        FName value_type_name = value_class->GetFName();
                                        if (value_type_name == FName(STR("AnsiStrProperty"), FNAME_Find))
                                        {
                                            FAnsiStrProperty::StaticClassStorage = value_class;
                                        }
                                        else if (value_type_name == FName(STR("Utf8StrProperty"), FNAME_Find))
                                        {
                                            FUtf8StrProperty::StaticClassStorage = value_class;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if (type_name == FName(STR("StructProperty"), FNAME_Find))
                    {
                        FStructProperty::StaticClassStorage = ffield_class;
                    }
                    if (type_name == FName(STR("ClassProperty"), FNAME_Find))
                    {
                        FClassProperty::StaticClassStorage = ffield_class;
                    }
                    if (type_name == FName(STR("ClassPtrProperty"), FNAME_Find))
                    {
                        FClassPtrProperty::StaticClassStorage = ffield_class;
                    }
                    if (type_name == FName(STR("SoftClassProperty"), FNAME_Find))
                    {
                        FSoftClassProperty::StaticClassStorage = ffield_class;
                    }
                    if (type_name == FName(STR("WeakObjectProperty"), FNAME_Find))
                    {
                        FWeakObjectProperty::StaticClassStorage = ffield_class;
                    }
                    if (type_name == FName(STR("LazyObjectProperty"), FNAME_Find))
                    {
                        FLazyObjectProperty::StaticClassStorage = ffield_class;
                    }
                    if (type_name == FName(STR("SoftObjectProperty"), FNAME_Find))
                    {
                        FSoftObjectProperty::StaticClassStorage = ffield_class;
                    }
                    if (type_name == FName(STR("EnumProperty"), FNAME_Find))
                    {
                        FEnumProperty::StaticClassStorage = ffield_class;
                    }
                    if (type_name == FName(STR("TextProperty"), FNAME_Find))
                    {
                        FTextProperty::StaticClassStorage = ffield_class;
                        FText::StaticSize_Private = static_cast<FStructProperty*>(field)->GetSize();
                    }
                    if (type_name == FName(STR("StrProperty"), FNAME_Find))
                    {
                        FStrProperty::StaticClassStorage = ffield_class;
                    }
                    if (Version::IsAtLeast(5, 6))
                    {
                        if (type_name == FName(STR("Utf8StrProperty"), FNAME_Find))
                        {
                            FUtf8StrProperty::StaticClassStorage = ffield_class;
                        }
                        if (type_name == FName(STR("AnsiStrProperty"), FNAME_Find))
                        {
                            FAnsiStrProperty::StaticClassStorage = ffield_class;
                        }
                    }
                    if (type_name == FName(STR("DelegateProperty"), FNAME_Find))
                    {
                        FDelegateProperty::StaticClassStorage = ffield_class;
                    }
                    if (type_name == FName(STR("MulticastInlineDelegateProperty"), FNAME_Find))
                    {
                        FMulticastInlineDelegateProperty::StaticClassStorage = ffield_class;
                        FFieldClass* multicast_delegate_class = ffield_class->GetSuperClass();
                        FMulticastDelegateProperty::StaticClassStorage = multicast_delegate_class;

                        // Add MulticastDelegateProperty to the map
                        if (multicast_delegate_class)
                        {
                            FName multicast_type_name = multicast_delegate_class->GetFName();
                            if (!FFieldClass::GetNameToFieldClassMap().Contains(multicast_type_name))
                            {
                                FFieldClass::GetNameToFieldClassMap().Add(multicast_type_name, multicast_delegate_class);
                                FFieldClass::GetAllFieldClasses().Add(multicast_delegate_class);
                            }
                        }

                        // Attempt to get the pointer to the FObjectProperty FFieldClass.
                        // It seems that all UObject parameters are of type FObjectProperty and not FObjectPtrProperty.
                        // This doesn't have to go in the delegate property section, it can also go in the UFunction section.
                        // The 'HashObject' function simply returns the address in a size_t, but keep this in mind if the 'HashObject' function ever changes.
                        if (Version::IsAtLeast(5, 0) && std::bit_cast<void*>(FObjectProperty::StaticClassStorage.HashObject()) == STATIC_CLASS_INVALID)
                        {
                            FMulticastInlineDelegateProperty* AsMulticastInlineDelegateProperty = static_cast<FMulticastInlineDelegateProperty*>(field);
                            for (FProperty* Param : TFieldRange<FProperty>(AsMulticastInlineDelegateProperty->GetSignatureFunction(), EFieldIterationFlags::IncludeDeprecated)) 
                            {
                                if (Param->GetClass().GetName() == STR("ObjectProperty"))
                                {
                                    FObjectProperty::StaticClassStorage = Param->GetClass();
                                    break;
                                }
                            }
                        }
                    }
                    if (type_name == FName(STR("MulticastSparseDelegateProperty"), FNAME_Find))
                    {
                        FMulticastSparseDelegateProperty::StaticClassStorage = ffield_class;
                    }
                    if (type_name == FName(STR("InterfaceProperty"), FNAME_Find))
                    {
                        FInterfaceProperty::StaticClassStorage = ffield_class;
                    }
                    if (type_name == FName(STR("FieldPathProperty"), FNAME_Find))
                    {
                        FFieldPathProperty::StaticClassStorage = ffield_class;
                    }
                    if (Version::IsAtLeast(5, 4)) {
                        if (type_name == FName(STR("OptionalProperty"), FNAME_Find))
                        {
                            FOptionalProperty::StaticClassStorage = ffield_class;
                        }
                    }

                    field = field->GetNextFFieldUnsafe();
                }
            };

            // TODO: Maybe replace all of the calls to 'find_all_property_types' with a GUObjectArray iteration with an early exit once everything's been found ?

            // Bool, Enum, Byte, Struct, Float, Object, Name, Int, Array
            // WeakObject, MulticastSparseDelegate
            find_all_property_types(STR("/Script/Engine.Actor"));
            // Class
            find_all_property_types(STR("/Script/Engine.Pawn"));
            // Str, Map
            find_all_property_types(STR("/Script/Engine.NetDriver"));
            // Double
            find_all_property_types(STR("/Script/Engine.NetConnection"));
            // Text
            find_all_property_types(STR("/Script/Engine.GameModeBase"));
            // Int8, LazyObject
            find_all_property_types(STR("/Script/Landscape.LandscapeComponent"));
            find_all_property_types(STR("/Script/VariantManagerContent.VariantObjectBinding"));
            // UInt16, UInt32, UInt64, Int8, Int16, Int64
            find_all_property_types(STR("/Script/Engine.IntSerialization"));
            // Set, MulticastInlineDelegate, Delegate
            find_all_property_types(STR("/Script/Engine.AudioComponent"));
            // MulticastInlineDelegate, Interface
            find_all_property_types(STR("/Script/MovieScene.MovieSceneSequencePlayer"));
            // Delegate
            find_all_property_types(STR("/Script/UMG.Widget"));
            // SoftObject
            find_all_property_types(STR("/Script/Engine.LevelStreaming"));
            // SoftClass
            find_all_property_types(STR("/Script/Engine.PrimaryAssetTypeInfo"));
            // FieldPath
            find_all_property_types(STR("/Script/Engine.InterpTrackInstProperty"));
            find_all_property_types(STR("/Script/MovieSceneTracks.MovieSceneEventPtrs"));
            // TOptional
            if (Version::IsAtLeast(5, 4))
            {
                find_all_property_types(STR("/Script/Engine.WorldPartitionRuntimeCellData"));
            }
            // FUtf8StrProperty
            if (Version::IsAtLeast(5, 6))
            {
                find_all_property_types(STR("/Script/CoreUObject.VerseEnum"));
            }
            // FAnsiStrProperty
            if (Version::IsAtLeast(5, 7))
            {
                find_all_property_types(STR("/Script/CoreUObject.VerseClass"));
            }
        }
        else
        {
            // 4.24 and earlier, just use StaticFindObject to find all of the property type pointers

            auto add_property = []<typename PropertyType>(const CharType* full_property_name, [[maybe_unused]]PropertyType property_type_object) {
                UObject* property = UObjectGlobals::StaticFindObject_InternalSlow(nullptr, nullptr, full_property_name);
                if (!property)
                {
                    // TODO: Put this error back when you've confirmed when every property type was introduced and you're only trying to find it in those versions and later
                    /*
                    StringType error = fmt::format(STR("Was unable to find pointer to '{}'"), full_property_name);
                    std::string error_ansi = std::string(error.begin(), error.end());
                    throw std::runtime_error{error_ansi};
                    //*/
                    return;
                }

                if constexpr (!std::is_same_v<PropertyType, int32_t>)
                {
                    PropertyType::StaticClassStorage = static_cast<UClass*>(property);
                }
                if constexpr (std::is_same_v<PropertyType, FTextProperty>)
                {
                    auto attempt_to_set_ftext_size = [](const CharType* property_name) {
                        if (FText::StaticSize_Private > 0)
                        {
                            return;
                        }
                        // Casting UObject* to FProperty* is safe in <4.25
                        UObject* text_property_instance = UObjectGlobals::StaticFindObject_InternalSlow(nullptr, nullptr, property_name);
                        if (text_property_instance)
                        {
                            if (const auto size = std::bit_cast<PropertyType*>(text_property_instance)->GetSize(); size > 0)
                            {
                                FText::StaticSize_Private = size;
                            }
                        }
                    };
                    attempt_to_set_ftext_size(STR("/Script/Engine.GameMode:DefaultPlayerName"));
                    attempt_to_set_ftext_size(STR("/Script/Engine.TextRenderComponent:Text"));
                    attempt_to_set_ftext_size(STR("/Script/UMG.EditableText:Text"));
                    attempt_to_set_ftext_size(STR("/Script/Engine.SubtitleCue:Text"));
                    attempt_to_set_ftext_size(STR("/Script/Engine.BPVariableDescription:Category"));
                    attempt_to_set_ftext_size(STR("/Script/Engine.SpriteCategoryInfo:DisplayName"));
                }
            };

            add_property(STR("/Script/CoreUObject.ObjectProperty"), FObjectProperty{});
            // AssetObjectProperty & AssetClassProperty only exists in <4.18.
            add_property(STR("/Script/CoreUObject.AssetObjectProperty"), FAssetObjectProperty{});
            add_property(STR("/Script/CoreUObject.AssetClassProperty"), FAssetClassProperty{});
            add_property(STR("/Script/CoreUObject.NumericProperty"), FNumericProperty{});
            add_property(STR("/Script/CoreUObject.Int8Property"), FInt8Property{});
            add_property(STR("/Script/CoreUObject.Int16Property"), FInt16Property{});
            add_property(STR("/Script/CoreUObject.IntProperty"), FIntProperty{});
            add_property(STR("/Script/CoreUObject.Int64Property"), FInt64Property{});
            add_property(STR("/Script/CoreUObject.NameProperty"), FNameProperty{});
            add_property(STR("/Script/CoreUObject.FloatProperty"), FFloatProperty{});
            add_property(STR("/Script/CoreUObject.DoubleProperty"), FDoubleProperty{});
            add_property(STR("/Script/CoreUObject.ByteProperty"), FByteProperty{});
            add_property(STR("/Script/CoreUObject.UInt16Property"), FUInt16Property{});
            add_property(STR("/Script/CoreUObject.UInt32Property"), FUInt32Property{});
            add_property(STR("/Script/CoreUObject.UInt64Property"), FUInt64Property{});
            add_property(STR("/Script/CoreUObject.BoolProperty"), FBoolProperty{});
            add_property(STR("/Script/CoreUObject.ArrayProperty"), FArrayProperty{});
            add_property(STR("/Script/CoreUObject.MapProperty"), FMapProperty{});
            add_property(STR("/Script/CoreUObject.StructProperty"), FStructProperty{});
            add_property(STR("/Script/CoreUObject.ClassProperty"), FClassProperty{});
            add_property(STR("/Script/CoreUObject.SoftClassProperty"), FSoftClassProperty{});
            add_property(STR("/Script/CoreUObject.WeakObjectProperty"), FWeakObjectProperty{});
            add_property(STR("/Script/CoreUObject.LazyObjectProperty"), FLazyObjectProperty{});
            add_property(STR("/Script/CoreUObject.SoftObjectProperty"), FSoftObjectProperty{});
            if (Version::IsAtLeast(4, 15)) { add_property(STR("/Script/CoreUObject.EnumProperty"), FEnumProperty{}); }
            add_property(STR("/Script/CoreUObject.TextProperty"), FTextProperty{});
            add_property(STR("/Script/CoreUObject.StrProperty"), FStrProperty{});
            add_property(STR("/Script/CoreUObject.DelegateProperty"), FDelegateProperty{});
            add_property(STR("/Script/CoreUObject.MulticastDelegateProperty"), FMulticastDelegateProperty{});
            if (Version::IsAtLeast(4, 23)) { add_property(STR("/Script/CoreUObject.MulticastInlineDelegateProperty"), FMulticastInlineDelegateProperty{}); }
            if (Version::IsAtLeast(4, 23)) { add_property(STR("/Script/CoreUObject.MulticastSparseDelegateProperty"), FMulticastSparseDelegateProperty{}); }
            add_property(STR("/Script/CoreUObject.InterfaceProperty"), FInterfaceProperty{});

            // Not yet supported, only here for completion and to prevent crashes
            // Not all of these will be found right now, need to call this function with more UObjects that actually have these properties
            add_property(STR("/Script/CoreUObject.SetProperty"), FSetProperty{});

            // Find the root 'Property' FField. This may not be necessary but I'm leaving it here for now, might be useful later.
            add_property(STR("/Script/CoreUObject.Property"), FProperty{});
        }

        if (FText::StaticSize() == 0)
        {
            FText::StaticSize_Private = sizeof(FText);
            Output::send<LogLevel::Warning>(STR("Was unable to detect FText size, using default: 0x{:X} bytes.\n"), FText::StaticSize());
        }
        else
        {
            Output::send(STR("FText size detected as 0x{:X} bytes.\n"), FText::StaticSize());
        }

        return true;
    }

    auto TypeChecker::is_property(FField* field) -> bool
    {
        UObject* object = std::bit_cast<UObject*>(field);
        return is_property(object);
    }

    auto TypeChecker::is_property(UObject* object) -> bool
    {
        UClass* obj_class = object->GetClassPrivate();
        if (!obj_class) { return false; }

        if (obj_class->GetNamePrivate() == GPropertyName) { return true; }

        UStruct* super_struct = obj_class->GetSuperStruct();
        while (super_struct)
        {
            if (super_struct->GetNamePrivate() == GPropertyName)
            {
                return true;
            }

            super_struct = super_struct->GetSuperStruct();
        }

        return false;
    }
}