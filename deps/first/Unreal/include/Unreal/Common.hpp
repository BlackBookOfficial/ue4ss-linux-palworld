#pragma once


#ifdef _WIN32
#define FORCENOINLINE __declspec(noinline)
#define FORCEINLINE __forceinline
#define RESTRICT __restrict
#else
#define FORCENOINLINE __attribute__((noinline))
#define FORCEINLINE inline __attribute__((always_inline))
#define RESTRICT __restrict__
#endif

#ifndef RC_UNREAL_EXPORTS
#ifndef RC_UNREAL_BUILD_STATIC
#ifndef RC_UE_API
#ifdef _WIN32
#define RC_UE_API __declspec(dllimport)
#else
#define RC_UE_API __attribute__((visibility("default")))
#endif
#endif
#else
#ifndef RC_UE_API
#define RC_UE_API
#endif
#endif
#else
#ifndef RC_UE_API
#ifdef _WIN32
#define RC_UE_API __declspec(dllexport)
#else
#define RC_UE_API __attribute__((visibility("default")))
#endif
#endif
#endif


