/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef FLOAT80X2_MPFR_H
#define FLOAT80X2_MPFR_H

/**
 * @brief defines coversion routines between Float80x2 and MPFR.
 */

#include "Float80x2_def.h"
#include <mpfr.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Sets a mpfr_t to a Float80x2 value.
 * @returns 0 if exact, >0 if rounded up, <0 if rounded down
 */
inline int mpfr_set_float80x2(mpfr_t rop, const Float80x2 op, const mpfr_rnd_t rnd) {
	mpfr_t temp;
	mpfr_init2(temp, mpfr_get_prec(rop));
	
	mpfr_set_ld(temp, op.lo, rnd);
	mpfr_set_ld(rop , op.hi, rnd);
	int ret_val = mpfr_add(rop, rop, temp, rnd);
	
	mpfr_clear(temp);
	return ret_val;
}

/**
 * @brief Returns a Float80x2 value from a mpfr_t
 */
inline Float80x2 mpfr_get_float80x2(mpfr_srcptr op, const mpfr_rnd_t rnd) {
	mpfr_t src;
	mpfr_init2(src, mpfr_get_prec(op));
	mpfr_set(src, op, rnd);

	Float80x2 dst;
	dst.hi = mpfr_get_ld(src, rnd);
	mpfr_set_ld(src, dst.hi, rnd);

	mpfr_sub(src, op, src, rnd);
	dst.lo = mpfr_get_ld(src, rnd);
	
	mpfr_clear(src);
	return dst;
}

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include "util_mpfr/mpfr_convert.hpp"

template <>
inline int mpfr_set_type<Float80x2>(mpfr_t rop, const Float80x2& op, const mpfr_rnd_t rnd) {
	return mpfr_set_float80x2(rop, op, rnd);
}
template <>
inline Float80x2 mpfr_get_type<Float80x2>(mpfr_srcptr op, const mpfr_rnd_t rnd) {
	return mpfr_get_float80x2(op, rnd);
}

#endif

#endif /* FLOAT80X2_MPFR_H */
