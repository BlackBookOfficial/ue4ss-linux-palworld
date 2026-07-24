#pragma once

#ifndef RC_UE4SS_EXPORTS
#ifndef RC_UE4SS_API
#ifdef _WIN32
#define RC_UE4SS_API __declspec(dllimport)
#else
#define RC_UE4SS_API
#endif
#endif
#else
#ifndef RC_UE4SS_API
#ifdef _WIN32
#define RC_UE4SS_API __declspec(dllexport)
#else
#define RC_UE4SS_API __attribute__((visibility("default")))
#endif
#endif
#endif
