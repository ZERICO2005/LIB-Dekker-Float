/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef FLOAT32X2_DEF_H
#define FLOAT32X2_DEF_H

/**
 * @brief defines the Float32x2 struct
 */

#include "../Float32/Float32.h"

typedef float fp32;

//------------------------------------------------------------------------------
// Float32x2 struct
//------------------------------------------------------------------------------

typedef struct Float32x2 {
	fp32 hi;
	fp32 lo;
#ifdef __cplusplus

/* Constructors */
	Float32x2() = default;

	constexpr inline Float32x2(const fp32 value_hi, const fp32 value_lo) :
		hi(value_hi), lo(value_lo) {}

	constexpr inline Float32x2(const fp32 values[2]) :
		hi(values[0]), lo(values[1]) {}

	constexpr inline Float32x2(const fp32 (&values)[2]) :
		hi(values[0]), lo(values[1]) {}

	constexpr inline Float32x2(const fp32 value) :
		hi(value), lo(0.0f) {}

	template<typename fpX>
	constexpr inline Float32x2(const fpX& value) :
		hi(static_cast<fp32>(value)), lo(static_cast<fp32>(value - static_cast<fpX>(this->hi))) {}

/* Casts */

	constexpr inline operator fp32() const {
		return this->hi;
	}

	template<typename fpX>
	constexpr inline operator fpX() const {
		return static_cast<fpX>(this->hi) + static_cast<fpX>(this->lo);
	}

#endif
} Float32x2;

#endif /* FLOAT32X2_DEF_H */
