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

#include <emmintrin.h>
#if (!defined(__AVX__) && defined(__GNUC__))
	#error "__AVX__ is not enabled in your compiler. Try -mavx"
#endif

#include <stdint.h>
#include <immintrin.h>

#include "Float64_SSE2.h"

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

/** @brief Returns a __m256d value set to positive infinity */
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

/** @brief Returns the bitmask for extracting the sign bit */
static inline __m256d _mm256_get_sign_mask_pd(void) {
	return _mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x8000000000000000));
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
	// extract the exponent, and check that it is not all ones or zeros
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
// __m256d float utilities
//------------------------------------------------------------------------------

#if defined(__AVX512F__) && defined(__AVX512VL__)

/**
 * @brief Truncates __m256i int64_t to a __m128i int32_t using intrinsics
 * present in AVX512F + AVX512VL
 */
static inline __m128i _internal_mm256_convert_epi64_epi32(const __m256i x) {
	return _mm256_cvtepi64_epi32(x);
}

#else  

/**
 * @brief Truncates __m256i int64_t to a __m128i int32_t using AVX instead
 * of AVX512F + AVX512VL
 * @author Taken from stackoverflow:
 * https://stackoverflow.com/a/69408295/19507346
 */
static inline __m128i _internal_mm256_convert_epi64_epi32(const __m256i x) {
	__m256 vf = _mm256_castsi256_ps(x);
	__m128 hi = _mm256_extractf128_ps(vf, 1);
	__m128 lo = _mm256_castps256_ps128(vf);
	__m128 packed = _mm_shuffle_ps(lo, hi, _MM_SHUFFLE(2, 0, 2, 0));
	return _mm_castps_si128(packed);
}

#endif

//------------------------------------------------------------------------------
// __m256d ilogb
//------------------------------------------------------------------------------

#ifdef __AVX2__

	/**
	 * @brief Computes ilogb(x) using AVX2 integer operations
	 * @returns sign extended __m128i int32_t
	 */
	static inline __m128i _mm256_ilogb_pd_epi32(__m256d x) {
		// shifts the exponent into the lower half of the int64_t
		__m256i mask = _mm256_srli_epi64(_mm256_castpd_si256(x), 31);
		__m128i packed = _internal_mm256_convert_epi64_epi32(mask);
		// sign extends
		return _mm_srai_epi32(packed, 21);
	}

	/**
	 * @brief Computes ilogb(x) using AVX2 integer operations
	 * @returns sign extended __m256i int64_t
	 */
	static inline __m256i _mm256_ilogb_pd_epi64(const __m256d x) {
		return _mm256_cvtepi32_epi64(_mm256_ilogb_pd_epi32(x));
	}

	/**
	 * @brief Computes ilogb(x) using AVX2 integer operations
	 * @returns zero extended __m256i uint64_t
	 */
	static inline __m256i _mm256_ilogb_pd_epu64(__m256d x) {
		__m256i ret = _mm256_castpd_si256(_mm256_andnot_pd(
			x, _mm256_get_sign_mask_pd()
		));
		return _mm256_srli_epi64(ret, 52);
	}
	
	/**
	 * @brief Computes ilogb(x) using AVX2 integer operations
	 * @returns zero extended __m128i uint32_t
	 */
	static inline __m128i _mm256_ilogb_pd_epu32(__m256d x) {
		return _internal_mm256_convert_epi64_epi32(_mm256_ilogb_pd_epu64(x));
	}

#else

	/**
	 * @brief Computes ilogb(x) using SSE2 integer operations
	 * @returns sign extended __m256i int64_t
	 */
	static inline __m256i _mm256_ilogb_pd_epi64(__m256d x) {
		__m128i part_0 = _mm_ilogb_pd_epi64(_mm256_extractf128_pd(x, 0));
		__m128i part_1 = _mm_ilogb_pd_epi64(_mm256_extractf128_pd(x, 1));
		return _mm256_set_m128i(part_0, part_1);
	}

	/**
	 * @brief Computes ilogb(x) using SSE2 integer operations
	 * @returns sign extended __m128i int32_t
	 */
	static inline __m128i _mm256_ilogb_pd_epi32(__m256d x) {
		return _internal_mm256_convert_epi64_epi32(_mm256_ilogb_pd_epi64(x));
	}

	/**
	 * @brief Computes ilogb(x) using SSE2 integer operations
	 * @returns zero extended __m256i uint64_t
	 */
	static inline __m256i _mm256_ilogb_pd_epu64(__m256d x) {
		__m128i part_0 = _mm_ilogb_pd_epu64(_mm256_extractf128_pd(x, 0));
		__m128i part_1 = _mm_ilogb_pd_epu64(_mm256_extractf128_pd(x, 1));
		return _mm256_set_m128i(part_0, part_1);
	}
	
	/**
	 * @brief Computes ilogb(x) using SSE2 integer operations
	 * @returns zero extended __m128i uint32_t
	 */
	static inline __m128i _mm256_ilogb_pd_epu32(__m256d x) {
		return _internal_mm256_convert_epi64_epi32(_mm256_ilogb_pd_epu64(x));
	}

