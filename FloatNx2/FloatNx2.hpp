/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

// This will be worked on later
#if 0

/**
 * @note There are no include guards because this file is intended to be
 * included multiple times.
 */

/**
 * @brief FloatNx2.hpp is used for generating a basic FloatNx2 type using
 * macros. To use it, follow these steps:
 * 
 * 1. provide the struct/class definition
 * 2. provide the dekker_split function
 * 3. define GENERATE_FLOATNX2_BASE_TYPE to float, double, etc
 * 4. define GENERATE_FLOATNX2_TYPE_NAME to Float32x2, Float64x2, etc
 * 5. include this file
 */

// test code
#if 1

#include "../Float64x2/Float64x2_def.h"

#define GENERATE_FLOATNX2_BASE_TYPE fp64
#define GENERATE_FLOATNX2_TYPE_NAME Float64x2

#endif

#include <limits>
#include <cmath>
#include <cfenv>

//------------------------------------------------------------------------------
// FloatNx2 Macro Checks
//------------------------------------------------------------------------------

#ifndef GENERATE_FLOATNX2_BASE_TYPE
	#error "GENERATE_FLOATNX2_BASE_TYPE must be set to a type (float, double, etc)"
#endif
#ifndef GENERATE_FLOATNX2_TYPE_NAME
	#error "GENERATE_FLOATNX2_TYPE_NAME must be set (Float32x2, Float64x2, etc)"
#endif
#ifdef FloatBase
	#error "FloatBase must be undefined":
#endif
#ifdef FloatNx2
	#error "FloatNx2 must be undefined":
#endif

#define FloatBase GENERATE_FLOATNX2_BASE_TYPE
#define FloatNx2 GENERATE_FLOATNX2_TYPE_NAME

//------------------------------------------------------------------------------
// FloatNx2 Static Asserts
//------------------------------------------------------------------------------

static_assert(std::numeric_limits<FloatBase>::is_integer == false, "FloatBase cannot be an integer type");

//------------------------------------------------------------------------------
// FloatNx2 Comparison
//------------------------------------------------------------------------------

/* Comparison */

inline constexpr bool operator==(const FloatNx2& x, const FloatNx2& y) {
	return (x.hi == y.hi && x.lo == y.lo);
}
inline constexpr bool operator!=(const FloatNx2& x, const FloatNx2& y) {
	return (x.hi != y.hi || x.lo != y.lo);
}
inline constexpr bool operator<(const FloatNx2& x, const FloatNx2& y) {
	return (x.hi == y.hi) ? (x.lo < y.lo) : (x.hi < y.hi);
}
inline constexpr bool operator<=(const FloatNx2& x, const FloatNx2& y) {
	return (x.hi == y.hi) ? (x.lo <= y.lo) : (x.hi < y.hi);
}
inline constexpr bool operator>(const FloatNx2& x, const FloatNx2& y) {
	return (x.hi == y.hi) ? (x.lo > y.lo) : (x.hi > y.hi);
}
inline constexpr bool operator>=(const FloatNx2& x, const FloatNx2& y) {
	return (x.hi == y.hi) ? (x.lo >= y.lo) : (x.hi > y.hi);
}

/* Optimized Comparison */

inline constexpr bool operator==(const FloatNx2& x, const FloatBase y) {
	return (x.hi == y && x.lo == static_cast<FloatBase>(0.0));
}
inline constexpr bool operator!=(const FloatNx2& x, const FloatBase y) {
	return (x.hi != y || x.lo != static_cast<FloatBase>(0.0));
}
inline constexpr bool operator<(const FloatNx2& x, const FloatBase y) {
	return (x.hi == y) ? (x.lo < static_cast<FloatBase>(0.0)) : (x.hi < y);
}
inline constexpr bool operator<=(const FloatNx2& x, const FloatBase y) {
	return (x.hi == y) ? (x.lo <= static_cast<FloatBase>(0.0)) : (x.hi < y);
}
inline constexpr bool operator>(const FloatNx2& x, const FloatBase y) {
	return (x.hi == y) ? (x.lo > static_cast<FloatBase>(0.0)) : (x.hi > y);
}
inline constexpr bool operator>=(const FloatNx2& x, const FloatBase y) {
	return (x.hi == y) ? (x.lo >= static_cast<FloatBase>(0.0)) : (x.hi > y);
}

