/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/
#ifndef FLOAT64X2_AVX_H
#define FLOAT64X2_AVX_H

/**
 * @brief Double-Float64 AVX Dekker Float implementation.
 * Source: Creel "Double it Like Dekker" on YouTube.
 *
 * @note Requires AVX or later.
 * @warning -Ofast may break this library. -O3 compiles okay on gcc and clang.
 */

#include "Float64x2_def.h"

#include <stdint.h>

#if (!defined(__AVX__) && defined(__GNUC__))
	#error "__AVX__ is not enabled in your compiler. Try -mavx"
#endif

#include <immintrin.h>

#if defined(__GNUC__) && false
	#define DOUBLE_FLOAT64_AVX_ATTRIBUTE(flags) \
	__attribute__((flags))
#else
	#define DOUBLE_FLOAT64_AVX_ATTRIBUTE(...)
#endif

#if defined(__clang__) && defined(__FAST_MATH__)
	#warning "-ffast-math may break this library, adding -fno-associative-math should fix this."
#endif

#ifdef __cplusplus
	extern "C" {
#endif

//------------------------------------------------------------------------------
// __m256d functions
//------------------------------------------------------------------------------

#ifndef _mm256_fabs_pd
/**
 * @remarks _mm256_andnot_pd cannot be used because 0x8000000000000000 gets
 * converted from -0.0 to 0.0 on -Ofast
 */
inline __m256d _mm256_fabs_pd(__m256d x) {
	return _mm256_and_pd(
		x,
		_mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x7FFFFFFFFFFFFFFF))
	);
}
#endif

#ifndef _mm256_negate_pd
inline __m256d _mm256_negate_pd(__m256d x) {
	// return _mm256_xor_pd(
	// 	x,
	// 	_mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x8000000000000000))
	// );
	return _mm256_mul_pd(x, _mm256_set1_pd(-1.0));
}
#endif

#ifndef _mm256_trunc_pd
/**
 * @brief _mm256_trunc_pd replacement function.
 */
inline __m256d _mm256_trunc_pd(__m256d x) {
	return _mm256_round_pd(x, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
}
#endif

#ifndef _mm256_cbrt_pd
#include <math.h>
/**
 * @brief _mm256_cbrt_pd replacement function. May be slow/inefficient.
 */
inline __m256d _mm256_cbrt_pd(__m256d x) {
	double val[4];
	_mm256_storeu_pd(val, x);
	val[0] = cbrt(val[0]);
	val[1] = cbrt(val[1]);
	val[2] = cbrt(val[2]);
	val[3] = cbrt(val[3]);
	return _mm256_loadu_pd(val);
}
#endif

//------------------------------------------------------------------------------
// __m256dx2 struct
//------------------------------------------------------------------------------

/**
 * @brief Holds four Double-Float64 dekker floats
 */
typedef struct __m256dx2 {
	__m256d hi;
	__m256d lo;
} __m256dx2;

//------------------------------------------------------------------------------
// __m256dx2 basic arithmetic
//------------------------------------------------------------------------------

inline __m256dx2 _mm256x2_negate_pdx2(__m256dx2 x) {
	x.hi = _mm256_xor_pd(
		x.hi,
		_mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x8000000000000000))
	);
	x.lo = _mm256_xor_pd(
		x.lo,
		_mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x8000000000000000))
	);
	return x;
}

DOUBLE_FLOAT64_AVX_ATTRIBUTE(optimize("-fno-associative"))
inline __m256dx2 _mm256x2_add_pdx2(__m256dx2 x, __m256dx2 y) {
	// __m256d r_hi = _mm256_add_pd(x.hi, y.hi);
	// /* if (fabs(x.hi) < fabs(y.hi)) */ {
	// 	const __m256d cmp_result = _mm256_cmp_pd(
	// 		_mm256_fabs_pd(x.hi), _mm256_fabs_pd(y.hi),
	// 	_CMP_LT_OQ);
		
	// 	// Swaps x and y
	// 	__m256d temp_hi = _mm256_blendv_pd(x.hi, y.hi, cmp_result);
	// 	y.hi = _mm256_blendv_pd(y.hi, x.hi, cmp_result);
	// 	x.hi = temp_hi;
	// 	__m256d temp_lo = _mm256_blendv_pd(x.lo, y.lo, cmp_result);
	// 	y.lo = _mm256_blendv_pd(y.lo, x.lo, cmp_result);
	// 	x.lo = temp_lo;
	// }
	// __m256d r_lo = _mm256_add_pd(_mm256_add_pd(
	// 	_mm256_add_pd(_mm256_sub_pd(x.hi, r_hi), y.hi),
	// y.lo), x.lo);

	__m256d r_hi = _mm256_add_pd(x.hi, y.hi);

	__m256d rx_lo = _mm256_add_pd(_mm256_add_pd(
		_mm256_add_pd(_mm256_sub_pd(x.hi, r_hi), y.hi),
	y.lo), x.lo);
	__m256d ry_lo = _mm256_add_pd(_mm256_add_pd(
		_mm256_add_pd(_mm256_sub_pd(y.hi, r_hi), x.hi),
	x.lo), y.lo);

	const __m256d cmp_result = _mm256_cmp_pd(
	 		_mm256_fabs_pd(x.hi), _mm256_fabs_pd(y.hi),
	_CMP_LE_OQ);
	__m256d r_lo = _mm256_blendv_pd(rx_lo, ry_lo, cmp_result);

	__m256dx2 c;
	c.hi = _mm256_add_pd(r_hi, r_lo);
	c.lo = _mm256_add_pd(_mm256_sub_pd(r_hi, c.hi), r_lo);
	return c;
}

DOUBLE_FLOAT64_AVX_ATTRIBUTE(optimize("-fno-associative"))
inline __m256dx2 _mm256x2_sub_pdx2(__m256dx2 x, __m256dx2 y) {
	// y.hi = _mm256_negate_pd(y.hi);
	// y.lo = _mm256_negate_pd(y.lo);
	// return _mm256x2_add_pdx2(x, y);

	// __m256d r_hi = _mm256_sub_pd(x.hi, y.hi);
	// /* if (fabs(x.hi) < fabs(y.hi)) */ {
	// 	const __m256d cmp_result = _mm256_cmp_pd(
	// 		_mm256_fabs_pd(x.hi), _mm256_fabs_pd(y.hi),
	// 	_CMP_LT_OQ);
		
	// 	// Swaps x and y
	// 	__m256d temp_hi = _mm256_blendv_pd(x.hi, y.hi, cmp_result);
	// 	y.hi = _mm256_blendv_pd(y.hi, x.hi, cmp_result);
	// 	x.hi = temp_hi;
	// 	__m256d temp_lo = _mm256_blendv_pd(x.lo, y.lo, cmp_result);
	// 	y.lo = _mm256_blendv_pd(y.lo, x.lo, cmp_result);
	// 	x.lo = temp_lo;
	// }
	// __m256d r_lo = _mm256_add_pd(_mm256_sub_pd(
	// 	_mm256_sub_pd(_mm256_sub_pd(x.hi, r_hi), y.hi),
	// y.lo), x.lo);
	
	__m256d r_hi = _mm256_sub_pd(x.hi, y.hi);

	__m256d rx_lo = _mm256_add_pd(_mm256_sub_pd(
		_mm256_sub_pd(_mm256_sub_pd(x.hi, r_hi), y.hi),
	y.lo), x.lo);

	y.hi = _mm256_negate_pd(y.hi);
	__m256d ry_lo = _mm256_sub_pd(_mm256_add_pd(
		_mm256_add_pd(_mm256_sub_pd(/* negative */ y.hi, r_hi), x.hi),
	x.lo), y.lo);

	const __m256d cmp_result = _mm256_cmp_pd(
	 		_mm256_fabs_pd(x.hi), _mm256_fabs_pd(y.hi),
	_CMP_LE_OQ);
	__m256d r_lo = _mm256_blendv_pd(rx_lo, ry_lo, cmp_result);

	__m256dx2 c;
	c.hi = _mm256_add_pd(r_hi, r_lo);
	c.lo = _mm256_add_pd(_mm256_sub_pd(r_hi, c.hi), r_lo);
	return c;
}

