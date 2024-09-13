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

#include "../FloatNxN/FloatNxN_arithmetic.hpp"
#include "../FloatNxN/FloatNxN_constants.hpp"

/**
 * @note Float32x4 is currently unimplemented.
 */

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
// Float32x4 Arithmetic
//------------------------------------------------------------------------------

/* Negation */

inline constexpr Float32x4 operator-(const Float32x4& x) {
	return {-x.val[0], -x.val[1], -x.val[2], -x.val[3]};
}

//------------------------------------------------------------------------------
// Float32x4 specialized arithmetic
//------------------------------------------------------------------------------

/**
 * @brief Multiplies by a known power of two (such as 2.0f, 0.5f, etc.) or zero
 */
inline Float32x4 mul_pwr2(const Float32x4& x, const fp32 y) {
	Float32x4 ret;
	ret.val[0] = x.val[0] * y;
	ret.val[1] = x.val[1] * y;
	ret.val[2] = x.val[2] * y;
	ret.val[3] = x.val[3] * y;
	return ret;
}

/**
 * @brief Multiplies by a known power of two (such as 2.0f, 0.5f, etc.) or zero
 */
inline Float32x4 mul_pwr2(const fp32 x, const Float32x4& y) {
	Float32x4 ret;
	ret.val[0] = x * y.val[0];
	ret.val[1] = x * y.val[1];
	ret.val[2] = x * y.val[2];
	ret.val[3] = x * y.val[3];
	return ret;
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

/* C++20 <numbers> */

	constexpr Float32x4 Float32x4_e          = {0x1.5bf0a8p+1f,+0x1.628aeep-24f,-0x1.ab2a82p-49f,+0x1.c56202p-74f}; /**< ~2.718281828 */
	constexpr Float32x4 Float32x4_log2e      = {0x1.715476p+0f,+0x1.4ae0c0p-26f,-0x1.e88830p-52f,+0x1.ffb41ap-77f}; /**< ~1.442695041 */
	constexpr Float32x4 Float32x4_log10e     = {0x1.bcb7b2p-2f,-0x1.5b235ep-27f,-0x1.cd5954p-54f,-0x1.155414p-79f}; /**< ~0.434294482 */
	constexpr Float32x4 Float32x4_pi         = {0x1.921fb6p+1f,-0x1.777a5cp-24f,-0x1.ee59dap-49f,+0x1.98a2e0p-76f}; /**< ~3.141592654 */
	constexpr Float32x4 Float32x4_inv_pi     = {0x1.45f306p-2f,+0x1.b93910p-27f,+0x1.529fc2p-53f,+0x1.d5f47ep-79f}; /**< ~0.318309886 */
	constexpr Float32x4 Float32x4_inv_sqrtpi = {0x1.20dd76p-1f,-0x1.f7ac92p-26f,-0x1.7728e2p-52f,-0x1.6eb012p-77f}; /**< ~0.564189584 */
	constexpr Float32x4 Float32x4_ln2        = {0x1.62e430p-1f,-0x1.05c610p-29f,-0x1.950d88p-54f,+0x1.d9cc02p-79f}; /**< ~0.693147181 */
	constexpr Float32x4 Float32x4_ln10       = {0x1.26bb1cp+1f,-0x1.12aabap-25f,-0x1.3e915ap-50f,-0x1.253a90p-75f}; /**< ~2.302585093 */
	constexpr Float32x4 Float32x4_sqrt2      = {0x1.6a09e6p+0f,+0x1.9fcef4p-26f,-0x1.b7ba68p-51f,-0x1.3b2646p-78f}; /**< ~1.414213562 */
	constexpr Float32x4 Float32x4_sqrt3      = {0x1.bb67aep+0f,+0x1.0b0996p-25f,-0x1.63136ap-50f,-0x1.7a51f0p-77f}; /**< ~1.732050808 */
	constexpr Float32x4 Float32x4_inv_sqrt3  = {0x1.279a74p-1f,+0x1.640cc8p-27f,-0x1.d96f38p-52f,-0x1.f86d42p-79f}; /**< ~0.577350269 */
	constexpr Float32x4 Float32x4_egamma     = {0x1.2788d0p-1f,-0x1.c824f4p-28f,+0x1.e93470p-54f,-0x1.c07efep-80f}; /**< ~0.577215665 */
	constexpr Float32x4 Float32x4_phi        = {0x1.9e377ap+0f,-0x1.1a02d6p-26f,-0x1.f50632p-55f,+0x1.80c0bap-81f}; /**< ~1.618033989 */

#if __cplusplus >= 201907L
#include <numbers>
namespace std {
	namespace numbers {
		template<> inline constexpr Float32x4 e_v          <Float32x4> = Float32x4_e         ; /**< ~2.718281828 */
		template<> inline constexpr Float32x4 log2e_v      <Float32x4> = Float32x4_log2e     ; /**< ~1.442695041 */
		template<> inline constexpr Float32x4 log10e_v     <Float32x4> = Float32x4_log10e    ; /**< ~0.434294482 */
		template<> inline constexpr Float32x4 pi_v         <Float32x4> = Float32x4_pi        ; /**< ~3.141592654 */
		template<> inline constexpr Float32x4 inv_pi_v     <Float32x4> = Float32x4_inv_pi    ; /**< ~0.318309886 */
		template<> inline constexpr Float32x4 inv_sqrtpi_v <Float32x4> = Float32x4_inv_sqrtpi; /**< ~0.564189584 */
		template<> inline constexpr Float32x4 ln2_v        <Float32x4> = Float32x4_ln2       ; /**< ~0.693147181 */
		template<> inline constexpr Float32x4 ln10_v       <Float32x4> = Float32x4_ln10      ; /**< ~2.302585093 */
		template<> inline constexpr Float32x4 sqrt2_v      <Float32x4> = Float32x4_sqrt2     ; /**< ~1.414213562 */
		template<> inline constexpr Float32x4 sqrt3_v      <Float32x4> = Float32x4_sqrt3     ; /**< ~1.732050808 */
		template<> inline constexpr Float32x4 inv_sqrt3_v  <Float32x4> = Float32x4_inv_sqrt3 ; /**< ~0.577350269 */
		template<> inline constexpr Float32x4 egamma_v     <Float32x4> = Float32x4_egamma    ; /**< ~0.577215665 */
		template<> inline constexpr Float32x4 phi_v        <Float32x4> = Float32x4_phi       ; /**< ~1.618033989 */
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
