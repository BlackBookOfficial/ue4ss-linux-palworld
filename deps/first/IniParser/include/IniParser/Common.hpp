#pragma once

#ifndef RC_INI_PARSER_EXPORTS
#ifndef RC_INI_PARSER_BUILD_STATIC
#ifndef RC_INI_PARSER_API
#ifdef _WIN32
#define RC_INI_PARSER_API __declspec(dllimport)
#else
#define RC_INI_PARSER_API
#endif
#endif
#else
#ifndef RC_INI_PARSER_API
#define RC_INI_PARSER_API
#endif
#endif
#else
#ifndef RC_INI_PARSER_API
#ifdef _WIN32
#define RC_INI_PARSER_API __declspec(dllexport)
#else
#define RC_INI_PARSER_API __attribute__((visibility("default")))
#endif
#endif
#endif
