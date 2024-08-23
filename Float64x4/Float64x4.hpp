/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/
#ifndef FLOAT64X4_HPP
#define FLOAT64X4_HPP

#include "Float64x4_def.h"

/**
 * @note Float64x4 is currently unimplemented.
 */

//------------------------------------------------------------------------------
// Float64x2 Constants
//------------------------------------------------------------------------------

/* C++20 <numbers> */

	constexpr Float64x4 Float64x4_e          = {0x1.5bf0a8b145769p+1,+0x1.4d57ee2b1013ap-53,-0x1.618713a31d3e2p-109,+0x1.c5a6d2b53c26dp-163}; /**< ~2.718281828 */
	constexpr Float64x4 Float64x4_log2e      = {0x1.71547652b82fep+0,+0x1.777d0ffda0d24p-56,-0x1.60bb8a5442ab9p-110,-0x1.4b52d3ba6d74dp-166}; /**< ~1.442695041 */
	constexpr Float64x4 Float64x4_log10e     = {0x1.bcb7b1526e50ep-2,+0x1.95355baaafad3p-57,+0x1.ee191f71a3012p-112,+0x1.7268808e8fcb5p-167}; /**< ~0.434294482 */
	constexpr Float64x4 Float64x4_pi         = {0x1.921fb54442d18p+1,+0x1.1a62633145c07p-53,-0x1.f1976b7ed8fbcp-109,+0x1.4cf98e804177dp-163}; /**< ~3.141592654 */
	constexpr Float64x4 Float64x4_inv_pi     = {0x1.45f306dc9c883p-2,-0x1.6b01ec5417056p-56,-0x1.6447e493ad4cep-110,+0x1.e21c820ff28b2p-164}; /**< ~0.318309886 */
	constexpr Float64x4 Float64x4_inv_sqrtpi = {0x1.20dd750429b6dp-1,+0x1.1ae3a914fed80p-57,-0x1.3cbbebf65f145p-112,-0x1.e0c574632f53ep-167}; /**< ~0.564189584 */
	constexpr Float64x4 Float64x4_ln2        = {0x1.62e42fefa39efp-1,+0x1.abc9e3b39803fp-56,+0x1.7b57a079a1934p-111,-0x1.ace93a4ebe5d1p-165}; /**< ~0.693147181 */
	constexpr Float64x4 Float64x4_ln10       = {0x1.26bb1bbb55516p+1,-0x1.f48ad494ea3e9p-53,-0x1.9ebae3ae0260cp-107,-0x1.2d10378be1cf1p-161}; /**< ~2.302585093 */
	constexpr Float64x4 Float64x4_sqrt2      = {0x1.6a09e667f3bcdp+0,-0x1.bdd3413b26456p-54,+0x1.57d3e3adec175p-108,+0x1.2775099da2f59p-164}; /**< ~1.414213562 */
	constexpr Float64x4 Float64x4_sqrt3      = {0x1.bb67ae8584caap+0,+0x1.cec95d0b5c1e3p-54,-0x1.f11db689f2ccfp-110,+0x1.3da4798c720a6p-164}; /**< ~1.732050808 */
	constexpr Float64x4 Float64x4_inv_sqrt3  = {0x1.279a74590331cp-1,+0x1.34863e0792bedp-55,-0x1.a82f9e6c53222p-109,-0x1.cb0f41134253ap-163}; /**< ~0.577350269 */
	constexpr Float64x4 Float64x4_egamma     = {0x1.2788cfc6fb619p-1,-0x1.6cb90701fbfabp-58,-0x1.34a95e3133c51p-112,+0x1.9730064300f7dp-166}; /**< ~0.577215665 */
	constexpr Float64x4 Float64x4_phi        = {0x1.9e3779b97f4a8p+0,-0x1.f506319fcfd19p-55,+0x1.b906821044ed8p-109,-0x1.8bb1b5c0f272cp-165}; /**< ~1.618033989 */

#if __cplusplus >= 201907L
#include <numbers>
namespace std {
	namespace numbers {
		template<> inline constexpr Float64x4 e_v          <Float64x4> = Float64x4_e         ; /**< ~2.718281828 */
		template<> inline constexpr Float64x4 log2e_v      <Float64x4> = Float64x4_log2e     ; /**< ~1.442695041 */
		template<> inline constexpr Float64x4 log10e_v     <Float64x4> = Float64x4_log10e    ; /**< ~0.434294482 */
		template<> inline constexpr Float64x4 pi_v         <Float64x4> = Float64x4_pi        ; /**< ~3.141592654 */
		template<> inline constexpr Float64x4 inv_pi_v     <Float64x4> = Float64x4_inv_pi    ; /**< ~0.318309886 */
		template<> inline constexpr Float64x4 inv_sqrtpi_v <Float64x4> = Float64x4_inv_sqrtpi; /**< ~0.564189584 */
		template<> inline constexpr Float64x4 ln2_v        <Float64x4> = Float64x4_ln2       ; /**< ~0.693147181 */
		template<> inline constexpr Float64x4 ln10_v       <Float64x4> = Float64x4_ln10      ; /**< ~2.302585093 */
		template<> inline constexpr Float64x4 sqrt2_v      <Float64x4> = Float64x4_sqrt2     ; /**< ~1.414213562 */
		template<> inline constexpr Float64x4 sqrt3_v      <Float64x4> = Float64x4_sqrt3     ; /**< ~1.732050808 */
		template<> inline constexpr Float64x4 inv_sqrt3_v  <Float64x4> = Float64x4_inv_sqrt3 ; /**< ~0.577350269 */
		template<> inline constexpr Float64x4 egamma_v     <Float64x4> = Float64x4_egamma    ; /**< ~0.577215665 */
		template<> inline constexpr Float64x4 phi_v        <Float64x4> = Float64x4_phi       ; /**< ~1.618033989 */
	}
}
#endif

#endif /* FLOAT64X4_HPP */