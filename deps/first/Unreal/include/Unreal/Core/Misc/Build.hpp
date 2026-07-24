// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


/*--------------------------------------------------------------------------------
    Build configuration coming from UBT, do not modify
--------------------------------------------------------------------------------*/

// Set any configuration not defined by UBT to zero
#ifndef UE_BUILD_DEBUG
    #define UE_BUILD_DEBUG                0
#endif
#ifndef UE_BUILD_DEVELOPMENT
    #define UE_BUILD_DEVELOPMENT        0
#endif
#ifndef UE_BUILD_TEST
    #define UE_BUILD_TEST                0
#endif
#ifndef UE_BUILD_SHIPPING
    #define UE_BUILD_SHIPPING            0
#endif
#ifndef UE_GAME
    #define UE_GAME                        0
#endif
#ifndef UE_EDITOR
    #define UE_EDITOR                    0
#endif
#ifndef UE_BUILD_SHIPPING_WITH_EDITOR
    #define UE_BUILD_SHIPPING_WITH_EDITOR 0
#endif
#ifndef UE_BUILD_DOCS
    #define UE_BUILD_DOCS                0
#endif

/** 
 *   Whether compiling for dedicated server or not.
 */
#ifndef UE_SERVER
    #define UE_SERVER                    0
#endif

// Ensure that we have one, and only one build config coming from UBT
#if UE_BUILD_DEBUG + UE_BUILD_DEVELOPMENT + UE_BUILD_TEST + UE_BUILD_SHIPPING != 1
    #error Exactly one of [UE_BUILD_DEBUG UE_BUILD_DEVELOPMENT UE_BUILD_TEST UE_BUILD_SHIPPING] should be defined to be 1
#endif


/** Whether to use the null RHI. */
#ifndef USE_NULL_RHI
    #define USE_NULL_RHI 0
#endif

#ifndef USE_CHECKS_IN_SHIPPING
    #define USE_CHECKS_IN_SHIPPING 0
#endif

/** If not defined follow the CHECK behavior since previously ensures were compiled in with checks */
#ifndef USE_ENSURES_IN_SHIPPING
    #define USE_ENSURES_IN_SHIPPING USE_CHECKS_IN_SHIPPING
#endif

/** Compile flag to force stats to be compiled */
#ifndef FORCE_USE_STATS
    #define FORCE_USE_STATS 0
#endif

/**
 *    Optionally enable support for named events from the stat macros without the stat system overhead
 *    This will attempt to disable regular stats system and use named events instead
 */
#ifndef ENABLE_STATNAMEDEVENTS
    #define ENABLE_STATNAMEDEVENTS    0
#endif

#ifndef ENABLE_STATNAMEDEVENTS_UOBJECT
    #define ENABLE_STATNAMEDEVENTS_UOBJECT 0
#endif

/*--------------------------------------------------------------------------------
    Basic options that by default depend on the build configuration and platform

    DO_GUARD_SLOW                                    If true, then checkSlow, checkfSlow and verifySlow are compiled into the executable.
    DO_CHECK                                        If true, then checkCode, checkf, verify, check, checkNoEntry, checkNoReentry, checkNoRecursion, verifyf, checkf are compiled into the executables
    DO_ENSURE                                        If true, then ensure, ensureAlways, ensureMsgf and ensureAlwaysMsgf are compiled into the executables
    STATS                                            If true, then the stats system is compiled into the executable.
    ALLOW_DEBUG_FILES                                If true, then debug files like screen shots and profiles can be saved from the executable.
    NO_LOGGING                                        If true, then no logs or text output will be produced

--------------------------------------------------------------------------------*/

#if UE_BUILD_DEBUG
    #ifndef DO_GUARD_SLOW
        #define DO_GUARD_SLOW                                    1
    #endif
    #ifndef DO_CHECK
        #define DO_CHECK                                        1
    #endif
    #ifndef DO_ENSURE
        #define DO_ENSURE                                        1
    #endif
    #ifndef STATS
        #define STATS                                            ((WITH_UNREAL_DEVELOPER_TOOLS || !WITH_EDITORONLY_DATA || USE_STATS_WITHOUT_ENGINE || USE_MALLOC_PROFILER || FORCE_USE_STATS) && !ENABLE_STATNAMEDEVENTS)
    #endif
    #ifndef ALLOW_DEBUG_FILES
        #define ALLOW_DEBUG_FILES                                1
    #endif
    #ifndef NO_LOGGING
        #define NO_LOGGING                                        0
    #endif
