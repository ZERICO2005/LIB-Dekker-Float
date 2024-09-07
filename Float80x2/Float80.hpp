/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/
#ifndef FLOAT80_HPP
#define FLOAT80_HPP

#include <climits>
#include <cfloat>
#include <cstdlib>
#include <math.h>
#include <cmath>

#if defined(__GNUC__) && !defined(__clang__)
	typedef __float80 fp80;
	#define PRIFloat80 "L"
	#define PRIfp80 PRIFloat80
#else
	typedef long double fp80;
	#define PRIFloat80 "L"
	#define PRIfp80 PRIFloat80

	static_assert(
		LDBL_MANT_DIG > DBL_MANT_DIG && LDBL_EPSILON < DBL_EPSILON ,
		"Enable_Float80 failed. long double is equivilent to double."
	);
#endif

static_assert(
	sizeof(fp80) * CHAR_BIT >= 80,
	"Enable_Float80 failed. Float80 is less than 80 bits wide."
);

#endif /* FLOAT80_HPP */
