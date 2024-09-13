/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/
#ifndef FLOAT128X2_HPP
#define FLOAT128X2_HPP

#include "Float128.hpp"
#include "Float128x2_def.h"
#include "../FloatNxN/FloatNxN_constants.hpp"

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

/* C++20 <numbers> */

	constexpr Float128x2 Float128x2_e          = {0x1.5bf0a8b1457695355fb8ac404e7ap+1Q,+0x1.e78ec5ce2c1e7169b4ad4f09b209p-113Q}; /**< ~2.718281828 */
	constexpr Float128x2 Float128x2_log2e      = {0x1.71547652b82fe1777d0ffda0d23ap+0Q,+0x1.f4475abbd546eb4ad2c45928b367p-114Q}; /**< ~1.442695041 */
	constexpr Float128x2 Float128x2_log10e     = {0x1.bcb7b1526e50e32a6ab7555f5a68p-2Q,-0x1.1e6e08e5cfedd1b2efee2e0695d8p-116Q}; /**< ~0.434294482 */
	constexpr Float128x2 Float128x2_pi         = {0x1.921fb54442d18469898cc51701b8p+1Q,+0x1.cd129024e088a67cc74020bbea64p-114Q}; /**< ~3.141592654 */
	constexpr Float128x2 Float128x2_inv_pi     = {0x1.45f306dc9c882a53f84eafa3ea6ap-2Q,-0x1.11f924eb53361de37df00d74e2a1p-116Q}; /**< ~0.318309886 */
	constexpr Float128x2 Float128x2_inv_sqrtpi = {0x1.20dd750429b6d11ae3a914fed7fep-1Q,-0x1.e5df5fb2f8a29e0c574632f53e7ap-115Q}; /**< ~0.564189584 */
	constexpr Float128x2 Float128x2_ln2        = {0x1.62e42fefa39ef35793c7673007e6p-1Q,-0x1.2a17e1979b31ace93a4ebe5d148fp-117Q}; /**< ~0.693147181 */
	constexpr Float128x2 Float128x2_ln10       = {0x1.26bb1bbb5551582dd4adac5705a6p+1Q,+0x1.451c51fd9f3b4bbf21d078c3d040p-115Q}; /**< ~2.302585093 */
	constexpr Float128x2 Float128x2_sqrt2      = {0x1.6a09e667f3bcc908b2fb1366ea95p+0Q,+0x1.f4f8eb7b05d449dd426768bd642cp-114Q}; /**< ~1.414213562 */
	constexpr Float128x2 Float128x2_sqrt3      = {0x1.bb67ae8584caa73b25742d7078b8p+0Q,+0x1.dc492ec1a6629ed23cc639053243p-115Q}; /**< ~1.732050808 */
	constexpr Float128x2 Float128x2_inv_sqrt3  = {0x1.279a74590331c4d218f81e4afb25p-1Q,+0x1.f41864eb377634f0beecbdac6616p-115Q}; /**< ~0.577350269 */
	constexpr Float128x2 Float128x2_egamma     = {0x1.2788cfc6fb618f49a37c7f0202a6p-1Q,-0x1.a54af1899e284d19ff379fe1065cp-115Q}; /**< ~0.577215665 */
	constexpr Float128x2 Float128x2_phi        = {0x1.9e3779b97f4a7c15f39cc0605ceep+0Q,-0x1.be5f7beec4a062ec6d703c9caf71p-115Q}; /**< ~1.618033989 */

#if __cplusplus >= 201907L
#include <numbers>
namespace std {
	namespace numbers {
		template<> inline constexpr Float128x2 e_v          <Float128x2> = Float128x2_e         ; /**< ~2.718281828 */
		template<> inline constexpr Float128x2 log2e_v      <Float128x2> = Float128x2_log2e     ; /**< ~1.442695041 */
		template<> inline constexpr Float128x2 log10e_v     <Float128x2> = Float128x2_log10e    ; /**< ~0.434294482 */
		template<> inline constexpr Float128x2 pi_v         <Float128x2> = Float128x2_pi        ; /**< ~3.141592654 */
		template<> inline constexpr Float128x2 inv_pi_v     <Float128x2> = Float128x2_inv_pi    ; /**< ~0.318309886 */
		template<> inline constexpr Float128x2 inv_sqrtpi_v <Float128x2> = Float128x2_inv_sqrtpi; /**< ~0.564189584 */
		template<> inline constexpr Float128x2 ln2_v        <Float128x2> = Float128x2_ln2       ; /**< ~0.693147181 */
		template<> inline constexpr Float128x2 ln10_v       <Float128x2> = Float128x2_ln10      ; /**< ~2.302585093 */
		template<> inline constexpr Float128x2 sqrt2_v      <Float128x2> = Float128x2_sqrt2     ; /**< ~1.414213562 */
		template<> inline constexpr Float128x2 sqrt3_v      <Float128x2> = Float128x2_sqrt3     ; /**< ~1.732050808 */
		template<> inline constexpr Float128x2 inv_sqrt3_v  <Float128x2> = Float128x2_inv_sqrt3 ; /**< ~0.577350269 */
		template<> inline constexpr Float128x2 egamma_v     <Float128x2> = Float128x2_egamma    ; /**< ~0.577215665 */
		template<> inline constexpr Float128x2 phi_v        <Float128x2> = Float128x2_phi       ; /**< ~1.618033989 */
	}
}
#endif

//------------------------------------------------------------------------------
// Float128x2 Arithmetic Operator Overloads
//------------------------------------------------------------------------------

inline constexpr Float128x2 operator-(const Float128x2& x) {
	return {-x.hi, -x.lo};
}


#endif /* FLOAT128X2_HPP */
