/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#include "Float64x4.h"
#include "Float64x4_AVX.h"
#include "Float64x2/Float64x2_AVX.h"
#include "Float64x4_def.h"

//------------------------------------------------------------------------------
// __m256dx4 exponents and logarithms
//------------------------------------------------------------------------------

__m256dx4 _mm256x4_exp_pdx4(const __m256dx4 x) {
	Float64x4 val[4];
	_mm256x4_store_pdx4(val, x);
	val[0] = Float64x4_exp(val[0]);
	val[1] = Float64x4_exp(val[1]);
	val[2] = Float64x4_exp(val[2]);
	val[3] = Float64x4_exp(val[3]);
	return _mm256x4_load_pdx4(val);
}

__m256dx4 _mm256x4_expm1_pdx4(const __m256dx4 x) {
	Float64x4 val[4];
	_mm256x4_store_pdx4(val, x);
	val[0] = Float64x4_expm1(val[0]);
	val[1] = Float64x4_expm1(val[1]);
	val[2] = Float64x4_expm1(val[2]);
	val[3] = Float64x4_expm1(val[3]);
	return _mm256x4_load_pdx4(val);
}

__m256dx4 _mm256x4_log_pdx4(const __m256dx4 x) {
	Float64x4 val[4];
	_mm256x4_store_pdx4(val, x);
	val[0] = Float64x4_log(val[0]);
	val[1] = Float64x4_log(val[1]);
	val[2] = Float64x4_log(val[2]);
	val[3] = Float64x4_log(val[3]);
	return _mm256x4_load_pdx4(val);
}

__m256dx4 _mm256x4_log1p_pdx4(const __m256dx4 x) {
	Float64x4 val[4];
	_mm256x4_store_pdx4(val, x);
	val[0] = Float64x4_log1p(val[0]);
	val[1] = Float64x4_log1p(val[1]);
	val[2] = Float64x4_log1p(val[2]);
	val[3] = Float64x4_log1p(val[3]);
	return _mm256x4_load_pdx4(val);
}

__m256dx4 _mm256x4_pow_pdx4(const __m256dx4 x, const __m256dx4 y) {
	Float64x4 x_val[4];
	Float64x4 y_val[4];
	_mm256x4_store_pdx4(x_val, x);
	_mm256x4_store_pdx4(y_val, y);
	x_val[0] = Float64x4_pow(x_val[0], y_val[0]);
	x_val[1] = Float64x4_pow(x_val[1], y_val[1]);
	x_val[2] = Float64x4_pow(x_val[2], y_val[2]);
	x_val[3] = Float64x4_pow(x_val[3], y_val[3]);
	return _mm256x4_load_pdx4(x_val);
}

__m256dx4 _mm256x4_pow_pdx4_pd(const __m256dx4 x, const __m256d y) {
	Float64x4 x_val[4];
	fp64 y_val[4];
	_mm256x4_store_pdx4(x_val, x);
	_mm256_store_pd(y_val, y);
	x_val[0] = Float64x4_pow_dx4_d(x_val[0], y_val[0]);
	x_val[1] = Float64x4_pow_dx4_d(x_val[1], y_val[1]);
	x_val[2] = Float64x4_pow_dx4_d(x_val[2], y_val[2]);
	x_val[3] = Float64x4_pow_dx4_d(x_val[3], y_val[3]);
	return _mm256x4_load_pdx4(x_val);
}

//------------------------------------------------------------------------------
// __m256dx4 trigonometry
//------------------------------------------------------------------------------

__m256dx4 _mm256x4_sin_pdx4(const __m256dx4 x) {
	Float64x4 val[4];
	_mm256x4_store_pdx4(val, x);
	val[0] = Float64x4_sin(val[0]);
	val[1] = Float64x4_sin(val[1]);
	val[2] = Float64x4_sin(val[2]);
	val[3] = Float64x4_sin(val[3]);
	return _mm256x4_load_pdx4(val);
}

__m256dx4 _mm256x4_cos_pdx4(const __m256dx4 x) {
	Float64x4 val[4];
	_mm256x4_store_pdx4(val, x);
	val[0] = Float64x4_cos(val[0]);
	val[1] = Float64x4_cos(val[1]);
	val[2] = Float64x4_cos(val[2]);
	val[3] = Float64x4_cos(val[3]);
	return _mm256x4_load_pdx4(val);
}