DOUBLE_FLOAT64_AVX_ATTRIBUTE(optimize("-fno-associative"))
inline __m256dx2 _mm256x2_dekker_split_pd(__m256d x) {
	// (2^ceil(53 / 2) + 1)
	const __m256d dekker_scale = _mm256_set1_pd(134217729.0); 
	__m256d p = _mm256_mul_pd(x, dekker_scale);
	__m256dx2 r;
	r.hi = _mm256_add_pd(_mm256_sub_pd(x, p), p);
	r.lo = _mm256_sub_pd(x, r.hi);
	return r;
}

// DOUBLE_FLOAT64_AVX_ATTRIBUTE(optimize("-fno-associative"))
// inline __m256dx2 _mm256x2_dekker_split_pd(__m256d x) {
// 	__m256dx2 r;
// 	r.hi = _mm256_andnot_pd(
// 		x,
// 		_mm256_castsi256_pd(_mm256_set1_epi64x(0x3FFFFFF))
// 	);
// 	r.lo = x - r.hi;
// 	return r;
// }

DOUBLE_FLOAT64_AVX_ATTRIBUTE(optimize("-fno-associative"))
inline __m256dx2 _mm256x2_dekker_mul12_pd(__m256d x, __m256d y) {
	__m256dx2 a = _mm256x2_dekker_split_pd(x);
	__m256dx2 b = _mm256x2_dekker_split_pd(y);
	__m256d p = _mm256_mul_pd(a.hi, b.hi);
	__m256d q = _mm256_add_pd(
		_mm256_mul_pd(a.hi, b.lo), _mm256_mul_pd(a.lo, b.hi)
	);

	__m256dx2 r;
	r.hi = _mm256_add_pd(p, q);
	r.lo = _mm256_add_pd(
		_mm256_add_pd(_mm256_sub_pd(p, r.hi), q),
		_mm256_mul_pd(a.lo, b.lo)
	);
	return r;
}

DOUBLE_FLOAT64_AVX_ATTRIBUTE(optimize("-fno-associative"))
inline __m256dx2 _mm256x2_mul_pdx2(__m256dx2 x, __m256dx2 y) {
	__m256dx2 t = _mm256x2_dekker_mul12_pd(x.hi, y.hi);
	__m256d c = _mm256_add_pd(_mm256_add_pd(
		_mm256_mul_pd(x.hi, y.lo), _mm256_mul_pd(x.lo, y.hi)
	), t.lo);

	__m256dx2 r;
	r.hi = _mm256_add_pd(t.hi, c);
	r.lo = _mm256_add_pd(_mm256_sub_pd(t.hi, r.hi), c);
	return r;
}

DOUBLE_FLOAT64_AVX_ATTRIBUTE(optimize("-fno-associative"))
inline __m256dx2 _mm256x2_div_pdx2(__m256dx2 x, __m256dx2 y) {
	__m256d u = _mm256_div_pd(x.hi, y.hi);
	__m256dx2 t = _mm256x2_dekker_mul12_pd(u, y.hi);
	__m256d l = _mm256_div_pd(_mm256_sub_pd(
		_mm256_add_pd(_mm256_sub_pd(_mm256_sub_pd(x.hi, t.hi), t.lo), x.lo),
		_mm256_mul_pd(u, y.lo)
	), y.hi);

	__m256dx2 r;
	r.hi = _mm256_add_pd(u, l);
	r.lo = _mm256_add_pd(_mm256_sub_pd(u, r.hi), l);
	return r;
}

/**
 * @brief returns 0 on division by 0
 */
DOUBLE_FLOAT64_AVX_ATTRIBUTE(optimize("-fno-associative"))
inline __m256dx2 _mm256x2_div_zero_pdx2(__m256dx2 x, __m256dx2 y) {
	__m256d u = _mm256_div_pd(x.hi, y.hi);
	__m256dx2 t = _mm256x2_dekker_mul12_pd(u, y.hi);
	__m256d l = _mm256_div_pd(_mm256_sub_pd(
		_mm256_add_pd(_mm256_sub_pd(_mm256_sub_pd(x.hi, t.hi), t.lo), x.lo),
		_mm256_mul_pd(u, y.lo)
	), y.hi);

	__m256dx2 r;
	r.hi = _mm256_add_pd(u, l);
	r.lo = _mm256_add_pd(_mm256_sub_pd(u, r.hi), l);

	__m256d cmp_zero = _mm256_cmp_pd(y.hi, _mm256_setzero_pd(), _CMP_EQ_OS);
	r.hi = _mm256_andnot_pd(r.hi, cmp_zero);
	r.lo = _mm256_andnot_pd(r.lo, cmp_zero);
	return r;
}

DOUBLE_FLOAT64_AVX_ATTRIBUTE(optimize("-fno-associative"))
inline __m256dx2 _mm256x2_dekker_square12_pd(__m256d x) {
	__m256dx2 a = _mm256x2_dekker_split_pd(x);
	__m256d p = _mm256_mul_pd(a.hi, a.hi);
	__m256d q = _mm256_mul_pd(
		_mm256_set1_pd(2.0), _mm256_mul_pd(a.hi, a.lo)
	);

	__m256dx2 r;
	r.hi = _mm256_add_pd(p, q);
	r.lo = _mm256_add_pd(
		_mm256_add_pd(_mm256_sub_pd(p, r.hi), q),
		_mm256_mul_pd(a.lo, a.lo)
	);
	return r;
}

DOUBLE_FLOAT64_AVX_ATTRIBUTE(optimize("-fno-associative"))
inline __m256dx2 _mm256x2_square_pdx2(__m256dx2 x) {
	__m256dx2 t = _mm256x2_dekker_square12_pd(x.hi);
	__m256d c = _mm256_add_pd(
		_mm256_mul_pd(_mm256_set1_pd(2.0), _mm256_mul_pd(x.hi, x.lo)), t.lo
	);

	__m256dx2 r;
	r.hi = _mm256_add_pd(t.hi, c);
	r.lo = _mm256_add_pd(_mm256_sub_pd(t.hi, r.hi), c);
	return r;
}

DOUBLE_FLOAT64_AVX_ATTRIBUTE(optimize("-fno-associative"))
inline __m256dx2 _mm256x2_recip_pdx2(__m256dx2 y) {
	__m256d u = _mm256_div_pd(_mm256_set1_pd(1.0), y.hi);
	__m256dx2 t = _mm256x2_dekker_mul12_pd(u, y.hi);
	__m256d l = _mm256_div_pd(_mm256_sub_pd(
		_mm256_sub_pd(_mm256_sub_pd(_mm256_set1_pd(1.0), t.hi), t.lo),
		_mm256_mul_pd(u, y.lo)
	), y.hi);

	__m256dx2 r;
	r.hi = _mm256_add_pd(u, l);
	r.lo = _mm256_add_pd(_mm256_sub_pd(u, r.hi), l);
	return r;
}

//------------------------------------------------------------------------------
// __m256dx2 optimized arithmetic
//------------------------------------------------------------------------------

DOUBLE_FLOAT64_AVX_ATTRIBUTE(optimize("-fno-associative"))
inline __m256dx2 _mm256x2_add_pdx2_pd(__m256dx2 x, __m256d y) {
	__m256d r_hi = _mm256_add_pd(x.hi, y);

	__m256d rx_lo = _mm256_add_pd(
		_mm256_add_pd(_mm256_sub_pd(x.hi, r_hi), y), x.lo
	);
	__m256d ry_lo = _mm256_add_pd(
		_mm256_add_pd(_mm256_sub_pd(y, r_hi), x.hi),
	x.lo);

	const __m256d cmp_result = _mm256_cmp_pd(
	 		_mm256_fabs_pd(x.hi), _mm256_fabs_pd(y),
	_CMP_LE_OQ);
	__m256d r_lo = _mm256_blendv_pd(rx_lo, ry_lo, cmp_result);

	__m256dx2 c;
	c.hi = _mm256_add_pd(r_hi, r_lo);
	c.lo = _mm256_add_pd(_mm256_sub_pd(r_hi, c.hi), r_lo);
	return c;
}

DOUBLE_FLOAT64_AVX_ATTRIBUTE(optimize("-fno-associative"))
inline __m256dx2 _mm256x2_add_pd_pdx2(__m256d x, __m256dx2 y) {
	__m256d r_hi = _mm256_add_pd(x, y.hi);

	__m256d rx_lo = _mm256_add_pd(
		_mm256_add_pd(_mm256_sub_pd(x, r_hi), y.hi),
	y.lo);
	__m256d ry_lo = _mm256_add_pd(
		_mm256_add_pd(_mm256_sub_pd(y.hi, r_hi), x), y.lo
	);

	const __m256d cmp_result = _mm256_cmp_pd(
	 		_mm256_fabs_pd(x), _mm256_fabs_pd(y.hi),
	_CMP_LE_OQ);
	__m256d r_lo = _mm256_blendv_pd(rx_lo, ry_lo, cmp_result);

	__m256dx2 c;
	c.hi = _mm256_add_pd(r_hi, r_lo);
	c.lo = _mm256_add_pd(_mm256_sub_pd(r_hi, c.hi), r_lo);
	return c;
}

