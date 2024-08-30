/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/
#if 0

#ifndef FLOAT64_AVX_H
#define FLOAT64_AVX_H

#if (!defined(__AVX__) && defined(__GNUC__))
	#error "__AVX__ is not enabled in your compiler. Try -mavx"
#endif

#include <immintrin.h>

#ifdef __cplusplus
	extern "C" {
#endif

//------------------------------------------------------------------------------
// __m256d SVML configuration
//------------------------------------------------------------------------------

// You may define this to 0 or 1 to force enable/disable the SVML replacement functions.
#ifndef FLOAT64_AVX_SVML_REPLACEMENTS
	#if defined(_SVML) || defined(__SVML__) && defined(__INTEL_COMPILER)
		// Don't define SVML replacement functions
		#define FLOAT64_AVX_SVML_REPLACEMENTS 0
	#else
		// Defines replacement functions for SVML
		#define FLOAT64_AVX_SVML_REPLACEMENTS 1
	#endif
#endif

/**
 * @brief defines functions and macros for the __m256d type.
 * @note the #ifndef _mm256_func_pd directives can only detect macros as the
 * preprocessor isn't aware of function definitions
 */

//------------------------------------------------------------------------------
// __m256d math.h functions
//------------------------------------------------------------------------------

/** @note Protects against macros, but not function definitions */
#ifndef _mm256_negate_pd 
	/**
	 * @brief `-x` Negates a __m256d (Multiplies by -1.0)
	 */
	static inline __m256d _mm256_negate_pd(__m256d x) {
		// return _mm256_xor_pd(
		// 	x,
		// 	_mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x8000000000000000))
		// );
		return _mm256_mul_pd(x, _mm256_set1_pd(-1.0));
	}
#endif

/** @note Protects against macros, but not function definitions */
#ifndef _mm256_fabs_pd
	/**
	 * @brief `|x|` Returns the absolute value of a __m256d value
	 * @remarks _mm256_andnot_pd cannot be used because 0x8000000000000000 gets
	 * converted from -0.0 to 0.0 on -Ofast
	 */
	static inline __m256d _mm256_fabs_pd(__m256d x) {
		return _mm256_and_pd(
			x,
			_mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x7FFFFFFFFFFFFFFF))
		);
	}
#endif

//------------------------------------------------------------------------------
// __m256d SVML replacement functions
//------------------------------------------------------------------------------

#if (FLOAT64_AVX_SVML_REPLACEMENTS != 0)

