/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef FLOAT64X2_MPFR_H
#define FLOAT64X2_MPFR_H

/**
 * @brief defines coversion routines between Float64x2 and MPFR.
 */

#include "Float64x2_def.h"
#include <mpfr.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Sets a mpfr_t to a Float64x2 value.
 * @returns 0 if exact, >0 if rounded up, <0 if rounded down
 */
static inline int mpfr_set_float64x2(mpfr_t rop, const Float64x2 op, const mpfr_rnd_t rnd) {
	// Adds smallest to largest
	mpfr_set_d(rop, op.lo, rnd);
	return mpfr_add_d(rop, rop, op.hi, rnd);
}

/**
 * @brief Returns a Float64x2 value from a mpfr_t
 */
static inline Float64x2 mpfr_get_float64x2(mpfr_srcptr op, const mpfr_rnd_t rnd) {
	mpfr_t src;
	mpfr_init2(src, mpfr_get_prec(op));
	mpfr_set(src, op, rnd);

	Float64x2 dst;
	dst.hi = mpfr_get_d(src, rnd);
	mpfr_sub_d(src, src, dst.hi, rnd);
	dst.lo = mpfr_get_d(src, rnd);
	
	mpfr_clear(src);
	return dst;
}

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include "util_mpfr/mpfr_convert.hpp"

template <>
inline int mpfr_set_type<Float64x2>(mpfr_t rop, const Float64x2& op, const mpfr_rnd_t rnd) {
	return mpfr_set_float64x2(rop, op, rnd);
}
template <>
inline Float64x2 mpfr_get_type<Float64x2>(mpfr_srcptr op, const mpfr_rnd_t rnd) {
	return mpfr_get_float64x2(op, rnd);
}

#endif

#endif /* FLOAT64X2_MPFR_H */
