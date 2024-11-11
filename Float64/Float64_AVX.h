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

#include <stdbool.h>
#include <stdint.h>
#include <math.h>
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
	return _mm256_blendv_pd(
		_mm256_setzero_pd(),
		_mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0xFFFFFFFFFFFFFFFF)),
		x
	);
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

/** @brief Returns true if x is denormal and non-zero */
static inline __m256d _mm256_isdenormal_pd(const __m256d x) {
	// check that x is not equal to zero, and that the exponent is all zeros
	__m256d x_exp = _mm256_extract_exponent_pd(x);
	return _mm256_and_pd(
		_mm256_cmp_pd(x, _mm256_setzero_pd(), _CMP_NEQ_UQ),
		_mm256_cmp_pd(x_exp, _mm256_setzero_pd(), _CMP_EQ_UQ)
	);
}

//------------------------------------------------------------------------------
// __m256d comparison
//------------------------------------------------------------------------------

#ifndef _mm256_cmpunord_pd
/** @brief Returns true if either x or y are NaN (Unordered) */
static inline __m256d _mm256_cmpunord_pd(__m256d x, __m256d y) {
	return _mm256_cmp_pd(x, y, _CMP_UNORD_Q);
}
#endif

#ifndef _mm256_cmpord_pd
/** @brief Returns true if both x and y are not NaN (Ordered) */
static inline __m256d _mm256_cmpord_pd(__m256d x, __m256d y) {
	return _mm256_cmp_pd(x, y, _CMP_ORD_Q);
}
#endif

#ifndef _mm256_cmpeq_pd
/** @brief `x == y` ordered equals */
static inline __m256d _mm256_cmpeq_pd(__m256d x, __m256d y) {
	return _mm256_cmp_pd(x, y, _CMP_EQ_OQ);
}
#endif

#ifndef _mm256_cmpneq_pd
/** @brief `x != y` ordered not-equals */
static inline __m256d _mm256_cmpneq_pd(__m256d x, __m256d y) {
	return _mm256_cmp_pd(x, y, _CMP_NEQ_OQ);
}
#endif

#ifndef _mm256_cmplg_pd
/** @brief `x <> y` unordered not-equals */
static inline __m256d _mm256_cmplg_pd(__m256d x, __m256d y) {
	return _mm256_cmp_pd(x, y, _CMP_NEQ_UQ);
}
#endif

#ifndef _mm256_cmpnlg_pd
/** @brief `x !<> y` unordered equals */
static inline __m256d _mm256_cmpnlg_pd(__m256d x, __m256d y) {
	return _mm256_cmp_pd(x, y, _CMP_EQ_UQ);
}
#endif

#ifndef _mm256_cmplt_pd
/** @brief `x < y` ordered less-than */
static inline __m256d _mm256_cmplt_pd(__m256d x, __m256d y) {
	return _mm256_cmp_pd(x, y, _CMP_LT_OQ);
}
#endif

#ifndef _mm256_cmple_pd
/** @brief `x <= y` ordered less-equal */
static inline __m256d _mm256_cmple_pd(__m256d x, __m256d y) {
	return _mm256_cmp_pd(x, y, _CMP_LE_OQ);
}
#endif

#ifndef _mm256_cmpgt_pd
/** @brief `x > y` ordered greater-than */
static inline __m256d _mm256_cmpgt_pd(__m256d x, __m256d y) {
	return _mm256_cmp_pd(x, y, _CMP_GT_OQ);
}
#endif

#ifndef _mm256_cmpge_pd
/** @brief `x >= y` ordered greater-equal */
static inline __m256d _mm256_cmpge_pd(__m256d x, __m256d y) {
	return _mm256_cmp_pd(x, y, _CMP_GE_OQ);
}
#endif

#ifndef _mm256_cmpnlt_pd
/** @brief `!(x < y)` unordered not-less-than */
static inline __m256d _mm256_cmpnlt_pd(__m256d x, __m256d y) {
	return _mm256_cmp_pd(x, y, _CMP_NLT_UQ);
}
#endif

#ifndef _mm256_cmpnle_pd
/** @brief `!(x <= y)` unordered not-less-equal */
static inline __m256d _mm256_cmpnle_pd(__m256d x, __m256d y) {
	return _mm256_cmp_pd(x, y, _CMP_NLE_UQ);
}
#endif