/** @note Protects against macros, but not function definitions */
#ifndef _mm256_trunc_pd
	/**
	 * @brief _mm256_trunc_pd replacement function.
	 */
	static inline __m256d _mm256_trunc_pd(__m256d x) {
		return _mm256_round_pd(x, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
	}
#endif

/**
 * @brief _mm256_cbrt_pd replacement function. May be slow/inefficient.
 * @note This function doesn't use AVX for calculations
 */
__m256d _mm256_cbrt_pd(__m256d x);


//------------------------------------------------------------------------------
// __m256d SVML exponents and logarithms
//------------------------------------------------------------------------------

/** @note This function doesn't use AVX for calculations */
__m256d _mm256_exp_pd(__m256d x);

/** @note This function doesn't use AVX for calculations */
__m256d _mm256_expm1_pd(__m256d x);

/** @note This function doesn't use AVX for calculations */
static inline __m256d _mm256_exp2_pdx2(const __m256d x) {
	const __m256d _mm256_log2 = _mm256x2_set1_pd_pd(
		6.931471805599452862e-01, 2.319046813846299558e-17
	);
	return _mm256x2_exp_pdx2(_mm256x2_mul_pdx2(x, __m256dx2_log2));
}

/** @note This function doesn't use AVX for calculations */
static inline __m256d _mm256_exp10_pdx2(const __m256dx2 a) {
	const __m256d _mm256_log10 = _mm256x2_set1_pd_pd(
		2.302585092994045901e+00, -2.170756223382249351e-16
	);
	return _mm256x2_exp_pdx2(_mm256x2_mul_pdx2(a, __m256dx2_log10));
}

/** @note This function doesn't use AVX for calculations */
__m256d _mm256_log_pd(__m256d x);

/** @note This function doesn't use AVX for calculations */
__m256d _mm256_log1p_pd(__m256d x);

/** @note This function doesn't use AVX for calculations */
static inline __m256d _mm256_log2_pdx2(const __m256dx2 x) {
	const __m256d _mm256__log2 = _mm256x2_set1_pd_pd(
		6.931471805599452862e-01, 2.319046813846299558e-17
	);
	return _mm256x2_div_pdx2(_mm256x2_log_pdx2(x), __m256dx2_log2);
}

/** @note This function doesn't use AVX for calculations */
static inline __m256d _mm256_log10_pdx2(const __m256dx2 x) {
	const __m256d _mm256__log10 = _mm256x2_set1_pd_pd(
		2.302585092994045901e+00, -2.170756223382249351e-16
	);
	return _mm256x2_div_pdx2(_mm256x2_log_pdx2(x), __m256dx2_log10);
}

/** @note This function doesn't use AVX for calculations */
__m256d _mm256_pow_pd(__m256d x, __m256dx2 y);

/** @note This function doesn't use AVX for calculations */
__m256d _mm256_pow_pdx2_pd(__m256dx2 x,  __m256d y);

//------------------------------------------------------------------------------
// __m256d SVML Trigonometry
//------------------------------------------------------------------------------

/** @note This function doesn't use AVX for calculations */
__m256d _mm256_sin_pd(__m256d x);

/** @note This function doesn't use AVX for calculations */
__m256d _mm256_cos_pd(__m256d x);

/**
 * @brief returns sin by value, and cos by pointer.
 * @warning cos_ptr must be aligned on a 32-byte boundary or a
 * general-protection exception may be generated.
 * @note This function doesn't use AVX for calculations
 */
__m256d _mm256_sincos_pd(__m256d* cos_ptr, __m256d theta);

/** @note This function doesn't use AVX for calculations */
static inline __m256d _mm256_tan_pd(__m256d theta) {
	__m256d cos_val;
	__m256d sin_val = _mm256_sincos_pd(&cos_val, theta);
	return _mm256_div_pd(t_sin, t_cos);
}

/** @note This function doesn't use AVX for calculations */
__m256d _mm256_asin_pd(__m256d x);

/** @note This function doesn't use AVX for calculations */
__m256d _mm256_acos_pd(__m256d x);

/** @note This function doesn't use AVX for calculations */
__m256d _mm256_atan_pd(__m256d x);

/** @note This function doesn't use AVX for calculations */
__m256d _mm256_atan2_pd(__m256d y, __m256d x);

/**
 * @note This function doesn't use AVX for calculations
 * @remarks sinh is inaccurate when x is close to 0, which is why it isn't inlined
 */
__m256d _mm256_sinh_pd(__m256d x);

/** @note This function doesn't use AVX for calculations */
static inline __m256d _mm256_cosh_pd(__m256d x) {
	__m256d exp_x = _mm256_exp_pd(x);
	return _mm256_mul_pd(
		_mm256_add_pd(exp_x, _mm256_recip_pd(exp_x)),
	_mm256_set1_pd(0.5));
}

/** @note This function doesn't use AVX for calculations */
__m256d _mm256_tanh_pd(__m256d x);

/**
 * @brief returns sinh by value, and cosh by pointer.
 * @warning cosh_ptr must be aligned on a 32-byte boundary or a
 * general-protection exception may be generated.
 * @note This function doesn't use AVX for calculations
 */
__m256d _mm256_sinhcosh_pd(__m256d* cosh_ptr, __m256d theta);

/** @note This function doesn't use AVX for calculations */
static inline __m256d _mm256_asinh_pd(__m256d x) {
	return _mm256_log_pd(_mm256_add_pd(x,
		_mm256_sqrt_pd(
			_mm256_sub_pd(_mm256_mul_pd(x, x), _mm256_set1_pd(1.0))
		)
	));
}

/** @note This function doesn't use AVX for calculations */
static inline __m256d _mm256_acosh_pd(__m256d x) {
	return _mm256_log_pd(_mm256_add_pd(x,
		_mm256_sqrt_pd(
			_mm256_add_pd(_mm256_mul_pd(x, x), _mm256_set1_pd(1.0))
		)
	));
}

/** @note This function doesn't use AVX for calculations */
static inline __m256d _mm256_atanh_pd(__m256d x) {
	return _mm256_mul_pd(_mm256_log_pd(_mm256_div_pd(
			_mm256_add_pd(_mm256_set1_pd(1.0), x),
			_mm256_sub_pd(_mm256_set1_pd(1.0), x)
	)), _mm256_set1_pd(0.5));
}

#endif

#ifdef __cplusplus
	}
#endif

#endif /* FLOAT64_AVX_H */

#endif