/**
 * @brief Adds two __m256d values with the result stored as a __m256dx2
 */
DOUBLE_FLOAT64_AVX_ATTRIBUTE(optimize("-fno-associative"))
inline __m256dx2 _mm256x2_add_pd_pd(__m256d x, __m256d y) {
	__m256d r_hi = _mm256_add_pd(x, y);

	__m256d rx_lo = _mm256_add_pd(_mm256_sub_pd(x, r_hi), y);
	__m256d ry_lo = _mm256_add_pd(_mm256_sub_pd(y, r_hi), x);

	const __m256d cmp_result = _mm256_cmp_pd(
	 		_mm256_fabs_pd(x), _mm256_fabs_pd(y),
	_CMP_LE_OQ);
	__m256d r_lo = _mm256_blendv_pd(rx_lo, ry_lo, cmp_result);

	__m256dx2 c;
	c.hi = _mm256_add_pd(r_hi, r_lo);
	c.lo = _mm256_add_pd(_mm256_sub_pd(r_hi, c.hi), r_lo);
	return c;
}

DOUBLE_FLOAT64_AVX_ATTRIBUTE(optimize("-fno-associative"))
inline __m256dx2 _mm256x2_sub_pdx2_pd(__m256dx2 x, __m256d y) {
	__m256d r_hi = _mm256_sub_pd(x.hi, y);

	__m256d rx_lo = _mm256_add_pd(
		_mm256_sub_pd(_mm256_sub_pd(x.hi, r_hi), y), x.lo
	);

	y = _mm256_negate_pd(y);
	__m256d ry_lo = _mm256_add_pd(
		_mm256_add_pd(_mm256_sub_pd(/* negative */ y, r_hi), x.hi), x.lo
	);

	const __m256d cmp_result = _mm256_cmp_pd(
	 		_mm256_fabs_pd(x.hi), _mm256_fabs_pd(y),
	_CMP_LE_OQ);
	__m256d r_lo = _mm256_blendv_pd(rx_lo, ry_lo, cmp_result);

	__m256dx2 c;
	c.hi = _mm256_add_pd(r_hi, r_lo);
	c.lo = _mm256_add_pd(_mm256_sub_pd(r_hi, c.hi), r_lo);
	return c;
}

DOUBLE_FLOAT64_AVX_ATTRIBUTE(optimize("-fno-associative"))
inline __m256dx2 _mm256x2_sub_pd_pdx2(__m256d x, __m256dx2 y) {
	__m256d r_hi = _mm256_sub_pd(x, y.hi);

	__m256d rx_lo = _mm256_sub_pd(
		_mm256_sub_pd(_mm256_sub_pd(x, r_hi), y.hi),
	y.lo);

	y.hi = _mm256_negate_pd(y.hi);
	__m256d ry_lo = _mm256_sub_pd(
		_mm256_add_pd(_mm256_sub_pd(/* negative */ y.hi, r_hi), x), y.lo
	);

	const __m256d cmp_result = _mm256_cmp_pd(
	 		_mm256_fabs_pd(x), _mm256_fabs_pd(y.hi),
	_CMP_LE_OQ);
	__m256d r_lo = _mm256_blendv_pd(rx_lo, ry_lo, cmp_result);

	__m256dx2 c;
	c.hi = _mm256_add_pd(r_hi, r_lo);
	c.lo = _mm256_add_pd(_mm256_sub_pd(r_hi, c.hi), r_lo);
	return c;
}

/**
 * @brief Subtracts two __m256d values with the result stored as a __m256dx2
 */
DOUBLE_FLOAT64_AVX_ATTRIBUTE(optimize("-fno-associative"))
inline __m256dx2 _mm256x2_sub_pd_pd(__m256d x, __m256d y) {
	__m256d r_hi = _mm256_sub_pd(x, y);

	__m256d rx_lo = _mm256_sub_pd(_mm256_sub_pd(x, r_hi), y);

	y = _mm256_negate_pd(y);
	__m256d ry_lo = _mm256_add_pd(_mm256_sub_pd(/* negative */ y, r_hi), x);

	const __m256d cmp_result = _mm256_cmp_pd(
	 		_mm256_fabs_pd(x), _mm256_fabs_pd(y),
	_CMP_LE_OQ);
	__m256d r_lo = _mm256_blendv_pd(rx_lo, ry_lo, cmp_result);

	__m256dx2 c;
	c.hi = _mm256_add_pd(r_hi, r_lo);
	c.lo = _mm256_add_pd(_mm256_sub_pd(r_hi, c.hi), r_lo);
	return c;
}

DOUBLE_FLOAT64_AVX_ATTRIBUTE(optimize("-fno-associative"))
inline __m256dx2 _mm256x2_mul_pdx2_pd(__m256dx2 x, __m256d y) {
	__m256dx2 t = _mm256x2_dekker_mul12_pd(x.hi, y);
	__m256d c = _mm256_add_pd(_mm256_mul_pd(x.lo, y), t.lo);

	__m256dx2 r;
	r.hi = _mm256_add_pd(t.hi, c);
	r.lo = _mm256_add_pd(_mm256_sub_pd(t.hi, r.hi), c);
	return r;
}

DOUBLE_FLOAT64_AVX_ATTRIBUTE(optimize("-fno-associative"))
inline __m256dx2 _mm256x2_mul_pd_pdx2(__m256d x, __m256dx2 y) {
	__m256dx2 t = _mm256x2_dekker_mul12_pd(x, y.hi);
	__m256d c = _mm256_add_pd(_mm256_mul_pd(x, y.lo), t.lo);

	__m256dx2 r;
	r.hi = _mm256_add_pd(t.hi, c);
	r.lo = _mm256_add_pd(_mm256_sub_pd(t.hi, r.hi), c);
	return r;
}

/**
 * @brief Multiplies two __m256d values with the result stored as a __m256dx2
 */
DOUBLE_FLOAT64_AVX_ATTRIBUTE(optimize("-fno-associative"))
inline __m256dx2 _mm256x2_mul_pd_pd(__m256d x, __m256d y) {
	return _mm256x2_dekker_mul12_pd(x, y);
}

DOUBLE_FLOAT64_AVX_ATTRIBUTE(optimize("-fno-associative"))
inline __m256dx2 _mm256x2_div_pdx2_pd(__m256dx2 x, __m256d y) {
	__m256d u = _mm256_div_pd(x.hi, y);
	__m256dx2 t = _mm256x2_dekker_mul12_pd(u, y);
	__m256d l = _mm256_div_pd(
		_mm256_add_pd(_mm256_sub_pd(_mm256_sub_pd(x.hi, t.hi), t.lo), x.lo), y
	);

	__m256dx2 r;
	r.hi = _mm256_add_pd(u, l);
	r.lo = _mm256_add_pd(_mm256_sub_pd(u, r.hi), l);
	return r;
}

DOUBLE_FLOAT64_AVX_ATTRIBUTE(optimize("-fno-associative"))
inline __m256dx2 _mm256x2_div_pd_pdx2(__m256d x, __m256dx2 y) {
	__m256d u = _mm256_div_pd(x, y.hi);
	__m256dx2 t = _mm256x2_dekker_mul12_pd(u, y.hi);
	__m256d l = _mm256_div_pd(_mm256_sub_pd(
		_mm256_sub_pd(_mm256_sub_pd(x, t.hi), t.lo),
		_mm256_mul_pd(u, y.lo)
	), y.hi);

	__m256dx2 r;
	r.hi = _mm256_add_pd(u, l);
	r.lo = _mm256_add_pd(_mm256_sub_pd(u, r.hi), l);
	return r;
}

/**
 * @brief Divides two __m256d values with the result stored as a __m256dx2
 */