inline constexpr bool operator==(const FloatBase x, const FloatNx2& y) {
	return (x == y.hi && static_cast<FloatBase>(0.0) == y.lo);
}
inline constexpr bool operator!=(const FloatBase x, const FloatNx2& y) {
	return (x != y.hi || static_cast<FloatBase>(0.0) != y.lo);
}
inline constexpr bool operator<(const FloatBase x, const FloatNx2& y) {
	return (x == y.hi) ? (static_cast<FloatBase>(0.0) < y.lo) : (x < y.hi);
}
inline constexpr bool operator<=(const FloatBase x, const FloatNx2& y) {
	return (x == y.hi) ? (static_cast<FloatBase>(0.0) <= y.lo) : (x < y.hi);
}
inline constexpr bool operator>(const FloatBase x, const FloatNx2& y) {
	return (x == y.hi) ? (static_cast<FloatBase>(0.0) > y.lo) : (x > y.hi);
}
inline constexpr bool operator>=(const FloatBase x, const FloatNx2& y) {
	return (x == y.hi) ? (static_cast<FloatBase>(0.0) >= y.lo) : (x > y.hi);
}

/* Compare to Zero */

/** @brief Assumes that if x.hi is zero then x.lo is also zero */
inline constexpr bool dekker_equal_zero(const FloatNx2& x) {
	return (x.hi == static_cast<FloatBase>(0.0));
}
/** @brief Assumes that if x.hi is zero then x.lo is also zero */
inline constexpr bool dekker_notequal_zero(const FloatNx2& x) {
	return (x.hi != static_cast<FloatBase>(0.0));
}
/** @brief Assumes that if x.hi is zero then x.lo is also zero */
inline constexpr bool dekker_less_zero(const FloatNx2& x) {
	return (x.hi < static_cast<FloatBase>(0.0));
}
/** @brief Assumes that if x.hi is zero then x.lo is also zero */
inline constexpr bool dekker_lessequal_zero(const FloatNx2& x) {
	return (x.hi <= static_cast<FloatBase>(0.0));
}
/** @brief Assumes that if x.hi is zero then x.lo is also zero */
inline constexpr bool dekker_greater_zero(const FloatNx2& x) {
	return (x.hi > static_cast<FloatBase>(0.0));
}
/** @brief Assumes that if x.hi is zero then x.lo is also zero */
inline constexpr bool dekker_greaterequal_zero(const FloatNx2& x) {
	return (x.hi >= static_cast<FloatBase>(0.0));
}

//------------------------------------------------------------------------------
// FloatNx2 Basic Arithmetic
//------------------------------------------------------------------------------

/* Negation */

inline constexpr FloatNx2 operator-(const FloatNx2& x) {
	return {-x.hi, -x.lo};
}

inline FloatNx2 operator+(const FloatNx2& x, const FloatNx2& y) {
	FloatBase r_hi = x.hi + y.hi;
	FloatBase r_lo = static_cast<FloatBase>(0.0);
	if (fabs(x.hi) > fabs(y.hi)) {
		r_lo = x.hi - r_hi + y.hi + y.lo + x.lo;
	} else {
		r_lo = y.hi - r_hi + x.hi + x.lo + y.lo;
	}

	FloatNx2 c;
	c.hi = r_hi + r_lo;
	c.lo = r_hi - c.hi + r_lo;
	return c;
}

inline FloatNx2 operator-(const FloatNx2& x, const FloatNx2& y) {
	FloatBase r_hi = x.hi - y.hi;
	FloatBase r_lo = static_cast<FloatBase>(0.0);
	if (fabs(x.hi) > fabs(y.hi)) {
		r_lo = x.hi - r_hi - y.hi - y.lo + x.lo;
	} else {
		r_lo = -y.hi - r_hi + x.hi + x.lo - y.lo;
	}

	FloatNx2 c;
	c.hi = r_hi + r_lo;
	c.lo = r_hi - c.hi + r_lo;
	return c;
}

/**
 * @brief Multiplies two FloatBase values with result stored as a FloatNx2
 */
inline FloatNx2 dekker_mul12(const FloatBase x, const FloatBase y) {
	FloatNx2 a = dekker_split(x);
	FloatNx2 b = dekker_split(y);
	FloatBase p = a.hi * b.hi;
	FloatBase q = a.hi * b.lo + a.lo * b.hi;

	FloatNx2 r;
	r.hi = p + q;
	r.lo = p - r.hi + q + a.lo * b.lo;
	return r;
}

