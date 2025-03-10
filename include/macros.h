/*

macros.h

Header file containing global preprocessor constants and macros.

Part of the "Lightning-Fast Password Check" project by OperaVaria.

*/

// Guard.
#ifndef MACROS_H
#define MACROS_H

// Header files.
#include <openssl/sha.h>

// Constants:

// Integers.
#define DIGEST_STRING_LENGTH SHA_DIGEST_LENGTH * 2 + 1
#define PREFIX_LENGTH 6
#define SUFFIX_LENGTH DIGEST_STRING_LENGTH - 5
#define PASSWORD_MAX_LENGTH 64
#define PASSWORD_MIN_LENGTH 8
#define STRONG_PASSWORD_LENGTH 16

// Platform dependent strings.
#ifdef _WIN32
/*  NB. MYSYS2 UCRT64 path:
    #define CSS_FILE_PATH "c:/msys64/ucrt64/share/lfpch/styles.css" */
    #define CSS_FILE_PATH "c:/Tools/lfpch/resources/styles.css"
    /* The "'" format specifier (thousand separated number) does not work on Windows,
    therefore it is not implemented in the pwn result message. */
    #define PWN_RESULT_MESSAGE "Warning! This password has been breached at least %ld times!"
#else
    #define CSS_FILE_PATH "/usr/share/lfpch/styles.css"
    #define PWN_RESULT_MESSAGE "Warning! This password has been breached at least %'ld times!"
#endif

#endif
