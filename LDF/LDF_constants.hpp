/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef LDF_CONSTANTS_HPP
#define LDF_CONSTANTS_HPP

/**
 * When generating constants for float, double, and long double:
 * Print ceil(mantissa-bits * log10(2)) + 1 decimal digits
 * Assume long double has a 128bit mantissa (40 digits)
 * Assume double has a 64bit mantisaa (21 digits)
 * Assume float has a 32bit mantissa (11 digits)
 */

/**
 * Required Constants for LIB-Dekker-Float:
 * - const_pi, const_2pi, const_pi2, const_pi4, const_3pi4,
 * - const_inv_pi, const_sqrtpi,
 * - const_e, const_inv_e, const_ln2, const_ln10, const_log2e, const_log10e,
 * - const_sqrt2, const_sqrt3, const_inv_sqrt3,
 * - const_egamma, const_phi
 *
 * All of these constants are required for calculating C99 math.h functions,
 * and for C++20 <numbers>
 */

namespace LDF {

/* Multiples of pi*/
template<typename T> inline constexpr T const_pi            (); /**< ~3.141592654 */
template<typename T> inline constexpr T const_2pi           (); /**< ~6.283185307 `2 * pi` */
template<typename T> inline constexpr T const_pi2           (); /**< ~1.570796327 `1/2 * pi` */
template<typename T> inline constexpr T const_pi4           (); /**< ~0.785398163 `1/4 * pi` */
template<typename T> inline constexpr T const_3pi4          (); /**< ~2.356194490 `3/4 * pi` */
template<typename T> inline constexpr T const_pi3           (); /**< ~1.047197551 `1/3 * pi` */

/* Inverse and sqrt pi */
template<typename T> inline constexpr T const_inv_pi        (); /**< ~0.318309886 `1 / pi` */
template<typename T> inline constexpr T const_inv_2pi       (); /**< ~0.159154943 `1 / 2pi` */
template<typename T> inline constexpr T const_sqrtpi        (); /**< ~1.772453851 `sqrt(pi)` */
template<typename T> inline constexpr T const_sqrt2pi       (); /**< ~2.506628275 `sqrt(2pi)` */
template<typename T> inline constexpr T const_inv_sqrtpi    (); /**< ~0.564189584 `1 / sqrt(pi)` */
template<typename T> inline constexpr T const_inv_sqrt2pi   (); /**< ~0.398942280 `1 / sqrt(2pi)` */

/* Logarithms and Exponents */
template<typename T> inline constexpr T const_e             (); /**< ~2.718281828 Eulers number */
template<typename T> inline constexpr T const_inv_e         (); /**< ~0.367879441 `1 / e` */
template<typename T> inline constexpr T const_ln2           (); /**< ~0.693147181 `ln(2)` */
template<typename T> inline constexpr T const_ln3           (); /**< ~1.098612289 `ln(3)` */
template<typename T> inline constexpr T const_ln10          (); /**< ~2.302585093 `ln(10)` */
template<typename T> inline constexpr T const_log2e         (); /**< ~1.442695041 `log2(e)` */
template<typename T> inline constexpr T const_log3e         (); /**< ~0.910239227 `log3(e)` */
template<typename T> inline constexpr T const_log10e        (); /**< ~0.434294482 `log10(e)` */

/* Square Roots */
template<typename T> inline constexpr T const_sqrt2         (); /**< ~1.414213562 `sqrt(2)` */
template<typename T> inline constexpr T const_sqrt3         (); /**< ~1.732050808 `sqrt(3)` */
template<typename T> inline constexpr T const_sqrt5         (); /**< ~2.236067977 `sqrt(5)` */
template<typename T> inline constexpr T const_sqrt6         (); /**< ~2.449489743 `sqrt(6)` */
template<typename T> inline constexpr T const_inv_sqrt2     (); /**< ~0.707106781 `1 / sqrt(2)` or `1/2 * sqrt(2)` */
template<typename T> inline constexpr T const_inv_sqrt3     (); /**< ~0.577350269 `1 / sqrt(3)` */
template<typename T> inline constexpr T const_inv_sqrt5     (); /**< ~0.447213595 `1 / sqrt(5)` */
template<typename T> inline constexpr T const_inv_sqrt6     (); /**< ~0.408248290 `1 / sqrt(6)` */

/* Cube Roots */
template<typename T> inline constexpr T const_cbrt2         (); /**< ~1.259921050 `cbrt(2)` */
template<typename T> inline constexpr T const_cbrt3         (); /**< ~1.442249570 `cbrt(3)` */
template<typename T> inline constexpr T const_cbrt5         (); /**< ~1.709975947 `cbrt(5)` */
template<typename T> inline constexpr T const_cbrt6         (); /**< ~1.817120593 `cbrt(6)` */
template<typename T> inline constexpr T const_inv_cbrt2     (); /**< ~0.793700526 `1 / cbrt(2)` */
template<typename T> inline constexpr T const_inv_cbrt3     (); /**< ~0.693361274 `1 / cbrt(3)` */
template<typename T> inline constexpr T const_inv_cbrt5     (); /**< ~0.584803548 `1 / cbrt(5)` */
template<typename T> inline constexpr T const_inv_cbrt6     (); /**< ~0.550321208 `1 / cbrt(6)` */

/* Additional Mathematical Constants */
template<typename T> inline constexpr T const_egamma        (); /**< ~0.577215665 Euler-Mascheroni constant */
template<typename T> inline constexpr T const_phi           (); /**< ~1.618033989 Golden Ratio */
template<typename T> inline constexpr T const_tribonacci    (); /**< ~1.839286755 */
template<typename T> inline constexpr T const_inv_tribonacci(); /**< ~0.543689013 `1 / tribonacci` */
template<typename T> inline constexpr T const_catalan       (); /**< ~0.915965594 */
template<typename T> inline constexpr T const_apery         (); /**< ~1.202056903 `zeta(3)` */
template<typename T> inline constexpr T const_gompertz      (); /**< ~0.596347362 `-e * eint(-1)` */
template<typename T> inline constexpr T const_lemniscate    (); /**< ~2.622057554 */
template<typename T> inline constexpr T const_2lemniscate   (); /**< ~5.244115109 `2 * lemniscate` */
template<typename T> inline constexpr T const_lemniscate2   (); /**< ~1.311028777 `1/2 * lemniscate` */

//------------------------------------------------------------------------------
// <long double> Constants
//------------------------------------------------------------------------------

/* Multiples of pi*/

/** ~3.141592654 */
template<> inline constexpr long double const_pi            <long double>() { return 3.1415926535897932384626433832795028841972e+00L; }
/** ~6.283185307 `2 * pi` */
template<> inline constexpr long double const_2pi           <long double>() { return 6.2831853071795864769252867665590057683943e+00L; }
/** ~1.570796327 `1/2 * pi` */
template<> inline constexpr long double const_pi2           <long double>() { return 1.5707963267948966192313216916397514420986e+00L; }
/** ~0.785398163 `1/4 * pi` */
template<> inline constexpr long double const_pi4           <long double>() { return 7.8539816339744830961566084581987572104929e-01L; }
/** ~2.356194490 `3/4 * pi` */
template<> inline constexpr long double const_3pi4          <long double>() { return 2.3561944901923449288469825374596271631479e+00L; }
/** ~1.047197551 `1/3 * pi` */
template<> inline constexpr long double const_pi3           <long double>() { return 1.0471975511965977461542144610931676280657e+00L; }

/* Inverse and sqrt pi */

/** ~0.318309886 `1 / pi` */
template<> inline constexpr long double const_inv_pi        <long double>() { return 3.1830988618379067153776752674502872406892e-01L; }
/** ~0.159154943 `1 / 2pi` */
template<> inline constexpr long double const_inv_2pi       <long double>() { return 1.5915494309189533576888376337251436203446e-01L; }
/** ~1.772453851 `sqrt(pi)` */
template<> inline constexpr long double const_sqrtpi        <long double>() { return 1.7724538509055160272981674833411451827975e+00L; }
/** ~2.506628275 `sqrt(2pi)` */
template<> inline constexpr long double const_sqrt2pi       <long double>() { return 2.5066282746310005024157652848110452530070e+00L; }
/** ~0.564189584 `1 / sqrt(pi)` */
template<> inline constexpr long double const_inv_sqrtpi    <long double>() { return 5.6418958354775628694807945156077258584405e-01L; }
/** ~0.398942280 `1 / sqrt(2pi)` */
template<> inline constexpr long double const_inv_sqrt2pi   <long double>() { return 3.9894228040143267793994605993438186847586e-01L; }

/* Logarithms and Exponents */

/** ~2.718281828 Eulers number */
template<> inline constexpr long double const_e             <long double>() { return 2.7182818284590452353602874713526624977572e+00L; }
/** ~0.367879441 `1 / e` */
template<> inline constexpr long double const_inv_e         <long double>() { return 3.6787944117144232159552377016146086744581e-01L; }
/** ~0.693147181 `ln(2)` */
template<> inline constexpr long double const_ln2           <long double>() { return 6.9314718055994530941723212145817656807550e-01L; }
/** ~1.098612289 `ln(3)` */
template<> inline constexpr long double const_ln3           <long double>() { return 1.0986122886681096913952452369225257046475e+00L; }
/** ~2.302585093 `ln(10)` */
template<> inline constexpr long double const_ln10          <long double>() { return 2.3025850929940456840179914546843642076011e+00L; }
/** ~1.442695041 `log2(e)` */
template<> inline constexpr long double const_log2e         <long double>() { return 1.4426950408889634073599246810018921374266e+00L; }
/** ~0.910239227 `log3(e)` */
template<> inline constexpr long double const_log3e         <long double>() { return 9.1023922662683739361424016573610700061264e-01L; }
/** ~0.434294482 `log10(e)` */
template<> inline constexpr long double const_log10e        <long double>() { return 4.3429448190325182765112891891660508229440e-01L; }

/* Square Roots */

/** ~1.414213562 `sqrt(2)` */
template<> inline constexpr long double const_sqrt2         <long double>() { return 1.4142135623730950488016887242096980785697e+00L; }
/** ~1.732050808 `sqrt(3)` */
template<> inline constexpr long double const_sqrt3         <long double>() { return 1.7320508075688772935274463415058723669428e+00L; }
/** ~2.236067977 `sqrt(5)` */
template<> inline constexpr long double const_sqrt5         <long double>() { return 2.2360679774997896964091736687312762354406e+00L; }
/** ~2.449489743 `sqrt(6)` */
template<> inline constexpr long double const_sqrt6         <long double>() { return 2.4494897427831780981972840747058913919659e+00L; }
/** ~0.707106781 `1 / sqrt(2)` or `1/2 * sqrt(2)` */
template<> inline constexpr long double const_inv_sqrt2     <long double>() { return 7.0710678118654752440084436210484903928484e-01L; }
/** ~0.577350269 `1 / sqrt(3)` */
template<> inline constexpr long double const_inv_sqrt3     <long double>() { return 5.7735026918962576450914878050195745564760e-01L; }
/** ~0.447213595 `1 / sqrt(5)` */
template<> inline constexpr long double const_inv_sqrt5     <long double>() { return 4.4721359549995793928183473374625524708812e-01L; }
/** ~0.408248290 `1 / sqrt(6)` */
template<> inline constexpr long double const_inv_sqrt6     <long double>() { return 4.0824829046386301636621401245098189866099e-01L; }

/* Cube Roots */

/** ~1.259921050 `cbrt(2)` */
template<> inline constexpr long double const_cbrt2         <long double>() { return 1.2599210498948731647672106072782283505703e+00L; }
/** ~1.442249570 `cbrt(3)` */
template<> inline constexpr long double const_cbrt3         <long double>() { return 1.4422495703074083823216383107801095883919e+00L; }
/** ~1.709975947 `cbrt(5)` */
template<> inline constexpr long double const_cbrt5         <long double>() { return 1.7099759466766969893531088725438601098681e+00L; }
/** ~1.817120593 `cbrt(6)` */
template<> inline constexpr long double const_cbrt6         <long double>() { return 1.8171205928321396588912117563272605024282e+00L; }
/** ~0.793700526 `1 / cbrt(2)` */
template<> inline constexpr long double const_inv_cbrt2     <long double>() { return 7.9370052598409973737585281963615413019575e-01L; }
/** ~0.693361274 `1 / cbrt(3)` */
template<> inline constexpr long double const_inv_cbrt3     <long double>() { return 6.9336127435063470484335227478596179544594e-01L; }
/** ~0.584803548 `1 / cbrt(5)` */
template<> inline constexpr long double const_inv_cbrt5     <long double>() { return 5.8480354764257321310135747202758455570610e-01L; }
/** ~0.550321208 `1 / cbrt(6)` */
template<> inline constexpr long double const_inv_cbrt6     <long double>() { return 5.5032120814910444731243499206818082614115e-01L; }

/* Additional Mathematical Constants */

/** ~0.577215665 Euler-Mascheroni constant */
template<> inline constexpr long double const_egamma        <long double>() { return 5.7721566490153286060651209008240243104216e-01L; }
/** ~1.618033989 Golden Ratio */
template<> inline constexpr long double const_phi           <long double>() { return 1.6180339887498948482045868343656381177203e+00L; }
/** ~1.839286755 */
template<> inline constexpr long double const_tribonacci    <long double>() { return 1.8392867552141611325518525646532866004242e+00L; }
/** ~0.543689013 `1 / tribonacci` */
template<> inline constexpr long double const_inv_tribonacci<long double>() { return 5.4368901269207636157085597180174798652520e-01L; }
/** ~0.915965594 */
template<> inline constexpr long double const_catalan       <long double>() { return 9.1596559417721901505460351493238411077415e-01L; }
/** ~1.202056903 `zeta(3)` */
template<> inline constexpr long double const_apery         <long double>() { return 1.2020569031595942853997381615114499907650e+00L; }
/** ~0.596347362 `-e * eint(-1)` */
template<> inline constexpr long double const_gompertz      <long double>() { return 5.9634736232319407434107849936927937607418e-01L; }
/** ~2.622057554 */
template<> inline constexpr long double const_lemniscate    <long double>() { return 2.6220575542921198104648395898911194136828e+00L; }
/** ~5.244115109 `2 * lemniscate` */
template<> inline constexpr long double const_2lemniscate   <long double>() { return 5.2441151085842396209296791797822388273655e+00L; }
/** ~1.311028777 `1/2 * lemniscate` */
template<> inline constexpr long double const_lemniscate2   <long double>() { return 1.3110287771460599052324197949455597068414e+00L; }

//------------------------------------------------------------------------------
// <double> Constants
//------------------------------------------------------------------------------

/* Multiples of pi*/

/** ~3.141592654 */
template<> inline constexpr double const_pi            <double>() { return 3.141592653589793238463e+00; }
/** ~6.283185307 `2 * pi` */
template<> inline constexpr double const_2pi           <double>() { return 6.283185307179586476925e+00; }
/** ~1.570796327 `1/2 * pi` */
template<> inline constexpr double const_pi2           <double>() { return 1.570796326794896619231e+00; }
/** ~0.785398163 `1/4 * pi` */
template<> inline constexpr double const_pi4           <double>() { return 7.853981633974483096157e-01; }
/** ~2.356194490 `3/4 * pi` */
template<> inline constexpr double const_3pi4          <double>() { return 2.356194490192344928847e+00; }
/** ~1.047197551 `1/3 * pi` */
template<> inline constexpr double const_pi3           <double>() { return 1.047197551196597746154e+00; }

/* Inverse and sqrt pi */

/** ~0.318309886 `1 / pi` */
template<> inline constexpr double const_inv_pi        <double>() { return 3.183098861837906715378e-01; }
/** ~0.159154943 `1 / 2pi` */
template<> inline constexpr double const_inv_2pi       <double>() { return 1.591549430918953357689e-01; }
/** ~1.772453851 `sqrt(pi)` */
template<> inline constexpr double const_sqrtpi        <double>() { return 1.772453850905516027298e+00; }
/** ~2.506628275 `sqrt(2pi)` */
template<> inline constexpr double const_sqrt2pi       <double>() { return 2.506628274631000502416e+00; }
/** ~0.564189584 `1 / sqrt(pi)` */
template<> inline constexpr double const_inv_sqrtpi    <double>() { return 5.641895835477562869481e-01; }
/** ~0.398942280 `1 / sqrt(2pi)` */
template<> inline constexpr double const_inv_sqrt2pi   <double>() { return 3.989422804014326779399e-01; }

/* Logarithms and Exponents */

/** ~2.718281828 Eulers number */
template<> inline constexpr double const_e             <double>() { return 2.718281828459045235360e+00; }
/** ~0.367879441 `1 / e` */
template<> inline constexpr double const_inv_e         <double>() { return 3.678794411714423215955e-01; }
/** ~0.693147181 `ln(2)` */
template<> inline constexpr double const_ln2           <double>() { return 6.931471805599453094172e-01; }
/** ~1.098612289 `ln(3)` */
template<> inline constexpr double const_ln3           <double>() { return 1.098612288668109691395e+00; }
/** ~2.302585093 `ln(10)` */
template<> inline constexpr double const_ln10          <double>() { return 2.302585092994045684018e+00; }
/** ~1.442695041 `log2(e)` */
template<> inline constexpr double const_log2e         <double>() { return 1.442695040888963407360e+00; }
/** ~0.910239227 `log3(e)` */
template<> inline constexpr double const_log3e         <double>() { return 9.102392266268373936142e-01; }
/** ~0.434294482 `log10(e)` */
template<> inline constexpr double const_log10e        <double>() { return 4.342944819032518276511e-01; }

/* Square Roots */

/** ~1.414213562 `sqrt(2)` */
template<> inline constexpr double const_sqrt2         <double>() { return 1.414213562373095048802e+00; }
/** ~1.732050808 `sqrt(3)` */
template<> inline constexpr double const_sqrt3         <double>() { return 1.732050807568877293527e+00; }
/** ~2.236067977 `sqrt(5)` */
template<> inline constexpr double const_sqrt5         <double>() { return 2.236067977499789696409e+00; }
/** ~2.449489743 `sqrt(6)` */
template<> inline constexpr double const_sqrt6         <double>() { return 2.449489742783178098197e+00; }
/** ~0.707106781 `1 / sqrt(2)` or `1/2 * sqrt(2)` */
template<> inline constexpr double const_inv_sqrt2     <double>() { return 7.071067811865475244008e-01; }
/** ~0.577350269 `1 / sqrt(3)` */
template<> inline constexpr double const_inv_sqrt3     <double>() { return 5.773502691896257645091e-01; }
/** ~0.447213595 `1 / sqrt(5)` */
template<> inline constexpr double const_inv_sqrt5     <double>() { return 4.472135954999579392818e-01; }
/** ~0.408248290 `1 / sqrt(6)` */
template<> inline constexpr double const_inv_sqrt6     <double>() { return 4.082482904638630163662e-01; }

/* Cube Roots */

/** ~1.259921050 `cbrt(2)` */
template<> inline constexpr double const_cbrt2         <double>() { return 1.259921049894873164767e+00; }
/** ~1.442249570 `cbrt(3)` */
template<> inline constexpr double const_cbrt3         <double>() { return 1.442249570307408382322e+00; }
/** ~1.709975947 `cbrt(5)` */
template<> inline constexpr double const_cbrt5         <double>() { return 1.709975946676696989353e+00; }
/** ~1.817120593 `cbrt(6)` */
template<> inline constexpr double const_cbrt6         <double>() { return 1.817120592832139658891e+00; }
/** ~0.793700526 `1 / cbrt(2)` */
template<> inline constexpr double const_inv_cbrt2     <double>() { return 7.937005259840997373759e-01; }
/** ~0.693361274 `1 / cbrt(3)` */
template<> inline constexpr double const_inv_cbrt3     <double>() { return 6.933612743506347048434e-01; }
/** ~0.584803548 `1 / cbrt(5)` */
template<> inline constexpr double const_inv_cbrt5     <double>() { return 5.848035476425732131014e-01; }
/** ~0.550321208 `1 / cbrt(6)` */
template<> inline constexpr double const_inv_cbrt6     <double>() { return 5.503212081491044473124e-01; }

/* Additional Mathematical Constants */

/** ~0.577215665 Euler-Mascheroni constant */
template<> inline constexpr double const_egamma        <double>() { return 5.772156649015328606065e-01; }
/** ~1.618033989 Golden Ratio */
template<> inline constexpr double const_phi           <double>() { return 1.618033988749894848205e+00; }
/** ~1.839286755 */
template<> inline constexpr double const_tribonacci    <double>() { return 1.839286755214161132552e+00; }
/** ~0.543689013 `1 / tribonacci` */
template<> inline constexpr double const_inv_tribonacci<double>() { return 5.436890126920763615709e-01; }
/** ~0.915965594 */
template<> inline constexpr double const_catalan       <double>() { return 9.159655941772190150546e-01; }
/** ~1.202056903 `zeta(3)` */
template<> inline constexpr double const_apery         <double>() { return 1.202056903159594285400e+00; }
/** ~0.596347362 `-e * eint(-1)` */
template<> inline constexpr double const_gompertz      <double>() { return 5.963473623231940743411e-01; }
/** ~2.622057554 */
template<> inline constexpr double const_lemniscate    <double>() { return 2.622057554292119810465e+00; }
/** ~5.244115109 `2 * lemniscate` */
template<> inline constexpr double const_2lemniscate   <double>() { return 5.244115108584239620930e+00; }
/** ~1.311028777 `1/2 * lemniscate` */
template<> inline constexpr double const_lemniscate2   <double>() { return 1.311028777146059905232e+00; }

//------------------------------------------------------------------------------
// <float> Constants
//------------------------------------------------------------------------------

/* Multiples of pi*/

/** ~3.141592654 */
template<> inline constexpr float const_pi            <float>() { return 3.14159265359e+00f; }
/** ~6.283185307 `2 * pi` */
template<> inline constexpr float const_2pi           <float>() { return 6.28318530718e+00f; }
/** ~1.570796327 `1/2 * pi` */
template<> inline constexpr float const_pi2           <float>() { return 1.57079632679e+00f; }
/** ~0.785398163 `1/4 * pi` */
template<> inline constexpr float const_pi4           <float>() { return 7.85398163397e-01f; }
/** ~2.356194490 `3/4 * pi` */
template<> inline constexpr float const_3pi4          <float>() { return 2.35619449019e+00f; }
/** ~1.047197551 `1/3 * pi` */
template<> inline constexpr float const_pi3           <float>() { return 1.04719755120e+00f; }

/* Inverse and sqrt pi */

/** ~0.318309886 `1 / pi` */
template<> inline constexpr float const_inv_pi        <float>() { return 3.18309886184e-01f; }
/** ~0.159154943 `1 / 2pi` */
template<> inline constexpr float const_inv_2pi       <float>() { return 1.59154943092e-01f; }
/** ~1.772453851 `sqrt(pi)` */
template<> inline constexpr float const_sqrtpi        <float>() { return 1.77245385091e+00f; }
/** ~2.506628275 `sqrt(2pi)` */
template<> inline constexpr float const_sqrt2pi       <float>() { return 2.50662827463e+00f; }
/** ~0.564189584 `1 / sqrt(pi)` */
template<> inline constexpr float const_inv_sqrtpi    <float>() { return 5.64189583548e-01f; }
/** ~0.398942280 `1 / sqrt(2pi)` */
template<> inline constexpr float const_inv_sqrt2pi   <float>() { return 3.98942280401e-01f; }

/* Logarithms and Exponents */

/** ~2.718281828 Eulers number */
template<> inline constexpr float const_e             <float>() { return 2.71828182846e+00f; }
/** ~0.367879441 `1 / e` */
template<> inline constexpr float const_inv_e         <float>() { return 3.67879441171e-01f; }
/** ~0.693147181 `ln(2)` */
template<> inline constexpr float const_ln2           <float>() { return 6.93147180560e-01f; }
/** ~1.098612289 `ln(3)` */
template<> inline constexpr float const_ln3           <float>() { return 1.09861228867e+00f; }
/** ~2.302585093 `ln(10)` */
template<> inline constexpr float const_ln10          <float>() { return 2.30258509299e+00f; }
/** ~1.442695041 `log2(e)` */
template<> inline constexpr float const_log2e         <float>() { return 1.44269504089e+00f; }
/** ~0.910239227 `log3(e)` */
template<> inline constexpr float const_log3e         <float>() { return 9.10239226627e-01f; }
/** ~0.434294482 `log10(e)` */
template<> inline constexpr float const_log10e        <float>() { return 4.34294481903e-01f; }

/* Square Roots */

/** ~1.414213562 `sqrt(2)` */
template<> inline constexpr float const_sqrt2         <float>() { return 1.41421356237e+00f; }
/** ~1.732050808 `sqrt(3)` */
template<> inline constexpr float const_sqrt3         <float>() { return 1.73205080757e+00f; }
/** ~2.236067977 `sqrt(5)` */
template<> inline constexpr float const_sqrt5         <float>() { return 2.23606797750e+00f; }
/** ~2.449489743 `sqrt(6)` */
template<> inline constexpr float const_sqrt6         <float>() { return 2.44948974278e+00f; }
/** ~0.707106781 `1 / sqrt(2)` or `1/2 * sqrt(2)` */
template<> inline constexpr float const_inv_sqrt2     <float>() { return 7.07106781187e-01f; }
/** ~0.577350269 `1 / sqrt(3)` */
template<> inline constexpr float const_inv_sqrt3     <float>() { return 5.77350269190e-01f; }
/** ~0.447213595 `1 / sqrt(5)` */
template<> inline constexpr float const_inv_sqrt5     <float>() { return 4.47213595500e-01f; }
/** ~0.408248290 `1 / sqrt(6)` */
template<> inline constexpr float const_inv_sqrt6     <float>() { return 4.08248290464e-01f; }

/* Cube Roots */

/** ~1.259921050 `cbrt(2)` */
template<> inline constexpr float const_cbrt2         <float>() { return 1.25992104989e+00f; }
/** ~1.442249570 `cbrt(3)` */
template<> inline constexpr float const_cbrt3         <float>() { return 1.44224957031e+00f; }
/** ~1.709975947 `cbrt(5)` */
template<> inline constexpr float const_cbrt5         <float>() { return 1.70997594668e+00f; }
/** ~1.817120593 `cbrt(6)` */
template<> inline constexpr float const_cbrt6         <float>() { return 1.81712059283e+00f; }
/** ~0.793700526 `1 / cbrt(2)` */
template<> inline constexpr float const_inv_cbrt2     <float>() { return 7.93700525984e-01f; }
/** ~0.693361274 `1 / cbrt(3)` */
template<> inline constexpr float const_inv_cbrt3     <float>() { return 6.93361274351e-01f; }
/** ~0.584803548 `1 / cbrt(5)` */
template<> inline constexpr float const_inv_cbrt5     <float>() { return 5.84803547643e-01f; }
/** ~0.550321208 `1 / cbrt(6)` */
template<> inline constexpr float const_inv_cbrt6     <float>() { return 5.50321208149e-01f; }

/* Additional Mathematical Constants */

/** ~0.577215665 Euler-Mascheroni constant */
template<> inline constexpr float const_egamma        <float>() { return 5.77215664902e-01f; }
/** ~1.618033989 Golden Ratio */
template<> inline constexpr float const_phi           <float>() { return 1.61803398875e+00f; }
/** ~1.839286755 */
template<> inline constexpr float const_tribonacci    <float>() { return 1.83928675521e+00f; }
/** ~0.543689013 `1 / tribonacci` */
template<> inline constexpr float const_inv_tribonacci<float>() { return 5.43689012692e-01f; }
/** ~0.915965594 */
template<> inline constexpr float const_catalan       <float>() { return 9.15965594177e-01f; }
/** ~1.202056903 `zeta(3)` */
template<> inline constexpr float const_apery         <float>() { return 1.20205690316e+00f; }
/** ~0.596347362 `-e * eint(-1)` */
template<> inline constexpr float const_gompertz      <float>() { return 5.96347362323e-01f; }
/** ~2.622057554 */
template<> inline constexpr float const_lemniscate    <float>() { return 2.62205755429e+00f; }
/** ~5.244115109 `2 * lemniscate` */
template<> inline constexpr float const_2lemniscate   <float>() { return 5.24411510858e+00f; }
/** ~1.311028777 `1/2 * lemniscate` */
template<> inline constexpr float const_lemniscate2   <float>() { return 1.31102877715e+00f; }

} /* LDF */

#endif /* LDF_CONSTANTS_HPP */
