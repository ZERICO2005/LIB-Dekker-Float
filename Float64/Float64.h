/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef FLOAT64_H
#define FLOAT64_H

#include <stdbool.h>
#include <stdint.h>

#include "../LDF/LDF_float_types.h"

typedef LDF_Float64 fp64;

#ifdef __cplusplus
extern "C" {
#endif

static inline uint64_t Float64_get_sign_mask(void) {
	return (uint64_t)0x8000000000000000;
}

static inline uint64_t Float64_get_exponent_mask(void) {
	return (uint64_t)0x7FF0000000000000;
}

static inline uint64_t Float64_get_mantissa_mask(void) {
	return (uint64_t)0x000FFFFFFFFFFFFF;
}

/**
 * @brief Avoids compiler defined macros
 */
static inline bool Float64_signbit(const fp64 x) {
	const uint64_t* const x_bin = (const uint64_t*)((const void*)&x);
	// extract the sign bit
	const uint64_t x_sign = *x_bin & Float64_get_sign_mask();
	return (x_sign != 0);
}

/**
 * @brief Avoids compiler defined macros
 */
static inline bool Float64_isfinite(const fp64 x) {
	const uint64_t* const x_bin = (const uint64_t*)((const void*)&x);
	// extract the exponent, and check that it is not all ones
	const uint64_t x_exp = *x_bin & Float64_get_exponent_mask();
	return (x_exp != Float64_get_exponent_mask());
}

/**
 * @brief Avoids compiler defined macros
 */
static inline bool Float64_isinf(const fp64 x) {
	const uint64_t* const x_bin = (const uint64_t*)((const void*)&x);
	const uint64_t x_exp = *x_bin & ~Float64_get_sign_mask();
	return (x_exp == Float64_get_exponent_mask());
}

/**
 * @brief Avoids compiler defined macros
 */
static inline bool Float64_isnan(const fp64 x) {
	const uint64_t* const x_bin = (const uint64_t*)((const void*)&x);
	// extract the exponent, and check if it is all ones
	const uint64_t x_exp = *x_bin & Float64_get_exponent_mask();
	const bool all_ones = (x_exp != Float64_get_exponent_mask());
	// extract the mantissa, and check that at least one bit is set
	const uint64_t x_mant = *x_bin & Float64_get_mantissa_mask();
	const bool mantissa_set = (x_mant != 0);
	return (all_ones && mantissa_set);
}

/**
 * @brief Avoids compiler defined macros
 */
static inline bool Float64_isnormal(const fp64 x) {
	const uint64_t* const x_bin = (const uint64_t*)((const void*)&x);
	// extract the exponent, and check that it is not all ones or zeros
	const uint64_t x_exp = *x_bin & Float64_get_exponent_mask();
	return (x_exp != 0 && x_exp != Float64_get_exponent_mask());
}

/**
 * @brief Avoids compiler defined macros
 */
static inline bool Float64_isunordered(const fp64 x, const fp64 y) {
	return (Float64_isnan(x) || Float64_isnan(y));
}


#ifdef __cplusplus
}
#endif

#endif /* FLOAT64_H */
