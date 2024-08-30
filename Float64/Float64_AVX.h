/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef FLOAT64_AVX_H
#define FLOAT64_AVX_H


/**
 * @brief defines functions and macros for the __m256d type.
 * @note the #ifndef _mm256_func_pd directives can only detect macros as the
 * preprocessor isn't aware of function definitions
 */

#if (!defined(__AVX__) && defined(__GNUC__))
	#error "__AVX__ is not enabled in your compiler. Try -mavx"
#endif

#include <stdint.h>
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

//------------------------------------------------------------------------------
// __m256d mathematical constants
//------------------------------------------------------------------------------

/**
 * @brief ~2.718281828 Returns the value of euler's number
 */
static inline __m256d _mm256_const_e_pd(void) {
	return _mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x4005BF0A8B145769));
}

/**
 * @brief ~1.442695041 Returns the value of log2(e)
 */
static inline __m256d _mm256_const_log2e_pd(void) {
	return _mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x3FF71547652B82FE));
}

/**
 * @brief ~0.434294482 Returns the value of log10(e)
 */
static inline __m256d _mm256_const_log10e_pd(void) {
	return _mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x3FDBCB7B1526E50E));
}

/**
 * @brief ~3.141592654 Returns the value of pi
 */
static inline __m256d _mm256_const_pi_pd(void) {
	return _mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x400921FB54442D18));
}

/**
 * @brief ~0.318309886 Returns the value of 1 / pi
 */
static inline __m256d _mm256_const_inv_pi_pd(void) {
	return _mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x3FD45F306DC9C883));
}

/**
 * @brief ~0.564189584 Returns the value of 1 / sqrt(pi)
 */
static inline __m256d _mm256_const_inv_sqrtpi_pd(void) {
	return _mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x3FE20DD750429B6D));
}

/**
 * @brief ~0.693147181 Returns the value of ln(2)
 */
static inline __m256d _mm256_const_ln2_pd(void) {
	return _mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x3FE62E42FEFA39EF));
}

/**
 * @brief ~2.302585093 Returns the value of ln(10)
 */
static inline __m256d _mm256_const_ln10_pd(void) {
	return _mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x40026BB1BBB55516));
}

/**
 * @brief ~1.414213562 Returns the value of sqrt(2)
 */
static inline __m256d _mm256_const_sqrt2_pd(void) {
	return _mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x3FF6A09E667F3BCD));
}

/**
 * @brief ~1.732050808 Returns the value of sqrt(3)
 */
static inline __m256d _mm256_const_sqrt3_pd(void) {
	return _mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x3FFBB67AE8584CAA));
}

/**
 * @brief ~0.577350269 Returns the value of 1 / sqrt(3)
 */
static inline __m256d _mm256_const_inv_sqrt3_pd(void) {
	return _mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x3FE279A74590331C));
}

/**
 * @brief ~0.577215665 Returns the value of gamma (The Euler–Mascheroni constant)
 */
static inline __m256d _mm256_const_egamma_pd(void) {
	return _mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x3FE2788CFC6FB619));
}

/**
 * @brief ~1.618033989 Returns the value of phi (The golden ratio)
 */
static inline __m256d _mm256_const_phi_pd(void) {
	return _mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x3FF9E3779B97F4A8));
}

//------------------------------------------------------------------------------
// __m256d floating point manipulation
//------------------------------------------------------------------------------

/** @brief Returns a __m256dx4 value set to positive infinity */
static inline __m256d _mm256_get_infinity_pd(void) {
	return _mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x7FF0000000000000));
}

/** @brief Returns a __m256d value set to signaling NaN */
static inline __m256d _mm256_get_sNaN_pd(void) {
	return _mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x7FF0000000000001));
}

/** @brief Returns a __m256d value set to quiet NaN */
static inline __m256d _mm256_get_qNaN_pd(void) {
	return _mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x7FF8000000000001));
}

/** @brief Returns the bitmask for extracting the exponent bits */
static inline __m256d _mm256_get_exponent_mask_pd(void) {
	return _mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x7FF0000000000000));
}

/** @brief Returns the bitmask for extracting the mantissa bits */
static inline __m256d _mm256_get_mantissa_mask_pd(void) {
	return _mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x000FFFFFFFFFFFFF));
}

/** @brief Extracts the exponent via a bitmask */
static inline __m256d _mm256_extract_exponent_pd(const __m256d x) {
	return _mm256_and_pd(x, _mm256_get_exponent_mask_pd());
}

/** @brief Extracts the mantissa via a bitmask */
static inline __m256d _mm256_extract_mantissa_pd(const __m256d x) {
	return _mm256_and_pd(x, _mm256_get_mantissa_mask_pd());
}

//------------------------------------------------------------------------------
// __m256d floating point classify
//------------------------------------------------------------------------------