#elif UE_BUILD_DEVELOPMENT
    #ifndef DO_GUARD_SLOW
        #define DO_GUARD_SLOW                                    0
    #endif
    #ifndef DO_CHECK
        #define DO_CHECK                                        1
    #endif
    #ifndef DO_ENSURE
        #define DO_ENSURE                                        1
    #endif
    #ifndef STATS
        #define STATS                                            ((WITH_UNREAL_DEVELOPER_TOOLS || !WITH_EDITORONLY_DATA || USE_STATS_WITHOUT_ENGINE || USE_MALLOC_PROFILER || FORCE_USE_STATS) && !ENABLE_STATNAMEDEVENTS)
    #endif
    #ifndef ALLOW_DEBUG_FILES
        #define ALLOW_DEBUG_FILES                                1
    #endif
    #ifndef NO_LOGGING
        #define NO_LOGGING                                        0
    #endif
#elif UE_BUILD_TEST
    #ifndef DO_GUARD_SLOW
        #define DO_GUARD_SLOW                                    0
    #endif
    #ifndef DO_CHECK
        #define DO_CHECK                                        USE_CHECKS_IN_SHIPPING
    #endif
    #ifndef DO_ENSURE
        #define DO_ENSURE                                        USE_ENSURES_IN_SHIPPING
    #endif
    #ifndef STATS
        #define STATS                                            ((USE_MALLOC_PROFILER || FORCE_USE_STATS) && !ENABLE_STATNAMEDEVENTS)
    #endif
    #ifndef ALLOW_DEBUG_FILES
        #define ALLOW_DEBUG_FILES                                1
    #endif
    #ifndef NO_LOGGING
        #define NO_LOGGING                                        !USE_LOGGING_IN_SHIPPING
    #endif
#elif UE_BUILD_SHIPPING
    #if WITH_EDITOR
        #ifndef DO_GUARD_SLOW
            #define DO_GUARD_SLOW                                0
        #endif
        #ifndef DO_CHECK
            #define DO_CHECK                                    1
        #endif
        #ifndef DO_ENSURE
            #define DO_ENSURE                                    1
        #endif
        #ifndef STATS
            #define STATS                                        1
        #endif
        #ifndef ALLOW_DEBUG_FILES
            #define ALLOW_DEBUG_FILES                            1
        #endif
        #ifndef NO_LOGGING
            #define NO_LOGGING                                    0
        #endif
    #else
        #ifndef DO_GUARD_SLOW
            #define DO_GUARD_SLOW                                0
        #endif
        #ifndef DO_CHECK
            #define DO_CHECK                                    USE_CHECKS_IN_SHIPPING
        #endif
        #ifndef DO_ENSURE
            #define DO_ENSURE                                    USE_ENSURES_IN_SHIPPING
        #endif
        #ifndef STATS
            #define STATS                                        (FORCE_USE_STATS && !ENABLE_STATNAMEDEVENTS)
        #endif
        #ifndef ALLOW_DEBUG_FILES
            #define ALLOW_DEBUG_FILES                            0
        #endif
        #ifndef NO_LOGGING
            #define NO_LOGGING                                    !USE_LOGGING_IN_SHIPPING
        #endif
    #endif
#else
    #error Exactly one of [UE_BUILD_DEBUG UE_BUILD_DEVELOPMENT UE_BUILD_TEST UE_BUILD_SHIPPING] should be defined to be 1
#endif