#endif

//------------------------------------------------------------------------------
// __m256d ldexp
//------------------------------------------------------------------------------

#ifdef __AVX2__

	/**
	 * @brief Computes ldexp(1.0, expon) using AVX2 integer operations
	 */
	static inline __m256d _mm256_ldexp1_pd_epi64(__m256i expon) {
		// Adds to the exponent bits of an ieee double
		return _mm256_castsi256_pd(_mm256_add_epi64(
			_mm256_castpd_si256(_mm256_set1_pd(1.0)), _mm256_slli_epi64(expon, 52)
		));
	}

	/**
	 * @brief Computes ldexp(1.0, expon) using AVX2 integer operations
	 */
	static inline __m256d _mm256_ldexp1_pd_epi32(__m128i expon) {
		return _mm256_ldexp1_pd_epi64(_mm256_cvtepi32_epi64(expon));
	}

	/**
	 * @brief Computes ldexp(1.0, expon) using AVX2 integer operations
	 */
	static inline __m256d _mm256_ldexp1_pd_pd(__m256d expon) {
		return _mm256_ldexp1_pd_epi64(
			_mm256_cvtepi32_epi64(_mm256_cvttpd_epi32(expon))
		);
	}

#else

	/**
	 * @brief Computes ldexp(1.0, expon) using SSE2 integer operations
	 */
	static inline __m256d _mm256_ldexp1_pd_epi64(__m256i expon) {
		__m128d part_0 = _mm_ldexp1_pd_epi64(_mm256_extractf128_si256(expon, 0));
		__m128d part_1 = _mm_ldexp1_pd_epi64(_mm256_extractf128_si256(expon, 1));
		return _mm256_set_m128d(part_0, part_1);
	}

	/**
	 * @brief Computes ldexp(1.0, expon) using SSE2 integer operations
	 */
	static inline __m256d _mm256_ldexp1_pd_epi32(__m128i expon) {
		// Turns ABCD---- into -A-B-C-D
		__m256i extend = _mm256_set_m128i(
			_mm_castps_si128(_mm_permute_ps(_mm_castsi128_ps(expon), 0x50)),
			_mm_castps_si128(_mm_permute_ps(_mm_castsi128_ps(expon), 0xFA))
		);
		extend = _mm256_castps_si256(_mm256_and_ps(
			_mm256_castsi256_ps(extend), _mm256_castsi256_ps(_mm256_set1_epi32(0x0000FFFF))
		));
		
		return _mm256_ldexp1_pd_epi64(extend);
	}
	
	/**
	 * @brief Computes ldexp(1.0, expon) using SSE2 integer operations
	 */
	static inline __m256d _mm256_ldexp1_pd_pd(__m256d expon) {
		return _mm256_ldexp1_pd_epi32(_mm256_cvttpd_epi32(expon));
	}

#endif

/**
 * @brief This is an internal funciton, do NOT call it directly.
 */
static inline __m256d _internal_mm256_ldexp_pd(__m256d x, __m256d expon) {
	__m256d x_mult = _mm256_and_pd(
		expon,
		// sign bit and exponent mask
		_mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0xFFF0000000000000))
	);
	__m256d ret = _mm256_mul_pd(x, x_mult);
	__m256d err_cmp = _mm256_cmp_pd(
		_mm256_fabs_pd(x_mult),
		_mm256_fabs_pd(ret),
		_CMP_GT_OQ
	);
	
	__m256d err_ret = _mm256_blendv_pd(
		_mm256_setzero_pd(), _mm256_get_infinity_pd(),
	err_cmp);
	// blendv checks the most significant bit
	return _mm256_blendv_pd(ret, err_ret, x_mult);
}

/**
 * @brief Computes ldexp(x, expon)
 * @note The result may be undefined if expon is >= 1024 or if expon <= -1024
 */
static inline __m256d _mm256_ldexp_pd_epi64(__m256d x, __m256i expon) {
	return _internal_mm256_ldexp_pd(x, _mm256_ldexp1_pd_epi64(expon));
}

/**
 * @brief Computes ldexp(x, expon)
 * @note The result may be undefined if expon is >= 1024 or if expon <= -1024
 */
static inline __m256d _mm256_ldexp_pd_epi32(__m256d x, __m128i expon) {
	return _internal_mm256_ldexp_pd(x, _mm256_ldexp1_pd_epi32(expon));
}

/**
 * @brief Computes ldexp(x, expon)
 * @note The result may be undefined if expon is >= 1024 or if expon <= -1024
 */
static inline __m256d _mm256_ldexp_pd_pd(__m256d x, __m256d expon) {
	return _internal_mm256_ldexp_pd(x, _mm256_ldexp1_pd_pd(expon));
}

