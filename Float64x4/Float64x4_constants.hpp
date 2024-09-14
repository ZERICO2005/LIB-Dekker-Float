/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef FLOAT64X4_CONSTANTS_HPP
#define FLOAT64X4_CONSTANTS_HPP

#include "Float64x4_def.h"
#include "../LDF/LDF_constants.hpp"

namespace LDF {

/* Multiples of pi */

/** ~3.141592654 */
template<> inline constexpr Float64x4 const_pi<Float64x4>() { return {
	+3.141592653589793116e+00,
	+1.224646799147353207e-16,
	-2.994769809718339666e-33,
	+1.112454220863365282e-49
}; }

/** ~6.283185307 `2 * pi` */
template<> inline constexpr Float64x4 const_2pi<Float64x4>() { return {
	+6.283185307179586232e+00,
	+2.449293598294706414e-16,
	-5.989539619436679332e-33,
	+2.224908441726730563e-49
}; }

/** ~1.570796327 `1/2 * pi` */
template<> inline constexpr Float64x4 const_pi2<Float64x4>() { return {
	+1.570796326794896558e+00,
	+6.123233995736766036e-17,
	-1.497384904859169833e-33,
	+5.562271104316826408e-50
}; }

/** ~0.785398163 `1/4 * pi` */
template<> inline constexpr Float64x4 const_pi4<Float64x4>() { return {
	+7.853981633974482790e-01,
	+3.061616997868383018e-17,
	-7.486924524295849165e-34,
	+2.781135552158413204e-50
}; }

/** ~2.356194490 `3/4 * pi` */
template<> inline constexpr Float64x4 const_3pi4<Float64x4>() { return {
	+2.356194490192344837e+00,
	+9.184850993605148438e-17,
	+3.916898464750400322e-33,
	-2.586798163270486418e-49
}; }

/** ~1.047197551 `1/3 * pi` */
template<> inline constexpr Float64x4 const_pi3<Float64x4>() { return {
	+1.047197551196597853e+00,
	-1.072081766451090985e-16,
	-9.982566032394464413e-34,
	-7.695615360182150485e-50
}; }

/* Inverse and sqrt pi */

/** ~0.318309886 `1 / pi` */
template<> inline constexpr Float64x4 const_inv_pi<Float64x4>() { return {
	+3.183098861837906912e-01,
	-1.967867667518248588e-17,
	-1.072143628289300400e-33,
	+8.053563926594111967e-50
}; }

/** ~0.159154943 `1 / 2pi` */
template<> inline constexpr Float64x4 const_inv_2pi<Float64x4>() { return {
	+1.591549430918953456e-01,
	-9.839338337591242941e-18,
	-5.360718141446502002e-34,
	+4.026781963297055983e-50
}; }

/** ~1.772453851 `sqrt(pi)` */
template<> inline constexpr Float64x4 const_sqrtpi<Float64x4>() { return {
	+1.772453850905516104e+00,
	-7.666586499825798697e-17,
	-1.305833490794542906e-33,
	-2.611014208782715459e-50
}; }

/** ~2.506628275 `sqrt(2pi)` */
template<> inline constexpr Float64x4 const_sqrt2pi<Float64x4>() { return {
	+2.506628274631000686e+00,
	-1.832857998045916677e-16,
	-7.345337700682642697e-33,
	+5.880128511846697217e-50
}; }

/** ~0.564189584 `1 / sqrt(pi)` */
template<> inline constexpr Float64x4 const_inv_sqrtpi<Float64x4>() { return {
	+5.641895835477562793e-01,
	+7.667729806582940611e-18,
	-2.382842298346843148e-34,
	-1.003897330827631504e-50
}; }

/** ~0.398942280 `1 / sqrt(2pi)` */
template<> inline constexpr Float64x4 const_inv_sqrt2pi<Float64x4>() { return {
	+3.989422804014327029e-01,
	-2.492327202277730044e-17,
	-3.424925447729621017e-34,
	+3.080222938252878104e-51
}; }

/* Logarithms and Exponents */

/** ~2.718281828 Eulers number */
template<> inline constexpr Float64x4 const_e<Float64x4>() { return {
	+2.718281828459045091e+00,
	+1.445646891729250158e-16,
	-2.127717108038176765e-33,
	+1.515630159841219144e-49
}; }

/** ~0.367879441 `1 / e` */
template<> inline constexpr Float64x4 const_inv_e<Float64x4>() { return {
	+3.678794411714423340e-01,
	-1.242875367278836258e-17,
	-5.830044851072742004e-34,
	-2.826797784901743573e-50
}; }

/** ~0.693147181 `ln(2)` */
template<> inline constexpr Float64x4 const_ln2<Float64x4>() { return {
	+6.931471805599452862e-01,
	+2.319046813846299558e-17,
	+5.707708438416212066e-34,
	-3.582432210601811423e-50
}; }

/** ~1.098612289 `ln(3)` */
template<> inline constexpr Float64x4 const_ln3<Float64x4>() { return {
	+1.098612288668109782e+00,
	-9.071297235001529955e-17,
	-8.691436473170396324e-34,
	-2.171042457240107544e-50
}; }

/** ~2.302585093 `ln(10)` */
template<> inline constexpr Float64x4 const_ln10<Float64x4>() { return {
	+2.302585092994045901e+00,
	-2.170756223382249351e-16,
	-9.984262454465776570e-33,
	-4.023357454450206379e-49
}; }

/** ~1.442695041 `log2(e)` */
template<> inline constexpr Float64x4 const_log2e<Float64x4>() { return {
	+1.442695040888963387e+00,
	+2.035527374093103311e-17,
	-1.061465995611725787e-33,
	-1.383671678018140168e-50
}; }

/** ~0.910239227 `log3(e)` */
template<> inline constexpr Float64x4 const_log3e<Float64x4>() { return {
	+9.102392266268374277e-01,
	-3.406628736007232203e-17,
	-3.169480364331625582e-34,
	-1.631816369235663708e-50
}; }

/** ~0.434294482 `log10(e)` */
template<> inline constexpr Float64x4 const_log10e<Float64x4>() { return {
	+4.342944819032518167e-01,
	+1.098319650216765073e-17,
	+3.717181233110958967e-34,
	+7.734484346504298627e-51
}; }

/* Square Roots */

/** ~1.414213562 `sqrt(2)` */
template<> inline constexpr Float64x4 const_sqrt2<Float64x4>() { return {
	+1.414213562373095145e+00,
	-9.667293313452913451e-17,
	+4.138675308699413563e-33,
	+4.935546991468350912e-50
}; }

/** ~1.732050808 `sqrt(3)` */
template<> inline constexpr Float64x4 const_sqrt3<Float64x4>() { return {
	+1.732050807568877193e+00,
	+1.003508422180690280e-16,
	-1.495954247573389563e-33,
	+5.306147563296169417e-50
}; }

/** ~2.236067977 `sqrt(5)` */
template<> inline constexpr Float64x4 const_sqrt5<Float64x4>() { return {
	+2.236067977499789805e+00,
	-1.086423040736501230e-16,
	+5.308650416763130923e-33,
	-6.609983995004215569e-50
}; }

/** ~2.449489743 `sqrt(6)` */
template<> inline constexpr Float64x4 const_sqrt6<Float64x4>() { return {
	+2.449489742783177881e+00,
	+2.168616518103246086e-16,
	+8.240049980770320147e-33,
	-4.434369519944876985e-50
}; }

/** ~0.707106781 `1 / sqrt(2)` or `1/2 * sqrt(2)` */
template<> inline constexpr Float64x4 const_inv_sqrt2<Float64x4>() { return {
	+7.071067811865475727e-01,
	-4.833646656726456726e-17,
	+2.069337654349706781e-33,
	+2.467773495734175456e-50
}; }

/** ~0.577350269 `1 / sqrt(3)` */
template<> inline constexpr Float64x4 const_inv_sqrt3<Float64x4>() { return {
	+5.773502691896257311e-01,
	+3.345028073935634473e-17,
	-2.552976689870847927e-33,
	-1.533697829015799630e-49
}; }

/** ~0.447213595 `1 / sqrt(5)` */
template<> inline constexpr Float64x4 const_inv_sqrt5<Float64x4>() { return {
	+4.472135954999579277e-01,
	+1.157822992402467192e-17,
	+7.535812922506684652e-34,
	-3.032566213459848327e-50
}; }

/** ~0.408248290 `1 / sqrt(6)` */
template<> inline constexpr Float64x4 const_inv_sqrt6<Float64x4>() { return {
	+4.082482904638630172e-01,
	-8.638255191177818720e-19,
	-6.908130015799011614e-36,
	+6.276782637017912716e-52
}; }

/* Cube Roots */

/** ~1.259921050 `cbrt(2)` */
template<> inline constexpr Float64x4 const_cbrt2<Float64x4>() { return {
	+1.259921049894873191e+00,
	-2.589933375300506918e-17,
	+9.727808156156372402e-34,
	+5.932267471174277737e-50
}; }

/** ~1.442249570 `cbrt(3)` */
template<> inline constexpr Float64x4 const_cbrt3<Float64x4>() { return {
	+1.442249570307408302e+00,
	+8.054912676113687134e-17,
	-2.618247242901535899e-33,
	-2.824357315193685883e-50
}; }

/** ~1.709975947 `cbrt(5)` */
template<> inline constexpr Float64x4 const_cbrt5<Float64x4>() { return {
	+1.709975946676697056e+00,
	-6.679487771389463610e-17,
	+4.267291597281299356e-33,
	+2.263656361985388306e-49
}; }

/** ~1.817120593 `cbrt(6)` */
template<> inline constexpr Float64x4 const_cbrt6<Float64x4>() { return {
	+1.817120592832139669e+00,
	-1.053461653145814723e-17,
	+5.770942774615513103e-34,
	+3.354496791720487423e-50
}; }

/** ~0.793700526 `1 / cbrt(2)` */
template<> inline constexpr Float64x4 const_inv_cbrt2<Float64x4>() { return {
	+7.937005259840997917e-01,
	-5.434504097098911493e-17,
	+4.690480978357969268e-34,
	+1.341866407751138654e-50
}; }

/** ~0.693361274 `1 / cbrt(3)` */
template<> inline constexpr Float64x4 const_inv_cbrt3<Float64x4>() { return {
	+6.933612743506346598e-01,
	+4.499680387265698707e-17,
	+7.461963611696051741e-34,
	-1.650780102808548231e-50
}; }

/** ~0.584803548 `1 / cbrt(5)` */
template<> inline constexpr Float64x4 const_inv_cbrt5<Float64x4>() { return {
	+5.848035476425732515e-01,
	-3.840686705794331653e-17,
	-1.861690042334640117e-33,
	-6.874880988134781036e-50
}; }

/** ~0.550321208 `1 / cbrt(6)` */
template<> inline constexpr Float64x4 const_inv_cbrt6<Float64x4>() { return {
	+5.503212081491044572e-01,
	-9.851067964905208562e-18,
	+5.965810966617877789e-34,
	+1.805683742763388315e-51
}; }

/* Additional Mathematical Constants */

/** ~0.577215665 Euler-Mascheroni constant */
template<> inline constexpr Float64x4 const_egamma<Float64x4>() { return {
	+5.772156649015328655e-01,
	-4.942915152430644868e-18,
	-2.322111740706956918e-34,
	+1.700494743381096356e-50
}; }

/** ~1.618033989 Golden Ratio */
template<> inline constexpr Float64x4 const_phi<Float64x4>() { return {
	+1.618033988749894903e+00,
	-5.432115203682506149e-17,
	+2.654325208381565462e-33,
	-3.304991997502107784e-50
}; }

/** ~1.839286755 */
template<> inline constexpr Float64x4 const_tribonacci<Float64x4>() { return {
	+1.839286755214161184e+00,
	-5.166128711235951994e-17,
	+1.640165092040780304e-33,
	-1.813002943644954296e-50
}; }

/** ~0.543689013 `1 / tribonacci` */
template<> inline constexpr Float64x4 const_inv_tribonacci<Float64x4>() { return {
	+5.436890126920763677e-01,
	-6.156766738133783152e-18,
	+1.187931874837851405e-34,
	-8.252416427936383413e-51
}; }

/** ~0.915965594 */
template<> inline constexpr Float64x4 const_catalan<Float64x4>() { return {
	+9.159655941772190113e-01,
	+3.747558421514983845e-18,
	-2.281215906674146270e-34,
	+4.708639405026647471e-51
}; }

/** ~1.202056903 `zeta(3)` */
template<> inline constexpr Float64x4 const_apery<Float64x4>() { return {
	+1.202056903159594237e+00,
	+4.875891010379531804e-17,
	-2.985864108294299059e-33,
	-3.053579984245075500e-50
}; }

/** ~0.596347362 `-e * eint(-1)` */
template<> inline constexpr Float64x4 const_gompertz<Float64x4>() { return {
	+5.963473623231940746e-01,
	-2.215149147878839757e-19,
	-1.078400903200283423e-38,
	-4.530953279294682502e-55
}; }

/** ~2.622057554 */
template<> inline constexpr Float64x4 const_lemniscate<Float64x4>() { return {
	+2.622057554292119619e+00,
	+1.916430959469797945e-16,
	+9.968917493117175421e-33,
	+6.099667701471762700e-49
}; }

/** ~5.244115109 `2 * lemniscate` */
template<> inline constexpr Float64x4 const_2lemniscate<Float64x4>() { return {
	+5.244115108584239238e+00,
	+3.832861918939595890e-16,
	+1.993783498623435084e-32,
	+1.219933540294352540e-48
}; }

/** ~1.311028777 `1/2 * lemniscate` */
template<> inline constexpr Float64x4 const_lemniscate2<Float64x4>() { return {
	+1.311028777146059809e+00,
	+9.582154797348989724e-17,
	+4.984458746558587710e-33,
	+3.049833850735881350e-49
}; }

}

#endif /* FLOAT64X4_CONSTANTS_HPP */
