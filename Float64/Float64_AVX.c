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
	double val[4];
	_mm256_store_pd(val, x);
	val[0] = cbrt(val[0]);
	val[1] = cbrt(val[1]);
	val[2] = cbrt(val[2]);
	val[3] = cbrt(val[3]);
	return _mm256_load_pd(val);
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

__m256d _mm256_exp_pd(const __m256d x) {
	double val[4];
	_mm256_store_pd(val, x);
	val[0] = exp(val[0]);
	val[1] = exp(val[1]);
	val[2] = exp(val[2]);
	val[3] = exp(val[3]);
	return _mm256_load_pd(val);
}

__m256d _mm256_expm1_pd(const __m256d x) {
	double val[4];
	_mm256_store_pd(val, x);
	val[0] = expm1(val[0]);
	val[1] = expm1(val[1]);
	val[2] = expm1(val[2]);
	val[3] = expm1(val[3]);
	return _mm256_load_pd(val);
}

__m256d _mm256_log_pd(const __m256d x) {
	double val[4];
	_mm256_store_pd(val, x);
	val[0] = log(val[0]);
	val[1] = log(val[1]);
	val[2] = log(val[2]);
	val[3] = log(val[3]);
	return _mm256_load_pd(val);
}

__m256d _mm256_log1p_pd(const __m256d x) {
	double val[4];
	_mm256_store_pd(val, x);
	val[0] = log1p(val[0]);
	val[1] = log1p(val[1]);
	val[2] = log1p(val[2]);
	val[3] = log1p(val[3]);
	return _mm256_load_pd(val);
}

__m256d _mm256_logb_pd(const __m256d x) {
	double val[4];
	_mm256_store_pd(val, x);
	val[0] = logb(val[0]);
	val[1] = logb(val[1]);
	val[2] = logb(val[2]);
	val[3] = logb(val[3]);
	return _mm256_load_pd(val);
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