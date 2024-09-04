/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/
#ifndef FLOAT80X2_STRING_H
#define FLOAT80X2_STRING_H

#include "Float80x2_def.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
	Float80x2 stringTo_Float80x2(const char* nPtr, char** endPtr = nullptr);
#else
	Float80x2 stringTo_Float80x2(const char* nPtr, char** endPtr);
#endif

#ifndef PRIFloat80x2
	#define PRIFloat80x2 "DX"
#endif

/**
 * @brief snprintf a singular Float80x2/fp80x2.
 * Similar in functionallity to quadmath_snprintf.
 * @note $ not supported. This function ignores additional format specifiers.
 * @return -1 on encoding failure. Otherwise the total length of the
 * string excluding the \0 terminator and ignoring the buffer size.
 */
int Float80x2_snprintf(char* buf, size_t len, const char* format, ...);



#ifdef __cplusplus
}
#endif

#endif /* FLOAT80X2_STRING_H */
