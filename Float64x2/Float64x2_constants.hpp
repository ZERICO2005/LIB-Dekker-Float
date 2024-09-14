/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef FLOAT64X2_CONSTANTS_HPP
#define FLOAT64X2_CONSTANTS_HPP

#include "Float64x2_def.h"
#include "../LDF/LDF_constants.hpp"

namespace LDF {

/* Multiples of pi */

/** ~3.141592654 */
template<> inline constexpr Float64x2 const_pi<Float64x2>() { return {
	+3.141592653589793116e+00,
	+1.224646799147353207e-16
}; }

/** ~6.283185307 `2 * pi` */
template<> inline constexpr Float64x2 const_2pi<Float64x2>() { return {
	+6.283185307179586232e+00,
	+2.449293598294706414e-16
}; }

/** ~1.570796327 `1/2 * pi` */
template<> inline constexpr Float64x2 const_pi2<Float64x2>() { return {
	+1.570796326794896558e+00,
	+6.123233995736766036e-17
}; }

/** ~0.785398163 `1/4 * pi` */
template<> inline constexpr Float64x2 const_pi4<Float64x2>() { return {
	+7.853981633974482790e-01,
	+3.061616997868383018e-17
}; }

/** ~2.356194490 `3/4 * pi` */
template<> inline constexpr Float64x2 const_3pi4<Float64x2>() { return {
	+2.356194490192344837e+00,
	+9.184850993605148438e-17
}; }

/** ~1.047197551 `1/3 * pi` */
template<> inline constexpr Float64x2 const_pi3<Float64x2>() { return {
	+1.047197551196597853e+00,
	-1.072081766451090985e-16
}; }

/* Inverse and sqrt pi */

/** ~0.318309886 `1 / pi` */
template<> inline constexpr Float64x2 const_inv_pi<Float64x2>() { return {
	+3.183098861837906912e-01,
	-1.967867667518248588e-17
}; }

/** ~0.159154943 `1 / 2pi` */
template<> inline constexpr Float64x2 const_inv_2pi<Float64x2>() { return {
	+1.591549430918953456e-01,
	-9.839338337591242941e-18
}; }

/** ~1.772453851 `sqrt(pi)` */
template<> inline constexpr Float64x2 const_sqrtpi<Float64x2>() { return {
	+1.772453850905516104e+00,
	-7.666586499825798697e-17
}; }

/** ~2.506628275 `sqrt(2pi)` */
template<> inline constexpr Float64x2 const_sqrt2pi<Float64x2>() { return {
	+2.506628274631000686e+00,
	-1.832857998045916677e-16
}; }

/** ~0.564189584 `1 / sqrt(pi)` */
template<> inline constexpr Float64x2 const_inv_sqrtpi<Float64x2>() { return {
	+5.641895835477562793e-01,
	+7.667729806582940611e-18
}; }

/** ~0.398942280 `1 / sqrt(2pi)` */
template<> inline constexpr Float64x2 const_inv_sqrt2pi<Float64x2>() { return {
	+3.989422804014327029e-01,
	-2.492327202277730044e-17
}; }

/* Logarithms and Exponents */

/** ~2.718281828 Eulers number */
template<> inline constexpr Float64x2 const_e<Float64x2>() { return {
	+2.718281828459045091e+00,
	+1.445646891729250158e-16
}; }

/** ~0.367879441 `1 / e` */
template<> inline constexpr Float64x2 const_inv_e<Float64x2>() { return {
	+3.678794411714423340e-01,
	-1.242875367278836258e-17
}; }

/** ~0.693147181 `ln(2)` */
template<> inline constexpr Float64x2 const_ln2<Float64x2>() { return {
	+6.931471805599452862e-01,
	+2.319046813846299558e-17
}; }

/** ~1.098612289 `ln(3)` */
template<> inline constexpr Float64x2 const_ln3<Float64x2>() { return {
	+1.098612288668109782e+00,
	-9.071297235001529955e-17
}; }

/** ~2.302585093 `ln(10)` */
template<> inline constexpr Float64x2 const_ln10<Float64x2>() { return {
	+2.302585092994045901e+00,
	-2.170756223382249351e-16
}; }

/** ~1.442695041 `log2(e)` */
template<> inline constexpr Float64x2 const_log2e<Float64x2>() { return {
	+1.442695040888963387e+00,
	+2.035527374093103311e-17
}; }

/** ~0.910239227 `log3(e)` */
template<> inline constexpr Float64x2 const_log3e<Float64x2>() { return {
	+9.102392266268374277e-01,
	-3.406628736007232203e-17
}; }

/** ~0.434294482 `log10(e)` */
template<> inline constexpr Float64x2 const_log10e<Float64x2>() { return {
	+4.342944819032518167e-01,
	+1.098319650216765073e-17
}; }

/* Square Roots */

/** ~1.414213562 `sqrt(2)` */
template<> inline constexpr Float64x2 const_sqrt2<Float64x2>() { return {
	+1.414213562373095145e+00,
	-9.667293313452913451e-17
}; }

/** ~1.732050808 `sqrt(3)` */
template<> inline constexpr Float64x2 const_sqrt3<Float64x2>() { return {
	+1.732050807568877193e+00,
	+1.003508422180690280e-16
}; }

/** ~2.236067977 `sqrt(5)` */
template<> inline constexpr Float64x2 const_sqrt5<Float64x2>() { return {
	+2.236067977499789805e+00,
	-1.086423040736501230e-16
}; }

/** ~2.449489743 `sqrt(6)` */
template<> inline constexpr Float64x2 const_sqrt6<Float64x2>() { return {
	+2.449489742783177881e+00,
	+2.168616518103246086e-16
}; }

/** ~0.707106781 `1 / sqrt(2)` or `1/2 * sqrt(2)` */
template<> inline constexpr Float64x2 const_inv_sqrt2<Float64x2>() { return {
	+7.071067811865475727e-01,
	-4.833646656726456726e-17
}; }

/** ~0.577350269 `1 / sqrt(3)` */
template<> inline constexpr Float64x2 const_inv_sqrt3<Float64x2>() { return {
	+5.773502691896257311e-01,
	+3.345028073935634473e-17
}; }

/** ~0.447213595 `1 / sqrt(5)` */
template<> inline constexpr Float64x2 const_inv_sqrt5<Float64x2>() { return {
	+4.472135954999579277e-01,
	+1.157822992402467192e-17
}; }

/** ~0.408248290 `1 / sqrt(6)` */
template<> inline constexpr Float64x2 const_inv_sqrt6<Float64x2>() { return {
	+4.082482904638630172e-01,
	-8.638255191177818720e-19
}; }

/* Cube Roots */

/** ~1.259921050 `cbrt(2)` */
template<> inline constexpr Float64x2 const_cbrt2<Float64x2>() { return {
	+1.259921049894873191e+00,
	-2.589933375300506918e-17
}; }

/** ~1.442249570 `cbrt(3)` */
template<> inline constexpr Float64x2 const_cbrt3<Float64x2>() { return {
	+1.442249570307408302e+00,
	+8.054912676113687134e-17
}; }

/** ~1.709975947 `cbrt(5)` */
template<> inline constexpr Float64x2 const_cbrt5<Float64x2>() { return {
	+1.709975946676697056e+00,
	-6.679487771389463610e-17
}; }

/** ~1.817120593 `cbrt(6)` */
template<> inline constexpr Float64x2 const_cbrt6<Float64x2>() { return {
	+1.817120592832139669e+00,
	-1.053461653145814723e-17
}; }

/** ~0.793700526 `1 / cbrt(2)` */
template<> inline constexpr Float64x2 const_inv_cbrt2<Float64x2>() { return {
	+7.937005259840997917e-01,
	-5.434504097098911493e-17
}; }

/** ~0.693361274 `1 / cbrt(3)` */
template<> inline constexpr Float64x2 const_inv_cbrt3<Float64x2>() { return {
	+6.933612743506346598e-01,
	+4.499680387265698707e-17
}; }

/** ~0.584803548 `1 / cbrt(5)` */
template<> inline constexpr Float64x2 const_inv_cbrt5<Float64x2>() { return {
	+5.848035476425732515e-01,
	-3.840686705794331653e-17
}; }

/** ~0.550321208 `1 / cbrt(6)` */
template<> inline constexpr Float64x2 const_inv_cbrt6<Float64x2>() { return {
	+5.503212081491044572e-01,
	-9.851067964905208562e-18
}; }

/* Additional Mathematical Constants */

/** ~0.577215665 Euler-Mascheroni constant */
template<> inline constexpr Float64x2 const_egamma<Float64x2>() { return {
	+5.772156649015328655e-01,
	-4.942915152430644868e-18
}; }

/** ~1.618033989 Golden Ratio */
template<> inline constexpr Float64x2 const_phi<Float64x2>() { return {
	+1.618033988749894903e+00,
	-5.432115203682506149e-17
}; }

/** ~1.839286755 */
template<> inline constexpr Float64x2 const_tribonacci<Float64x2>() { return {
	+1.839286755214161184e+00,
	-5.166128711235951994e-17
}; }

/** ~0.543689013 `1 / tribonacci` */
template<> inline constexpr Float64x2 const_inv_tribonacci<Float64x2>() { return {
	+5.436890126920763677e-01,
	-6.156766738133783152e-18
}; }

/** ~0.915965594 */
template<> inline constexpr Float64x2 const_catalan<Float64x2>() { return {
	+9.159655941772190113e-01,
	+3.747558421514983845e-18
}; }

/** ~1.202056903 `zeta(3)` */
template<> inline constexpr Float64x2 const_apery<Float64x2>() { return {
	+1.202056903159594237e+00,
	+4.875891010379531804e-17
}; }

/** ~0.596347362 `-e * eint(-1)` */
template<> inline constexpr Float64x2 const_gompertz<Float64x2>() { return {
	+5.963473623231940746e-01,
	-2.215149147878839757e-19
}; }

/** ~2.622057554 */
template<> inline constexpr Float64x2 const_lemniscate<Float64x2>() { return {
	+2.622057554292119619e+00,
	+1.916430959469797945e-16
}; }

/** ~5.244115109 `2 * lemniscate` */
template<> inline constexpr Float64x2 const_2lemniscate<Float64x2>() { return {
	+5.244115108584239238e+00,
	+3.832861918939595890e-16
}; }

/** ~1.311028777 `1/2 * lemniscate` */
template<> inline constexpr Float64x2 const_lemniscate2<Float64x2>() { return {
	+1.311028777146059809e+00,
	+9.582154797348989724e-17
}; }

}

#endif /* FLOAT64X2_CONSTANTS_HPP */
