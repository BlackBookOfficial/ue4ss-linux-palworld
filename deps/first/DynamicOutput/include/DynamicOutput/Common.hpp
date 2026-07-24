#pragma once

#ifndef RC_DYNAMIC_OUTPUT_EXPORTS
#ifndef RC_DYNAMIC_OUTPUT_BUILD_STATIC
#ifndef RC_DYNOUT_API
#ifdef _WIN32
#define RC_DYNOUT_API __declspec(dllimport)
#else
#define RC_DYNOUT_API
#endif
#endif
#else
#ifndef RC_DYNOUT_API
#define RC_DYNOUT_API
#endif
#endif
#else
#ifndef RC_DYNOUT_API
#ifdef _WIN32
#define RC_DYNOUT_API __declspec(dllexport)
#else
#define RC_DYNOUT_API __attribute__((visibility("default")))
#endif
#endif
#endif