/** @brief Returns true if x is negative */
static inline __m256d _mm256_signbit_pd(const __m256d x) {
	return _mm256_cmp_pd(x, _mm256_setzero_pd(), _CMP_LT_OQ);
}

/** @brief Returns true if x is finite */
static inline __m256d _mm256_isfinite_pd(const __m256d x) {
	// extract the exponent, and check that it is not all ones
	__m256d x_exp = _mm256_extract_exponent_pd(x);
	return _mm256_cmp_pd(x_exp, _mm256_get_exponent_mask_pd(), _CMP_NEQ_UQ);
}

/** @brief Returns true if x is +-infinity */
static inline __m256d _mm256_isinf_pd(const __m256d x) {
	return _mm256_cmp_pd(
		_mm256_and_pd(
			x,
			_mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x7FFFFFFFFFFFFFFF))
		),
		_mm256_get_infinity_pd(),
	_CMP_EQ_UQ);
}

/** @brief Returns true if x is any kind of NaN */
static inline __m256d _mm256_isnan_pd(const __m256d x) {
	// extract the exponent, and check if it is all ones
	__m256d x_exp = _mm256_cmp_pd(
		_mm256_extract_exponent_pd(x), _mm256_get_exponent_mask_pd(),
	_CMP_EQ_UQ);
	// extract the mantissa, and check that at least one bit is set
	__m256d x_mant = _mm256_cmp_pd(
		_mm256_extract_mantissa_pd(x), _mm256_setzero_pd(),
	_CMP_NEQ_UQ);
	return _mm256_and_pd(x_exp, x_mant);
}

/** @brief Returns true if x is normal */
static inline __m256d _mm256_isnormal_pd(const __m256d x) {
	// extract the exponent, and check that it is not all ones or zeros.
	__m256d x_exp = _mm256_extract_exponent_pd(x);
	return _mm256_and_pd(
		_mm256_cmp_pd(x_exp, _mm256_get_exponent_mask_pd(), _CMP_NEQ_UQ),
		_mm256_cmp_pd(x_exp, _mm256_setzero_pd(), _CMP_NEQ_UQ)
	);
}

/** @brief Returns true if x and y are unordered */
static inline __m256d _mm256_isunordered_pd(__m256d x, __m256d y) {
	return _mm256_cmp_pd(x, y, _CMP_UNORD_Q);
}

//------------------------------------------------------------------------------
// __m256d math.h functions
//------------------------------------------------------------------------------

#ifndef _mm256_negate_pd 
/**
 * @brief `-x` Negates a __m256d value (Multiplies by -1.0)
 */
static inline __m256d _mm256_negate_pd(__m256d x) {
	// return _mm256_xor_pd(
	// 	x,
	// 	_mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x8000000000000000))
	// );
	return _mm256_mul_pd(x, _mm256_set1_pd(-1.0));
}
#endif

#ifndef _mm256_recip_pd 
/**
 * @brief `1 / x` Calculates the reciprocal of a __m256d value
 */
static inline __m256d _mm256_recip_pd(__m256d x) {
	return _mm256_div_pd(_mm256_set1_pd(1.0), x);
}
#endif

#ifndef _mm256_square_pd 
/**
 * @brief `x * x` Squares a __m256d value
 */
static inline __m256d _mm256_square_pd(__m256d x) {
	return _mm256_mul_pd(x, x);
}
#endif

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

#ifndef _mm256_fmax_pd
/**
 * @brief Returns the fmax of x and y. Correctly handling NaN and signed zeros.
 * You may use _mm256_max_pd as a faster alternative.
 */
static inline __m256d _mm256_fmax_pd(__m256d x, __m256d y) {
	__m256d fmax_cmp =
		_mm256_or_pd(
			_mm256_andnot_pd(
				_mm256_or_pd(
					_mm256_andnot_pd(
						_mm256_signbit_pd(x),
						_mm256_isnan_pd(y)
					),
					_mm256_isnan_pd(x)
				),
				_mm256_cmp_pd(y, x, _CMP_LT_OQ)
			),
			_mm256_cmp_pd(x, y, _CMP_LT_OQ)
		);
	return _mm256_blendv_pd(x, y, fmax_cmp);
}
#endif

#ifndef _mm256_fmin_pd
/**
 * @brief Returns the fmin of x and y. Correctly handling NaN and signed zeros.
 * You may use _mm256_min_pd as a faster alternative.
 */
static inline __m256d _mm256_fmin_pd(__m256d x, __m256d y) {
	__m256d fmax_cmp =
		_mm256_or_pd(
			_mm256_andnot_pd(
				_mm256_or_pd(
					_mm256_andnot_pd(
						_mm256_signbit_pd(x),
						_mm256_isnan_pd(y)
					),
					_mm256_isnan_pd(x)
				),
				_mm256_cmp_pd(y, x, _CMP_GT_OQ)
			),
			_mm256_cmp_pd(x, y, _CMP_GT_OQ)
		);
	return _mm256_blendv_pd(x, y, fmax_cmp);
}
#endif