DOUBLE_FLOAT64_AVX_ATTRIBUTE(optimize("-fno-associative"))
inline __m256dx2 _mm256x2_div_pd_pd(__m256d x, __m256d y) {
	__m256d u = _mm256_div_pd(x, y);
	__m256dx2 t = _mm256x2_dekker_mul12_pd(u, y);
	__m256d l = _mm256_div_pd(
		_mm256_sub_pd(_mm256_sub_pd(x, t.hi), t.lo), y
	);

	__m256dx2 r;
	r.hi = _mm256_add_pd(u, l);
	r.lo = _mm256_add_pd(_mm256_sub_pd(u, r.hi), l);
	return r;
}

/**
 * @brief Returns 0 on division by 0
 */
DOUBLE_FLOAT64_AVX_ATTRIBUTE(optimize("-fno-associative"))
inline __m256dx2 _mm256x2_div_zero_pdx2_pd(__m256dx2 x, __m256d y) {
	__m256d u = _mm256_div_pd(x.hi, y);
	__m256dx2 t = _mm256x2_dekker_mul12_pd(u, y);
	__m256d l = _mm256_div_pd(
		_mm256_add_pd(_mm256_sub_pd(_mm256_sub_pd(x.hi, t.hi), t.lo), x.lo), y
	);

	__m256dx2 r;
	r.hi = _mm256_add_pd(u, l);
	r.lo = _mm256_add_pd(_mm256_sub_pd(u, r.hi), l);

	__m256d cmp_zero = _mm256_cmp_pd(y, _mm256_setzero_pd(), _CMP_EQ_OS);
	r.hi = _mm256_andnot_pd(r.hi, cmp_zero);
	r.lo = _mm256_andnot_pd(r.lo, cmp_zero);
	return r;
}

/**
 * @brief Returns 0 on division by 0
 */
DOUBLE_FLOAT64_AVX_ATTRIBUTE(optimize("-fno-associative"))
inline __m256dx2 _mm256x2_div_zero_pd_pdx2(__m256d x, __m256dx2 y) {
	__m256d u = _mm256_div_pd(x, y.hi);
	__m256dx2 t = _mm256x2_dekker_mul12_pd(u, y.hi);
	__m256d l = _mm256_div_pd(_mm256_sub_pd(
		_mm256_sub_pd(_mm256_sub_pd(x, t.hi), t.lo),
		_mm256_mul_pd(u, y.lo)
	), y.hi);

	__m256dx2 r;
	r.hi = _mm256_add_pd(u, l);
	r.lo = _mm256_add_pd(_mm256_sub_pd(u, r.hi), l);

	__m256d cmp_zero = _mm256_cmp_pd(y.hi, _mm256_setzero_pd(), _CMP_EQ_OS);
	r.hi = _mm256_andnot_pd(r.hi, cmp_zero);
	r.lo = _mm256_andnot_pd(r.lo, cmp_zero);
	return r;
}


/**
 * @brief Returns 0 on division by 0. Divides two __m256d values with the
 * result stored as a __m256dx2
 */
DOUBLE_FLOAT64_AVX_ATTRIBUTE(optimize("-fno-associative"))
inline __m256dx2 _mm256x2_div_zero_pd_pd(__m256d x, __m256d y) {
	__m256d u = _mm256_div_pd(x, y);
	__m256dx2 t = _mm256x2_dekker_mul12_pd(u, y);
	__m256d l = _mm256_div_pd(
		_mm256_sub_pd(_mm256_sub_pd(x, t.hi), t.lo), y
	);

	__m256dx2 r;
	r.hi = _mm256_add_pd(u, l);
	r.lo = _mm256_add_pd(_mm256_sub_pd(u, r.hi), l);

	__m256d cmp_zero = _mm256_cmp_pd(y, _mm256_setzero_pd(), _CMP_EQ_OS);
	r.hi = _mm256_andnot_pd(r.hi, cmp_zero);
	r.lo = _mm256_andnot_pd(r.lo, cmp_zero);
	return r;
}

/**
 * @brief Squares a __m256d value with the result stored as a __m256dx2
 */
 
inline __m256dx2 _mm256x2_square_pd(__m256d x) {
	return _mm256x2_dekker_square12_pd(x);
}

/**
 * @brief Calculates the reciprocal of a __m256d value with the result stored
 * as a __m256dx2
 */
DOUBLE_FLOAT64_AVX_ATTRIBUTE(optimize("-fno-associative"))
inline __m256dx2 _mm256x2_recip_pd(__m256d y) {
	__m256d u = _mm256_div_pd(_mm256_set1_pd(1.0), y);
	__m256dx2 t = _mm256x2_dekker_mul12_pd(u, y);
	__m256d l = _mm256_div_pd(
		_mm256_sub_pd(_mm256_sub_pd(_mm256_set1_pd(1.0), t.hi), t.lo), y
	);

	__m256dx2 r;
	r.hi = _mm256_add_pd(u, l);
	r.lo = _mm256_add_pd(_mm256_sub_pd(u, r.hi), l);
	return r;
}

//------------------------------------------------------------------------------
// __m256dx2 specialized arithmetic
//------------------------------------------------------------------------------

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero
 */
