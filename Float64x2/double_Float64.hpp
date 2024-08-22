/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/
#ifndef FLOAT64X2_HPP
#define FLOAT64X2_HPP

#include "Float64x2.h"
#include "Float64x2_def.h"

#include <cfloat>
#include <cstdint>
#include <limits>
#include <cmath>
#include <cfenv>

// Can be changed to other types for better accuracy
// typedef fp64 fp64x2_Math; // deprecated

#if 0
/**
 * @brief Double-Float64 Dekker Float implementation for C++.
 * Source: Creel "Double it Like Dekker" on YouTube.
 *
 * @warning -Ofast may break this library. -O3 compiles okay on gcc and clang.
 */
struct Float64x2 {
	fp64 hi;
	fp64 lo;

	
	/* Arithmetic */

	static inline Float64x2 Dekker_Add(
		const Float64x2& x, const Float64x2& y
	) {
		fp64 r_hi = x.hi + y.hi;
		fp64 r_lo = static_cast<fp64>(0.0);
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

	static inline Float64x2 Dekker_Sub(
		const Float64x2& x, const Float64x2& y
	) {
		fp64 r_hi = x.hi - y.hi;
		fp64 r_lo = static_cast<fp64>(0.0);
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

	static constexpr fp64 Dekker_Scale = 134217729.0; // (2^ceil(53 / 2) + 1)
	
	static inline Float64x2 Dekker_Split(const fp64& x) {
		fp64 p = x * Dekker_Scale;
		Float64x2 r;
		r.hi = (x - p) + p;
		r.lo = x - r.hi;
		return r;
	}
	
	// static constexpr uint64_t Dekker_Split_Mask = ~((uint64_t)0x3FFFFFF);

	// static inline Float64x2 Dekker_Split(const fp64& x) {
	// 	Float64x2 r;
	// 	uint64_t temp = (*(uint64_t*)((void*)&x)) & Dekker_Split_Mask;
	// 	r.hi = (*(fp64*)((void*)&temp));
	// 	r.lo = x - r.hi;
	// 	return r;
	// }

	static inline Float64x2 Dekker_Mul12(
		const fp64& x, const fp64& y
	) {
		Float64x2 a = Dekker_Split(x);
		Float64x2 b = Dekker_Split(y);
		fp64 p = a.hi * b.hi;
		fp64 q = a.hi * b.lo + a.lo * b.hi;

		Float64x2 r;
		r.hi = p + q;
		r.lo = p - r.hi + q + a.lo * b.lo;
		return r;
	}

	static inline Float64x2 Dekker_Mul(
		const Float64x2& x, const Float64x2& y
	) {
		Float64x2 t = Dekker_Mul12(x.hi, y.hi);
		fp64 c = x.hi * y.lo + x.lo * y.hi + t.lo;

		Float64x2 r;
		r.hi = t.hi + c;
		r.lo = t.hi - r.hi + c;
		return r;
	}

	static inline Float64x2 Dekker_Div(
		const Float64x2& x, const Float64x2& y
	) {
		fp64 u = x.hi / y.hi;
		Float64x2 t = Dekker_Mul12(u, y.hi);
		fp64 l = (x.hi - t.hi - t.lo + x.lo - u * y.lo) / y.hi;

		Float64x2 r;
		r.hi = u + l;
		r.lo = u - r.hi + l;
		return r;
	}

	// static inline Float64x2 Dekker_Div(
	// 	const Float64x2& x, const Float64x2& y
	// ) {
	// 	Float64x2 q;
	// 	fp64 q_bottom;
	// 	Float64x2 r;

	// 	q.hi = x.hi / y.hi;  /* approximate quotient */

	// 	r = x - y * q.hi;
		
	// 	q.lo = r.hi / y.hi;
	// 	r -= (y * q.lo);

	// 	q_bottom = r.hi / y.hi;

	// 	fp64 s = q.hi + q.lo;
	// 	q.lo = q.lo - (s - q.hi);
	// 	q.hi = s;

	// 	r = q + q_bottom;
	// 	return r;
	// }

	static inline Float64x2 Dekker_Sqr12(
		const fp64& x
	) {
		Float64x2 a = Dekker_Split(x);
		fp64 p = a.hi * a.hi;
		fp64 q = static_cast<fp64>(2.0) * a.hi * a.lo;

		Float64x2 r;
		r.hi = p + q;
		r.lo = p - r.hi + q + a.lo * a.lo;
		return r;
	}

	static inline Float64x2 Dekker_Sqr(
		const Float64x2& x
	) {
		Float64x2 t = Dekker_Sqr12(x.hi);
		fp64 c = static_cast<fp64>(2.0) * x.hi * x.lo + t.lo;

		Float64x2 r;
		r.hi = t.hi + c;
		r.lo = t.hi - r.hi + c;
		return r;
	}

	static inline Float64x2 Dekker_Recip(
		const Float64x2& y
	) {
		fp64 u = 1.0 / y.hi;
		Float64x2 t = Dekker_Mul12(u, y.hi);
		fp64 l = (1.0 - t.hi - t.lo - u * y.lo) / y.hi;

		Float64x2 r;
		r.hi = u + l;
		r.lo = u - r.hi + l;
		return r;
	}

	/* Double-Single Arithmetic */

	static inline Float64x2 Dekker_Add_Float64(
		const Float64x2& x, const fp64& y
	) {
		fp64 r_hi = x.hi + y;
		fp64 r_lo = static_cast<fp64>(0.0);
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

	static inline Float64x2 Dekker_Sub_Float64(
		const Float64x2& x, const fp64& y
	) {
		fp64 r_hi = x.hi - y;
		fp64 r_lo = static_cast<fp64>(0.0);
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

	static inline Float64x2 Dekker_Mul_Float64(
		const Float64x2& x, const fp64& y
	) {
		Float64x2 t = Dekker_Mul12(x.hi, y);
		fp64 c = x.lo * y + t.lo;

		Float64x2 r;
		r.hi = t.hi + c;
		r.lo = t.hi - r.hi + c;
		return r;
	}

	static inline Float64x2 Dekker_Div_Float64(
		const Float64x2& x, const fp64& y
	) {
		Float64x2 u;
		u.hi = x.hi / y;
		Float64x2 t = Dekker_Mul12(u.hi, y);
		fp64 l = (x.hi - t.hi - t.lo + x.lo) / y;

		Float64x2 r;
		r.hi = u.hi + l;
		r.lo = u.hi - r.hi + l;
		return r;
	}

	static inline Float64x2 Float64_Div_Dekker(
		const fp64& x, const Float64x2& y
	) {
		Float64x2 u;
		u.hi = x / y.hi;
		Float64x2 t = Dekker_Mul12(u.hi, y.hi);
		fp64 l = (x - t.hi - t.lo - u.hi * y.lo) / y.hi;

		Float64x2 r;
		r.hi = u.hi + l;
		r.lo = u.hi - r.hi + l;
		return r;
	}

/* Arithmetic */

	inline Float64x2 operator+(const Float64x2 &value) const {
		return Dekker_Add(*this, value);
	}

	inline Float64x2 operator-(const Float64x2 &value) const {
		return Dekker_Sub(*this, value);
	}

	inline Float64x2 operator*(const Float64x2 &value) const {
		return Dekker_Mul(*this, value);
	}

	inline Float64x2 operator/(const Float64x2 &value) const {
		return Dekker_Div(*this, value);
	}

	inline Float64x2 operator+(const fp64 &value) const {
		return Dekker_Add_Float64(*this, value);
	}

	inline Float64x2 operator-(const fp64 &value) const {
		return Dekker_Sub_Float64(*this, value);
	}

	inline Float64x2 operator*(const fp64 &value) const {
		return Dekker_Mul_Float64(*this, value);
	}

	inline Float64x2 operator/(const fp64 &value) const {
		return Dekker_Div_Float64(*this, value);
	}

	inline constexpr Float64x2 operator-() const {
		return {-this->hi, -this->lo};
	}

/* Increment/Decrement */

	inline Float64x2& operator++() {
		*this = Dekker_Add(*this, static_cast<Float64x2>(1.0));
		return *this;
	}

	inline Float64x2& operator--() {
		*this = Dekker_Sub(*this, static_cast<Float64x2>(1.0));
		return *this;
	}

	inline Float64x2 operator++(int) {
		Float64x2 temp = *this;
		*this = Dekker_Add(*this, static_cast<Float64x2>(1.0));
		return temp;
	}

	inline Float64x2 operator--(int) {
		Float64x2 temp = *this;
		*this = Dekker_Sub(*this, static_cast<Float64x2>(1.0));
		return temp;
	}

/* Compound Assignment */

	inline Float64x2& operator+=(const Float64x2 &value) {
		*this = Dekker_Add(*this, value);
		return *this;
	}

	inline Float64x2& operator-=(const Float64x2 &value) {
		*this = Dekker_Sub(*this, value);
		return *this;
	}

	inline Float64x2& operator*=(const Float64x2 &value) {
		*this = Dekker_Mul(*this, value);
		return *this;
	}

	inline Float64x2& operator/=(const Float64x2 &value) {
		*this = Dekker_Div(*this, value);
		return *this;
	}

/* Double-Single Compound Assignment */

	inline Float64x2& operator+=(const fp64 &value) {
		*this = Dekker_Add_Float64(*this, value);
		return *this;
	}

	inline Float64x2& operator-=(const fp64 &value) {
		*this = Dekker_Sub_Float64(*this, value);
		return *this;
	}

	inline Float64x2& operator*=(const fp64 &value) {
		*this = Dekker_Mul_Float64(*this, value);
		return *this;
	}

	inline Float64x2& operator/=(const fp64 &value) {
		*this = Dekker_Div_Float64(*this, value);
		return *this;
	}

/* Comparison */

	inline bool operator==(const Float64x2 &value) const {
		return (
			this->hi == value.hi &&
			this->lo == value.lo
		) ? true : false;
	}
	inline bool operator!=(const Float64x2 &value) const {
		return (
			this->hi != value.hi ||
			this->lo != value.lo
		) ? true : false;
	}

	inline bool operator<(const Float64x2 &value) const {
		if (this->hi == value.hi) {
			return (this->lo < value.lo);
		}
		return (this->hi < value.hi);
	}

	inline bool operator<=(const Float64x2 &value) const {
		if (this->hi == value.hi) {
			return (this->lo <= value.lo);
		}
		return (this->hi < value.hi);
	}

	inline bool operator>(const Float64x2 &value) const {
		if (this->hi == value.hi) {
			return (this->lo > value.lo);
		}
		return (this->hi > value.hi);
	}

	inline bool operator>=(const Float64x2 &value) const {
		if (this->hi == value.hi) {
			return (this->lo >= value.lo);
		}
		return (this->hi > value.hi);
	}

/* Constructors */

	constexpr inline Float64x2() : hi(), lo() {}

	constexpr inline Float64x2(const fp64& value_hi, const fp64& value_lo) :
		hi(value_hi), lo(value_lo) {}

	constexpr inline Float64x2(const fp32& value) :
		hi((fp64)value), lo(0.0) {}

	constexpr inline Float64x2(const fp64& value) :
		hi(value), lo(0.0) {}

	template<typename fpX>
	constexpr inline Float64x2(const fpX& value) :
		hi((fp64)value), lo((fp64)(value - (fpX)this->hi)) {}

/* Casts */

	constexpr inline operator fp32() const {
		return (fp32)this->hi;
	}
	constexpr inline operator fp64() const {
		return this->hi;
	}

	template<typename fpX>
	constexpr inline operator fpX() const {
		return (fpX)this->hi + (fpX)this->lo;
	}

};
#endif

//------------------------------------------------------------------------------
// Float64x2 Operator Overloads
//------------------------------------------------------------------------------


// #if __cplusplus >= 201304L
// 	#define FLOAT64X2_RELAXED_CONSTEXPR constexpr
// #else
// 	#define FLOAT64X2_RELAXED_CONSTEXPR
// #endif

/* Basic Arithmetic */

inline Float64x2 operator+(const Float64x2& x, const Float64x2& y) {
	return Float64x2_add(x, y);
}
inline Float64x2 operator-(const Float64x2& x, const Float64x2& y) {
	return Float64x2_sub(x, y);
}
inline Float64x2 operator*(const Float64x2& x, const Float64x2& y) {
	return Float64x2_mul(x, y);
}
inline Float64x2 operator/(const Float64x2& x, const Float64x2& y) {
	return Float64x2_div(x, y);
}

constexpr inline Float64x2 operator-(const Float64x2& x) {
	return {-x.hi, -x.lo};
}

/* Optimized Arithmetic */

inline Float64x2 operator+(const Float64x2& x, const fp64 y) {
	return Float64x2_add_dx2_d(x, y);
}
inline Float64x2 operator-(const Float64x2& x, const fp64 y) {
	return Float64x2_sub_dx2_d(x, y);
}
inline Float64x2 operator*(const Float64x2& x, const fp64 y) {
	return Float64x2_mul_dx2_d(x, y);
}
inline Float64x2 operator/(const Float64x2& x, const fp64 y) {
	return Float64x2_div_dx2_d(x, y);
}

inline Float64x2 operator+(const fp64 x, const Float64x2& y) {
	return Float64x2_add_d_dx2(x, y);
}
inline Float64x2 operator-(const fp64 x, const Float64x2& y) {
	return Float64x2_sub_d_dx2(x, y);
}
inline Float64x2 operator*(const fp64 x, const Float64x2& y) {
	return Float64x2_mul_d_dx2(x, y);
}
inline Float64x2 operator/(const fp64 x, const Float64x2& y) {
	return Float64x2_div_d_dx2(x, y);
}

/* Comparison */

inline Float64x2 operator==(const Float64x2& x, const Float64x2& y) {
	return Float64x2_cmpeq(x, y);
}
inline Float64x2 operator!=(const Float64x2& x, const Float64x2& y) {
	return Float64x2_cmpneq(x, y);
}
inline Float64x2 operator<(const Float64x2& x, const Float64x2& y) {
	return Float64x2_cmplt(x, y);
}
inline Float64x2 operator<=(const Float64x2& x, const Float64x2& y) {
	return Float64x2_cmple(x, y);
}
inline Float64x2 operator>(const Float64x2& x, const Float64x2& y) {
	return Float64x2_cmpgt(x, y);
}
inline Float64x2 operator>=(const Float64x2& x, const Float64x2& y) {
	return Float64x2_cmpge(x, y);
}

/* Optimized Comparison */

inline Float64x2 operator==(const Float64x2& x, const fp64 y) {
	return Float64x2_cmpeq_dx2_d(x, y);
}
inline Float64x2 operator!=(const Float64x2& x, const fp64 y) {
	return Float64x2_cmpneq_dx2_d(x, y);
}
inline Float64x2 operator<(const Float64x2& x, const fp64 y) {
	return Float64x2_cmplt_dx2_d(x, y);
}
inline Float64x2 operator<=(const Float64x2& x, const fp64 y) {
	return Float64x2_cmple_dx2_d(x, y);
}
inline Float64x2 operator>(const Float64x2& x, const fp64 y) {
	return Float64x2_cmpgt_dx2_d(x, y);
}
inline Float64x2 operator>=(const Float64x2& x, const fp64 y) {
	return Float64x2_cmpge_dx2_d(x, y);
}

inline Float64x2 operator==(const fp64 x, const Float64x2& y) {
	return Float64x2_cmpeq_d_dx2(x, y);
}
inline Float64x2 operator!=(const fp64 x, const Float64x2& y) {
	return Float64x2_cmpneq_d_dx2(x, y);
}
inline Float64x2 operator<(const fp64 x, const Float64x2& y) {
	return Float64x2_cmplt_d_dx2(x, y);
}
inline Float64x2 operator<=(const fp64 x, const Float64x2& y) {
	return Float64x2_cmple_d_dx2(x, y);
}
inline Float64x2 operator>(const fp64 x, const Float64x2& y) {
	return Float64x2_cmpgt_d_dx2(x, y);
}
inline Float64x2 operator>=(const fp64 x, const Float64x2& y) {
	return Float64x2_cmpge_d_dx2(x, y);
}

/* Compound Assignment */

inline Float64x2& operator+=(Float64x2 &x, const Float64x2 &y) {
	x = Float64x2_add(x, y);
	return x;
}

inline Float64x2& operator-=(Float64x2 &x, const Float64x2 &y) {
	x = Float64x2_sub(x, y);
	return x;
}

inline Float64x2& operator*=(Float64x2 &x, const Float64x2 &y) {
	x = Float64x2_mul(x, y);
	return x;
}

inline Float64x2& operator/=(Float64x2 &x, const Float64x2 &y) {
	x = Float64x2_div(x, y);
	return x;
}

inline Float64x2& operator+=(Float64x2 &x, const fp64 y) {
	x = Float64x2_add_dx2_d(x, y);
	return x;
}

inline Float64x2& operator-=(Float64x2 &x, const fp64 y) {
	x = Float64x2_sub_dx2_d(x, y);
	return x;
}

inline Float64x2& operator*=(Float64x2 &x, const fp64 y) {
	x = Float64x2_mul_dx2_d(x, y);
	return x;
}

inline Float64x2& operator/=(Float64x2 &x, const fp64 y) {
	Float64x2_div_dx2_d(x, y);
	return x;
}

/* Increment/Decrement */

inline Float64x2& operator++(Float64x2& x) {
	Float64x2_add_dx2_d(x, 1.0);
	return x;
}

inline Float64x2& operator--(Float64x2& x) {
	Float64x2_sub_dx2_d(x, 1.0);
	return x;
}

inline Float64x2 operator++(Float64x2& x, int) {
	Float64x2 temp = x;
	x = Float64x2_add_dx2_d(x, 1.0);
	return temp;
}

inline Float64x2 operator--(Float64x2& x, int) {
	Float64x2 temp = x;
	x = Float64x2_sub_dx2_d(x, 1.0);
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
		inline static constexpr Float64x2 lowest() { return -max(); };
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

/* C Style Limits */

	#define FLOAT64X2_MAX std::numeric_limits<Float64x2>::max()
	#define FLOAT64X2_MIN std::numeric_limits<Float64x2>::min()
	#define FLOAT64X2_EPSILON std::numeric_limits<Float64x2>::epsilon()
	#define FLOAT64X2_DENORM_MIN std::numeric_limits<Float64x2>::denorm_min()
	#define FLOAT64X2_MANT_DIG std::numeric_limits<Float64x2>::digits
	#define FLOAT64X2_MIN_EXP std::numeric_limits<Float64x2>::min_exponent
	#define FLOAT64X2_MAX_EXP std::numeric_limits<Float64x2>::max_exponent
	#define FLOAT64X2_DIG std::numeric_limits<Float64x2>::digits10
	#define FLOAT64X2_MIN_10_EXP std::numeric_limits<Float64x2>::min_exponent10
	#define FLOAT64X2_MAX_10_EXP std::numeric_limits<Float64x2>::max_exponent10
	#define FLOAT64X2_DECIMAL_DIG std::numeric_limits<Float64x2>::max_digits10

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

typedef Float64x2 fp64x2;

	/* Arithmetic */

	inline fp64x2 fmax(fp64x2 x, fp64x2 y) {
		return (x > y) ? x : y;
	}
	// inline fp64x2 fmax(fp64x2 x, fp64x2 y, fp64x2 z) {
	// 	return (x > y) ?
	// 	((x > z) ? x : z) :
	// 	((y > z) ? y : z);
	// }
	inline fp64x2 fmin(fp64x2 x, fp64x2 y) {
		return (x < y) ? x : y;
	}
	// inline fp64x2 fmin(fp64x2 x, fp64x2 y, fp64x2 z) {
	// 	return (x < y) ?
	// 	((x < z) ? x : z) :
	// 	((y < z) ? y : z);
	// }
	inline fp64x2 fabs(fp64x2 x) {
		return (x < static_cast<fp64x2>(0.0)) ? -x : x;
	}
	inline fp64x2 fdim(fp64x2 x, fp64x2 y) {
		return (x > y) ? (x - y) : static_cast<fp64x2>(0.0);
	}
	inline fp64x2 fma(fp64x2 x, fp64x2 y, fp64x2 z) {
		return (x * y) + z;
	}
	inline fp64x2 copysign(fp64x2 x, fp64x2 y) {
		return (
			(x.hi < static_cast<fp64>(0.0)) != (y.hi < static_cast<fp64>(0.0))
		) ? -x : x;
	}
	/** @note This function name may change to square() or etc */
	inline fp64x2 sqr(fp64x2 x) {
		return Float64x2_square(x);
	}
	inline fp64x2 sqrt(fp64x2 x) {
		if (x == static_cast<fp64x2>(0.0)) {
			return x;
		}
		fp64x2 guess = (fp64x2)sqrt(x.hi);
		return (guess + x / guess) * static_cast<fp64>(0.5);
	}
	inline fp64x2 cbrt(fp64x2 x) {
		if (x == static_cast<fp64x2>(0.0)) {
			return x;
		}
		fp64x2 guess = (fp64x2)cbrt(x.hi);
		return (
			guess * static_cast<fp64>(2.0) + (x) / Float64x2_square(guess)
		) / static_cast<fp64>(3.0);
	}
	inline fp64x2 hypot(fp64x2 x, fp64x2 y) {
		return sqrt(
			Float64x2_square(x) + Float64x2_square(y)
		);
	}
	// inline fp64x2 hypot(fp64x2 x, fp64x2 y, fp64x2 z) {
	// 	return sqrt(
	// 		Float64x2_square(x) + Float64x2_square(y) + Float64x2_square(z)
	// 	);
	// }

	/* Trigonometry */

		fp64x2  sin (fp64x2 x);
		fp64x2  cos (fp64x2 x);
		fp64x2  tan (fp64x2 x);
		fp64x2 asin (fp64x2 x);
		fp64x2 acos (fp64x2 x);
		fp64x2 atan (fp64x2 x);
		fp64x2  sinh(fp64x2 x);
		fp64x2  cosh(fp64x2 x);
		fp64x2  tanh(fp64x2 x);
		fp64x2 asinh(fp64x2 x);
		fp64x2 acosh(fp64x2 x);
		fp64x2 atanh(fp64x2 x);
		fp64x2 atan2(fp64x2 y, fp64x2 x);
		void sincos  (const Float64x2& a, Float64x2& s, Float64x2& c);
		void sinhcosh(const Float64x2& a, Float64x2& s, Float64x2& c);

	/* Logarithms and Exponents */

		fp64x2 log (fp64x2 x);
		inline fp64x2 log1p(fp64x2 x) {
			return log(x + static_cast<fp64>(1.0));
		}
		inline fp64x2 log2(fp64x2 x) {
			return log(x) * Float64x2_log2e;
		}
		inline fp64x2 log10(fp64x2 x) {
			return log(x) * Float64x2_log10e;
		}
		inline fp64x2 logb(fp64x2 x) { return logb(x.hi + x.lo); }

		fp64x2 exp(fp64x2 x);
		inline fp64x2 expm1(fp64x2 x) {
			return log(x) - static_cast<fp64>(1.0);
		}
		inline fp64x2 exp2(fp64x2 x) {
			return exp(x * Float64x2_ln2);
		}
		inline fp64x2 exp10(fp64x2 x) {
			return exp(x * Float64x2_ln10);
		}

		inline fp64x2 pow(fp64x2 x, fp64x2 y) {
			return exp(y * log(x));
		}

	/* Tests */

	inline bool signbit(fp64x2 x) {
		return (x.hi < 0.0) ? true : false;
	}
	/** Returns true if both x.hi and x.lo are finite */
	inline bool isfinite(fp64x2 x) {
		return (isfinite(x.hi) && isfinite(x.lo));
	}
	/** Returns true if either x.hi or x.lo are infinite */
	inline bool isinf(fp64x2 x) {
		return (isinf(x.hi) || isinf(x.lo));
	}
	/** Returns true if either x.hi or x.lo are nan */
	inline bool isnan(fp64x2 x) {
		return (isnan(x.hi) || isnan(x.lo));
	}
	/** Returns true if both x.hi and x.lo are normal */
	inline bool isnormal(fp64x2 x) {
		return (isnormal(x.hi) && isnormal(x.lo));
	}
	/** Returns true if either {x.hi, y.hi} or {x.lo, y.lo} are unordered */
	inline bool isunordered(fp64x2 x, fp64x2 y) {
		return (isunordered(x.hi, y.hi) || isunordered(x.lo, y.lo));
	}
	inline int fpclassify(fp64x2 x) {
		if (isfinite(x)) { return FP_INFINITE; }
		if (isnan(x)) { return FP_NAN; }
		if (x == static_cast<fp64x2>(0.0)) { return FP_ZERO; }
		if (isnormal(x)) { return FP_NORMAL; }
		return FP_SUBNORMAL;
	}

	/* Comparison */

	inline bool isgreater(fp64x2 x, fp64x2 y) {
		return (x > y);
	}
	inline bool isgreaterequal(fp64x2 x, fp64x2 y) {
		return (x >= y);
	}
	inline bool isless(fp64x2 x, fp64x2 y) {
		return (x < y);
	}
	inline bool islessequal(fp64x2 x, fp64x2 y) {
		return (x <= y);
	}
	inline bool islessgreater(fp64x2 x, fp64x2 y) {
		return (x < y) || (x > y);
	}
	
	/* Rounding */

	inline fp64x2 trunc(fp64x2 x) {
		fp64x2 int_hi = trunc(x.hi);
		fp64x2 int_lo = trunc(x.lo);
		fp64 frac_hi = x.hi - int_hi.hi;
		fp64 frac_lo = x.lo - int_lo.hi;
		// Sum in increasing order
		fp64x2 trunc_all = static_cast<fp64x2>(0.0);
		trunc_all += (
			(fp64x2)frac_hi + (fp64x2)frac_lo >= static_cast<fp64x2>(1.0)
		) ? static_cast<fp64x2>(1.0) : static_cast<fp64x2>(0.0);
		trunc_all += int_lo;
		trunc_all += int_hi;
		return trunc_all;
	}
	inline fp64x2 floor(fp64x2 x) {
		fp64x2 int_part = trunc(x);
		return (
			x < static_cast<fp64x2>(0.0) && int_part != x
		) ? int_part - static_cast<fp64x2>(1.0) : int_part;
	}
	inline fp64x2 ceil(fp64x2 x) {
		fp64x2 int_part = trunc(x);
		return (
			x > static_cast<fp64x2>(0.0) && int_part != x
		) ? int_part + static_cast<fp64x2>(1.0) : int_part;
	}
	inline fp64x2 round(fp64x2 x) {
		fp64x2 int_part = trunc(x);
		fp64x2 frac_part = x - int_part;
		if (x >= static_cast<fp64x2>(0.0)) {
			if (frac_part >= static_cast<fp64x2>(0.5)) {
				return int_part + static_cast<fp64x2>(1.0);
			}
			return int_part;
		}
		if (frac_part <= static_cast<fp64x2>(-0.5)) {
			return int_part - static_cast<fp64x2>(1.0);
		}
		return int_part;
	}
	inline fp64x2 rint(fp64x2 x) {
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
	inline long lround(fp64x2 x) {
		return (long)round(x);
	}
	inline long lrint(fp64x2 x) {
		return (long)rint(x);
	}
	inline long long llround(fp64x2 x) {
		return (long long)round(x);
	}
	inline long long llrint(fp64x2 x) {
		return (long long)rint(x);
	}

	/* Integer and Remainder */

	inline fp64x2 fmod(fp64x2 x, fp64x2 y) {
		fp64x2 trunc_part = trunc(x / y);
		return x - y * trunc_part;
	}
	inline fp64x2 modf(fp64x2 x, fp64x2* int_part) {
		fp64x2 trunc_part = trunc(x);
		if (int_part != nullptr) {
			*int_part = trunc_part;
		}
		return x - trunc_part;
	}
	inline fp64x2 nearbyint(fp64x2 x) {
		return rint(x);
	}
	inline fp64x2 remainder(fp64x2 x, fp64x2 y) {
		fp64x2 round_part = round(x / y);
		return x - y * round_part;
	}
	inline fp64x2 remquo(fp64x2 x, fp64x2 y, int* quo) {
		fp64x2 q = round(x / y);
		fp64x2 r = x - y * q;
		*quo = (int)(q.hi + q.lo);
		return r;
	}
	/* Float Exponents */
	/** @brief ilogb(x.hi) */
	inline int ilogb(fp64x2 x) {
		return ilogb(x.hi);
	}
	/** @brief frexp(x.hi, exp) */
	inline fp64x2 frexp(fp64x2 x, int* exp) {
		return frexp(x.hi, exp);
	}
	inline fp64x2 ldexp(fp64x2 x, int exp) {
		x.hi = ldexp(x.hi, exp);
		x.lo = isfinite(x.hi) ? ldexp(x.lo, exp) : x.hi;
		return x;
	}
	inline fp64x2 scalbn(fp64x2 x, int exp) {
		x.hi = scalbn(x.hi, exp);
		x.lo = isfinite(x.hi) ? scalbn(x.lo, exp) : x.hi;
		return x;
	}
	inline fp64x2 scalbln(fp64x2 x, long exp) {
		x.hi = scalbln(x.hi, exp);
		x.lo = isfinite(x.hi) ? scalbln(x.lo, exp) : x.hi;
		return x;
	}

/* Math overloads (Casts to other types) */

		/* Arithmetic */
		// inline fp64x2 fmax(fp64x2 x, fp64x2 y) { return (fp64x2)fmax((fp64x2_Math)x, (fp64x2_Math)y); }
		// inline fp64x2 fmin(fp64x2 x, fp64x2 y) { return (fp64x2)fmin((fp64x2_Math)x, (fp64x2_Math)y); }
		// inline fp64x2 fabs(fp64x2 x) { return (fp64x2)fabs((fp64x2_Math)x); }
		// inline fp64x2 fdim(fp64x2 x, fp64x2 y) { return (fp64x2)fdim((fp64x2_Math)x, (fp64x2_Math)y); }
		// inline fp64x2 fma(fp64x2 x, fp64x2 y, fp64x2 z) { return (fp64x2)fma((fp64x2_Math)x, (fp64x2_Math)y, (fp64x2_Math)z); }
		// inline fp64x2 copysign(fp64x2 x, fp64x2 y) { return (fp64x2)copysign((fp64x2_Math)x, (fp64x2_Math)y); }
		// inline fp64x2 sqrt(fp64x2 x) { return (fp64x2)sqrt((fp64x2_Math)x); }
		// inline fp64x2 cbrt(fp64x2 x) { return (fp64x2)cbrt((fp64x2_Math)x); }
		// inline fp64x2 hypot(fp64x2 x, fp64x2 y) { return (fp64x2)hypot((fp64x2_Math)x, (fp64x2_Math)y); }
		/* Trigonometry */
		// inline fp64x2  sin (fp64x2 x) { return (fp64x2) sin ((fp64x2_Math)x); }
		// inline fp64x2  cos (fp64x2 x) { return (fp64x2) cos ((fp64x2_Math)x); }
		// inline fp64x2  tan (fp64x2 x) { return (fp64x2) tan ((fp64x2_Math)x); }
		// inline fp64x2 asin (fp64x2 x) { return (fp64x2)asin ((fp64x2_Math)x); }
		// inline fp64x2 acos (fp64x2 x) { return (fp64x2)acos ((fp64x2_Math)x); }
		// inline fp64x2 atan (fp64x2 x) { return (fp64x2)atan ((fp64x2_Math)x); }
		// inline fp64x2  sinh(fp64x2 x) { return (fp64x2) sinh((fp64x2_Math)x); }
		// inline fp64x2  cosh(fp64x2 x) { return (fp64x2) cosh((fp64x2_Math)x); }
		// inline fp64x2  tanh(fp64x2 x) { return (fp64x2) tanh((fp64x2_Math)x); }
		// inline fp64x2 asinh(fp64x2 x) { return (fp64x2)asinh((fp64x2_Math)x); }
		// inline fp64x2 acosh(fp64x2 x) { return (fp64x2)acosh((fp64x2_Math)x); }
		// inline fp64x2 atanh(fp64x2 x) { return (fp64x2)atanh((fp64x2_Math)x); }
		// inline fp64x2 atan2(fp64x2 y, fp64x2 x) { return (fp64x2)atan2((fp64x2_Math)y, (fp64x2_Math)x); }
		// inline void sincos(fp64x2 x, fp64x2* p_sin, fp64x2* p_cos) {
		// 	*p_sin = sin(x);
		// 	*p_cos = cos(x);
		// }
		/* Logarithms and Exponents */
		// inline fp64x2 log  (fp64x2 x) { return (fp64x2)log  ((fp64x2_Math)x); }
		// inline fp64x2 log1p(fp64x2 x) { return (fp64x2)log1p((fp64x2_Math)x); }
		// inline fp64x2 logb (fp64x2 x) { return (fp64x2)logb ((fp64x2_Math)x); }
		// inline fp64x2 log2 (fp64x2 x) { return (fp64x2)log2 ((fp64x2_Math)x); }
		// inline fp64x2 log10(fp64x2 x) { return (fp64x2)log10((fp64x2_Math)x); }
		// inline fp64x2 exp  (fp64x2 x) { return (fp64x2)exp  ((fp64x2_Math)x); }
		// inline fp64x2 expm1(fp64x2 x) { return (fp64x2)expm1((fp64x2_Math)x); }
		// inline fp64x2 exp2 (fp64x2 x) { return (fp64x2)exp2 ((fp64x2_Math)x); }
		// inline fp64x2 pow(fp64x2 x, fp64x2 y) { return (fp64x2)pow((fp64x2_Math)x, (fp64x2_Math)y); }
		/* Rounding */
		// inline fp64x2 trunc(fp64x2 x) { return (fp64x2)trunc((fp64x2_Math)x); }
		// inline fp64x2 floor(fp64x2 x) { return (fp64x2)floor((fp64x2_Math)x); }
		// inline fp64x2 ceil (fp64x2 x) { return (fp64x2)ceil ((fp64x2_Math)x); }
		// inline fp64x2 rint (fp64x2 x) { return (fp64x2)rint ((fp64x2_Math)x); }
		// inline fp64x2 round(fp64x2 x) { return (fp64x2)round((fp64x2_Math)x); }
		// inline long lrint (fp64x2 x) { return lrint ((fp64x2_Math)x); }
		// inline long lround(fp64x2 x) { return lround((fp64x2_Math)x); }
		// inline long long llrint (fp64x2 x) { return llrint ((fp64x2_Math)x); }
		// inline long long llround(fp64x2 x) { return llround((fp64x2_Math)x); }
		/* Integer and Remainder */
		// inline fp64x2 fmod(fp64x2 x, fp64x2 y) { return (fp64x2)fmod((fp64x2_Math)x, (fp64x2_Math)y); }
		// inline fp64x2 modf(fp64x2 x, fp64x2* y) {
		// 	fp64x2_Math y_temp;
		// 	fp64x2 result = modf((fp64x2_Math)x, &y_temp);
		// 	*y = (fp64x2)y_temp;
		// 	return result;
		// }
		// inline fp64x2 nearbyint(fp64x2 x) { return (fp64x2)nearbyint((fp64x2_Math)x); }
		// Incorrect Function // inline fp64x2 nextafter(fp64x2 x, fp64x2 y) { return (fp64x2)nextafter((fp64x2_Math)x, (fp64x2_Math)y); }
		// inline fp64x2 remainder(fp64x2 x, fp64x2 y) { return (fp64x2)remainder((fp64x2_Math)x, (fp64x2_Math)y); }
		// inline fp64x2 remquo(fp64x2 x, fp64x2 y, int* quo) { return (fp64x2)remquo((fp64x2_Math)x, (fp64x2_Math)y, quo); }
		/* Float Exponents */
		// inline int ilogb(fp64x2 x) { return ilogb((fp64x2_Math)x); }
		// inline fp64x2 frexp  (fp64x2 x, int* exp) { return (fp64x2)frexp  ((fp64x2_Math)x, exp); }
		// inline fp64x2 ldexp  (fp64x2 x, int  exp) { return (fp64x2)ldexp  ((fp64x2_Math)x, exp); }
		// inline fp64x2 scalbn (fp64x2 x, int  exp) { return (fp64x2)scalbn ((fp64x2_Math)x, exp); }
		// inline fp64x2 scalbln(fp64x2 x, long exp) { return (fp64x2)scalbln((fp64x2_Math)x, exp); }
		/* Tests */
		// inline bool signbit(fp64x2 x) { return (signbit((fp64x2_Math)x) != 0) ? true : false; }
		// inline bool isfinite(fp64x2 x) { return (isfinite((fp64x2_Math)x) != 0) ? true : false; }
		// inline bool isinf(fp64x2 x) { return (isinf((fp64x2_Math)x) != 0) ? true : false; }
		// inline bool isnan(fp64x2 x) { return (isnan((fp64x2_Math)x) != 0) ? true : false; }
		/* Transcendental Functions */
		// inline fp64x2 erf (fp64x2 x) { return (fp64x2)erf ((fp64x2_Math)x); }
		// inline fp64x2 erfc(fp64x2 x) { return (fp64x2)erfc((fp64x2_Math)x); }
		// inline fp64x2 lgamma(fp64x2 x) { return (fp64x2)lgamma((fp64x2_Math)x); }
		// inline fp64x2 tgamma(fp64x2 x) { return (fp64x2)tgamma((fp64x2_Math)x); }

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
