#pragma once

#ifndef RC_INPUT_EXPORTS
#ifndef RC_INPUT_BUILD_STATIC
#ifndef RC_INPUT_API
#ifdef _WIN32
#define RC_INPUT_API __declspec(dllimport)
#else
#define RC_INPUT_API
#endif
#endif
#else
#ifndef RC_INPUT_API
#define RC_INPUT_API
#endif
#endif
#else
#ifndef RC_INPUT_API
#ifdef _WIN32
#define RC_INPUT_API __declspec(dllexport)
#else
#define RC_INPUT_API __attribute__((visibility("default")))
#endif
#endif
#endif