//------------------------------------------------------------------------------
// __m256d frexp
//------------------------------------------------------------------------------

#ifdef __AVX2__

static inline __m256d _mm256_frexp_pd_epi64(__m256d x, __m256i* const expon) {
	__m256d ret;
	__m256i binary_log = _mm256_add_epi64(_mm256_ilogb_pd_epi64(x), _mm256_set1_epi64x(1));
	*expon = binary_log;
	// negates
	_mm256_sub_epi64(_mm256_ilogb_pd_epi64(x), _mm256_set1_epi64x(2));
	_mm256_andnot_si256(binary_log, _mm256_setzero_si256());
	ret = _mm256_ldexp_pd_epi64(x, binary_log);
	return ret;
}

static inline __m256d _mm256_frexp_pd_epi32(__m256d x, __m128i* const expon) {
	__m256d ret;
	__m128i binary_log = _mm_add_epi32(_mm256_ilogb_pd_epi32(x), _mm_set1_epi32(1));
	*expon = binary_log;
	// negates
	_mm_sub_epi32(_mm256_ilogb_pd_epi32(x), _mm_set1_epi32(2));
	_mm_andnot_si128(binary_log, _mm_setzero_si128());
	ret = _mm256_ldexp_pd_epi32(x, binary_log);
	return ret;
}

static inline __m256d _internal_mm256_frexp_pd_epi64(__m256d x, __m256i* const expon, __m256i* const logb_ret) {
	__m256d ret;
	__m256i binary_log = _mm256_add_epi64(_mm256_ilogb_pd_epi64(x), _mm256_set1_epi64x(1));
	*expon = binary_log;
	// negates
	_mm256_sub_epi64(_mm256_ilogb_pd_epi64(x), _mm256_set1_epi64x(2));
	_mm256_andnot_si256(binary_log, _mm256_setzero_si256());
	ret = _mm256_ldexp_pd_epi64(x, binary_log);
	*logb_ret = binary_log;
	return ret;
}

static inline __m256d _internal_mm256_frexp_pd_epi32(__m256d x, __m128i* const expon, __m128i* const logb_ret) {
	__m256d ret;
	__m128i binary_log = _mm_add_epi32(_mm256_ilogb_pd_epi32(x), _mm_set1_epi32(1));
	*expon = binary_log;
	// negates
	_mm_sub_epi32(_mm256_ilogb_pd_epi32(x), _mm_set1_epi32(2));
	_mm_andnot_si128(binary_log, _mm_setzero_si128());
	ret = _mm256_ldexp_pd_epi32(x, binary_log);
	*logb_ret = binary_log;
	return ret;
}

#else

static inline __m256d _mm256_frexp_pd_epi32(__m256d x, __m128i* const expon) {
	__m256d ret;
	__m128 binary_log = _mm_add_ps(_mm_cvtepi32_ps(_mm256_ilogb_pd_epi32(x)), _mm_set1_ps(1.0f));
	if (expon != NULL) { *expon = _mm_cvtps_epi32(binary_log); }
	// negates
	binary_log = _mm_mul_ps(binary_log, _mm_set1_ps(-1.0f));
	ret = _mm256_ldexp_pd_epi32(x, _mm_cvtps_epi32(binary_log));
	return ret;
}

static inline __m256d _mm256_frexp_pd_epi64(__m256d x, __m256i* const expon) {
	__m128i temp_expon;
	__m256d ret = _mm256_frexp_pd_epi32(x, &temp_expon);
	if (expon != NULL) { *expon = _mm256_cvtepi32_epi64(temp_expon); }
	return ret;
}

static inline __m256d _internal_mm256_frexp_pd_epi32(__m256d x, __m128i* const expon, __m128i* const logb_ret) {
	__m256d ret;
	__m128 binary_log = _mm_add_ps(_mm_cvtepi32_ps(_mm256_ilogb_pd_epi32(x)), _mm_set1_ps(1.0f));
	*expon = _mm_cvtps_epi32(binary_log);
	// negates
	binary_log = _mm_mul_ps(binary_log, _mm_set1_ps(-1.0f));
	*logb_ret = _mm_cvtps_epi32(binary_log);
	ret = _mm256_ldexp_pd_epi32(x, *logb_ret);
	return ret;
}

static inline __m256d _internal_mm256_frexp_pd_epi64(__m256d x, __m256i* const expon, __m256i* const logb_ret) {
	__m128i temp_expon, temp_logb_ret;
	__m256d ret = _internal_mm256_frexp_pd_epi32(x, &temp_expon, &temp_logb_ret);
	*expon = _mm256_cvtepi32_epi64(temp_expon);
	*logb_ret = _mm256_cvtepi32_epi64(temp_logb_ret);
	return ret;
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
__m256d _mm256_tgamma_pd(__m256d x);

/** @note This function doesn't use AVX for calculations */
__m256d _mm256_lgamma_pd(__m256d x);

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
