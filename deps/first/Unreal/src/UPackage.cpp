#include <Unreal/UPackage.hpp>
#include <Unreal/CoreUObject/UObject/Class.hpp>

namespace RC::Unreal
{
    static UPackage* GObjTransientPkg = NULL;    
    IMPLEMENT_EXTERNAL_OBJECT_CLASS(UPackage);

    UPackage* GetTransientPackage()
    {
      return GObjTransientPkg;
    }
}