//------------------------------------------------------------------------------
// __m256d SVML replacement functions
//------------------------------------------------------------------------------

#if (FLOAT64_AVX_SVML_REPLACEMENTS != 0)

#ifndef _mm256_trunc_pd

/**
 * @brief _mm256_trunc_pd replacement function.
 */
static inline __m256d _mm256_trunc_pd(__m256d x) {
	return _mm256_round_pd(x, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
}

#endif

/**
 * @note Naive implementation of inverse sqrt
 */
static inline __m256d _mm256_invsqrt_pd(const __m256d x) {
	return _mm256_recip_pd(_mm256_sqrt_pd(x));
}

/**
 * @note This function doesn't use AVX for calculations
 */
__m256d _mm256_cbrt_pd(__m256d x);

/**
 * @note This function doesn't use AVX for calculations
 */
static inline __m256d _mm256_invcbrt_pd(const __m256d x) {
	return _mm256_recip_pd(_mm256_cbrt_pd(x));
}

/**
 * @note This function doesn't use AVX for calculations
 * @remarks Assuming SVML _mm256_hypot_pd is a true hypot function that
 * can handle overflows.
 */
__m256d _mm256_hypot_pd(const __m256d x, const __m256d y);

//------------------------------------------------------------------------------
// __m256d SVML exponents and logarithms
//------------------------------------------------------------------------------

/** @note This function doesn't use AVX for calculations */
__m256d _mm256_exp_pd(__m256d x);

/** @note This function doesn't use AVX for calculations */
__m256d _mm256_expm1_pd(__m256d x);

/** @note This function doesn't use AVX for calculations */
static inline __m256d _mm256_exp2_pd(const __m256d x) {
	return _mm256_exp_pd(_mm256_mul_pd(x, _mm256_const_ln2_pd()));
}

/** @note This function doesn't use AVX for calculations */
static inline __m256d _mm256_exp10_pd(const __m256d x) {
	return _mm256_exp_pd(_mm256_mul_pd(x, _mm256_const_ln10_pd()));
}

/** @note This function doesn't use AVX for calculations */
__m256d _mm256_log_pd(__m256d x);

/** @note This function doesn't use AVX for calculations */
__m256d _mm256_log1p_pd(__m256d x);

/** @note This function doesn't use AVX for calculations */
static inline __m256d _mm256_log2_pd(const __m256d x) {
	return _mm256_exp_pd(_mm256_mul_pd(x, _mm256_const_log2e_pd()));
}

/** @note This function doesn't use AVX for calculations */
static inline __m256d _mm256_log10_pd(const __m256d x) {
	return _mm256_exp_pd(_mm256_mul_pd(x, _mm256_const_log10e_pd()));
}

/** @note This function doesn't use AVX for calculations */
__m256d _mm256_logb_pd(__m256d x);

/** @note This function doesn't use AVX for calculations */
__m256d _mm256_pow_pd(__m256d x, __m256d y);

/** @note This function doesn't use AVX for calculations */
__m256d _mm256_pow_pd_pd(__m256d x,  __m256d y);

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
	return _mm256_div_pd(sin_val, cos_val);
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
		_mm256_add_pd(exp_x, _mm256_div_pd(_mm256_set1_pd(1.0), exp_x)),
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
			_mm256_sub_pd(_mm256_square_pd(x), _mm256_set1_pd(1.0))
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

//------------------------------------------------------------------------------
// __m256d SVML transcendental functions
//------------------------------------------------------------------------------

/** @note This function doesn't use AVX for calculations */
__m256d _mm256_erf_pd(__m256d x);

/** @note This function doesn't use AVX for calculations */
__m256d _mm256_erfc_pd(__m256d x);

/** @note This function doesn't use AVX for calculations */
static inline __m256d _mm256_erfinv_pd(__m256d x) {
	return _mm256_recip_pd(_mm256_erf_pd(x));
}

/** @note This function doesn't use AVX for calculations */
static inline __m256d _mm256_erfcinv_pd(__m256d x) {
	return _mm256_recip_pd(_mm256_erfc_pd(x));
}

/** @note This function doesn't use AVX for calculations */
static inline __m256d _mm256_cdfnorm_pd(__m256d x) {
	return _mm256_mul_pd(
		_mm256_add_pd(
			_mm256_erfc_pd(
				_mm256_mul_pd(
					x,
					// 1.0 / sqrt(2)
					_mm256_set1_pd(0.70710678118654752440084436210485)
				)
			),
			_mm256_set1_pd(1.0)
		),
		// sqrt(pi) * sqrt(2) * 0.5
		_mm256_set1_pd(1.2533141373155002512078826424055)
	);
}

#endif 

#ifdef __cplusplus
	}
#endif

#endif /* FLOAT64_AVX_H */