#ifndef _mm256_cmpngt_pd
/** @brief `!(x > y)` unordered not-greater-than */
static inline __m256d _mm256_cmpngt_pd(__m256d x, __m256d y) {
	return _mm256_cmp_pd(x, y, _CMP_NGT_UQ);
}
#endif

#ifndef _mm256_cmpnge_pd
/** @brief `!(x >= y)` unordered not-greater-equal */
static inline __m256d _mm256_cmpnge_pd(__m256d x, __m256d y) {
	return _mm256_cmp_pd(x, y, _CMP_NGE_UQ);
}
#endif

//------------------------------------------------------------------------------
// __m256d math.h comparison
//------------------------------------------------------------------------------

/** @brief Returns true if either x or y are NaN (Unordered) */
static inline __m256d _mm256_isunordered_pd(__m256d x, __m256d y) {
	return _mm256_cmp_pd(x, y, _CMP_UNORD_Q);
}

/** @brief `x <> y` unordered not-equals */
static inline __m256d _mm256_islessgreater_pd(__m256d x, __m256d y) {
	return _mm256_cmp_pd(x, y, _CMP_NEQ_UQ);
}

/** @brief `x < y` ordered less-than */
static inline __m256d _mm256_isless_pd(__m256d x, __m256d y) {
	return _mm256_cmp_pd(x, y, _CMP_LT_OQ);
}

/** @brief `x <= y` ordered less-equal */
static inline __m256d _mm256_islessequal_pd(__m256d x, __m256d y) {
	return _mm256_cmp_pd(x, y, _CMP_LE_OQ);
}

/** @brief `x > y` ordered greater-than */
static inline __m256d _mm256_isgreater_pd(__m256d x, __m256d y) {
	return _mm256_cmp_pd(x, y, _CMP_GT_OQ);
}

/** @brief `x >= y` ordered greater-equal */
static inline __m256d _mm256_isgreaterequal_pd(__m256d x, __m256d y) {
	return _mm256_cmp_pd(x, y, _CMP_GE_OQ);
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

#ifndef _mm256_not_pd
static inline __m256d _mm256_not_pd(__m256d x) {
	return _mm256_xor_pd(
		x,
		_mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0xFFFFFFFFFFFFFFFF))
	);
}
#endif

static inline __m256d _mm256_copysign_pd(__m256d x, __m256d y) {
	return _mm256_xor_pd(
		y, _mm256_and_pd(
			_mm256_xor_pd(x, y),
			_mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x7FFFFFFFFFFFFFFF))
		)
	);
}

static inline __m256d _mm256_fdim_pd(__m256d x, __m256d y) {
	__m256d ret;
	ret = _mm256_sub_pd(x, y);
	// returns true when ret > 0.0 or ret is NaN
	__m256d cmp_nle = _mm256_cmp_pd(ret, _mm256_setzero_pd(), _CMP_NLE_UQ);
	// NaN remains NaN, and -0.0 becomes +0.0
	ret = _mm256_and_pd(ret, cmp_nle);
	return ret;
}

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
 * https://stackoverflow.com/a/69408295
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

static inline __m256i _internal_mm256_ilogb_pd_epi64(__m256d x) {
	const int64_t float64_bias = 1023;
	#if 0
		/* Ignores denormals and inf */
		__m256i bin_x = _mm256_castpd_si256(x);
		// clear the signbit
		bin_x = _mm256_slli_epi64(bin_x, 1);
		// shift the exponent down
		bin_x = _mm256_slri_epi64(bin_x, 52 + 1);
		bin_x = _mm256_add_epi64(bin_x, _mm256_set1_epi64x(float64_bias));
		return bin_x;
	#else

		// 2 ^ +64
		const __m256d mult_2_p64 = _mm256_set1_pd(1.8446744073709551616e+19);
		
		const __m256d x_isdenorm = _mm256_isdenormal_pd(x);
		__m256i bin_x = _mm256_castpd_si256(_mm256_mul_pd(
			x, _mm256_blendv_pd(_mm256_set1_pd(1.0), mult_2_p64, x_isdenorm)
		));
		
		// clear the signbit
		bin_x = _mm256_slli_epi64(bin_x, 1);
		// shift the exponent down
		bin_x = _mm256_srli_epi64(bin_x, 52 + 1);
		bin_x = _mm256_add_epi64(bin_x, _mm256_set1_epi64x(float64_bias));
		
		// subtracts the exponent shift used for denormal numbers
		bin_x = _mm256_sub_epi64(bin_x,
			_mm256_and_si256(_mm256_set1_epi64x((int64_t)64), _mm256_castpd_si256(x_isdenorm))
		);
		return bin_x;

	#endif
}

