/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef FLOAT32_AVX_H
#define FLOAT32_AVX_H


/**
 * @brief defines functions and macros for the __m256 type.
 * @note the #ifndef _mm256_func_ps directives can only detect macros as the
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
// __m256 mathematical constants
//------------------------------------------------------------------------------

/**
 * @brief ~2.718281828 Returns the value of euler's number
 */
static inline __m256 _mm256_const_e_ps(void) {
	return _mm256_castsi256_ps(_mm256_set1_epi32((int32_t)0x402DF854));
}

/**
 * @brief ~1.442695041 Returns the value of log2(e)
 */
static inline __m256 _mm256_const_log2e_ps(void) {
	return _mm256_castsi256_ps(_mm256_set1_epi32((int32_t)0x3FB8AA3B));
}

/**
 * @brief ~0.434294482 Returns the value of log10(e)
 */
static inline __m256 _mm256_const_log10e_ps(void) {
	return _mm256_castsi256_ps(_mm256_set1_epi32((int32_t)0x3EDE5BD9));
}

/**
 * @brief ~3.141592654 Returns the value of pi
 */
static inline __m256 _mm256_const_pi_ps(void) {
	return _mm256_castsi256_ps(_mm256_set1_epi32((int32_t)0x40490FDB));
}

/**
 * @brief ~0.318309886 Returns the value of 1 / pi
 */
static inline __m256 _mm256_const_inv_pi_ps(void) {
	return _mm256_castsi256_ps(_mm256_set1_epi32((int32_t)0x3EA2F983));
}

/**
 * @brief ~0.564189584 Returns the value of 1 / sqrt(pi)
 */
static inline __m256 _mm256_const_inv_sqrtpi_ps(void) {
	return _mm256_castsi256_ps(_mm256_set1_epi32((int32_t)0x3F106EBB));
}

/**
 * @brief ~0.693147181 Returns the value of ln(2)
 */
static inline __m256 _mm256_const_ln2_ps(void) {
	return _mm256_castsi256_ps(_mm256_set1_epi32((int32_t)0x3F317218));
}

/**
 * @brief ~2.302585093 Returns the value of ln(10)
 */
static inline __m256 _mm256_const_ln10_ps(void) {
	return _mm256_castsi256_ps(_mm256_set1_epi32((int32_t)0x40135D8E));
}

/**
 * @brief ~1.414213562 Returns the value of sqrt(2)
 */
static inline __m256 _mm256_const_sqrt2_ps(void) {
	return _mm256_castsi256_ps(_mm256_set1_epi32((int32_t)0x3FB504F3));
}

/**
 * @brief ~1.732050808 Returns the value of sqrt(3)
 */
static inline __m256 _mm256_const_sqrt3_ps(void) {
	return _mm256_castsi256_ps(_mm256_set1_epi32((int32_t)0x3FDDB3D7));
}

/**
 * @brief ~0.577350269 Returns the value of 1 / sqrt(3)
 */
static inline __m256 _mm256_const_inv_sqrt3_ps(void) {
	return _mm256_castsi256_ps(_mm256_set1_epi32((int32_t)0x3F13CD3A));
}

/**
 * @brief ~0.577215665 Returns the value of gamma (The Euler–Mascheroni constant)
 */
static inline __m256 _mm256_const_egamma_ps(void) {
	return _mm256_castsi256_ps(_mm256_set1_epi32((int32_t)0x3F13C468));
}

/**
 * @brief ~1.618033989 Returns the value of phi (The golden ratio)
 */
static inline __m256 _mm256_const_phi_ps(void) {
	return _mm256_castsi256_ps(_mm256_set1_epi32((int32_t)0x3FCF1BBD));
}

//------------------------------------------------------------------------------
// __m256 floating point manipulation
//------------------------------------------------------------------------------

/** @brief Returns a __m256 value set to positive infinity */
static inline __m256 _mm256_get_infinity_ps(void) {
	return _mm256_castsi256_ps(_mm256_set1_epi32((int32_t)0x7F800000));
}

/** @brief Returns a __m256 value set to signaling NaN */
static inline __m256 _mm256_get_sNaN_ps(void) {
	return _mm256_castsi256_ps(_mm256_set1_epi32((int32_t)0x7F800001));
}

/** @brief Returns a __m256 value set to quiet NaN */
static inline __m256 _mm256_get_qNaN_ps(void) {
	return _mm256_castsi256_ps(_mm256_set1_epi32((int32_t)0x7FC00001));
}

/** @brief Returns the bitmask for extracting the sign bit */
static inline __m256 _mm256_get_sign_mask_ps(void) {
	return _mm256_castsi256_ps(_mm256_set1_epi32((int32_t)0x80000000));
}

