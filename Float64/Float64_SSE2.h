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

#ifdef __SSE4_1__
#include <smmintrin.h>
#endif
#ifdef __SSE4_2__
#include <nmmintrin.h>
#endif

#if (!defined(__SSE2__) && defined(__GNUC__))
	#error "__SSE2__ is not enabled in your compiler. Try -msse2"
#endif

#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------------------
// __m128d mathematical constants
//------------------------------------------------------------------------------

/**
 * @brief ~2.718281828 Returns the value of euler's number
 */
static inline __m128d _mm_const_e_pd(void) {
	return _mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x4005BF0A8B145769));
}

/**
 * @brief ~1.442695041 Returns the value of log2(e)
 */
static inline __m128d _mm_const_log2e_pd(void) {
	return _mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x3FF71547652B82FE));
}

/**
 * @brief ~0.434294482 Returns the value of log10(e)
 */
static inline __m128d _mm_const_log10e_pd(void) {
	return _mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x3FDBCB7B1526E50E));
}

/**
 * @brief ~3.141592654 Returns the value of pi
 */
static inline __m128d _mm_const_pi_pd(void) {
	return _mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x400921FB54442D18));
}

/**
 * @brief ~0.318309886 Returns the value of 1 / pi
 */
static inline __m128d _mm_const_inv_pi_pd(void) {
	return _mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x3FD45F306DC9C883));
}

/**
 * @brief ~0.564189584 Returns the value of 1 / sqrt(pi)
 */
static inline __m128d _mm_const_inv_sqrtpi_pd(void) {
	return _mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x3FE20DD750429B6D));
}

/**
 * @brief ~0.693147181 Returns the value of ln(2)
 */
static inline __m128d _mm_const_ln2_pd(void) {
	return _mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x3FE62E42FEFA39EF));
}

/**
 * @brief ~2.302585093 Returns the value of ln(10)
 */
static inline __m128d _mm_const_ln10_pd(void) {
	return _mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x40026BB1BBB55516));
}

/**
 * @brief ~1.414213562 Returns the value of sqrt(2)
 */
static inline __m128d _mm_const_sqrt2_pd(void) {
	return _mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x3FF6A09E667F3BCD));
}

/**
 * @brief ~1.732050808 Returns the value of sqrt(3)
 */
static inline __m128d _mm_const_sqrt3_pd(void) {
	return _mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x3FFBB67AE8584CAA));
}

/**
 * @brief ~0.577350269 Returns the value of 1 / sqrt(3)
 */
static inline __m128d _mm_const_inv_sqrt3_pd(void) {
	return _mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x3FE279A74590331C));
}

/**
 * @brief ~0.577215665 Returns the value of gamma (The Euler–Mascheroni constant)
 */
static inline __m128d _mm_const_egamma_pd(void) {
	return _mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x3FE2788CFC6FB619));
}

/**
 * @brief ~1.618033989 Returns the value of phi (The golden ratio)
 */
static inline __m128d _mm_const_phi_pd(void) {
	return _mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x3FF9E3779B97F4A8));
}

//------------------------------------------------------------------------------
// __m128d floating point manipulation
//------------------------------------------------------------------------------

/** @brief Returns a __m128d value set to positive infinity */
static inline __m128d _mm_get_infinity_pd(void) {
	return _mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x7FF0000000000000));
}

/** @brief Returns a __m128d value set to signaling NaN */
static inline __m128d _mm_get_sNaN_pd(void) {
	return _mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x7FF0000000000001));
}

/** @brief Returns a __m128d value set to quiet NaN */
static inline __m128d _mm_get_qNaN_pd(void) {
	return _mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x7FF8000000000001));
}

/** @brief Returns the bitmask for extracting the sign bit */
static inline __m128d _mm_get_sign_mask_pd(void) {
	return _mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x8000000000000000));
}

/** @brief Returns the bitmask for extracting the exponent bits */
static inline __m128d _mm_get_exponent_mask_pd(void) {
	return _mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x7FF0000000000000));
}

/** @brief Returns the bitmask for extracting the mantissa bits */
static inline __m128d _mm_get_mantissa_mask_pd(void) {
	return _mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x000FFFFFFFFFFFFF));
}

