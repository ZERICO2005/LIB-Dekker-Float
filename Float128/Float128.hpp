/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/
#ifndef FLOAT128_HPP
#define FLOAT128_HPP

#include "../LDF/LDF_float_types.h"

#if defined(__GNUC__) && !defined(__clang__)
	#include "Float128_quadmath_overloads.hpp"
#endif

typedef LDF_Float128 fp128;

#ifndef PRIFloat128
	#define PRIFloat128 "Q"
#endif

#endif /* FLOAT128_HPP */