/** @brief Returns the bitmask for extracting the exponent bits */
static inline __m256 _mm256_get_exponent_mask_ps(void) {
	return _mm256_castsi256_ps(_mm256_set1_epi32((int32_t)0x7F800000));
}

/** @brief Returns the bitmask for extracting the mantissa bits */
static inline __m256 _mm256_get_mantissa_mask_ps(void) {
	return _mm256_castsi256_ps(_mm256_set1_epi32((int32_t)0x007FFFFF));
}

/** @brief Extracts the exponent via a bitmask */
static inline __m256 _mm256_extract_exponent_ps(const __m256 x) {
	return _mm256_and_ps(x, _mm256_get_exponent_mask_ps());
}

/** @brief Extracts the mantissa via a bitmask */
static inline __m256 _mm256_extract_mantissa_ps(const __m256 x) {
	return _mm256_and_ps(x, _mm256_get_mantissa_mask_ps());
}

//------------------------------------------------------------------------------
// __m256 floating point classify
//------------------------------------------------------------------------------

/** @brief Returns true if x is negative */
static inline __m256 _mm256_signbit_ps(const __m256 x) {
	return _mm256_cmp_ps(x, _mm256_setzero_ps(), _CMP_LT_OQ);
}

/** @brief Returns true if x is finite */
static inline __m256 _mm256_isfinite_ps(const __m256 x) {
	// extract the exponent, and check that it is not all ones
	__m256 x_exp = _mm256_extract_exponent_ps(x);
	return _mm256_cmp_ps(x_exp, _mm256_get_exponent_mask_ps(), _CMP_NEQ_UQ);
}

/** @brief Returns true if x is +-infinity */
static inline __m256 _mm256_isinf_ps(const __m256 x) {
	return _mm256_cmp_ps(
		_mm256_and_ps(
			x,
			_mm256_castsi256_ps(_mm256_set1_epi32((int32_t)0x7FFFFFFF))
		),
		_mm256_get_infinity_ps(),
	_CMP_EQ_UQ);
}

/** @brief Returns true if x is any kind of NaN */
static inline __m256 _mm256_isnan_ps(const __m256 x) {
	// extract the exponent, and check if it is all ones
	__m256 x_exp = _mm256_cmp_ps(
		_mm256_extract_exponent_ps(x), _mm256_get_exponent_mask_ps(),
	_CMP_EQ_UQ);
	// extract the mantissa, and check that at least one bit is set
	__m256 x_mant = _mm256_cmp_ps(
		_mm256_extract_mantissa_ps(x), _mm256_setzero_ps(),
	_CMP_NEQ_UQ);
	return _mm256_and_ps(x_exp, x_mant);
}

/** @brief Returns true if x is normal */
static inline __m256 _mm256_isnormal_ps(const __m256 x) {
	// extract the exponent, and check that it is not all ones or zeros
	__m256 x_exp = _mm256_extract_exponent_ps(x);
	return _mm256_and_ps(
		_mm256_cmp_ps(x_exp, _mm256_get_exponent_mask_ps(), _CMP_NEQ_UQ),
		_mm256_cmp_ps(x_exp, _mm256_setzero_ps(), _CMP_NEQ_UQ)
	);
}

/** @brief Returns true if x is denormal */
static inline __m256 _mm256_isdenormal_ps(const __m256 x) {
	// check that x is not equal to zero, and that the exponent is all zeros
	__m256 x_exp = _mm256_extract_exponent_pd(x);
	return _mm256_and_ps(
		_mm256_cmp_ps(x, _mm256_setzero_ps(), _CMP_NEQ_UQ),
		_mm256_cmp_ps(x_exp, _mm256_setzero_ps(), _CMP_EQ_UQ)
	);
}

//------------------------------------------------------------------------------
// __m256 comparison
//------------------------------------------------------------------------------

#ifndef _mm256_cmpunord_ps
/** @brief Returns true if either x or y are NaN (Unordered) */
static inline __m256 _mm256_cmpunord_ps(__m256 x, __m256 y) {
	return _mm256_cmp_ps(x, y, _CMP_UNORD_Q);
}
#endif

#ifndef _mm256_cmpord_ps
/** @brief Returns true if both x and y are not NaN (Ordered) */
static inline __m256 _mm256_cmpord_ps(__m256 x, __m256 y) {
	return _mm256_cmp_ps(x, y, _CMP_ORD_Q);
}
#endif

#ifndef _mm256_cmpeq_ps
/** @brief `x == y` ordered equals */
static inline __m256 _mm256_cmpeq_ps(__m256 x, __m256 y) {
	return _mm256_cmp_ps(x, y, _CMP_EQ_OQ);
}
#endif