/** @brief Extracts the exponent via a bitmask */
static inline __m128d _mm_extract_exponent_pd(const __m128d x) {
	return _mm_and_pd(x, _mm_get_exponent_mask_pd());
}

/** @brief Extracts the mantissa via a bitmask */
static inline __m128d _mm_extract_mantissa_pd(const __m128d x) {
	return _mm_and_pd(x, _mm_get_mantissa_mask_pd());
}

//------------------------------------------------------------------------------
// __m128d floating point classify
//------------------------------------------------------------------------------

#ifdef __SSE4_1__

/** @brief Returns true if x is negative */
static inline __m128d _mm_signbit_pd(const __m128d x) {
	return _mm_blendv_pd(
		_mm_setzero_pd(),
		_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0xFFFFFFFFFFFFFFFF)),
		x
	);
}

#else

/** @brief Returns true if x is negative */
static inline __m128d _mm_signbit_pd(const __m128d x) {
	/**
	 * Extracts the signbit from x, and performs a bitwise OR with 1.0, setting
	 * the value to be either +1.0 or -1.0
	 */
	return
		_mm_cmpeq_pd(
			_mm_or_pd(
				_mm_and_pd(x, _mm_get_sign_mask_pd()), _mm_set1_pd(1.0)
			),
			_mm_set1_pd(-1.0)
		);
}

#endif

/** @brief Returns true if x is finite */
static inline __m128d _mm_isfinite_pd(const __m128d x) {
	// extract the exponent, and check that it is not all ones
	__m128d x_exp = _mm_extract_exponent_pd(x);
	return _mm_cmpneq_pd(x_exp, _mm_get_exponent_mask_pd());
}

/** @brief Returns true if x is +-infinity */
static inline __m128d _mm_isinf_pd(const __m128d x) {
	return _mm_cmpeq_pd(
		_mm_and_pd(
			x,
			_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x7FFFFFFFFFFFFFFF))
		),
		_mm_get_infinity_pd()
	);
}

/** @brief Returns true if x is any kind of NaN */
static inline __m128d _mm_isnan_pd(const __m128d x) {
	// extract the exponent, and check if it is all ones
	__m128d x_exp = _mm_cmpeq_pd(
		_mm_extract_exponent_pd(x), _mm_get_exponent_mask_pd()
	);
	// extract the mantissa, and check that at least one bit is set
	__m128d x_mant = _mm_cmpneq_pd(
		_mm_extract_mantissa_pd(x), _mm_setzero_pd()
	);
	return _mm_and_pd(x_exp, x_mant);
}

/** @brief Returns true if x is normal */
static inline __m128d _mm_isnormal_pd(const __m128d x) {
	// extract the exponent, and check that it is not all ones or zeros
	__m128d x_exp = _mm_extract_exponent_pd(x);
	return _mm_and_pd(
		_mm_cmpneq_pd(x_exp, _mm_get_exponent_mask_pd()),
		_mm_cmpneq_pd(x_exp, _mm_setzero_pd())
	);
}

/** @brief Returns true if x is denormal */
static inline __m128d _mm_isdenormal_pd(const __m128d x) {
	// check that x is not equal to zero, and that the exponent is all zeros
	__m128d x_exp = _mm_extract_exponent_pd(x);
	return _mm_and_pd(
		_mm_cmpneq_pd(x, _mm_setzero_pd()),
		_mm_cmpeq_pd(x_exp, _mm_setzero_pd())
	);
}

//------------------------------------------------------------------------------
// __m128d comparison
//------------------------------------------------------------------------------

#ifdef __AVX__

	#ifndef _mm_cmplg_pd
	/** @brief `x <> y` unordered not-equals */
	static inline __m128d _mm_cmplg_pd(__m128d x, __m128d y) {
		return _mm_cmp_pd(x, y, _CMP_NEQ_UQ);
	}
	#endif

	#ifndef _mm_cmpnlg_pd
	/** @brief `x !<> y` unordered equals */
	static inline __m128d _mm_cmpnlg_pd(__m128d x, __m128d y) {
		return _mm_cmp_pd(x, y, _CMP_EQ_UQ);
	}
	#endif

