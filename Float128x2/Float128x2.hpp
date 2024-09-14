/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/
#ifndef FLOAT128X2_HPP
#define FLOAT128X2_HPP

#include "Float128x2_def.h"
#include "../LDF/LDF_arithmetic.hpp"

//------------------------------------------------------------------------------
// Float128x2 LDF Type Information
//------------------------------------------------------------------------------

#include "../LDF/LDF_type_info.hpp"
namespace LDF {
	template<> struct LDF_Type_Info<Float128x2> {
		static constexpr int FloatBase_Count = 2;
		static constexpr bool to_string_implemented = false;
		static constexpr bool from_string_implemented = false;
		static constexpr bool arithmetic_implemented = false;
		static constexpr bool numeric_limits_implemented = false;
		static constexpr bool bitwise_implemented = false;
		static constexpr bool constants_implemented = true;
		static constexpr bool basic_C99_math_implemented = false;
		static constexpr bool accurate_C99_math_implemented = false;
	};
}

//------------------------------------------------------------------------------
// Float128x2 Constants
//------------------------------------------------------------------------------

#include "../Float128/Float128_constants.hpp"
#include "Float128x2_constants.hpp"

#if __cplusplus >= 201907L
#include <numbers>
namespace std {
	namespace numbers {
		template<> inline constexpr Float128x2 e_v          <Float128x2> = LDF::const_e         <Float128x2>(); /**< ~2.718281828 */
		template<> inline constexpr Float128x2 log2e_v      <Float128x2> = LDF::const_log2e     <Float128x2>(); /**< ~1.442695041 */
		template<> inline constexpr Float128x2 log10e_v     <Float128x2> = LDF::const_log10e    <Float128x2>(); /**< ~0.434294482 */
		template<> inline constexpr Float128x2 pi_v         <Float128x2> = LDF::const_pi        <Float128x2>(); /**< ~3.141592654 */
		template<> inline constexpr Float128x2 inv_pi_v     <Float128x2> = LDF::const_inv_pi    <Float128x2>(); /**< ~0.318309886 */
		template<> inline constexpr Float128x2 inv_sqrtpi_v <Float128x2> = LDF::const_inv_sqrtpi<Float128x2>(); /**< ~0.564189584 */
		template<> inline constexpr Float128x2 ln2_v        <Float128x2> = LDF::const_ln2       <Float128x2>(); /**< ~0.693147181 */
		template<> inline constexpr Float128x2 ln10_v       <Float128x2> = LDF::const_ln10      <Float128x2>(); /**< ~2.302585093 */
		template<> inline constexpr Float128x2 sqrt2_v      <Float128x2> = LDF::const_sqrt2     <Float128x2>(); /**< ~1.414213562 */
		template<> inline constexpr Float128x2 sqrt3_v      <Float128x2> = LDF::const_sqrt3     <Float128x2>(); /**< ~1.732050808 */
		template<> inline constexpr Float128x2 inv_sqrt3_v  <Float128x2> = LDF::const_inv_sqrt3 <Float128x2>(); /**< ~0.577350269 */
		template<> inline constexpr Float128x2 egamma_v     <Float128x2> = LDF::const_egamma    <Float128x2>(); /**< ~0.577215665 */
		template<> inline constexpr Float128x2 phi_v        <Float128x2> = LDF::const_phi       <Float128x2>(); /**< ~1.618033989 */
	}
}
#endif

//------------------------------------------------------------------------------
// Float128x2 specialized arithmetic
//------------------------------------------------------------------------------

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero
 */
template <> inline constexpr
Float128x2 LDF::mul_pwr2<Float128x2, Float128x2, fp128>
(const Float128x2& x, const fp128& y) {
	return {x.hi * y, x.lo * y};
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero
 */
template <> inline constexpr
Float128x2 LDF::mul_pwr2<Float128x2, fp128, Float128x2>
(const fp128& x, const Float128x2& y) {
	return {x * y.hi, x * y.hi};
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero.
 * The result is stored as a Float128x2
 */
template <> inline constexpr
Float128x2 LDF::mul_pwr2<Float128x2, fp128, fp128>
(const fp128& x, const fp128& y) {
	return {x * y, static_cast<fp128>(0.0)};
}

//------------------------------------------------------------------------------
// Float128x2 Arithmetic Operator Overloads
//------------------------------------------------------------------------------

inline constexpr Float128x2 operator-(const Float128x2& x) {
	return {-x.hi, -x.lo};
}

inline constexpr Float128x2 mul_pwr2(const Float128x2& x, const fp128 y) {
	return LDF::mul_pwr2<Float128x2, Float128x2, fp128>(x, y);
}
inline constexpr Float128x2 mul_pwr2(const fp128 x, const Float128x2& y) {
	return LDF::mul_pwr2<Float128x2, fp128, Float128x2>(x, y);
}

#endif /* FLOAT128X2_HPP */
