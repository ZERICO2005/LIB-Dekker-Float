/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/
#ifndef FLOAT64X2_DEF_H
#define FLOAT64X2_DEF_H

/**
 * @brief defines the Float64x2 struct
 */

#include "../Float64/Float64.h"

typedef float fp32;
typedef double fp64;

//------------------------------------------------------------------------------
// Float64x2 struct
//------------------------------------------------------------------------------

typedef struct Float64x2 {
	fp64 hi;
	fp64 lo;
#ifdef __cplusplus

/* Constructors */
	Float64x2() = default;

	constexpr inline Float64x2(const fp64 value_hi, const fp64 value_lo) :
		hi(value_hi), lo(value_lo) {}

	constexpr inline Float64x2(const fp64 values[2]) :
		hi(values[0]), lo(values[1]) {}

	constexpr inline Float64x2(const fp64 (&values)[2]) :
		hi(values[0]), lo(values[1]) {}

	constexpr inline Float64x2(const fp32 value) :
		hi(static_cast<fp64>(value)), lo(0.0) {}

	constexpr inline Float64x2(const fp64 value) :
		hi(value), lo(0.0) {}

	template<typename fpX>
	constexpr inline Float64x2(const fpX& value) :
		hi(static_cast<fp64>(value)), lo(static_cast<fp64>(value - static_cast<fpX>(this->hi))) {}

/* Casts */

	constexpr inline operator fp32() const {
		return static_cast<fp32>(this->hi);
	}
	constexpr inline operator fp64() const {
		return this->hi;
	}

	template<typename fpX>
	constexpr inline operator fpX() const {
		return static_cast<fpX>(this->hi) + static_cast<fpX>(this->lo);
	}

#endif
} Float64x2;

#endif /* FLOAT64X2_DEF_H */
