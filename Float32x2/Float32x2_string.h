/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/
#ifndef FLOAT32X2_STRING_H
#define FLOAT32X2_STRING_H

#include "Float32x2_def.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
	Float32x2 stringTo_Float32x2(const char* nPtr, char** endPtr = nullptr);
#else
	Float32x2 stringTo_Float32x2(const char* nPtr, char** endPtr);
#endif

#ifndef PRIFloat32x2
	#define PRIFloat32x2 "DS"
#endif

/**
 * @brief snprintf a singular Float32x2/fp32x2.
 * Similar in functionallity to quadmath_snprintf.
 * @note $ not supported. This function ignores additional format specifiers.
 * @return -1 on encoding failure. Otherwise the total length of the
 * string excluding the \0 terminator and ignoring the buffer size.
 */
int Float32x2_snprintf(char* buf, size_t len, const char* format, ...);



#ifdef __cplusplus
	}
#endif

#endif /* FLOAT32X2_STRING_H */
