/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#include <immintrin.h>
#include <math.h>
#include "Float64_AVX.h"

#if (FLOAT64_AVX_SVML_REPLACEMENTS != 0)

__m256d _mm256_cbrt_pd(const __m256d x) {
	// 2^floor(ilogb(fabs(x)) / 3)
	__m256d guess = _mm256_ldexp1_pd_pd(_mm256_div_pd(
		_mm256_ilogb_pd_pd(x), _mm256_set1_pd(3.0)
	));

	/**
	 * @remarks 7 iterations seems to yeild the full precision of ieee doubles.
	 * If the ilogb approximation was changed to 2.0^(ilogb(fabs(x)) / 3.0),
	 * then only 5 iterations would be needed.
	 */
	for (int i = 0; i < 7; i++) {
		guess = _mm256_div_pd(_mm256_add_pd(
			_mm256_mul_pd(_mm256_set1_pd(2.0), guess),
			_mm256_div_pd(x, _mm256_square_pd(guess))
		), _mm256_set1_pd(3.0));
	}
	__m256d neg_mask = _mm256_and_pd(
		x, _mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x8000000000000000))
	);
	return _mm256_and_pd(
		_mm256_or_pd(guess, neg_mask),
		_mm256_cmp_pd(x, _mm256_setzero_pd(), _CMP_NEQ_UQ)
	);
}

__m256d _mm256_hypot_pd(const __m256d x, const __m256d y) {
	double x_val[4];
	double y_val[4];
	_mm256_store_pd(x_val, x);
	_mm256_store_pd(y_val, y);
	x_val[0] = hypot(x_val[0], y_val[0]);
	x_val[1] = hypot(x_val[1], y_val[1]);
	x_val[2] = hypot(x_val[2], y_val[2]);
	x_val[3] = hypot(x_val[3], y_val[3]);
	return _mm256_load_pd(x_val);
}

//------------------------------------------------------------------------------
// __m256d exponents and logarithms
//------------------------------------------------------------------------------

/**
 * @note This is currently the __m256dx2 version of the function, which means
 * the extra precision is wasted.
 * @todo Find the correct value for k and the number of terms to use for the
 * taylor series for this function.
 */
static inline __m256d _mm256_taylor_expm1_pd(
	const __m256d x, __m128i* m_bin
) {
	const __m256d inv_fact[6] = {
	/* 3! */ _mm256_set1_pd(0x1.5555555555555p-3 ),
	/* 4! */ _mm256_set1_pd(0x1.5555555555555p-5 ),
	/* 5! */ _mm256_set1_pd(0x1.1111111111111p-7 ),
	/* 6! */ _mm256_set1_pd(0x1.6c16c16c16c17p-10),
	/* 7! */ _mm256_set1_pd(0x1.a01a01a01a01ap-13),
	/* 8! */ _mm256_set1_pd(0x1.a01a01a01a01ap-16)
	};
	/* Strategy:  We first reduce the size of x by noting that
		
			exp(kr + m * log(2)) = 2^m * exp(r)^k

		where m and k are integers.  By choosing m appropriately
		we can make |kr| <= log(2) / 2 = 0.347.  Then exp(r) is 
		evaluated using the familiar Taylor series.  Reducing the 
		argument substantially speeds up the convergence.       */  

	// const __m256d k = _mm256_set1_pd(0x1.0p+9);
	const __m256d inv_k = _mm256_set1_pd(0x1.0p-9);

	const __m256d const_log2e = _mm256_const_log2e_pd();
	const __m256d const_ln2 = _mm256_const_ln2_pd();

	__m256d m = _mm256_floor_pd(
		_mm256_add_pd(_mm256_mul_pd(x, const_log2e), _mm256_set1_pd(0.5))
	);
	*m_bin = _mm256_cvttpd_epi32(m);

	__m256d r = _mm256_mul_pd(
		_mm256_sub_pd(x, _mm256_mul_pd(const_ln2, m)), inv_k
	);
	__m256d s, t, p;

	p = _mm256_square_pd(r);
	s = _mm256_add_pd(r, _mm256_mul_pd(p, _mm256_set1_pd(0.5)));
	p = _mm256_mul_pd(p, r);
	t = _mm256_mul_pd(p, inv_fact[0]);
	size_t i = 0;
	do {
		s = _mm256_add_pd(s, t);
		p = _mm256_mul_pd(p, r);
		++i;
		t = _mm256_mul_pd(p, inv_fact[i]);
	} while (i < 5);

	s = _mm256_add_pd(s, t);

	s = _mm256_add_pd(_mm256_mul_pd(s, _mm256_set1_pd(2.0)), _mm256_square_pd(s));
	s = _mm256_add_pd(_mm256_mul_pd(s, _mm256_set1_pd(2.0)), _mm256_square_pd(s));
	s = _mm256_add_pd(_mm256_mul_pd(s, _mm256_set1_pd(2.0)), _mm256_square_pd(s));

	s = _mm256_add_pd(_mm256_mul_pd(s, _mm256_set1_pd(2.0)), _mm256_square_pd(s));
	s = _mm256_add_pd(_mm256_mul_pd(s, _mm256_set1_pd(2.0)), _mm256_square_pd(s));
	s = _mm256_add_pd(_mm256_mul_pd(s, _mm256_set1_pd(2.0)), _mm256_square_pd(s));

	s = _mm256_add_pd(_mm256_mul_pd(s, _mm256_set1_pd(2.0)), _mm256_square_pd(s));
	s = _mm256_add_pd(_mm256_mul_pd(s, _mm256_set1_pd(2.0)), _mm256_square_pd(s));
	s = _mm256_add_pd(_mm256_mul_pd(s, _mm256_set1_pd(2.0)), _mm256_square_pd(s));
	
	return s;
	// Original return code:
	// s += 1.0;
	// return ldexp(s, static_cast<int>(m));
}

