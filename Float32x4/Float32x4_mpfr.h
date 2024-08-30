/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef FLOAT32X4_MPFR_H
#define FLOAT32X4_MPFR_H

/**
 * @brief defines coversion routines between Float32x4 and MPFR.
 */

#include "Float32x4_def.h"
#include <mpfr.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Sets a mpfr_t to a Float32x4 value.
 * @returns 0 if exact, >0 if rounded up, <0 if rounded down
 */
static inline int mpfr_set_float32x4(mpfr_t rop, const Float32x4 op, const mpfr_rnd_t rnd) {
	// Adds from smallest to largest
	mpfr_set_flt(rop, op.val[3], rnd);
	mpfr_add_d(rop, rop, (double)op.val[2], rnd);
	mpfr_add_d(rop, rop, (double)op.val[1], rnd);
	return mpfr_add_d(rop, rop, (double)op.val[0], rnd);
}

/**
 * @brief Returns a Float32x4 value from a mpfr_t
 */
static inline Float32x4 mpfr_get_float32x4(mpfr_srcptr op, const mpfr_rnd_t rnd) {
	mpfr_t src;
	mpfr_init2(src, mpfr_get_prec(op));
	mpfr_set(src, op, rnd);

	Float32x4 dst;
	dst.val[0] = mpfr_get_flt(src, rnd);
	mpfr_sub_d(src, src, (double)dst.val[0], rnd);
	dst.val[1] = mpfr_get_flt(src, rnd);
	mpfr_sub_d(src, src, (double)dst.val[1], rnd);
	dst.val[2] = mpfr_get_flt(src, rnd);
	mpfr_sub_d(src, src, (double)dst.val[2], rnd);
	dst.val[3] = mpfr_get_flt(src, rnd);

	mpfr_clear(src);
	return dst;
}

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include "util_mpfr/mpfr_convert.hpp"

template <>
inline int mpfr_set_type<Float32x4>(mpfr_t rop, const Float32x4& op, const mpfr_rnd_t rnd) {
	return mpfr_set_float32x4(rop, op, rnd);
}
template <>
inline Float32x4 mpfr_get_type<Float32x4>(mpfr_srcptr op, const mpfr_rnd_t rnd) {
	return mpfr_get_float32x4(op, rnd);
}

#endif

#endif /* FLOAT32X4_MPFR_H */
