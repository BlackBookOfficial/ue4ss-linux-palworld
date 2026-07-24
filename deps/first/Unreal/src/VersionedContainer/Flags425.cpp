#include <Unreal/VersionedContainer/Flags425.hpp>

namespace RC::Unreal
{
    auto Flags425::to_impl_flags(const EObjectFlags flags) -> EObjectFlags_Impl
    {
        EObjectFlags_Impl flags_impl{};

        if ((flags & EObjectFlags::RF_NoFlags) != 0)  flags_impl |= EObjectFlags_Impl::RF_NoFlags;
        if ((flags & EObjectFlags::RF_Public) != 0)  flags_impl |= EObjectFlags_Impl::RF_Public;
        if ((flags & EObjectFlags::RF_Standalone) != 0)  flags_impl |= EObjectFlags_Impl::RF_Standalone;
        if ((flags & EObjectFlags::RF_MarkAsNative) != 0)  flags_impl |= EObjectFlags_Impl::RF_MarkAsNative;
        if ((flags & EObjectFlags::RF_Transactional) != 0)  flags_impl |= EObjectFlags_Impl::RF_Transactional;
        if ((flags & EObjectFlags::RF_ClassDefaultObject) != 0)  flags_impl |= EObjectFlags_Impl::RF_ClassDefaultObject;
        if ((flags & EObjectFlags::RF_ArchetypeObject) != 0)  flags_impl |= EObjectFlags_Impl::RF_ArchetypeObject;
        if ((flags & EObjectFlags::RF_Transient) != 0)  flags_impl |= EObjectFlags_Impl::RF_Transient;
        if ((flags & EObjectFlags::RF_MarkAsRootSet) != 0)  flags_impl |= EObjectFlags_Impl::RF_MarkAsRootSet;
        if ((flags & EObjectFlags::RF_TagGarbageTemp) != 0) flags_impl |= EObjectFlags_Impl::RF_TagGarbageTemp;
        if ((flags & EObjectFlags::RF_NeedInitialization) != 0) flags_impl |= EObjectFlags_Impl::RF_NeedInitialization;
        if ((flags & EObjectFlags::RF_NeedLoad) != 0) flags_impl |= EObjectFlags_Impl::RF_NeedLoad;
        if ((flags & EObjectFlags::RF_KeepForCooker) != 0) flags_impl |= EObjectFlags_Impl::RF_KeepForCooker;
        if ((flags & EObjectFlags::RF_NeedPostLoad) != 0) flags_impl |= EObjectFlags_Impl::RF_NeedPostLoad;
        if ((flags & EObjectFlags::RF_NeedPostLoadSubobjects) != 0) flags_impl |= EObjectFlags_Impl::RF_NeedPostLoadSubobjects;
        if ((flags & EObjectFlags::RF_NewerVersionExists) != 0) flags_impl |= EObjectFlags_Impl::RF_NewerVersionExists;
        if ((flags & EObjectFlags::RF_BeginDestroyed) != 0) flags_impl |= EObjectFlags_Impl::RF_BeginDestroyed;
        if ((flags & EObjectFlags::RF_FinishDestroyed) != 0) flags_impl |= EObjectFlags_Impl::RF_FinishDestroyed;
        if ((flags & EObjectFlags::RF_BeingRegenerated) != 0) flags_impl |= EObjectFlags_Impl::RF_BeingRegenerated;
        if ((flags & EObjectFlags::RF_DefaultSubObject) != 0) flags_impl |= EObjectFlags_Impl::RF_DefaultSubObject;
        if ((flags & EObjectFlags::RF_WasLoaded) != 0) flags_impl |= EObjectFlags_Impl::RF_WasLoaded;
        if ((flags & EObjectFlags::RF_TextExportTransient) != 0) flags_impl |= EObjectFlags_Impl::RF_TextExportTransient;
        if ((flags & EObjectFlags::RF_LoadCompleted) != 0) flags_impl |= EObjectFlags_Impl::RF_LoadCompleted;
        if ((flags & EObjectFlags::RF_InheritableComponentTemplate) != 0) flags_impl |= EObjectFlags_Impl::RF_InheritableComponentTemplate;
        if ((flags & EObjectFlags::RF_DuplicateTransient) != 0) flags_impl |= EObjectFlags_Impl::RF_DuplicateTransient;
        if ((flags & EObjectFlags::RF_StrongRefOnFrame) != 0) flags_impl |= EObjectFlags_Impl::RF_StrongRefOnFrame;
        if ((flags & EObjectFlags::RF_NonPIEDuplicateTransient) != 0) flags_impl |= EObjectFlags_Impl::RF_NonPIEDuplicateTransient;
        if ((flags & EObjectFlags::RF_Dynamic) != 0) flags_impl |= EObjectFlags_Impl::RF_Dynamic;
        if ((flags & EObjectFlags::RF_WillBeLoaded) != 0) flags_impl |= EObjectFlags_Impl::RF_WillBeLoaded;
        if ((flags & EObjectFlags::RF_HasExternalPackage) != 0) flags_impl |= EObjectFlags_Impl::RF_HasExternalPackage;

        return flags_impl;
    }
}