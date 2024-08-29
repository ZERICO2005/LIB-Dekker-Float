/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef FLOAT80X2_DEF_H
#define FLOAT80X2_DEF_H

#include "Float80.hpp"
#include "Float80x2.hpp"

#if 0

/**
 * @brief defines the Float80x2 struct
 */

typedef float fp32;
typedef double fp64;

//------------------------------------------------------------------------------
// Float80x2 struct
//------------------------------------------------------------------------------

typedef struct Float80x2 {
	fp80 hi;
	fp80 lo;
#ifdef __cplusplus

/* Constructors */
	Float80x2() = default;

	constexpr inline Float80x2(const fp80 value_hi, const fp80 value_lo) :
		hi(value_hi), lo(value_lo) {}

	constexpr inline Float80x2(const fp80 values[2]) :
		hi(values[0]), lo(values[1]) {}

	constexpr inline Float80x2(const fp32 value) :
		hi(static_cast<fp80>(value)), lo(0.0L) {}

	constexpr inline Float80x2(const fp64 value) :
		hi(static_cast<fp80>(value)), lo(0.0L) {}

	constexpr inline Float80x2(const fp80 value) :
		hi(value), lo(0.0L) {}

	template<typename fpX>
	constexpr inline Float80x2(const fpX& value) :
		hi(static_cast<fp80>(value)), lo(static_cast<fp80>(value - static_cast<fpX>(this->hi))) {}

/* Casts */

	constexpr inline operator fp32() const {
		return static_cast<fp32>(this->hi);
	}
	constexpr inline operator fp64() const {
		return static_cast<fp64>(this->hi);
	}
	constexpr inline operator fp80() const {
		return this->hi;
	}

	template<typename fpX>
	constexpr inline operator fpX() const {
		return static_cast<fpX>(this->hi) + static_cast<fpX>(this->lo);
	}

#endif
} Float80x2;

#endif

#endif /* FLOAT80X2_DEF_H */