/**
 * @brief Computes ilogb(x) using AVX2 integer operations
 * @returns __m256i int64_t
 */
static inline __m256i _mm256_ilogb_pd_epi64(__m256d x) {
	__m256d ret = _mm256_castsi256_pd(_internal_mm256_ilogb_pd_epi64(x));
	// Sets ret to INT64_MIN if x is zero or NaN
	ret = _mm256_blendv_pd(
		ret, _mm256_castsi256_pd(_mm256_set1_epi64x(INT64_MIN)),
		_mm256_or_pd(_mm256_isnan_pd(x), _mm256_cmp_pd(x, _mm256_setzero_pd(), _CMP_EQ_OQ))
	);
	// Sets ret to INT64_MAX if x is infinity
	ret = _mm256_blendv_pd(
		ret, _mm256_castsi256_pd(_mm256_set1_epi64x(INT64_MAX)),
		_mm256_isinf_pd(x)
	);
	return _mm256_castpd_si256(ret);
}

/**
 * @brief Computes ilogb(x) using AVX2 integer operations
 * @returns __m128i int32_t
 */
static inline __m128i _mm256_ilogb_pd_epi32(__m256d x) {
	__m256d ret = _mm256_castsi256_pd(_internal_mm256_ilogb_pd_epi64(x));
	// Sets ret to INT32_MIN if x is zero or NaN
	ret = _mm256_blendv_pd(
		ret, _mm256_castsi256_pd(_mm256_set1_epi64x(INT32_MIN)),
		_mm256_or_pd(_mm256_isnan_pd(x), _mm256_cmp_pd(x, _mm256_setzero_pd(), _CMP_EQ_OQ))
	);
	// Sets ret to INT32_MAX if x is infinity
	ret = _mm256_blendv_pd(
		ret, _mm256_castsi256_pd(_mm256_set1_epi64x(INT32_MAX)),
		_mm256_isinf_pd(x)
	);
	return _internal_mm256_convert_epi64_epi32(_mm256_castpd_si256(ret));
}

#else

	/**
	 * @brief Computes ilogb(x) using SSE2 integer operations
	 * @returns __m256i int64_t
	 */
	static inline __m256i _mm256_ilogb_pd_epi64(__m256d x) {
		__m128i part_0 = _mm_ilogb_pd_epi64(_mm256_extractf128_pd(x, 0));
		__m128i part_1 = _mm_ilogb_pd_epi64(_mm256_extractf128_pd(x, 1));
		return _mm256_set_m128i(part_0, part_1);
	}

	/**
	 * @brief Computes ilogb(x) using SSE2 integer operations
	 * @returns __m128i int32_t
	 */
	static inline __m128i _mm256_ilogb_pd_epi32(__m256d x) {
		return _internal_mm256_convert_epi64_epi32(_mm256_ilogb_pd_epi64(x));
	}

#endif

//------------------------------------------------------------------------------
// __m256d ldexp
//------------------------------------------------------------------------------

#ifdef __AVX2__

/**
 * @brief Computes ldexp(x, expon) with support for denormal numbers.
 * @remarks Uses 5 fp64 multiplications, 4 blendv, 4 int64 comparisons,
 * 5 int64 additions, and 1 int64_t left shfit
 */
