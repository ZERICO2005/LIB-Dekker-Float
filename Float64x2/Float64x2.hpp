/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef FLOAT64X2_HPP
#define FLOAT64X2_HPP

/**
 * @brief Double-Float64 Dekker Float implementation for C++.
 * Source: Creel "Double it Like Dekker" on YouTube.
 *
 * @warning -Ofast may break this library. -O3 compiles okay on gcc and clang.
 */

#include "Float64x2.h"
#include "Float64x2_def.h"

#include <cfloat>
#include <climits>
#include <cstdint>
#include <limits>
#include <cmath>
#include <cfenv>

//------------------------------------------------------------------------------
// Float64x2 Arithmetic
//------------------------------------------------------------------------------

/* Comparison */

inline constexpr bool operator==(const Float64x2& x, const Float64x2& y) {
	return (x.hi == y.hi && x.lo == y.lo);
}
inline constexpr bool operator!=(const Float64x2& x, const Float64x2& y) {
	return (x.hi != y.hi || x.lo != y.lo);
}
inline constexpr bool operator<(const Float64x2& x, const Float64x2& y) {
	return (x.hi == y.hi) ? (x.lo < y.lo) : (x.hi < y.hi);
}
inline constexpr bool operator<=(const Float64x2& x, const Float64x2& y) {
	return (x.hi == y.hi) ? (x.lo <= y.lo) : (x.hi < y.hi);
}
inline constexpr bool operator>(const Float64x2& x, const Float64x2& y) {
	return (x.hi == y.hi) ? (x.lo > y.lo) : (x.hi > y.hi);
}
inline constexpr bool operator>=(const Float64x2& x, const Float64x2& y) {
	return (x.hi == y.hi) ? (x.lo >= y.lo) : (x.hi > y.hi);
}

/* Optimized Comparison */

inline constexpr bool operator==(const Float64x2& x, const fp64 y) {
	return (x.hi == y && x.lo == 0.0);
}
inline constexpr bool operator!=(const Float64x2& x, const fp64 y) {
	return (x.hi != y || x.lo != 0.0);
}
inline constexpr bool operator<(const Float64x2& x, const fp64 y) {
	return (x.hi == y) ? (x.lo < 0.0) : (x.hi < y);
}
inline constexpr bool operator<=(const Float64x2& x, const fp64 y) {
	return (x.hi == y) ? (x.lo <= 0.0) : (x.hi < y);
}
inline constexpr bool operator>(const Float64x2& x, const fp64 y) {
	return (x.hi == y) ? (x.lo > 0.0) : (x.hi > y);
}
inline constexpr bool operator>=(const Float64x2& x, const fp64 y) {
	return (x.hi == y) ? (x.lo >= 0.0) : (x.hi > y);
}

inline constexpr bool operator==(const fp64 x, const Float64x2& y) {
	return (x == y.hi && 0.0 == y.lo);
}
inline constexpr bool operator!=(const fp64 x, const Float64x2& y) {
	return (x != y.hi || 0.0 != y.lo);
}
inline constexpr bool operator<(const fp64 x, const Float64x2& y) {
	return (x == y.hi) ? (0.0 < y.lo) : (x < y.hi);
}
inline constexpr bool operator<=(const fp64 x, const Float64x2& y) {
	return (x == y.hi) ? (0.0 <= y.lo) : (x < y.hi);
}
inline constexpr bool operator>(const fp64 x, const Float64x2& y) {
	return (x == y.hi) ? (0.0 > y.lo) : (x > y.hi);
}
inline constexpr bool operator>=(const fp64 x, const Float64x2& y) {
	return (x == y.hi) ? (0.0 >= y.lo) : (x > y.hi);
}

/* Compare to Zero */

/** @brief Assumes that if x.hi is zero then x.lo is also zero */
inline constexpr bool dekker_equal_zero(const Float64x2& x) {
	return (x.hi == 0.0);
}
/** @brief Assumes that if x.hi is zero then x.lo is also zero */
inline constexpr bool dekker_notequal_zero(const Float64x2& x) {
	return (x.hi != 0.0);
}
/** @brief Assumes that if x.hi is zero then x.lo is also zero */
inline constexpr bool dekker_less_zero(const Float64x2& x) {
	return (x.hi < 0.0);
}
/** @brief Assumes that if x.hi is zero then x.lo is also zero */
inline constexpr bool dekker_lessequal_zero(const Float64x2& x) {
	return (x.hi <= 0.0);
}
/** @brief Assumes that if x.hi is zero then x.lo is also zero */
inline constexpr bool dekker_greater_zero(const Float64x2& x) {
	return (x.hi > 0.0);
}
/** @brief Assumes that if x.hi is zero then x.lo is also zero */
inline constexpr bool dekker_greaterequal_zero(const Float64x2& x) {
	return (x.hi >= 0.0);
}

//------------------------------------------------------------------------------
// Float64x4 Basic Arithmetic
//------------------------------------------------------------------------------

/* Negation */

inline constexpr Float64x2 operator-(const Float64x2& x) {
	return {-x.hi, -x.lo};
}

