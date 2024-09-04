/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/
#ifndef FLOAT64X4_STRING_H
#define FLOAT64X4_STRING_H

#include "Float64x4_def.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
	Float64x4 stringTo_Float64x4(const char* nPtr, char** endPtr = nullptr);
#else
	Float64x4 stringTo_Float64x4(const char* nPtr, char** endPtr);
#endif

#ifndef PRIFloat64x4
	#define PRIFloat64x4 "QD"
#endif

/**
 * @brief snprintf a singular Float64x4/fp64x4.
 * Similar in functionallity to quadmath_snprintf.
 * @note $ not supported. This function ignores additional format specifiers.
 * @return -1 on encoding failure. Otherwise the total length of the
 * string excluding the \0 terminator and ignoring the buffer size.
 */
int Float64x4_snprintf(char* buf, size_t len, const char* format, ...);



#ifdef __cplusplus
	}
#endif

#endif /* FLOAT64X4_STRING_H */
