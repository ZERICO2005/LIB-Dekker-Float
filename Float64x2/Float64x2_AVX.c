/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#include "Float64x2.h"
#include "Float64x2_AVX.h"

#include <immintrin.h>

static inline __m256dx2 _mm256x2_taylor_expm1_pdx2(const __m256dx2 x, __m128i* m_bin) {
	const __m256dx2 inv_fact[6] = {
		_mm256x2_set1_pd_pd(0x1.5555555555555p-3 ,+0x1.5555555555555p-57),
		_mm256x2_set1_pd_pd(0x1.5555555555555p-5 ,+0x1.5555555555555p-59),
		_mm256x2_set1_pd_pd(0x1.1111111111111p-7 ,+0x1.1111111111111p-63),
		_mm256x2_set1_pd_pd(0x1.6c16c16c16c17p-10,-0x1.f49f49f49f49fp-65),
		_mm256x2_set1_pd_pd(0x1.a01a01a01a01ap-13,+0x1.a01a01a01a01ap-73),
		_mm256x2_set1_pd_pd(0x1.a01a01a01a01ap-16,+0x1.a01a01a01a01ap-76)
	};
	/* Strategy:  We first reduce the size of x by noting that
		
			exp(kr + m * log(2)) = 2^m * exp(r)^k

		where m and k are integers.  By choosing m appropriately
		we can make |kr| <= log(2) / 2 = 0.347.  Then exp(r) is 
		evaluated using the familiar Taylor series.  Reducing the 
		argument substantially speeds up the convergence.       */  

	// const __m256d k = _mm256_set1_pd(0x1.0p+9);
	const __m256d inv_k = _mm256_set1_pd(0x1.0p-9);

	const __m256dx2 const_ln2 = _mm256x2_const_ln2_pdx2();

	__m256d m = _mm256_floor_pd(
		_mm256_add_pd(_mm256_mul_pd(x.hi, const_ln2.hi), _mm256_set1_pd(0.5))
	);
	*m_bin = _mm256_cvttpd_epi32(m);

	__m256dx2 r = _mm256x2_mul_power2_pdx2_pd(_mm256x2_sub_pdx2(x, _mm256x2_mul_pdx2_pd(const_ln2, m)), inv_k);
	__m256dx2 s, t, p;

	p = _mm256x2_square_pdx2(r);
	s = _mm256x2_add_pdx2(r, _mm256x2_mul_power2_pdx2_pd(p, _mm256_set1_pd(0.5)));
	p = _mm256x2_mul_pdx2(p, r);
	t = _mm256x2_mul_pdx2(p, inv_fact[0]);
	size_t i = 0;
	do {
		s = _mm256x2_add_pdx2(s, t);
		p = _mm256x2_mul_pdx2(p, r);
		++i;
		t = _mm256x2_mul_pdx2(p, inv_fact[1]);
	} while (i < 5);

	s = _mm256x2_add_pdx2(s, t);

	s = _mm256x2_add_pdx2(_mm256x2_mul_power2_pdx2_pd(s, _mm256_set1_pd(2.0)), _mm256x2_square_pdx2(s));
	s = _mm256x2_add_pdx2(_mm256x2_mul_power2_pdx2_pd(s, _mm256_set1_pd(2.0)), _mm256x2_square_pdx2(s));
	s = _mm256x2_add_pdx2(_mm256x2_mul_power2_pdx2_pd(s, _mm256_set1_pd(2.0)), _mm256x2_square_pdx2(s));

	s = _mm256x2_add_pdx2(_mm256x2_mul_power2_pdx2_pd(s, _mm256_set1_pd(2.0)), _mm256x2_square_pdx2(s));
	s = _mm256x2_add_pdx2(_mm256x2_mul_power2_pdx2_pd(s, _mm256_set1_pd(2.0)), _mm256x2_square_pdx2(s));
	s = _mm256x2_add_pdx2(_mm256x2_mul_power2_pdx2_pd(s, _mm256_set1_pd(2.0)), _mm256x2_square_pdx2(s));

	s = _mm256x2_add_pdx2(_mm256x2_mul_power2_pdx2_pd(s, _mm256_set1_pd(2.0)), _mm256x2_square_pdx2(s));
	s = _mm256x2_add_pdx2(_mm256x2_mul_power2_pdx2_pd(s, _mm256_set1_pd(2.0)), _mm256x2_square_pdx2(s));
	s = _mm256x2_add_pdx2(_mm256x2_mul_power2_pdx2_pd(s, _mm256_set1_pd(2.0)), _mm256x2_square_pdx2(s));
	
	return s;
	// Original return code:
	// s += 1.0;
	// return ldexp(s, static_cast<int>(m));
}

__m256dx2 _mm256x2_exp_pdx2(const __m256dx2 x) {
	__m128i m_bin;
	__m256dx2 ret = _mm256x2_taylor_expm1_pdx2(x, &m_bin);
	ret = _mm256x2_add_pdx2_pd(ret, _mm256_set1_pd(1.0));
	
	return _mm256x2_mul_pdx2_pd(ret, _mm256_ldexp1_pd_epi32(m_bin));
}

