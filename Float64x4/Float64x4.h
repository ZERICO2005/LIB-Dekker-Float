/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

/*
**	Portions of this file were part of the libQD library, licensed
**	under a modifed BSD license that can be found below:
**	https://www.davidhbailey.com/dhbsoftware/LBNL-BSD-License.docx
**	Or alternatively from this website:
**	https://www.davidhbailey.com/dhbsoftware/
**	A copy of the LBNL-BSD-License can also be found at:
**	LIB-Dekker-Float/libQD/LBNL-BSD-License.txt
*/

#ifndef FLOAT64X4_H
#define FLOAT64X4_H

/**
 * @brief Double-Float64 Dekker Float implementation for C.
 * Source: Creel "Double it Like Dekker" on YouTube.
 *
 * @warning -Ofast may break this library. -O3 compiles okay on gcc and clang.
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <fenv.h>

#include "../LDF/LDF_restrict.h"

//------------------------------------------------------------------------------
// Float64x4 struct
//------------------------------------------------------------------------------

#include "Float64x4_def.h"
#include "../Float64x2/Float64x2.h"

/**
 * @brief Allows for type punning
 */
typedef union Bitwise_Float64x4 {
	Float64x4 float_part;
	struct {
		uint64_t val[4];
	} binary_part;
	#ifdef __cplusplus
		Bitwise_Float64x4() : float_part() {}
	#endif
} Bitwise_Float64x4;

//------------------------------------------------------------------------------
// Float64x4 string operations
//------------------------------------------------------------------------------

#include "Float64x4_string.h"

//------------------------------------------------------------------------------
// Float64x4 constants
//------------------------------------------------------------------------------

/* C++20 <numbers> */
#define FLOAT64X4_E          {{0x1.5bf0a8b145769p+1,+0x1.4d57ee2b1013ap-53,-0x1.618713a31d3e2p-109,+0x1.c5a6d2b53c26dp-163}} /**< ~2.718281828 */
#define FLOAT64X4_LOG2E      {{0x1.71547652b82fep+0,+0x1.777d0ffda0d24p-56,-0x1.60bb8a5442ab9p-110,-0x1.4b52d3ba6d74dp-166}} /**< ~1.442695041 */
#define FLOAT64X4_LOG10E     {{0x1.bcb7b1526e50ep-2,+0x1.95355baaafad3p-57,+0x1.ee191f71a3012p-112,+0x1.7268808e8fcb5p-167}} /**< ~0.434294482 */
#define FLOAT64X4_PI         {{0x1.921fb54442d18p+1,+0x1.1a62633145c07p-53,-0x1.f1976b7ed8fbcp-109,+0x1.4cf98e804177dp-163}} /**< ~3.141592654 */
#define FLOAT64X4_INV_PI     {{0x1.45f306dc9c883p-2,-0x1.6b01ec5417056p-56,-0x1.6447e493ad4cep-110,+0x1.e21c820ff28b2p-164}} /**< ~0.318309886 */
#define FLOAT64X4_INV_SQRTPI {{0x1.20dd750429b6dp-1,+0x1.1ae3a914fed80p-57,-0x1.3cbbebf65f145p-112,-0x1.e0c574632f53ep-167}} /**< ~0.564189584 */
#define FLOAT64X4_LN2        {{0x1.62e42fefa39efp-1,+0x1.abc9e3b39803fp-56,+0x1.7b57a079a1934p-111,-0x1.ace93a4ebe5d1p-165}} /**< ~0.693147181 */
#define FLOAT64X4_LN10       {{0x1.26bb1bbb55516p+1,-0x1.f48ad494ea3e9p-53,-0x1.9ebae3ae0260cp-107,-0x1.2d10378be1cf1p-161}} /**< ~2.302585093 */
#define FLOAT64X4_SQRT2      {{0x1.6a09e667f3bcdp+0,-0x1.bdd3413b26456p-54,+0x1.57d3e3adec175p-108,+0x1.2775099da2f59p-164}} /**< ~1.414213562 */
#define FLOAT64X4_SQRT3      {{0x1.bb67ae8584caap+0,+0x1.cec95d0b5c1e3p-54,-0x1.f11db689f2ccfp-110,+0x1.3da4798c720a6p-164}} /**< ~1.732050808 */
#define FLOAT64X4_INV_SQRT3  {{0x1.279a74590331cp-1,+0x1.34863e0792bedp-55,-0x1.a82f9e6c53222p-109,-0x1.cb0f41134253ap-163}} /**< ~0.577350269 */
#define FLOAT64X4_EGAMMA     {{0x1.2788cfc6fb619p-1,-0x1.6cb90701fbfabp-58,-0x1.34a95e3133c51p-112,+0x1.9730064300f7dp-166}} /**< ~0.577215665 */
#define FLOAT64X4_PHI        {{0x1.9e3779b97f4a8p+0,-0x1.f506319fcfd19p-55,+0x1.b906821044ed8p-109,-0x1.8bb1b5c0f272cp-165}} /**< ~1.618033989 */

/* <math.h> constants */
#define FLOAT64X4_1_PI       FLOAT64X4_INV_PI /**< ~0.318309886 */
#define FLOAT64X4_PI_2       {{0x1.921fb54442d18p+0,+0x1.1a62633145c07p-54,-0x1.f1976b7ed8fbcp-110,+0x1.4cf98e804177dp-164}} /**< ~1.570796327 */
#define FLOAT64X4_PI_4       {{0x1.921fb54442d18p-1,+0x1.1a62633145c07p-55,-0x1.f1976b7ed8fbcp-111,+0x1.4cf98e804177dp-165}} /**< ~0.785398163 */
#define FLOAT64X4_2_PI       {{0x1.45f306dc9c883p-1,-0x1.6b01ec5417056p-55,-0x1.6447e493ad4cep-109,+0x1.e21c820ff28b2p-163}} /**< ~0.636619772 */
#define FLOAT64X4_2_SQRTPI   {{0x1.20dd750429b6dp+0,+0x1.1ae3a914fed80p-56,-0x1.3cbbebf65f145p-111,-0x1.e0c574632f53ep-166}} /**< ~1.128379167 */
#define FLOAT64X4_SQRT1_2    {{0x1.6a09e667f3bcdp-1,-0x1.bdd3413b26456p-55,+0x1.57d3e3adec175p-109,+0x1.2775099da2f59p-165}} /**< ~0.707106781 */

//------------------------------------------------------------------------------
// Float64x4 <float.h>
//------------------------------------------------------------------------------

#define FLOAT64X4_RADIX       FLT_RADIX
#define FLOAT64X4_MANT_DIG    209
#define FLOAT64X4_DECIMAL_DIG (DBL_MAX_10_EXP - DBL_MIN_10_EXP + DBL_DIG + 1) /**< ~631 with ieee doubles */
#define FLOAT64X4_DIG         62
#define FLOAT64X4_MIN_EXP     (DBL_MIN_EXP    + 159)
#define FLOAT64X4_MIN_10_EXP  (DBL_MIN_10_EXP + 48)
#define FLOAT64X4_MAX_EXP     (DBL_MAX_EXP   )
#define FLOAT64X4_MAX_10_EXP  (DBL_MAX_10_EXP)
#define FLOAT64X4_MAX         {DBL_MAX, DBL_MAX * 0x1.0p-54, DBL_MAX * 0x1.0p-108, DBL_MAX * 0x1.0p-162}
#define FLOAT64X4_EPSILON     {0x1.0p-104, 0.0}
#define FLOAT64X4_MIN         {DBL_MIN * 0x1.0p+159, DBL_MIN * 0x1.0p+106, DBL_MIN * 0x1.0p+53, DBL_MIN}
#ifdef DBL_TRUE_MIN
	#define FLOAT64X4_TRUE_MIN    {DBL_TRUE_MIN, 0.0, 0.0, 0.0}
	#define FLOAT64X4_DENORM_MIN  FLOAT64X4_TRUE_MIN
#endif
#ifdef DBL_HAS_SUBNORM
	#define FLOAT64X4_HAS_SUBNORM DBL_HAS_SUBNORM
#endif