inline FloatNx2 operator*(const FloatNx2& x, const FloatNx2& y) {
	FloatNx2 t = dekker_mul12(x.hi, y.hi);
	FloatBase c = x.hi * y.lo + x.lo * y.hi + t.lo;

	FloatNx2 r;
	r.hi = t.hi + c;
	r.lo = t.hi - r.hi + c;
	return r;
}

inline FloatNx2 operator/(const FloatNx2& x, const FloatNx2& y) {
	FloatBase u = x.hi / y.hi;
	FloatNx2 t = dekker_mul12(u, y.hi);
	FloatBase l = (x.hi - t.hi - t.lo + x.lo - u * y.lo) / y.hi;

	FloatNx2 r;
	r.hi = u + l;
	r.lo = u - r.hi + l;
	return r;
}

/**
 * @brief Squares a FloatBase value with the result stored as a FloatNx2
 */
inline FloatNx2 dekker_square12(const FloatBase x) {
	FloatNx2 a = dekker_split(x);
	FloatBase p = a.hi * a.hi;
	FloatBase q = static_cast<FloatBase>(2.0) * (a.hi * a.lo);

	FloatNx2 r;
	r.hi = p + q;
	r.lo = ((p - r.hi) + q) + (a.lo * a.lo);
	return r;
}

inline FloatNx2 square(const FloatNx2 x) {
	FloatNx2 t = dekker_square12(x.hi);
	FloatBase c = (static_cast<FloatBase>(2.0) * (x.hi * x.lo)) + t.lo;

	FloatNx2 r;
	r.hi = t.hi + c;
	r.lo = (t.hi - r.hi) + c;
	return r;
}

inline FloatNx2 recip(const FloatNx2 y) {
	FloatBase u = static_cast<FloatBase>(1.0) / y.hi;
	FloatNx2 t = dekker_mul12(u, y.hi);
	FloatBase l = (((static_cast<FloatBase>(1.0) - t.hi) - t.lo) - (u * y.lo)) / y.hi;

	FloatNx2 r;
	r.hi = u + l;
	r.lo = (u - r.hi) + l;
	return r;
}

//------------------------------------------------------------------------------
// FloatNx2 optimized arithmetic
//------------------------------------------------------------------------------

inline FloatNx2 operator+(const FloatNx2& x, const FloatBase y) {
	FloatBase r_hi = x.hi + y;
	FloatBase r_lo = static_cast<FloatBase>(0.0);
	if (fabs(x.hi) > fabs(y)) {
		r_lo = x.hi - r_hi + y + x.lo;
	} else {
		r_lo = y - r_hi + x.hi + x.lo;
	}

	FloatNx2 c;
	c.hi = r_hi + r_lo;
	c.lo = r_hi - c.hi + r_lo;
	return c;
}

inline FloatNx2 operator+(const FloatBase x, const FloatNx2& y) {
	FloatBase r_hi = x + y.hi;
	FloatBase r_lo = static_cast<FloatBase>(0.0);
	if (fabs(x) > fabs(y.hi)) {
		r_lo = x - r_hi + y.hi + y.lo;
	} else {
		r_lo = y.hi - r_hi + x + y.lo;
	}

	FloatNx2 c;
	c.hi = r_hi + r_lo;
	c.lo = r_hi - c.hi + r_lo;
	return c;
}

/**
 * @brief Adds two FloatBase values with the result stored as a FloatNx2
 */
inline FloatNx2 dekker_add12(const FloatBase x, const FloatBase y) {
	FloatBase r_hi = x + y;
	FloatBase r_lo = static_cast<FloatBase>(0.0);
	if (fabs(x) > fabs(y)) {
		r_lo = x - r_hi + y;
	} else {
		r_lo = y - r_hi + x;
	}

	FloatNx2 c;
	c.hi = r_hi + r_lo;
	c.lo = r_hi - c.hi + r_lo;
	return c;
}