__m256dx2 _mm256x2_expm1_pdx2(const __m256dx2 x) {
	__m128i m_bin;
	__m256dx2 ret_expm1 = _mm256x2_taylor_expm1_pdx2(x, &m_bin);

	__m256dx2 ret = _mm256x2_add_pdx2_pd(ret_expm1, _mm256_set1_pd(1.0));
	
	ret = _mm256x2_mul_pdx2_pd(ret, _mm256_ldexp1_pd_epi32(m_bin));
	ret = _mm256x2_sub_pdx2_pd(ret, _mm256_set1_pd(1.0));

	// Check if x was in range
	const __m256dx2 const_half_ln2 = _mm256x2_mul_power2_pdx2_pd(
		_mm256x2_const_ln2_pdx2(), _mm256_set1_pd(0.5)
	);
	__m256d ret_cmp = _mm256_cmplt_pdx2(_mm256x2_fabs_pdx2(x), const_half_ln2);

	ret.hi = _mm256_blendv_pd(ret.hi, ret_expm1.hi, ret_cmp);
	ret.lo = _mm256_blendv_pd(ret.lo, ret_expm1.lo, ret_cmp);
	return ret;
}

//------------------------------------------------------------------------------
// __m256dx2 exponents and logarithms
//------------------------------------------------------------------------------

// __m256dx2 _mm256x2_exp_pdx2(const __m256dx2 x) {
// 	Float64x2 val[4];
// 	_mm256x2_store_pdx2(val, x);
// 	val[0] = Float64x2_exp(val[0]);
// 	val[1] = Float64x2_exp(val[1]);
// 	val[2] = Float64x2_exp(val[2]);
// 	val[3] = Float64x2_exp(val[3]);
// 	return _mm256x2_load_pdx2(val);
// }

// __m256dx2 _mm256x2_expm1_pdx2(const __m256dx2 x) {
// 	Float64x2 val[4];
// 	_mm256x2_store_pdx2(val, x);
// 	val[0] = Float64x2_expm1(val[0]);
// 	val[1] = Float64x2_expm1(val[1]);
// 	val[2] = Float64x2_expm1(val[2]);
// 	val[3] = Float64x2_expm1(val[3]);
// 	return _mm256x2_load_pdx2(val);
// }

__m256dx2 _mm256x2_log_pdx2(const __m256dx2 x) {
	Float64x2 val[4];
	_mm256x2_store_pdx2(val, x);
	val[0] = Float64x2_log(val[0]);
	val[1] = Float64x2_log(val[1]);
	val[2] = Float64x2_log(val[2]);
	val[3] = Float64x2_log(val[3]);
	return _mm256x2_load_pdx2(val);
}

__m256dx2 _mm256x2_log1p_pdx2(const __m256dx2 x) {
	Float64x2 val[4];
	_mm256x2_store_pdx2(val, x);
	val[0] = Float64x2_log1p(val[0]);
	val[1] = Float64x2_log1p(val[1]);
	val[2] = Float64x2_log1p(val[2]);
	val[3] = Float64x2_log1p(val[3]);
	return _mm256x2_load_pdx2(val);
}

__m256dx2 _mm256x2_pow_pdx2(const __m256dx2 x, const __m256dx2 y) {
	Float64x2 x_val[4];
	Float64x2 y_val[4];
	_mm256x2_store_pdx2(x_val, x);
	_mm256x2_store_pdx2(y_val, y);
	x_val[0] = Float64x2_pow(x_val[0], y_val[0]);
	x_val[1] = Float64x2_pow(x_val[1], y_val[1]);
	x_val[2] = Float64x2_pow(x_val[2], y_val[2]);
	x_val[3] = Float64x2_pow(x_val[3], y_val[3]);
	return _mm256x2_load_pdx2(x_val);
}

__m256dx2 _mm256x2_pow_pdx2_pd(const __m256dx2 x, const __m256d y) {
	Float64x2 x_val[4];
	fp64 y_val[4];
	_mm256x2_store_pdx2(x_val, x);
	_mm256_store_pd(y_val, y);
	x_val[0] = Float64x2_pow_dx2_d(x_val[0], y_val[0]);
	x_val[1] = Float64x2_pow_dx2_d(x_val[1], y_val[1]);
	x_val[2] = Float64x2_pow_dx2_d(x_val[2], y_val[2]);
	x_val[3] = Float64x2_pow_dx2_d(x_val[3], y_val[3]);
	return _mm256x2_load_pdx2(x_val);
}

//------------------------------------------------------------------------------
// __m256dx2 trigonometry
//------------------------------------------------------------------------------

__m256dx2 _mm256x2_sin_pdx2(const __m256dx2 x) {
	Float64x2 val[4];
	_mm256x2_store_pdx2(val, x);
	val[0] = Float64x2_sin(val[0]);
	val[1] = Float64x2_sin(val[1]);
	val[2] = Float64x2_sin(val[2]);
	val[3] = Float64x2_sin(val[3]);
	return _mm256x2_load_pdx2(val);
}

