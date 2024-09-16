/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/
#ifndef FLOAT80X2_HPP
#define FLOAT80X2_HPP

#include <cstdint>
#include <math.h>
#include <cmath>
#include <cfenv>
#include <limits>

#include "Float80x2_def.h"

// Can be changed to other types for better accuracy
typedef long double Float80x2_Math;

#include "../LDF/LDF_arithmetic.hpp"

//------------------------------------------------------------------------------
// Float80x2 LDF Type Information
//------------------------------------------------------------------------------

#include "../LDF/LDF_type_info.hpp"
namespace LDF {
	template<> struct LDF_Type_Info<Float80x2> {
		static constexpr int FloatBase_Count = 2;
		static constexpr bool to_string_implemented = true;
		static constexpr bool from_string_implemented = true;
		static constexpr bool arithmetic_implemented = true;
		static constexpr bool numeric_limits_implemented = true;
		static constexpr bool bitwise_implemented = true;
		static constexpr bool constants_implemented = true;
		static constexpr bool basic_C99_math_implemented = true;
		static constexpr bool accurate_C99_math_implemented = false;
	};
}

//------------------------------------------------------------------------------
// Float80x2 String Operations
//------------------------------------------------------------------------------

#include "Float80x2_string.h"

#if __cplusplus >= 200809L
/**
 * @brief Wrapper for stringTo_Float80x2
 */
inline Float80x2 operator""_FP80X2(const char* str, std::size_t) {
	return stringTo_Float80x2(str, nullptr);
}
#endif

#include <istream>
/**
 * @brief Wrapper for stringTo_Float80x2
 */
std::istream& operator>>(std::istream& stream, Float80x2& value);

#include <ostream>
/**
 * @brief Wrapper for Float80x2_snprintf
 */
std::ostream& operator<<(std::ostream& stream, const Float80x2& value);

//------------------------------------------------------------------------------
// Float80x2 Comparison
//------------------------------------------------------------------------------

/* Comparison */

inline constexpr bool operator==(const Float80x2& x, const Float80x2& y) {
	return (x.hi == y.hi && x.lo == y.lo);
}
inline constexpr bool operator!=(const Float80x2& x, const Float80x2& y) {
	return (x.hi != y.hi || x.lo != y.lo);
}
inline constexpr bool operator<(const Float80x2& x, const Float80x2& y) {
	return (x.hi == y.hi) ? (x.lo < y.lo) : (x.hi < y.hi);
}
inline constexpr bool operator<=(const Float80x2& x, const Float80x2& y) {
	return (x.hi == y.hi) ? (x.lo <= y.lo) : (x.hi < y.hi);
}
inline constexpr bool operator>(const Float80x2& x, const Float80x2& y) {
	return (x.hi == y.hi) ? (x.lo > y.lo) : (x.hi > y.hi);
}
inline constexpr bool operator>=(const Float80x2& x, const Float80x2& y) {
	return (x.hi == y.hi) ? (x.lo >= y.lo) : (x.hi > y.hi);
}

/* Optimized Comparison */

inline constexpr bool operator==(const Float80x2& x, const fp80 y) {
	return (x.hi == y && x.lo == static_cast<fp80>(0.0));
}
inline constexpr bool operator!=(const Float80x2& x, const fp80 y) {
	return (x.hi != y || x.lo != static_cast<fp80>(0.0));
}
inline constexpr bool operator<(const Float80x2& x, const fp80 y) {
	return (x.hi == y) ? (x.lo < static_cast<fp80>(0.0)) : (x.hi < y);
}
inline constexpr bool operator<=(const Float80x2& x, const fp80 y) {
	return (x.hi == y) ? (x.lo <= static_cast<fp80>(0.0)) : (x.hi < y);
}
inline constexpr bool operator>(const Float80x2& x, const fp80 y) {
	return (x.hi == y) ? (x.lo > static_cast<fp80>(0.0)) : (x.hi > y);
}
inline constexpr bool operator>=(const Float80x2& x, const fp80 y) {
	return (x.hi == y) ? (x.lo >= static_cast<fp80>(0.0)) : (x.hi > y);
}

inline constexpr bool operator==(const fp80 x, const Float80x2& y) {
	return (x == y.hi && static_cast<fp80>(0.0) == y.lo);
}
inline constexpr bool operator!=(const fp80 x, const Float80x2& y) {
	return (x != y.hi || static_cast<fp80>(0.0) != y.lo);
}
inline constexpr bool operator<(const fp80 x, const Float80x2& y) {
	return (x == y.hi) ? (static_cast<fp80>(0.0) < y.lo) : (x < y.hi);
}
inline constexpr bool operator<=(const fp80 x, const Float80x2& y) {
	return (x == y.hi) ? (static_cast<fp80>(0.0) <= y.lo) : (x < y.hi);
}
inline constexpr bool operator>(const fp80 x, const Float80x2& y) {
	return (x == y.hi) ? (static_cast<fp80>(0.0) > y.lo) : (x > y.hi);
}
inline constexpr bool operator>=(const fp80 x, const Float80x2& y) {
	return (x == y.hi) ? (static_cast<fp80>(0.0) >= y.lo) : (x > y.hi);
}

/* Compare to Zero */

/** @brief Assumes that if x.hi is zero then x.lo is also zero */
inline constexpr bool isequal_zero(const Float80x2& x) {
	return (x.hi == static_cast<fp80>(0.0));
}
/** @brief Assumes that if x.hi is zero then x.lo is also zero */
inline constexpr bool isnotequal_zero(const Float80x2& x) {
	return (x.hi != static_cast<fp80>(0.0));
}
/** @brief Assumes that if x.hi is zero then x.lo is also zero */
inline constexpr bool isless_zero(const Float80x2& x) {
	return (x.hi < static_cast<fp80>(0.0));
}
/** @brief Assumes that if x.hi is zero then x.lo is also zero */
inline constexpr bool islessequal_zero(const Float80x2& x) {
	return (x.hi <= static_cast<fp80>(0.0));
}
/** @brief Assumes that if x.hi is zero then x.lo is also zero */
inline constexpr bool isgreater_zero(const Float80x2& x) {
	return (x.hi > static_cast<fp80>(0.0));
}
/** @brief Assumes that if x.hi is zero then x.lo is also zero */
inline constexpr bool isgreaterequal_zero(const Float80x2& x) {
	return (x.hi >= static_cast<fp80>(0.0));
}