#else

	#ifndef _mm_cmplg_pd
	/** @brief `x <> y` unordered not-equals */
	static inline __m128d _mm_cmplg_pd(__m128d x, __m128d y) {
		return _mm_or_pd(_mm_cmplt_pd(x, y), _mm_cmpgt_pd(x, y));
	}
	#endif

	#ifndef _mm_cmpnlg_pd
	/** @brief `x !<> y` unordered equals */
	static inline __m128d _mm_cmpnlg_pd(__m128d x, __m128d y) {
		return _mm_and_pd(_mm_cmpnlt_pd(x, y), _mm_cmpngt_pd(x, y));
	}
	#endif

#endif

//------------------------------------------------------------------------------
// __m128d math.h comparison
//------------------------------------------------------------------------------

/** @brief Returns true if either x or y are NaN (Unordered) */
static inline __m128d _mm_isunordered_pd(__m128d x, __m128d y) {
	return _mm_cmpunord_pd(x, y);
}

/** @brief `x <> y` unordered not-equals */
static inline __m128d _mm_islessgreater_pd(__m128d x, __m128d y) {
	return _mm_cmplg_pd(x, y);
}

/** @brief `x < y` ordered less-than */
static inline __m128d _mm_isless_pd(__m128d x, __m128d y) {
	return _mm_cmplt_pd(x, y);
}

/** @brief `x <= y` ordered less-equal */
static inline __m128d _mm_islessequal_pd(__m128d x, __m128d y) {
	return _mm_cmple_pd(x, y);
}

/** @brief `x > y` ordered greater-than */
static inline __m128d _mm_isgreater_pd(__m128d x, __m128d y) {
	return _mm_cmpgt_pd(x, y);
}

/** @brief `x >= y` ordered greater-equal */
static inline __m128d _mm_isgreaterequal_pd(__m128d x, __m128d y) {
	return _mm_cmpge_pd(x, y);
}

//------------------------------------------------------------------------------
// __m128d math.h functions
//------------------------------------------------------------------------------

#ifndef _mm_negate_pd 
/**
 * @brief `-x` Negates a __m128d value (Multiplies by -1.0)
 */
static inline __m128d _mm_negate_pd(__m128d x) {
	// return _mm_xor_pd(
	// 	x,
	// 	_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x8000000000000000))
	// );
	return _mm_mul_pd(x, _mm_set1_pd(-1.0));
}
#endif

#ifndef _mm_recip_pd 
/**
 * @brief `1 / x` Calculates the reciprocal of a __m128d value
 */
static inline __m128d _mm_recip_pd(__m128d x) {
	return _mm_div_pd(_mm_set1_pd(1.0), x);
}
#endif

#ifndef _mm_square_pd 
/**
 * @brief `x * x` Squares a __m128d value
 */
static inline __m128d _mm_square_pd(__m128d x) {
	return _mm_mul_pd(x, x);
}
#endif

#ifndef _mm_fabs_pd
/**
 * @brief `|x|` Returns the absolute value of a __m128d value
 * @remarks _mm_andnot_pd cannot be used because 0x8000000000000000 gets
 * converted from -0.0 to 0.0 on -Ofast
 */
static inline __m128d _mm_fabs_pd(__m128d x) {
	return _mm_and_pd(
		x,
		_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x7FFFFFFFFFFFFFFF))
	);
}
#endif

#ifndef _mm_not_pd
static inline __m128d _mm_not_pd(__m128d x) {
	return _mm_xor_pd(
		x,
		_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0xFFFFFFFFFFFFFFFF))
	);
}
#endif

static inline __m128d _mm_copysign_pd(__m128d x, __m128d y) {
	return _mm_xor_pd(
		x, _mm_and_pd(
			_mm_xor_pd(x, y),
			_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x7FFFFFFFFFFFFFFF))
		)
	);
}

#ifdef __SSE4_1__

static inline __m128d _mm_fdim_pd(__m128d x, __m128d y) {
	__m128d ret;
	ret = _mm_sub_pd(x, y);
	__m128d cmp_gt = _mm_cmp_pd(x, y, _CMP_GT_OS);
	ret = _mm_blendv_pd(ret, _mm_setzero_pd(), cmp_gt);
	return ret;
}