static inline __m256d _mm256_ldexp_pd_epi64(__m256d x, __m256i expon) {

	// Update this
	const int64_t float64_bias = 1023;

	// Arbritrary, but should be large and less than ~1024
	const int64_t mult_2_power = 896;
	// 2 ^ +896
	const __m256d mult_2_p896 = _mm256_set1_pd(5.2829453113566524635233978491652e+269);
	// 2 ^ -896
	const __m256d mult_2_n896 = _mm256_set1_pd(1.8928834978668395375564025560288e-270);

	{ /* multiplies by a large power of 2 */
		__m256i test = _mm256_cmpgt_epi64(expon, _mm256_set1_epi64x(mult_2_power - 1));
		x = _mm256_mul_pd(x, _mm256_blendv_pd(_mm256_set1_pd(1.0), mult_2_p896, _mm256_castsi256_pd(test)));
		expon = _mm256_sub_epi64(expon, _mm256_set1_epi64x(mult_2_power));
	}
	{ /* multiplies by a large power of 2 */
		__m256i test = _mm256_cmpgt_epi64(expon, _mm256_set1_epi64x(mult_2_power - 1));
		x = _mm256_mul_pd(x, _mm256_blendv_pd(_mm256_set1_pd(1.0), mult_2_p896, _mm256_castsi256_pd(test)));
		expon = _mm256_sub_epi64(expon, _mm256_set1_epi64x(mult_2_power));
	}
	{ /* divides by a large power of 2 */
		__m256i test = _mm256_cmpgt_epi64(_mm256_set1_epi64x(-mult_2_power + 1), expon);
		x = _mm256_mul_pd(x, _mm256_blendv_pd(mult_2_n896, _mm256_set1_pd(1.0), _mm256_castsi256_pd(test)));
		expon = _mm256_add_epi64(expon, _mm256_set1_epi64x(mult_2_power));
	}
	{ /* divides by a large power of 2 */
		__m256i test = _mm256_cmpgt_epi64(_mm256_set1_epi64x(-mult_2_power + 1), expon);
		x = _mm256_mul_pd(x, _mm256_blendv_pd(mult_2_n896, _mm256_set1_pd(1.0), _mm256_castsi256_pd(test)));
		expon = _mm256_add_epi64(expon, _mm256_set1_epi64x(mult_2_power));
	}

	/* multiplies by the remaining exponent */

	// Creates a normalized number of the form 2^expon
	__m256i bias_expon = _mm256_add_epi64(expon, _mm256_set1_epi64x(float64_bias));
	// fabs clears the signbit
	__m256d mult = _mm256_fabs_pd(_mm256_castsi256_pd(_mm256_slli_epi64(bias_expon, 52)));
	
	return _mm256_mul_pd(x, mult);
}

static inline __m256d _mm256_ldexp_pd_epi32(__m256d x, __m128i expon) {
	return _mm256_ldexp_pd_epi64(x, _mm256_cvtepi32_epi64(expon));
}

#else

/**
 * @brief Computes ldexp(1.0, expon) using SSE4 integer operations
 */
static inline __m256d _mm256_ldexp_pd_epi64(__m256d x, __m256i expon) {
	__m128d part_0 = _mm_ldexp_pd_epi64(_mm256_extractf128_pd(x, 0), _mm256_extractf128_si256(expon, 0));
	__m128d part_1 = _mm_ldexp_pd_epi64(_mm256_extractf128_pd(x, 1), _mm256_extractf128_si256(expon, 1));
	return _mm256_set_m128d(part_0, part_1);
}

/**
 * @brief Computes ldexp(1.0, expon) using SSE4 integer operations
 */
static inline __m256d _mm256_ldexp_pd_epi32(__m256d x, __m128i expon) {
	// Loads the lower half, extending each from int32_t to int64_t
	__m128d part_0 = _mm_ldexp_pd_epi64(_mm256_extractf128_pd(x, 0), _mm_cvtepi32_epi64(expon));
	// Copy the upper half to the lower half
	expon = _mm_move_epi64(expon);
	// Loads the upper half, extending each from int32_t to int64_t
	__m128d part_1 = _mm_ldexp_pd_epi64(_mm256_extractf128_pd(x, 1), _mm_cvtepi32_epi64(expon));
	return _mm256_set_m128d(part_0, part_1);
}

#endif

/**
 * @brief Computes ldexp(x, expon) with support for denormal numbers.
 */
static inline __m256d _mm256_ldexp_pd_i32(__m256d x, int32_t expon) {

	// Arbritrary, but should be large and less than ~1024
	const int32_t mult_2_power = 896;
	// 2 ^ +896
	const __m256d mult_2_p896 = _mm256_set1_pd(5.2829453113566524635233978491652e+269);
	// 2 ^ -896
	const __m256d mult_2_n896 = _mm256_set1_pd(1.8928834978668395375564025560288e-270);
	if (expon == 0) {
		return x;
	}

	if (expon > mult_2_power - 1) {
		x = _mm256_mul_pd(x, mult_2_p896);
		expon -= mult_2_power;
		if (expon > 2 * mult_2_power - 1) {
			x = _mm256_mul_pd(x, mult_2_p896);
			expon -= mult_2_power;
		}

	}
	if (-mult_2_power + 1 > expon) {
		x = _mm256_mul_pd(x, mult_2_n896);
		expon += mult_2_power;
		if (-2 * mult_2_power + 1 > expon) {
			x = _mm256_mul_pd(x, mult_2_n896);
			expon += mult_2_power;
		}
	}

	x = _mm256_mul_pd(x, _mm256_set1_pd(ldexp(1.0, expon)));
	return x;
}

