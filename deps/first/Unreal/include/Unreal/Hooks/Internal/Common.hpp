#ifndef UE_HOOK_DEFINES
#define UE_HOOK_DEFINES

#ifdef UE_HOOK_TEST
    #define UE_HOOK_PRIVATE public
    #define UE_HOOK_PROTECTED public
#else
    #define UE_HOOK_PRIVATE private
    #define UE_HOOK_PROTECTED protected
#endif

#endif