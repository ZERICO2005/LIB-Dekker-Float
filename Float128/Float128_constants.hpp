/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef FLOAT128_CONSTANTS_HPP
#define FLOAT128_CONSTANTS_HPP

#include "../LDF/LDF_constants.hpp"

namespace LDF {

/* Multiples of pi*/

/** ~3.141592654 */
template<> inline constexpr __float128 const_pi            <__float128>() { return 3.141592653589793238462643383279502884e+00Q; }
/** ~6.283185307 `2 * pi` */
template<> inline constexpr __float128 const_2pi           <__float128>() { return 6.283185307179586476925286766559005768e+00Q; }
/** ~1.570796327 `1/2 * pi` */
template<> inline constexpr __float128 const_pi2           <__float128>() { return 1.570796326794896619231321691639751442e+00Q; }
/** ~0.785398163 `1/4 * pi` */
template<> inline constexpr __float128 const_pi4           <__float128>() { return 7.853981633974483096156608458198757210e-01Q; }
/** ~2.356194490 `3/4 * pi` */
template<> inline constexpr __float128 const_3pi4          <__float128>() { return 2.356194490192344928846982537459627163e+00Q; }
/** ~1.047197551 `1/3 * pi` */
template<> inline constexpr __float128 const_pi3           <__float128>() { return 1.047197551196597746154214461093167628e+00Q; }

/* Inverse and sqrt pi */

/** ~0.318309886 `1 / pi` */
template<> inline constexpr __float128 const_inv_pi        <__float128>() { return 3.183098861837906715377675267450287241e-01Q; }
/** ~0.159154943 `1 / 2pi` */
template<> inline constexpr __float128 const_inv_2pi       <__float128>() { return 1.591549430918953357688837633725143620e-01Q; }
/** ~1.772453851 `sqrt(pi)` */
template<> inline constexpr __float128 const_sqrtpi        <__float128>() { return 1.772453850905516027298167483341145183e+00Q; }
/** ~2.506628275 `sqrt(2pi)` */
template<> inline constexpr __float128 const_sqrt2pi       <__float128>() { return 2.506628274631000502415765284811045253e+00Q; }
/** ~0.564189584 `1 / sqrt(pi)` */
template<> inline constexpr __float128 const_inv_sqrtpi    <__float128>() { return 5.641895835477562869480794515607725858e-01Q; }
/** ~0.398942280 `1 / sqrt(2pi)` */
template<> inline constexpr __float128 const_inv_sqrt2pi   <__float128>() { return 3.989422804014326779399460599343818685e-01Q; }

/* Logarithms and Exponents */

/** ~2.718281828 Eulers number */
template<> inline constexpr __float128 const_e             <__float128>() { return 2.718281828459045235360287471352662498e+00Q; }
/** ~0.367879441 `1 / e` */
template<> inline constexpr __float128 const_inv_e         <__float128>() { return 3.678794411714423215955237701614608674e-01Q; }
/** ~0.693147181 `ln(2)` */
template<> inline constexpr __float128 const_ln2           <__float128>() { return 6.931471805599453094172321214581765681e-01Q; }
/** ~1.098612289 `ln(3)` */
template<> inline constexpr __float128 const_ln3           <__float128>() { return 1.098612288668109691395245236922525705e+00Q; }
/** ~2.302585093 `ln(10)` */
template<> inline constexpr __float128 const_ln10          <__float128>() { return 2.302585092994045684017991454684364208e+00Q; }
/** ~1.442695041 `log2(e)` */
template<> inline constexpr __float128 const_log2e         <__float128>() { return 1.442695040888963407359924681001892137e+00Q; }
/** ~0.910239227 `log3(e)` */
template<> inline constexpr __float128 const_log3e         <__float128>() { return 9.102392266268373936142401657361070006e-01Q; }
/** ~0.434294482 `log10(e)` */
template<> inline constexpr __float128 const_log10e        <__float128>() { return 4.342944819032518276511289189166050823e-01Q; }

/* Square Roots */

/** ~1.414213562 `sqrt(2)` */
template<> inline constexpr __float128 const_sqrt2         <__float128>() { return 1.414213562373095048801688724209698079e+00Q; }
/** ~1.732050808 `sqrt(3)` */
template<> inline constexpr __float128 const_sqrt3         <__float128>() { return 1.732050807568877293527446341505872367e+00Q; }
/** ~2.236067977 `sqrt(5)` */
template<> inline constexpr __float128 const_sqrt5         <__float128>() { return 2.236067977499789696409173668731276235e+00Q; }
/** ~2.449489743 `sqrt(6)` */
template<> inline constexpr __float128 const_sqrt6         <__float128>() { return 2.449489742783178098197284074705891392e+00Q; }
/** ~0.707106781 `1 / sqrt(2)` or `1/2 * sqrt(2)` */
template<> inline constexpr __float128 const_inv_sqrt2     <__float128>() { return 7.071067811865475244008443621048490393e-01Q; }
/** ~0.577350269 `1 / sqrt(3)` */
template<> inline constexpr __float128 const_inv_sqrt3     <__float128>() { return 5.773502691896257645091487805019574556e-01Q; }
/** ~0.447213595 `1 / sqrt(5)` */
template<> inline constexpr __float128 const_inv_sqrt5     <__float128>() { return 4.472135954999579392818347337462552471e-01Q; }
/** ~0.408248290 `1 / sqrt(6)` */
template<> inline constexpr __float128 const_inv_sqrt6     <__float128>() { return 4.082482904638630163662140124509818987e-01Q; }

/* Cube Roots */

/** ~1.259921050 `cbrt(2)` */
template<> inline constexpr __float128 const_cbrt2         <__float128>() { return 1.259921049894873164767210607278228351e+00Q; }
/** ~1.442249570 `cbrt(3)` */
template<> inline constexpr __float128 const_cbrt3         <__float128>() { return 1.442249570307408382321638310780109588e+00Q; }
/** ~1.709975947 `cbrt(5)` */
template<> inline constexpr __float128 const_cbrt5         <__float128>() { return 1.709975946676696989353108872543860110e+00Q; }
/** ~1.817120593 `cbrt(6)` */
template<> inline constexpr __float128 const_cbrt6         <__float128>() { return 1.817120592832139658891211756327260502e+00Q; }
/** ~0.793700526 `1 / cbrt(2)` */
template<> inline constexpr __float128 const_inv_cbrt2     <__float128>() { return 7.937005259840997373758528196361541302e-01Q; }
/** ~0.693361274 `1 / cbrt(3)` */
template<> inline constexpr __float128 const_inv_cbrt3     <__float128>() { return 6.933612743506347048433522747859617954e-01Q; }
/** ~0.584803548 `1 / cbrt(5)` */
template<> inline constexpr __float128 const_inv_cbrt5     <__float128>() { return 5.848035476425732131013574720275845557e-01Q; }
/** ~0.550321208 `1 / cbrt(6)` */
template<> inline constexpr __float128 const_inv_cbrt6     <__float128>() { return 5.503212081491044473124349920681808261e-01Q; }

/* Additional Mathematical Constants */

/** ~0.577215665 Euler-Mascheroni constant */
template<> inline constexpr __float128 const_egamma        <__float128>() { return 5.772156649015328606065120900824024310e-01Q; }
/** ~1.618033989 Golden Ratio */
template<> inline constexpr __float128 const_phi           <__float128>() { return 1.618033988749894848204586834365638118e+00Q; }
/** ~1.839286755 */
template<> inline constexpr __float128 const_tribonacci    <__float128>() { return 1.839286755214161132551852564653286600e+00Q; }
/** ~0.543689013 `1 / tribonacci` */
template<> inline constexpr __float128 const_inv_tribonacci<__float128>() { return 5.436890126920763615708559718017479865e-01Q; }
/** ~0.915965594 */
template<> inline constexpr __float128 const_catalan       <__float128>() { return 9.159655941772190150546035149323841108e-01Q; }
/** ~1.202056903 `zeta(3)` */
template<> inline constexpr __float128 const_apery         <__float128>() { return 1.202056903159594285399738161511449991e+00Q; }
/** ~0.596347362 `-e * eint(-1)` */
template<> inline constexpr __float128 const_gompertz      <__float128>() { return 5.963473623231940743410784993692793761e-01Q; }
/** ~2.622057554 */
template<> inline constexpr __float128 const_lemniscate    <__float128>() { return 2.622057554292119810464839589891119414e+00Q; }
/** ~5.244115109 `2 * lemniscate` */
template<> inline constexpr __float128 const_2lemniscate   <__float128>() { return 5.244115108584239620929679179782238827e+00Q; }
/** ~1.311028777 `1/2 * lemniscate` */
template<> inline constexpr __float128 const_lemniscate2   <__float128>() { return 1.311028777146059905232419794945559707e+00Q; }

}

#endif /* FLOAT128X2_CONSTANTS_HPP */
