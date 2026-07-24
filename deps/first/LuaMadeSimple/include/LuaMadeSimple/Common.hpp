#pragma once

#ifndef RC_LUA_MADE_SIMPLE_EXPORTS
#ifndef RC_LUA_MADE_SIMPLE_BUILD_STATIC
#ifndef RC_LMS_API
#ifdef _WIN32
#define RC_LMS_API __declspec(dllimport)
#else
#define RC_LMS_API
#endif
#endif
#else
#ifndef RC_LMS_API
#define RC_LMS_API
#endif
#endif
#else
#ifndef RC_LMS_API
#ifdef _WIN32
#define RC_LMS_API __declspec(dllexport)
#else
#define RC_LMS_API __attribute__((visibility("default")))
#endif
#endif
#endif