static inline __m256d _mm256_ldexp_pd_i64(__m256d x, int64_t expon) {
	return _mm256_ldexp_pd_i32(x, (int32_t)expon);
}

//------------------------------------------------------------------------------
// __m256d frexp
//------------------------------------------------------------------------------

#ifdef __AVX2__

static inline __m256d _mm256_frexp_pd_epi64(__m256d x, __m256i* const expon) {
	*expon = _mm256_add_epi64(_mm256_ilogb_pd_epi64(x), _mm256_set1_epi64x((int64_t)1));
	/**
	 * Clears the exponent bits of x, then does a bitwise OR so that x will
	 * be inside the range [0.5, 1.0)
	 */
	x = _mm256_andnot_pd(x, _mm256_get_exponent_mask_pd());
	x = _mm256_or_pd(x, _mm256_set1_pd(0.5));
	return x;
}

#else

static inline __m256d _mm256_frexp_pd_epi64(__m256d x, __m256i* const expon) {
	__m128i expon_0, expon_1;
	__m128d part_0 = _mm_frexp_pd_epi64(_mm256_extractf128_pd(x, 0), &expon_0);
	__m128d part_1 = _mm_frexp_pd_epi64(_mm256_extractf128_pd(x, 1), &expon_1);
	*expon = _mm256_set_m128i(expon_0, expon_1);
	return _mm256_set_m128d(part_0, part_1);
}

#endif

static inline __m256d _mm256_frexp_pd_epi32(__m256d x, __m128i* const expon) {
	*expon = _mm_add_epi32(_mm256_ilogb_pd_epi32(x), _mm_set1_epi32((int32_t)1));
	/**
	 * Clears the exponent bits of x, then does a bitwise OR so that x will
	 * be inside the range [0.5, 1.0)
	 */
	__m256d ret;
	ret = _mm256_andnot_pd(x, _mm256_get_exponent_mask_pd());
	ret = _mm256_or_pd(ret, _mm256_set1_pd(0.5));
	// if x is NaN or inf, x is returned instead
	return _mm256_blendv_pd(x, ret, _mm256_isfinite_pd(x));
}

//------------------------------------------------------------------------------
// __m256d nextafter and nexttoward
//------------------------------------------------------------------------------

#ifdef __AVX2__

static inline __m256d _mm256_nextafter_pd(__m256d x, __m256d y) {

	// x > y == -1, otherwise 1
	__m256d increment_direction = _mm256_or_pd(
		_mm256_xor_pd(
			_mm256_isgreater_pd(x, y),
			_mm256_signbit_pd(x)
		),
		_mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x1))
	);
	// Flip the sign bit instead of decrementing for signed zeros. Incrementing is unchanged
	increment_direction = _mm256_blendv_pd(
		increment_direction,
		_mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x8000000000000000)),
		_mm256_cmp_pd(x, _mm256_setzero_pd(), _CMP_EQ_OQ)
	);
	__m256d nextafter_ret = _mm256_castsi256_pd(
		_mm256_add_epi64(
			_mm256_castpd_si256(x),
			_mm256_castpd_si256(increment_direction)
		)
	);
	/**
	 * if x is NaN, the arithmetic operations should keep it as NaN
	 * if y is NaN, or if x == y, return y instead of nextafter_ret
	 */
	return _mm256_blendv_pd(
		nextafter_ret, y,
		_mm256_or_pd(_mm256_isnan_pd(y), _mm256_cmp_pd(x, y, _CMP_EQ_OQ))
	);
}

#else

static inline __m256d _mm256_nextafter_pd(__m256d x, __m256d y) {
	__m128d part_0 = _mm_nextafter_pd(_mm256_extractf128_pd(x, 0), _mm256_extractf128_pd(y, 0));
	__m128d part_1 = _mm_nextafter_pd(_mm256_extractf128_pd(x, 1), _mm256_extractf128_pd(y, 1));
	return _mm256_set_m128d(part_0, part_1);
}

#endif

