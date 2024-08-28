/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#include "Float64x2.h"
#include "Float64x2_AVX.h"

__m256dx2 _mm256x2_exp_pdx2(const __m256dx2 x) {
	Float64x2 val[4];
	_mm256x2_store_pdx2(val, x);
	val[0] = Float64x2_exp(val[0]);
	val[1] = Float64x2_exp(val[1]);
	val[2] = Float64x2_exp(val[2]);
	val[3] = Float64x2_exp(val[3]);
	return _mm256x2_load_pdx2(val);
}

__m256dx2 _mm256x2_expm1_pdx2(const __m256dx2 x) {
	Float64x2 val[4];
	_mm256x2_store_pdx2(val, x);
	val[0] = Float64x2_expm1(val[0]);
	val[1] = Float64x2_expm1(val[1]);
	val[2] = Float64x2_expm1(val[2]);
	val[3] = Float64x2_expm1(val[3]);
	return _mm256x2_load_pdx2(val);
}

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
	Float64x2 sin_val[4];
	Float64x2 cos_val[4];
	_mm256x2_store_pdx2(val, theta);
	Float64x2_sinhcosh(val[0], &sin_val[0], &cos_val[0]);
	Float64x2_sinhcosh(val[1], &sin_val[1], &cos_val[1]);
	Float64x2_sinhcosh(val[2], &sin_val[2], &cos_val[2]);
	Float64x2_sinhcosh(val[3], &sin_val[3], &cos_val[3]);
	*p_sinh = _mm256x2_load_pdx2(sin_val);
	*p_cosh = _mm256x2_load_pdx2(cos_val);
}
