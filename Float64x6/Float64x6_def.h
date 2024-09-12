/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/
#ifndef FLOAT64X6_DEF_H
#define FLOAT64X6_DEF_H

/**
 * @brief defines the Float64x4 struct
 */

#include "../Float32/Float32.h"
#include "../Float64/Float64.h"

#include "../Float64x2/Float64x2_def.h"
#include "../Float64x4/Float64x4_def.h"

//------------------------------------------------------------------------------
// Float64x4 struct
//------------------------------------------------------------------------------

typedef struct Float64x6 {
	fp64 val[6];
#ifdef __cplusplus

/* Constructors */
	Float64x6() = default;

	constexpr inline Float64x6(
		const fp64 val_0, const fp64 val_1, const fp64 val_2, const fp64 val_3, const fp64 val_4, const fp64 val_5
	) : val{val_0, val_1, val_2, val_3, val_4, val_5} {}

	constexpr inline Float64x6(const fp64 values[6]) :
		val{values[0], values[1], values[2], values[3], values[4], values[5]} {}

	constexpr inline Float64x6(const fp64 (&values)[6]) :
		val{values[0], values[1], values[2], values[3], values[4], values[5]} {}

	constexpr inline Float64x6(const Float64x4& value) :
		val{value.val[0], value.val[1], value.val[2], value.val[3], 0.0, 0.0} {}

	constexpr inline Float64x6(const Float64x2& value) :
		val{value.hi, value.lo, 0.0, 0.0, 0.0, 0.0} {}

	constexpr inline Float64x6(const fp32 value) :
		val{static_cast<fp64>(value), 0.0, 0.0, 0.0, 0.0, 0.0} {}
	
	constexpr inline Float64x6(const fp64 value) :
		val{value, 0.0, 0.0, 0.0, 0.0, 0.0} {}


	template<typename fpX>
	constexpr inline Float64x6(const fpX& value) :
		val{
			static_cast<fp64>(value),
			static_cast<fp64>(value - static_cast<fpX>(val[0])),
			static_cast<fp64>(value - static_cast<fpX>(val[0]) - static_cast<fpX>(val[1])),
			static_cast<fp64>(value - static_cast<fpX>(val[0]) - static_cast<fpX>(val[1]) - static_cast<fpX>(val[2])),
			static_cast<fp64>(value - static_cast<fpX>(val[0]) - static_cast<fpX>(val[1]) - static_cast<fpX>(val[2]) - static_cast<fpX>(val[3])),
			static_cast<fp64>(value - static_cast<fpX>(val[0]) - static_cast<fpX>(val[1]) - static_cast<fpX>(val[2]) - static_cast<fpX>(val[3]) - static_cast<fpX>(val[4]))
		} {}

/* Casts */

	constexpr inline operator Float64x2() const {
		return Float64x2(this->val[0], this->val[1]);
	}
	constexpr inline operator Float64x4() const {
		return Float64x4(this->val[0], this->val[1], this->val[2], this->val[3]);
	}
	constexpr inline operator fp32() const {
		return static_cast<fp32>(this->val[0]);
	}
	constexpr inline operator fp64() const {
		return static_cast<fp64>(this->val[0]);
	}

	template<typename fpX>
	constexpr inline operator fpX() const {
		// Adds from smallest to largest
		return static_cast<fpX>(this->val[0]) + (static_cast<fpX>(this->val[1]) + (
			static_cast<fpX>(this->val[2]) + (static_cast<fpX>(this->val[3])
				+ (static_cast<fpX>(this->val[4]) + static_cast<fpX>(this->val[5]))
			)
		));
	}

#endif
} Float64x6;

#endif /* FLOAT64X6_DEF_H */
