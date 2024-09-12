/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef FLOAT64X6_MPFR_H
#define FLOAT64X6_MPFR_H

/**
 * @brief defines coversion routines between Float64x6 and MPFR.
 */

#include "Float64x6_def.h"
#include <mpfr.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Sets a mpfr_t to a Float64x6 value.
 * @returns 0 if exact, >0 if rounded up, <0 if rounded down
 */
static inline int mpfr_set_float64x6(mpfr_t rop, const Float64x6 op, const mpfr_rnd_t rnd) {
	// Adds from smallest to largest
	mpfr_set_d(rop, op.val[5], rnd);
	mpfr_add_d(rop, rop, op.val[4], rnd);
	mpfr_add_d(rop, rop, op.val[3], rnd);
	mpfr_add_d(rop, rop, op.val[2], rnd);
	mpfr_add_d(rop, rop, op.val[1], rnd);
	return mpfr_add_d(rop, rop, op.val[0], rnd);
}

/**
 * @brief Returns a Float64x6 value from a mpfr_t
 */
static inline Float64x6 mpfr_get_float64x6(mpfr_srcptr op, const mpfr_rnd_t rnd) {
	mpfr_t src;
	mpfr_init2(src, mpfr_get_prec(op));
	mpfr_set(src, op, rnd);

	Float64x6 dst;
	for (int i = 0; i < 6; i++) {
		dst.val[i] = mpfr_get_d(src, rnd);
		mpfr_sub_d(src, src, dst.val[i], rnd);
	}

	mpfr_clear(src);
	return dst;
}

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include "util_mpfr/mpfr_convert.hpp"

template <>
inline int mpfr_set_type<Float64x6>(mpfr_t rop, const Float64x6& op, const mpfr_rnd_t rnd) {
	return mpfr_set_float64x6(rop, op, rnd);
}
template <>
inline Float64x6 mpfr_get_type<Float64x6>(mpfr_srcptr op, const mpfr_rnd_t rnd) {
	return mpfr_get_float64x6(op, rnd);
}

#endif

#endif /* FLOAT64X6_MPFR_H */
