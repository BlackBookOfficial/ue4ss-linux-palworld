#pragma once

#ifndef RC_SINGLE_PASS_SIG_SCANNER_EXPORTS
#ifndef RC_SINGLE_PASS_SIG_SCANNER_BUILD_STATIC
#ifndef RC_SPSS_API
#ifdef _WIN32
#define RC_SPSS_API __declspec(dllimport)
#else
#define RC_SPSS_API
#endif
#endif
#else
#ifndef RC_SPSS_API
#define RC_SPSS_API
#endif
#endif
#else
#ifndef RC_SPSS_API
#ifdef _WIN32
#define RC_SPSS_API __declspec(dllexport)
#else
#define RC_SPSS_API __attribute__((visibility("default")))
#endif
#endif
#endif
