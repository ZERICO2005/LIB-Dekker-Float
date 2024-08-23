/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef FLOAT128X2_DEF_H
#define FLOAT128X2_DEF_H

#include "Float128.hpp"
#include "Float128x2.hpp"

/**
 * @brief defines the Float128x2 struct
 */

typedef float fp32;
typedef double fp64;

//------------------------------------------------------------------------------
// Float128x2 struct
//------------------------------------------------------------------------------

typedef struct Float128x2 {
	fp128 hi;
	fp128 lo;
#ifdef __cplusplus

/* Constructors */
	Float128x2() = default;

	constexpr inline Float128x2(const fp128 value_hi, const fp128 value_lo) :
		hi(value_hi), lo(value_lo) {}

	constexpr inline Float128x2(const fp128 values[2]) :
		hi(values[0]), lo(values[1]) {}

	constexpr inline Float128x2(const fp32 value) :
		hi((fp128)value), lo(0.0Q) {}

	constexpr inline Float128x2(const fp64 value) :
		hi((fp128)value), lo(0.0Q) {}

	#ifdef __float80
	constexpr inline Float128x2(const __float80 value) :
		hi((fp128)value), lo(0.0Q) {}
	#endif

	constexpr inline Float128x2(const fp128 value) :
		hi(value), lo(0.0Q) {}

	template<typename fpX>
	constexpr inline Float128x2(const fpX& value) :
		hi((fp128)value), lo((fp128)(value - (fpX)this->hi)) {}

/* Casts */

	constexpr inline operator fp32() const {
		return (fp32)this->hi;
	}
	constexpr inline operator fp64() const {
		return (fp64)this->hi;
	}
	#ifdef __float80
	constexpr inline operator __float80() const {
		return (__float80)this->hi;
	}
	#endif
	constexpr inline operator fp128() const {
		return this->hi;
	}

	template<typename fpX>
	constexpr inline operator fpX() const {
		return (fpX)this->hi + (fpX)this->lo;
	}

#endif
} Float128x2;

#endif /* FLOAT128X2_DEF_H */