//------------------------------------------------------------------------------
// Float80x2 Dekker Split
//------------------------------------------------------------------------------

#if defined(FLOATNX2_BITWISE_SPLIT) || defined(FLOAT80X2_BITWISE_SPLIT)
	/**
	 * @brief Splits the mantissa bits of a floating point value via bitwise
	 * operations for use in the dekker_mul12 function.
	 * @note This function might not work at the moment.
	 */
	inline Float80x2 dekker_split(const fp80 x) {
		Bitwise_Float80x2 r;
		const uint64_t Dekker_Split_Mask = ~((uint64_t)0x3FFFFFF);
		r.float_part.hi = x;
		r.binary_part.hi &= Dekker_Split_Mask;
		r.float_part.lo = x - r.float_part.hi;
		return r.float_part;
	}
#else
	/**
	 * @brief Splits the mantissa bits of a floating point value via
	 * multiplication for use in the dekker_mul12 function.
	 */
	inline Float80x2 dekker_split(const fp80 x) {
		constexpr fp80 Dekker_Scale = 4294967297.0L; // (2^ceil(64 / 2) + 1)
		fp80 p = x * Dekker_Scale;
		Float80x2 r;
		r.hi = (x - p) + p;
		r.lo = x - r.hi;
		return r;
	}
#endif

//------------------------------------------------------------------------------
// Float80x2 Basic Arithmetic
//------------------------------------------------------------------------------

template <> inline
Float80x2 LDF::add<Float80x2, Float80x2, Float80x2>
(const Float80x2& x, const Float80x2& y) {
	fp80 r_hi = x.hi + y.hi;
	fp80 r_lo = static_cast<fp80>(0.0);
	if (fabs(x.hi) > fabs(y.hi)) {
		r_lo = x.hi - r_hi + y.hi + y.lo + x.lo;
	} else {
		r_lo = y.hi - r_hi + x.hi + x.lo + y.lo;
	}

	Float80x2 c;
	c.hi = r_hi + r_lo;
	c.lo = r_hi - c.hi + r_lo;
	return c;
}

template <> inline
Float80x2 LDF::sub<Float80x2, Float80x2, Float80x2>
(const Float80x2& x, const Float80x2& y) {
	fp80 r_hi = x.hi - y.hi;
	fp80 r_lo = static_cast<fp80>(0.0);
	if (fabs(x.hi) > fabs(y.hi)) {
		r_lo = x.hi - r_hi - y.hi - y.lo + x.lo;
	} else {
		r_lo = -y.hi - r_hi + x.hi + x.lo - y.lo;
	}

	Float80x2 c;
	c.hi = r_hi + r_lo;
	c.lo = r_hi - c.hi + r_lo;
	return c;
}

/**
 * @brief Multiplies two fp80 values with result stored as a Float80x2
 */
template <> inline
Float80x2 LDF::mul<Float80x2, fp80, fp80>
(const fp80& x, const fp80& y) {
	Float80x2 a = dekker_split(x);
	Float80x2 b = dekker_split(y);
	fp80 p = a.hi * b.hi;
	fp80 q = a.hi * b.lo + a.lo * b.hi;

	Float80x2 r;
	r.hi = p + q;
	r.lo = p - r.hi + q + a.lo * b.lo;
	return r;
}

template <> inline
Float80x2 LDF::mul<Float80x2, Float80x2, Float80x2>
(const Float80x2& x, const Float80x2& y) {
	Float80x2 t = LDF::mul<Float80x2, fp80, fp80>(x.hi, y.hi);
	fp80 c = x.hi * y.lo + x.lo * y.hi + t.lo;

	Float80x2 r;
	r.hi = t.hi + c;
	r.lo = t.hi - r.hi + c;
	return r;
}

template <> inline
Float80x2 LDF::div<Float80x2, Float80x2, Float80x2>
(const Float80x2& x, const Float80x2& y) {
	fp80 u = x.hi / y.hi;
	Float80x2 t = LDF::mul<Float80x2, fp80, fp80>(u, y.hi);
	fp80 l = (x.hi - t.hi - t.lo + x.lo - u * y.lo) / y.hi;

	Float80x2 r;
	r.hi = u + l;
	r.lo = u - r.hi + l;
	return r;
}

/**
 * @brief Squares a fp80 value with the result stored as a Float80x2
 */
template <> inline
Float80x2 LDF::square<Float80x2, fp80>
(const fp80& x) {
	Float80x2 a = dekker_split(x);
	fp80 p = a.hi * a.hi;
	fp80 q = static_cast<fp80>(2.0) * (a.hi * a.lo);

	Float80x2 r;
	r.hi = p + q;
	r.lo = ((p - r.hi) + q) + (a.lo * a.lo);
	return r;
}

template <> inline
Float80x2 LDF::square<Float80x2, Float80x2>
(const Float80x2& x) {
	Float80x2 t = LDF::square<Float80x2, fp80>(x.hi);
	fp80 c = (static_cast<fp80>(2.0) * (x.hi * x.lo)) + t.lo;

	Float80x2 r;
	r.hi = t.hi + c;
	r.lo = (t.hi - r.hi) + c;
	return r;
}

template <> inline
Float80x2 LDF::recip<Float80x2, Float80x2>
(const Float80x2& y) {
	fp80 u = static_cast<fp80>(1.0) / y.hi;
	Float80x2 t = LDF::mul<Float80x2, fp80, fp80>(u, y.hi);
	fp80 l = (((static_cast<fp80>(1.0) - t.hi) - t.lo) - (u * y.lo)) / y.hi;

	Float80x2 r;
	r.hi = u + l;
	r.lo = (u - r.hi) + l;
	return r;
}

//------------------------------------------------------------------------------
// Float80x2 optimized arithmetic
//------------------------------------------------------------------------------

template <> inline
Float80x2 LDF::add<Float80x2, Float80x2, fp80>
(const Float80x2& x, const fp80& y) {
	fp80 r_hi = x.hi + y;
	fp80 r_lo = static_cast<fp80>(0.0);
	if (fabs(x.hi) > fabs(y)) {
		r_lo = x.hi - r_hi + y + x.lo;
	} else {
		r_lo = y - r_hi + x.hi + x.lo;
	}

	Float80x2 c;
	c.hi = r_hi + r_lo;
	c.lo = r_hi - c.hi + r_lo;
	return c;
}

