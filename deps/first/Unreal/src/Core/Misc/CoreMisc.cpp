#include <Unreal/Core/Misc/CoreMisc.hpp>
#include <Unreal/Core/Misc/CoreGlobals.hpp>

namespace RC::Unreal
{
    void EnsureRetrievingVTablePtrDuringCtor(const TCHAR* CtorSignature)
    {
        // UE4SS CHANGE -> START
        /*UE_CLOG(!GIsRetrievingVTablePtr, LogCore, Fatal, TEXT("The %s constructor is for internal usage only for hot-reload purposes. Please do NOT use it."), CtorSignature);*/
        throw std::runtime_error{"The called constructor is for internal usage only for hot-reload purposes. Please do NOT use it."};
        // UE4SS CHANGE -> END
    }
}