#endif

#ifdef __SSE4_1__

#ifndef _mm_fmax_pd
/**
 * @brief Returns the fmax of x and y. Correctly handling NaN and signed zeros.
 * You may use _mm_max_pd as a faster alternative.
 */
static inline __m128d _mm_fmax_pd(__m128d x, __m128d y) {
	__m128d fmax_cmp =
		_mm_or_pd(
			_mm_andnot_pd(
				_mm_or_pd(
					_mm_andnot_pd(
						_mm_signbit_pd(x),
						_mm_isnan_pd(y)
					),
					_mm_isnan_pd(x)
				),
				_mm_cmp_pd(y, x, _CMP_LT_OQ)
			),
			_mm_cmp_pd(x, y, _CMP_LT_OQ)
		);
	return _mm_blendv_pd(x, y, fmax_cmp);
}
#endif

#ifndef _mm_fmin_pd
/**
 * @brief Returns the fmin of x and y. Correctly handling NaN and signed zeros.
 * You may use _mm_min_pd as a faster alternative.
 */
static inline __m128d _mm_fmin_pd(__m128d x, __m128d y) {
	__m128d fmax_cmp =
		_mm_or_pd(
			_mm_andnot_pd(
				_mm_or_pd(
					_mm_andnot_pd(
						_mm_signbit_pd(x),
						_mm_isnan_pd(y)
					),
					_mm_isnan_pd(x)
				),
				_mm_cmp_pd(y, x, _CMP_GT_OQ)
			),
			_mm_cmp_pd(x, y, _CMP_GT_OQ)
		);
	return _mm_blendv_pd(x, y, fmax_cmp);
}
#endif

#endif

//------------------------------------------------------------------------------
// __m128d ilogb
//------------------------------------------------------------------------------

#if true || defined(__SSE4_1__) && defined(__SSE4_2__)

static inline __m128i _internal_mm_ilogb_pd_epi64(__m128d x) {
	const int64_t float64_bias = 1023;
	#if 0
		/* Ignores denormals and inf */
		__m128i bin_x = _mm_castpd_si128(x);
		// clear the signbit
		bin_x = _mm_slli_epi64(bin_x, 1);
		// shift the exponent down
		bin_x = _mm_slri_epi64(bin_x, 52 + 1);
		bin_x = _mm_add_epi64(bin_x, _mm_set1_epi64x(float64_bias));
		return bin_x;
	#else

		// 2 ^ +64
		const __m128d mult_2_p64 = _mm_set1_pd(1.8446744073709551616e+19);
		
		const __m128d x_isdenorm = _mm_isdenormal_pd(x);
		__m128i bin_x = _mm_castpd_si128(_mm_mul_pd(
			x, _mm_blendv_pd(_mm_set1_pd(1.0), mult_2_p64, x_isdenorm)
		));
		
		// clear the signbit
		bin_x = _mm_slli_epi64(bin_x, 1);
		// shift the exponent down
		bin_x = _mm_srli_epi64(bin_x, 52 + 1);
		bin_x = _mm_add_epi64(bin_x, _mm_set1_epi64x(float64_bias));
		
		// subtracts the exponent shift used for denormal numbers
		bin_x = _mm_sub_epi64(bin_x,
			_mm_and_si128(_mm_set1_epi64x((int64_t)64), _mm_castpd_si128(x_isdenorm))
		);
		return bin_x;

	#endif
}

/**
 * @brief Computes ilogb(x) using AVX2 integer operations
 * @returns __m128i int64_t
 */
static inline __m128i _mm_ilogb_pd_epi64(__m128d x) {
	__m128d ret = _mm_castsi128_pd(_internal_mm_ilogb_pd_epi64(x));
	// Sets ret to INT64_MIN if x is zero or NaN
	ret = _mm_blendv_pd(
		ret, _mm_castsi128_pd(_mm_set1_epi64x(INT64_MIN)),
		_mm_or_pd(_mm_isnan_pd(x), _mm_cmp_pd(x, _mm_setzero_pd(), _CMP_EQ_OQ))
	);
	// Sets ret to INT64_MAX if x is infinity
	ret = _mm_blendv_pd(
		ret, _mm_castsi128_pd(_mm_set1_epi64x(INT64_MAX)),
		_mm_isinf_pd(x)
	);
	return _mm_castpd_si128(ret);
}

