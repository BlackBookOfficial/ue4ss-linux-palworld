#pragma once

#include <Unreal/UObject.hpp>

namespace RC::Unreal
{
    class RC_UE_API UPackage : public UObject
    {
        DECLARE_EXTERNAL_OBJECT_CLASS_WITH_CAST(UPackage, CoreUObject, CASTCLASS_UPackage)
    public:
        // Placeholder for now, but is there even anything inside that would be useful ?
        // It's needed regardless because it's used in a few places but not in any way that's different to a UObject
    };

    /** Returns the transient top-level package, which is useful for temporarily storing objects that should never be saved */
    UPackage* GetTransientPackage();
}