static inline __m256d _mm256_nexttoward_pd(__m256d x, long double y) {
	double double_y = (double)y;
	long double rounded_y = (long double)double_y;
	
	const bool rounding_occured = islessgreater(rounded_y, y);
	
	__m256d input_y = _mm256_set1_pd(double_y);

	__m256d cmp_eq = _mm256_cmp_pd(x, input_y, _CMP_EQ_OQ);
	
	if (rounding_occured) {
		double nextafter_direction = isless(rounded_y, y) ?
			(double)-INFINITY :
			(double)INFINITY;
		
		input_y = _mm256_blendv_pd(
			input_y,
			_mm256_set1_pd(nextafter(double_y, nextafter_direction)),
			cmp_eq
		);
	}
	return _mm256_nextafter_pd(x, input_y);
}

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

__m256d _mm256_cbrt_pd(__m256d x);

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

__m256d _mm256_exp_pd(__m256d x);

__m256d _mm256_expm1_pd(__m256d x);

static inline __m256d _mm256_exp2_pd(const __m256d x) {
	return _mm256_exp_pd(_mm256_mul_pd(x, _mm256_const_ln2_pd()));
}

static inline __m256d _mm256_exp10_pd(const __m256d x) {
	return _mm256_exp_pd(_mm256_mul_pd(x, _mm256_const_ln10_pd()));
}

__m256d _mm256_log_pd(__m256d x);

/** @note This is not an accurate implementation of log1p */
static inline __m256d _mm256_log1p_pd(__m256d x) {
	return _mm256_log_pd(_mm256_add_pd(x, _mm256_set1_pd(1.0)));
}

static inline __m256d _mm256_log2_pd(const __m256d x) {
	return _mm256_exp_pd(_mm256_mul_pd(x, _mm256_const_log2e_pd()));
}

static inline __m256d _mm256_log10_pd(const __m256d x) {
	return _mm256_exp_pd(_mm256_mul_pd(x, _mm256_const_log10e_pd()));
}

/** @note This function doesn't use AVX for calculations */
__m256d _mm256_pow_pd(__m256d x, __m256d y);

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

#if 0

/** @note This function doesn't use AVX for calculations */
static inline __m256d _mm256_erfinv_pd(__m256d x);

/** @note This function doesn't use AVX for calculations */
static inline __m256d _mm256_erfcinv_pd(__m256d x);

#endif

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

//------------------------------------------------------------------------------
// __m256d other functions
//------------------------------------------------------------------------------

static inline __m256d _mm256_clamp_pd(__m256d x, __m256d min_val, __m256d max_val) {
	x = _mm256_max_pd(x, min_val);
	x = _mm256_min_pd(x, max_val);
	return x;
}

#ifndef __FMA__
/**
 * @brief Naive implementation of lerp (using FMA)
 */
static inline __m256d _mm256_lerp_pd(__m256d a, __m256d b, __m256d t) {
	// a + t * (b - a) == a + t * b - t * a
	__m256d ret = _mm256_fmadd_pd(t, _mm256_sub_pd(b, a), a);
	ret = _mm256_blendv_pd(ret, a, _mm256_cmp_pd(t, _mm256_setzero_pd(), _CMP_LE_OQ));
	ret = _mm256_blendv_pd(ret, b, _mm256_cmp_pd(t, _mm256_set1_pd(1.0), _CMP_GE_OQ));
	return ret;
}
#else
/**
 * @brief Naive implementation of lerp (without FMA)
 */
static inline __m256d _mm256_lerp_pd(__m256d a, __m256d b, __m256d t) {
	// a + t * (b - a) == a + t * b - t * a
	__m256d ret = _mm256_add_pd(_mm256_mul_pd(t, _mm256_sub_pd(b, a)), a);
	ret = _mm256_blendv_pd(ret, a, _mm256_cmp_pd(t, _mm256_setzero_pd(), _CMP_LE_OQ));
	ret = _mm256_blendv_pd(ret, b, _mm256_cmp_pd(t, _mm256_set1_pd(1.0), _CMP_GE_OQ));
	return ret;
}
#endif

#ifdef __AVX2__
/**
 * @brief reverses the elements inside a __m256d
 * @author https://stackoverflow.com/questions/13422747/
 */
static inline __m256d _mm256_reverse_pd(__m256d x) {
	return _mm256_permute4x64_pd(x, _MM_SHUFFLE(0, 1, 2, 3));
}
#else
/**
 * @brief reverses the elements inside a __m256d
 * @author https://stackoverflow.com/questions/13422747/
 */
static inline __m256d _mm256_reverse_pd(__m256d x) {
	x = _mm256_permute2f128_pd(x, x, 1);
    x = _mm256_permute_pd(x, 5);
    return x;
}
#endif

#ifdef __cplusplus
	}
#endif

#endif /* FLOAT64_AVX_H */
