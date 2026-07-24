#pragma once

#ifndef RC_PARSER_BASE_EXPORTS
#ifndef RC_PARSER_BASE_BUILD_STATIC
#ifndef RC_PB_API
#ifdef _WIN32
#define RC_PB_API __declspec(dllimport)
#else
#define RC_PB_API
#endif
#endif
#else
#ifndef RC_PB_API
#define RC_PB_API
#endif
#endif
#else
#ifndef RC_PB_API
#ifdef _WIN32
#define RC_PB_API __declspec(dllexport)
#else
#define RC_PB_API __attribute__((visibility("default")))
#endif
#endif
#endif