__m256d _mm256_exp_pd(const __m256d x) {
	__m128i m_bin;
	__m256d ret = _mm256_taylor_expm1_pd(x, &m_bin);
	ret = _mm256_add_pd(ret, _mm256_set1_pd(1.0));
	
	return _mm256_ldexp_pd_epi32(ret, m_bin);
}

__m256d _mm256_expm1_pd(const __m256d x) {
	__m128i m_bin;
	__m256d ret_expm1 = _mm256_taylor_expm1_pd(x, &m_bin);

	__m256d ret = _mm256_add_pd(ret_expm1, _mm256_set1_pd(1.0));
	
	ret = _mm256_ldexp_pd_epi32(ret, m_bin);
	ret = _mm256_sub_pd(ret, _mm256_set1_pd(1.0));

	// Check if x was in range
	const __m256d const_half_ln2 = _mm256_mul_pd(
		_mm256_const_ln2_pd(), _mm256_set1_pd(0.5)
	);
	__m256d ret_cmp = _mm256_cmp_pd(_mm256_fabs_pd(x), const_half_ln2, _CMP_LT_OQ);

	ret = _mm256_blendv_pd(ret, ret_expm1, ret_cmp);
	return ret;
}

__m256d _mm256_log_pd(const __m256d x) {
	// extract the exponent, and multiply by ln(2)
	__m256d guess = _mm256_mul_pd(
		_mm256_ilogb_pd_pd(x), _mm256_const_ln2_pd()
	);
	// 6 iterations should yield the full precision of ieee doubles
	for (int i = 0; i < 6; i++) {
		guess = _mm256_sub_pd(_mm256_add_pd(
			guess,
			_mm256_mul_pd(x, _mm256_exp_pd(_mm256_negate_pd(guess)))
		), _mm256_set1_pd(1.0));
	}
	return guess;
}

__m256d _mm256_pow_pd(const __m256d x, const __m256d y) {
	double x_val[4];
	double y_val[4];
	_mm256_store_pd(x_val, x);
	_mm256_store_pd(y_val, y);
	x_val[0] = pow(x_val[0], y_val[0]);
	x_val[1] = pow(x_val[1], y_val[1]);
	x_val[2] = pow(x_val[2], y_val[2]);
	x_val[3] = pow(x_val[3], y_val[3]);
	return _mm256_load_pd(x_val);
}

//------------------------------------------------------------------------------
// __m256d trigonometry
//------------------------------------------------------------------------------

__m256d _mm256_sin_pd(const __m256d x) {
	double val[4];
	_mm256_store_pd(val, x);
	val[0] = sin(val[0]);
	val[1] = sin(val[1]);
	val[2] = sin(val[2]);
	val[3] = sin(val[3]);
	return _mm256_load_pd(val);
}

__m256d _mm256_cos_pd(const __m256d x) {
	double val[4];
	_mm256_store_pd(val, x);
	val[0] = cos(val[0]);
	val[1] = cos(val[1]);
	val[2] = cos(val[2]);
	val[3] = cos(val[3]);
	return _mm256_load_pd(val);
}