template <> inline
Float80x2 LDF::add<Float80x2, fp80, Float80x2>
(const fp80& x, const Float80x2& y) {
	fp80 r_hi = x + y.hi;
	fp80 r_lo = static_cast<fp80>(0.0);
	if (fabs(x) > fabs(y.hi)) {
		r_lo = x - r_hi + y.hi + y.lo;
	} else {
		r_lo = y.hi - r_hi + x + y.lo;
	}

	Float80x2 c;
	c.hi = r_hi + r_lo;
	c.lo = r_hi - c.hi + r_lo;
	return c;
}

/**
 * @brief Adds two fp80 values with the result stored as a Float80x2
 */
template <> inline
Float80x2 LDF::add<Float80x2, fp80, fp80>
(const fp80& x, const fp80& y) {
	fp80 r_hi = x + y;
	fp80 r_lo = static_cast<fp80>(0.0);
	if (fabs(x) > fabs(y)) {
		r_lo = x - r_hi + y;
	} else {
		r_lo = y - r_hi + x;
	}

	Float80x2 c;
	c.hi = r_hi + r_lo;
	c.lo = r_hi - c.hi + r_lo;
	return c;
}

template <> inline
Float80x2 LDF::sub<Float80x2, Float80x2, fp80>
(const Float80x2& x, const fp80& y) {
	fp80 r_hi = x.hi - y;
	fp80 r_lo = static_cast<fp80>(0.0);
	if (fabs(x.hi) > fabs(y)) {
		r_lo = x.hi - r_hi - y + x.lo;
	} else {
		r_lo = -y - r_hi + x.hi + x.lo;
	}

	Float80x2 c;
	c.hi = r_hi + r_lo;
	c.lo = r_hi - c.hi + r_lo;
	return c;
}

template <> inline
Float80x2 LDF::sub<Float80x2, fp80, Float80x2>
(const fp80& x, const Float80x2& y) {
	fp80 r_hi = x - y.hi;
	fp80 r_lo = static_cast<fp80>(0.0);
	if (fabs(x) > fabs(y.hi)) {
		r_lo = x - r_hi - y.hi - y.lo;
	} else {
		r_lo = -y.hi - r_hi + x - y.lo;
	}

	Float80x2 c;
	c.hi = r_hi + r_lo;
	c.lo = r_hi - c.hi + r_lo;
	return c;
}

/**
 * @brief Subtracts two fp80 values with the result stored as a Float80x2
 */
template <> inline
Float80x2 LDF::sub<Float80x2, fp80, fp80>
(const fp80& x, const fp80& y) {
	fp80 r_hi = x - y;
	fp80 r_lo = static_cast<fp80>(0.0);
	if (fabs(x) > fabs(y)) {
		r_lo = x - r_hi - y;
	} else {
		r_lo = -y - r_hi + x;
	}

	Float80x2 c;
	c.hi = r_hi + r_lo;
	c.lo = r_hi - c.hi + r_lo;
	return c;
}

template <> inline
Float80x2 LDF::mul<Float80x2, Float80x2, fp80>
(const Float80x2& x, const fp80& y) {
	Float80x2 t = LDF::mul<Float80x2, fp80, fp80>(x.hi, y);
	fp80 c = (x.lo * y) + t.lo;

	Float80x2 r;
	r.hi = t.hi + c;
	r.lo = (t.hi - r.hi) + c;
	return r;
}

template <> inline
Float80x2 LDF::mul<Float80x2, fp80, Float80x2>
(const fp80& x, const Float80x2& y) {
	Float80x2 t = LDF::mul<Float80x2, fp80, fp80>(x, y.hi);
	fp80 c = (x * y.lo) + t.lo;

	Float80x2 r;
	r.hi = t.hi + c;
	r.lo = (t.hi - r.hi) + c;
	return r;
}

template <> inline
Float80x2 LDF::div<Float80x2, Float80x2, fp80>
(const Float80x2& x, const fp80& y) {
	fp80 u = x.hi / y;
	Float80x2 t = LDF::mul<Float80x2, fp80, fp80>(u, y);
	fp80 l = (((x.hi - t.hi) - t.lo) + x.lo) / y;

	Float80x2 r;
	r.hi = u + l;
	r.lo = (u - r.hi) + l;
	return r;
}

template <> inline
Float80x2 LDF::div<Float80x2, fp80, Float80x2>
(const fp80& x, const Float80x2& y) {
	fp80 u = x / y.hi;
	Float80x2 t = LDF::mul<Float80x2, fp80, fp80>(u, y.hi);
	fp80 l = (((x - t.hi) - t.lo) - (u * y.lo)) / y.hi;

	Float80x2 r;
	r.hi = u + l;
	r.lo = (u - r.hi) + l;
	return r;
}

/**
 * @brief Divides two fp80 values with the result stored as a Float80x2
 */
template <> inline
Float80x2 LDF::div<Float80x2, fp80, fp80>
(const fp80& x, const fp80& y) {
	fp80 u = x / y;
	Float80x2 t = LDF::mul<Float80x2, fp80, fp80>(u, y);
	fp80 l = ((x - t.hi) - t.lo) / y;

	Float80x2 r;
	r.hi = u + l;
	r.lo = (u - r.hi) + l;
	return r;
}

/**
 * @brief Calculates the reciprocal of a fp80 value with the result stored
 * as a Float80x2
 */

template <> inline
Float80x2 LDF::recip<Float80x2, fp80>
(const fp80& y) {
	fp80 u = static_cast<fp80>(1.0) / y;
	Float80x2 t = LDF::mul<Float80x2, fp80, fp80>(u, y);
	fp80 l = ((static_cast<fp80>(1.0) - t.hi) - t.lo) / y;

	Float80x2 r;
	r.hi = u + l;
	r.lo = (u - r.hi) + l;
	return r;
}

//------------------------------------------------------------------------------
// Float80x2 specialized arithmetic
//------------------------------------------------------------------------------

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero
 */
