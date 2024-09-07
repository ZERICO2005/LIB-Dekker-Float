/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/
#ifndef FLOAT32X2_HPP
#define FLOAT32X2_HPP

// #include "Float32x2.h"
#include "Float32x2_def.h"

#include <cstdarg>
#include <cstdint>
#include <math.h>
#include <cmath>
#include <cfenv>
#include <limits>

#include "../FloatNxN/FloatNxN_arithmetic.hpp"

typedef float fp32;
typedef double fp64;

// Can be changed to other types for better accuracy
typedef fp64 Float32x2_Math;

//------------------------------------------------------------------------------
// Float32x2 String Operations
//------------------------------------------------------------------------------

#include "Float32x2_string.h"

#if __cplusplus >= 200809L
/**
 * @brief Wrapper for stringTo_Float32x2
 */
inline Float32x2 operator""_FP32X2(const char* str, std::size_t) {
	return stringTo_Float32x2(str, nullptr);
}
#endif

#include <istream>
/**
 * @brief Wrapper for stringTo_Float32x2
 */
std::istream& operator>>(std::istream& stream, Float32x2& value);

#include <ostream>
/**
 * @brief Wrapper for Float32x2_snprintf
 */
std::ostream& operator<<(std::ostream& stream, const Float32x2& value);

//------------------------------------------------------------------------------
// Float32x2 Comparison
//------------------------------------------------------------------------------

/* Comparison */

inline constexpr bool operator==(const Float32x2 x, const Float32x2 y) {
	return (x.hi == y.hi && x.lo == y.lo);
}
inline constexpr bool operator!=(const Float32x2 x, const Float32x2 y) {
	return (x.hi != y.hi || x.lo != y.lo);
}
inline constexpr bool operator<(const Float32x2 x, const Float32x2 y) {
	return (x.hi == y.hi) ? (x.lo < y.lo) : (x.hi < y.hi);
}
inline constexpr bool operator<=(const Float32x2 x, const Float32x2 y) {
	return (x.hi == y.hi) ? (x.lo <= y.lo) : (x.hi < y.hi);
}
inline constexpr bool operator>(const Float32x2 x, const Float32x2 y) {
	return (x.hi == y.hi) ? (x.lo > y.lo) : (x.hi > y.hi);
}
inline constexpr bool operator>=(const Float32x2 x, const Float32x2 y) {
	return (x.hi == y.hi) ? (x.lo >= y.lo) : (x.hi > y.hi);
}

/* Optimized Comparison */

inline constexpr bool operator==(const Float32x2 x, const fp32 y) {
	return (x.hi == y && x.lo == static_cast<fp32>(0.0));
}
inline constexpr bool operator!=(const Float32x2 x, const fp32 y) {
	return (x.hi != y || x.lo != static_cast<fp32>(0.0));
}
inline constexpr bool operator<(const Float32x2 x, const fp32 y) {
	return (x.hi == y) ? (x.lo < static_cast<fp32>(0.0)) : (x.hi < y);
}
inline constexpr bool operator<=(const Float32x2 x, const fp32 y) {
	return (x.hi == y) ? (x.lo <= static_cast<fp32>(0.0)) : (x.hi < y);
}
inline constexpr bool operator>(const Float32x2 x, const fp32 y) {
	return (x.hi == y) ? (x.lo > static_cast<fp32>(0.0)) : (x.hi > y);
}
inline constexpr bool operator>=(const Float32x2 x, const fp32 y) {
	return (x.hi == y) ? (x.lo >= static_cast<fp32>(0.0)) : (x.hi > y);
}

inline constexpr bool operator==(const fp32 x, const Float32x2 y) {
	return (x == y.hi && static_cast<fp32>(0.0) == y.lo);
}
inline constexpr bool operator!=(const fp32 x, const Float32x2 y) {
	return (x != y.hi || static_cast<fp32>(0.0) != y.lo);
}
inline constexpr bool operator<(const fp32 x, const Float32x2 y) {
	return (x == y.hi) ? (static_cast<fp32>(0.0) < y.lo) : (x < y.hi);
}
inline constexpr bool operator<=(const fp32 x, const Float32x2 y) {
	return (x == y.hi) ? (static_cast<fp32>(0.0) <= y.lo) : (x < y.hi);
}
inline constexpr bool operator>(const fp32 x, const Float32x2 y) {
	return (x == y.hi) ? (static_cast<fp32>(0.0) > y.lo) : (x > y.hi);
}
inline constexpr bool operator>=(const fp32 x, const Float32x2 y) {
	return (x == y.hi) ? (static_cast<fp32>(0.0) >= y.lo) : (x > y.hi);
}

/* Compare to Zero */

/** @brief Assumes that if x.hi is zero then x.lo is also zero */
inline constexpr bool isequal_zero(const Float32x2 x) {
	return (x.hi == static_cast<fp32>(0.0));
}
/** @brief Assumes that if x.hi is zero then x.lo is also zero */
inline constexpr bool isnotequal_zero(const Float32x2 x) {
	return (x.hi != static_cast<fp32>(0.0));
}
/** @brief Assumes that if x.hi is zero then x.lo is also zero */
inline constexpr bool isless_zero(const Float32x2 x) {
	return (x.hi < static_cast<fp32>(0.0));
}
/** @brief Assumes that if x.hi is zero then x.lo is also zero */
inline constexpr bool islessequal_zero(const Float32x2 x) {
	return (x.hi <= static_cast<fp32>(0.0));
}
/** @brief Assumes that if x.hi is zero then x.lo is also zero */
inline constexpr bool isgreater_zero(const Float32x2 x) {
	return (x.hi > static_cast<fp32>(0.0));
}
/** @brief Assumes that if x.hi is zero then x.lo is also zero */
inline constexpr bool isgreaterequal_zero(const Float32x2 x) {
	return (x.hi >= static_cast<fp32>(0.0));
}