__m256dx2 _mm256x2_cos_pdx2(const __m256dx2 x) {
	Float64x2 val[4];
	_mm256x2_store_pdx2(val, x);
	val[0] = Float64x2_cos(val[0]);
	val[1] = Float64x2_cos(val[1]);
	val[2] = Float64x2_cos(val[2]);
	val[3] = Float64x2_cos(val[3]);
	return _mm256x2_load_pdx2(val);
}

void _mm256x2_sincos_pdx2(
	const __m256dx2 theta, __m256dx2* const p_sin, __m256dx2* const p_cos
) {
	Float64x2 val[4];
	Float64x2 sin_val[4];
	Float64x2 cos_val[4];
	_mm256x2_store_pdx2(val, theta);
	Float64x2_sincos(val[0], &sin_val[0], &cos_val[0]);
	Float64x2_sincos(val[1], &sin_val[1], &cos_val[1]);
	Float64x2_sincos(val[2], &sin_val[2], &cos_val[2]);
	Float64x2_sincos(val[3], &sin_val[3], &cos_val[3]);
	*p_sin = _mm256x2_load_pdx2(sin_val);
	*p_cos = _mm256x2_load_pdx2(cos_val);
}

__m256dx2 _mm256x2_asin_pdx2(const __m256dx2 x) {
	Float64x2 val[4];
	_mm256x2_store_pdx2(val, x);
	val[0] = Float64x2_asin(val[0]);
	val[1] = Float64x2_asin(val[1]);
	val[2] = Float64x2_asin(val[2]);
	val[3] = Float64x2_asin(val[3]);
	return _mm256x2_load_pdx2(val);
}

__m256dx2 _mm256x2_acos_pdx2(const __m256dx2 x) {
	Float64x2 val[4];
	_mm256x2_store_pdx2(val, x);
	val[0] = Float64x2_acos(val[0]);
	val[1] = Float64x2_acos(val[1]);
	val[2] = Float64x2_acos(val[2]);
	val[3] = Float64x2_acos(val[3]);
	return _mm256x2_load_pdx2(val);
}

__m256dx2 _mm256x2_atan_pdx2(const __m256dx2 x) {
	Float64x2 val[4];
	_mm256x2_store_pdx2(val, x);
	val[0] = Float64x2_atan(val[0]);
	val[1] = Float64x2_atan(val[1]);
	val[2] = Float64x2_atan(val[2]);
	val[3] = Float64x2_atan(val[3]);
	return _mm256x2_load_pdx2(val);
}

__m256dx2 _mm256x2_atan2_pdx2(const __m256dx2 y, const __m256dx2 x) {
	Float64x2 y_val[4];
	Float64x2 x_val[4];
	_mm256x2_store_pdx2(y_val, y);
	_mm256x2_store_pdx2(x_val, x);
	y_val[0] = Float64x2_atan2(y_val[0], x_val[0]);
	y_val[1] = Float64x2_atan2(y_val[1], x_val[1]);
	y_val[2] = Float64x2_atan2(y_val[2], x_val[2]);
	y_val[3] = Float64x2_atan2(y_val[3], x_val[3]);
	return _mm256x2_load_pdx2(y_val);
}

__m256dx2 _mm256x2_sinh_pdx2(const __m256dx2 x) {
	Float64x2 val[4];
	_mm256x2_store_pdx2(val, x);
	val[0] = Float64x2_sinh(val[0]);
	val[1] = Float64x2_sinh(val[1]);
	val[2] = Float64x2_sinh(val[2]);
	val[3] = Float64x2_sinh(val[3]);
	return _mm256x2_load_pdx2(val);
}

__m256dx2 _mm256x2_tanh_pdx2(const __m256dx2 x) {
	Float64x2 val[4];
	_mm256x2_store_pdx2(val, x);
	val[0] = Float64x2_tanh(val[0]);
	val[1] = Float64x2_tanh(val[1]);
	val[2] = Float64x2_tanh(val[2]);
	val[3] = Float64x2_tanh(val[3]);
	return _mm256x2_load_pdx2(val);
}

void _mm256x2_sinhcosh_pdx2(
	const __m256dx2 theta, __m256dx2* const p_sinh, __m256dx2* const p_cosh
) {
	Float64x2 val[4];
	Float64x2 sinh_val[4];
	Float64x2 cosh_val[4];
	_mm256x2_store_pdx2(val, theta);
	Float64x2_sinhcosh(val[0], &sinh_val[0], &cosh_val[0]);
	Float64x2_sinhcosh(val[1], &sinh_val[1], &cosh_val[1]);
	Float64x2_sinhcosh(val[2], &sinh_val[2], &cosh_val[2]);
	Float64x2_sinhcosh(val[3], &sinh_val[3], &cosh_val[3]);
	*p_sinh = _mm256x2_load_pdx2(sinh_val);
	*p_cosh = _mm256x2_load_pdx2(cosh_val);
}
