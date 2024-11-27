/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef FLOAT64_UTIL_H
#define FLOAT64_UTIL_H

#include "Float64.h"

//------------------------------------------------------------------------------
// qd_real.cpp functions
//------------------------------------------------------------------------------
/** 
 * @author Taken and/or modified from libQD which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */

/** @brief Computes fl(x + y) and err(x + y). Assumes |x| >= |y|. */
static inline fp64 Float64_quick_two_sum(const fp64 x, const fp64 y, fp64* LDF_restrict const err) {
	fp64 s = x + y;
	*err = y - (s - x);
	return s;
}

/** @brief Computes fl(x - y) and err(x - y). Assumes |x| >= |y|. */
static inline fp64 Float64_quick_two_diff(const fp64 x, const fp64 y, fp64* LDF_restrict const err) {
	fp64 s = x - y;
	*err = (x - s) - y;
	return s;
}

/** @brief Computes fl(x + y) and err(x + y). */
static inline fp64 Float64_two_sum(const fp64 x, const fp64 y, fp64* LDF_restrict const err) {
	fp64 s = x + y;
	fp64 bb = s - x;
	*err = (x - (s - bb)) + (y - bb);
	return s;
}

/** @brief Computes fl(x - y) and err(x - y). */
static inline fp64 Float64_two_diff(const fp64 x, const fp64 y, fp64* LDF_restrict const err) {
	fp64 s = x - y;
	fp64 bb = s - x;
	*err = (x - (s - bb)) - (y + bb);
	return s;
}

static inline void Float64_split(
	fp64 x,
	fp64* LDF_restrict const hi,
	fp64* LDF_restrict const lo
) {
	const fp64 FLOAT64_SPLITTER = 134217729.0; // = 2^27 + 1
	const fp64 FLOAT64_SPLIT_THRESH = 0x1.0p+996; // = 2^996
	fp64 temp;
	if (x > FLOAT64_SPLIT_THRESH || x < -FLOAT64_SPLIT_THRESH) {
		x *= 0x1.0p-28; // 2^-28
		temp = FLOAT64_SPLITTER * x;
		*hi = temp - (temp - x);
		*lo = x - *hi;
		*hi *= 0x1.0p+28; // 2^28
		*lo *= 0x1.0p+28; // 2^28
	} else {
		temp = FLOAT64_SPLITTER * x;
		*hi = temp - (temp - x);
		*lo = x - *hi;
	}
}

/** @brief Computes fl(x * y) and err(x * y). */
static inline fp64 Float64_two_prod(const fp64 a, const fp64 b, fp64* LDF_restrict const err) {
	fp64 a_hi, a_lo, b_hi, b_lo;
	fp64 p = a * b;
	Float64_split(a, &a_hi, &a_lo);
	Float64_split(b, &b_hi, &b_lo);
	*err = (
		(a_hi * b_hi - p) + 
		a_hi * b_lo + a_lo * b_hi
	) + a_lo * b_lo;
	return p;
}

/** @brief Computes fl(x * x) and err(x * x). Faster than Float64_two_prod(x, x, err) */
static inline fp64 Float64_two_sqr(const fp64 a, fp64* LDF_restrict const err) {
	fp64 hi, lo;
	fp64 q = a * a;
	Float64_split(a, &hi, &lo);
	*err = (
		(hi * hi - q) +
		2.0 * hi * lo
	) + lo * lo;
	return q;
}

/** 
 * @brief Adds `c` to the dd-pair `(a, b)`. If the result does not fit in two
 * doubles, then the sum is output into `s` and `(a, b)` contains the
 * remainder. Otherwise `s` is zero and `(a, b)` contains the sum.
 */
static inline fp64 Float64_quick_three_accum(
	fp64* LDF_restrict const a,
	fp64* LDF_restrict const b,
	const fp64 c
) {
	fp64 s;
	bool za, zb;

	s = Float64_two_sum(*b, c, b);
	s = Float64_two_sum(*a, s, a);

	za = (*a != 0.0);
	zb = (*b != 0.0);

	if (za && zb) {
		return s;
	}
		
	if (!zb) {
		*b = *a;
		*a = s;
	} else {
		*a = s;
	}

	return 0.0;
}

static inline void Float64_three_sum(
	fp64* LDF_restrict const a,
	fp64* LDF_restrict const b,
	fp64* LDF_restrict const c
) {
	fp64 t1, t2, t3;
	t1 = Float64_two_sum(*a, *b, &t2);
	*a = Float64_two_sum(*c, t1, &t3);
	*b = Float64_two_sum(t2, t3, c  );
}

static inline void Float64_three_sum2(
	fp64* LDF_restrict const a,
	fp64* LDF_restrict const b,
	const fp64 c
) {
	fp64 t1, t2, t3;
	t1 = Float64_two_sum(*a, *b, &t2);
	*a = Float64_two_sum( c, t1, &t3);
	*b = t2 + t3;
}

#endif /* FLOAT64_UTIL_H */
