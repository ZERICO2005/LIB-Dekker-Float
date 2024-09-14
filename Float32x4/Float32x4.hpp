/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/
#ifndef FLOAT32X4_HPP
#define FLOAT32X4_HPP

#include "Float32x4_def.h"

#include <cstdint>
#include <cmath>

#include "../LDF/LDF_arithmetic.hpp"

/**
 * @note Float32x4 is currently unimplemented.
 */

//------------------------------------------------------------------------------
// Float32x4 LDF Type Information
//------------------------------------------------------------------------------

#include "../LDF/LDF_type_info.hpp"
namespace LDF {
	template<> struct LDF_Type_Info<Float32x4> {
		static constexpr int FloatBase_Count = 4;
		static constexpr bool to_string_implemented = false;
		static constexpr bool from_string_implemented = false;
		static constexpr bool arithmetic_implemented = false;
		static constexpr bool numeric_limits_implemented = false;
		static constexpr bool bitwise_implemented = true;
		static constexpr bool constants_implemented = true;
		static constexpr bool basic_C99_math_implemented = false;
		static constexpr bool accurate_C99_math_implemented = false;
	};
}

//------------------------------------------------------------------------------
// Float32x4 Compairison
//------------------------------------------------------------------------------

inline constexpr bool operator==(const Float32x4& x, const Float32x4& y) {
	return (
		x.val[0] == y.val[0] && x.val[1] == y.val[1] &&
		x.val[2] == y.val[2] && x.val[3] == y.val[3]
	);
}
inline constexpr bool operator!=(const Float32x4& x, const Float32x4& y) {
	return (
		x.val[0] != y.val[0] || x.val[1] != y.val[1] ||
		x.val[2] != y.val[2] || x.val[3] != y.val[3]
	);
}
inline constexpr bool operator<(const Float32x4& x, const Float32x4& y) {
	return
		(x.val[0] == y.val[0]) ? (
			(x.val[1] == y.val[1]) ? (
				(x.val[2] == y.val[2]) ? (
					x.val[3] < y.val[3]
				) : (x.val[2] < y.val[2])
			) : (x.val[1] < y.val[1])
		) : (x.val[0] < y.val[0]);
}
inline constexpr bool operator<=(const Float32x4& x, const Float32x4& y) {
	return
		(x.val[0] == y.val[0]) ? (
			(x.val[1] == y.val[1]) ? (
				(x.val[2] == y.val[2]) ? (
					x.val[3] <= y.val[3]
				) : (x.val[2] < y.val[2])
			) : (x.val[1] < y.val[1])
		) : (x.val[0] < y.val[0]);
}
inline constexpr bool operator>(const Float32x4& x, const Float32x4& y) {
	return
		(x.val[0] == y.val[0]) ? (
			(x.val[1] == y.val[1]) ? (
				(x.val[2] == y.val[2]) ? (
					x.val[3] > y.val[3]
				) : (x.val[2] > y.val[2])
			) : (x.val[1] > y.val[1])
		) : (x.val[0] > y.val[0]);
}
inline constexpr bool operator>=(const Float32x4& x, const Float32x4& y) {
	return
		(x.val[0] == y.val[0]) ? (
			(x.val[1] == y.val[1]) ? (
				(x.val[2] == y.val[2]) ? (
					x.val[3] >= y.val[3]
				) : (x.val[2] > y.val[2])
			) : (x.val[1] > y.val[1])
		) : (x.val[0] > y.val[0]);
}

//------------------------------------------------------------------------------
// Float32x4 Compare to Zero
//------------------------------------------------------------------------------

/** @brief Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero */
inline constexpr bool isequal_zero(const Float32x4& x) {
	return (x.val[0] == 0.0);
}
/** @brief Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero */
inline constexpr bool isnotequal_zero(const Float32x4& x) {
	return (x.val[0] != 0.0);
}
/** @brief Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero */
inline constexpr bool isless_zero(const Float32x4& x) {
	return (x.val[0] < 0.0);
}
/** @brief Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero */
inline constexpr bool islessequal_zero(const Float32x4& x) {
	return (x.val[0] <= 0.0);
}
/** @brief Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero */
inline constexpr bool isgreater_zero(const Float32x4& x) {
	return (x.val[0] > 0.0);
}
/** @brief Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero */
inline constexpr bool isgreaterequal_zero(const Float32x4& x) {
	return (x.val[0] >= 0.0);
}

