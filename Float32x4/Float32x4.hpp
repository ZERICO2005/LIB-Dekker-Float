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

/**
 * @note Float32x4 is currently unimplemented.
 */

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

#endif /* FLOAT32X4_HPP */