inline __m256dx2 _mm256x2_mul_power2_pdx2_pd(__m256dx2 x, __m256d y) {
	x.hi = _mm256_mul_pd(x.hi, y);
	x.lo = _mm256_mul_pd(x.lo, y);
	return x;
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero
 */
inline __m256dx2 _mm256x2_mul_power2_pd_pdx2(__m256d x, __m256dx2 y) {
	y.hi = _mm256_mul_pd(x, y.hi);
	y.lo = _mm256_mul_pd(x, y.lo);
	return y;
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero.
 * The result is stored as a __m256dx2
 */
inline __m256dx2 _mm256x2_mul_power2_pd_pd(__m256d x, __m256d y) {
	__m256dx2 ret;
	ret.hi = _mm256_mul_pd(x, y);
	ret.lo = _mm256_setzero_pd();
	return ret;
}

//------------------------------------------------------------------------------
// __m256dx2 bitwise operations
//------------------------------------------------------------------------------

inline __m256dx2 _mm256x2_and_pdx2(__m256dx2 x, __m256dx2 y) {
	x.hi = _mm256_and_pd(x.hi, y.hi);
	x.lo = _mm256_and_pd(x.lo, y.lo);
	return x;
}

inline __m256dx2 _mm256x2_andnot_pdx2(__m256dx2 x, __m256dx2 y) {
	x.hi = _mm256_andnot_pd(x.hi, y.hi);
	x.lo = _mm256_andnot_pd(x.lo, y.lo);
	return x;
}

inline __m256dx2 _mm256x2_or_pdx2(__m256dx2 x, __m256dx2 y) {
	x.hi = _mm256_or_pd(x.hi, y.hi);
	x.lo = _mm256_or_pd(x.lo, y.lo);
	return x;
}

inline __m256dx2 _mm256x2_xor_pdx2(__m256dx2 x, __m256dx2 y) {
	x.hi = _mm256_xor_pd(x.hi, y.hi);
	x.lo = _mm256_xor_pd(x.lo, y.lo);
	return x;
}

//------------------------------------------------------------------------------
// __m256dx2 set1 functions
//------------------------------------------------------------------------------

inline __m256dx2 _mm256x2_setzero_pdx2(void) {
	__m256dx2 ret;
	ret.hi = _mm256_setzero_pd();
	ret.lo = _mm256_setzero_pd();
	return ret;
}

inline __m256dx2 _mm256x2_set1_pd_pd(double hi, double lo) {
	__m256dx2 ret;
	ret.hi = _mm256_set1_pd(hi);
	ret.lo = _mm256_set1_pd(lo);
	return ret;
}

inline __m256dx2 _mm256x2_set1_pd(double x) {
	__m256dx2 ret;
	ret.hi = _mm256_set1_pd(x);
	ret.lo = _mm256_setzero_pd();
	return ret;
}

inline __m256dx2 _mm256x2_set1_epi64x(long long x) {
	__m256dx2 ret;
	ret.hi = _mm256_castsi256_pd(_mm256_set1_epi64x(x));
	ret.lo = _mm256_castsi256_pd(_mm256_set1_epi64x(x));
	return ret;
}

//------------------------------------------------------------------------------
// __m256dx2 set functions
//------------------------------------------------------------------------------

inline __m256dx2 _mm256x2_set_pd_pd(
	double hi_3, double lo_3, double hi_2, double lo_2,
	double hi_1, double lo_1, double hi_0, double lo_0
) {
	__m256dx2 ret;
	ret.hi = _mm256_set_pd(hi_3, hi_2, hi_1, hi_0);
	ret.lo = _mm256_set_pd(lo_3, lo_2, lo_1, lo_0);
	return ret;
}

inline __m256dx2 _mm256x2_set_pd(
	double e3, double e2, double e1, double e0
) {
	__m256dx2 ret;
	ret.hi = _mm256_set_pd(e3, e2, e1, e0);
	ret.lo = _mm256_setzero_pd();
	return ret;
}

inline __m256dx2 _mm256x2_set_epi64x(
	long long hi_3, long long lo_3, long long hi_2, long long lo_2,
	long long hi_1, long long lo_1, long long hi_0, long long lo_0
) {
	__m256dx2 ret;
	ret.hi = _mm256_castsi256_pd(_mm256_set_epi64x(hi_3, hi_2, hi_1, hi_0));
	ret.lo = _mm256_castsi256_pd(_mm256_set_epi64x(lo_3, lo_2, lo_1, lo_0));
	return ret;
}

//------------------------------------------------------------------------------
// __m256dx2 setr (set reverse) functions
//------------------------------------------------------------------------------

inline __m256dx2 _mm256x2_setr_pd_pd(
	double hi_3, double lo_3, double hi_2, double lo_2,
	double hi_1, double lo_1, double hi_0, double lo_0
) {
	__m256dx2 ret;
	ret.hi = _mm256_setr_pd(hi_3, hi_2, hi_1, hi_0);
	ret.lo = _mm256_setr_pd(lo_3, lo_2, lo_1, lo_0);
	return ret;
}

inline __m256dx2 _mm256x2_setr_pd(
	double x3, double x2, double x1, double x0
) {
	__m256dx2 ret;
	ret.hi = _mm256_setr_pd(x3, x2, x1, x0);
	ret.lo = _mm256_setzero_pd();
	return ret;
}

inline __m256dx2 _mm256x2_setr_epi64x(
	long long hi_3, long long lo_3, long long hi_2, long long lo_2,
	long long hi_1, long long lo_1, long long hi_0, long long lo_0
) {
	__m256dx2 ret;
	ret.hi = _mm256_castsi256_pd(_mm256_setr_epi64x(hi_3, hi_2, hi_1, hi_0));
	ret.lo = _mm256_castsi256_pd(_mm256_setr_epi64x(lo_3, lo_2, lo_1, lo_0));
	return ret;
}

//------------------------------------------------------------------------------
// __m256dx2 load operations
//------------------------------------------------------------------------------

/**
 * @note mem_addr must be aligned on a 16-byte boundary or a general-protection
 * exception may be generated. However, this may change to be a 32-byte boundry
 * in future implementations.
 */
inline __m256dx2 _mm256x2_load_pd(const double* mem_addr) {
	__m256d v0 = _mm256_castpd128_pd256(_mm_load_pd(mem_addr));
	__m256d v1 = _mm256_castpd128_pd256(_mm_load_pd(mem_addr + 2));
	__m128d temp;
	temp = _mm_load_pd(mem_addr + 4);
	v0 = _mm256_insertf128_pd(v0, temp, 1);
	temp = _mm_load_pd(mem_addr + 6);
	v1 = _mm256_insertf128_pd(v1, temp, 1);

	__m256dx2 val;
	val.hi = _mm256_unpacklo_pd(v0, v1);
	val.lo = _mm256_unpackhi_pd(v0, v1);
	return val;
}

inline __m256dx2 _mm256x2_loadu_pd(const double* mem_addr) {
	__m256d v0 = _mm256_castpd128_pd256(_mm_loadu_pd(mem_addr));
	__m256d v1 = _mm256_castpd128_pd256(_mm_loadu_pd(mem_addr + 2));
	__m128d temp;
	temp = _mm_loadu_pd(mem_addr + 4);
	v0 = _mm256_insertf128_pd(v0, temp, 1);
	temp = _mm_loadu_pd(mem_addr + 6);
	v1 = _mm256_insertf128_pd(v1, temp, 1);

	__m256dx2 val;
	val.hi = _mm256_unpacklo_pd(v0, v1);
	val.lo = _mm256_unpackhi_pd(v0, v1);
	return val;
}

/**
 * @note mem_addr must be aligned on a 16-byte boundary or a general-protection
 * exception may be generated. However, this may change to be a 32-byte boundry
 * in future implementations.
 */
inline __m256dx2 _mm256x2_load_pdx2(const Float64x2* mem_addr) {
	return _mm256x2_load_pd((const double*)((const void*)mem_addr));
}

inline __m256dx2 _mm256x2_loadu_pdx2(const Float64x2* mem_addr) {
	return _mm256x2_loadu_pd((const double*)((const void*)mem_addr));
}


/**
 * @note mem_addr must be aligned on a 32-byte boundary or a general-protection
 * exception may be generated.
 */
inline __m256dx2 _mm256x2_load_raw_pd(const double* mem_addr) {
	__m256dx2 val;
	val.hi = _mm256_load_pd(mem_addr);
	mem_addr += sizeof(__m256d) / sizeof(double);
	val.lo = _mm256_load_pd(mem_addr);
	return val;
}

inline __m256dx2 _mm256x2_loadu_raw_pd(const double* mem_addr) {
	__m256dx2 val;
	val.hi = _mm256_loadu_pd(mem_addr);
	mem_addr += sizeof(__m256d) / sizeof(double);
	val.lo = _mm256_loadu_pd(mem_addr);
	return val;
}

//------------------------------------------------------------------------------
// __m256dx2 store operations
//------------------------------------------------------------------------------

/**
 * @note mem_addr must be aligned on a 32-byte boundary or a general-protection
 * exception may be generated.
 */
inline void _mm256x2_store_pd(double* mem_addr, __m256dx2 val) {
	// hi.x, lo.x, hi.z, lo.z
	__m256d v0 = _mm256_unpacklo_pd(val.hi, val.lo);
	// hi.y, lo.y, hi.w, lo.w
	__m256d v1 = _mm256_unpackhi_pd(val.hi, val.lo);
	__m256d tmp;
	// hi.z, lo.z, hi.w, lo.w
	tmp = _mm256_permute2f128_pd(v0, v1, 0x31);
	_mm256_store_pd(mem_addr + 4, tmp);
	// hi.x, lo.x, hi.y, lo.y
	tmp = _mm256_insertf128_pd(v0, _mm256_castpd256_pd128(v1), 1);
	_mm256_store_pd(mem_addr, tmp);
}

inline void _mm256x2_storeu_pd(double* mem_addr, __m256dx2 val) {
	// hi.x, lo.x, hi.z, lo.z
	__m256d v0 = _mm256_unpacklo_pd(val.hi, val.lo);
	// hi.y, lo.y, hi.w, lo.w
	__m256d v1 = _mm256_unpackhi_pd(val.hi, val.lo);
	__m256d temp;
	// hi.z, lo.z, hi.w, lo.w
	temp = _mm256_permute2f128_pd(v0, v1, 0x31);
	_mm256_storeu_pd(mem_addr + 4, temp);
	// hi.x, lo.x, hi.y, lo.y
	temp = _mm256_insertf128_pd(v0, _mm256_castpd256_pd128(v1), 1);
	_mm256_storeu_pd(mem_addr, temp);
}

/**
 * @note mem_addr must be aligned on a 32-byte boundary or a general-protection
 * exception may be generated.
 */
inline void _mm256x2_store_pdx2(Float64x2* mem_addr, __m256dx2 val) {
	_mm256x2_store_pd((double*)((void*)mem_addr), val);
}

inline void _mm256x2_storeu_pdx2(Float64x2* mem_addr, __m256dx2 val) {
	_mm256x2_storeu_pd((double*)((void*)mem_addr), val);
}

/**
 * @note mem_addr must be aligned on a 32-byte boundary or a general-protection
 * exception may be generated.
 */
inline void _mm256_store_raw_pdx2(double* mem_addr, __m256dx2 x) {
	_mm256_store_pd(mem_addr, x.hi);
	mem_addr += sizeof(__m256d) / sizeof(double);
	_mm256_store_pd(mem_addr, x.lo);
}

inline void _mm256_storeu_raw_pdx2(double* mem_addr, __m256dx2 x) {
	_mm256_storeu_pd(mem_addr, x.hi);
	mem_addr += sizeof(__m256d) / sizeof(double);
	_mm256_storeu_pd(mem_addr, x.lo);
}

//------------------------------------------------------------------------------
// __m256dx2 movemask
//------------------------------------------------------------------------------

/**
 * @note Assumes x.hi == x.lo
 * @returns 4bit movemask
 */
inline int _mm256x2_movemask_pdx2(__m256dx2 x) {
	return _mm256_movemask_pd(x.hi);
}

//------------------------------------------------------------------------------
// __m256dx2 full comparison functions
//------------------------------------------------------------------------------

/**
 * @brief _CMP_EQ_UQ
 */
inline __m256dx2 _mm256x2_cmpeq_pdx2(__m256dx2 x, __m256dx2 y) {
	__m256dx2 cmp_result;
	cmp_result.hi = _mm256_cmp_pd(x.hi, y.hi, _CMP_EQ_UQ);
	cmp_result.lo = _mm256_cmp_pd(x.lo, y.lo, _CMP_EQ_UQ);
	__m256dx2 ret;
	ret.hi = _mm256_and_pd(cmp_result.hi, cmp_result.lo);
	ret.lo = ret.hi;
	return ret;
}

/**
 * @brief _CMP_NEQ_UQ
 */
inline __m256dx2 _mm256x2_cmpneq_pdx2(__m256dx2 x, __m256dx2 y) {
	__m256dx2 cmp_result;
	cmp_result.hi = _mm256_cmp_pd(x.hi, y.hi, _CMP_NEQ_UQ);
	cmp_result.lo = _mm256_cmp_pd(x.lo, y.lo, _CMP_NEQ_UQ);
	__m256dx2 ret;
	ret.hi = _mm256_or_pd(cmp_result.hi, cmp_result.lo);
	ret.lo = ret.hi;
	return ret;
}

/**
 * @brief _CMP_ORD_Q
 */
inline __m256dx2 _mm256x2_cmpord_pdx2(__m256dx2 x, __m256dx2 y) {
	__m256dx2 cmp_result;
	cmp_result.hi = _mm256_cmp_pd(x.hi, y.hi, _CMP_ORD_Q);
	cmp_result.lo = _mm256_cmp_pd(x.lo, y.lo, _CMP_ORD_Q);
	__m256dx2 ret;
	ret.hi = _mm256_and_pd(cmp_result.hi, cmp_result.lo);
	ret.lo = ret.hi;
	return ret;
}

/**
 * @brief _CMP_UNORD_Q
 */
inline __m256dx2 _mm256x2_cmpunord_pdx2(__m256dx2 x, __m256dx2 y) {
	__m256dx2 cmp_result;
	cmp_result.hi = _mm256_cmp_pd(x.hi, y.hi, _CMP_UNORD_Q);
	cmp_result.lo = _mm256_cmp_pd(x.lo, y.lo, _CMP_UNORD_Q);
	__m256dx2 ret;
	ret.hi = _mm256_or_pd(cmp_result.hi, cmp_result.lo);
	ret.lo = ret.hi;
	return ret;
}


/**
 * @brief _CMP_LT_OQ
 */
inline __m256dx2 _mm256x2_cmplt_pdx2(__m256dx2 x, __m256dx2 y) {
	__m256d cmp_eq = _mm256_cmp_pd(x.hi, y.hi, _CMP_EQ_OQ);
	__m256d cmp_hi = _mm256_cmp_pd(x.hi, y.hi, _CMP_LT_OQ);
	__m256d cmp_lo = _mm256_cmp_pd(x.lo, y.lo, _CMP_LT_OQ);
	__m256dx2 ret;
	ret.hi = _mm256_blendv_pd(cmp_hi, cmp_lo, cmp_eq);
	ret.lo = ret.hi;
	return ret;
}

/**
 * @brief _CMP_LE_OQ
 */
inline __m256dx2 _mm256x2_cmple_pdx2(__m256dx2 x, __m256dx2 y) {
	__m256d cmp_eq = _mm256_cmp_pd(x.hi, y.hi, _CMP_EQ_OQ);
	__m256d cmp_hi = _mm256_cmp_pd(x.hi, y.hi, _CMP_LE_OQ);
	__m256d cmp_lo = _mm256_cmp_pd(x.lo, y.lo, _CMP_LE_OQ);
	__m256dx2 ret;
	ret.hi = _mm256_blendv_pd(cmp_hi, cmp_lo, cmp_eq);
	ret.lo = ret.hi;
	return ret;
}

/**
 * @brief _CMP_GT_OQ
 */
inline __m256dx2 _mm256x2_cmpgt_pdx2(__m256dx2 x, __m256dx2 y) {
	__m256d cmp_eq = _mm256_cmp_pd(x.hi, y.hi, _CMP_EQ_OQ);
	__m256d cmp_hi = _mm256_cmp_pd(x.hi, y.hi, _CMP_GT_OQ);
	__m256d cmp_lo = _mm256_cmp_pd(x.lo, y.lo, _CMP_GT_OQ);
	__m256dx2 ret;
	ret.hi = _mm256_blendv_pd(cmp_hi, cmp_lo, cmp_eq);
	ret.lo = ret.hi;
	return ret;
}

/**
 * @brief _CMP_GE_OQ
 */
inline __m256dx2 _mm256x2_cmpge_pdx2(__m256dx2 x, __m256dx2 y) {
	__m256d cmp_eq = _mm256_cmp_pd(x.hi, y.hi, _CMP_EQ_OQ);
	__m256d cmp_hi = _mm256_cmp_pd(x.hi, y.hi, _CMP_GE_OQ);
	__m256d cmp_lo = _mm256_cmp_pd(x.lo, y.lo, _CMP_GE_OQ);
	__m256dx2 ret;
	ret.hi = _mm256_blendv_pd(cmp_hi, cmp_lo, cmp_eq);
	ret.lo = ret.hi;
	return ret;
}

//------------------------------------------------------------------------------
// __m256dx2 reduced comparison functions
//------------------------------------------------------------------------------

/**
 * @brief _CMP_EQ_UQ
 */
inline __m256d _mm256_cmpeq_pdx2(__m256dx2 x, __m256dx2 y) {
	__m256d cmp_hi = _mm256_cmp_pd(x.hi, y.hi, _CMP_EQ_UQ);
	__m256d cmp_lo = _mm256_cmp_pd(x.lo, y.lo, _CMP_EQ_UQ);
	return _mm256_and_pd(cmp_hi, cmp_lo);
}

/**
 * @brief _CMP_NEQ_UQ
 */
inline __m256d _mm256_cmpneq_pdx2(__m256dx2 x, __m256dx2 y) {
	__m256d cmp_hi = _mm256_cmp_pd(x.hi, y.hi, _CMP_NEQ_UQ);
	__m256d cmp_lo = _mm256_cmp_pd(x.lo, y.lo, _CMP_NEQ_UQ);
	return _mm256_or_pd(cmp_hi, cmp_lo);
}

/**
 * @brief _CMP_ORD_Q
 */
inline __m256d _mm256_cmpord_pdx2(__m256dx2 x, __m256dx2 y) {
	__m256d cmp_hi = _mm256_cmp_pd(x.hi, y.hi, _CMP_ORD_Q);
	__m256d cmp_lo = _mm256_cmp_pd(x.lo, y.lo, _CMP_ORD_Q);
	return _mm256_and_pd(cmp_hi, cmp_lo);
}

/**
 * @brief _CMP_UNORD_Q
 */
inline __m256d _mm256_cmpunord_pdx2(__m256dx2 x, __m256dx2 y) {
	__m256d cmp_hi = _mm256_cmp_pd(x.hi, y.hi, _CMP_UNORD_Q);
	__m256d cmp_lo = _mm256_cmp_pd(x.lo, y.lo, _CMP_UNORD_Q);
	return _mm256_or_pd(cmp_hi, cmp_lo);
}

/**
 * @brief _CMP_LT_OQ
 */
inline __m256d _mm256_cmplt_pdx2(__m256dx2 x, __m256dx2 y) {
	__m256d cmp_eq = _mm256_cmp_pd(x.hi, y.hi, _CMP_EQ_OQ);
	__m256d cmp_hi = _mm256_cmp_pd(x.hi, y.hi, _CMP_LT_OQ);
	__m256d cmp_lo = _mm256_cmp_pd(x.lo, y.lo, _CMP_LT_OQ);
	return _mm256_blendv_pd(cmp_hi, cmp_lo, cmp_eq);
}

/**
 * @brief _CMP_LE_OQ
 */
inline __m256d _mm256_cmple_pdx2(__m256dx2 x, __m256dx2 y) {
	__m256d cmp_eq = _mm256_cmp_pd(x.hi, y.hi, _CMP_EQ_OQ);
	__m256d cmp_hi = _mm256_cmp_pd(x.hi, y.hi, _CMP_LE_OQ);
	__m256d cmp_lo = _mm256_cmp_pd(x.lo, y.lo, _CMP_LE_OQ);
	return _mm256_blendv_pd(cmp_hi, cmp_lo, cmp_eq);
}

/**
 * @brief _CMP_GT_OQ
 */
inline __m256d _mm256_cmpgt_pdx2(__m256dx2 x, __m256dx2 y) {
	__m256d cmp_eq = _mm256_cmp_pd(x.hi, y.hi, _CMP_EQ_OQ);
	__m256d cmp_hi = _mm256_cmp_pd(x.hi, y.hi, _CMP_GT_OQ);
	__m256d cmp_lo = _mm256_cmp_pd(x.lo, y.lo, _CMP_GT_OQ);
	return _mm256_blendv_pd(cmp_hi, cmp_lo, cmp_eq);
}

/**
 * @brief _CMP_GE_OQ
 */
inline __m256d _mm256_cmpge_pdx2(__m256dx2 x, __m256dx2 y) {
	__m256d cmp_eq = _mm256_cmp_pd(x.hi, y.hi, _CMP_EQ_OQ);
	__m256d cmp_hi = _mm256_cmp_pd(x.hi, y.hi, _CMP_GE_OQ);
	__m256d cmp_lo = _mm256_cmp_pd(x.lo, y.lo, _CMP_GE_OQ);
	return _mm256_blendv_pd(cmp_hi, cmp_lo, cmp_eq);
}

//------------------------------------------------------------------------------
// _mm256_cmp_pdx2 AVX compare function
//------------------------------------------------------------------------------

/**
 * @warning Only compares x.hi and y.hi, use dedicated cmp functions instead.
 */
#define _mm256_cmp_pdx2(x, y, imm8)\
	_mm256_cmp_pd(x.hi, y.hi, _CMP_EQ_OQ)

//------------------------------------------------------------------------------
// __m256dx2 max/min functions
//------------------------------------------------------------------------------

inline __m256dx2 _mm256x2_max_pdx2(__m256dx2 x, __m256dx2 y) {
	__m256dx2 ret;
	ret.hi = _mm256_max_pd(x.hi, y.hi);
	
	// if (x.hi == y.hi)
	ret.lo = _mm256_max_pd(x.lo, y.lo);

	// if (x.hi > y.hi), set ret.lo to x.lo 
	__m256d cmp_x_hi_gt = _mm256_cmp_pd(x.hi, y.hi, _CMP_GT_OQ);
	ret.lo = _mm256_blendv_pd(ret.lo, x.lo, cmp_x_hi_gt);

	// if (y.hi > x.hi), set ret.lo to y.lo 
	__m256d cmp_y_hi_gt = _mm256_cmp_pd(y.hi, x.hi, _CMP_GT_OQ);
	ret.lo = _mm256_blendv_pd(ret.lo, y.lo, cmp_y_hi_gt);

	return ret;
}

inline __m256dx2 _mm256x2_min_pdx2(__m256dx2 x, __m256dx2 y) {
	__m256dx2 ret;
	ret.hi = _mm256_min_pd(x.hi, y.hi);
	
	// if (x.hi == y.hi)
	ret.lo = _mm256_min_pd(x.lo, y.lo);

	// if (x.hi < y.hi), set ret.lo to x.lo 
	__m256d cmp_x_hi_lt = _mm256_cmp_pd(x.hi, y.hi, _CMP_LT_OQ);
	ret.lo = _mm256_blendv_pd(ret.lo, x.lo, cmp_x_hi_lt);

	// if (y.hi < x.hi), set ret.lo to y.lo 
	__m256d cmp_y_hi_lt = _mm256_cmp_pd(y.hi, x.hi, _CMP_LT_OQ);
	ret.lo = _mm256_blendv_pd(ret.lo, y.lo, cmp_y_hi_lt);

	return ret;
}

//------------------------------------------------------------------------------
// __m256dx2 rounding functions
//------------------------------------------------------------------------------

/** same as aint(x) */
inline __m256dx2 _mm256x2_trunc_pdx2(__m256dx2 x) {
	__m256d int_hi = _mm256_trunc_pd(x.hi);
	__m256d int_lo = _mm256_trunc_pd(x.lo);
	__m256d frac_hi = _mm256_sub_pd(x.hi, int_hi);
	__m256d frac_lo = _mm256_sub_pd(x.lo, int_lo);
	
	__m256d frac_ge_1 = _mm256_cmp_pd(_mm256_add_pd(frac_hi, frac_lo), _mm256_set1_pd(1.0), _CMP_GE_OQ);

	__m256dx2 trunc_all = _mm256x2_add_pdx2_pd(_mm256x2_add_pd_pd(
		_mm256_blendv_pd(_mm256_setzero_pd(), _mm256_set1_pd(1.0), frac_ge_1),
		int_lo
	), int_hi);
	return trunc_all;
}

inline __m256dx2 _mm256x2_floor_pdx2(__m256dx2 x) {
	__m256dx2 int_part = _mm256x2_trunc_pdx2(x);
	
	__m256d cmp_floor;
	cmp_floor = _mm256_and_pd(
		_mm256_cmplt_pdx2(x, _mm256x2_setzero_pdx2()),
		_mm256_cmpneq_pdx2(x, int_part)
	);
	__m256d floor_part = _mm256_blendv_pd(
		_mm256_setzero_pd(), _mm256_set1_pd(1.0), cmp_floor
	);
	return _mm256x2_sub_pdx2_pd(int_part, floor_part);
}

inline __m256dx2 _mm256x2_ceil_pdx2(__m256dx2 x) {
	__m256dx2 int_part = _mm256x2_trunc_pdx2(x);
	
	__m256d cmp_ceil = _mm256_and_pd(
		_mm256_cmpgt_pdx2(x, _mm256x2_setzero_pdx2()),
		_mm256_cmpneq_pdx2(x, int_part)
	);
	__m256d ceil_part = _mm256_blendv_pd(
		_mm256_setzero_pd(), _mm256_set1_pd(1.0), cmp_ceil
	);
	return _mm256x2_add_pdx2_pd(int_part, ceil_part);
}

/** same as nint(x) */
inline __m256dx2 _mm256x2_round_pdx2(__m256dx2 x) {
	__m256dx2 round_up = _mm256x2_add_pdx2_pd(_mm256x2_floor_pdx2(x), _mm256_set1_pd(0.5));
	__m256dx2 round_dn = _mm256x2_sub_pdx2_pd(_mm256x2_ceil_pdx2 (x), _mm256_set1_pd(0.5));
	__m256d cmp_mask = _mm256_cmplt_pdx2(x, _mm256x2_setzero_pdx2());
	__m256dx2 ret;
	ret.hi = _mm256_blendv_pd(round_up.hi, round_dn.hi, cmp_mask);
	ret.lo = _mm256_blendv_pd(round_up.lo, round_dn.lo, cmp_mask);
	return ret;
}

//------------------------------------------------------------------------------
// __m256dx2 math.h functions
//------------------------------------------------------------------------------

inline __m256dx2 _mm256x2_fabs_pdx2(__m256dx2 x) {
	__m256d cmp_lt = _mm256_cmplt_pdx2(x, _mm256x2_setzero_pdx2());
	
	__m256d fabs_mask = _mm256_blendv_pd(
		_mm256_set1_pd(1.0), _mm256_set1_pd(-1.0), cmp_lt
	);
	x.hi = _mm256_mul_pd(x.hi, fabs_mask);
	x.lo = _mm256_mul_pd(x.lo, fabs_mask);
	return x;
}

inline __m256dx2 _mm256x2_fdim_pdx2(__m256dx2 x, __m256dx2 y) {
	__m256dx2 ret;
	ret = _mm256x2_sub_pdx2(x, y);
	__m256d cmp_gt = _mm256_cmpgt_pdx2(x, y);
	ret.hi = _mm256_blendv_pd(ret.hi, _mm256_setzero_pd(), cmp_gt);
	ret.lo = _mm256_blendv_pd(ret.lo, _mm256_setzero_pd(), cmp_gt);
	return ret;
}

inline __m256dx2 _mm256x2_copysign_pdx2(__m256dx2 x, __m256dx2 y) {
	__m256d negate_mask = _mm256_xor_pd(
		_mm256_cmp_pd(x.hi, _mm256_setzero_pd(), _CMP_LT_OQ),
		_mm256_cmp_pd(y.hi, _mm256_setzero_pd(), _CMP_LT_OQ)
	);
	__m256d negate_mul = _mm256_blendv_pd(
		_mm256_set1_pd(1.0), _mm256_set1_pd(-1.0), negate_mask
	);
	x.hi = _mm256_mul_pd(x.hi, negate_mul);
	x.lo = _mm256_mul_pd(x.lo, negate_mul);
	return x;
}

inline __m256dx2 _mm256x2_sqrt_pdx2(__m256dx2 x) {
	__m256d guess = _mm256_sqrt_pd(x.hi);
	return _mm256x2_mul_power2_pdx2_pd(
		_mm256x2_add_pd_pdx2(guess, _mm256x2_div_zero_pdx2_pd(x, guess)),
		_mm256_set1_pd(0.5)
	);
}

/** @note This function may or may not use AVX for calculations */
inline __m256dx2 _mm256x2_cbrt_pdx2(__m256dx2 x) {
	__m256d guess = _mm256_cbrt_pd(x.hi);
	return _mm256x2_div_pdx2_pd(
		_mm256x2_add_pdx2(
			_mm256x2_mul_power2_pd_pd(
				_mm256_set1_pd(2.0), guess
			),
			_mm256x2_div_zero_pdx2(x, _mm256x2_square_pd(guess))
		),
		_mm256_set1_pd(3.0)
	);
}

/**
 * @brief returns the fraction part of a __m256dx2 value. int_part may be NULL
 */
inline __m256dx2 _mm256x2_modf_pdx2(__m256dx2 x, __m256dx2* int_part) {
	__m256dx2 trunc_part = _mm256x2_trunc_pdx2(x);
	if (int_part != NULL) {
		*int_part = trunc_part;
	}
	return _mm256x2_sub_pdx2(x, trunc_part);
}

inline __m256dx2 _mm256x2_fmod_pdx2(__m256dx2 x, __m256dx2 y) {
	__m256dx2 trunc_part = _mm256x2_trunc_pdx2(_mm256x2_div_pdx2(x, y));
	return _mm256x2_sub_pdx2(x, _mm256x2_mul_pdx2(y, trunc_part));
}

//------------------------------------------------------------------------------
// __m256dx2 exponents and logarithms
//------------------------------------------------------------------------------

/** @note This function doesn't use AVX for calculations */
__m256dx2 _mm256x2_exp_pdx2(__m256dx2 x);

/** @note This function doesn't use AVX for calculations */
inline __m256dx2 _mm256x2_exp2_pdx2(const __m256dx2 a) {
	const __m256dx2 __m256dx2_log2 = _mm256x2_set1_pd_pd(
		6.931471805599452862e-01, 2.319046813846299558e-17
	);
	return _mm256x2_exp_pdx2(_mm256x2_mul_pdx2(a, __m256dx2_log2));
}

/** @note This function doesn't use AVX for calculations */
inline __m256dx2 _mm256x2_exp10_pdx2(const __m256dx2 a) {
	const __m256dx2 __m256dx2_log10 = _mm256x2_set1_pd_pd(
		2.302585092994045901e+00, -2.170756223382249351e-16
	);
	return _mm256x2_exp_pdx2(_mm256x2_mul_pdx2(a, __m256dx2_log10));
}

/** @note This function doesn't use AVX for calculations */
__m256dx2 _mm256x2_log_pdx2(__m256dx2 x);

/** @note This function doesn't use AVX for calculations */
inline __m256dx2 _mm256x2_log2_pdx2(const __m256dx2 x) {
	const __m256dx2 __m256dx2_log2 = _mm256x2_set1_pd_pd(
		6.931471805599452862e-01, 2.319046813846299558e-17
	);
	return _mm256x2_div_pdx2(_mm256x2_log_pdx2(x), __m256dx2_log2);
}

/** @note This function doesn't use AVX for calculations */
inline __m256dx2 _mm256x2_log10_pdx2(const __m256dx2 x) {
	const __m256dx2 __m256dx2_log10 = _mm256x2_set1_pd_pd(
		2.302585092994045901e+00, -2.170756223382249351e-16
	);
	return _mm256x2_div_pdx2(_mm256x2_log_pdx2(x), __m256dx2_log10);
}


//------------------------------------------------------------------------------
// __m256dx2 trigonometry
//------------------------------------------------------------------------------

/** @note This function doesn't use AVX for calculations */
__m256dx2 _mm256x2_sin_pdx2(__m256dx2 x);

/** @note This function doesn't use AVX for calculations */
__m256dx2 _mm256x2_cos_pdx2(__m256dx2 x);

/**
 * @note This function doesn't use AVX for calculations
 * @warning p_sin and p_cos must be aligned on a 32-byte boundary or a
 * general-protection exception may be generated.
 */
void _mm256x2_sincos_pdx2(
	__m256dx2 theta, __m256dx2* p_sin, __m256dx2* p_cos
);

/** @note This function doesn't use AVX for calculations */
inline __m256dx2 _mm256x2_tan_pdx2(__m256dx2 x) {
	__m256dx2 t_sin, t_cos;
	_mm256x2_sincos_pdx2(x, &t_sin, &t_cos);
	return _mm256x2_div_pdx2(t_sin, t_cos);
}

/** @note This function doesn't use AVX for calculations */
__m256dx2 _mm256x2_asin_pdx2(__m256dx2 x);

/** @note This function doesn't use AVX for calculations */
__m256dx2 _mm256x2_acos_pdx2(__m256dx2 x);

/** @note This function doesn't use AVX for calculations */
__m256dx2 _mm256x2_atan_pdx2(__m256dx2 x);

/** @note This function doesn't use AVX for calculations */
__m256dx2 _mm256x2_atan2_pdx2(__m256dx2 y, __m256dx2 x);

/** @note sinh is inaccurate when x is close to 0, which is why it isn't inlined */
__m256dx2 _mm256x2_sinh_pdx2(__m256dx2 x);

/** @note This function doesn't use AVX for calculations */
inline __m256dx2 _mm256x2_cosh_pdx2(__m256dx2 x) {
	__m256dx2 exp_x = _mm256x2_exp_pdx2(x);
	return _mm256x2_mul_power2_pdx2_pd(
		_mm256x2_add_pdx2(exp_x, _mm256x2_recip_pdx2(exp_x)),
	_mm256_set1_pd(0.5));
}

/** @note This function doesn't use AVX for calculations */
__m256dx2 _mm256x2_tanh_pdx2(__m256dx2 x);

/**
 * @note This function doesn't use AVX for calculations
 * @warning p_sin and p_cos must be aligned on a 32-byte boundary or a
 * general-protection exception may be generated.
 */
void _mm256x2_sinhcosh_pdx2(
	__m256dx2 theta, __m256dx2* p_sinh, __m256dx2* p_cosh
);

/** @note This function doesn't use AVX for calculations */
inline __m256dx2 _mm256x2_asinh_pdx2(__m256dx2 x) {
	return _mm256x2_log_pdx2(_mm256x2_add_pdx2(x,
		_mm256x2_sqrt_pdx2(
			_mm256x2_sub_pdx2_pd(_mm256x2_square_pdx2(x), _mm256_set1_pd(1.0))
		)
	));
}

/** @note This function doesn't use AVX for calculations */
inline __m256dx2 _mm256x2_acosh_pdx2(__m256dx2 x) {
	return _mm256x2_log_pdx2(_mm256x2_add_pdx2(x,
		_mm256x2_sqrt_pdx2(
			_mm256x2_add_pdx2_pd(_mm256x2_square_pdx2(x), _mm256_set1_pd(1.0))
		)
	));
}

/** @note This function doesn't use AVX for calculations */
inline __m256dx2 _mm256x2_atanh_pdx2(__m256dx2 x) {
	return _mm256x2_mul_power2_pdx2_pd(_mm256x2_log_pdx2(_mm256x2_div_pdx2(
			_mm256x2_add_pd_pdx2(_mm256_set1_pd(1.0), x),
			_mm256x2_sub_pd_pdx2(_mm256_set1_pd(1.0), x)
	)), _mm256_set1_pd(0.5));
}

#ifdef __cplusplus
	}
#endif

#endif /* FLOAT64X2_AVX_H */
