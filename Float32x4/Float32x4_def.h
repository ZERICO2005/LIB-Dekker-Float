/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/
#ifndef FLOAT32X4_DEF_H
#define FLOAT32X4_DEF_H

/**
 * @brief defines the Float32x4 struct
 */

typedef float fp32;
typedef double fp64;

#include "Float32x2/Float32x2_def.h"

//------------------------------------------------------------------------------
// Float32x4 struct
//------------------------------------------------------------------------------

typedef struct Float32x4 {
	fp32 val[4];
#ifdef __cplusplus

/* Constructors */
	Float32x4() = default;

	constexpr inline Float32x4(
		const fp32 val_0, const fp32 val_1, const fp32 val_2, const fp32 val_3
	) : val{val_0, val_1, val_2, val_3} {}

    constexpr inline Float32x4(const fp32 values[4])
        : val{values[0], values[1], values[2], values[3]} {}

	constexpr inline Float32x4(const fp32 (&values)[4]) :
		val{values[0], values[1], values[2], values[3]} {}

	constexpr inline Float32x4(const Float32x2 value) :
		val{value.hi, value.lo, 0.0f, 0.0f} {}
	
	constexpr inline Float32x4(const fp32 value) :
		val{value, 0.0f, 0.0f, 0.0f} {}

	constexpr inline Float32x4(const fp64 value) :
	val{
		static_cast<fp32>(value),
		static_cast<fp32>(value - static_cast<fp64>(val[0])),
		static_cast<fp32>(value - static_cast<fp64>(val[0]) - static_cast<fp64>(val[1])),
		0.0f
	} {}

	#ifdef __float80
		constexpr inline Float32x4(const __float80 value) :
		val{
			static_cast<fp32>(value),
			static_cast<fp32>(value - static_cast<__float80>(val[0])),
			static_cast<fp32>(value - static_cast<__float80>(val[0]) - static_cast<__float80>(val[1])),
			0.0f
		} {}
	#endif

	template<typename fpX>
	constexpr inline Float32x4(const fpX& value) :
		val{
			static_cast<fp32>(value),
			static_cast<fp32>(value - static_cast<fpX>(val[0])),
			static_cast<fp32>(value - static_cast<fpX>(val[0]) - static_cast<fpX>(val[1])),
			static_cast<fp32>(value - static_cast<fpX>(val[0]) - static_cast<fpX>(val[1]) - static_cast<fpX>(val[2]))
		} {}

/* Casts */

	constexpr inline operator Float32x2() const {
		return Float32x2(this->val[0], this->val[1]);
	}
	constexpr inline operator fp32() const {
		return this->val[0];
	}
	constexpr inline operator fp64() const {
		// Adds from smallest to largest
		return static_cast<fp64>(this->val[0]) + (
			static_cast<fp64>(this->val[1]) + static_cast<fp64>(this->val[2])
		);
	}
	#ifdef __float80
	constexpr inline operator __float80() const {
		// Adds from smallest to largest
		return static_cast<__float80>(this->val[0]) + (
			static_cast<__float80>(this->val[1]) + static_cast<__float80>(this->val[2])
		);
	}
	#endif

	template<typename fpX>
	constexpr inline operator fpX() const {
		// Adds from smallest to largest
		return static_cast<fpX>(this->val[0]) + (static_cast<fpX>(this->val[1]) + (
			static_cast<fpX>(this->val[2]) + static_cast<fpX>(this->val[3])
		));
	}

#endif
} Float32x4;

#endif /* FLOAT32X4_DEF_H */
