#pragma once

#ifndef RC_FILE_EXPORTS
#ifndef RC_FILE_BUILD_STATIC
#ifndef RC_FILE_API
#ifdef _WIN32
#define RC_FILE_API __declspec(dllimport)
#else
#define RC_FILE_API
#endif
#endif
#else
#ifndef RC_FILE_API
#define RC_FILE_API
#endif
#endif
#else
#ifndef RC_FILE_API
#ifdef _WIN32
#define RC_FILE_API __declspec(dllexport)
#else
#define RC_FILE_API __attribute__((visibility("default")))
#endif
#endif
#endif