__m256d _mm256_sincos_pd(__m256d* const p_cos, const __m256d theta) {
	double val[4];
	double sin_val[4];
	double cos_val[4];
	_mm256_store_pd(val, theta);
	sin_val[0] = sin(val[0]);
	sin_val[1] = sin(val[1]);
	sin_val[2] = sin(val[2]);
	sin_val[3] = sin(val[3]);
	cos_val[0] = cos(val[0]);
	cos_val[1] = cos(val[1]);
	cos_val[2] = cos(val[2]);
	cos_val[3] = cos(val[3]);
	*p_cos = _mm256_load_pd(cos_val);
	return _mm256_load_pd(sin_val);
}

__m256d _mm256_asin_pd(const __m256d x) {
	double val[4];
	_mm256_store_pd(val, x);
	val[0] = asin(val[0]);
	val[1] = asin(val[1]);
	val[2] = asin(val[2]);
	val[3] = asin(val[3]);
	return _mm256_load_pd(val);
}

__m256d _mm256_acos_pd(const __m256d x) {
	double val[4];
	_mm256_store_pd(val, x);
	val[0] = acos(val[0]);
	val[1] = acos(val[1]);
	val[2] = acos(val[2]);
	val[3] = acos(val[3]);
	return _mm256_load_pd(val);
}

__m256d _mm256_atan_pd(const __m256d x) {
	double val[4];
	_mm256_store_pd(val, x);
	val[0] = atan(val[0]);
	val[1] = atan(val[1]);
	val[2] = atan(val[2]);
	val[3] = atan(val[3]);
	return _mm256_load_pd(val);
}

__m256d _mm256_atan2_pd(const __m256d y, const __m256d x) {
	double y_val[4];
	double x_val[4];
	_mm256_store_pd(y_val, y);
	_mm256_store_pd(x_val, x);
	y_val[0] = atan2(y_val[0], x_val[0]);
	y_val[1] = atan2(y_val[1], x_val[1]);
	y_val[2] = atan2(y_val[2], x_val[2]);
	y_val[3] = atan2(y_val[3], x_val[3]);
	return _mm256_load_pd(y_val);
}

__m256d _mm256_sinh_pd(const __m256d x) {
	double val[4];
	_mm256_store_pd(val, x);
	val[0] = sinh(val[0]);
	val[1] = sinh(val[1]);
	val[2] = sinh(val[2]);
	val[3] = sinh(val[3]);
	return _mm256_load_pd(val);
}

__m256d _mm256_tanh_pd(const __m256d x) {
	double val[4];
	_mm256_store_pd(val, x);
	val[0] = tanh(val[0]);
	val[1] = tanh(val[1]);
	val[2] = tanh(val[2]);
	val[3] = tanh(val[3]);
	return _mm256_load_pd(val);
}

__m256d _mm256_sinhcosh_pd(__m256d* const p_cosh, const __m256d theta) {
	double val[4];
	double sinh_val[4];
	double cosh_val[4];
	_mm256_store_pd(val, theta);
	sinh_val[0] = sinh(val[0]);
	sinh_val[1] = sinh(val[1]);
	sinh_val[2] = sinh(val[2]);
	sinh_val[3] = sinh(val[3]);
	cosh_val[0] = cosh(val[0]);
	cosh_val[1] = cosh(val[1]);
	cosh_val[2] = cosh(val[2]);
	cosh_val[3] = cosh(val[3]);
	*p_cosh = _mm256_load_pd(cosh_val);
	return _mm256_load_pd(sinh_val);
}

//------------------------------------------------------------------------------
// __m256d transcendental functions
//------------------------------------------------------------------------------

__m256d _mm256_tgamma_pd(const __m256d x) {
	double val[4];
	_mm256_store_pd(val, x);
	val[0] = tgamma(val[0]);
	val[1] = tgamma(val[1]);
	val[2] = tgamma(val[2]);
	val[3] = tgamma(val[3]);
	return _mm256_load_pd(val);
}

__m256d _mm256_lgamma_pd(const __m256d x) {
	double val[4];
	_mm256_store_pd(val, x);
	val[0] = lgamma(val[0]);
	val[1] = lgamma(val[1]);
	val[2] = lgamma(val[2]);
	val[3] = lgamma(val[3]);
	return _mm256_load_pd(val);
}

__m256d _mm256_erf_pd(const __m256d x) {
	double val[4];
	_mm256_store_pd(val, x);
	val[0] = erf(val[0]);
	val[1] = erf(val[1]);
	val[2] = erf(val[2]);
	val[3] = erf(val[3]);
	return _mm256_load_pd(val);
}

__m256d _mm256_erfc_pd(const __m256d x) {
	double val[4];
	_mm256_store_pd(val, x);
	val[0] = erfc(val[0]);
	val[1] = erfc(val[1]);
	val[2] = erfc(val[2]);
	val[3] = erfc(val[3]);
	return _mm256_load_pd(val);
}

#endif