#ifndef _mm256_cmpneq_ps
/** @brief `x != y` ordered not-equals */
static inline __m256 _mm256_cmpneq_ps(__m256 x, __m256 y) {
	return _mm256_cmp_ps(x, y, _CMP_NEQ_OQ);
}
#endif

#ifndef _mm256_cmplg_ps
/** @brief `x <> y` unordered not-equals */
static inline __m256 _mm256_cmplg_ps(__m256 x, __m256 y) {
	return _mm256_cmp_ps(x, y, _CMP_NEQ_UQ);
}
#endif

#ifndef _mm256_cmpnlg_ps
/** @brief `x !<> y` unordered equals */
static inline __m256 _mm256_cmpnlg_ps(__m256 x, __m256 y) {
	return _mm256_cmp_ps(x, y, _CMP_EQ_UQ);
}
#endif

#ifndef _mm256_cmplt_ps
/** @brief `x < y` ordered less-than */
static inline __m256 _mm256_cmplt_ps(__m256 x, __m256 y) {
	return _mm256_cmp_ps(x, y, _CMP_LT_OQ);
}
#endif

#ifndef _mm256_cmple_ps
/** @brief `x <= y` ordered less-equal */
static inline __m256 _mm256_cmple_ps(__m256 x, __m256 y) {
	return _mm256_cmp_ps(x, y, _CMP_LE_OQ);
}
#endif

#ifndef _mm256_cmpgt_ps
/** @brief `x > y` ordered greater-than */
static inline __m256 _mm256_cmpgt_ps(__m256 x, __m256 y) {
	return _mm256_cmp_ps(x, y, _CMP_GT_OQ);
}
#endif

#ifndef _mm256_cmpge_ps
/** @brief `x >= y` ordered greater-equal */
static inline __m256 _mm256_cmpge_ps(__m256 x, __m256 y) {
	return _mm256_cmp_ps(x, y, _CMP_GE_OQ);
}
#endif

#ifndef _mm256_cmpnlt_ps
/** @brief `!(x < y)` unordered not-less-than */
static inline __m256 _mm256_cmpnlt_ps(__m256 x, __m256 y) {
	return _mm256_cmp_ps(x, y, _CMP_NLT_UQ);
}
#endif

#ifndef _mm256_cmpnle_ps
/** @brief `!(x <= y)` unordered not-less-equal */
static inline __m256 _mm256_cmpnle_ps(__m256 x, __m256 y) {
	return _mm256_cmp_ps(x, y, _CMP_NLE_UQ);
}
#endif

#ifndef _mm256_cmpngt_ps
/** @brief `!(x > y)` unordered not-greater-than */
static inline __m256 _mm256_cmpngt_ps(__m256 x, __m256 y) {
	return _mm256_cmp_ps(x, y, _CMP_NGT_UQ);
}
#endif

#ifndef _mm256_cmpnge_ps
/** @brief `!(x >= y)` unordered not-greater-equal */
static inline __m256 _mm256_cmpnge_ps(__m256 x, __m256 y) {
	return _mm256_cmp_ps(x, y, _CMP_NGE_UQ);
}
#endif

//------------------------------------------------------------------------------
// __m256 math.h comparison
//------------------------------------------------------------------------------

/** @brief Returns true if either x or y are NaN (Unordered) */
static inline __m256 _mm256_isunordered_ps(__m256 x, __m256 y) {
	return _mm256_cmp_ps(x, y, _CMP_UNORD_Q);
}

/** @brief `x <> y` unordered not-equals */
static inline __m256 _mm256_islessgreater_ps(__m256 x, __m256 y) {
	return _mm256_cmp_ps(x, y, _CMP_NEQ_UQ);
}

/** @brief `x < y` ordered less-than */
static inline __m256 _mm256_isless_ps(__m256 x, __m256 y) {
	return _mm256_cmp_ps(x, y, _CMP_LT_OQ);
}

/** @brief `x <= y` ordered less-equal */
static inline __m256 _mm256_islessequal_ps(__m256 x, __m256 y) {
	return _mm256_cmp_ps(x, y, _CMP_LE_OQ);
}

/** @brief `x > y` ordered greater-than */
static inline __m256 _mm256_isgreater_ps(__m256 x, __m256 y) {
	return _mm256_cmp_ps(x, y, _CMP_GT_OQ);
}

/** @brief `x >= y` ordered greater-equal */
static inline __m256 _mm256_isgreaterequal_ps(__m256 x, __m256 y) {
	return _mm256_cmp_ps(x, y, _CMP_GE_OQ);
}