inline FloatNx2 operator-(const FloatNx2& x, const FloatBase y) {
	FloatBase r_hi = x.hi - y;
	FloatBase r_lo = static_cast<FloatBase>(0.0);
	if (fabs(x.hi) > fabs(y)) {
		r_lo = x.hi - r_hi - y + x.lo;
	} else {
		r_lo = -y - r_hi + x.hi + x.lo;
	}

	FloatNx2 c;
	c.hi = r_hi + r_lo;
	c.lo = r_hi - c.hi + r_lo;
	return c;
}

inline FloatNx2 operator-(const FloatBase x, const FloatNx2& y) {
	FloatBase r_hi = x - y.hi;
	FloatBase r_lo = static_cast<FloatBase>(0.0);
	if (fabs(x) > fabs(y.hi)) {
		r_lo = x - r_hi - y.hi - y.lo;
	} else {
		r_lo = -y.hi - r_hi + x - y.lo;
	}

	FloatNx2 c;
	c.hi = r_hi + r_lo;
	c.lo = r_hi - c.hi + r_lo;
	return c;
}

/**
 * @brief Subtracts two FloatBase values with the result stored as a FloatNx2
 */
inline FloatNx2 dekker_sub12(const FloatBase x, const FloatBase y) {
	FloatBase r_hi = x - y;
	FloatBase r_lo = static_cast<FloatBase>(0.0);
	if (fabs(x) > fabs(y)) {
		r_lo = x - r_hi - y;
	} else {
		r_lo = -y - r_hi + x;
	}

	FloatNx2 c;
	c.hi = r_hi + r_lo;
	c.lo = r_hi - c.hi + r_lo;
	return c;
}

inline FloatNx2 operator*(const FloatNx2& x, const FloatBase y) {
	FloatNx2 t = dekker_mul12(x.hi, y);
	FloatBase c = (x.lo * y) + t.lo;

	FloatNx2 r;
	r.hi = t.hi + c;
	r.lo = (t.hi - r.hi) + c;
	return r;
}

inline FloatNx2 operator*(const FloatBase x, const FloatNx2& y) {
	FloatNx2 t = dekker_mul12(x, y.hi);
	FloatBase c = (x * y.lo) + t.lo;

	FloatNx2 r;
	r.hi = t.hi + c;
	r.lo = (t.hi - r.hi) + c;
	return r;
}

inline FloatNx2 operator/(const FloatNx2& x, const FloatBase y) {
	FloatBase u = x.hi / y;
	FloatNx2 t = dekker_mul12(u, y);
	FloatBase l = (((x.hi - t.hi) - t.lo) + x.lo) / y;

	FloatNx2 r;
	r.hi = u + l;
	r.lo = (u - r.hi) + l;
	return r;
}

inline FloatNx2 operator/(const FloatBase x, const FloatNx2& y) {
	FloatBase u = x / y.hi;
	FloatNx2 t = dekker_mul12(u, y.hi);
	FloatBase l = (((x - t.hi) - t.lo) - (u * y.lo)) / y.hi;

	FloatNx2 r;
	r.hi = u + l;
	r.lo = (u - r.hi) + l;
	return r;
}

/**
 * @brief Divides two FloatBase values with the result stored as a FloatNx2
 */
inline FloatNx2 dekker_div12(const FloatBase x, const FloatBase y) {
	FloatBase u = x / y;
	FloatNx2 t = dekker_mul12(u, y);
	FloatBase l = ((x - t.hi) - t.lo) / y;

	FloatNx2 r;
	r.hi = u + l;
	r.lo = (u - r.hi) + l;
	return r;
}

/**
 * @brief Calculates the reciprocal of a FloatBase value with the result stored
 * as a FloatNx2
 */

inline FloatNx2 dekker_recip12(const FloatBase y) {
	FloatBase u = static_cast<FloatBase>(1.0) / y;
	FloatNx2 t = dekker_mul12(u, y);
	FloatBase l = ((static_cast<FloatBase>(1.0) - t.hi) - t.lo) / y;

	FloatNx2 r;
	r.hi = u + l;
	r.lo = (u - r.hi) + l;
	return r;
}

//------------------------------------------------------------------------------
// FloatNx2 specialized arithmetic
//------------------------------------------------------------------------------

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero
 */
