/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef LDF_FLOAT_TYPES_H
#define LDF_FLOAT_TYPES_H

/**
 * @brief Provides floating point types
 */

#include "../LDF_config.h"

//------------------------------------------------------------------------------
// Float32
//------------------------------------------------------------------------------

#ifdef LDF_TOGGLE_FLOAT32
	#if LDF_TOGGLE_FLOAT32 != 0
		#define LDF_ENABLE_FLOAT32
	#endif
#else
	#define LDF_ENABLE_FLOAT32
#endif

#ifdef LDF_ENABLE_FLOAT32
	#ifdef LDF_OVERRIDE_FLOAT32
		typedef LDF_Float32 LDF_OVERRIDE_FLOAT32;
	#else
		typedef float LDF_Float32;
	#endif
	#ifndef PRIFloat32
		#define PRIFloat32 ""
	#endif
#endif

//------------------------------------------------------------------------------
// Float64
//------------------------------------------------------------------------------

#ifdef LDF_TOGGLE_FLOAT64
	#if LDF_TOGGLE_FLOAT64 != 0
		#define LDF_ENABLE_FLOAT64
	#endif
#else
	#define LDF_ENABLE_FLOAT64
#endif

#ifdef LDF_ENABLE_FLOAT64
	#ifdef LDF_OVERRIDE_FLOAT64
		typedef LDF_Float64 LDF_OVERRIDE_FLOAT64;
	#else
		typedef double LDF_Float64;
	#endif
	#ifndef PRIFloat64
		#define PRIFloat64 "l"
	#endif
#endif

//------------------------------------------------------------------------------
// Float80
//------------------------------------------------------------------------------

#ifdef LDF_TOGGLE_FLOAT80
	#if LDF_TOGGLE_FLOAT80 != 0
		#define LDF_ENABLE_FLOAT80
	#endif
#else
	#if defined(__GNUC__) || defined(__INTEL_COMPILER)
		// Checks for x87 FPU support https://stackoverflow.com/questions/152016
		#if \
			defined(__x86_64__) || defined(_M_X64) ||\
			defined(__i386__) || defined(__i386) || defined(_M_IX86)
		/* #then */
			#define LDF_ENABLE_FLOAT80
		#endif
	#endif
#endif

#ifdef LDF_ENABLE_FLOAT80
	#ifdef LDF_OVERRIDE_FLOAT80
		typedef LDF_Float80 LDF_OVERRIDE_FLOAT80;
	#else
		#if defined(__GNUC__) && !defined(__clang__)
			typedef __float80 LDF_Float80;
		#else
			typedef long double LDF_Float80;
		#endif
	#endif
	#ifndef PRIFloat80
		#define PRIFloat80 "l"
	#endif
#endif

//------------------------------------------------------------------------------
// Float128
//------------------------------------------------------------------------------

#ifdef LDF_TOGGLE_FLOAT128
	#if LDF_TOGGLE_FLOAT128 != 0
		#define LDF_ENABLE_FLOAT128
	#endif
#else
	#if defined(__GNUC__) && !defined(__clang__)
		#define LDF_ENABLE_FLOAT128
	#endif
#endif

#ifdef LDF_ENABLE_FLOAT128
	#ifdef LDF_OVERRIDE_FLOAT128
		typedef LDF_Float128 LDF_OVERRIDE_FLOAT128;
	#else
		typedef __float128 LDF_Float128;
	#endif
	#ifndef PRIFloat128
		#define PRIFloat128 "l"
	#endif
#endif

//------------------------------------------------------------------------------
// Float16
//------------------------------------------------------------------------------

/* Unimplemented */

//------------------------------------------------------------------------------
// BFloat16
//------------------------------------------------------------------------------

/* Unimplemented */

//------------------------------------------------------------------------------
// Decimal32
//------------------------------------------------------------------------------

/* Unimplemented */

//------------------------------------------------------------------------------
// Decimal64
//------------------------------------------------------------------------------

/* Unimplemented */

//------------------------------------------------------------------------------
// Decimal128
//------------------------------------------------------------------------------

/* Unimplemented */

#endif /* LDF_FLOAT_TYPES_H */
