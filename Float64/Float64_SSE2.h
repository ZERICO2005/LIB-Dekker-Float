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

#endif /* FLOAT64_SSE2_H */