inline FloatNx2 mul_pwr2(const FloatNx2& x, const FloatBase y) {
	FloatNx2 ret;
	ret.hi = x.hi * y;
	ret.lo = x.lo * y;
	return ret;
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero
 */
inline FloatNx2 mul_pwr2(const FloatBase x, const FloatNx2& y) {
	FloatNx2 ret;
	ret.hi = x * y.hi;
	ret.lo = x * y.lo;
	return ret;
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero.
 * The result is stored as a FloatNx2
 */
inline FloatNx2 dekker_mul12_pwr2(const FloatBase x, const FloatBase y) {
	FloatNx2 ret;
	ret.hi = x * y;
	ret.lo = static_cast<FloatBase>(0.0);
	return ret;
}

//------------------------------------------------------------------------------
// FloatNx2 bitwise operators
//------------------------------------------------------------------------------

inline FloatNx2 bitwise_not(FloatNx2 x) {
	uint64_t* binary_part = reinterpret_cast<uint64_t*>(&x);
	binary_part[0] = ~binary_part[0];
	binary_part[1] = ~binary_part[1];
	return x;
}

inline FloatNx2 bitwise_and(FloatNx2 x, const FloatNx2 y) {
	uint64_t* x_bin = reinterpret_cast<uint64_t*>(&x);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	x_bin[0] &= y_bin[0];
	x_bin[1] &= y_bin[1];
	return x;
}

inline FloatNx2 bitwise_andnot(FloatNx2 x, const FloatNx2 y) {
	uint64_t* x_bin = reinterpret_cast<uint64_t*>(&x);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	x_bin[0] &= ~y_bin[0];
	x_bin[1] &= ~y_bin[1];
	return x;
}

inline FloatNx2 bitwise_or(FloatNx2 x, const FloatNx2 y) {
	uint64_t* x_bin = reinterpret_cast<uint64_t*>(&x);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	x_bin[0] |= y_bin[0];
	x_bin[1] |= y_bin[1];
	return x;
}

inline FloatNx2 bitwise_xor(FloatNx2 x, const FloatNx2 y) {
	uint64_t* x_bin = reinterpret_cast<uint64_t*>(&x);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	x_bin[0] ^= y_bin[0];
	x_bin[1] ^= y_bin[1];
	return x;
}

//------------------------------------------------------------------------------
// FloatNx2 Operator Overloads
//------------------------------------------------------------------------------

// #if __cplusplus >= 201304L
// 	#define FLOAT64X2_RELAXED_CONSTEXPR constexpr
// #else
// 	#define FLOAT64X2_RELAXED_CONSTEXPR
// #endif

/* Compound Assignment */

inline FloatNx2& operator+=(FloatNx2& x, const FloatNx2& y) {
	x = x + y;
	return x;
}
inline FloatNx2& operator-=(FloatNx2& x, const FloatNx2& y) {
	x = x - y;
	return x;
}
inline FloatNx2& operator*=(FloatNx2& x, const FloatNx2& y) {
	x = x * y;
	return x;
}
inline FloatNx2& operator/=(FloatNx2& x, const FloatNx2& y) {
	x = x / y;
	return x;
}

inline FloatNx2& operator+=(FloatNx2& x, const FloatBase y) {
	x = x + y;
	return x;
}
inline FloatNx2& operator-=(FloatNx2& x, const FloatBase y) {
	x = x - y;
	return x;
}
inline FloatNx2& operator*=(FloatNx2& x, const FloatBase y) {
	x = x * y;
	return x;
}
inline FloatNx2& operator/=(FloatNx2& x, const FloatBase y) {
	x = x / y;
	return x;
}

/* Increment/Decrement */

inline FloatNx2& operator++(FloatNx2& x) {
	x += static_cast<FloatBase>(1.0);
	return x;
}

inline FloatNx2& operator--(FloatNx2& x) {
	x -= static_cast<FloatBase>(1.0);
	return x;
}

inline FloatNx2 operator++(FloatNx2& x, int) {
	FloatNx2 temp = x;
	x += static_cast<FloatBase>(1.0);
	return temp;
}

inline FloatNx2 operator--(FloatNx2& x, int) {
	FloatNx2 temp = x;
	x -= static_cast<FloatBase>(1.0);
	return temp;
}

//------------------------------------------------------------------------------
// FloatNx2 Limits
//------------------------------------------------------------------------------

namespace std {
	template <>
	class numeric_limits<FloatNx2> {
	public:
		static constexpr bool is_signed = true;
		static constexpr bool is_integer = false;
		static constexpr bool is_exact = std::numeric_limits<FloatBase>::is_exact;
		static constexpr bool has_infinity = std::numeric_limits<FloatBase>::has_infinity;
		static constexpr bool has_quiet_NaN = std::numeric_limits<FloatBase>::has_quiet_NaN;
		static constexpr bool has_signaling_NaN = std::numeric_limits<FloatBase>::has_signaling_NaN;
		static constexpr std::float_denorm_style has_denorm = std::numeric_limits<FloatBase>::has_denorm;
		static constexpr bool is_bounded = std::numeric_limits<FloatBase>::is_bounded;
		static constexpr int digits = 2 * std::numeric_limits<double>::digits10;
		static constexpr int digits10 = static_cast<int>(
			static_cast<double>(std::numeric_limits<FloatNx2>::digits) * 0.30102999566398119521
		); /**< floor(mantissa bits * log10(2)) */
		/**
		 * @brief Dekker floats can represent FLT_MAX + FLT_MIN exactly, which
		 * is why an absurd amount of digits may be required.
		 */
		static constexpr int max_digits10 =
			std::numeric_limits<FloatBase>::max_exponent10 - std::numeric_limits<FloatBase>::min_exponent10 + std::numeric_limits<FloatBase>::digits10 + 1;
		static constexpr int radix = std::numeric_limits<FloatBase>::radix;
		static constexpr int min_exponent   = std::numeric_limits<FloatBase>::min_exponent   + std::numeric_limits<FloatNx2>::digits;
		static constexpr int min_exponent10 = std::numeric_limits<FloatBase>::min_exponent10 +
			static_cast<double>(std::numeric_limits<FloatNx2>::digits) * 0.30102999566398119521; /* ceil(mantissa bits * log10(2)) */;
		static constexpr int max_exponent   = std::numeric_limits<FloatBase>::max_exponent  ;
		static constexpr int max_exponent10 = std::numeric_limits<FloatBase>::max_exponent10;
		static constexpr bool traps = std::numeric_limits<FloatBase>::traps;
		inline static constexpr FloatNx2 round_error() { return {static_cast<FloatBase>(0.5), static_cast<FloatBase>(0.0)}; }
		inline static constexpr FloatNx2 infinity() {
			return {
				std::numeric_limits<FloatBase>::infinity(),
				std::numeric_limits<FloatBase>::infinity()
			};
		}
		inline static constexpr FloatNx2 quiet_NaN() {
			return {
				std::numeric_limits<FloatBase>::quiet_NaN(),
				std::numeric_limits<FloatBase>::quiet_NaN()
			};
		}
		inline static constexpr FloatNx2 signaling_NaN() {
			return {
				std::numeric_limits<FloatBase>::signaling_NaN(),
				std::numeric_limits<FloatBase>::signaling_NaN()
			};
		}
		inline static constexpr FloatNx2 denorm_min() {
			return {std::numeric_limits<FloatBase>::denorm_min(), static_cast<FloatBase>(0.0)};
		}
	};
}

//------------------------------------------------------------------------------
// FloatNx2 Math Functions
//------------------------------------------------------------------------------

/* Floating Point Classify */

	/** @brief Returns true if x is negative */
	inline constexpr bool signbit(const FloatNx2& x) {
		return std::signbit(x.hi);
	}

	/** @brief Returns true if x is finite */
	inline constexpr bool isfinite(const FloatNx2& x) {
		return std::isfinite(x.hi);
	}

	/** @brief Returns true if x is +-infinity */
	inline constexpr bool isinf(const FloatNx2& x) {
		return std::isinf(x.hi);
	}

	/** @brief Returns true if x is any kind of NaN */
	inline constexpr bool isnan(const FloatNx2& x) {
		return std::isnan(x.hi);
	}

	/** @brief Returns true if x is normal */
	inline constexpr bool isnormal(const FloatNx2& x) {
		return (std::isnormal(x.hi) && std::isnormal(x.lo));
	}
	
	/** @brief Returns true if x and y are unordered */
	inline constexpr bool isunordered(const FloatNx2& x, const FloatNx2& y) {
		return std::isunordered(x.hi, y.hi);
	}

	inline constexpr int fpclassify(const FloatNx2& x) {
		return
			isinf(x)             ? FP_INFINITE :
			isnan(x)             ? FP_NAN      :
			dekker_equal_zero(x) ? FP_ZERO     :
			isnormal(x)          ? FP_NORMAL   :
			FP_SUBNORMAL;
	}

/* Comparison */

	inline constexpr bool isgreater(const FloatNx2& x, const FloatNx2& y) {
		return (x > y);
	}
	inline constexpr bool isgreaterequal(const FloatNx2& x, const FloatNx2& y) {
		return (x >= y);
	}
	inline constexpr bool isless(const FloatNx2& x, const FloatNx2& y) {
		return (x < y);
	}
	inline constexpr bool islessequal(const FloatNx2& x, const FloatNx2& y) {
		return (x <= y);
	}
	inline constexpr bool islessgreater(const FloatNx2& x, const FloatNx2& y) {
		return (x < y || x > y);
	}

/* fmax and fmin */

	/**
	 * @brief Returns the fmax of x and y. Correctly handling NaN and signed zeros.
	 * You may use std::max as a faster alternative.
	 */
	inline constexpr FloatNx2 fmax(const FloatNx2& x, const FloatNx2& y) {
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
	inline constexpr FloatNx2 fmin(const FloatNx2& x, const FloatNx2& y) {
		return
			(x > y) ? y :
			(y > x) ? x :
			isnan(x) ? y :
			isnan(y) ? x :
			signbit(x) ? x : y;
	}

/* Arithmetic */

	inline constexpr FloatNx2 fmax(const FloatNx2& x, const FloatNx2& y, const FloatNx2& z) {
		return fmax(fmax(x, y), z);
	}
	inline constexpr FloatNx2 fmin(const FloatNx2& x, const FloatNx2& y, const FloatNx2& z) {
		return fmin(fmin(x, y), z);
	}
	inline constexpr FloatNx2 fabs(const FloatNx2& x) {
		return signbit(x) ? -x : x;
	}
	inline constexpr FloatNx2 fdim(const FloatNx2& x, const FloatNx2& y) {
		return (x > y) ? (x - y) : static_cast<FloatNx2>(0.0);
	}
	/** @note Naive implementation of fma (Fused multiply add). May lose precision */
	inline FloatNx2 fma(const FloatNx2& x, const FloatNx2& y, const FloatNx2& z) {
		return (x * y) + z;
	}
	inline constexpr FloatNx2 copysign(const FloatNx2& x, const FloatNx2& y) {
		return (signbit(x) != signbit(y)) ? -x : x;
	}
	inline FloatNx2 sqrt(const FloatNx2& x) {
		if (dekker_equal_zero(x)) {
			return x; // Preserves signed zeros
		}
		FloatBase guess = sqrt(x.hi);
		return mul_pwr2((guess + x / guess), static_cast<FloatBase>(0.5));
	}
	inline FloatNx2 cbrt(const FloatNx2& x) {
		if (dekker_equal_zero(x)) {
			return x; // Preserves signed zeros
		}
		FloatBase guess = cbrt(x.hi);
		return (
			(static_cast<FloatBase>(2.0) * guess) + (x / dekker_square12(guess))
		) / static_cast<FloatBase>(3.0);
	}
	/** @note Naive implementation of hypot, may overflow for large inputs */
	inline FloatNx2 hypot(const FloatNx2& x, const FloatNx2& y) {
		return sqrt(
			square(x) + square(y)
		);
	}
	/** @note Naive implementation of hypot, may overflow for large inputs */
	inline FloatNx2 hypot(const FloatNx2& x, const FloatNx2& y, const FloatNx2& z) {
		return sqrt(
			square(x) + square(y) + square(z)
		);
	}

/* Rounding */

	inline FloatNx2 trunc(const FloatNx2& x) {
		FloatNx2 int_hi = trunc(x.hi);
		FloatNx2 int_lo = trunc(x.lo);
		FloatBase frac_hi = x.hi - int_hi.hi;
		FloatBase frac_lo = x.lo - int_lo.hi;
		// Sum in increasing order
		FloatNx2 trunc_all = (
			dekker_add12(frac_hi, frac_lo) >= static_cast<FloatBase>(1.0)
		) ? static_cast<FloatNx2>(1.0) : static_cast<FloatNx2>(0.0);
		trunc_all += int_lo;
		trunc_all += int_hi;
		return trunc_all;
	}
	inline FloatNx2 floor(const FloatNx2& x) {
		FloatNx2 int_part = trunc(x);
		return (
			dekker_less_zero(x) && int_part != x
		) ? int_part - static_cast<FloatBase>(1.0) : int_part;
	}
	inline FloatNx2 ceil(const FloatNx2& x) {
		FloatNx2 int_part = trunc(x);
		return (
			dekker_greater_zero(x) && int_part != x
		) ? int_part + static_cast<FloatBase>(1.0) : int_part;
	}
	inline FloatNx2 round(const FloatNx2& x) {
		FloatNx2 int_part = trunc(x);
		FloatNx2 frac_part = x - int_part;
		if (dekker_greaterequal_zero(x)) {
			if (frac_part >= static_cast<FloatBase>(0.5)) {
				return int_part + static_cast<FloatBase>(1.0);
			}
			return int_part;
		}
		if (frac_part <= static_cast<FloatBase>(-0.5)) {
			return int_part - static_cast<FloatBase>(1.0);
		}
		return int_part;
	}
	inline FloatNx2 rint(const FloatNx2& x) {
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
	inline long lround(const FloatNx2& x) {
		return static_cast<long>(round(x));
	}
	inline long lrint(const FloatNx2& x) {
		return static_cast<long>(rint(x));
	}
	inline long long llround(const FloatNx2& x) {
		return static_cast<long long>(round(x));
	}
	inline long long llrint(const FloatNx2& x) {
		return static_cast<long long>(rint(x));
	}

/* Integer and Remainder */

	inline FloatNx2 fmod(const FloatNx2& x, const FloatNx2& y) {
		FloatNx2 trunc_part = trunc(x / y);
		return x - y * trunc_part;
	}
	inline FloatNx2 modf(const FloatNx2& x, FloatNx2& int_part) {
		FloatNx2 trunc_part = trunc(x);
		int_part = trunc_part;
		return x - trunc_part;
	}
	inline FloatNx2 nearbyint(const FloatNx2& x) {
		return rint(x);
	}
	inline FloatNx2 remainder(const FloatNx2& x, const FloatNx2& y) {
		FloatNx2 round_part = round(x / y);
		return x - y * round_part;
	}
	inline FloatNx2 remquo(const FloatNx2& x, const FloatNx2& y, int& quo) {
		FloatNx2 q = round(x / y);
		FloatNx2 r = x - y * q;
		quo = static_cast<int>(q);
		return r;
	}

/* Float Exponents */

	/**
	 * @brief Extracts the exponent of a FloatNx2 value to compute the
	 * binary logarithm.
	 */
	inline int ilogb(const FloatNx2& x) {
		return ilogb(x.hi);
	}
	/**
	 * @brief Returns a normalized FloatNx2 value and the exponent in
	 * the form [0.0, 1.0) * 2^expon
	 */
	inline FloatNx2 frexp(const FloatNx2& x, int& expon) {
		FloatNx2 ret;
		expon = ilogb(x.hi + x.lo) + 1;
		ret.hi = ldexp(x.hi, -(expon));
		ret.lo = ldexp(x.lo, -(expon));
		return ret;
	}
	/**
	 * @brief Multiplies a FloatNx2 value by 2^expon
	 */
	inline FloatNx2 ldexp(const FloatNx2& x, int expon) {
		FloatNx2 ret;
		ret.hi = ldexp(x.hi, expon);
		ret.lo = isfinite(x.hi) ? ldexp(x.lo, expon) : x.hi;
		return ret;
	}
	/**
	 * @brief Multiplies a FloatNx2 value by FLT_RADIX^expon
	 */
	inline FloatNx2 scalbn(const FloatNx2& x, int expon) {
		FloatNx2 ret;
		ret.hi = scalbn(x.hi, expon);
		ret.lo = isfinite(x.hi) ? scalbn(x.lo, expon) : x.hi;
		return ret;
	}
	/**
	 * @brief Multiplies a FloatNx2 value by FLT_RADIX^expon
	 */
	inline FloatNx2 scalbln(const FloatNx2& x, long expon) {
		FloatNx2 ret;
		ret.hi = scalbln(x.hi, expon);
		ret.lo = isfinite(x.hi) ? scalbln(x.lo, expon) : x.hi;
		return ret;
	}

#undef FloatN
#undef FloatNx2
#undef GENERATE_FLOATNX2_BASE_TYPE
#undef GENERATE_FLOATNX2_TYPE_NAME

#endif