/**
 * This is a global setting which will turn on logging / checks for things which are
 * considered especially bad for consoles.  Some of the checks are probably useful for PCs also.
 *
 * Throughout the code base there are specific things which dramatically affect performance and/or
 * are good indicators that something is wrong with the content.  These have PERF_ISSUE_FINDER in the
 * comment near the define to turn the individual checks on. 
 *
 * e.g. #if defined(PERF_LOG_DYNAMIC_LOAD_OBJECT) || LOOKING_FOR_PERF_ISSUES
 *
 * If one only cares about DLO, then one can enable the PERF_LOG_DYNAMIC_LOAD_OBJECT define.  Or one can
 * globally turn on all PERF_ISSUE_FINDERS :-)
 *
 **/
#ifndef LOOKING_FOR_PERF_ISSUES
    #define LOOKING_FOR_PERF_ISSUES (0 && !(UE_BUILD_SHIPPING))
#endif

/** Enable the use of the network profiler as long as we are not a Shipping or Test build */
#ifndef USE_NETWORK_PROFILER
#define USE_NETWORK_PROFILER !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
#endif

/** Enable perf counters on dedicated servers */
#define USE_SERVER_PERF_COUNTERS ((UE_SERVER || UE_EDITOR) && WITH_PERFCOUNTERS)

#define USE_CIRCULAR_DEPENDENCY_LOAD_DEFERRING 1
#define USE_DEFERRED_DEPENDENCY_CHECK_VERIFICATION_TESTS (USE_CIRCULAR_DEPENDENCY_LOAD_DEFERRING && 0)

// 0 (default), set this to 1 to get draw events with "TOGGLEDRAWEVENTS" "r.ShowMaterialDrawEvents" and the "ProfileGPU" command working in test
#ifndef ALLOW_PROFILEGPU_IN_TEST
    #define ALLOW_PROFILEGPU_IN_TEST 0
#endif

#ifndef ALLOW_PROFILEGPU_IN_SHIPPING
    #define ALLOW_PROFILEGPU_IN_SHIPPING 0
#endif

// draw events with "TOGGLEDRAWEVENTS" "r.ShowMaterialDrawEvents" (for ProfileGPU, Pix, Razor, RenderDoc, ...) and the "ProfileGPU" command are normally compiled out for TEST and SHIPPING
#define WITH_PROFILEGPU (!(UE_BUILD_SHIPPING || UE_BUILD_TEST) || (UE_BUILD_TEST && ALLOW_PROFILEGPU_IN_TEST) || (UE_BUILD_SHIPPING && ALLOW_PROFILEGPU_IN_SHIPPING))


// Controls the creation of a thread for detecting hangs (FThreadHeartBeat). This is subject to other criteria, USE_HANG_DETECTION
#ifndef ALLOW_HANG_DETECTION
    #define ALLOW_HANG_DETECTION 1
#endif
#define USE_HANG_DETECTION (ALLOW_HANG_DETECTION && !WITH_EDITORONLY_DATA && !IS_PROGRAM && !UE_BUILD_DEBUG && !ENABLE_PGO_PROFILE)

// Controls the creation of a thread for detecting hitches (FGameThreadHitchHeartBeat). This is subject to other criteria, USE_HITCH_DETECTION
#ifndef ALLOW_HITCH_DETECTION
    #define ALLOW_HITCH_DETECTION 0
#endif

// Adjust a few things with the slack policy and MallocBinned2 to minimize memory usage (at some performance cost)
#ifndef AGGRESSIVE_MEMORY_SAVING
    #define AGGRESSIVE_MEMORY_SAVING 0
#endif

// Controls if UObjects are initialized as soon as they are available or only after the module is "loaded". This only applies to monolithic builds; if there are DLLs, this is how it works anyway and this should not be turned on
#ifndef USE_PER_MODULE_UOBJECT_BOOTSTRAP
    #define USE_PER_MODULE_UOBJECT_BOOTSTRAP 0
#endif

#define USE_HITCH_DETECTION (ALLOW_HITCH_DETECTION && !WITH_EDITORONLY_DATA && !IS_PROGRAM && !UE_BUILD_DEBUG)

// Controls whether shipping builds create backups of the most recent log file.
// All other configurations always create backups.
#ifndef PRESERVE_LOG_BACKUPS_IN_SHIPPING
    #define PRESERVE_LOG_BACKUPS_IN_SHIPPING 1
#endif
