#pragma once

#ifndef RC_ASM_HELPER_EXPORTS
#ifndef RC_ASM_HELPER_BUILD_STATIC
#ifndef RC_ASM_API
#ifdef _WIN32
#define RC_ASM_API __declspec(dllimport)
#else
#define RC_ASM_API
#endif
#endif
#else
#ifndef RC_ASM_API
#define RC_ASM_API
#endif
#endif
#else
#ifndef RC_ASM_API
#ifdef _WIN32
#define RC_ASM_API __declspec(dllexport)
#else
#define RC_ASM_API __attribute__((visibility("default")))
#endif
#endif
#endif
