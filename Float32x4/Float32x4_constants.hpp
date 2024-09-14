/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef FLOAT32X4_CONSTANTS_HPP
#define FLOAT32X4_CONSTANTS_HPP

#include "Float32x4_def.h"
#include "../LDF/LDF_constants.hpp"

namespace LDF {

/* Multiples of pi */

/** ~3.141592654 */
template<> inline constexpr Float32x4 const_pi<Float32x4>() { return {
	+3.1415927410e+00f,
	-8.7422776573e-08f,
	-3.4302490200e-15f,
	+2.1125997964e-23f
}; }

/** ~6.283185307 `2 * pi` */
template<> inline constexpr Float32x4 const_2pi<Float32x4>() { return {
	+6.2831854820e+00f,
	-1.7484555315e-07f,
	-6.8604980400e-15f,
	+4.2251995929e-23f
}; }

/** ~1.570796327 `1/2 * pi` */
template<> inline constexpr Float32x4 const_pi2<Float32x4>() { return {
	+1.5707963705e+00f,
	-4.3711388287e-08f,
	-1.7151245100e-15f,
	+1.0562998982e-23f
}; }

/** ~0.785398163 `1/4 * pi` */
template<> inline constexpr Float32x4 const_pi4<Float32x4>() { return {
	+7.8539818525e-01f,
	-2.1855694143e-08f,
	-8.5756225500e-16f,
	+5.2814994911e-24f
}; }

/** ~2.356194490 `3/4 * pi` */
template<> inline constexpr Float32x4 const_3pi4<Float32x4>() { return {
	+2.3561944962e+00f,
	-5.9624403193e-09f,
	+9.1848507326e-17f,
	+2.6096088697e-24f
}; }

/** ~1.047197551 `1/3 * pi` */
template<> inline constexpr Float32x4 const_pi3<Float32x4>() { return {
	+1.0471975803e+00f,
	-2.9140926117e-08f,
	-5.5129737589e-16f,
	-1.0604520676e-23f
}; }

/* Inverse and sqrt pi */

/** ~0.318309886 `1 / pi` */
template<> inline constexpr Float32x4 const_inv_pi<Float32x4>() { return {
	+3.1830987334e-01f,
	+1.2841276487e-08f,
	+1.4685477398e-16f,
	+3.0370133137e-24f
}; }

/** ~0.159154943 `1 / 2pi` */
template<> inline constexpr Float32x4 const_inv_2pi<Float32x4>() { return {
	+1.5915493667e-01f,
	+6.4206382433e-09f,
	+7.3427386991e-17f,
	+1.5185066568e-24f
}; }

/** ~1.772453851 `sqrt(pi)` */
template<> inline constexpr Float32x4 const_sqrtpi<Float32x4>() { return {
	+1.7724539042e+00f,
	-5.3246399290e-08f,
	-1.1868889296e-15f,
	+3.9969792931e-23f
}; }

/** ~2.506628275 `sqrt(2pi)` */
template<> inline constexpr Float32x4 const_sqrt2pi<Float32x4>() { return {
	+2.5066282749e+00f,
	-2.8660204765e-10f,
	+1.1003229300e-17f,
	+2.0473643572e-25f
}; }

/** ~0.564189584 `1 / sqrt(pi)` */
template<> inline constexpr Float32x4 const_inv_sqrtpi<Float32x4>() { return {
	+5.6418961287e-01f,
	-2.9317691386e-08f,
	-3.2539916810e-16f,
	-9.4786568143e-24f
}; }

/** ~0.398942280 `1 / sqrt(2pi)` */
template<> inline constexpr Float32x4 const_inv_sqrt2pi<Float32x4>() { return {
	+3.9894229174e-01f,
	-1.1335170136e-08f,
	+3.0587878429e-17f,
	+7.7952310938e-25f
}; }

/* Logarithms and Exponents */

/** ~2.718281828 Eulers number */
template<> inline constexpr Float32x4 const_e<Float32x4>() { return {
	+2.7182817459e+00f,
	+8.2548403668e-08f,
	-2.9640598735e-15f,
	+9.3757374452e-23f
}; }

/** ~0.367879441 `1 / e` */
template<> inline constexpr Float32x4 const_inv_e<Float32x4>() { return {
	+3.6787945032e-01f,
	-9.1497556198e-09f,
	+4.3166045719e-16f,
	-1.0097096154e-24f
}; }

/** ~0.693147181 `ln(2)` */
template<> inline constexpr Float32x4 const_ln2<Float32x4>() { return {
	+6.9314718246e-01f,
	-1.9046542121e-09f,
	-8.7831837386e-17f,
	+3.0618407385e-24f
}; }

/** ~1.098612289 `ln(3)` */
template<> inline constexpr Float32x4 const_ln3<Float32x4>() { return {
	+1.0986123085e+00f,
	-1.9834088150e-08f,
	+5.7542082129e-16f,
	+2.1136183736e-23f
}; }

/** ~2.302585093 `ln(10)` */
template<> inline constexpr Float32x4 const_ln10<Float32x4>() { return {
	+2.3025851250e+00f,
	-3.1975435633e-08f,
	-1.1052540117e-15f,
	-3.0319143140e-23f
}; }

/** ~1.442695041 `log2(e)` */
template<> inline constexpr Float32x4 const_log2e<Float32x4>() { return {
	+1.4426950216e+00f,
	+1.9259630335e-08f,
	-4.2373394934e-16f,
	+1.3227226017e-23f
}; }

/** ~0.910239227 `log3(e)` */
template<> inline constexpr Float32x4 const_log3e<Float32x4>() { return {
	+9.1023921967e-01f,
	+6.9613101950e-09f,
	-1.4508859117e-16f,
	+1.3499563679e-24f
}; }

/** ~0.434294482 `log10(e)` */
template<> inline constexpr Float32x4 const_log10e<Float32x4>() { return {
	+4.3429449201e-01f,
	-1.0103049952e-08f,
	-1.0003910417e-16f,
	-1.7921929746e-24f
}; }

/* Square Roots */

/** ~1.414213562 `sqrt(2)` */
template<> inline constexpr Float32x4 const_sqrt2<Float32x4>() { return {
	+1.4142135382e+00f,
	+2.4203234972e-08f,
	-7.6280674384e-16f,
	-4.0732118922e-24f
}; }

/** ~1.732050808 `sqrt(3)` */
template<> inline constexpr Float32x4 const_sqrt3<Float32x4>() { return {
	+1.7320507765e+00f,
	+3.1087250107e-08f,
	-1.2319167776e-15f,
	-9.7793445590e-24f
}; }

/** ~2.236067977 `sqrt(5)` */
template<> inline constexpr Float32x4 const_sqrt5<Float32x4>() { return {
	+2.2360680103e+00f,
	-3.2830410390e-08f,
	-1.0864230532e-16f,
	+1.2432034700e-24f
}; }

/** ~2.449489743 `sqrt(6)` */
template<> inline constexpr Float32x4 const_sqrt6<Float32x4>() { return {
	+2.4494898319e+00f,
	-8.9141259707e-08f,
	-6.7131675644e-16f,
	-1.1450017061e-23f
}; }

/** ~0.707106781 `1 / sqrt(2)` or `1/2 * sqrt(2)` */
template<> inline constexpr Float32x4 const_inv_sqrt2<Float32x4>() { return {
	+7.0710676908e-01f,
	+1.2101617486e-08f,
	-3.8140337192e-16f,
	-2.0366059461e-24f
}; }

/** ~0.577350269 `1 / sqrt(3)` */
template<> inline constexpr Float32x4 const_inv_sqrt3<Float32x4>() { return {
	+5.7735025883e-01f,
	+1.0362416702e-08f,
	-4.1063892585e-16f,
	-3.2597817169e-24f
}; }

/** ~0.447213595 `1 / sqrt(5)` */
template<> inline constexpr Float32x4 const_inv_sqrt5<Float32x4>() { return {
	+4.4721359015e-01f,
	+5.3548467882e-09f,
	+6.7089383554e-17f,
	-2.3983373253e-24f
}; }

/** ~0.408248290 `1 / sqrt(6)` */
template<> inline constexpr Float32x4 const_inv_sqrt6<Float32x4>() { return {
	+4.0824830532e-01f,
	-1.4856876618e-08f,
	-1.1188613048e-16f,
	+2.5032938883e-24f
}; }

/* Cube Roots */

/** ~1.259921050 `cbrt(2)` */
template<> inline constexpr Float32x4 const_cbrt2<Float32x4>() { return {
	+1.2599210739e+00f,
	-2.4018701694e-08f,
	+6.4023445892e-16f,
	+2.2098275341e-23f
}; }

/** ~1.442249570 `cbrt(3)` */
template<> inline constexpr Float32x4 const_cbrt3<Float32x4>() { return {
	+1.4422495365e+00f,
	+3.3793124743e-08f,
	+1.4128167571e-15f,
	-7.5360286567e-25f
}; }

/** ~1.709975947 `cbrt(5)` */
template<> inline constexpr Float32x4 const_cbrt5<Float32x4>() { return {
	+1.7099759579e+00f,
	-1.1193786342e-08f,
	-6.6794880786e-17f,
	+3.0718766270e-24f
}; }

/** ~1.817120593 `cbrt(6)` */
template<> inline constexpr Float32x4 const_cbrt6<Float32x4>() { return {
	+1.8171205521e+00f,
	+4.0769151610e-08f,
	-2.3257923310e-16f,
	+1.1642882508e-23f
}; }

/** ~0.793700526 `1 / cbrt(2)` */
template<> inline constexpr Float32x4 const_inv_cbrt2<Float32x4>() { return {
	+7.9370051622e-01f,
	+9.7601926541e-09f,
	-3.8741195895e-16f,
	+1.0589695613e-23f
}; }

/** ~0.693361274 `1 / cbrt(3)` */
template<> inline constexpr Float32x4 const_inv_cbrt3<Float32x4>() { return {
	+6.9336128235e-01f,
	-7.9979978196e-09f,
	-2.8807010848e-16f,
	+4.9645647617e-24f
}; }

/** ~0.584803548 `1 / cbrt(5)` */
template<> inline constexpr Float32x4 const_inv_cbrt5<Float32x4>() { return {
	+5.8480352163e-01f,
	+2.6009425724e-08f,
	-7.0454067088e-16f,
	-1.0949269458e-23f
}; }

/** ~0.550321208 `1 / cbrt(6)` */
template<> inline constexpr Float32x4 const_inv_cbrt6<Float32x4>() { return {
	+5.5032122135e-01f,
	-1.3202519078e-08f,
	-9.8510676228e-18f,
	-3.4208255506e-25f
}; }

/* Additional Mathematical Constants */

/** ~0.577215665 Euler-Mascheroni constant */
template<> inline constexpr Float32x4 const_egamma<Float32x4>() { return {
	+5.7721567154e-01f,
	-6.6377738861e-09f,
	+1.0607938876e-16f,
	-1.4491689387e-24f
}; }

/** ~1.618033989 Golden Ratio */
template<> inline constexpr Float32x4 const_phi<Float32x4>() { return {
	+1.6180340052e+00f,
	-1.6415205195e-08f,
	-5.4321152658e-17f,
	+6.2160173502e-25f
}; }

/** ~1.839286755 */
template<> inline constexpr Float32x4 const_tribonacci<Float32x4>() { return {
	+1.8392868042e+00f,
	-4.8985057788e-08f,
	+1.7038332432e-16f,
	-6.5054909440e-24f
}; }

/** ~0.543689013 `1 / tribonacci` */
template<> inline constexpr Float32x4 const_inv_tribonacci<Float32x4>() { return {
	+5.4368901253e-01f,
	+1.6461054742e-10f,
	-6.1567669242e-18f,
	+1.8605404011e-25f
}; }

/** ~0.915965594 */
template<> inline constexpr Float32x4 const_catalan<Float32x4>() { return {
	+9.1596561670e-01f,
	-2.2525814103e-08f,
	-3.2931934246e-16f,
	-6.5047135216e-24f
}; }

/** ~1.202056903 `zeta(3)` */
template<> inline constexpr Float32x4 const_apery<Float32x4>() { return {
	+1.2020568848e+00f,
	+1.8393969015e-08f,
	+2.7080352714e-16f,
	-1.2109306774e-23f
}; }

/** ~0.596347362 `-e * eint(-1)` */
template<> inline constexpr Float32x4 const_gompertz<Float32x4>() { return {
	+5.9634739161e-01f,
	-2.9282183789e-08f,
	+6.6591231566e-16f,
	-1.5799080596e-23f
}; }

/** ~2.622057554 */
template<> inline constexpr Float32x4 const_lemniscate<Float32x4>() { return {
	+2.6220574379e+00f,
	+1.1639539110e-07f,
	+1.9164309691e-16f,
	-9.5854715391e-25f
}; }

/** ~5.244115109 `2 * lemniscate` */
template<> inline constexpr Float32x4 const_2lemniscate<Float32x4>() { return {
	+5.2441148758e+00f,
	+2.3279078221e-07f,
	+3.8328619381e-16f,
	-1.9170943078e-24f
}; }

/** ~1.311028777 `1/2 * lemniscate` */
template<> inline constexpr Float32x4 const_lemniscate2<Float32x4>() { return {
	+1.3110287189e+00f,
	+5.8197695552e-08f,
	+9.5821548453e-17f,
	-4.7927357695e-25f
}; }

}

#endif /* FLOAT32X4_CONSTANTS_HPP */