inline Float64x2 operator+(const Float64x2& x, const Float64x2& y) {
	fp64 r_hi = x.hi + y.hi;
	fp64 r_lo = 0.0;
	if (fabs(x.hi) > fabs(y.hi)) {
		r_lo = x.hi - r_hi + y.hi + y.lo + x.lo;
	} else {
		r_lo = y.hi - r_hi + x.hi + x.lo + y.lo;
	}

	Float64x2 c;
	c.hi = r_hi + r_lo;
	c.lo = r_hi - c.hi + r_lo;
	return c;
}

inline Float64x2 operator-(const Float64x2& x, const Float64x2& y) {
	fp64 r_hi = x.hi - y.hi;
	fp64 r_lo = 0.0;
	if (fabs(x.hi) > fabs(y.hi)) {
		r_lo = x.hi - r_hi - y.hi - y.lo + x.lo;
	} else {
		r_lo = -y.hi - r_hi + x.hi + x.lo - y.lo;
	}

	Float64x2 c;
	c.hi = r_hi + r_lo;
	c.lo = r_hi - c.hi + r_lo;
	return c;
}

#if defined(FLOATNX2_BITWISE_SPLIT) || defined(FLOAT64X2_BITWISE_SPLIT)
	/**
	* @brief Splits the mantissa bits of a floating point value via bitwise
	* operations for use in the dekker_mul12 function.
	*/
	inline Float64x2 dekker_split(const fp64 x) {
		Bitwise_Float64x2 r;
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
	inline Float64x2 dekker_split(const fp64 x) {
		const fp64 Dekker_Scale = 134217729.0; // (2^ceil(53 / 2) + 1)
		fp64 p = x * Dekker_Scale;
		Float64x2 r;
		r.hi = (x - p) + p;
		r.lo = x - r.hi;
		return r;
	}
#endif

/**
 * @brief Multiplies two fp64 values with result stored as a Float64x2
 */
inline Float64x2 dekker_mul12(const fp64 x, const fp64 y) {
	Float64x2 a = dekker_split(x);
	Float64x2 b = dekker_split(y);
	fp64 p = a.hi * b.hi;
	fp64 q = a.hi * b.lo + a.lo * b.hi;

	Float64x2 r;
	r.hi = p + q;
	r.lo = p - r.hi + q + a.lo * b.lo;
	return r;
}

inline Float64x2 operator*(const Float64x2& x, const Float64x2& y) {
	Float64x2 t = dekker_mul12(x.hi, y.hi);
	fp64 c = x.hi * y.lo + x.lo * y.hi + t.lo;

	Float64x2 r;
	r.hi = t.hi + c;
	r.lo = t.hi - r.hi + c;
	return r;
}

inline Float64x2 operator/(const Float64x2& x, const Float64x2& y) {
	fp64 u = x.hi / y.hi;
	Float64x2 t = dekker_mul12(u, y.hi);
	fp64 l = (x.hi - t.hi - t.lo + x.lo - u * y.lo) / y.hi;

	Float64x2 r;
	r.hi = u + l;
	r.lo = u - r.hi + l;
	return r;
}

/**
 * @brief Squares a fp64 value with the result stored as a Float64x2
 */
inline Float64x2 dekker_square12(const fp64 x) {
	Float64x2 a = dekker_split(x);
	fp64 p = a.hi * a.hi;
	fp64 q = 2.0 * (a.hi * a.lo);

	Float64x2 r;
	r.hi = p + q;
	r.lo = (
		((p - r.hi) + q) +
		(a.lo + a.lo)
	);
	return r;
}

inline Float64x2 square(const Float64x2 x) {
	Float64x2 t = dekker_square12(x.hi);
	fp64 c = ((2.0 * (x.hi * x.lo)) + t.lo);

	Float64x2 r;
	r.hi = (t.hi + c);
	r.lo = ((t.hi - r.hi) + c);
	return r;
}

inline Float64x2 recip(const Float64x2 y) {
	fp64 u = (1.0 / y.hi);
	Float64x2 t = dekker_mul12(u, y.hi);
	fp64 l = ((((1.0 - t.hi) - t.lo) - (u * y.lo)) / y.hi);

	Float64x2 r;
	r.hi = (u + l);
	r.lo = ((u - r.hi) + l);
	return r;
}

//------------------------------------------------------------------------------
// Float64x2 optimized arithmetic
//------------------------------------------------------------------------------

inline Float64x2 operator+(const Float64x2& x, const fp64 y) {
	fp64 r_hi = x.hi + y;
	fp64 r_lo = 0.0;
	if (fabs(x.hi) > fabs(y)) {
		r_lo = x.hi - r_hi + y + x.lo;
	} else {
		r_lo = y - r_hi + x.hi + x.lo;
	}

	Float64x2 c;
	c.hi = r_hi + r_lo;
	c.lo = r_hi - c.hi + r_lo;
	return c;
}

inline Float64x2 operator+(const fp64 x, const Float64x2& y) {
	fp64 r_hi = x + y.hi;
	fp64 r_lo = 0.0;
	if (fabs(x) > fabs(y.hi)) {
		r_lo = x - r_hi + y.hi + y.lo;
	} else {
		r_lo = y.hi - r_hi + x + y.lo;
	}

	Float64x2 c;
	c.hi = r_hi + r_lo;
	c.lo = r_hi - c.hi + r_lo;
	return c;
}

/**
 * @brief Adds two fp64 values with the result stored as a Float64x2
 */
inline Float64x2 dekker_add12(const fp64 x, const fp64 y) {
	fp64 r_hi = x + y;
	fp64 r_lo = 0.0;
	if (fabs(x) > fabs(y)) {
		r_lo = x - r_hi + y;
	} else {
		r_lo = y - r_hi + x;
	}

	Float64x2 c;
	c.hi = r_hi + r_lo;
	c.lo = r_hi - c.hi + r_lo;
	return c;
}

inline Float64x2 operator-(const Float64x2& x, const fp64 y) {
	fp64 r_hi = x.hi - y;
	fp64 r_lo = 0.0;
	if (fabs(x.hi) > fabs(y)) {
		r_lo = x.hi - r_hi - y + x.lo;
	} else {
		r_lo = -y - r_hi + x.hi + x.lo;
	}

	Float64x2 c;
	c.hi = r_hi + r_lo;
	c.lo = r_hi - c.hi + r_lo;
	return c;
}

inline Float64x2 operator-(const fp64 x, const Float64x2& y) {
	fp64 r_hi = x - y.hi;
	fp64 r_lo = 0.0;
	if (fabs(x) > fabs(y.hi)) {
		r_lo = x - r_hi - y.hi - y.lo;
	} else {
		r_lo = -y.hi - r_hi + x - y.lo;
	}

	Float64x2 c;
	c.hi = r_hi + r_lo;
	c.lo = r_hi - c.hi + r_lo;
	return c;
}

/**
 * @brief Subtracts two fp64 values with the result stored as a Float64x2
 */
inline Float64x2 dekker_sub12(const fp64 x, const fp64 y) {
	fp64 r_hi = x - y;
	fp64 r_lo = 0.0;
	if (fabs(x) > fabs(y)) {
		r_lo = x - r_hi - y;
	} else {
		r_lo = -y - r_hi + x;
	}

	Float64x2 c;
	c.hi = r_hi + r_lo;
	c.lo = r_hi - c.hi + r_lo;
	return c;
}

inline Float64x2 operator*(const Float64x2& x, const fp64 y) {
	Float64x2 t = dekker_mul12(x.hi, y);
	fp64 c = ((x.lo * y) + t.lo);

	Float64x2 r;
	r.hi = (t.hi + c);
	r.lo = ((t.hi - r.hi) + c);
	return r;
}

inline Float64x2 operator*(const fp64 x, const Float64x2& y) {
	Float64x2 t = dekker_mul12(x, y.hi);
	fp64 c = ((x * y.lo) + t.lo);

	Float64x2 r;
	r.hi = (t.hi + c);
	r.lo = ((t.hi - r.hi) + c);
	return r;
}

inline Float64x2 operator/(const Float64x2& x, const fp64 y) {
	fp64 u = x.hi / y;
	Float64x2 t = dekker_mul12(u, y);
	fp64 l = (((x.hi - t.hi) - t.lo) + x.lo) / y;

	Float64x2 r;
	r.hi = u + l;
	r.lo = (u - r.hi) + l;
	return r;
}

inline Float64x2 operator/(const fp64 x, const Float64x2& y) {
	fp64 u = x / y.hi;
	Float64x2 t = dekker_mul12(u, y.hi);
	fp64 l = (((x - t.hi) - t.lo) - (u * y.lo)) / y.hi;

	Float64x2 r;
	r.hi = u + l;
	r.lo = (u - r.hi) + l;
	return r;
}

/**
 * @brief Divides two fp64 values with the result stored as a Float64x2
 */
inline Float64x2 dekker_div12(const fp64 x, const fp64 y) {
	fp64 u = x / y;
	Float64x2 t = dekker_mul12(u, y);
	fp64 l = ((x - t.hi) - t.lo) / y;

	Float64x2 r;
	r.hi = u + l;
	r.lo = (u - r.hi) + l;
	return r;
}

/**
 * @brief Calculates the reciprocal of a fp64 value with the result stored
 * as a Float64x2
 */

inline Float64x2 dekker_recip12(const fp64 y) {
	fp64 u = (1.0 / y);
	Float64x2 t = dekker_mul12(u, y);
	fp64 l = (((1.0 - t.hi) - t.lo) / y);

	Float64x2 r;
	r.hi = (u + l);
	r.lo = ((u - r.hi) + l);
	return r;
}

//------------------------------------------------------------------------------
// Float64x2 specialized arithmetic
//------------------------------------------------------------------------------

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero
 */
inline Float64x2 mul_pwr2(const Float64x2& x, const fp64 y) {
	Float64x2 ret;
	ret.hi = x.hi * y;
	ret.lo = x.lo * y;
	return ret;
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero
 */
inline Float64x2 mul_pwr2(const fp64 x, const Float64x2& y) {
	Float64x2 ret;
	ret.hi = x * y.hi;
	ret.lo = x * y.lo;
	return ret;
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero.
 * The result is stored as a Float64x2
 */
inline Float64x2 dekker_mul12_pwr2(const fp64 x, const fp64 y) {
	Float64x2 ret;
	ret.hi = x * y;
	ret.lo = 0.0;
	return ret;
}

//------------------------------------------------------------------------------
// Float64x2 bitwise operators
//------------------------------------------------------------------------------

inline Float64x2 bitwise_not(Float64x2 x) {
	uint64_t* binary_part = reinterpret_cast<uint64_t*>(&x);
	binary_part[0] = ~binary_part[0];
	binary_part[1] = ~binary_part[1];
	return x;
}

inline Float64x2 bitwise_and(Float64x2 x, const Float64x2 y) {
	uint64_t* x_bin = reinterpret_cast<uint64_t*>(&x);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	x_bin[0] &= y_bin[0];
	x_bin[1] &= y_bin[1];
	return x;
}

inline Float64x2 bitwise_andnot(Float64x2 x, const Float64x2 y) {
	uint64_t* x_bin = reinterpret_cast<uint64_t*>(&x);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	x_bin[0] &= ~y_bin[0];
	x_bin[1] &= ~y_bin[1];
	return x;
}

inline Float64x2 bitwise_or(Float64x2 x, const Float64x2 y) {
	uint64_t* x_bin = reinterpret_cast<uint64_t*>(&x);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	x_bin[0] |= y_bin[0];
	x_bin[1] |= y_bin[1];
	return x;
}

inline Float64x2 bitwise_xor(Float64x2 x, const Float64x2 y) {
	uint64_t* x_bin = reinterpret_cast<uint64_t*>(&x);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	x_bin[0] ^= y_bin[0];
	x_bin[1] ^= y_bin[1];
	return x;
}

//------------------------------------------------------------------------------
// Float64x2 Operator Overloads
//------------------------------------------------------------------------------

// #if __cplusplus >= 201304L
// 	#define FLOAT64X2_RELAXED_CONSTEXPR constexpr
// #else
// 	#define FLOAT64X2_RELAXED_CONSTEXPR
// #endif

/* Compound Assignment */

inline Float64x2& operator+=(Float64x2 &x, const Float64x2 &y) {
	x = x + y;
	return x;
}
inline Float64x2& operator-=(Float64x2 &x, const Float64x2 &y) {
	x = x - y;
	return x;
}
inline Float64x2& operator*=(Float64x2 &x, const Float64x2 &y) {
	x = x * y;
	return x;
}
inline Float64x2& operator/=(Float64x2 &x, const Float64x2 &y) {
	x = x / y;
	return x;
}

inline Float64x2& operator+=(Float64x2 &x, const fp64 y) {
	x = x + y;
	return x;
}
inline Float64x2& operator-=(Float64x2 &x, const fp64 y) {
	x = x - y;
	return x;
}
inline Float64x2& operator*=(Float64x2 &x, const fp64 y) {
	x = x * y;
	return x;
}
inline Float64x2& operator/=(Float64x2 &x, const fp64 y) {
	x = x / y;
	return x;
}

/* Increment/Decrement */

inline Float64x2& operator++(Float64x2& x) {
	x += 1.0;
	return x;
}

inline Float64x2& operator--(Float64x2& x) {
	x -= 1.0;
	return x;
}

inline Float64x2 operator++(Float64x2& x, int) {
	Float64x2 temp = x;
	x += 1.0;
	return temp;
}

inline Float64x2 operator--(Float64x2& x, int) {
	Float64x2 temp = x;
	x -= 1.0;
	return temp;
}

//------------------------------------------------------------------------------
// Float64x2 Limits
//------------------------------------------------------------------------------

namespace std {
	template <>
	class numeric_limits<Float64x2> {
	public:
		static constexpr bool is_signed = true;
		static constexpr bool is_integer = false;
		static constexpr bool is_exact = false;
		static constexpr bool has_infinity = std::numeric_limits<fp64>::has_infinity;
		static constexpr bool has_quiet_NaN = std::numeric_limits<fp64>::has_quiet_NaN;
		static constexpr bool has_signaling_NaN = std::numeric_limits<fp64>::has_signaling_NaN;
		static constexpr std::float_denorm_style has_denorm = std::numeric_limits<fp64>::has_denorm;
		static constexpr bool is_bounded = true;
		static constexpr int digits = 104;
		static constexpr int digits10 = 31;
		/**
		 * @brief Dekker floats can represent FLT_MAX + FLT_MIN exactly, which
		 * is why an absurd amount of digits may be required.
		 */
		static constexpr int max_digits10 =
			std::numeric_limits<fp64>::max_exponent10 - std::numeric_limits<fp64>::min_exponent10 + std::numeric_limits<fp64>::digits10 + 1;
		static constexpr int radix = std::numeric_limits<fp64>::radix;
		static constexpr int min_exponent   = std::numeric_limits<fp64>::min_exponent   + 53;
		static constexpr int min_exponent10 = std::numeric_limits<fp64>::min_exponent10 + 16 /* ceil(53 * log10(2)) */;
		static constexpr int max_exponent   = std::numeric_limits<fp64>::max_exponent  ;
		static constexpr int max_exponent10 = std::numeric_limits<fp64>::max_exponent10;
		static constexpr bool traps = std::numeric_limits<fp64>::traps;
		inline static constexpr Float64x2 min() {
			/** 
			 * @remarks libQD lists this as the minimum value that is fully
			 * normalized, although I am not sure if this is the best
			 * definition to use for min()
			 */
			return {std::numeric_limits<fp64>::min() * 0x1.0p+53, std::numeric_limits<fp64>::min()};
			// return {std::numeric_limits<fp64>::min(), 0.0};
		}
	
		inline static constexpr Float64x2 max() {
			return {
				std::numeric_limits<fp64>::max(),
				std::numeric_limits<fp64>::max() * 0x1.0p-54
			};
		}
		inline static constexpr Float64x2 lowest() { return -max(); }
		inline static constexpr Float64x2 epsilon() { return {0x1.0p-104, 0.0}; }
		inline static constexpr Float64x2 round_error() { return {0.5, 0.0}; }
		inline static constexpr Float64x2 infinity() {
			return {
				std::numeric_limits<fp64>::infinity(),
				std::numeric_limits<fp64>::infinity()
			};
		}
		inline static constexpr Float64x2 quiet_NaN() {
			return {
				std::numeric_limits<fp64>::quiet_NaN(),
				std::numeric_limits<fp64>::quiet_NaN()
			};
		}
		inline static constexpr Float64x2 signaling_NaN() {
			return {
				std::numeric_limits<fp64>::signaling_NaN(),
				std::numeric_limits<fp64>::signaling_NaN()
			};
		}
		inline static constexpr Float64x2 denorm_min() {
			return {std::numeric_limits<fp64>::denorm_min(), 0.0};
		}
	};
}

//------------------------------------------------------------------------------
// Float64x2 Constants
//------------------------------------------------------------------------------

/* C++20 <numbers> */

	constexpr Float64x2 Float64x2_e          = {0x1.5bf0a8b145769p+1,+0x1.4d57ee2b1013ap-53}; /**< ~2.718281828 */
	constexpr Float64x2 Float64x2_log2e      = {0x1.71547652b82fep+0,+0x1.777d0ffda0d24p-56}; /**< ~1.442695041 */
	constexpr Float64x2 Float64x2_log10e     = {0x1.bcb7b1526e50ep-2,+0x1.95355baaafad3p-57}; /**< ~0.434294482 */
	constexpr Float64x2 Float64x2_pi         = {0x1.921fb54442d18p+1,+0x1.1a62633145c07p-53}; /**< ~3.141592654 */
	constexpr Float64x2 Float64x2_inv_pi     = {0x1.45f306dc9c883p-2,-0x1.6b01ec5417056p-56}; /**< ~0.318309886 */
	constexpr Float64x2 Float64x2_inv_sqrtpi = {0x1.20dd750429b6dp-1,+0x1.1ae3a914fed80p-57}; /**< ~0.564189584 */
	constexpr Float64x2 Float64x2_ln2        = {0x1.62e42fefa39efp-1,+0x1.abc9e3b39803fp-56}; /**< ~0.693147181 */
	constexpr Float64x2 Float64x2_ln10       = {0x1.26bb1bbb55516p+1,-0x1.f48ad494ea3e9p-53}; /**< ~2.302585093 */
	constexpr Float64x2 Float64x2_sqrt2      = {0x1.6a09e667f3bcdp+0,-0x1.bdd3413b26456p-54}; /**< ~1.414213562 */
	constexpr Float64x2 Float64x2_sqrt3      = {0x1.bb67ae8584caap+0,+0x1.cec95d0b5c1e3p-54}; /**< ~1.732050808 */
	constexpr Float64x2 Float64x2_inv_sqrt3  = {0x1.279a74590331cp-1,+0x1.34863e0792bedp-55}; /**< ~0.577350269 */
	constexpr Float64x2 Float64x2_egamma     = {0x1.2788cfc6fb619p-1,-0x1.6cb90701fbfabp-58}; /**< ~0.577215665 */
	constexpr Float64x2 Float64x2_phi        = {0x1.9e3779b97f4a8p+0,-0x1.f506319fcfd19p-55}; /**< ~1.618033989 */

#if __cplusplus >= 201907L
#include <numbers>
namespace std {
	namespace numbers {
		template<> inline constexpr Float64x2 e_v          <Float64x2> = Float64x2_e         ; /**< ~2.718281828 */
		template<> inline constexpr Float64x2 log2e_v      <Float64x2> = Float64x2_log2e     ; /**< ~1.442695041 */
		template<> inline constexpr Float64x2 log10e_v     <Float64x2> = Float64x2_log10e    ; /**< ~0.434294482 */
		template<> inline constexpr Float64x2 pi_v         <Float64x2> = Float64x2_pi        ; /**< ~3.141592654 */
		template<> inline constexpr Float64x2 inv_pi_v     <Float64x2> = Float64x2_inv_pi    ; /**< ~0.318309886 */
		template<> inline constexpr Float64x2 inv_sqrtpi_v <Float64x2> = Float64x2_inv_sqrtpi; /**< ~0.564189584 */
		template<> inline constexpr Float64x2 ln2_v        <Float64x2> = Float64x2_ln2       ; /**< ~0.693147181 */
		template<> inline constexpr Float64x2 ln10_v       <Float64x2> = Float64x2_ln10      ; /**< ~2.302585093 */
		template<> inline constexpr Float64x2 sqrt2_v      <Float64x2> = Float64x2_sqrt2     ; /**< ~1.414213562 */
		template<> inline constexpr Float64x2 sqrt3_v      <Float64x2> = Float64x2_sqrt3     ; /**< ~1.732050808 */
		template<> inline constexpr Float64x2 inv_sqrt3_v  <Float64x2> = Float64x2_inv_sqrt3 ; /**< ~0.577350269 */
		template<> inline constexpr Float64x2 egamma_v     <Float64x2> = Float64x2_egamma    ; /**< ~0.577215665 */
		template<> inline constexpr Float64x2 phi_v        <Float64x2> = Float64x2_phi       ; /**< ~1.618033989 */
	}
}
#endif

/* Other constants */

	constexpr Float64x2 Float64x2_inv_e = {+0x1.78b56362cef370p-2, +0x1.8d5d6f63c14820p-55}; /**< ~0.367879 */

	constexpr Float64x2 Float64x2_2pi  = {+0x1.921fb54442d180p+2, +0x1.1a62633145c060p-52}; /**< ~6.283185 */
	constexpr Float64x2 Float64x2_pi2  = {+0x1.921fb54442d180p+0, +0x1.1a62633145c060p-54}; /**< ~1.570796 */
	constexpr Float64x2 Float64x2_pi4  = {+0x1.921fb54442d180p-1, +0x1.1a62633145c060p-55}; /**< ~0.785398 */
	constexpr Float64x2 Float64x2_pi8  = {+0x1.921fb54442d180p-2, +0x1.1a62633145c060p-56}; /**< ~0.392699 */
	constexpr Float64x2 Float64x2_pi16 = {+0x1.921fb54442d180p-3, +0x1.1a62633145c060p-57}; /**< ~0.196350 */
	constexpr Float64x2 Float64x2_3pi4 = {+0x1.2d97c7f3321d20p+0, +0x1.a79394c9e8a0a0p-55}; /**< ~2.356194 */

/* Constant Aliases */

	constexpr Float64x2 Float64x2_euler = Float64x2_e   ; /**< ~0.693147181 */

	constexpr Float64x2 Float64x2_tau   = Float64x2_2pi ; /**< ~6.283185 */
	constexpr Float64x2 Float64x2_tau2  = Float64x2_pi  ; /**< ~3.141593 */
	constexpr Float64x2 Float64x2_tau4  = Float64x2_pi2 ; /**< ~1.570796 */
	constexpr Float64x2 Float64x2_tau8  = Float64x2_pi4 ; /**< ~0.785398 */
	constexpr Float64x2 Float64x2_tau16 = Float64x2_pi8 ; /**< ~0.392699 */
	constexpr Float64x2 Float64x2_tau32 = Float64x2_pi16; /**< ~0.196350 */
	constexpr Float64x2 Float64x2_3tau8 = Float64x2_3pi4; /**< ~2.356194 */

/* Math functions (Natively implemented) */

	/* Arithmetic */

	inline constexpr Float64x2 fmax(const Float64x2& x, const Float64x2& y) {
		return (x > y) ? x : y;
	}
	inline constexpr Float64x2 fmax(const Float64x2& x, const Float64x2& y, const Float64x2& z) {
		return (x > y) ?
		((x > z) ? x : z) :
		((y > z) ? y : z);
	}
	inline constexpr Float64x2 fmin(const Float64x2& x, const Float64x2& y) {
		return (x < y) ? x : y;
	}
	inline constexpr Float64x2 fmin(const Float64x2& x, const Float64x2& y, const Float64x2& z) {
		return (x < y) ?
		((x < z) ? x : z) :
		((y < z) ? y : z);
	}
	inline constexpr Float64x2 fabs(const Float64x2& x) {
		return (dekker_less_zero(x)) ? -x : x;
	}
	inline constexpr Float64x2 fdim(const Float64x2& x, const Float64x2& y) {
		return (x > y) ? (x - y) : static_cast<Float64x2>(0.0);
	}
	/** @note Naive implementation of fma (Fused multiply add). May lose precision */
	inline Float64x2 fma(const Float64x2& x, const Float64x2& y, const Float64x2& z) {
		return (x * y) + z;
	}
	inline constexpr Float64x2 copysign(const Float64x2& x, const Float64x2& y) {
		return (
			(dekker_less_zero(x)) != (dekker_less_zero(y))
		) ? -x : x;
	}
	inline Float64x2 sqrt(const Float64x2& x) {
		if (dekker_equal_zero(x)) {
			return x;
		}
		fp64 guess = sqrt(x.hi);
		return mul_pwr2((guess + x / guess), static_cast<fp64>(0.5));
	}
	inline Float64x2 cbrt(const Float64x2& x) {
		if (dekker_equal_zero(x)) {
			return x;
		}
		fp64 guess = cbrt(x.hi);
		return (
			(static_cast<fp64>(2.0) * guess) + (x / dekker_square12(guess))
		) / static_cast<fp64>(3.0);
	}
	/** @note Naive implementation of hypot, may overflow for large inputs */
	inline Float64x2 hypot(const Float64x2& x, const Float64x2& y) {
		return sqrt(
			square(x) + square(y)
		);
	}
	/** @note Naive implementation of hypot, may overflow for large inputs */
	inline Float64x2 hypot(const Float64x2& x, const Float64x2& y, const Float64x2& z) {
		return sqrt(
			square(x) + square(y) + square(z)
		);
	}

/* Trigonometry */

	Float64x2  sin (const Float64x2& x);
	Float64x2  cos (const Float64x2& x);
	void sincos(const Float64x2& x, Float64x2& p_sin , Float64x2& p_cos );
	inline Float64x2 tan(const Float64x2& x) {
		Float64x2 sin_val, cos_val;
		sincos(x, sin_val, cos_val);
		return sin_val / cos_val;
	}
	Float64x2 asin (const Float64x2& x);
	Float64x2 acos (const Float64x2& x);
	Float64x2 atan (const Float64x2& x);
	Float64x2  sinh(const Float64x2& x);
	Float64x2  cosh(const Float64x2& x);
	void sinhcosh(const Float64x2& x, Float64x2& p_sinh, Float64x2& p_cosh);
	Float64x2  tanh(const Float64x2& x);
	Float64x2 asinh(const Float64x2& x);
	Float64x2 acosh(const Float64x2& x);
	Float64x2 atanh(const Float64x2& x);
	Float64x2 atan2(const Float64x2& y, const Float64x2& x);

/* Logarithms and Exponents */

	Float64x2 log(const Float64x2& x);
	Float64x2 log1p(const Float64x2& x);
	inline Float64x2 log2(const Float64x2 x) {
		return log(x) * Float64x2_log2e;
	}
	inline Float64x2 log10(const Float64x2 x) {
		return log(x) * Float64x2_log10e;
	}
	inline Float64x2 logb(const Float64x2 x) { return logb(x.hi + x.lo); }

	Float64x2 exp(const Float64x2& x);
	Float64x2 expm1(const Float64x2& x);
	inline Float64x2 exp2(const Float64x2 x) {
		return exp(x * Float64x2_ln2);
	}
	inline Float64x2 exp10(const Float64x2 x) {
		return exp(x * Float64x2_ln10);
	}

	inline Float64x2 pow(const Float64x2 x, const Float64x2 y) {
		return exp(y * log(x));
	}
	inline Float64x2 pow(const Float64x2 x, const fp64 y) {
		return exp(y * log(x));
	}

/* Tests */

	inline constexpr bool signbit(const Float64x2& x) {
		return (x.hi < 0.0) ? true : false;
	}
	/** Returns true if both x.hi and x.lo are finite */
	inline constexpr bool isfinite(const Float64x2& x) {
		return (isfinite(x.hi) && isfinite(x.lo));
	}
	/** Returns true if either x.hi or x.lo are infinite */
	inline constexpr bool isinf(const Float64x2& x) {
		return (isinf(x.hi) || isinf(x.lo));
	}
	/** Returns true if either x.hi or x.lo are nan */
	inline constexpr bool isnan(const Float64x2& x) {
		return (isnan(x.hi) || isnan(x.lo));
	}
	/** Returns true if both x.hi and x.lo are normal */
	inline constexpr bool isnormal(const Float64x2& x) {
		return (isnormal(x.hi) && isnormal(x.lo));
	}
	/** Returns true if either {x.hi, y.hi} or {x.lo, y.lo} are unordered */
	inline constexpr bool isunordered(const Float64x2& x, const Float64x2& y) {
		return (isunordered(x.hi, y.hi) || isunordered(x.lo, y.lo));
	}
	inline constexpr int fpclassify(const Float64x2& x) {
		return
			isinf(x)             ? FP_INFINITE :
			isnan(x)             ? FP_NAN      :
			dekker_equal_zero(x) ? FP_ZERO     :
			isnormal(x)          ? FP_NORMAL   :
			FP_SUBNORMAL;
	}

/* Comparison */

	inline constexpr bool isgreater(const Float64x2& x, const Float64x2& y) {
		return (x > y);
	}
	inline constexpr bool isgreaterequal(const Float64x2& x, const Float64x2& y) {
		return (x >= y);
	}
	inline constexpr bool isless(const Float64x2& x, const Float64x2& y) {
		return (x < y);
	}
	inline constexpr bool islessequal(const Float64x2& x, const Float64x2& y) {
		return (x <= y);
	}
	inline constexpr bool islessgreater(const Float64x2& x, const Float64x2& y) {
		return (x < y) || (x > y);
	}
	
/* Rounding */

	inline Float64x2 trunc(const Float64x2& x) {
		Float64x2 int_hi = trunc(x.hi);
		Float64x2 int_lo = trunc(x.lo);
		fp64 frac_hi = x.hi - int_hi.hi;
		fp64 frac_lo = x.lo - int_lo.hi;
		// Sum in increasing order
		Float64x2 trunc_all = (
			dekker_add12(frac_hi, frac_lo) >= static_cast<fp64>(1.0)
		) ? static_cast<Float64x2>(1.0) : static_cast<Float64x2>(0.0);
		trunc_all += int_lo;
		trunc_all += int_hi;
		return trunc_all;
	}
	inline Float64x2 floor(const Float64x2& x) {
		Float64x2 int_part = trunc(x);
		return (
			dekker_less_zero(x) && int_part != x
		) ? int_part - static_cast<fp64>(1.0) : int_part;
	}
	inline Float64x2 ceil(const Float64x2& x) {
		Float64x2 int_part = trunc(x);
		return (
			dekker_greater_zero(x) && int_part != x
		) ? int_part + static_cast<fp64>(1.0) : int_part;
	}
	inline Float64x2 round(const Float64x2& x) {
		Float64x2 int_part = trunc(x);
		Float64x2 frac_part = x - int_part;
		if (dekker_greaterequal_zero(x)) {
			if (frac_part >= static_cast<fp64>(0.5)) {
				return int_part + static_cast<fp64>(1.0);
			}
			return int_part;
		}
		if (frac_part <= static_cast<fp64>(-0.5)) {
			return int_part - static_cast<fp64>(1.0);
		}
		return int_part;
	}
	inline Float64x2 rint(const Float64x2& x) {
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
	inline long lround(const Float64x2& x) {
		return static_cast<long>(round(x));
	}
	inline long lrint(const Float64x2& x) {
		return static_cast<long>(rint(x));
	}
	inline long long llround(const Float64x2& x) {
		return static_cast<long long>(round(x));
	}
	inline long long llrint(const Float64x2& x) {
		return static_cast<long long>(rint(x));
	}

	/* Integer and Remainder */

	inline Float64x2 fmod(const Float64x2& x, const Float64x2& y) {
		Float64x2 trunc_part = trunc(x / y);
		return x - y * trunc_part;
	}
	inline Float64x2 modf(const Float64x2& x, Float64x2* int_part) {
		Float64x2 trunc_part = trunc(x);
		if (int_part != nullptr) {
			*int_part = trunc_part;
		}
		return x - trunc_part;
	}
	inline Float64x2 nearbyint(const Float64x2& x) {
		return rint(x);
	}
	inline Float64x2 remainder(const Float64x2& x, const Float64x2& y) {
		Float64x2 round_part = round(x / y);
		return x - y * round_part;
	}
	inline Float64x2 remquo(const Float64x2& x, const Float64x2& y, int* quo) {
		Float64x2 q = round(x / y);
		Float64x2 r = x - y * q;
		*quo = static_cast<int>(q.hi + q.lo);
		return r;
	}
	/* Float Exponents */
	/** @brief ilogb(x.hi) */
	inline int ilogb(const Float64x2& x) {
		return ilogb(x.hi);
	}
	/** @brief frexp(x.hi, exp) */
	inline Float64x2 frexp(const Float64x2& x, int* exp) {
		return frexp(x.hi, exp);
	}
	inline Float64x2 ldexp(Float64x2 x, int exp) {
		x.hi = ldexp(x.hi, exp);
		x.lo = isfinite(x.hi) ? ldexp(x.lo, exp) : x.hi;
		return x;
	}
	inline Float64x2 scalbn(Float64x2 x, int exp) {
		x.hi = scalbn(x.hi, exp);
		x.lo = isfinite(x.hi) ? scalbn(x.lo, exp) : x.hi;
		return x;
	}
	inline Float64x2 scalbln(Float64x2 x, long exp) {
		x.hi = scalbln(x.hi, exp);
		x.lo = isfinite(x.hi) ? scalbln(x.lo, exp) : x.hi;
		return x;
	}

/* Transcendental Functions */
	
	/** 
	 * @note casts to long double for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float64x2 erf(const Float64x2& x) {
		return static_cast<Float64x2>(
			erf(static_cast<long double>(x))
		);
	}
	/** 
	 * @note casts to long double for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float64x2 erfc(const Float64x2& x) {
		return static_cast<Float64x2>(
			erfc(static_cast<long double>(x))
		);
	}
	/** 
	 * @note casts to long double for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float64x2 lgamma(const Float64x2& x) {
		return static_cast<Float64x2>(
			lgamma(static_cast<long double>(x))
		);
	}
	/** 
	 * @note casts to long double for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float64x2 tgamma(const Float64x2& x) {
		return static_cast<Float64x2>(
			tgamma(static_cast<long double>(x))
		);
	}

//------------------------------------------------------------------------------
// Float64x2 String Operations
//------------------------------------------------------------------------------

	#include <istream>
	/**
	* @brief Wrapper for stringTo_Float64x2
	*/
	inline std::istream& operator>>(std::istream& stream, Float64x2& value);
	
	#include <ostream>
	/**
	* @brief Wrapper for Float64x2_snprintf
	*/
	inline std::ostream& operator<<(std::ostream& stream, const Float64x2& value);

#endif /* FLOAT64X2_HPP */