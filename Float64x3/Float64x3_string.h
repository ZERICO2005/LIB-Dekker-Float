/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/
#ifndef FLOAT64X3_STRING_H
#define FLOAT64X3_STRING_H

#include "Float64x3_def.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
	Float64x3 stringTo_Float64x3(const char* nPtr, char** endPtr = nullptr);
#else
	Float64x3 stringTo_Float64x3(const char* nPtr, char** endPtr);
#endif

#ifndef PRIFloat64x3
	#define PRIFloat64x3 "TD"
#endif

/**
 * @brief snprintf a singular Float64x3/fp64x3.
 * Similar in functionallity to quadmath_snprintf.
 * @note $ not supported. This function ignores additional format specifiers.
 * @return -1 on encoding failure. Otherwise the total length of the
 * string excluding the \0 terminator and ignoring the buffer size.
 */
int Float64x3_snprintf(char* buf, size_t len, const char* format, ...);



#ifdef __cplusplus
	}
#endif

#endif /* FLOAT64X3_STRING_H */