#ifdef __cplusplus
	extern "C" {
#endif

//------------------------------------------------------------------------------
// Float64x4 set functions
//------------------------------------------------------------------------------

static inline Float64x4 Float64x4_set_zero(void) {
	Float64x4 ret = {{0.0, 0.0, 0.0, 0.0}};
	return ret;
}

static inline Float64x4 Float64x4_set_d(const fp64 x) {
	Float64x4 ret = {{x, 0.0, 0.0, 0.0}};
	return ret;
}

static inline Float64x4 Float64x4_set_dx4(const fp64 values[4]) {
	Float64x4 ret = {{values[0], values[1], values[2], values[3]}};
	return ret;
}

static inline Float64x4 Float64x4_set_u64(const uint64_t values[4]) {
	Bitwise_Float64x4 ret;
	ret.binary_part.val[0] = values[0];
	ret.binary_part.val[1] = values[1];
	ret.binary_part.val[2] = values[2];
	ret.binary_part.val[3] = values[3];
	return ret.float_part;
}

static inline Float64x4 Float64x4_set_i64(const int64_t values[4]) {
	Bitwise_Float64x4 ret;
	ret.binary_part.val[0] = (uint64_t)values[0];
	ret.binary_part.val[1] = (uint64_t)values[1];
	ret.binary_part.val[2] = (uint64_t)values[2];
	ret.binary_part.val[3] = (uint64_t)values[3];
	return ret.float_part;
}

//------------------------------------------------------------------------------
// Float64x4 get functions
//------------------------------------------------------------------------------

static inline fp64 Float64x4_get_d(const Float64x4 x) {
	return x.val[0];
}

static inline void Float64x4_get_dx4(const Float64x4 src, fp64 dst[4]) {
	dst[0] = src.val[0];
	dst[1] = src.val[1];
	dst[2] = src.val[2];
	dst[3] = src.val[3];
}

static inline void Float64x4_get_u64(const Float64x4 src, uint64_t dst[4]) {
	Bitwise_Float64x4 bitwise_src;
	bitwise_src.float_part = src;
	dst[0] = bitwise_src.binary_part.val[0];
	dst[1] = bitwise_src.binary_part.val[1];
	dst[2] = bitwise_src.binary_part.val[2];
	dst[3] = bitwise_src.binary_part.val[3];
}

static inline void Float64x4_get_i64(const Float64x4 src, int64_t dst[4]) {
	Bitwise_Float64x4 bitwise_src;
	bitwise_src.float_part = src;
	dst[0] = (int64_t)bitwise_src.binary_part.val[0];
	dst[1] = (int64_t)bitwise_src.binary_part.val[1];
	dst[2] = (int64_t)bitwise_src.binary_part.val[2];
	dst[3] = (int64_t)bitwise_src.binary_part.val[3];
}

//------------------------------------------------------------------------------
// Float64x4 comparison functions
//------------------------------------------------------------------------------

static inline bool Float64x4_cmpeq(const Float64x4 x, const Float64x4 y) {
	return (
		x.val[0] == y.val[0] && x.val[1] == y.val[1] &&
		x.val[2] == y.val[2] && x.val[3] == y.val[3]
	);
}

static inline bool Float64x4_cmpneq(const Float64x4 x, const Float64x4 y) {
	return (
		x.val[0] != y.val[0] || x.val[1] != y.val[1] ||
		x.val[2] != y.val[2] || x.val[3] != y.val[3]
	);
}

static inline bool Float64x4_cmpord(const Float64x4 x, const Float64x4 y) {
	return (
		!isunordered(x.val[0], y.val[0]) && !isunordered(x.val[1], y.val[1]) &&
		!isunordered(x.val[2], y.val[2]) && !isunordered(x.val[3], y.val[3])
	);
}

static inline bool Float64x4_cmpunord(const Float64x4 x, const Float64x4 y) {
	return (
		isunordered(x.val[0], y.val[0]) || isunordered(x.val[1], y.val[1]) ||
		isunordered(x.val[2], y.val[2]) || isunordered(x.val[3], y.val[3])
	);
}

static inline bool Float64x4_cmplt(const Float64x4 x, const Float64x4 y) {
	return
		(x.val[0] == y.val[0]) ? (
			(x.val[1] == y.val[1]) ? (
				(x.val[2] == y.val[2]) ? (
					x.val[3] < y.val[3]
				) : (x.val[2] < y.val[2])
			) : (x.val[1] < y.val[1])
		) : (x.val[0] < y.val[0]);
}

static inline bool Float64x4_cmple(const Float64x4 x, const Float64x4 y) {
	return
		(x.val[0] == y.val[0]) ? (
			(x.val[1] == y.val[1]) ? (
				(x.val[2] == y.val[2]) ? (
					x.val[3] <= y.val[3]
				) : (x.val[2] < y.val[2])
			) : (x.val[1] < y.val[1])
		) : (x.val[0] < y.val[0]);
}

static inline bool Float64x4_cmpgt(const Float64x4 x, const Float64x4 y) {
	return
		(x.val[0] == y.val[0]) ? (
			(x.val[1] == y.val[1]) ? (
				(x.val[2] == y.val[2]) ? (
					x.val[3] > y.val[3]
				) : (x.val[2] > y.val[2])
			) : (x.val[1] > y.val[1])
		) : (x.val[0] > y.val[0]);
}

static inline bool Float64x4_cmpge(const Float64x4 x, const Float64x4 y) {
	return
		(x.val[0] == y.val[0]) ? (
			(x.val[1] == y.val[1]) ? (
				(x.val[2] == y.val[2]) ? (
					x.val[3] >= y.val[3]
				) : (x.val[2] > y.val[2])
			) : (x.val[1] > y.val[1])
		) : (x.val[0] > y.val[0]);
}

//------------------------------------------------------------------------------
// Float64x4 compare to zero functions
//------------------------------------------------------------------------------

/** @brief Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero */
static inline bool Float64x4_cmpeq_zero(const Float64x4 x) {
	return (x.val[0] == 0.0);
}
/** @brief Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero */
static inline bool Float64x4_cmpneq_zero(const Float64x4 x) {
	return (x.val[0] != 0.0);
}
/** @brief Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero */
static inline bool Float64x4_cmplt_zero(const Float64x4 x) {
	return (x.val[0] < 0.0);
}
/** @brief Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero */
static inline bool Float64x4_cmple_zero(const Float64x4 x) {
	return (x.val[0] <= 0.0);
}
/** @brief Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero */
static inline bool Float64x4_cmpgt_zero(const Float64x4 x) {
	return (x.val[0] > 0.0);
}
/** @brief Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero */
static inline bool Float64x4_cmpge_zero(const Float64x4 x) {
	return (x.val[0] >= 0.0);
}

//------------------------------------------------------------------------------
// Float64x4 optimized comparison functions
//------------------------------------------------------------------------------

static inline bool Float64x4_cmpeq_dx4_d(const Float64x4 x, const fp64 y) {
	return (x.val[0] == y && x.val[1] == 0.0);
}

static inline bool Float64x4_cmpneq_dx4_d(const Float64x4 x, const fp64 y) {
	return (x.val[0] != y || x.val[1] != 0.0);
}

static inline bool Float64x4_cmpord_dx4_d(const Float64x4 x, const fp64 y) {
	return (!isunordered(x.val[0], y) && !isunordered(x.val[1], 0.0));
}

static inline bool Float64x4_cmpunord_dx4_d(const Float64x4 x, const fp64 y) {
	return (isunordered(x.val[0], y) || isunordered(x.val[1], 0.0));
}

static inline bool Float64x4_cmplt_dx4_d(const Float64x4 x, const fp64 y) {
	return (x.val[0] < y || (x.val[0] == y && x.val[1] < 0.0));
}

static inline bool Float64x4_cmple_dx4_d(const Float64x4 x, const fp64 y) {
	return (x.val[0] < y || (x.val[0] == y && x.val[1] <= 0.0));
}

static inline bool Float64x4_cmpgt_dx4_d(const Float64x4 x, const fp64 y) {
	return (x.val[0] > y || (x.val[0] == y && x.val[1] > 0.0));
}

static inline bool Float64x4_cmpge_dx4_d(const Float64x4 x, const fp64 y) {
	return (x.val[0] > y || (x.val[0] == y && x.val[1] >= 0.0));
}

static inline bool Float64x4_cmpeq_d_dx4(const fp64 x, const Float64x4 y) {
	return (x == y.val[0] && 0.0 == y.val[1]);
}

static inline bool Float64x4_cmpneq_d_dx4(const fp64 x, const Float64x4 y) {
	return (x != y.val[0] || 0.0 != y.val[1]);
}

static inline bool Float64x4_cmpord_d_dx4(const fp64 x, const Float64x4 y) {
	return (!isunordered(x, y.val[0]) && !isunordered(0.0, y.val[1]));
}

static inline bool Float64x4_cmpunord_d_dx4(const fp64 x, const Float64x4 y) {
	return (isunordered(x, y.val[0]) || isunordered(0.0, y.val[1]));
}

static inline bool Float64x4_cmplt_d_dx4(const fp64 x, const Float64x4 y) {
	return (x < y.val[0] || (x == y.val[0] && 0.0 < y.val[1]));
}

static inline bool Float64x4_cmple_d_dx4(const fp64 x, const Float64x4 y) {
	return (x < y.val[0] || (x == y.val[0] && 0.0 <= y.val[1]));
}

static inline bool Float64x4_cmpgt_d_dx4(const fp64 x, const Float64x4 y) {
	return (x > y.val[0] || (x == y.val[0] && 0.0 > y.val[1]));
}

static inline bool Float64x4_cmpge_d_dx4(const fp64 x, const Float64x4 y) {
	return (x > y.val[0] || (x == y.val[0] && 0.0 >= y.val[1]));
}

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
static inline fp64 Float64x4_quick_three_accum(
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

static inline void Float64x4_three_sum(
	fp64* LDF_restrict const a,
	fp64* LDF_restrict const b,
	fp64* LDF_restrict const c
) {
	fp64 t1, t2, t3;
	t1 = Float64_two_sum(*a, *b, &t2);
	*a = Float64_two_sum(*c, t1, &t3);
	*b = Float64_two_sum(t2, t3, c  );
}

static inline void Float64x4_three_sum2(
	fp64* LDF_restrict const a,
	fp64* LDF_restrict const b,
	const fp64 c
) {
	fp64 t1, t2, t3;
	t1 = Float64_two_sum(*a, *b, &t2);
	*a = Float64_two_sum( c, t1, &t3);
	*b = t2 + t3;
}

static inline void Float64x4_accurate_renorm(Float64x4* LDF_restrict const x) {
	fp64 s0, s1, s2 = 0.0, s3 = 0.0;

	// if (isinf(x->val[0])) {
	// 	return;
	// }

	s0 = Float64_quick_two_sum(x->val[2], x->val[3], &x->val[3]);
	s0 = Float64_quick_two_sum(x->val[1], s0, &x->val[2]);
	x->val[0] = Float64_quick_two_sum(x->val[0], s0, &x->val[1]);

	s0 = x->val[0];
	s1 = x->val[1];
	if (s1 != 0.0) {
		s1 = Float64_quick_two_sum(s1, x->val[2], &s2);
		if (s2 != 0.0) {
			s2 = Float64_quick_two_sum(s2, x->val[3], &s3);
		} else {
			s1 = Float64_quick_two_sum(s1, x->val[3], &s2);
		}
	} else {
		s0 = Float64_quick_two_sum(s0, x->val[2], &s1);
		if (s1 != 0.0) {
			s1 = Float64_quick_two_sum(s1, x->val[3], &s2);
		} else {
			s0 = Float64_quick_two_sum(s0, x->val[3], &s1);
		}
	}

	x->val[0] = s0;
	x->val[1] = s1;
	x->val[2] = s2;
	x->val[3] = s3;
}

static inline void Float64x4_quick_renorm(Float64x4* LDF_restrict const x) {
	fp64 t0, t1, t2;
	fp64 s;
	s         = x->val[3];
	s         = Float64_quick_two_sum(x->val[2], s, &t2);
	s         = Float64_quick_two_sum(x->val[1], s, &t1);
	x->val[0] = Float64_quick_two_sum(x->val[0], s, &t0);

	s         = Float64_quick_two_sum(t1, t2, &t1);
	x->val[1] = Float64_quick_two_sum(t0, s , &t0);
	x->val[2] = Float64_quick_two_sum(t0, t1, &t0);
	x->val[3] = t0;
}

static inline void Float64x4_renorm(
	Float64x4* LDF_restrict const x
) {
	#ifdef FLOAT64X4_IEEE_MODE
		Float64x4_accurate_renorm(x);
	#else
		Float64x4_quick_renorm(x);
	#endif
}

static inline void Float64x4_accurate_renorm_err(
	Float64x4* LDF_restrict const x, fp64* LDF_restrict const err
) {
	fp64 s0, s1, s2 = 0.0, s3 = 0.0;

	// if (isinf(x->val[0])) {
	// 	return;
	// }

	s0        = Float64_quick_two_sum(x->val[3], *err, err       );
	s0        = Float64_quick_two_sum(x->val[2], s0  , &x->val[3]);
	s0        = Float64_quick_two_sum(x->val[1], s0  , &x->val[2]);
	x->val[0] = Float64_quick_two_sum(x->val[0], s0  , &x->val[1]);

	s0 = x->val[0];
	s1 = x->val[1];

	if (s1 != 0.0) {
		s1 = Float64_quick_two_sum(s1, x->val[2], &s2);
		if (s2 != 0.0) {
		s2 = Float64_quick_two_sum(s2, x->val[3], &s3);
			if (s3 != 0.0) {
				s3 += *err;
			} else {
				s2 = Float64_quick_two_sum(s2, *err, &s3);
			}
		} else {
		s1 = Float64_quick_two_sum(s1, x->val[3], &s2);
			if (s2 != 0.0) {
				s2 = Float64_quick_two_sum(s2, *err, &s3);
			} else {
				s1 = Float64_quick_two_sum(s1, *err, &s2);
			}
		}
	} else {
		s0 = Float64_quick_two_sum(s0, x->val[2], &s1);
		if (s1 != 0.0) {
		s1 = Float64_quick_two_sum(s1, x->val[3], &s2);
			if (s2 != 0.0) {
				s2 = Float64_quick_two_sum(s2, *err, &s3);
			} else {
				s1 = Float64_quick_two_sum(s1, *err, &s2);
			}
		} else {
		s0 = Float64_quick_two_sum(s0, x->val[3], &s1);
			if (s1 != 0.0) {
				s1 = Float64_quick_two_sum(s1, *err, &s2);
			} else {
				s0 = Float64_quick_two_sum(s0, *err, &s1);
			}
		}
	}

	x->val[0] = s0;
	x->val[1] = s1;
	x->val[2] = s2;
	x->val[3] = s3;
}

static inline void Float64x4_quick_renorm_err(
	Float64x4* LDF_restrict const x, fp64* LDF_restrict const err
) {
	fp64 t0, t1, t2, t3;
	fp64 s;
	s         = Float64_quick_two_sum(x->val[3], *err, &t3);
	s         = Float64_quick_two_sum(x->val[2], s   , &t2);
	s         = Float64_quick_two_sum(x->val[1], s   , &t1);
	x->val[0] = Float64_quick_two_sum(x->val[0], s   , &t0);

	s         = Float64_quick_two_sum(t2, t3, &t2);
	s         = Float64_quick_two_sum(t1, s , &t1);
	x->val[1] = Float64_quick_two_sum(t0, s , &t0);

	s         = Float64_quick_two_sum(t1, t2, &t1);
	x->val[2] = Float64_quick_two_sum(t0, s , &t0);
	
	x->val[3] = t0 + t1;
}

static inline void Float64x4_renorm_err(
	Float64x4* LDF_restrict const x, fp64* LDF_restrict const err
) {
	#ifdef FLOAT64X4_IEEE_MODE
		Float64x4_accurate_renorm_err(x, err);
	#else
		Float64x4_quick_renorm_err(x, err);
	#endif
}

//------------------------------------------------------------------------------
// Float64x4 Arithmetic
//------------------------------------------------------------------------------

/* Negation */

/**
 * @brief Negates a Float64x4 value (multiplies by -1.0)
 */
static inline Float64x4 Float64x4_negate(const Float64x4 x) {
	Float64x4 ret = {{-x.val[0], -x.val[1], -x.val[2], -x.val[3]}};
	return ret;
}

//------------------------------------------------------------------------------
// Float64x4 Addition
//------------------------------------------------------------------------------
/** 
 * @author Taken and/or modified from libQD which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */

/* Float64x4 + Float64x4 */

/** @brief Orginally qd_real::ieee_add */
static inline Float64x4 Float64x4_add_accurate(const Float64x4 x, const Float64x4 y) {
	int i, j, k;
	fp64 s, t;
	fp64 u, v;   /* double-length accumulator */
	Float64x4 ret = Float64x4_set_zero();
	
	i = j = k = 0;
	if (fabs(x.val[i]) > fabs(y.val[j])) {
		u = x.val[i++];
	} else {
		u = y.val[j++];
	}
	if (fabs(x.val[i]) > fabs(y.val[j])) {
		v = x.val[i++];
	} else {
		v = y.val[j++];
	}

	u = Float64_quick_two_sum(u, v, &v);
	
	while (k < 4) {
		if (i >= 4 && j >= 4) {
			ret.val[k] = u;
			if (k < 3) {
				ret.val[++k] = v;
			}
			break;
		}

		if (i >= 4) {
			t = y.val[j++];
		} else if (j >= 4) {
			t = x.val[i++];
		} else if (fabs(x.val[i]) > fabs(y.val[j])) {
			t = x.val[i++];
		} else {
			t = y.val[j++];
		}

		s = Float64x4_quick_three_accum(&u, &v, t);

		if (s != 0.0) {
			ret.val[k++] = s;
		}
	}

	/* add the rest. */
	for (k = i; k < 4; k++) {
		ret.val[3] += x.val[k];
	}
	for (k = j; k < 4; k++) {
		ret.val[3] += y.val[k];
	}

	Float64x4_renorm(&ret);
	return ret;
}

/** @brief Orginally qd_real::sloppy_add */
static inline Float64x4 Float64x4_add_quick(const Float64x4 x, const Float64x4 y) {
	/*
	fp64 s0, s1, s2, s3;
	fp64 t0, t1, t2, t3;
	
	s0 = Float64_two_sum(x.val[0], y.val[0], t0);
	s1 = Float64_two_sum(x.val[1], y.val[1], t1);
	s2 = Float64_two_sum(x.val[2], y.val[2], t2);
	s3 = Float64_two_sum(x.val[3], y.val[3], t3);

	s1 = Float64_two_sum(s1, t0, t0);
	Float64_three_sum(s2, t0, t1);
	Float64_three_sum2(s3, t0, t2);
	t0 = t0 + t1 + t3;

	Float64_renorm(s0, s1, s2, s3, t0);
	return qd_real(s0, s1, s2, s3, t0);
	*/

	/* Same as above, but addition re-organized to minimize
		data dependency ... unfortunately some compilers are
		not very smart to do this automatically */
	Float64x4 s;
	fp64 t0, t1, t2, t3;

	fp64 v0, v1, v2, v3;
	fp64 u0, u1, u2, u3;
	fp64 w0, w1, w2, w3;

	s.val[0] = x.val[0] + y.val[0];
	s.val[1] = x.val[1] + y.val[1];
	s.val[2] = x.val[2] + y.val[2];
	s.val[3] = x.val[3] + y.val[3];

	v0 = s.val[0] - x.val[0];
	v1 = s.val[1] - x.val[1];
	v2 = s.val[2] - x.val[2];
	v3 = s.val[3] - x.val[3];

	u0 = s.val[0] - v0;
	u1 = s.val[1] - v1;
	u2 = s.val[2] - v2;
	u3 = s.val[3] - v3;

	w0 = x.val[0] - u0;
	w1 = x.val[1] - u1;
	w2 = x.val[2] - u2;
	w3 = x.val[3] - u3;

	u0 = y.val[0] - v0;
	u1 = y.val[1] - v1;
	u2 = y.val[2] - v2;
	u3 = y.val[3] - v3;

	t0 = w0 + u0;
	t1 = w1 + u1;
	t2 = w2 + u2;
	t3 = w3 + u3;

	s.val[1] = Float64_two_sum(s.val[1], t0, &t0);
	Float64x4_three_sum (&s.val[2], &t0, &t1);
	Float64x4_three_sum2(&s.val[3], &t0,  t2);
	t0 = t0 + t1 + t3;

	/* renormalize */
	Float64x4_renorm_err(&s, &t0);
	return s;
}

static inline Float64x4 Float64x4_add(const Float64x4 x, const Float64x4 y) {
	#ifdef FLOAT64X4_IEEE_MODE
		return Float64x4_add_accurate(x, y);
	#else
		return Float64x4_add_quick(x, y);
	#endif
}

/* Float64x4 + Float64x2 */

static inline Float64x4 Float64x4_add_dx4_dx2(const Float64x4 x, const Float64x2 y) {
	Float64x4 s;
	fp64 t0, t1;

	s.val[0] = Float64_two_sum(x.val[0], y.hi, &t0);
	s.val[1] = Float64_two_sum(x.val[1], y.lo, &t1);

	s.val[1] = Float64_two_sum(s.val[1], t0, &t0);

	s.val[2] = x.val[2];
	Float64x4_three_sum(&s.val[2], &t0, &t1);

	s.val[3] = Float64_two_sum(t0, x.val[3], &t0);
	t0 += t1;

	Float64x4_renorm_err(&s, &t0);
	return s;
}

/* Float64x2 + Float64x4 */

static inline Float64x4 Float64x4_add_dx2_dx4(const Float64x2 x, const Float64x4 y) {
	Float64x4 s;
	fp64 t0, t1;

	s.val[0] = Float64_two_sum(x.hi, y.val[0], &t0);
	s.val[1] = Float64_two_sum(x.lo, y.val[1], &t1);

	s.val[1] = Float64_two_sum(s.val[1], t0, &t0);

	s.val[2] = y.val[2];
	Float64x4_three_sum(&s.val[2], &t0, &t1);

	s.val[3] = Float64_two_sum(t0, y.val[3], &t0);
	t0 += t1;

	Float64x4_renorm_err(&s, &t0);
	return s;
}

/* Float64x4 + fp64 */

static inline Float64x4 Float64x4_add_dx4_d(const Float64x4 x, const fp64 y) {
	Float64x4 ret;
	fp64 e;

	ret.val[0] = Float64_two_sum(x.val[0], y, &e);
	ret.val[1] = Float64_two_sum(x.val[1], e, &e);
	ret.val[2] = Float64_two_sum(x.val[2], e, &e);
	ret.val[3] = Float64_two_sum(x.val[3], e, &e);

	Float64x4_renorm_err(&ret, &e);
	return ret;
}

/* fp64 + Float64x4 */

static inline Float64x4 Float64x4_add_d_dx4(const fp64 x, const Float64x4 y) {
	Float64x4 ret;
	fp64 e;

	ret.val[0] = Float64_two_sum(x, y.val[0], &e);
	ret.val[1] = Float64_two_sum(e, y.val[1], &e);
	ret.val[2] = Float64_two_sum(e, y.val[2], &e);
	ret.val[3] = Float64_two_sum(e, y.val[3], &e);

	Float64x4_renorm_err(&ret, &e);
	return ret;
}

//------------------------------------------------------------------------------
// Float64x4 Optimized Addition
//------------------------------------------------------------------------------

/* Float64x2 + Float64x2 */

static inline Float64x4 Float64x4_add_dx2_dx2(const Float64x2 x, const Float64x2 y) {
	Float64x4 s;
	fp64 t0, t1;

	s.val[0] = Float64_two_sum(x.hi, y.hi, &t0);
	s.val[1] = Float64_two_sum(x.lo, y.lo, &t1);

	s.val[1] = Float64_two_sum(s.val[1], t0, &t0);
	s.val[2] = Float64_two_sum(t0, t1, &t0);
	s.val[3] = t0;

	// Float64x4_renorm_err(&s, &t1);
	return s;
}

/* Float64x2 + fp64 */

static inline Float64x4 Float64x4_add_dx2_d(const Float64x2 x, const fp64 y) {
	Float64x4 s;
	fp64 t0;

	s.val[0] = Float64_two_sum(x.hi, y, &t0);
	s.val[1] = x.lo;

	s.val[1] = Float64_two_sum(s.val[1], t0, &t0);
	s.val[2] = t0;
	s.val[3] = 0.0;
	return s; // renormalization not needed
}

/* fp64 + Float64x2 */

static inline Float64x4 Float64x4_add_d_dx2(const fp64 x, const Float64x2 y) {
	Float64x4 s;
	fp64 t0;

	s.val[0] = Float64_two_sum(x, y.hi, &t0);
	s.val[1] = y.lo;

	s.val[1] = Float64_two_sum(s.val[1], t0, &t0);
	s.val[2] = t0;
	s.val[3] = 0.0;
	return s; // renormalization not needed
}

/* fp64 + fp64 */

static inline Float64x4 Float64x4_add_d_d(const fp64 x, const fp64 y) {
	Float64x4 s;
	fp64 t0;

	s.val[0] = Float64_two_sum(x, y, &t0);
	s.val[1] = t0;
	s.val[2] = 0.0;
	s.val[3] = 0.0;
	return s; // renormalization not needed
}

//------------------------------------------------------------------------------
// Float64x4 Subtraction
//------------------------------------------------------------------------------
/** 
 * @author Taken and/or modified from libQD which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */

/* Float64x4 - Float64x4 */

/** @brief Orginally qd_real::ieee_add */
static inline Float64x4 Float64x4_sub_accurate(const Float64x4 x, const Float64x4 y) {
	int i, j, k;
	fp64 s, t;
	fp64 u, v;   /* double-length accumulator */
	Float64x4 ret = Float64x4_set_zero();
	
	i = j = k = 0;
	if (fabs(x.val[i]) > fabs(y.val[j])) {
		u = x.val[i++];
	} else {
		u = -y.val[j++];
	}
	if (fabs(x.val[i]) > fabs(y.val[j])) {
		v = x.val[i++];
	} else {
		v = -y.val[j++];
	}

	u = Float64_quick_two_sum(u, v, &v);
	
	while (k < 4) {
		if (i >= 4 && j >= 4) {
			ret.val[k] = u;
			if (k < 3) {
				ret.val[++k] = v;
			}
			break;
		}

		if (i >= 4) {
			t = -y.val[j++];
		} else if (j >= 4) {
			t = x.val[i++];
		} else if (fabs(x.val[i]) > fabs(y.val[j])) {
			t = x.val[i++];
		} else {
			t = -y.val[j++];
		}

		s = Float64x4_quick_three_accum(&u, &v, t);

		if (s != 0.0) {
			ret.val[k++] = s;
		}
	}

	/* add the rest. */
	for (k = i; k < 4; k++) {
		ret.val[3] += x.val[k];
	}
	for (k = j; k < 4; k++) {
		ret.val[3] -= y.val[k];
	}

	Float64x4_renorm(&ret);
	return ret;
}

/** @brief Orginally qd_real::sloppy_add */
static inline Float64x4 Float64x4_sub_quick(const Float64x4 x, const Float64x4 y) {
	/*
	fp64 s0, s1, s2, s3;
	fp64 t0, t1, t2, t3;
	
	s0 = Float64_two_sum(x.val[0], y.val[0], t0);
	s1 = Float64_two_sum(x.val[1], y.val[1], t1);
	s2 = Float64_two_sum(x.val[2], y.val[2], t2);
	s3 = Float64_two_sum(x.val[3], y.val[3], t3);

	s1 = Float64_two_sum(s1, t0, t0);
	Float64_three_sum(s2, t0, t1);
	Float64_three_sum2(s3, t0, t2);
	t0 = t0 + t1 + t3;

	Float64_renorm(s0, s1, s2, s3, t0);
	return qd_real(s0, s1, s2, s3, t0);
	*/

	/* Same as above, but addition re-organized to minimize
		data dependency ... unfortunately some compilers are
		not very smart to do this automatically */
	Float64x4 s;
	fp64 t0, t1, t2, t3;

	fp64 v0, v1, v2, v3;
	fp64 u0, u1, u2, u3;
	fp64 w0, w1, w2, w3;

	s.val[0] = x.val[0] - y.val[0];
	s.val[1] = x.val[1] - y.val[1];
	s.val[2] = x.val[2] - y.val[2];
	s.val[3] = x.val[3] - y.val[3];

	v0 = s.val[0] - x.val[0];
	v1 = s.val[1] - x.val[1];
	v2 = s.val[2] - x.val[2];
	v3 = s.val[3] - x.val[3];

	u0 = s.val[0] - v0;
	u1 = s.val[1] - v1;
	u2 = s.val[2] - v2;
	u3 = s.val[3] - v3;

	w0 = x.val[0] - u0;
	w1 = x.val[1] - u1;
	w2 = x.val[2] - u2;
	w3 = x.val[3] - u3;

	// u is negative
	u0 = y.val[0] + v0;
	u1 = y.val[1] + v1;
	u2 = y.val[2] + v2;
	u3 = y.val[3] + v3;

	t0 = w0 - u0;
	t1 = w1 - u1;
	t2 = w2 - u2;
	t3 = w3 - u3;

	s.val[1] = Float64_two_sum(s.val[1], t0, &t0);
	Float64x4_three_sum (&s.val[2], &t0, &t1);
	Float64x4_three_sum2(&s.val[3], &t0,  t2);
	t0 = t0 + t1 + t3;

	/* renormalize */
	Float64x4_renorm_err(&s, &t0);
	return s;
}

static inline Float64x4 Float64x4_sub(const Float64x4 x, const Float64x4 y) {
	#ifdef FLOAT64X4_IEEE_MODE
		return Float64x4_sub_accurate(x, y);
	#else
		return Float64x4_sub_quick(x, y);
	#endif
}

/* Float64x4 - Float64x2 */

static inline Float64x4 Float64x4_sub_dx4_dx2(const Float64x4 x, const Float64x2 y) {
	Float64x4 s;
	fp64 t0, t1;

	s.val[0] = Float64_two_diff(x.val[0], y.hi, &t0);
	s.val[1] = Float64_two_diff(x.val[1], y.lo, &t1);

	s.val[1] = Float64_two_sum(s.val[1], t0, &t0);

	s.val[2] = x.val[2];
	Float64x4_three_sum(&s.val[2], &t0, &t1);

	s.val[3] = Float64_two_sum(t0, x.val[3], &t0);
	t0 += t1;

	Float64x4_renorm_err(&s, &t0);
	return s;
}

/* Float64x2 - Float64x4 */

static inline Float64x4 Float64x4_sub_dx2_dx4(const Float64x2 x, const Float64x4 y) {
	Float64x4 s;
	fp64 t0, t1;

	s.val[0] = Float64_two_diff(x.hi, y.val[0], &t0);
	s.val[1] = Float64_two_diff(x.lo, y.val[1], &t1);

	s.val[1] = Float64_two_sum(s.val[1], t0, &t0);

	s.val[2] = -y.val[2];
	Float64x4_three_sum(&s.val[2], &t0, &t1);

	s.val[3] = Float64_two_diff(t0, y.val[3], &t0);
	t0 += t1;

	Float64x4_renorm_err(&s, &t0);
	return s;
}

/* Float64x4 - fp64 */

static inline Float64x4 Float64x4_sub_dx4_d(const Float64x4 x, const fp64 y) {
	Float64x4 ret;
	fp64 e;

	ret.val[0] = Float64_two_diff(x.val[0], y, &e);
	ret.val[1] = Float64_two_sum(x.val[1], e, &e);
	ret.val[2] = Float64_two_sum(x.val[2], e, &e);
	ret.val[3] = Float64_two_sum(x.val[3], e, &e);

	Float64x4_renorm_err(&ret, &e);
	return ret;
}

/* fp64 - Float64x4 */

static inline Float64x4 Float64x4_sub_d_dx4(const fp64 x, const Float64x4 y) {
	Float64x4 ret;
	fp64 e;

	ret.val[0] = Float64_two_diff(x, y.val[0], &e);
	ret.val[1] = Float64_two_diff(e, y.val[1], &e);
	ret.val[2] = Float64_two_diff(e, y.val[2], &e);
	ret.val[3] = Float64_two_diff(e, y.val[3], &e);

	Float64x4_renorm_err(&ret, &e);
	return ret;
}

//------------------------------------------------------------------------------
// Float64x4 Optimized Subtraction
//------------------------------------------------------------------------------
/** 
 * @author Taken and/or modified from libQD which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */

/* Float64x2 - Float64x2 */

static inline Float64x4 Float64x4_sub_dx2_dx2(const Float64x2 x, const Float64x2 y) {
	Float64x4 s;
	fp64 t0, t1;

	s.val[0] = Float64_two_diff(x.hi, y.hi, &t0);
	s.val[1] = Float64_two_diff(x.lo, y.lo, &t1);

	s.val[1] = Float64_two_sum(s.val[1], t0, &t0);
	s.val[2] = Float64_two_sum(t0, t1, &t0);
	s.val[3] = t0;

	// Float64x4_renorm_err(&s, &t1);
	return s;
}

/* Float64x2 - fp64 */

static inline Float64x4 Float64x4_sub_dx2_d(const Float64x2 x, const fp64 y) {
	Float64x4 s;
	fp64 t0;

	s.val[0] = Float64_two_diff(x.hi, y, &t0);
	s.val[1] = x.lo;

	s.val[1] = Float64_two_sum(s.val[1], t0, &t0);
	s.val[2] = t0;
	s.val[3] = 0.0;
	return s; // renormalization not needed
}

/* fp64 - Float64x2 */

static inline Float64x4 Float64x4_sub_d_dx2(const fp64 x, const Float64x2 y) {
	Float64x4 s;
	fp64 t0;

	s.val[0] = Float64_two_diff(x, y.hi, &t0);
	s.val[1] = -y.lo;

	s.val[1] = Float64_two_sum(s.val[1], t0, &t0);
	s.val[2] = t0;
	s.val[3] = 0.0;
	return s; // renormalization not needed
}

/* fp64 - fp64 */

static inline Float64x4 Float64x4_sub_d_d(const fp64 x, const fp64 y) {
	Float64x4 s;
	fp64 t0;

	s.val[0] = Float64_two_diff(x, y, &t0);
	s.val[1] = t0;
	s.val[2] = 0.0;
	s.val[3] = 0.0;
	return s; // renormalization not needed
}

//------------------------------------------------------------------------------
// Float64x4 Multiplication
//------------------------------------------------------------------------------
/** 
 * @author Taken/Modified from libQD which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */

/* Float64x4 * Float64x4 */

/** @brief Orginally qd_real::accurate_mul */
static inline Float64x4 Float64x4_mul_accurate(const Float64x4 x, const Float64x4 y) {
	fp64 p0, p1, p2, p3, p4, p5;
	fp64 q0, q1, q2, q3, q4, q5;
	fp64 p6, p7, p8, p9;
	fp64 q6, q7, q8, q9;
	fp64 r0, r1;
	fp64 t0, t1;
	fp64 s0, s1, s2;

	p0 = Float64_two_prod(x.val[0], y.val[0], &q0);

	p1 = Float64_two_prod(x.val[0], y.val[1], &q1);
	p2 = Float64_two_prod(x.val[1], y.val[0], &q2);

	p3 = Float64_two_prod(x.val[0], y.val[2], &q3);
	p4 = Float64_two_prod(x.val[1], y.val[1], &q4);
	p5 = Float64_two_prod(x.val[2], y.val[0], &q5);

	/* Start Accumulation */
	Float64x4_three_sum(&p1, &p2, &q0);

	/* Six-Three Sum  of p2, q1, q2, p3, p4, p5. */
	Float64x4_three_sum(&p2, &q1, &q2);
	Float64x4_three_sum(&p3, &p4, &p5);
	/* compute (s0, s1, s2) = (p2, q1, q2) + (p3, p4, p5). */
	s0 = Float64_two_sum(p2, p3, &t0);
	s1 = Float64_two_sum(q1, p4, &t1);
	s2 = q2 + p5;
	s1 = Float64_two_sum(s1, t0, &t0);
	s2 += (t0 + t1);

	/* O(eps^3) order terms */
	p6 = Float64_two_prod(x.val[0], y.val[3], &q6);
	p7 = Float64_two_prod(x.val[1], y.val[2], &q7);
	p8 = Float64_two_prod(x.val[2], y.val[1], &q8);
	p9 = Float64_two_prod(x.val[3], y.val[0], &q9);

	/* Nine-Two-Sum of q0, s1, q3, q4, q5, p6, p7, p8, p9. */
	q0 = Float64_two_sum(q0, q3, &q3);
	q4 = Float64_two_sum(q4, q5, &q5);
	p6 = Float64_two_sum(p6, p7, &p7);
	p8 = Float64_two_sum(p8, p9, &p9);
	/* Compute (t0, t1) = (q0, q3) + (q4, q5). */
	t0 = Float64_two_sum(q0, q4, &t1);
	t1 += (q3 + q5);
	/* Compute (r0, r1) = (p6, p7) + (p8, p9). */
	r0 = Float64_two_sum(p6, p8, &r1);
	r1 += (p7 + p9);
	/* Compute (q3, q4) = (t0, t1) + (r0, r1). */
	q3 = Float64_two_sum(t0, r0, &q4);
	q4 += (t1 + r1);
	/* Compute (t0, t1) = (q3, q4) + s1. */
	t0 = Float64_two_sum(q3, s1, &t1);
	t1 += q4;

	/* O(eps^4) terms -- Nine-One-Sum */
	t1 += x.val[1] * y.val[3] + x.val[2] * y.val[2] + x.val[3] * y.val[1] + q6 + q7 + q8 + q9 + s2;
	Float64x4 ret = {{p0, p1, s0, t0}};
	Float64x4_renorm_err(&ret, &t1);
	return ret;
}

/** @brief Orginally qd_real::sloppy_mul */
static inline Float64x4 Float64x4_mul_quick(const Float64x4 x, const Float64x4 y) {
	fp64 p0, p1, p2, p3, p4, p5;
	fp64 q0, q1, q2, q3, q4, q5;
	fp64 t0, t1;
	fp64 s0, s1, s2;

	p0 = Float64_two_prod(x.val[0], y.val[0], &q0);

	p1 = Float64_two_prod(x.val[0], y.val[1], &q1);
	p2 = Float64_two_prod(x.val[1], y.val[0], &q2);

	p3 = Float64_two_prod(x.val[0], y.val[2], &q3);
	p4 = Float64_two_prod(x.val[1], y.val[1], &q4);
	p5 = Float64_two_prod(x.val[2], y.val[0], &q5);

	/* Start Accumulation */
	Float64x4_three_sum(&p1, &p2, &q0);

	/* Six-Three Sum  of p2, q1, q2, p3, p4, p5. */
	Float64x4_three_sum(&p2, &q1, &q2);
	Float64x4_three_sum(&p3, &p4, &p5);
	/* compute (s0, s1, s2) = (p2, q1, q2) + (p3, p4, p5). */
	s0 = Float64_two_sum(p2, p3, &t0);
	s1 = Float64_two_sum(q1, p4, &t1);
	s2 = q2 + p5;
	s1 = Float64_two_sum(s1, t0, &t0);
	s2 += (t0 + t1);

	/* O(eps^3) order terms */
	s1 += x.val[0]*y.val[3] + x.val[1]*y.val[2] + x.val[2]*y.val[1] + x.val[3]*y.val[0] + q0 + q3 + q4 + q5;
	Float64x4 ret = {{p0, p1, s0, s1}};
	Float64x4_renorm_err(&ret, &s2);
	return ret;
}

static inline Float64x4 Float64x4_mul(const Float64x4 x, const Float64x4 y) {
	#ifdef FLOAT64X4_IEEE_MODE
		return Float64x4_mul_accurate(x, y);
	#else
		return Float64x4_mul_quick(x, y);
	#endif
}

/* Float64x4 * Float64x2 */

static inline Float64x4 Float64x4_mul_dx4_dx2(const Float64x4 x, const Float64x2 y) {
	Float64x4 p;
	fp64 p_err;
	fp64 q0, q1, q2, q3, q4;
	fp64 s0, s1, s2;
	fp64 t0, t1;

	p.val[0] = Float64_two_prod(x.val[0], y.hi, &q0);
	p.val[1] = Float64_two_prod(x.val[0], y.lo, &q1);
	p.val[2] = Float64_two_prod(x.val[1], y.hi, &q2);
	p.val[3] = Float64_two_prod(x.val[1], y.lo, &q3);
	p_err    = Float64_two_prod(x.val[2], y.hi, &q4);
	
	Float64x4_three_sum(&p.val[1], &p.val[2], &q0);
	
	/* Five-Three-Sum */
	Float64x4_three_sum(&p.val[2], &p.val[3], &p_err);
	q1 = Float64_two_sum(q1      , q2, &q2);
	s0 = Float64_two_sum(p.val[2], q1, &t0);
	s1 = Float64_two_sum(p.val[3], q2, &t1);
	s1 = Float64_two_sum(s1      , t0, &t0);
	s2 = t0 + t1 + p_err;
	p.val[2] = s0;

	p.val[3] = x.val[2] * y.hi + x.val[3] * y.lo + q3 + q4;
	Float64x4_three_sum2(&p.val[3], &q0, s1);
	p_err = q0 + s2;

	Float64x4_renorm_err(&p, &p_err);
	return p;
}

/* Float64x2 * Float64x4 */

static inline Float64x4 Float64x4_mul_dx2_dx4(const Float64x2 x, const Float64x4 y) {
	Float64x4 p;
	fp64 p_err;
	fp64 q0, q1, q2, q3, q4;
	fp64 s0, s1, s2;
	fp64 t0, t1;

	p.val[0] = Float64_two_prod(x.hi, y.val[0], &q0);
	p.val[1] = Float64_two_prod(x.lo, y.val[0], &q1);
	p.val[2] = Float64_two_prod(x.hi, y.val[1], &q2);
	p.val[3] = Float64_two_prod(x.lo, y.val[1], &q3);
	p_err    = Float64_two_prod(x.hi, y.val[2], &q4);
	
	Float64x4_three_sum(&p.val[1], &p.val[2], &q0);
	
	/* Five-Three-Sum */
	Float64x4_three_sum(&p.val[2], &p.val[3], &p_err);
	q1 = Float64_two_sum(q1      , q2, &q2);
	s0 = Float64_two_sum(p.val[2], q1, &t0);
	s1 = Float64_two_sum(p.val[3], q2, &t1);
	s1 = Float64_two_sum(s1      , t0, &t0);
	s2 = t0 + t1 + p_err;
	p.val[2] = s0;

	p.val[3] = y.val[2] * x.hi + y.val[3] * x.lo + q3 + q4;
	Float64x4_three_sum2(&p.val[3], &q0, s1);
	p_err = q0 + s2;

	Float64x4_renorm_err(&p, &p_err);
	return p;
}

/* Float64x4 * fp64 */

static inline Float64x4 Float64x4_mul_dx4_d(const Float64x4 x, const fp64 y) {
	fp64 p0, p1, p2, p3;
	fp64 q0, q1, q2;
	Float64x4 s;
	fp64 s_err;

	p0 = Float64_two_prod(x.val[0], y, &q0);
	p1 = Float64_two_prod(x.val[1], y, &q1);
	p2 = Float64_two_prod(x.val[2], y, &q2);
	p3 = x.val[3] * y;

	s.val[0] = p0;

	s.val[1] = Float64_two_sum(q0, p1, &s.val[2]);

	Float64x4_three_sum(&s.val[2], &q1, &p2);

	Float64x4_three_sum2(&q1, &q2, p3);
	s.val[3] = q1;

	s_err = q2 + p2;

	Float64x4_renorm_err(&s, &s_err);
	return s;
}

/* fp64 * Float64x4 */

static inline Float64x4 Float64x4_mul_d_dx4(const fp64 x, const Float64x4 y) {
	fp64 p0, p1, p2, p3;
	fp64 q0, q1, q2;
	Float64x4 s;
	fp64 s_err;

	p0 = Float64_two_prod(x, y.val[0], &q0);
	p1 = Float64_two_prod(x, y.val[1], &q1);
	p2 = Float64_two_prod(x, y.val[2], &q2);
	p3 = x * y.val[3];

	s.val[0] = p0;

	s.val[1] = Float64_two_sum(q0, p1, &s.val[2]);

	Float64x4_three_sum(&s.val[2], &q1, &p2);

	Float64x4_three_sum2(&q1, &q2, p3);
	s.val[3] = q1;

	s_err = q2 + p2;

	Float64x4_renorm_err(&s, &s_err);
	return s;
}

//------------------------------------------------------------------------------
// Float64x4 Optimized Mutliplication
//------------------------------------------------------------------------------
/** 
 * @author Modified from libQD which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */

/* Float64x2 * Float64x2 */

static inline Float64x4 Float64x4_mul_dx2_dx2(const Float64x2 x, const Float64x2 y) {
	Float64x4 p;
	fp64 p_err;
	fp64 q0, q1, q2, q3;
	fp64 s0, s1, s2;
	fp64 t0, t1;

	p.val[0] = Float64_two_prod(x.hi, y.hi, &q0);
	p.val[1] = Float64_two_prod(x.lo, y.hi, &q1);
	p.val[2] = Float64_two_prod(x.hi, y.lo, &q2);
	p.val[3] = Float64_two_prod(x.lo, y.lo, &q3);
	
	Float64x4_three_sum(&p.val[1], &p.val[2], &q0);
	
	/* Five-Three-Sum */
	p.val[2] = Float64_two_sum(p.val[2], p.val[3], &p.val[3]);
	q1 = Float64_two_sum(q1      , q2, &q2);
	s0 = Float64_two_sum(p.val[2], q1, &t0);
	s1 = Float64_two_sum(p.val[3], q2, &t1);
	s1 = Float64_two_sum(s1      , t0, &t0);
	s2 = t0 + t1;
	p.val[2] = s0;

	p.val[3] = q3;
	Float64x4_three_sum2(&p.val[3], &q0, s1);
	p_err = q0 + s2;

	Float64x4_renorm_err(&p, &p_err);
	return p;
}

/* Float64x2 * fp64 */

/**
 * @brief Multiplies a Float64x2 value with a fp64 value. Storing the result as
 * a Float64x4 value
 */
static inline Float64x4 Float64x4_mul_dx2_d(const Float64x2 x, const fp64 y) {
	fp64 p0, p1;
	fp64 q0, q1;
	Float64x4 s;

	p0 = Float64_two_prod(x.hi, y, &q0);
	p1 = Float64_two_prod(x.lo, y, &q1);

	s.val[0] = p0;
	s.val[1] = Float64_two_sum(q0, p1, &s.val[2]);
	s.val[2] = Float64_two_sum(s.val[2], q1, &q1);
	s.val[3] = q1;

	Float64x4_renorm(&s);
	return s;
}

/* fp64 * Float64x2 */

/**
 * @brief Multiplies a fp64 value with a Float64x2 value. Storing the result as
 * a Float64x4 value
 */
static inline Float64x4 Float64x4_mul_d_dx2(const fp64 x, const Float64x2 y) {
	fp64 p0, p1;
	fp64 q0, q1;
	Float64x4 s;

	p0 = Float64_two_prod(x, y.hi, &q0);
	p1 = Float64_two_prod(x, y.lo, &q1);

	s.val[0] = p0;
	s.val[1] = Float64_two_sum(q0, p1, &s.val[2]);
	s.val[2] = Float64_two_sum(s.val[2], q1, &q1);
	s.val[3] = q1;

	Float64x4_renorm(&s);
	return s;
}

/* fp64 * fp64 */

/**
 * @brief Multiplies a fp64 value with another fp64 value. Storing the result
 * as a Float64x4 value.
 * @note Float64x2 can store the values from this function exactly.
 */
static inline Float64x4 Float64x4_mul_d_d(const fp64 x, const fp64 y) {
	Float64x4 s;
	s.val[0] = Float64_two_prod(x, y, &s.val[1]);
	s.val[2] = 0.0;
	s.val[3] = 0.0; 
	return s; // renormalization not needed
}

//------------------------------------------------------------------------------
// Float64x4 Square
//------------------------------------------------------------------------------
/** 
 * @author Taken/Modified from libQD which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */

static inline Float64x4 Float64x4_square(const Float64x4 x) {
	Float64x4 p;
	fp64 p_err_hi, p_err_lo;
	fp64 q0, q1, q2, q3;
	fp64 s0, s1;
	fp64 t0, t1;
	
	p.val[0] = Float64_two_sqr(x.val[0], &q0);
	p.val[1] = Float64_two_prod(2.0 * x.val[0], x.val[1], &q1);
	p.val[2] = Float64_two_prod(2.0 * x.val[0], x.val[2], &q2);
	p.val[3] = Float64_two_sqr(x.val[1], &q3);

	p.val[1] = Float64_two_sum(q0, p.val[1], &q0);

	q0 = Float64_two_sum(q0, q1, &q1);
	p.val[2] = Float64_two_sum(p.val[2], p.val[3], &p.val[3]);

	s0 = Float64_two_sum(q0, p.val[2], &t0);
	s1 = Float64_two_sum(q1, p.val[3], &t1);

	s1 = Float64_two_sum(s1, t0, &t0);
	t0 += t1;

	s1 = Float64_quick_two_sum(s1, t0, &t0);
	p.val[2] = Float64_quick_two_sum(s0, s1, &t1);
	p.val[3] = Float64_quick_two_sum(t1, t0, &q0);

	p_err_hi = 2.0 * x.val[0] * x.val[3];
	p_err_lo = 2.0 * x.val[1] * x.val[2];

	p_err_hi = Float64_two_sum(p_err_hi, p_err_lo, &p_err_lo);
	q2 = Float64_two_sum(q2, q3, &q3);

	t0 = Float64_two_sum(p_err_hi, q2, &t1);
	t1 = t1 + p_err_lo + q3;

	p.val[3] = Float64_two_sum(p.val[3], t0, &p_err_hi);
	p_err_hi = p_err_hi + q0 + t1;

	Float64x4_renorm_err(&p, &p_err_hi);
	return p;
}

/**
 * @brief Squares a Float64x2 value with the result stored as a Float64x4
 */
static inline Float64x4 Float64x4_square_dx2(const Float64x2 x) {
	Float64x4 p;
	fp64 p_err;
	fp64 q0, q1, q2;
	fp64 s0, s1;
	fp64 t0, t1;
	
	p.val[0] = Float64_two_sqr(x.hi, &q0);
	p.val[1] = Float64_two_prod(2.0 * x.hi, x.lo, &q1);
	p.val[2] = Float64_two_sqr(x.lo, &q2);

	p.val[1] = Float64_two_sum(q0, p.val[1], &q0);

	q0 = Float64_two_sum(q0, q1, &q1);
	s0 = Float64_two_sum(q0, p.val[2], &t0);

	s1 = Float64_two_sum(q1, t0, &t0);
	s1 = Float64_quick_two_sum(s1, t0, &t0);
	p.val[2] = Float64_quick_two_sum(s0, s1, &t1);
	p.val[3] = Float64_quick_two_sum(t1, t0, &q0);

	p.val[3] = Float64_two_sum(p.val[3], q2, &p_err);
	p_err += q0;

	Float64x4_renorm_err(&p, &p_err);
	return p;
}

/**
 * @brief Squares a fp64 value with the result stored as a Float64x4.
 * @note Float64x2 can store the values from this function exactly.
 */
static inline Float64x4 Float64x4_square_d(const fp64 x) {
	Float64x4 p;
	p.val[0] = Float64_two_sqr(x, &p.val[1]);
	p.val[2] = 0.0;
	p.val[3] = 0.0;
	return p; // renormalization not needed
}


//------------------------------------------------------------------------------
// Float64x4 Division
//------------------------------------------------------------------------------
/** 
 * @author Taken from libQD which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */

/* Float64x4 / Float64x4 */

/** @brief Orginally qd_real::accurate_div */
static inline Float64x4 Float64x4_div_accurate(const Float64x4 x, const Float64x4 y) {
	Float64x4 q, r;

	q.val[0] = x.val[0] / y.val[0];
	r = Float64x4_sub(x, Float64x4_mul_dx4_d(y, q.val[0]));

	q.val[1] = r.val[0] / y.val[0];
	r = Float64x4_sub(r, Float64x4_mul_dx4_d(y, q.val[1]));

	q.val[2] = r.val[0] / y.val[0];
	r = Float64x4_sub(r, Float64x4_mul_dx4_d(y, q.val[2]));

	q.val[3] = r.val[0] / y.val[0];
	r = Float64x4_sub(r, Float64x4_mul_dx4_d(y, q.val[3]));

	fp64 err = r.val[0] / y.val[0];
	Float64x4_renorm_err(&q, &err);
	return q;
}

/** @brief Orginally qd_real::sloppy_div */
static inline Float64x4 Float64x4_div_quick(const Float64x4 x, const Float64x4 y) {
	Float64x4 q, r;

	q.val[0] = x.val[0] / y.val[0];
	r = Float64x4_sub(x, Float64x4_mul_dx4_d(y, q.val[0]));

	q.val[1] = r.val[0] / y.val[0];
	r = Float64x4_sub(r, Float64x4_mul_dx4_d(y, q.val[1]));

	q.val[2] = r.val[0] / y.val[0];
	r = Float64x4_sub(r, Float64x4_mul_dx4_d(y, q.val[2]));

	q.val[3] = r.val[0] / y.val[0];
	Float64x4_renorm(&q);
	return q;
}

static inline Float64x4 Float64x4_div(const Float64x4 x, const Float64x4 y) {
	#ifdef FLOAT64X4_IEEE_MODE
		return Float64x4_div_accurate(x, y);
	#else
		return Float64x4_div_quick(x, y);
	#endif
}

/* Float64x4 / Float64x2 */

static inline Float64x4 Float64x4_div_accurate_dx4_dx2(const Float64x4 x, const Float64x2 y) {
	Float64x4 q, r;

	q.val[0] = x.val[0] / y.hi;
	r = Float64x4_sub(x, Float64x4_mul_dx2_d(y, q.val[0]));

	q.val[1] = r.val[0] / y.hi;
	r = Float64x4_sub(r, Float64x4_mul_dx2_d(y, q.val[1]));

	q.val[2] = r.val[0] / y.hi;
	r = Float64x4_sub(r, Float64x4_mul_dx2_d(y, q.val[2]));

	q.val[3] = r.val[0] / y.hi;
	r = Float64x4_sub(r, Float64x4_mul_dx2_d(y, q.val[3]));

	fp64 err = r.val[0] / y.hi;
	Float64x4_renorm_err(&q, &err);
	return q;
}

static inline Float64x4 Float64x4_div_quick_dx4_dx2(const Float64x4 x, const Float64x2 y) {
	Float64x4 q, r;

	q.val[0] = x.val[0] / y.hi;
	r = Float64x4_sub(x, Float64x4_mul_dx2_d(y, q.val[0]));

	q.val[1] = r.val[0] / y.hi;
	r = Float64x4_sub(r, Float64x4_mul_dx2_d(y, q.val[1]));

	q.val[2] = r.val[0] / y.hi;
	r = Float64x4_sub(r, Float64x4_mul_dx2_d(y, q.val[2]));

	q.val[3] = r.val[0] / y.hi;
	Float64x4_renorm(&q);
	return q;
}

static inline Float64x4 Float64x4_div_dx4_dx2(const Float64x4 x, const Float64x2 y) {
	#ifdef FLOAT64X4_IEEE_MODE
		return Float64x4_div_accurate_dx4_dx2(x, y);
	#else
		return Float64x4_div_quick_dx4_dx2(x, y);
	#endif
}

/* Float64x4 / fp64 */

static inline Float64x4 Float64x4_div_accurate_dx4_d(const Float64x4 x, const fp64 y) {
	Float64x4 q, r;

	q.val[0] = x.val[0] / y;
	r = Float64x4_sub_dx4_dx2(x, Float64x2_mul_d_d(y, q.val[0]));

	q.val[1] = r.val[0] / y;
	r = Float64x4_sub_dx4_dx2(r, Float64x2_mul_d_d(y, q.val[1]));

	q.val[2] = r.val[0] / y;
	r = Float64x4_sub_dx4_dx2(r, Float64x2_mul_d_d(y, q.val[2]));

	q.val[3] = r.val[0] / y;
	r = Float64x4_sub_dx4_dx2(r, Float64x2_mul_d_d(y, q.val[3]));
	
	fp64 err = r.val[0] / y;
	Float64x4_renorm_err(&q, &err);
	return q;
}

static inline Float64x4 Float64x4_div_quick_dx4_d(const Float64x4 x, const fp64 y) {
	Float64x4 q, r;

	q.val[0] = x.val[0] / y;
	r = Float64x4_sub_dx4_dx2(x, Float64x2_mul_d_d(y, q.val[0]));

	q.val[1] = r.val[0] / y;
	r = Float64x4_sub_dx4_dx2(r, Float64x2_mul_d_d(y, q.val[1]));

	q.val[2] = r.val[0] / y;
	r = Float64x4_sub_dx4_dx2(r, Float64x2_mul_d_d(y, q.val[2]));

	q.val[3] = r.val[0] / y;
	Float64x4_renorm(&q);
	return q;
}

static inline Float64x4 Float64x4_div_dx4_d(const Float64x4 x, const fp64 y) {
	#ifdef FLOAT64X4_IEEE_MODE
		return Float64x4_div_accurate_dx4_d(x, y);
	#else
		return Float64x4_div_quick_dx4_d(x, y);
	#endif
}

/* Float64x2 / Float64x4 */

static inline Float64x4 Float64x4_div_accurate_dx2_dx4(const Float64x2 x, const Float64x4 y) {
	Float64x4 q, r;

	q.val[0] = x.hi / y.val[0];
	r = Float64x4_sub_dx2_dx4(x, Float64x4_mul_dx4_d(y, q.val[0]));

	q.val[1] = r.val[0] / y.val[0];
	r = Float64x4_sub(r, Float64x4_mul_dx4_d(y, q.val[1]));

	q.val[2] = r.val[0] / y.val[0];
	r = Float64x4_sub(r, Float64x4_mul_dx4_d(y, q.val[2]));

	q.val[3] = r.val[0] / y.val[0];
	r = Float64x4_sub(r, Float64x4_mul_dx4_d(y, q.val[3]));

	fp64 err = r.val[0] / y.val[0];
	Float64x4_renorm_err(&q, &err);
	return q;
}

static inline Float64x4 Float64x4_div_quick_dx2_dx4(const Float64x2 x, const Float64x4 y) {
	Float64x4 q, r;

	q.val[0] = x.hi / y.val[0];
	r = Float64x4_sub_dx2_dx4(x, Float64x4_mul_dx4_d(y, q.val[0]));

	q.val[1] = r.val[0] / y.val[0];
	r = Float64x4_sub(r, Float64x4_mul_dx4_d(y, q.val[1]));

	q.val[2] = r.val[0] / y.val[0];
	r = Float64x4_sub(r, Float64x4_mul_dx4_d(y, q.val[2]));

	q.val[3] = r.val[0] / y.val[0];
	Float64x4_renorm(&q);
	return q;
}

static inline Float64x4 Float64x4_div_dx2_dx4(const Float64x2 x, const Float64x4 y) {
	#ifdef FLOAT64X4_IEEE_MODE
		return Float64x4_div_accurate_dx2_dx4(x, y);
	#else
		return Float64x4_div_quick_dx2_dx4(x, y);
	#endif
}

/* fp64 / Float64x4 */

static inline Float64x4 Float64x4_div_accurate_d_dx4(const fp64 x, const Float64x4 y) {
	Float64x4 q, r;

	q.val[0] = x / y.val[0];
	r = Float64x4_sub_d_dx4(x, Float64x4_mul_dx4_d(y, q.val[0]));

	q.val[1] = r.val[0] / y.val[0];
	r = Float64x4_sub(r, Float64x4_mul_dx4_d(y, q.val[1]));

	q.val[2] = r.val[0] / y.val[0];
	r = Float64x4_sub(r, Float64x4_mul_dx4_d(y, q.val[2]));

	q.val[3] = r.val[0] / y.val[0];
	r = Float64x4_sub(r, Float64x4_mul_dx4_d(y, q.val[3]));

	fp64 err = r.val[0] / y.val[0];
	Float64x4_renorm_err(&q, &err);
	return q;
}

static inline Float64x4 Float64x4_div_quick_d_dx4(const fp64 x, const Float64x4 y) {
	Float64x4 q, r;

	q.val[0] = x / y.val[0];
	r = Float64x4_sub_d_dx4(x, Float64x4_mul_dx4_d(y, q.val[0]));

	q.val[1] = r.val[0] / y.val[0];
	r = Float64x4_sub(r, Float64x4_mul_dx4_d(y, q.val[1]));

	q.val[2] = r.val[0] / y.val[0];
	r = Float64x4_sub(r, Float64x4_mul_dx4_d(y, q.val[2]));

	q.val[3] = r.val[0] / y.val[0];
	Float64x4_renorm(&q);
	return q;
}

static inline Float64x4 Float64x4_div_d_dx4(const fp64 x, const Float64x4 y) {
	#ifdef FLOAT64X4_IEEE_MODE
		return Float64x4_div_accurate_d_dx4(x, y);
	#else
		return Float64x4_div_quick_d_dx4(x, y);
	#endif
}

//------------------------------------------------------------------------------
// Float64x4 Optimized Division
//------------------------------------------------------------------------------
/** 
 * @author Taken and/or modified from libQD which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */

/* Float64x2 / Float64x2 */

static inline Float64x4 Float64x4_div_accurate_dx2_dx2(const Float64x2 x, const Float64x2 y) {
	Float64x4 q, r;

	q.val[0] = x.hi / y.hi;
	r = Float64x4_sub_dx2_dx4(x, Float64x4_mul_dx2_d(y, q.val[0]));

	q.val[1] = r.val[0] / y.hi;
	r = Float64x4_sub(r, Float64x4_mul_dx2_d(y, q.val[1]));

	q.val[2] = r.val[0] / y.hi;
	r = Float64x4_sub(r, Float64x4_mul_dx2_d(y, q.val[2]));

	q.val[3] = r.val[0] / y.hi;
	r = Float64x4_sub(r, Float64x4_mul_dx2_d(y, q.val[3]));

	fp64 err = r.val[0] / y.hi;
	Float64x4_renorm_err(&q, &err);
	return q;
}

static inline Float64x4 Float64x4_div_quick_dx2_dx2(const Float64x2 x, const Float64x2 y) {
	Float64x4 q, r;

	q.val[0] = x.hi / y.hi;
	r = Float64x4_sub_dx2_dx4(x, Float64x4_mul_dx2_d(y, q.val[0]));

	q.val[1] = r.val[0] / y.hi;
	r = Float64x4_sub(r, Float64x4_mul_dx2_d(y, q.val[1]));

	q.val[2] = r.val[0] / y.hi;
	r = Float64x4_sub(r, Float64x4_mul_dx2_d(y, q.val[2]));

	q.val[3] = r.val[0] / y.hi;
	Float64x4_renorm(&q);
	return q;
}

static inline Float64x4 Float64x4_div_dx2_dx2(const Float64x2 x, const Float64x2 y) {
	#ifdef FLOAT64X4_IEEE_MODE
		return Float64x4_div_accurate_dx2_dx2(x, y);
	#else
		return Float64x4_div_quick_dx2_dx2(x, y);
	#endif
}

/* Float64x2 / fp64 */

static inline Float64x4 Float64x4_div_accurate_dx2_d(const Float64x2 x, const fp64 y) {
	Float64x4 q, r;

	q.val[0] = x.hi / y;
	r = Float64x4_sub_dx2_dx2(x, Float64x2_mul_d_d(y, q.val[0]));

	q.val[1] = r.val[0] / y;
	r = Float64x4_sub_dx4_dx2(r, Float64x2_mul_d_d(y, q.val[1]));

	q.val[2] = r.val[0] / y;
	r = Float64x4_sub_dx4_dx2(r, Float64x2_mul_d_d(y, q.val[2]));

	q.val[3] = r.val[0] / y;
	r = Float64x4_sub_dx4_dx2(r, Float64x2_mul_d_d(y, q.val[3]));

	fp64 err = r.val[0] / y;
	Float64x4_renorm_err(&q, &err);
	return q;
}

static inline Float64x4 Float64x4_div_quick_dx2_d(const Float64x2 x, const fp64 y) {
	Float64x4 q, r;

	q.val[0] = x.hi / y;
	r = Float64x4_sub_dx2_dx2(x, Float64x2_mul_d_d(y, q.val[0]));

	q.val[1] = r.val[0] / y;
	r = Float64x4_sub_dx4_dx2(r, Float64x2_mul_d_d(y, q.val[1]));

	q.val[2] = r.val[0] / y;
	r = Float64x4_sub_dx4_dx2(r, Float64x2_mul_d_d(y, q.val[2]));

	q.val[3] = r.val[0] / y;
	Float64x4_renorm(&q);
	return q;
}

static inline Float64x4 Float64x4_div_dx2_d(const Float64x2 x, const fp64 y) {
	#ifdef FLOAT64X4_IEEE_MODE
		return Float64x4_div_accurate_dx2_d(x, y);
	#else
		return Float64x4_div_quick_dx2_d(x, y);
	#endif
}

/* fp64 / Float64x2 */

static inline Float64x4 Float64x4_div_accurate_d_dx2(const fp64 x, const Float64x2 y) {
	Float64x4 q, r;

	q.val[0] = x / y.hi;
	r = Float64x4_sub_d_dx4(x, Float64x4_mul_dx2_d(y, q.val[0]));

	q.val[1] = r.val[0] / y.hi;
	r = Float64x4_sub(r, Float64x4_mul_dx2_d(y, q.val[1]));

	q.val[2] = r.val[0] / y.hi;
	r = Float64x4_sub(r, Float64x4_mul_dx2_d(y, q.val[2]));

	q.val[3] = r.val[0] / y.hi;
	r = Float64x4_sub(r, Float64x4_mul_dx2_d(y, q.val[3]));

	fp64 err = r.val[0] / y.hi;
	Float64x4_renorm_err(&q, &err);
	return q;
}

static inline Float64x4 Float64x4_div_quick_d_dx2(const fp64 x, const Float64x2 y) {
	Float64x4 q, r;

	q.val[0] = x / y.hi;
	r = Float64x4_sub_d_dx4(x, Float64x4_mul_dx2_d(y, q.val[0]));

	q.val[1] = r.val[0] / y.hi;
	r = Float64x4_sub(r, Float64x4_mul_dx2_d(y, q.val[1]));

	q.val[2] = r.val[0] / y.hi;
	r = Float64x4_sub(r, Float64x4_mul_dx2_d(y, q.val[2]));

	q.val[3] = r.val[0] / y.hi;
	Float64x4_renorm(&q);
	return q;
}

static inline Float64x4 Float64x4_div_d_dx2(const fp64 x, const Float64x2 y) {
	#ifdef FLOAT64X4_IEEE_MODE
		return Float64x4_div_accurate_d_dx2(x, y);
	#else
		return Float64x4_div_quick_d_dx2(x, y);
	#endif
}

/* fp64 / fp64 */

static inline Float64x4 Float64x4_div_accurate_d_d(const fp64 x, const fp64 y) {
	Float64x4 q, r;

	q.val[0] = x / y;
	r = Float64x4_sub_d_dx2(x, Float64x2_mul_d_d(y, q.val[0]));

	q.val[1] = r.val[0] / y;
	r = Float64x4_sub_dx4_dx2(r, Float64x2_mul_d_d(y, q.val[1]));

	q.val[2] = r.val[0] / y;
	r = Float64x4_sub_dx4_dx2(r, Float64x2_mul_d_d(y, q.val[2]));

	q.val[3] = r.val[0] / y;
	r = Float64x4_sub_dx4_dx2(r, Float64x2_mul_d_d(y, q.val[3]));

	fp64 err = r.val[0] / y;
	Float64x4_renorm_err(&q, &err);
	return q;
}

static inline Float64x4 Float64x4_div_quick_d_d(const fp64 x, const fp64 y) {
	Float64x4 q, r;

	q.val[0] = x / y;
	r = Float64x4_sub_d_dx2(x, Float64x2_mul_d_d(y, q.val[0]));

	q.val[1] = r.val[0] / y;
	r = Float64x4_sub_dx4_dx2(r, Float64x2_mul_d_d(y, q.val[1]));

	q.val[2] = r.val[0] / y;
	r = Float64x4_sub_dx4_dx2(r, Float64x2_mul_d_d(y, q.val[2]));

	q.val[3] = r.val[0] / y;
	Float64x4_renorm(&q);
	return q;
}

static inline Float64x4 Float64x4_div_d_d(const fp64 x, const fp64 y) {
	#ifdef FLOAT64X4_IEEE_MODE
		return Float64x4_div_accurate_d_d(x, y);
	#else
		return Float64x4_div_quick_d_d(x, y);
	#endif
}

//------------------------------------------------------------------------------
// Float64x4 Reciprocal
//------------------------------------------------------------------------------
/** 
 * @author Taken and/or modified from libQD which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */

/* 1.0 / Float64x4 */

static inline Float64x4 Float64x4_recip_accurate(const Float64x4 y) {
	Float64x4 q, r;

	q.val[0] = 1.0 / y.val[0];
	r = Float64x4_sub_d_dx4(1.0, Float64x4_mul_dx4_d(y, q.val[0]));

	q.val[1] = r.val[0] / y.val[0];
	r = Float64x4_sub(r, Float64x4_mul_dx4_d(y, q.val[1]));

	q.val[2] = r.val[0] / y.val[0];
	r = Float64x4_sub(r, Float64x4_mul_dx4_d(y, q.val[2]));

	q.val[3] = r.val[0] / y.val[0];
	r = Float64x4_sub(r, Float64x4_mul_dx4_d(y, q.val[3]));

	fp64 err = r.val[0] / y.val[0];
	Float64x4_renorm_err(&q, &err);
	return q;
}

static inline Float64x4 Float64x4_recip_quick(const Float64x4 y) {
	Float64x4 q, r;

	q.val[0] = 1.0 / y.val[0];
	r = Float64x4_sub_d_dx4(1.0, Float64x4_mul_dx4_d(y, q.val[0]));

	q.val[1] = r.val[0] / y.val[0];
	r = Float64x4_sub(r, Float64x4_mul_dx4_d(y, q.val[1]));

	q.val[2] = r.val[0] / y.val[0];
	r = Float64x4_sub(r, Float64x4_mul_dx4_d(y, q.val[2]));

	q.val[3] = r.val[0] / y.val[0];
	Float64x4_renorm(&q);
	return q;
}

static inline Float64x4 Float64x4_recip(const Float64x4 y) {
	#ifdef FLOAT64X4_IEEE_MODE
		return Float64x4_recip_accurate(y);
	#else
		return Float64x4_recip_quick(y);
	#endif
}

/* 1.0 / Float64x2 */

static inline Float64x4 Float64x4_recip_accurate_dx2(const Float64x2 y) {
	Float64x4 q, r;

	q.val[0] = 1.0 / y.hi;
	r = Float64x4_sub_d_dx4(1.0, Float64x4_mul_dx2_d(y, q.val[0]));

	q.val[1] = r.val[0] / y.hi;
	r = Float64x4_sub(r, Float64x4_mul_dx2_d(y, q.val[1]));

	q.val[2] = r.val[0] / y.hi;
	r = Float64x4_sub(r, Float64x4_mul_dx2_d(y, q.val[2]));

	q.val[3] = r.val[0] / y.hi;
	r = Float64x4_sub(r, Float64x4_mul_dx2_d(y, q.val[3]));

	fp64 err = r.val[0] / y.hi;
	Float64x4_renorm_err(&q, &err);
	return q;
}

static inline Float64x4 Float64x4_recip_quick_dx2(const Float64x2 y) {
	Float64x4 q, r;

	q.val[0] = 1.0 / y.hi;
	r = Float64x4_sub_d_dx4(1.0, Float64x4_mul_dx2_d(y, q.val[0]));

	q.val[1] = r.val[0] / y.hi;
	r = Float64x4_sub(r, Float64x4_mul_dx2_d(y, q.val[1]));

	q.val[2] = r.val[0] / y.hi;
	r = Float64x4_sub(r, Float64x4_mul_dx2_d(y, q.val[2]));

	q.val[3] = r.val[0] / y.hi;
	Float64x4_renorm(&q);
	return q;
}

static inline Float64x4 Float64x4_recip_dx2(const Float64x2 y) {
	#ifdef FLOAT64X4_IEEE_MODE
		return Float64x4_recip_accurate_dx2(y);
	#else
		return Float64x4_recip_quick_dx2(y);
	#endif
}

/* 1.0 / fp64 */

static inline Float64x4 Float64x4_recip_accurate_d(const fp64 y) {
	Float64x4 q, r;

	q.val[0] = 1.0 / y;
	r = Float64x4_sub_d_dx2(1.0, Float64x2_mul_d_d(y, q.val[0]));

	q.val[1] = r.val[0] / y;
	r = Float64x4_sub_dx4_dx2(r, Float64x2_mul_d_d(y, q.val[1]));

	q.val[2] = r.val[0] / y;
	r = Float64x4_sub_dx4_dx2(r, Float64x2_mul_d_d(y, q.val[2]));

	q.val[3] = r.val[0] / y;
	r = Float64x4_sub_dx4_dx2(r, Float64x2_mul_d_d(y, q.val[3]));

	fp64 err = r.val[0] / y;
	Float64x4_renorm_err(&q, &err);
	return q;
}

static inline Float64x4 Float64x4_recip_quick_d(const fp64 y) {
	Float64x4 q, r;

	q.val[0] = 1.0 / y;
	r = Float64x4_sub_d_dx2(1.0, Float64x2_mul_d_d(y, q.val[0]));

	q.val[1] = r.val[0] / y;
	r = Float64x4_sub_dx4_dx2(r, Float64x2_mul_d_d(y, q.val[1]));

	q.val[2] = r.val[0] / y;
	r = Float64x4_sub_dx4_dx2(r, Float64x2_mul_d_d(y, q.val[2]));

	q.val[3] = r.val[0] / y;
	Float64x4_renorm(&q);
	return q;
}

static inline Float64x4 Float64x4_recip_d(const fp64 y) {
	#ifdef FLOAT64X4_IEEE_MODE
		return Float64x4_recip_accurate_d(y);
	#else
		return Float64x4_recip_quick_d(y);
	#endif
}

//------------------------------------------------------------------------------
// Float64x4 specialized arithmetic
//------------------------------------------------------------------------------

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero
 */
static inline Float64x4 Float64x4_mul_power2_dx4_d(Float64x4 x, const fp64 y) {
	x.val[0] *= y;
	x.val[1] *= y;
	x.val[2] *= y;
	x.val[3] *= y;
	return x;
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero
 */
static inline Float64x4 Float64x4_mul_power2_d_dx4(const fp64 x, Float64x4 y) {
	y.val[0] *= x;
	y.val[1] *= x;
	y.val[2] *= x;
	y.val[3] *= x;
	return y;
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero.
 * The result is stored as a Float64x4
 */
static inline Float64x4 Float64x4_mul_power2_d_d(const fp64 x, const fp64 y) {
	Float64x4 ret;
	ret.val[0] = x * y;
	ret.val[1] = 0.0;
	ret.val[2] = 0.0;
	ret.val[3] = 0.0;
	return ret;
}

//------------------------------------------------------------------------------
// Float64x4 bitwise operations
//------------------------------------------------------------------------------

static inline Float64x4 Float64x4_bitwise_not(const Float64x4 x) {
	Bitwise_Float64x4 x0;
	x0.float_part = x;
	x0.binary_part.val[0] = ~x0.binary_part.val[0];
	x0.binary_part.val[1] = ~x0.binary_part.val[1];
	x0.binary_part.val[2] = ~x0.binary_part.val[2];
	x0.binary_part.val[3] = ~x0.binary_part.val[3];
	return x0.float_part;
}

static inline Float64x4 Float64x4_bitwise_and(const Float64x4 x, const Float64x4 y) {
	Bitwise_Float64x4 x0, y0;
	x0.float_part = x;
	y0.float_part = y;
	x0.binary_part.val[0] &= y0.binary_part.val[0];
	x0.binary_part.val[1] &= y0.binary_part.val[1];
	x0.binary_part.val[2] &= y0.binary_part.val[2];
	x0.binary_part.val[3] &= y0.binary_part.val[3];
	return x0.float_part;
}

static inline Float64x4 Float64x4_bitwise_andnot(const Float64x4 x, const Float64x4 y) {
	Bitwise_Float64x4 x0, y0;
	x0.float_part = x;
	y0.float_part = y;
	x0.binary_part.val[0] &= ~y0.binary_part.val[0];
	x0.binary_part.val[1] &= ~y0.binary_part.val[1];
	x0.binary_part.val[2] &= ~y0.binary_part.val[2];
	x0.binary_part.val[3] &= ~y0.binary_part.val[3];
	return x0.float_part;
}

static inline Float64x4 Float64x4_bitwise_or(const Float64x4 x, const Float64x4 y) {
	Bitwise_Float64x4 x0, y0;
	x0.float_part = x;
	y0.float_part = y;
	x0.binary_part.val[0] |= y0.binary_part.val[0];
	x0.binary_part.val[1] |= y0.binary_part.val[1];
	x0.binary_part.val[2] |= y0.binary_part.val[2];
	x0.binary_part.val[3] |= y0.binary_part.val[3];
	return x0.float_part;
}

static inline Float64x4 Float64x4_bitwise_xor(const Float64x4 x, const Float64x4 y) {
	Bitwise_Float64x4 x0, y0;
	x0.float_part = x;
	y0.float_part = y;
	x0.binary_part.val[0] ^= y0.binary_part.val[0];
	x0.binary_part.val[1] ^= y0.binary_part.val[1];
	x0.binary_part.val[2] ^= y0.binary_part.val[2];
	x0.binary_part.val[3] ^= y0.binary_part.val[3];
	return x0.float_part;
}

//------------------------------------------------------------------------------
// Float64x2 floating point classify
//------------------------------------------------------------------------------

/** @brief Returns true if x is negative */
static inline bool Float64x4_signbit(const Float64x4 x) {
	return Float64_signbit(x.val[0]);
}
/** @brief Returns true if x is finite */
static inline bool Float64x4_isfinite(const Float64x4 x) {
	return Float64_isfinite(x.val[0]);
}
/** @brief Returns true if x is +-infinity */
static inline bool Float64x4_isinf(const Float64x4 x) {
	return Float64_isinf(x.val[0]);
}
/** @brief Returns true if x is any kind of NaN */
static inline bool Float64x4_isnan(const Float64x4 x) {
	return Float64_isnan(x.val[0]);
}
/** @brief Returns true if x is normal */
static inline bool Float64x4_isnormal(const Float64x4 x) {
	return (
		Float64_isnormal(x.val[0]) && Float64_isnormal(x.val[1]) &&
		Float64_isnormal(x.val[2]) && Float64_isnormal(x.val[3])
	);
}
/** @brief Returns true if x and y are unordered */
static inline bool Float64x4_isunordered(const Float64x4 x, const Float64x4 y) {
	return Float64_isunordered(x.val[0], y.val[0]);
}
static inline int Float64x4_fpclassify(const Float64x4 x) {
	return
		Float64x4_isinf(x)             ? FP_INFINITE :
		Float64x4_isnan(x)             ? FP_NAN      :
		Float64x4_cmpeq_zero(x)        ? FP_ZERO     :
		Float64x4_isnormal(x)          ? FP_NORMAL   :
		FP_SUBNORMAL;
}

//------------------------------------------------------------------------------
// Float64x4 max/min functions
//------------------------------------------------------------------------------

static inline Float64x4 Float64x4_max(const Float64x4 x, const Float64x4 y) {
	return Float64x4_cmpge(x, y) ? x : y;
}

static inline Float64x4 Float64x4_min(const Float64x4 x, const Float64x4 y) {
	return Float64x4_cmplt(x, y) ? x : y;
}

//------------------------------------------------------------------------------
// Float64x4 math.h comparison functions
//------------------------------------------------------------------------------

static inline bool Float64x4_isgreater(const Float64x4 x, const Float64x4 y) {
	return Float64x4_cmpgt(x, y);
}
static inline bool Float64x4_isgreaterequal(const Float64x4 x, const Float64x4 y) {
	return Float64x4_cmpge(x, y);
}
static inline bool Float64x4_isless(const Float64x4 x, const Float64x4 y) {
	return Float64x4_cmplt(x, y);
}
static inline bool Float64x4_islessequal(const Float64x4 x, const Float64x4 y) {
	return Float64x4_cmple(x, y);
}
static inline bool Float64x4_islessgreater(const Float64x4 x, const Float64x4 y) {
	return Float64x4_cmplt(x, y) || Float64x4_cmpgt(x, y);
}

//------------------------------------------------------------------------------
// Float64x4 rounding functions
//------------------------------------------------------------------------------
	
/** 
 * @author Taken from libQD which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
static inline Float64x4 Float64x4_trunc(const Float64x4 x) {
	Float64x4 ret = {{trunc(x.val[0]), 0.0, 0.0, 0.0}};
	if (ret.val[0] == x.val[0]) {
		ret.val[1] = trunc(x.val[1]);
		if (ret.val[1] == x.val[1]) {
			ret.val[2] = trunc(x.val[2]);

			if (ret.val[2] == x.val[2]) {
				ret.val[3] = trunc(x.val[3]);
			}
		}
		Float64x4_renorm(&ret);
		return ret;
	}
	return ret;
}

/**
 * @brief qd_real/fortran compatibility. Calls Float64x4_trunc(x)
 */
static inline Float64x4 Float64x4_aint(const Float64x4 x) {
	return Float64x4_trunc(x);
}

/** 
 * @author Taken from libQD which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
static inline Float64x4 Float64x4_floor(const Float64x4 x) {
	Float64x4 ret = {{floor(x.val[0]), 0.0, 0.0, 0.0}};
	if (ret.val[0] == x.val[0]) {
		ret.val[1] = floor(x.val[1]);
		
		if (ret.val[1] == x.val[1]) {
			ret.val[2] = floor(x.val[2]);

			if (ret.val[2] == x.val[2]) {
				ret.val[3] = floor(x.val[3]);
			}
		}
		Float64x4_renorm(&ret);
		return ret;
	}
	return ret;
}
static inline Float64x4 Float64x4_ceil(const Float64x4 x) {
	Float64x4 ret = {{ceil(x.val[0]), 0.0, 0.0, 0.0}};
	if (ret.val[0] == x.val[0]) {
		ret.val[1] = ceil(x.val[1]);
		
		if (ret.val[1] == x.val[1]) {
			ret.val[2] = ceil(x.val[2]);

			if (ret.val[2] == x.val[2]) {
				ret.val[3] = ceil(x.val[3]);
			}
		}
		Float64x4_renorm(&ret);
		return ret;
	}
	return ret;
}

/** 
 * @author Taken from libQD which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
static inline Float64x4 Float64x4_round(const Float64x4 x) {
	Float64x4 ret = {{round(x.val[0]), 0.0, 0.0, 0.0}};
	if (ret.val[0] == x.val[0]) {
		/* First double is already an integer. */
		ret.val[1] = round(x.val[1]);

		if (ret.val[1] == x.val[1]) {
			/* Second double is already an integer. */
			ret.val[2] = round(x.val[2]);
			
			if (ret.val[2] == x.val[2]) {
				/* Third double is already an integer. */
				ret.val[3] = round(x.val[3]);
			} else {
				if (fabs(ret.val[2] - x.val[2]) == 0.5 && x.val[3] < 0.0) {
					ret.val[2] -= 1.0;
				}
			}
		} else {
			if (fabs(ret.val[1] - x.val[1]) == 0.5 && x.val[2] < 0.0) {
				ret.val[1] -= 1.0;
			}
		}

	} else {
		/* First double is not an integer. */
		if (fabs(ret.val[0] - x.val[0]) == 0.5 && x.val[1] < 0.0) {
			ret.val[0] -= 1.0;
		}
	}
	Float64x4_renorm(&ret);
	return ret;
}

/**
 * @brief qd_real/fortran compatibility. Calls Float64x4_round(x)
 */
static inline Float64x4 Float64x4_nint(const Float64x4 x) {
	return Float64x4_round(x);
}

static inline Float64x4 Float64x4_rint(const Float64x4 x) {
	switch (fegetround()) {
		default:
		case FE_TOWARDZERO:
			return Float64x4_trunc(x);
		case FE_DOWNWARD:
			return Float64x4_floor(x);
		case FE_UPWARD:
			return Float64x4_ceil(x);
		case FE_TONEAREST:
			return Float64x4_round(x);
	}
}
static inline long Float64x4_lround(const Float64x4 x) {
	Float64x4 ret = Float64x4_round(x);
	return (long)ret.val[0] + (long)ret.val[1];
}
static inline long Float64x4_lrint(const Float64x4 x) {
	Float64x4 ret = Float64x4_rint(x);
	return (long)ret.val[0] + (long)ret.val[1];
}
static inline long long Float64x4_llround(const Float64x4 x) {
	Float64x4 ret = Float64x4_round(x);
	return (long long)ret.val[0] + (long long)ret.val[1] + (long long)ret.val[2];
}
static inline long long Float64x4_llrint(const Float64x4 x) {
	Float64x4 ret = Float64x4_rint(x);
	return (long long)ret.val[0] + (long long)ret.val[1] + (long long)ret.val[2];
}

//------------------------------------------------------------------------------
// Float64x4 math.h functions
//------------------------------------------------------------------------------

static inline Float64x4 Float64x4_fabs(const Float64x4 x) {
	return (
		Float64x4_cmplt_zero(x)
	) ? Float64x4_negate(x) : x;
}

static inline Float64x4 Float64x4_fdim(const Float64x4 x, const Float64x4 y) {
	return (
		Float64x4_cmple(x, y)
	) ? Float64x4_sub(x, y) : Float64x4_set_zero();
}

static inline Float64x4 Float64x4_copysign(const Float64x4 x, const Float64x4 y) {
	return (
		Float64x4_cmplt_zero(x) != Float64x4_cmplt_zero(y)
	) ? Float64x4_negate(x) : x;
}

static inline Float64x4 Float64x4_sqrt(const Float64x4 x) {
	if (Float64x4_cmpeq_zero(x)) {
		return x;
	}
	Float64x2 x_temp = {x.val[0], x.val[1]};
	Float64x2 guess = Float64x2_sqrt(x_temp);
	return Float64x4_mul_power2_dx4_d(Float64x4_add_dx2_dx4(
		guess, Float64x4_div_dx4_dx2(x, guess)
	), 0.5);
}

static inline Float64x4 Float64x4_cbrt(const Float64x4 x) {
	if (Float64x4_cmpeq_zero(x)) {
		return x;
	}
	Float64x2 x_temp = {x.val[0], x.val[1]};
	Float64x2 guess = Float64x2_cbrt(x_temp);
	return Float64x4_div_dx4_d(Float64x4_add_dx2_dx4(
			Float64x2_mul_power2_d_dx2(2.0, guess),
			Float64x4_div(x, Float64x4_square_dx2(guess))
	), 3.0);
}

//------------------------------------------------------------------------------
// Float64x4 Integer and Remainder
//------------------------------------------------------------------------------

/**
* @brief returns the fraction part of a Float64x4 value. int_part may be NULL
*/
static inline Float64x4 Float64x4_modf(const Float64x4 x, Float64x4* const int_part) {
	Float64x4 trunc_part = Float64x4_trunc(x);
	if (int_part != NULL) {
		*int_part = trunc_part;
	}
	return Float64x4_sub(x, trunc_part);
}

static inline Float64x4 Float64x4_fmod(const Float64x4 x, const Float64x4 y) {
	Float64x4 trunc_part = Float64x4_trunc(Float64x4_div(x, y));
	return Float64x4_sub(x, Float64x4_mul(y, trunc_part));
}

static inline Float64x4 Float64x4_remainder(const Float64x4 x, const Float64x4 y) {
	Float64x4 round_part = Float64x4_round(Float64x4_div(x, y));
	return Float64x4_sub(x, Float64x4_mul(y, round_part));
}
static inline Float64x4 Float64x4_remquo(const Float64x4 x, const Float64x4 y, int* const quo) {
	Float64x4 q = Float64x4_round(Float64x4_div(x, y));
	Float64x4 r = Float64x4_sub(x, Float64x4_mul(y, q));
	*quo = (int)(q.val[0] + q.val[1]);
	return r;
}

//------------------------------------------------------------------------------
// Float64x2 Float Exponents
//------------------------------------------------------------------------------

/**
 * @brief Extracts the exponent of a Float64x4 value to compute the
 * binary logarithm.
 */
static inline int Float64x4_ilogb(const Float64x4 x) {
	return ilogb(x.val[0] + (x.val[1] + (x.val[2] + x.val[3])));
}
/**
 * @brief Returns a normalized Float64x4 value and the exponent in
 * the form [0.0, 1.0) * 2^expon
 */
static inline Float64x4 Float64x4_frexp(const Float64x4 x, int* const expon) {
	Float64x4 ret;
	*expon = ilogb(x.val[0] + (x.val[1] + (x.val[2] + x.val[3]))) + 1;
	ret.val[0] = ldexp(x.val[0], -(*expon));
	ret.val[1] = ldexp(x.val[1], -(*expon));
	ret.val[2] = ldexp(x.val[2], -(*expon));
	ret.val[3] = ldexp(x.val[3], -(*expon));
	return ret;
}
/**
 * @brief Multiplies a Float64x4 value by 2^expon
 */
static inline Float64x4 Float64x4_ldexp(const Float64x4 x, const int expon) {
	Float64x4 ret;
	ret.val[0] = ldexp(x.val[0], expon);
	ret.val[1] = Float64_isfinite(x.val[0]) ? ldexp(x.val[1], expon) : x.val[0];
	ret.val[2] = Float64_isfinite(x.val[0]) ? ldexp(x.val[2], expon) : x.val[0];
	ret.val[3] = Float64_isfinite(x.val[0]) ? ldexp(x.val[3], expon) : x.val[0];
	return ret;
}
/**
 * @brief Multiplies a Float64x4 value by FLT_RADIX^expon
 */
static inline Float64x4 Float64x4_scalbn(const Float64x4 x, const int expon) {
	Float64x4 ret;
	ret.val[0] = scalbn(x.val[0], expon);
	ret.val[1] = Float64_isfinite(x.val[0]) ? scalbn(x.val[1], expon) : x.val[0];
	ret.val[2] = Float64_isfinite(x.val[0]) ? scalbn(x.val[2], expon) : x.val[0];
	ret.val[3] = Float64_isfinite(x.val[0]) ? scalbn(x.val[3], expon) : x.val[0];
	return ret;
}
/**
 * @brief Multiplies a Float64x4 value by FLT_RADIX^expon
 */
static inline Float64x4 Float64x4_scalbln(const Float64x4 x, const long expon) {
	Float64x4 ret;
	ret.val[0] = scalbln(x.val[0], expon);
	ret.val[1] = Float64_isfinite(x.val[0]) ? scalbln(x.val[1], expon) : x.val[0];
	ret.val[2] = Float64_isfinite(x.val[0]) ? scalbln(x.val[2], expon) : x.val[0];
	ret.val[3] = Float64_isfinite(x.val[0]) ? scalbln(x.val[3], expon) : x.val[0];
	return ret;
}

//------------------------------------------------------------------------------
// Float64x4 exponents and logarithms
//------------------------------------------------------------------------------

Float64x4 Float64x4_exp(Float64x4 x);
Float64x4 Float64x4_expm1(Float64x4 x);
static inline Float64x4 Float64x4_exp2(const Float64x4 x) {
	const Float64x4 mult_val = FLOAT64X4_LN2;
	return Float64x4_exp(Float64x4_mul(x, mult_val));
}
static inline Float64x4 Float64x4_exp10(const Float64x4 x) {
	const Float64x4 mult_val = FLOAT64X4_LN10;
	return Float64x4_exp(Float64x4_mul(x, mult_val));
}

Float64x4 Float64x4_log(Float64x4 x);
Float64x4 Float64x4_log1p(Float64x4 x);
static inline Float64x4 Float64x4_log2(const Float64x4 x) {
	const Float64x4 mult_val = FLOAT64X4_LOG2E;
	return Float64x4_mul(Float64x4_log(x), mult_val);
}
static inline Float64x4 Float64x4_log10(const Float64x4 x) {
	const Float64x4 mult_val = FLOAT64X4_LOG10E;
	return Float64x4_mul(Float64x4_log(x), mult_val);
}

static inline Float64x4 Float64x4_pow(const Float64x4 x, const Float64x4 y) {
	return Float64x4_cmpeq_zero(x) ? (
		Float64x4_cmpeq_zero(y) ? Float64x4_set_d(1.0) : Float64x4_set_d(0.0)
	) : Float64x4_exp(Float64x4_mul(Float64x4_log(x), y));	
}
static inline Float64x4 Float64x4_pow_dx4_d(const Float64x4 x, const fp64 y) {
	return Float64x4_cmpeq_zero(x) ? (
		(y == 0.0) ? Float64x4_set_d(1.0) : Float64x4_set_d(0.0)
	) : Float64x4_exp(Float64x4_mul_dx4_d(Float64x4_log(x), y));
}

//------------------------------------------------------------------------------
// Float64x4 trigonometry
//------------------------------------------------------------------------------

Float64x4 Float64x4_sin(Float64x4 x);
Float64x4 Float64x4_cos(Float64x4 x);
void Float64x4_sincos(Float64x4 x, Float64x4* LDF_restrict p_sin, Float64x4* LDF_restrict p_cos);
Float64x4 Float64x4_tan(Float64x4 x);
Float64x4 Float64x4_asin(Float64x4 x);
Float64x4 Float64x4_acos(Float64x4 x);
Float64x4 Float64x4_atan(Float64x4 x);
Float64x4 Float64x4_atan2(Float64x4 y, Float64x4 x);

Float64x4 Float64x4_sinh(Float64x4 x);
Float64x4 Float64x4_cosh(Float64x4 x);
Float64x4 Float64x4_tanh(Float64x4 x);
void Float64x4_sinhcosh(Float64x4 x, Float64x4* LDF_restrict p_sinh, Float64x4* LDF_restrict p_cosh);

Float64x4 Float64x4_asinh(Float64x4 x);
Float64x4 Float64x4_acosh(Float64x4 x);
Float64x4 Float64x4_atanh(Float64x4 x);

#ifdef __cplusplus
	}
#endif

#ifdef __cplusplus
	#include "Float64x4.hpp"
#endif

#endif /* FLOAT64X4_H */ 
