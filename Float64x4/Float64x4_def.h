/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/
#ifndef FLOAT64X4_DEF_H
#define FLOAT64X4_DEF_H

/**
 * @brief defines the Float64x4 struct
 */

typedef float fp32;
typedef double fp64;

#include "Float64x2/Float64x2_def.h"

//------------------------------------------------------------------------------
// Float64x4 struct
//------------------------------------------------------------------------------

typedef struct Float64x4 {
	fp64 val[4];
#ifdef __cplusplus

/* Constructors */
	Float64x4() = default;


	constexpr inline Float64x4(
		const fp64 val_0, const fp64 val_1, const fp64 val_2, const fp64 val_3
	) : val{val_0, val_1, val_2, val_3} {}

	constexpr inline Float64x4(const fp64 values[4])
		: val{values[0], values[1], values[2], values[3]} {}

	constexpr inline Float64x4(const double (&values)[4])
		: val{values[0], values[1], values[2], values[3]} {}

	constexpr inline Float64x4(const Float64x2& value) :
		val{value.hi, value.lo, 0.0, 0.0} {}

	constexpr inline Float64x4(const fp32 value) :
		val{static_cast<fp64>(value), 0.0, 0.0, 0.0} {}
	
	constexpr inline Float64x4(const fp64 value) :
		val{value, 0.0, 0.0, 0.0} {}

	#ifdef __float80
		constexpr inline Float64x4(const __float80 value) :
		val{static_cast<fp64>(value), static_cast<fp64>(value - (__float80)val[0]), 0.0, 0.0} {}
	#endif
	#ifdef __float128
		constexpr inline Float64x4(const __float128 value) :
		val{
			static_cast<fp64>(value),
			static_cast<fp64>(value - (__float128)val[0]),
			static_cast<fp64>(value - (__float128)val[0] - (__float128)val[1]), 0.0
		} {}
	#endif

	template<typename fpX>
	constexpr inline Float64x4(const fpX& value) :
		val{
			static_cast<fp64>(value),
			static_cast<fp64>(value - static_cast<fpX>(val[0])),
			static_cast<fp64>(value - static_cast<fpX>(val[0]) - static_cast<fpX>(val[1])),
			static_cast<fp64>(value - static_cast<fpX>(val[0]) - static_cast<fpX>(val[1]) - static_cast<fpX>(val[2]))
		} {}

/* Casts */

	constexpr inline operator Float64x2() const {
		return Float64x2(this->val[0], this->val[1]);
	}
	constexpr inline operator fp32() const {
		return static_cast<fp32>(this->val[0]);
	}
	constexpr inline operator fp64() const {
		return static_cast<fp64>(this->val[0]);
	}
	#ifdef __float80
	constexpr inline operator __float80() const {
		return static_cast<__float80>(this->val[0]) + static_cast<__float80>(this->val[1]);
	}
	#endif
	#ifdef __float128
	constexpr inline operator __float128() const {
		// Adds from smallest to largest
		return static_cast<__float128>(this->val[0]) + (
			static_cast<__float128>(this->val[1]) + static_cast<__float128>(this->val[2])
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
} Float64x4;

#endif /* FLOAT64X4_DEF_H */