//------------------------------------------------------------------------------
// __m256 math.h functions
//------------------------------------------------------------------------------

#ifndef _mm256_negate_ps 
/**
 * @brief `-x` Negates a __m256 value (Multiplies by -1.0)
 */
static inline __m256 _mm256_negate_ps(__m256 x) {
	// return _mm256_xor_ps(
	// 	x,
	// 	_mm256_castsi256_ps(_mm256_set1_epi32((int32_t)0x80000000))
	// );
	return _mm256_mul_ps(x, _mm256_set1_ps(-1.0f));
}
#endif

#ifndef _mm256_recip_ps 
/**
 * @brief `1 / x` Calculates the reciprocal of a __m256 value
 */
static inline __m256 _mm256_recip_ps(__m256 x) {
	return _mm256_div_ps(_mm256_set1_ps(1.0), x);
}
#endif

#ifndef _mm256_square_ps 
/**
 * @brief `x * x` Squares a __m256 value
 */
static inline __m256 _mm256_square_ps(__m256 x) {
	return _mm256_mul_ps(x, x);
}
#endif

#ifndef _mm256_fabs_ps
/**
 * @brief `|x|` Returns the absolute value of a __m256 value
 * @remarks _mm256_andnot_ps cannot be used because 0x80000000 gets
 * converted from -0.0 to 0.0 on -Ofast
 */
static inline __m256 _mm256_fabs_ps(__m256 x) {
	return _mm256_and_ps(
		x,
		_mm256_castsi256_ps(_mm256_set1_epi32((int32_t)0x7FFFFFFF))
	);
}
#endif

#ifndef _mm256_not_ps
static inline __m256 _mm256_not_ps(__m256 x) {
	return _mm256_xor_ps(
		x,
		_mm256_castsi256_ps(_mm256_set1_epi32((int32_t)0xFFFFFFFF))
	);
}
#endif

static inline __m256 _mm256_copysign_ps(__m256 x, __m256 y) {
	__m256 negate_mask = _mm256_xor_ps(
		_mm256_cmp_ps(x, _mm256_setzero_ps(), _CMP_LT_OQ),
		_mm256_cmp_ps(y, _mm256_setzero_ps(), _CMP_LT_OQ)
	);
	__m256 negate_mul = _mm256_blendv_ps(
		_mm256_set1_ps(1.0f), _mm256_set1_ps(-1.0f), negate_mask
	);
	return _mm256_mul_ps(x, negate_mul);
}

static inline __m256 _mm_fdim_ps(__m256 x, __m256 y) {
	__m256 ret;
	ret = _mm256_sub_ps(x, y);
	// returns true when ret > 0.0 or ret is NaN
	__m256 cmp_nle = _mm256_cmp_ps(ret, _mm256_setzero_ps(), _CMP_NLE_UQ);
	// NaN remains NaN, and -0.0 becomes +0.0
	ret = _mm256_and_ps(ret, cmp_nle);
	return ret;
}

#ifndef _mm256_fmax_ps
/**
 * @brief Returns the fmax of x and y. Correctly handling NaN and signed zeros.
 * You may use _mm256_max_ps as a faster alternative.
 */
static inline __m256 _mm256_fmax_ps(__m256 x, __m256 y) {
	__m256 fmax_cmp =
		_mm256_or_ps(
			_mm256_andnot_ps(
				_mm256_or_ps(
					_mm256_andnot_ps(
						_mm256_signbit_ps(x),
						_mm256_isnan_ps(y)
					),
					_mm256_isnan_ps(x)
				),
				_mm256_cmp_ps(y, x, _CMP_LT_OQ)
			),
			_mm256_cmp_ps(x, y, _CMP_LT_OQ)
		);
	return _mm256_blendv_ps(x, y, fmax_cmp);
}
#endif

#ifndef _mm256_fmin_ps
/**
 * @brief Returns the fmin of x and y. Correctly handling NaN and signed zeros.
 * You may use _mm256_min_ps as a faster alternative.
 */
static inline __m256 _mm256_fmin_ps(__m256 x, __m256 y) {
	__m256 fmax_cmp =
		_mm256_or_ps(
			_mm256_andnot_ps(
				_mm256_or_ps(
					_mm256_andnot_ps(
						_mm256_signbit_ps(x),
						_mm256_isnan_ps(y)
					),
					_mm256_isnan_ps(x)
				),
				_mm256_cmp_ps(y, x, _CMP_GT_OQ)
			),
			_mm256_cmp_ps(x, y, _CMP_GT_OQ)
		);
	return _mm256_blendv_ps(x, y, fmax_cmp);
}
#endif

#ifdef __cplusplus
	}
#endif

#endif /* FLOAT32_AVX_H */