template <> inline constexpr
Float80x2 LDF::mul_pwr2<Float80x2, Float80x2, fp80>
(const Float80x2& x, const fp80& y) {
	return {x.hi * y, x.lo * y};
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero
 */
template <> inline constexpr
Float80x2 LDF::mul_pwr2<Float80x2, fp80, Float80x2>
(const fp80& x, const Float80x2& y) {
	return {x * y.hi, x * y.hi};
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero.
 * The result is stored as a Float80x2
 */
template <> inline constexpr
Float80x2 LDF::mul_pwr2<Float80x2, fp80, fp80>
(const fp80& x, const fp80& y) {
	return {x * y, static_cast<fp80>(0.0)};
}

//------------------------------------------------------------------------------
// Float80x2 bitwise operators
//------------------------------------------------------------------------------

template <> inline
Float80x2 LDF::bitwise_not<Float80x2>
(const Float80x2& x) {
	Float80x2 ret = x;
	struct Binary_Float80 { uint64_t mantissa; uint16_t exponent; };
	Binary_Float80* binary_part = reinterpret_cast<Binary_Float80*>(&ret);
	binary_part[0].mantissa = ~binary_part[0].mantissa;
	binary_part[0].exponent = ~binary_part[0].exponent;
	binary_part[1].mantissa = ~binary_part[1].mantissa;
	binary_part[1].exponent = ~binary_part[1].exponent;
	return ret;
}

template <> inline
Float80x2 LDF::bitwise_and<Float80x2, Float80x2>
(const Float80x2& x, const Float80x2& y) {
	Float80x2 ret = x;
	struct Binary_Float80 { uint64_t mantissa; uint16_t exponent; };
	Binary_Float80* ret_bin = reinterpret_cast<Binary_Float80*>(&ret);
	const Binary_Float80* y_bin = reinterpret_cast<const Binary_Float80*>(&y);
	ret_bin[0].mantissa &= y_bin[0].mantissa;
	ret_bin[0].exponent &= y_bin[0].exponent;
	ret_bin[1].mantissa &= y_bin[1].mantissa;
	ret_bin[1].exponent &= y_bin[1].exponent;
	return ret;
}

template <> inline
Float80x2 LDF::bitwise_andnot<Float80x2, Float80x2>
(const Float80x2& x, const Float80x2& y) {
	Float80x2 ret = x;
	struct Binary_Float80 { uint64_t mantissa; uint16_t exponent; };
	Binary_Float80* ret_bin = reinterpret_cast<Binary_Float80*>(&ret);
	const Binary_Float80* y_bin = reinterpret_cast<const Binary_Float80*>(&y);
	ret_bin[0].mantissa &= ~y_bin[0].mantissa;
	ret_bin[0].exponent &= ~y_bin[0].exponent;
	ret_bin[1].mantissa &= ~y_bin[1].mantissa;
	ret_bin[1].exponent &= ~y_bin[1].exponent;
	return ret;
}

template <> inline
Float80x2 LDF::bitwise_or<Float80x2, Float80x2>
(const Float80x2& x, const Float80x2& y) {
	Float80x2 ret = x;
	struct Binary_Float80 { uint64_t mantissa; uint16_t exponent; };
	Binary_Float80* ret_bin = reinterpret_cast<Binary_Float80*>(&ret);
	const Binary_Float80* y_bin = reinterpret_cast<const Binary_Float80*>(&y);
	ret_bin[0].mantissa |= y_bin[0].mantissa;
	ret_bin[0].exponent |= y_bin[0].exponent;
	ret_bin[1].mantissa |= y_bin[1].mantissa;
	ret_bin[1].exponent |= y_bin[1].exponent;
	return ret;
}

template <> inline
Float80x2 LDF::bitwise_xor<Float80x2, Float80x2>
(const Float80x2& x, const Float80x2& y) {
	Float80x2 ret = x;
	struct Binary_Float80 { uint64_t mantissa; uint16_t exponent; };
	Binary_Float80* ret_bin = reinterpret_cast<Binary_Float80*>(&ret);
	const Binary_Float80* y_bin = reinterpret_cast<const Binary_Float80*>(&y);
	ret_bin[0].mantissa ^= y_bin[0].mantissa;
	ret_bin[0].exponent ^= y_bin[0].exponent;
	ret_bin[1].mantissa ^= y_bin[1].mantissa;
	ret_bin[1].exponent ^= y_bin[1].exponent;
	return ret;
}

template <> inline
Float80x2 LDF::bitwise_and<Float80x2, fp80>
(const Float80x2& x, const fp80& y) {
	Float80x2 ret = x;
	struct Binary_Float80 { uint64_t mantissa; uint16_t exponent; };
	Binary_Float80* ret_bin = reinterpret_cast<Binary_Float80*>(&ret);
	const Binary_Float80* y_bin = reinterpret_cast<const Binary_Float80*>(&y);
	ret_bin[0].mantissa &= y_bin->mantissa;
	ret_bin[0].exponent &= y_bin->exponent;
	ret_bin[1].mantissa &= y_bin->mantissa;
	ret_bin[1].exponent &= y_bin->exponent;
	return ret;
}

template <> inline
Float80x2 LDF::bitwise_andnot<Float80x2, fp80>
(const Float80x2& x, const fp80& y) {
	Float80x2 ret = x;
	struct Binary_Float80 { uint64_t mantissa; uint16_t exponent; };
	Binary_Float80* ret_bin = reinterpret_cast<Binary_Float80*>(&ret);
	const Binary_Float80* y_bin = reinterpret_cast<const Binary_Float80*>(&y);
	ret_bin[0].mantissa &= ~y_bin->mantissa;
	ret_bin[0].exponent &= ~y_bin->exponent;
	ret_bin[1].mantissa &= ~y_bin->mantissa;
	ret_bin[1].exponent &= ~y_bin->exponent;
	return ret;
}

template <> inline
Float80x2 LDF::bitwise_or<Float80x2, fp80>
(const Float80x2& x, const fp80& y) {
	Float80x2 ret = x;
	struct Binary_Float80 { uint64_t mantissa; uint16_t exponent; };
	Binary_Float80* ret_bin = reinterpret_cast<Binary_Float80*>(&ret);
	const Binary_Float80* y_bin = reinterpret_cast<const Binary_Float80*>(&y);
	ret_bin[0].mantissa |= y_bin->mantissa;
	ret_bin[0].exponent |= y_bin->exponent;
	ret_bin[1].mantissa |= y_bin->mantissa;
	ret_bin[1].exponent |= y_bin->exponent;
	return ret;
}

template <> inline
Float80x2 LDF::bitwise_xor<Float80x2, fp80>
(const Float80x2& x, const fp80& y) {
	Float80x2 ret = x;
	struct Binary_Float80 { uint64_t mantissa; uint16_t exponent; };
	Binary_Float80* ret_bin = reinterpret_cast<Binary_Float80*>(&ret);
	const Binary_Float80* y_bin = reinterpret_cast<const Binary_Float80*>(&y);
	ret_bin[0].mantissa ^= y_bin->mantissa;
	ret_bin[0].exponent ^= y_bin->exponent;
	ret_bin[1].mantissa ^= y_bin->mantissa;
	ret_bin[1].exponent ^= y_bin->exponent;
	return ret;
}

//------------------------------------------------------------------------------
// Float80x2 Arithmetic Operator Overloads
//------------------------------------------------------------------------------

inline constexpr Float80x2 operator-(const Float80x2& x) {
	return {-x.hi, -x.lo};
}

inline Float80x2 operator+(const Float80x2& x, const Float80x2& y) {
	return LDF::add<Float80x2, Float80x2, Float80x2>(x, y);
}
inline Float80x2 operator-(const Float80x2& x, const Float80x2& y) {
	return LDF::sub<Float80x2, Float80x2, Float80x2>(x, y);
}
inline Float80x2 operator*(const Float80x2& x, const Float80x2& y) {
	return LDF::mul<Float80x2, Float80x2, Float80x2>(x, y);
}
inline Float80x2 operator/(const Float80x2& x, const Float80x2& y) {
	return LDF::div<Float80x2, Float80x2, Float80x2>(x, y);
}

inline Float80x2 operator+(const Float80x2& x, const fp80 y) {
	return LDF::add<Float80x2, Float80x2, fp80>(x, y);
}
inline Float80x2 operator-(const Float80x2& x, const fp80 y) {
	return LDF::sub<Float80x2, Float80x2, fp80>(x, y);
}
inline Float80x2 operator*(const Float80x2& x, const fp80 y) {
	return LDF::mul<Float80x2, Float80x2, fp80>(x, y);
}
inline Float80x2 operator/(const Float80x2& x, const fp80 y) {
	return LDF::div<Float80x2, Float80x2, fp80>(x, y);
}

inline Float80x2 operator+(const fp80 x, const Float80x2& y) {
	return LDF::add<Float80x2, fp80, Float80x2>(x, y);
}
inline Float80x2 operator-(const fp80 x, const Float80x2& y) {
	return LDF::sub<Float80x2, fp80, Float80x2>(x, y);
}
inline Float80x2 operator*(const fp80 x, const Float80x2& y) {
	return LDF::mul<Float80x2, fp80, Float80x2>(x, y);
}
inline Float80x2 operator/(const fp80 x, const Float80x2& y) {
	return LDF::div<Float80x2, fp80, Float80x2>(x, y);
}

inline Float80x2 square(const Float80x2& x) {
	return LDF::square<Float80x2, Float80x2>(x);
}
inline Float80x2 recip(const Float80x2& x) {
	return LDF::recip<Float80x2, Float80x2>(x);
}

inline constexpr Float80x2 mul_pwr2(const Float80x2& x, const fp80 y) {
	return LDF::mul_pwr2<Float80x2, Float80x2, fp80>(x, y);
}
inline constexpr Float80x2 mul_pwr2(const fp80 x, const Float80x2& y) {
	return LDF::mul_pwr2<Float80x2, fp80, Float80x2>(x, y);
}

// #if __cplusplus >= 201304L
// 	#define FLOAT80X2_RELAXED_CONSTEXPR constexpr
// #else
// 	#define FLOAT80X2_RELAXED_CONSTEXPR
// #endif

/* Compound Assignment */

inline Float80x2& operator+=(Float80x2& x, const Float80x2& y) {
	x = x + y;
	return x;
}
inline Float80x2& operator-=(Float80x2& x, const Float80x2& y) {
	x = x - y;
	return x;
}
inline Float80x2& operator*=(Float80x2& x, const Float80x2& y) {
	x = x * y;
	return x;
}
inline Float80x2& operator/=(Float80x2& x, const Float80x2& y) {
	x = x / y;
	return x;
}

inline Float80x2& operator+=(Float80x2& x, const fp80 y) {
	x = x + y;
	return x;
}
inline Float80x2& operator-=(Float80x2& x, const fp80 y) {
	x = x - y;
	return x;
}
inline Float80x2& operator*=(Float80x2& x, const fp80 y) {
	x = x * y;
	return x;
}
inline Float80x2& operator/=(Float80x2& x, const fp80 y) {
	x = x / y;
	return x;
}

/* Increment/Decrement */

inline Float80x2& operator++(Float80x2& x) {
	x += static_cast<fp80>(1.0);
	return x;
}

inline Float80x2& operator--(Float80x2& x) {
	x -= static_cast<fp80>(1.0);
	return x;
}

inline Float80x2 operator++(Float80x2& x, int) {
	Float80x2 temp = x;
	x += static_cast<fp80>(1.0);
	return temp;
}

inline Float80x2 operator--(Float80x2& x, int) {
	Float80x2 temp = x;
	x -= static_cast<fp80>(1.0);
	return temp;
}

//------------------------------------------------------------------------------
// Float80x2 Limits
//------------------------------------------------------------------------------

namespace std {
	template <>
	class numeric_limits<Float80x2> {
	public:
		static constexpr bool is_signed = true;
		static constexpr bool is_integer = false;
		static constexpr bool is_exact = false;
		static constexpr bool has_infinity = std::numeric_limits<fp80>::has_infinity;
		static constexpr bool has_quiet_NaN = std::numeric_limits<fp80>::has_quiet_NaN;
		static constexpr bool has_signaling_NaN = std::numeric_limits<fp80>::has_signaling_NaN;
		static constexpr std::float_denorm_style has_denorm = std::numeric_limits<fp80>::has_denorm;
		static constexpr bool is_bounded = true;
		static constexpr int digits = 128; // 2 * (63 mantissa bits + 1 implicit bit)
		static constexpr int digits10 = 38; // floor(mantissa bits * log10(2))
		/**
		 * @brief Dekker floats can represent FLT_MAX + FLT_MIN exactly, which
		 * is why an absurd amount of digits may be required.
		 */
		#if __cplusplus >= 201103L
		static constexpr int max_digits10 =
			std::numeric_limits<fp80>::max_exponent10 - std::numeric_limits<fp80>::min_exponent10 + std::numeric_limits<fp80>::digits10 + 1;
		#endif
		static constexpr int radix = std::numeric_limits<fp80>::radix;
		static constexpr int min_exponent   = std::numeric_limits<fp80>::min_exponent   + 64;
		static constexpr int min_exponent10 = std::numeric_limits<fp80>::min_exponent10 + 20 /* ceil(64 * log10(2)) */;
		static constexpr int max_exponent   = std::numeric_limits<fp80>::max_exponent  ;
		static constexpr int max_exponent10 = std::numeric_limits<fp80>::max_exponent10;
		static constexpr bool traps = std::numeric_limits<fp80>::traps;
		inline static constexpr Float80x2 min() {
			/** 
			 * @remarks libQD lists this as the minimum value that is fully
			 * normalized, although I am not sure if this is the best
			 * definition to use for min()
			 */
			return {std::numeric_limits<fp80>::min() * static_cast<fp80>(0x1.0p+64), std::numeric_limits<fp80>::min()};
			// return {std::numeric_limits<fp80>::min(), static_cast<fp80>(0.0)};
		}
	
		inline static constexpr Float80x2 max() {
			return {
				std::numeric_limits<fp80>::max(),
				std::numeric_limits<fp80>::max() * static_cast<fp80>(0x1.0p-65)
			};
		}
		#if __cplusplus >= 201103L
		inline static constexpr Float80x2 lowest() { return -max(); }
		#endif
		inline static constexpr Float80x2 epsilon() { return {static_cast<fp80>(0x1.0p-126), static_cast<fp80>(0.0)}; } // LDBL_EPSILON seems to be 0x1.0p-63
		inline static constexpr Float80x2 round_error() { return {static_cast<fp80>(0.5), static_cast<fp80>(0.0)}; }
		inline static constexpr Float80x2 infinity() {
			return {
				std::numeric_limits<fp80>::infinity(),
				std::numeric_limits<fp80>::infinity()
			};
		}
		inline static constexpr Float80x2 quiet_NaN() {
			return {
				std::numeric_limits<fp80>::quiet_NaN(),
				std::numeric_limits<fp80>::quiet_NaN()
			};
		}
		inline static constexpr Float80x2 signaling_NaN() {
			return {
				std::numeric_limits<fp80>::signaling_NaN(),
				std::numeric_limits<fp80>::signaling_NaN()
			};
		}
		inline static constexpr Float80x2 denorm_min() {
			return {std::numeric_limits<fp80>::denorm_min(), static_cast<fp80>(0.0)};
		}
	};
}

//------------------------------------------------------------------------------
// Float80x2 Constants
//------------------------------------------------------------------------------

#include "Float80x2_constants.hpp"

#if __cplusplus >= 201907L
#include <numbers>
namespace std {
	namespace numbers {
		template<> inline constexpr Float80x2 e_v          <Float80x2> = LDF::const_e         <Float80x2>(); /**< ~2.718281828 */
		template<> inline constexpr Float80x2 log2e_v      <Float80x2> = LDF::const_log2e     <Float80x2>(); /**< ~1.442695041 */
		template<> inline constexpr Float80x2 log10e_v     <Float80x2> = LDF::const_log10e    <Float80x2>(); /**< ~0.434294482 */
		template<> inline constexpr Float80x2 pi_v         <Float80x2> = LDF::const_pi        <Float80x2>(); /**< ~3.141592654 */
		template<> inline constexpr Float80x2 inv_pi_v     <Float80x2> = LDF::const_inv_pi    <Float80x2>(); /**< ~0.318309886 */
		template<> inline constexpr Float80x2 inv_sqrtpi_v <Float80x2> = LDF::const_inv_sqrtpi<Float80x2>(); /**< ~0.564189584 */
		template<> inline constexpr Float80x2 ln2_v        <Float80x2> = LDF::const_ln2       <Float80x2>(); /**< ~0.693147181 */
		template<> inline constexpr Float80x2 ln10_v       <Float80x2> = LDF::const_ln10      <Float80x2>(); /**< ~2.302585093 */
		template<> inline constexpr Float80x2 sqrt2_v      <Float80x2> = LDF::const_sqrt2     <Float80x2>(); /**< ~1.414213562 */
		template<> inline constexpr Float80x2 sqrt3_v      <Float80x2> = LDF::const_sqrt3     <Float80x2>(); /**< ~1.732050808 */
		template<> inline constexpr Float80x2 inv_sqrt3_v  <Float80x2> = LDF::const_inv_sqrt3 <Float80x2>(); /**< ~0.577350269 */
		template<> inline constexpr Float80x2 egamma_v     <Float80x2> = LDF::const_egamma    <Float80x2>(); /**< ~0.577215665 */
		template<> inline constexpr Float80x2 phi_v        <Float80x2> = LDF::const_phi       <Float80x2>(); /**< ~1.618033989 */
	}
}
#endif

//------------------------------------------------------------------------------
// Float80x2 Math Functions
//------------------------------------------------------------------------------

/* Floating Point Classify */

	/** @brief Returns true if x is negative */
	inline constexpr bool signbit(const Float80x2& x) {
		return std::signbit(x.hi);
	}

	/** @brief Returns true if x is finite */
	inline constexpr bool isfinite(const Float80x2& x) {
		return std::isfinite(x.hi);
	}

	/** @brief Returns true if x is +-infinity */
	inline constexpr bool isinf(const Float80x2& x) {
		return std::isinf(x.hi);
	}

	/** @brief Returns true if x is any kind of NaN */
	inline constexpr bool isnan(const Float80x2& x) {
		return std::isnan(x.hi);
	}

	/** @brief Returns true if x is normal */
	inline constexpr bool isnormal(const Float80x2& x) {
		return (std::isnormal(x.hi) && std::isnormal(x.lo));
	}
	
	/** @brief Returns true if x and y are unordered */
	inline constexpr bool isunordered(const Float80x2& x, const Float80x2& y) {
		return std::isunordered(x.hi, y.hi);
	}

	inline constexpr int fpclassify(const Float80x2& x) {
		return
			isinf(x)             ? FP_INFINITE :
			isnan(x)             ? FP_NAN      :
			isequal_zero(x) ? FP_ZERO     :
			isnormal(x)          ? FP_NORMAL   :
			FP_SUBNORMAL;
	}

/* Comparison */

	inline constexpr bool isgreater(const Float80x2& x, const Float80x2& y) {
		return (x > y);
	}
	inline constexpr bool isgreaterequal(const Float80x2& x, const Float80x2& y) {
		return (x >= y);
	}
	inline constexpr bool isless(const Float80x2& x, const Float80x2& y) {
		return (x < y);
	}
	inline constexpr bool islessequal(const Float80x2& x, const Float80x2& y) {
		return (x <= y);
	}
	inline constexpr bool islessgreater(const Float80x2& x, const Float80x2& y) {
		return (x < y) || (x > y);
	}

/* fmax and fmin */

	/**
	 * @brief Returns the fmax of x and y. Correctly handling NaN and signed zeros.
	 * You may use std::max as a faster alternative.
	 */
	inline constexpr Float80x2 fmax(const Float80x2& x, const Float80x2& y) {
		return
			(x < y) ? y :
			(y < x) ? x :
			isnan(x) ? y :
			isnan(y) ? x :
			signbit(x) ? y : x;
	}

	/**
	 * @brief Returns the fmin of x and y. Correctly handling NaN and signed zeros.
	 * You may use std::min as a faster alternative.
	 */
	inline constexpr Float80x2 fmin(const Float80x2& x, const Float80x2& y) {
		return
			(x > y) ? y :
			(y > x) ? x :
			isnan(x) ? y :
			isnan(y) ? x :
			signbit(x) ? x : y;
	}

/* Arithmetic */

	inline constexpr Float80x2 fmax(const Float80x2& x, const Float80x2& y, const Float80x2& z) {
		return fmax(fmax(x, y), z);
	}
	inline constexpr Float80x2 fmin(const Float80x2& x, const Float80x2& y, const Float80x2& z) {
		return fmin(fmin(x, y), z);
	}
	inline constexpr Float80x2 fabs(const Float80x2& x) {
		return (signbit(x)) ? -x : x;
	}
	inline constexpr Float80x2 fdim(const Float80x2& x, const Float80x2& y) {
		return (x > y) ? (x - y) : static_cast<Float80x2>(0.0);
	}
	/** @note Naive implementation of fma (Fused multiply add). May lose precision */
	inline Float80x2 fma(const Float80x2& x, const Float80x2& y, const Float80x2& z) {
		return (x * y) + z;
	}
	inline constexpr Float80x2 copysign(const Float80x2& x, const Float80x2& y) {
		return (
			(signbit(x)) != (signbit(y))
		) ? -x : x;
	}
	inline Float80x2 sqrt(const Float80x2& x) {
		if (isequal_zero(x)) {
			return x;
		}
		fp80 guess = sqrt(x.hi);
		return mul_pwr2((guess + x / guess), static_cast<fp80>(0.5));
	}
	inline Float80x2 cbrt(const Float80x2& x) {
		if (isequal_zero(x)) {
			return x;
		}
		fp80 guess = cbrt(x.hi);
		return (
			(static_cast<fp80>(2.0) * guess) + (x / LDF::square<Float80x2, fp80>(guess))
		) / static_cast<fp80>(3.0);
	}
	/** @note Naive implementation of hypot, may overflow for large inputs */
	inline Float80x2 hypot(const Float80x2& x, const Float80x2& y) {
		return sqrt(
			square(x) + square(y)
		);
	}
	/** @note Naive implementation of hypot, may overflow for large inputs */
	inline Float80x2 hypot(const Float80x2& x, const Float80x2& y, const Float80x2& z) {
		return sqrt(
			square(x) + square(y) + square(z)
		);
	}

/* Trigonometry */

	Float80x2 sin(const Float80x2& x);
	Float80x2 cos(const Float80x2& x);
	
	void sincos(const Float80x2& x, Float80x2& p_sin, Float80x2& p_cos);

	inline Float80x2 tan(const Float80x2& x) {
		Float80x2 sin_val, cos_val;
		sincos(x, sin_val, cos_val);
		return sin_val / cos_val;
	}

	/** 
	 * @note casts to Float80x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float80x2 asin(const Float80x2& x) { return static_cast<Float80x2>(asin(static_cast<Float80x2_Math>(x))); }
	/** 
	 * @note casts to Float80x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float80x2 acos(const Float80x2& x) { return static_cast<Float80x2>(acos(static_cast<Float80x2_Math>(x))); }
	/** 
	 * @note casts to Float80x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float80x2 atan(const Float80x2& x) { return static_cast<Float80x2>(atan(static_cast<Float80x2_Math>(x))); }
	/** 
	 * @note casts to Float80x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float80x2 sinh(const Float80x2& x) { return static_cast<Float80x2>(sinh(static_cast<Float80x2_Math>(x))); }
	/** 
	 * @note casts to Float80x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float80x2 cosh(const Float80x2& x) { return static_cast<Float80x2>(cosh(static_cast<Float80x2_Math>(x))); }
	/** 
	 * @note casts to Float80x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float80x2 tanh(const Float80x2& x) { return static_cast<Float80x2>(tanh(static_cast<Float80x2_Math>(x))); }
	/** 
	 * @note casts to Float80x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline void sinhcosh(const Float80x2& x, Float80x2& p_sinh, Float80x2& p_cosh) {
		p_sinh = sinh(x);
		p_cosh = cosh(x);
	}
	/** 
	 * @note casts to Float80x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float80x2 asinh(const Float80x2& x) { return static_cast<Float80x2>(asinh(static_cast<Float80x2_Math>(x))); }
	/** 
	 * @note casts to Float80x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float80x2 acosh(const Float80x2& x) { return static_cast<Float80x2>(acosh(static_cast<Float80x2_Math>(x))); }
	/** 
	 * @note casts to Float80x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float80x2 atanh(const Float80x2& x) { return static_cast<Float80x2>(atanh(static_cast<Float80x2_Math>(x))); }
	/** 
	 * @note casts to Float80x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float80x2 atan2(const Float80x2& y, const Float80x2& x) {
		return static_cast<Float80x2>(atan2(static_cast<Float80x2_Math>(y), static_cast<Float80x2_Math>(x)));
	}

/* Logarithms and Exponents */

	Float80x2 log(const Float80x2& x);
	
	/** 
	 * @note Naive implementation of log1p
	 */
	inline Float80x2 log1p(const Float80x2& x) {
		return log(x + static_cast<fp80>(1.0));
	}
	
	/** 
	 * @note Naive implementation of log2
	 */
	inline Float80x2 log2(const Float80x2& x) {
		return log(x) * LDF::const_log2e<Float80x2>();
	}

	/** 
	 * @note Naive implementation of log10
	 */
	inline Float80x2 log10(const Float80x2& x) {
		return log(x) * LDF::const_log10e<Float80x2>();
	}
	
	inline Float80x2 logb(const Float80x2 x) { return logb(x.hi + x.lo); }

	Float80x2 exp(const Float80x2& x);

	Float80x2 expm1(const Float80x2& x);

	inline Float80x2 exp2(const Float80x2& x) {
		return exp(x * LDF::const_ln2<Float80x2>());
	}

	inline Float80x2 exp10(const Float80x2& x) {
		return exp(x * LDF::const_ln10<Float80x2>());
	}

	inline Float80x2 pow(const Float80x2& x, const Float80x2& y) {
		return isequal_zero(x) ? (
			isequal_zero(y) ? static_cast<Float80x2>(1.0) : static_cast<Float80x2>(0.0)
		) : exp(y * log(x));
	}

	inline Float80x2 pow(const Float80x2& x, const fp80 y) {
		return isequal_zero(x) ? (
			(y == static_cast<fp80>(0.0)) ? static_cast<Float80x2>(1.0) : static_cast<Float80x2>(0.0)
		) : exp(y * log(x));
	}
	
/* Rounding */

	inline Float80x2 trunc(const Float80x2& x) {
		Float80x2 int_hi = trunc(x.hi);
		Float80x2 int_lo = trunc(x.lo);
		fp80 frac_hi = x.hi - int_hi.hi;
		fp80 frac_lo = x.lo - int_lo.hi;
		// Sum in increasing order
		Float80x2 trunc_all = (
			LDF::add<Float80x2, fp80, fp80>(frac_hi, frac_lo) >= static_cast<fp80>(1.0)
		) ? static_cast<Float80x2>(1.0) : static_cast<Float80x2>(0.0);
		trunc_all += int_lo;
		trunc_all += int_hi;
		return trunc_all;
	}
	inline Float80x2 floor(const Float80x2& x) {
		Float80x2 int_part = trunc(x);
		return (
			isless_zero(x) && int_part != x
		) ? int_part - static_cast<fp80>(1.0) : int_part;
	}
	inline Float80x2 ceil(const Float80x2& x) {
		Float80x2 int_part = trunc(x);
		return (
			isgreater_zero(x) && int_part != x
		) ? int_part + static_cast<fp80>(1.0) : int_part;
	}
	inline Float80x2 round(const Float80x2& x) {
		Float80x2 int_part = trunc(x);
		Float80x2 frac_part = x - int_part;
		if (isgreaterequal_zero(x)) {
			if (frac_part >= static_cast<fp80>(0.5)) {
				return int_part + static_cast<fp80>(1.0);
			}
			return int_part;
		}
		if (frac_part <= static_cast<fp80>(-0.5)) {
			return int_part - static_cast<fp80>(1.0);
		}
		return int_part;
	}
	inline Float80x2 rint(const Float80x2& x) {
		switch (fegetround()) {
			default:
			case FE_TOWARDZERO:
				return trunc(x);
			case FE_DOWNWARD:
				return floor(x);
			case FE_UPWARD:
				return ceil(x);
			case FE_TONEAREST:
				return round(x);
		}
	}
	inline long lround(const Float80x2& x) {
		return static_cast<long>(round(x));
	}
	inline long lrint(const Float80x2& x) {
		return static_cast<long>(rint(x));
	}
	inline long long llround(const Float80x2& x) {
		return static_cast<long long>(round(x));
	}
	inline long long llrint(const Float80x2& x) {
		return static_cast<long long>(rint(x));
	}

	/* Integer and Remainder */

	inline Float80x2 fmod(const Float80x2& x, const Float80x2& y) {
		Float80x2 trunc_part = trunc(x / y);
		return x - y * trunc_part;
	}
	inline Float80x2 modf(const Float80x2& x, Float80x2& int_part) {
		Float80x2 trunc_part = trunc(x);
		int_part = trunc_part;
		return x - trunc_part;
	}
	inline Float80x2 nearbyint(const Float80x2& x) {
		return rint(x);
	}
	inline Float80x2 remainder(const Float80x2& x, const Float80x2& y) {
		Float80x2 round_part = round(x / y);
		return x - y * round_part;
	}
	inline Float80x2 remquo(const Float80x2& x, const Float80x2& y, int& quo) {
		Float80x2 q = round(x / y);
		Float80x2 r = x - y * q;
		quo = static_cast<int>(q.hi + q.lo);
		return r;
	}

/* Float Exponents */

	/**
	 * @brief Extracts the exponent of a Float80x2 value to compute the
	 * binary logarithm.
	 */
	inline int ilogb(const Float80x2& x) {
		return ilogb(x.hi + x.lo);
	}
	/**
	 * @brief Returns a normalized Float80x2 value and the exponent in
	 * the form [0.0, 1.0) * 2^expon
	 */
	inline Float80x2 frexp(const Float80x2& x, int& expon) {
		Float80x2 ret;
		expon = ilogb(x.hi + x.lo) + 1;
		ret.hi = ldexp(x.hi, -(expon));
		ret.lo = ldexp(x.lo, -(expon));
		return ret;
	}
	/**
	 * @brief Multiplies a Float80x2 value by 2^expon
	 */
	inline Float80x2 ldexp(const Float80x2& x, int expon) {
		Float80x2 ret;
		ret.hi = ldexp(x.hi, expon);
		ret.lo = isfinite(x.hi) ? ldexp(x.lo, expon) : x.hi;
		return ret;
	}
	/**
	 * @brief Multiplies a Float80x2 value by FLT_RADIX^expon
	 */
	inline Float80x2 scalbn(const Float80x2& x, int expon) {
		Float80x2 ret;
		ret.hi = scalbn(x.hi, expon);
		ret.lo = isfinite(x.hi) ? scalbn(x.lo, expon) : x.hi;
		return ret;
	}
	/**
	 * @brief Multiplies a Float80x2 value by FLT_RADIX^expon
	 */
	inline Float80x2 scalbln(const Float80x2& x, long expon) {
		Float80x2 ret;
		ret.hi = scalbln(x.hi, expon);
		ret.lo = isfinite(x.hi) ? scalbln(x.lo, expon) : x.hi;
		return ret;
	}

/* Transcendental Functions */
	
	Float80x2 erf(const Float80x2& x);

	/**
	 * @brief Calculates `1 - erf(x)` without losing precision when `x > 0`.
	 * @note Result will round to zero when `x > ~106.743878`
	 */
	Float80x2 erfc(const Float80x2& x);

	Float80x2 tgamma(const Float80x2& x);

	/** 
	 * @note naive implementation of lgamma(x)
	 */
	inline Float80x2 lgamma(const Float80x2& x) {
		return log(fabs(tgamma(x)));
	}

#endif /* FLOAT80X2_HPP */