void _mm256x4_sincos_pdx4(
	const __m256dx4 theta, __m256dx4* const p_sin, __m256dx4* const p_cos
) {
	Float64x4 val[4];
	Float64x4 sin_val[4];
	Float64x4 cos_val[4];
	_mm256x4_store_pdx4(val, theta);
	Float64x4_sincos(val[0], &sin_val[0], &cos_val[0]);
	Float64x4_sincos(val[1], &sin_val[1], &cos_val[1]);
	Float64x4_sincos(val[2], &sin_val[2], &cos_val[2]);
	Float64x4_sincos(val[3], &sin_val[3], &cos_val[3]);
	*p_sin = _mm256x4_load_pdx4(sin_val);
	*p_cos = _mm256x4_load_pdx4(cos_val);
}

__m256dx4 _mm256x4_asin_pdx4(const __m256dx4 x) {
	Float64x4 val[4];
	_mm256x4_store_pdx4(val, x);
	val[0] = Float64x4_asin(val[0]);
	val[1] = Float64x4_asin(val[1]);
	val[2] = Float64x4_asin(val[2]);
	val[3] = Float64x4_asin(val[3]);
	return _mm256x4_load_pdx4(val);
}

__m256dx4 _mm256x4_acos_pdx4(const __m256dx4 x) {
	Float64x4 val[4];
	_mm256x4_store_pdx4(val, x);
	val[0] = Float64x4_acos(val[0]);
	val[1] = Float64x4_acos(val[1]);
	val[2] = Float64x4_acos(val[2]);
	val[3] = Float64x4_acos(val[3]);
	return _mm256x4_load_pdx4(val);
}

__m256dx4 _mm256x4_atan_pdx4(const __m256dx4 x) {
	Float64x4 val[4];
	_mm256x4_store_pdx4(val, x);
	val[0] = Float64x4_atan(val[0]);
	val[1] = Float64x4_atan(val[1]);
	val[2] = Float64x4_atan(val[2]);
	val[3] = Float64x4_atan(val[3]);
	return _mm256x4_load_pdx4(val);
}

__m256dx4 _mm256x4_atan2_pdx4(const __m256dx4 y, const __m256dx4 x) {
	Float64x4 y_val[4];
	Float64x4 x_val[4];
	_mm256x4_store_pdx4(y_val, y);
	_mm256x4_store_pdx4(x_val, x);
	y_val[0] = Float64x4_atan2(y_val[0], x_val[0]);
	y_val[1] = Float64x4_atan2(y_val[1], x_val[1]);
	y_val[2] = Float64x4_atan2(y_val[2], x_val[2]);
	y_val[3] = Float64x4_atan2(y_val[3], x_val[3]);
	return _mm256x4_load_pdx4(y_val);
}

__m256dx4 _mm256x4_sinh_pdx4(const __m256dx4 x) {
	Float64x4 val[4];
	_mm256x4_store_pdx4(val, x);
	val[0] = Float64x4_sinh(val[0]);
	val[1] = Float64x4_sinh(val[1]);
	val[2] = Float64x4_sinh(val[2]);
	val[3] = Float64x4_sinh(val[3]);
	return _mm256x4_load_pdx4(val);
}

__m256dx4 _mm256x4_tanh_pdx4(const __m256dx4 x) {
	Float64x4 val[4];
	_mm256x4_store_pdx4(val, x);
	val[0] = Float64x4_tanh(val[0]);
	val[1] = Float64x4_tanh(val[1]);
	val[2] = Float64x4_tanh(val[2]);
	val[3] = Float64x4_tanh(val[3]);
	return _mm256x4_load_pdx4(val);
}

void _mm256x4_sinhcosh_pdx4(
	const __m256dx4 theta, __m256dx4* const p_sinh, __m256dx4* const p_cosh
) {
	Float64x4 val[4];
	Float64x4 sinh_val[4];
	Float64x4 cosh_val[4];
	_mm256x4_store_pdx4(val, theta);
	Float64x4_sinhcosh(val[0], &sinh_val[0], &cosh_val[0]);
	Float64x4_sinhcosh(val[1], &sinh_val[1], &cosh_val[1]);
	Float64x4_sinhcosh(val[2], &sinh_val[2], &cosh_val[2]);
	Float64x4_sinhcosh(val[3], &sinh_val[3], &cosh_val[3]);
	*p_sinh = _mm256x4_load_pdx4(sinh_val);
	*p_cosh = _mm256x4_load_pdx4(cosh_val);
}