//------------------------------------------------------------------------------
// Float32x2 Dekker Split
//------------------------------------------------------------------------------

#if defined(FLOATNX2_BITWISE_SPLIT) || defined(FLOAT32X2_BITWISE_SPLIT)
	/**
	 * @brief Splits the mantissa bits of a floating point value via bitwise
	 * operations for use in the dekker_mul12 function.
	 * @note This function might not work at the moment.
	 */
	inline Float32x2 dekker_split(const fp32 x) {
		Bitwise_Float32x2 r;
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
	inline Float32x2 dekker_split(const fp32 x) {
		constexpr fp32 Dekker_Scale = 4097.0f; // (2^ceil(24 / 2) + 1)
		fp32 p = x * Dekker_Scale;
		Float32x2 r;
		r.hi = (x - p) + p;
		r.lo = x - r.hi;
		return r;
	}
#endif

//------------------------------------------------------------------------------
// Float32x2 Basic Arithmetic
//------------------------------------------------------------------------------

template <> inline
Float32x2 LDF::add<Float32x2, Float32x2, Float32x2>
(const Float32x2& x, const Float32x2& y) {
	fp32 r_hi = x.hi + y.hi;
	fp32 r_lo = static_cast<fp32>(0.0);
	if (fabs(x.hi) > fabs(y.hi)) {
		r_lo = x.hi - r_hi + y.hi + y.lo + x.lo;
	} else {
		r_lo = y.hi - r_hi + x.hi + x.lo + y.lo;
	}

	Float32x2 c;
	c.hi = r_hi + r_lo;
	c.lo = r_hi - c.hi + r_lo;
	return c;
}

template <> inline
Float32x2 LDF::sub<Float32x2, Float32x2, Float32x2>
(const Float32x2& x, const Float32x2& y) {
	fp32 r_hi = x.hi - y.hi;
	fp32 r_lo = static_cast<fp32>(0.0);
	if (fabs(x.hi) > fabs(y.hi)) {
		r_lo = x.hi - r_hi - y.hi - y.lo + x.lo;
	} else {
		r_lo = -y.hi - r_hi + x.hi + x.lo - y.lo;
	}

	Float32x2 c;
	c.hi = r_hi + r_lo;
	c.lo = r_hi - c.hi + r_lo;
	return c;
}

/**
 * @brief Multiplies two fp32 values with result stored as a Float32x2
 */
template <> inline
Float32x2 LDF::mul<Float32x2, fp32, fp32>
(const fp32& x, const fp32& y) {
	Float32x2 a = dekker_split(x);
	Float32x2 b = dekker_split(y);
	fp32 p = a.hi * b.hi;
	fp32 q = a.hi * b.lo + a.lo * b.hi;

	Float32x2 r;
	r.hi = p + q;
	r.lo = p - r.hi + q + a.lo * b.lo;
	return r;
}

template <> inline
Float32x2 LDF::mul<Float32x2, Float32x2, Float32x2>
(const Float32x2& x, const Float32x2& y) {
	Float32x2 t = LDF::mul<Float32x2, fp32, fp32>(x.hi, y.hi);
	fp32 c = x.hi * y.lo + x.lo * y.hi + t.lo;

	Float32x2 r;
	r.hi = t.hi + c;
	r.lo = t.hi - r.hi + c;
	return r;
}

template <> inline
Float32x2 LDF::div<Float32x2, Float32x2, Float32x2>
(const Float32x2& x, const Float32x2& y) {
	fp32 u = x.hi / y.hi;
	Float32x2 t = LDF::mul<Float32x2, fp32, fp32>(u, y.hi);
	fp32 l = (x.hi - t.hi - t.lo + x.lo - u * y.lo) / y.hi;

	Float32x2 r;
	r.hi = u + l;
	r.lo = u - r.hi + l;
	return r;
}

/**
 * @brief Squares a fp32 value with the result stored as a Float32x2
 */
template <> inline
Float32x2 LDF::square<Float32x2, fp32>
(const fp32& x) {
	Float32x2 a = dekker_split(x);
	fp32 p = a.hi * a.hi;
	fp32 q = static_cast<fp32>(2.0) * (a.hi * a.lo);

	Float32x2 r;
	r.hi = p + q;
	r.lo = ((p - r.hi) + q) + (a.lo * a.lo);
	return r;
}

template <> inline
Float32x2 LDF::square<Float32x2, Float32x2>
(const Float32x2& x) {
	Float32x2 t = LDF::square<Float32x2, fp32>(x.hi);
	fp32 c = (static_cast<fp32>(2.0) * (x.hi * x.lo)) + t.lo;

	Float32x2 r;
	r.hi = t.hi + c;
	r.lo = (t.hi - r.hi) + c;
	return r;
}

template <> inline
Float32x2 LDF::recip<Float32x2, Float32x2>
(const Float32x2& y) {
	fp32 u = static_cast<fp32>(1.0) / y.hi;
	Float32x2 t = LDF::mul<Float32x2, fp32, fp32>(u, y.hi);
	fp32 l = (((static_cast<fp32>(1.0) - t.hi) - t.lo) - (u * y.lo)) / y.hi;

	Float32x2 r;
	r.hi = u + l;
	r.lo = (u - r.hi) + l;
	return r;
}

//------------------------------------------------------------------------------
// Float32x2 optimized arithmetic
//------------------------------------------------------------------------------

template <> inline
Float32x2 LDF::add<Float32x2, Float32x2, fp32>
(const Float32x2& x, const fp32& y) {
	fp32 r_hi = x.hi + y;
	fp32 r_lo = static_cast<fp32>(0.0);
	if (fabs(x.hi) > fabs(y)) {
		r_lo = x.hi - r_hi + y + x.lo;
	} else {
		r_lo = y - r_hi + x.hi + x.lo;
	}

	Float32x2 c;
	c.hi = r_hi + r_lo;
	c.lo = r_hi - c.hi + r_lo;
	return c;
}

template <> inline
Float32x2 LDF::add<Float32x2, fp32, Float32x2>
(const fp32& x, const Float32x2& y) {
	fp32 r_hi = x + y.hi;
	fp32 r_lo = static_cast<fp32>(0.0);
	if (fabs(x) > fabs(y.hi)) {
		r_lo = x - r_hi + y.hi + y.lo;
	} else {
		r_lo = y.hi - r_hi + x + y.lo;
	}

	Float32x2 c;
	c.hi = r_hi + r_lo;
	c.lo = r_hi - c.hi + r_lo;
	return c;
}

/**
 * @brief Adds two fp32 values with the result stored as a Float32x2
 */
template <> inline
Float32x2 LDF::add<Float32x2, fp32, fp32>
(const fp32& x, const fp32& y) {
	fp32 r_hi = x + y;
	fp32 r_lo = static_cast<fp32>(0.0);
	if (fabs(x) > fabs(y)) {
		r_lo = x - r_hi + y;
	} else {
		r_lo = y - r_hi + x;
	}

	Float32x2 c;
	c.hi = r_hi + r_lo;
	c.lo = r_hi - c.hi + r_lo;
	return c;
}

template <> inline
Float32x2 LDF::sub<Float32x2, Float32x2, fp32>
(const Float32x2& x, const fp32& y) {
	fp32 r_hi = x.hi - y;
	fp32 r_lo = static_cast<fp32>(0.0);
	if (fabs(x.hi) > fabs(y)) {
		r_lo = x.hi - r_hi - y + x.lo;
	} else {
		r_lo = -y - r_hi + x.hi + x.lo;
	}

	Float32x2 c;
	c.hi = r_hi + r_lo;
	c.lo = r_hi - c.hi + r_lo;
	return c;
}

template <> inline
Float32x2 LDF::sub<Float32x2, fp32, Float32x2>
(const fp32& x, const Float32x2& y) {
	fp32 r_hi = x - y.hi;
	fp32 r_lo = static_cast<fp32>(0.0);
	if (fabs(x) > fabs(y.hi)) {
		r_lo = x - r_hi - y.hi - y.lo;
	} else {
		r_lo = -y.hi - r_hi + x - y.lo;
	}

	Float32x2 c;
	c.hi = r_hi + r_lo;
	c.lo = r_hi - c.hi + r_lo;
	return c;
}

/**
 * @brief Subtracts two fp32 values with the result stored as a Float32x2
 */
template <> inline
Float32x2 LDF::sub<Float32x2, fp32, fp32>
(const fp32& x, const fp32& y) {
	fp32 r_hi = x - y;
	fp32 r_lo = static_cast<fp32>(0.0);
	if (fabs(x) > fabs(y)) {
		r_lo = x - r_hi - y;
	} else {
		r_lo = -y - r_hi + x;
	}

	Float32x2 c;
	c.hi = r_hi + r_lo;
	c.lo = r_hi - c.hi + r_lo;
	return c;
}

template <> inline
Float32x2 LDF::mul<Float32x2, Float32x2, fp32>
(const Float32x2& x, const fp32& y) {
	Float32x2 t = LDF::mul<Float32x2, fp32, fp32>(x.hi, y);
	fp32 c = (x.lo * y) + t.lo;

	Float32x2 r;
	r.hi = t.hi + c;
	r.lo = (t.hi - r.hi) + c;
	return r;
}

template <> inline
Float32x2 LDF::mul<Float32x2, fp32, Float32x2>
(const fp32& x, const Float32x2& y) {
	Float32x2 t = LDF::mul<Float32x2, fp32, fp32>(x, y.hi);
	fp32 c = (x * y.lo) + t.lo;

	Float32x2 r;
	r.hi = t.hi + c;
	r.lo = (t.hi - r.hi) + c;
	return r;
}

template <> inline
Float32x2 LDF::div<Float32x2, Float32x2, fp32>
(const Float32x2& x, const fp32& y) {
	fp32 u = x.hi / y;
	Float32x2 t = LDF::mul<Float32x2, fp32, fp32>(u, y);
	fp32 l = (((x.hi - t.hi) - t.lo) + x.lo) / y;

	Float32x2 r;
	r.hi = u + l;
	r.lo = (u - r.hi) + l;
	return r;
}

template <> inline
Float32x2 LDF::div<Float32x2, fp32, Float32x2>
(const fp32& x, const Float32x2& y) {
	fp32 u = x / y.hi;
	Float32x2 t = LDF::mul<Float32x2, fp32, fp32>(u, y.hi);
	fp32 l = (((x - t.hi) - t.lo) - (u * y.lo)) / y.hi;

	Float32x2 r;
	r.hi = u + l;
	r.lo = (u - r.hi) + l;
	return r;
}

/**
 * @brief Divides two fp32 values with the result stored as a Float32x2
 */
template <> inline
Float32x2 LDF::div<Float32x2, fp32, fp32>
(const fp32& x, const fp32& y) {
	fp32 u = x / y;
	Float32x2 t = LDF::mul<Float32x2, fp32, fp32>(u, y);
	fp32 l = ((x - t.hi) - t.lo) / y;

	Float32x2 r;
	r.hi = u + l;
	r.lo = (u - r.hi) + l;
	return r;
}

/**
 * @brief Calculates the reciprocal of a fp32 value with the result stored
 * as a Float32x2
 */

template <> inline
Float32x2 LDF::recip<Float32x2, fp32>
(const fp32& y) {
	fp32 u = static_cast<fp32>(1.0) / y;
	Float32x2 t = LDF::mul<Float32x2, fp32, fp32>(u, y);
	fp32 l = ((static_cast<fp32>(1.0) - t.hi) - t.lo) / y;

	Float32x2 r;
	r.hi = u + l;
	r.lo = (u - r.hi) + l;
	return r;
}

//------------------------------------------------------------------------------
// Float32x2 specialized arithmetic
//------------------------------------------------------------------------------

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero
 */
template <> inline
Float32x2 LDF::mul_pwr2<Float32x2, Float32x2, fp32>
(const Float32x2& x, const fp32& y) {
	Float32x2 ret;
	ret.hi = x.hi * y;
	ret.lo = x.lo * y;
	return ret;
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero
 */
template <> inline
Float32x2 LDF::mul_pwr2<Float32x2, fp32, Float32x2>
(const fp32& x, const Float32x2& y) {
	Float32x2 ret;
	ret.hi = x * y.hi;
	ret.lo = x * y.lo;
	return ret;
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero.
 * The result is stored as a Float32x2
 */
template <> inline
Float32x2 LDF::mul_pwr2<Float32x2, fp32, fp32>
(const fp32& x, const fp32& y) {
	Float32x2 ret;
	ret.hi = x * y;
	ret.lo = static_cast<fp32>(0.0);
	return ret;
}

//------------------------------------------------------------------------------
// Float32x2 bitwise operators
//------------------------------------------------------------------------------

template <> inline
Float32x2 LDF::bitwise_not<Float32x2>
(const Float32x2& x) {
	Float32x2 ret = x;
	uint32_t* binary_part = reinterpret_cast<uint32_t*>(&ret);
	binary_part[0] = ~binary_part[0];
	binary_part[1] = ~binary_part[1];
	return ret;
}

template <> inline
Float32x2 LDF::bitwise_and<Float32x2, Float32x2>
(const Float32x2& x, const Float32x2& y) {
	Float32x2 ret = x;
	uint32_t* ret_bin = reinterpret_cast<uint32_t*>(&ret);
	const uint32_t* y_bin = reinterpret_cast<const uint32_t*>(&y);
	ret_bin[0] &= y_bin[0];
	ret_bin[1] &= y_bin[1];
	return ret;
}

template <> inline
Float32x2 LDF::bitwise_andnot<Float32x2, Float32x2>
(const Float32x2& x, const Float32x2& y) {
	Float32x2 ret = x;
	uint32_t* ret_bin = reinterpret_cast<uint32_t*>(&ret);
	const uint32_t* y_bin = reinterpret_cast<const uint32_t*>(&y);
	ret_bin[0] &= ~y_bin[0];
	ret_bin[1] &= ~y_bin[1];
	return ret;
}

template <> inline
Float32x2 LDF::bitwise_or<Float32x2, Float32x2>
(const Float32x2& x, const Float32x2& y) {
	Float32x2 ret = x;
	uint32_t* ret_bin = reinterpret_cast<uint32_t*>(&ret);
	const uint32_t* y_bin = reinterpret_cast<const uint32_t*>(&y);
	ret_bin[0] |= y_bin[0];
	ret_bin[1] |= y_bin[1];
	return ret;
}

template <> inline
Float32x2 LDF::bitwise_xor<Float32x2, Float32x2>
(const Float32x2& x, const Float32x2& y) {
	Float32x2 ret = x;
	uint32_t* ret_bin = reinterpret_cast<uint32_t*>(&ret);
	const uint32_t* y_bin = reinterpret_cast<const uint32_t*>(&y);
	ret_bin[0] ^= y_bin[0];
	ret_bin[1] ^= y_bin[1];
	return ret;
}

template <> inline
Float32x2 LDF::bitwise_and<Float32x2, fp32>
(const Float32x2& x, const fp32& y) {
	Float32x2 ret = x;
	uint32_t* ret_bin = reinterpret_cast<uint32_t*>(&ret);
	const uint32_t* y_bin = reinterpret_cast<const uint32_t*>(&y);
	ret_bin[0] &= *y_bin;
	ret_bin[1] &= *y_bin;
	return x;
}

template <> inline
Float32x2 LDF::bitwise_andnot<Float32x2, fp32>
(const Float32x2& x, const fp32& y) {
	Float32x2 ret = x;
	uint32_t* ret_bin = reinterpret_cast<uint32_t*>(&ret);
	const uint32_t* y_bin = reinterpret_cast<const uint32_t*>(&y);
	ret_bin[0] &= ~(*y_bin);
	ret_bin[1] &= ~(*y_bin);
	return x;
}

template <> inline
Float32x2 LDF::bitwise_or<Float32x2, fp32>
(const Float32x2& x, const fp32& y) {
	Float32x2 ret = x;
	uint32_t* ret_bin = reinterpret_cast<uint32_t*>(&ret);
	const uint32_t* y_bin = reinterpret_cast<const uint32_t*>(&y);
	ret_bin[0] |= *y_bin;
	ret_bin[1] |= *y_bin;
	return x;
}

template <> inline
Float32x2 LDF::bitwise_xor<Float32x2, fp32>
(const Float32x2& x, const fp32& y) {
	Float32x2 ret = x;
	uint32_t* ret_bin = reinterpret_cast<uint32_t*>(&ret);
	const uint32_t* y_bin = reinterpret_cast<const uint32_t*>(&y);
	ret_bin[0] ^= *y_bin;
	ret_bin[1] ^= *y_bin;
	return x;
}

//------------------------------------------------------------------------------
// Float32x2 Arithmetic Operator Overloads
//------------------------------------------------------------------------------

inline constexpr Float32x2 operator-(const Float32x2& x) {
	return {-x.hi, -x.lo};
}

inline Float32x2 operator+(const Float32x2& x, const Float32x2& y) {
	return LDF::add<Float32x2, Float32x2, Float32x2>(x, y);
}
inline Float32x2 operator-(const Float32x2& x, const Float32x2& y) {
	return LDF::sub<Float32x2, Float32x2, Float32x2>(x, y);
}
inline Float32x2 operator*(const Float32x2& x, const Float32x2& y) {
	return LDF::mul<Float32x2, Float32x2, Float32x2>(x, y);
}
inline Float32x2 operator/(const Float32x2& x, const Float32x2& y) {
	return LDF::div<Float32x2, Float32x2, Float32x2>(x, y);
}

inline Float32x2 operator+(const Float32x2& x, const fp32 y) {
	return LDF::add<Float32x2, Float32x2, fp32>(x, y);
}
inline Float32x2 operator-(const Float32x2& x, const fp32 y) {
	return LDF::sub<Float32x2, Float32x2, fp32>(x, y);
}
inline Float32x2 operator*(const Float32x2& x, const fp32 y) {
	return LDF::mul<Float32x2, Float32x2, fp32>(x, y);
}
inline Float32x2 operator/(const Float32x2& x, const fp32 y) {
	return LDF::div<Float32x2, Float32x2, fp32>(x, y);
}

inline Float32x2 operator+(const fp32 x, const Float32x2& y) {
	return LDF::add<Float32x2, fp32, Float32x2>(x, y);
}
inline Float32x2 operator-(const fp32 x, const Float32x2& y) {
	return LDF::sub<Float32x2, fp32, Float32x2>(x, y);
}
inline Float32x2 operator*(const fp32 x, const Float32x2& y) {
	return LDF::mul<Float32x2, fp32, Float32x2>(x, y);
}
inline Float32x2 operator/(const fp32 x, const Float32x2& y) {
	return LDF::div<Float32x2, fp32, Float32x2>(x, y);
}

inline Float32x2 square(const Float32x2& x) {
	return LDF::square<Float32x2, Float32x2>(x);
}
inline Float32x2 recip(const Float32x2& x) {
	return LDF::recip<Float32x2, Float32x2>(x);
}

inline Float32x2 mul_pwr2(const Float32x2& x, const fp32 y) {
	return LDF::mul_pwr2<Float32x2, Float32x2, fp32>(x, y);
}
inline Float32x2 mul_pwr2(const fp32 x, const Float32x2& y) {
	return LDF::mul_pwr2<Float32x2, fp32, Float32x2>(x, y);
}

// #if __cplusplus >= 201304L
// 	#define FLOAT32X2_RELAXED_CONSTEXPR constexpr
// #else
// 	#define FLOAT32X2_RELAXED_CONSTEXPR
// #endif

/* Compound Assignment */

inline Float32x2& operator+=(Float32x2& x, const Float32x2 y) {
	x = x + y;
	return x;
}
inline Float32x2& operator-=(Float32x2& x, const Float32x2 y) {
	x = x - y;
	return x;
}
inline Float32x2& operator*=(Float32x2& x, const Float32x2 y) {
	x = x * y;
	return x;
}
inline Float32x2& operator/=(Float32x2& x, const Float32x2 y) {
	x = x / y;
	return x;
}

inline Float32x2& operator+=(Float32x2& x, const fp32 y) {
	x = x + y;
	return x;
}
inline Float32x2& operator-=(Float32x2& x, const fp32 y) {
	x = x - y;
	return x;
}
inline Float32x2& operator*=(Float32x2& x, const fp32 y) {
	x = x * y;
	return x;
}
inline Float32x2& operator/=(Float32x2& x, const fp32 y) {
	x = x / y;
	return x;
}

/* Increment/Decrement */

inline Float32x2& operator++(Float32x2& x) {
	x += static_cast<fp32>(1.0);
	return x;
}

inline Float32x2& operator--(Float32x2& x) {
	x -= static_cast<fp32>(1.0);
	return x;
}

inline Float32x2 operator++(Float32x2& x, int) {
	Float32x2 temp = x;
	x += static_cast<fp32>(1.0);
	return temp;
}

inline Float32x2 operator--(Float32x2& x, int) {
	Float32x2 temp = x;
	x -= static_cast<fp32>(1.0);
	return temp;
}

//------------------------------------------------------------------------------
// Float32x2 Constants
//------------------------------------------------------------------------------

/* C++20 <numbers> */

	constexpr Float32x2 Float32x2_e          = {0x1.5bf0a8p+1f,+0x1.628aeep-24f}; /**< ~2.718281828 */
	constexpr Float32x2 Float32x2_log2e      = {0x1.715476p+0f,+0x1.4ae0c0p-26f}; /**< ~1.442695041 */
	constexpr Float32x2 Float32x2_log10e     = {0x1.bcb7b2p-2f,-0x1.5b235ep-27f}; /**< ~0.434294482 */
	constexpr Float32x2 Float32x2_pi         = {0x1.921fb6p+1f,-0x1.777a5cp-24f}; /**< ~3.141592654 */
	constexpr Float32x2 Float32x2_inv_pi     = {0x1.45f306p-2f,+0x1.b93910p-27f}; /**< ~0.318309886 */
	constexpr Float32x2 Float32x2_inv_sqrtpi = {0x1.20dd76p-1f,-0x1.f7ac92p-26f}; /**< ~0.564189584 */
	constexpr Float32x2 Float32x2_ln2        = {0x1.62e430p-1f,-0x1.05c610p-29f}; /**< ~0.693147181 */
	constexpr Float32x2 Float32x2_ln10       = {0x1.26bb1cp+1f,-0x1.12aabap-25f}; /**< ~2.302585093 */
	constexpr Float32x2 Float32x2_sqrt2      = {0x1.6a09e6p+0f,+0x1.9fcef4p-26f}; /**< ~1.414213562 */
	constexpr Float32x2 Float32x2_sqrt3      = {0x1.bb67aep+0f,+0x1.0b0996p-25f}; /**< ~1.732050808 */
	constexpr Float32x2 Float32x2_inv_sqrt3  = {0x1.279a74p-1f,+0x1.640cc8p-27f}; /**< ~0.577350269 */
	constexpr Float32x2 Float32x2_egamma     = {0x1.2788d0p-1f,-0x1.c824f4p-28f}; /**< ~0.577215665 */
	constexpr Float32x2 Float32x2_phi        = {0x1.9e377ap+0f,-0x1.1a02d6p-26f}; /**< ~1.618033989 */

#if __cplusplus >= 201907L
#include <numbers>
namespace std {
	namespace numbers {
		template<> inline constexpr Float32x2 e_v          <Float32x2> = Float32x2_e         ; /**< ~2.718281828 */
		template<> inline constexpr Float32x2 log2e_v      <Float32x2> = Float32x2_log2e     ; /**< ~1.442695041 */
		template<> inline constexpr Float32x2 log10e_v     <Float32x2> = Float32x2_log10e    ; /**< ~0.434294482 */
		template<> inline constexpr Float32x2 pi_v         <Float32x2> = Float32x2_pi        ; /**< ~3.141592654 */
		template<> inline constexpr Float32x2 inv_pi_v     <Float32x2> = Float32x2_inv_pi    ; /**< ~0.318309886 */
		template<> inline constexpr Float32x2 inv_sqrtpi_v <Float32x2> = Float32x2_inv_sqrtpi; /**< ~0.564189584 */
		template<> inline constexpr Float32x2 ln2_v        <Float32x2> = Float32x2_ln2       ; /**< ~0.693147181 */
		template<> inline constexpr Float32x2 ln10_v       <Float32x2> = Float32x2_ln10      ; /**< ~2.302585093 */
		template<> inline constexpr Float32x2 sqrt2_v      <Float32x2> = Float32x2_sqrt2     ; /**< ~1.414213562 */
		template<> inline constexpr Float32x2 sqrt3_v      <Float32x2> = Float32x2_sqrt3     ; /**< ~1.732050808 */
		template<> inline constexpr Float32x2 inv_sqrt3_v  <Float32x2> = Float32x2_inv_sqrt3 ; /**< ~0.577350269 */
		template<> inline constexpr Float32x2 egamma_v     <Float32x2> = Float32x2_egamma    ; /**< ~0.577215665 */
		template<> inline constexpr Float32x2 phi_v        <Float32x2> = Float32x2_phi       ; /**< ~1.618033989 */
	}
}
#endif

//------------------------------------------------------------------------------
// Float32x2 Math Functions
//------------------------------------------------------------------------------

/* Floating Point Classify */

	/** @brief Returns true if x is negative */
	inline constexpr bool signbit(const Float32x2& x) {
		return std::signbit(x.hi);
	}

	/** @brief Returns true if x is finite */
	inline constexpr bool isfinite(const Float32x2& x) {
		return std::isfinite(x.hi);
	}

	/** @brief Returns true if x is +-infinity */
	inline constexpr bool isinf(const Float32x2& x) {
		return std::isinf(x.hi);
	}

	/** @brief Returns true if x is any kind of NaN */
	inline constexpr bool isnan(const Float32x2& x) {
		return std::isnan(x.hi);
	}

	/** @brief Returns true if x is normal */
	inline constexpr bool isnormal(const Float32x2& x) {
		return (std::isnormal(x.hi) && std::isnormal(x.lo));
	}
	
	/** @brief Returns true if x and y are unordered */
	inline constexpr bool isunordered(const Float32x2& x, const Float32x2& y) {
		return std::isunordered(x.hi, y.hi);
	}

	inline constexpr int fpclassify(const Float32x2& x) {
		return
			isinf(x)             ? FP_INFINITE :
			isnan(x)             ? FP_NAN      :
			isequal_zero(x) ? FP_ZERO     :
			isnormal(x)          ? FP_NORMAL   :
			FP_SUBNORMAL;
	}

/* Comparison */

	inline constexpr bool isgreater(const Float32x2 x, const Float32x2 y) {
		return (x > y);
	}
	inline constexpr bool isgreaterequal(const Float32x2 x, const Float32x2 y) {
		return (x >= y);
	}
	inline constexpr bool isless(const Float32x2 x, const Float32x2 y) {
		return (x < y);
	}
	inline constexpr bool islessequal(const Float32x2 x, const Float32x2 y) {
		return (x <= y);
	}
	inline constexpr bool islessgreater(const Float32x2 x, const Float32x2 y) {
		return (x < y) || (x > y);
	}

/* fmax and fmin */

	/**
	 * @brief Returns the fmax of x and y. Correctly handling NaN and signed zeros.
	 * You may use std::max as a faster alternative.
	 */
	inline constexpr Float32x2 fmax(const Float32x2 x, const Float32x2 y) {
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
	inline constexpr Float32x2 fmin(const Float32x2 x, const Float32x2 y) {
		return
			(x > y) ? y :
			(y > x) ? x :
			isnan(x) ? y :
			isnan(y) ? x :
			signbit(x) ? x : y;
	}

/* Arithmetic */

	inline constexpr Float32x2 fmax(const Float32x2 x, const Float32x2 y, const Float32x2 z) {
		return fmax(fmax(x, y), z);
	}
	inline constexpr Float32x2 fmin(const Float32x2 x, const Float32x2 y, const Float32x2 z) {
		return fmin(fmin(x, y), z);
	}
	inline constexpr Float32x2 fabs(const Float32x2 x) {
		return (signbit(x)) ? -x : x;
	}
	inline constexpr Float32x2 fdim(const Float32x2 x, const Float32x2 y) {
		return (x > y) ? (x - y) : static_cast<Float32x2>(0.0);
	}
	/** @note Naive implementation of fma (Fused multiply add). May lose precision */
	inline Float32x2 fma(const Float32x2 x, const Float32x2 y, const Float32x2 z) {
		return (x * y) + z;
	}
	inline constexpr Float32x2 copysign(const Float32x2 x, const Float32x2 y) {
		return (
			(signbit(x)) != (signbit(y))
		) ? -x : x;
	}
	inline Float32x2 sqrt(const Float32x2 x) {
		if (isequal_zero(x)) {
			return x;
		}
		fp32 guess = sqrt(x.hi);
		return mul_pwr2((guess + x / guess), static_cast<fp32>(0.5));
	}
	inline Float32x2 cbrt(const Float32x2 x) {
		if (isequal_zero(x)) {
			return x;
		}
		fp32 guess = cbrt(x.hi);
		return (
			(static_cast<fp32>(2.0) * guess) + (x / LDF::square<Float32x2, fp32>(guess))
		) / static_cast<fp32>(3.0);
	}
	/** @note Naive implementation of hypot, may overflow for large inputs */
	inline Float32x2 hypot(const Float32x2 x, const Float32x2 y) {
		return sqrt(
			square(x) + square(y)
		);
	}
	/** @note Naive implementation of hypot, may overflow for large inputs */
	inline Float32x2 hypot(const Float32x2 x, const Float32x2 y, const Float32x2 z) {
		return sqrt(
			square(x) + square(y) + square(z)
		);
	}

/* Trigonometry */

	/** 
	 * @note casts to Float32x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float32x2 sin(const Float32x2 x) { return static_cast<Float32x2>(sin(static_cast<Float32x2_Math>(x))); }
	/** 
	 * @note casts to Float32x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float32x2 cos(const Float32x2 x) { return static_cast<Float32x2>(cos(static_cast<Float32x2_Math>(x))); }
	/** 
	 * @note casts to Float32x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline void sincos(const Float32x2 x, Float32x2& p_sin, Float32x2& p_cos) {
		p_sin = sin(x);
		p_cos = cos(x);
	}
	/** 
	 * @note casts to Float32x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float32x2 tan(const Float32x2 x) {
		Float32x2 sin_val, cos_val;
		sincos(x, sin_val, cos_val);
		return sin_val / cos_val;
	}
	/** 
	 * @note casts to Float32x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float32x2 asin(const Float32x2 x) { return static_cast<Float32x2>(asin(static_cast<Float32x2_Math>(x))); }
	/** 
	 * @note casts to Float32x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float32x2 acos(const Float32x2 x) { return static_cast<Float32x2>(acos(static_cast<Float32x2_Math>(x))); }
	/** 
	 * @note casts to Float32x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float32x2 atan(const Float32x2 x) { return static_cast<Float32x2>(atan(static_cast<Float32x2_Math>(x))); }
	/** 
	 * @note casts to Float32x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float32x2 sinh(const Float32x2 x) { return static_cast<Float32x2>(sinh(static_cast<Float32x2_Math>(x))); }
	/** 
	 * @note casts to Float32x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float32x2 cosh(const Float32x2 x) { return static_cast<Float32x2>(cosh(static_cast<Float32x2_Math>(x))); }
	/** 
	 * @note casts to Float32x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float32x2 tanh(const Float32x2 x) { return static_cast<Float32x2>(tanh(static_cast<Float32x2_Math>(x))); }
	/** 
	 * @note casts to Float32x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline void sinhcosh(const Float32x2 x, Float32x2& p_sinh, Float32x2& p_cosh) {
		p_sinh = sinh(x);
		p_cosh = cosh(x);
	}
	/** 
	 * @note casts to Float32x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float32x2 asinh(const Float32x2 x) { return static_cast<Float32x2>(asinh(static_cast<Float32x2_Math>(x))); }
	/** 
	 * @note casts to Float32x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float32x2 acosh(const Float32x2 x) { return static_cast<Float32x2>(acosh(static_cast<Float32x2_Math>(x))); }
	/** 
	 * @note casts to Float32x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float32x2 atanh(const Float32x2 x) { return static_cast<Float32x2>(atanh(static_cast<Float32x2_Math>(x))); }
	/** 
	 * @note casts to Float32x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float32x2 atan2(const Float32x2 y, const Float32x2 x) {
		return static_cast<Float32x2>(atan2(static_cast<Float32x2_Math>(y), static_cast<Float32x2_Math>(x)));
	}

/* Logarithms and Exponents */

	/** 
	 * @note casts to Float32x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float32x2 log(const Float32x2 x) { return static_cast<Float32x2>(log(static_cast<Float32x2_Math>(x))); }
	/** 
	 * @note casts to Float32x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float32x2 log1p(const Float32x2 x) {
		return log(x + static_cast<fp32>(1.0));
	}
	/** 
	 * @note casts to Float32x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float32x2 log2(const Float32x2 x) {
		return log(x) * Float32x2_log2e;
	}
	/** 
	 * @note casts to Float32x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float32x2 log10(const Float32x2 x) {
		return log(x) * Float32x2_log10e;
	}
	
	inline Float32x2 logb(const Float32x2 x) { return logb(x.hi + x.lo); }
	
	/** 
	 * @note casts to Float32x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float32x2 exp(const Float32x2 x) { return static_cast<Float32x2>(exp(static_cast<Float32x2_Math>(x))); }
	/** 
	 * @note casts to Float32x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float32x2 expm1(const Float32x2 x) {
		return exp(x) - static_cast<fp32>(1.0);
	}
	/** 
	 * @note casts to Float32x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float32x2 exp2(const Float32x2 x) {
		return exp(x * Float32x2_ln2);
	}
	/** 
	 * @note casts to Float32x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float32x2 exp10(const Float32x2 x) {
		return exp(x * Float32x2_ln10);
	}
	/** 
	 * @note casts to Float32x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float32x2 pow(const Float32x2 x, const Float32x2 y) {
		return isequal_zero(x) ? (
			isequal_zero(y) ? static_cast<Float32x2>(1.0) : static_cast<Float32x2>(0.0)
		) : exp(y * log(x));
	}
	/** 
	 * @note casts to Float32x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float32x2 pow(const Float32x2 x, const fp32 y) {
		return isequal_zero(x) ? (
			(y == static_cast<fp32>(0.0)) ? static_cast<Float32x2>(1.0) : static_cast<Float32x2>(0.0)
		) : exp(y * log(x));
	}

/* Rounding */

	inline Float32x2 trunc(const Float32x2 x) {
		Float32x2 int_hi = trunc(x.hi);
		Float32x2 int_lo = trunc(x.lo);
		fp32 frac_hi = x.hi - int_hi.hi;
		fp32 frac_lo = x.lo - int_lo.hi;
		// Sum in increasing order
		Float32x2 trunc_all = (
			LDF::add<Float32x2, fp32, fp32>(frac_hi, frac_lo) >= static_cast<fp32>(1.0)
		) ? static_cast<Float32x2>(1.0) : static_cast<Float32x2>(0.0);
		trunc_all += int_lo;
		trunc_all += int_hi;
		return trunc_all;
	}
	inline Float32x2 floor(const Float32x2 x) {
		Float32x2 int_part = trunc(x);
		return (
			isless_zero(x) && int_part != x
		) ? int_part - static_cast<fp32>(1.0) : int_part;
	}
	inline Float32x2 ceil(const Float32x2 x) {
		Float32x2 int_part = trunc(x);
		return (
			isgreater_zero(x) && int_part != x
		) ? int_part + static_cast<fp32>(1.0) : int_part;
	}
	inline Float32x2 round(const Float32x2 x) {
		Float32x2 int_part = trunc(x);
		Float32x2 frac_part = x - int_part;
		if (isgreaterequal_zero(x)) {
			if (frac_part >= static_cast<fp32>(0.5)) {
				return int_part + static_cast<fp32>(1.0);
			}
			return int_part;
		}
		if (frac_part <= static_cast<fp32>(-0.5)) {
			return int_part - static_cast<fp32>(1.0);
		}
		return int_part;
	}
	inline Float32x2 rint(const Float32x2 x) {
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
	inline long lround(const Float32x2 x) {
		return static_cast<long>(round(x));
	}
	inline long lrint(const Float32x2 x) {
		return static_cast<long>(rint(x));
	}
	inline long long llround(const Float32x2 x) {
		return static_cast<long long>(round(x));
	}
	inline long long llrint(const Float32x2 x) {
		return static_cast<long long>(rint(x));
	}

	/* Integer and Remainder */

	inline Float32x2 fmod(const Float32x2 x, const Float32x2 y) {
		Float32x2 trunc_part = trunc(x / y);
		return x - y * trunc_part;
	}
	inline Float32x2 modf(const Float32x2 x, Float32x2& int_part) {
		Float32x2 trunc_part = trunc(x);
		int_part = trunc_part;
		return x - trunc_part;
	}
	inline Float32x2 nearbyint(const Float32x2 x) {
		return rint(x);
	}
	inline Float32x2 remainder(const Float32x2 x, const Float32x2 y) {
		Float32x2 round_part = round(x / y);
		return x - y * round_part;
	}
	inline Float32x2 remquo(const Float32x2 x, const Float32x2 y, int& quo) {
		Float32x2 q = round(x / y);
		Float32x2 r = x - y * q;
		quo = static_cast<int>(q.hi + q.lo);
		return r;
	}

/* Float Exponents */

	/**
	 * @brief Extracts the exponent of a Float32x2 value to compute the
	 * binary logarithm.
	 */
	inline int ilogb(const Float32x2 x) {
		return ilogb(x.hi + x.lo);
	}
	/**
	 * @brief Returns a normalized Float32x2 value and the exponent in
	 * the form [0.0, 1.0) * 2^expon
	 */
	inline Float32x2 frexp(const Float32x2 x, int& expon) {
		Float32x2 ret;
		expon = ilogb(x.hi + x.lo) + 1;
		ret.hi = ldexp(x.hi, -(expon));
		ret.lo = ldexp(x.lo, -(expon));
		return ret;
	}
	/**
	 * @brief Multiplies a Float32x2 value by 2^expon
	 */
	inline Float32x2 ldexp(const Float32x2 x, int expon) {
		Float32x2 ret;
		ret.hi = ldexp(x.hi, expon);
		ret.lo = isfinite(x.hi) ? ldexp(x.lo, expon) : x.hi;
		return ret;
	}
	/**
	 * @brief Multiplies a Float32x2 value by FLT_RADIX^expon
	 */
	inline Float32x2 scalbn(const Float32x2 x, int expon) {
		Float32x2 ret;
		ret.hi = scalbn(x.hi, expon);
		ret.lo = isfinite(x.hi) ? scalbn(x.lo, expon) : x.hi;
		return ret;
	}
	/**
	 * @brief Multiplies a Float32x2 value by FLT_RADIX^expon
	 */
	inline Float32x2 scalbln(const Float32x2 x, long expon) {
		Float32x2 ret;
		ret.hi = scalbln(x.hi, expon);
		ret.lo = isfinite(x.hi) ? scalbln(x.lo, expon) : x.hi;
		return ret;
	}

/* Transcendental Functions */
	
	/** 
	 * @note casts to Float32x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float32x2 erf(const Float32x2 x) {
		return static_cast<Float32x2>(
			erf(static_cast<Float32x2_Math>(x))
		);
	}
	/** 
	 * @note casts to Float32x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float32x2 erfc(const Float32x2 x) {
		return static_cast<Float32x2>(
			erfc(static_cast<Float32x2_Math>(x))
		);
	}
	/** 
	 * @note casts to Float32x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float32x2 lgamma(const Float32x2 x) {
		return static_cast<Float32x2>(
			lgamma(static_cast<Float32x2_Math>(x))
		);
	}
	/** 
	 * @note casts to Float32x2_Math for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float32x2 tgamma(const Float32x2 x) {
		return static_cast<Float32x2>(
			tgamma(static_cast<Float32x2_Math>(x))
		);
	}

#endif /* FLOAT32X2_HPP */