#endif

//------------------------------------------------------------------------------
// __m128d ldexp
//------------------------------------------------------------------------------

#if true || defined(__SSE4_1__) && defined(__SSE4_2__)

/**
 * @brief Computes ldexp(x, expon) with support for denormal numbers.
 * @remarks Uses 5 fp64 multiplications, 4 blendv, 4 int64 comparisons,
 * 5 int64 additions, and 1 int64_t left shfit
 */
static inline __m128d _mm_ldexp_pd_epi64(__m128d x, __m128i expon) {

	// Update this
	const int64_t float64_bias = 1023;

	// Arbritrary, but should be large and less than ~1024
	const int64_t mult_2_power = 896;
	// 2 ^ +896
	const __m128d mult_2_p896 = _mm_set1_pd(5.2829453113566524635233978491652e+269);
	// 2 ^ -896
	const __m128d mult_2_n896 = _mm_set1_pd(1.8928834978668395375564025560288e-270);

	{ /* multiplies by a large power of 2 */
		__m128i test = _mm_cmpgt_epi64(expon, _mm_set1_epi64x(mult_2_power - 1));
		x = _mm_mul_pd(x, _mm_blendv_pd(_mm_set1_pd(1.0), mult_2_p896, _mm_castsi128_pd(test)));
		expon = _mm_sub_epi64(expon, _mm_set1_epi64x(mult_2_power));
	}
	{ /* multiplies by a large power of 2 */
		__m128i test = _mm_cmpgt_epi64(expon, _mm_set1_epi64x(mult_2_power - 1));
		x = _mm_mul_pd(x, _mm_blendv_pd(_mm_set1_pd(1.0), mult_2_p896, _mm_castsi128_pd(test)));
		expon = _mm_sub_epi64(expon, _mm_set1_epi64x(mult_2_power));
	}
	{ /* divides by a large power of 2 */
		__m128i test = _mm_cmpgt_epi64(_mm_set1_epi64x(-mult_2_power + 1), expon);
		x = _mm_mul_pd(x, _mm_blendv_pd(mult_2_n896, _mm_set1_pd(1.0), _mm_castsi128_pd(test)));
		expon = _mm_add_epi64(expon, _mm_set1_epi64x(mult_2_power));
	}
	{ /* divides by a large power of 2 */
		__m128i test = _mm_cmpgt_epi64(_mm_set1_epi64x(-mult_2_power + 1), expon);
		x = _mm_mul_pd(x, _mm_blendv_pd(mult_2_n896, _mm_set1_pd(1.0), _mm_castsi128_pd(test)));
		expon = _mm_add_epi64(expon, _mm_set1_epi64x(mult_2_power));
	}

	/* multiplies by the remaining exponent */

	// Creates a normalized number of the form 2^expon
	__m128i bias_expon = _mm_add_epi64(expon, _mm_set1_epi64x(float64_bias));
	// fabs clears the signbit
	__m128d mult = _mm_fabs_pd(_mm_castsi128_pd(_mm_slli_epi64(bias_expon, 52)));
	
	return _mm_mul_pd(x, mult);
}

#endif

//------------------------------------------------------------------------------
// __m128d frexp
//------------------------------------------------------------------------------

#if true || defined(__SSE4_1__) && defined(__SSE4_2__)

static inline __m128d _mm_frexp_pd_epi64(__m128d x, __m128i* const expon) {
	*expon = _mm_add_epi64(_mm_ilogb_pd_epi64(x), _mm_set1_epi64x((int64_t)1));
	/**
	 * Clears the exponent bits of x, then does a bitwise OR so that x will
	 * be inside the range [0.5, 1.0)
	 */
	x = _mm_andnot_pd(x, _mm_get_exponent_mask_pd());
	x = _mm_or_pd(x, _mm_set1_pd(0.5));
	return x;
}

#endif

#if 0
/* Legacy Code */

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

#endif

#ifdef __cplusplus
}
#endif

#endif /* FLOAT64_SSE2_H */
