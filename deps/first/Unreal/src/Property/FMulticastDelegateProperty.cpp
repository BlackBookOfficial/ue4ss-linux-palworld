#include <Unreal/CoreUObject/UObject/UnrealType.hpp>
#include <Unreal/VersionedContainer/UnrealVirtualImpl/UnrealVirtualBaseVC.hpp>
#include <Helpers/Casting.hpp>

namespace RC::Unreal
{
    IMPLEMENT_FIELD_CLASS(FMulticastDelegateProperty);
    std::unordered_map<File::StringType, uint32_t> FMulticastDelegateProperty::VTableLayoutMap;

#include <MemberVariableLayout_SrcWrapper_FMulticastDelegateProperty.hpp>
    
    const FMulticastScriptDelegate* FMulticastDelegateProperty::GetMulticastDelegate(const void* PropertyValue) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FMulticastDelegateProperty,
                                         GetMulticastDelegate,
                                         FMulticastScriptDelegate*,
                                         PARAMS(const void*),
                                         ARGS(PropertyValue))
    }
    void FMulticastDelegateProperty::SetMulticastDelegate(void* PropertyValue, FMulticastScriptDelegate ScriptDelegate) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FMulticastDelegateProperty,
                                         SetMulticastDelegate,
                                         void,
                                         PARAMS(void*, FMulticastScriptDelegate),
                                         ARGS(PropertyValue, ScriptDelegate))
    }

    void FMulticastDelegateProperty::AddDelegate(FScriptDelegate ScriptDelegate, UObject* Parent, void* PropertyValue) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FMulticastDelegateProperty,
                                         AddDelegate,
                                         void,
                                         PARAMS(FScriptDelegate, UObject*, void*),
                                         ARGS(ScriptDelegate, Parent, PropertyValue))
    }

    void FMulticastDelegateProperty::RemoveDelegate(const FScriptDelegate& ScriptDelegate, UObject* Parent, void* PropertyValue) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FMulticastDelegateProperty,
                                         RemoveDelegate,
                                         void,
                                         PARAMS(const FScriptDelegate&, UObject*, void*),
                                         ARGS(ScriptDelegate, Parent, PropertyValue))
    }

    void FMulticastDelegateProperty::ClearDelegate(UObject* Parent, void* PropertyValue) const
    {
        IMPLEMENT_UNREAL_VIRTUAL_WRAPPER(FMulticastDelegateProperty,
                                         ClearDelegate,
                                         void,
                                         PARAMS(UObject*, void*),
                                         ARGS(Parent, PropertyValue))
    }
}
