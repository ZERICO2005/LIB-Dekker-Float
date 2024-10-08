/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef FLOAT64_SSE2_H
#define FLOAT64_SSE2_H

#include <stdint.h>
#include <emmintrin.h>

#if (!defined(__SSE2__) && defined(__GNUC__))
	#error "__SSE2__ is not enabled in your compiler. Try -msse2"
#endif

static inline __m128d _mm_ldexp1_pd_epi64(__m128i exp) {
	// Adds to the exponent bits of an ieee double
	return _mm_castsi128_pd(_mm_add_epi64(
		_mm_castpd_si128(_mm_set1_pd(1.0)), _mm_slli_epi64(exp, 52)
	));
}

#ifdef __SSE4_1__
/**
 * @brief Computes ilogb(x) using SSE2 integer operations
 * @returns sign extended __m128i int32_t
 */
static inline __m128i _mm_ilogb_pd_epi64(__m128d x) {
	// shifts the exponent into the lower half of the int64_t
	__m128i mask = _mm_srli_epi64(_mm_castpd_si128(x), 31);
	// sign extends
	mask = _mm_srai_epi32(mask, 21);
	__m128i packed = _mm_shuffle_epi32(mask, _MM_SHUFFLE(2, 0, 2, 0));
	return _mm_cvtepi32_epi64(packed);
}
#endif
/**
 * @brief Computes ilogb(x) using SSE2 integer operations
 * @returns zero extended __m128i uint64_t
 */
static inline __m128i _mm_ilogb_pd_epu64(__m128d x) {
	__m128i ret = _mm_castpd_si128(_mm_andnot_pd(
		x, _mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x8000000000000000))
	));
	return _mm_srli_epi64(ret, 52);
}

#endif /* FLOAT64_SSE2_H */