//------------------------------------------------------------------------------
// Float32x4 specialized arithmetic
//------------------------------------------------------------------------------

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero
 */
template <> inline constexpr
Float32x4 LDF::mul_pwr2<Float32x4, Float32x4, fp32>
(const Float32x4& x, const fp32& y) {
	return {
		x.val[0] * y,
		x.val[1] * y,
		x.val[2] * y,
		x.val[3] * y
	};
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero
 */
template <> inline constexpr
Float32x4 LDF::mul_pwr2<Float32x4, fp32, Float32x4>
(const fp32& x, const Float32x4& y) {
	return {
		x * y.val[0],
		x * y.val[1],
		x * y.val[2],
		x * y.val[3]
	};
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero.
 * The result is stored as a Float32x4
 */
template <> inline constexpr
Float32x4 LDF::mul_pwr2<Float32x4, fp32, fp32>
(const fp32& x, const fp32& y) {
	return {
		x * y,
		static_cast<fp32>(0.0),
		static_cast<fp32>(0.0),
		static_cast<fp32>(0.0)
	};
}

//------------------------------------------------------------------------------
// Float32x4 Basic Arithmetic
//------------------------------------------------------------------------------

/* Negation */

inline constexpr Float32x4 operator-(const Float32x4& x) {
	return {-x.val[0], -x.val[1], -x.val[2], -x.val[3]};
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero
 */
inline constexpr Float32x4 mul_pwr2(const Float32x4& x, const fp32 y) {
	return LDF::mul_pwr2<Float32x4, Float32x4, fp32>(x, y);
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero
 */
inline constexpr Float32x4 mul_pwr2(const fp32 x, const Float32x4& y) {
	return LDF::mul_pwr2<Float32x4, fp32, Float32x4>(x, y);
}

//------------------------------------------------------------------------------
// Float32x4 bitwise operators
//------------------------------------------------------------------------------

template <> inline
Float32x4 LDF::bitwise_not<Float32x4>
(const Float32x4& x) {
	Float32x4 ret = x;
	uint32_t* binary_part = reinterpret_cast<uint32_t*>(&ret);
	binary_part[0] = ~binary_part[0];
	binary_part[1] = ~binary_part[1];
	binary_part[2] = ~binary_part[2];
	binary_part[3] = ~binary_part[3];
	return ret;
}

template <> inline
Float32x4 LDF::bitwise_and<Float32x4, Float32x4>
(const Float32x4& x, const Float32x4& y) {
	Float32x4 ret = x;
	uint32_t* ret_bin = reinterpret_cast<uint32_t*>(&ret);
	const uint32_t* y_bin = reinterpret_cast<const uint32_t*>(&y);
	ret_bin[0] &= y_bin[0];
	ret_bin[1] &= y_bin[1];
	ret_bin[2] &= y_bin[2];
	ret_bin[3] &= y_bin[3];
	return ret;
}

template <> inline
Float32x4 LDF::bitwise_andnot<Float32x4, Float32x4>
(const Float32x4& x, const Float32x4& y) {
	Float32x4 ret = x;
	uint32_t* ret_bin = reinterpret_cast<uint32_t*>(&ret);
	const uint32_t* y_bin = reinterpret_cast<const uint32_t*>(&y);
	ret_bin[0] &= ~y_bin[0];
	ret_bin[1] &= ~y_bin[1];
	ret_bin[2] &= ~y_bin[2];
	ret_bin[3] &= ~y_bin[3];
	return ret;
}

template <> inline
Float32x4 LDF::bitwise_or<Float32x4, Float32x4>
(const Float32x4& x, const Float32x4& y) {
	Float32x4 ret = x;
	uint32_t* ret_bin = reinterpret_cast<uint32_t*>(&ret);
	const uint32_t* y_bin = reinterpret_cast<const uint32_t*>(&y);
	ret_bin[0] |= y_bin[0];
	ret_bin[1] |= y_bin[1];
	ret_bin[2] |= y_bin[2];
	ret_bin[3] |= y_bin[3];
	return ret;
}

template <> inline
Float32x4 LDF::bitwise_xor<Float32x4, Float32x4>
(const Float32x4& x, const Float32x4& y) {
	Float32x4 ret = x;
	uint32_t* ret_bin = reinterpret_cast<uint32_t*>(&ret);
	const uint32_t* y_bin = reinterpret_cast<const uint32_t*>(&y);
	ret_bin[0] ^= y_bin[0];
	ret_bin[1] ^= y_bin[1];
	ret_bin[2] ^= y_bin[2];
	ret_bin[3] ^= y_bin[3];
	return ret;
}

template <> inline
Float32x4 LDF::bitwise_and<Float32x4, fp32>
(const Float32x4& x, const fp32& y) {
	Float32x4 ret = x;
	uint32_t* ret_bin = reinterpret_cast<uint32_t*>(&ret);
	const uint32_t* y_bin = reinterpret_cast<const uint32_t*>(&y);
	ret_bin[0] &= *y_bin;
	ret_bin[1] &= *y_bin;
	ret_bin[2] &= *y_bin;
	ret_bin[3] &= *y_bin;
	return ret;
}

template <> inline
Float32x4 LDF::bitwise_andnot<Float32x4, fp32>
(const Float32x4& x, const fp32& y) {
	Float32x4 ret = x;
	uint32_t* ret_bin = reinterpret_cast<uint32_t*>(&ret);
	const uint32_t* y_bin = reinterpret_cast<const uint32_t*>(&y);
	ret_bin[0] &= ~(*y_bin);
	ret_bin[1] &= ~(*y_bin);
	ret_bin[2] &= ~(*y_bin);
	ret_bin[3] &= ~(*y_bin);
	return ret;
}

template <> inline
Float32x4 LDF::bitwise_or<Float32x4, fp32>
(const Float32x4& x, const fp32& y) {
	Float32x4 ret = x;
	uint32_t* ret_bin = reinterpret_cast<uint32_t*>(&ret);
	const uint32_t* y_bin = reinterpret_cast<const uint32_t*>(&y);
	ret_bin[0] |= *y_bin;
	ret_bin[1] |= *y_bin;
	ret_bin[2] |= *y_bin;
	ret_bin[3] |= *y_bin;
	return ret;
}

template <> inline
Float32x4 LDF::bitwise_xor<Float32x4, fp32>
(const Float32x4& x, const fp32& y) {
	Float32x4 ret = x;
	uint32_t* ret_bin = reinterpret_cast<uint32_t*>(&ret);
	const uint32_t* y_bin = reinterpret_cast<const uint32_t*>(&y);
	ret_bin[0] ^= *y_bin;
	ret_bin[1] ^= *y_bin;
	ret_bin[2] ^= *y_bin;
	ret_bin[3] ^= *y_bin;
	return ret;
}

//------------------------------------------------------------------------------
// Float32x4 Constants
//------------------------------------------------------------------------------

#include "Float32x4_constants.hpp"

#if __cplusplus >= 201907L
#include <numbers>
namespace std {
	namespace numbers {
		template<> inline constexpr Float32x4 e_v          <Float32x4> = LDF::const_e         <Float32x4>(); /**< ~2.718281828 */
		template<> inline constexpr Float32x4 log2e_v      <Float32x4> = LDF::const_log2e     <Float32x4>(); /**< ~1.442695041 */
		template<> inline constexpr Float32x4 log10e_v     <Float32x4> = LDF::const_log10e    <Float32x4>(); /**< ~0.434294482 */
		template<> inline constexpr Float32x4 pi_v         <Float32x4> = LDF::const_pi        <Float32x4>(); /**< ~3.141592654 */
		template<> inline constexpr Float32x4 inv_pi_v     <Float32x4> = LDF::const_inv_pi    <Float32x4>(); /**< ~0.318309886 */
		template<> inline constexpr Float32x4 inv_sqrtpi_v <Float32x4> = LDF::const_inv_sqrtpi<Float32x4>(); /**< ~0.564189584 */
		template<> inline constexpr Float32x4 ln2_v        <Float32x4> = LDF::const_ln2       <Float32x4>(); /**< ~0.693147181 */
		template<> inline constexpr Float32x4 ln10_v       <Float32x4> = LDF::const_ln10      <Float32x4>(); /**< ~2.302585093 */
		template<> inline constexpr Float32x4 sqrt2_v      <Float32x4> = LDF::const_sqrt2     <Float32x4>(); /**< ~1.414213562 */
		template<> inline constexpr Float32x4 sqrt3_v      <Float32x4> = LDF::const_sqrt3     <Float32x4>(); /**< ~1.732050808 */
		template<> inline constexpr Float32x4 inv_sqrt3_v  <Float32x4> = LDF::const_inv_sqrt3 <Float32x4>(); /**< ~0.577350269 */
		template<> inline constexpr Float32x4 egamma_v     <Float32x4> = LDF::const_egamma    <Float32x4>(); /**< ~0.577215665 */
		template<> inline constexpr Float32x4 phi_v        <Float32x4> = LDF::const_phi       <Float32x4>(); /**< ~1.618033989 */
	}
}
#endif

//------------------------------------------------------------------------------
// Float32x4 math.h functions
//------------------------------------------------------------------------------

/* Floating Point Classify */

	/** @brief Returns true if x is negative */
	inline constexpr bool signbit(const Float32x4& x) {
		return std::signbit(x.val[0]);
	}

	/** @brief Returns true if x is finite */
	inline constexpr bool isfinite(const Float32x4& x) {
		return std::isfinite(x.val[0]);
	}

	/** @brief Returns true if x is +-infinity */
	inline constexpr bool isinf(const Float32x4& x) {
		return std::isinf(x.val[0]);
	}

	/** @brief Returns true if x is any kind of NaN */
	inline constexpr bool isnan(const Float32x4& x) {
		return std::isnan(x.val[0]);
	}

	/** @brief Returns true if x is normal */
	inline constexpr bool isnormal(const Float32x4& x) {
		return (
			std::isnormal(x.val[0]) && std::isnormal(x.val[1]) &&
			std::isnormal(x.val[2]) && std::isnormal(x.val[3])
		);
	}

	/** @brief Returns true if x and y are unordered */
	inline constexpr bool isunordered(const Float32x4& x, const Float32x4& y) {
		return std::isunordered(x.val[0], y.val[0]);
	}

	inline constexpr int fpclassify(const Float32x4& x) {
		return
			isinf(x)             ? FP_INFINITE :
			isnan(x)             ? FP_NAN      :
			isequal_zero(x) ? FP_ZERO     :
			isnormal(x)          ? FP_NORMAL   :
			FP_SUBNORMAL;
	}

/* fmax and fmin */

	/**
	 * @brief Returns the fmax of x and y. Correctly handling NaN and signed zeros.
	 * You may use std::max as a faster alternative.
	 */
	inline constexpr Float32x4 fmax(const Float32x4& x, const Float32x4& y) {
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
	inline constexpr Float32x4 fmin(const Float32x4& x, const Float32x4& y) {
		return
			(x > y) ? y :
			(y > x) ? x :
			isnan(x) ? y :
			isnan(y) ? x :
			signbit(x) ? x : y;
	}

/* Arithmetic */

	inline constexpr Float32x4 fmax(const Float32x4& x, const Float32x4& y, const Float32x4& z) {
		return fmax(fmax(x, y), z);
	}
	inline constexpr Float32x4 fmin(const Float32x4& x, const Float32x4& y, const Float32x4& z) {
		return fmin(fmin(x, y), z);
	}
	inline constexpr Float32x4 fabs(const Float32x4& x) {
		return (isless_zero(x)) ? -x : x;
	}
	inline constexpr Float32x4 copysign(const Float32x4& x, const Float32x4& y) {
		return (isless_zero(x)) != (isless_zero(y)) ? -x : x;
	}

/* Comparison */

	inline constexpr bool isgreater(const Float32x4& x, const Float32x4& y) {
		return (x > y);
	}
	inline constexpr bool isgreaterequal(const Float32x4& x, const Float32x4& y) {
		return (x >= y);
	}
	inline constexpr bool isless(const Float32x4& x, const Float32x4& y) {
		return (x < y);
	}
	inline constexpr bool islessequal(const Float32x4& x, const Float32x4& y) {
		return (x <= y);
	}
	inline constexpr bool islessgreater(const Float32x4& x, const Float32x4& y) {
		return (x < y) || (x > y);
	}

#endif /* FLOAT32X4_HPP */
