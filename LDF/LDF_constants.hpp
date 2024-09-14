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
 */

namespace LDF {

template<typename T> struct constants {

static constexpr T C_pi             {}; /**< ~3.141592654 */
static constexpr T C_2pi            {}; /**< ~6.283185307 `2 * pi` */
static constexpr T C_pi2            {}; /**< ~1.570796327 `1/2 * pi` */
static constexpr T C_pi4            {}; /**< ~0.785398163 `1/4 * pi` */
static constexpr T C_3pi4           {}; /**< ~2.356194490 `3/4 * pi` */
static constexpr T C_pi3            {}; /**< ~1.047197551 `1/3 * pi` */

/* Inverse and sqrt pi */

static constexpr T C_inv_pi         {}; /**< ~0.318309886 `1 / pi` */
static constexpr T C_inv_2pi        {}; /**< ~0.159154943 `1 / 2pi` */
static constexpr T C_sqrtpi         {}; /**< ~1.772453851 `sqrt(pi)` */
static constexpr T C_sqrt2pi        {}; /**< ~2.506628275 `sqrt(2pi)` */
static constexpr T C_inv_sqrtpi     {}; /**< ~0.564189584 `1 / sqrt(pi)` */
static constexpr T C_inv_sqrt2pi    {}; /**< ~0.398942280 `1 / sqrt(2pi)` */

/* Logarithms and Exponents */

static constexpr T C_e              {}; /**< ~2.718281828 Eulers number */
static constexpr T C_inv_e          {}; /**< ~0.367879441 `1 / e` */
static constexpr T C_ln2            {}; /**< ~0.693147181 `ln(2)` */
static constexpr T C_ln3            {}; /**< ~1.098612289 `ln(3)` */
static constexpr T C_ln10           {}; /**< ~2.302585093 `ln(10)` */
static constexpr T C_log2e          {}; /**< ~1.442695041 `log2(e)` */
static constexpr T C_log3e          {}; /**< ~0.910239227 `log3(e)` */
static constexpr T C_log10e         {}; /**< ~0.434294482 `log10(e)` */

/* Square Roots */

static constexpr T C_sqrt2          {}; /**< ~1.414213562 `sqrt(2)` */
static constexpr T C_sqrt3          {}; /**< ~1.732050808 `sqrt(3)` */
static constexpr T C_sqrt5          {}; /**< ~2.236067977 `sqrt(5)` */
static constexpr T C_sqrt6          {}; /**< ~2.449489743 `sqrt(6)` */
static constexpr T C_inv_sqrt2      {}; /**< ~0.707106781 `1 / sqrt(2)` or `1/2 * sqrt(2)` */
static constexpr T C_inv_sqrt3      {}; /**< ~0.577350269 `1 / sqrt(3)` */
static constexpr T C_inv_sqrt5      {}; /**< ~0.447213595 `1 / sqrt(5)` */
static constexpr T C_inv_sqrt6      {}; /**< ~0.408248290 `1 / sqrt(6)` */

/* Cube Roots */

static constexpr T C_cbrt2          {}; /**< ~1.259921050 `cbrt(2)` */
static constexpr T C_cbrt3          {}; /**< ~1.442249570 `cbrt(3)` */
static constexpr T C_cbrt5          {}; /**< ~1.709975947 `cbrt(5)` */
static constexpr T C_cbrt6          {}; /**< ~1.817120593 `cbrt(6)` */
static constexpr T C_inv_cbrt2      {}; /**< ~0.793700526 `1 / cbrt(2)` */
static constexpr T C_inv_cbrt3      {}; /**< ~0.693361274 `1 / cbrt(3)` */
static constexpr T C_inv_cbrt5      {}; /**< ~0.584803548 `1 / cbrt(5)` */
static constexpr T C_inv_cbrt6      {}; /**< ~0.550321208 `1 / cbrt(6)` */

/* Additional Mathematical Constants */

static constexpr T C_egamma         {}; /**< ~0.577215665 Euler-Mascheroni constant */
static constexpr T C_phi            {}; /**< ~1.618033989 Golden Ratio */
static constexpr T C_tribonacci     {}; /**< ~1.839286755 */
static constexpr T C_inv_tribonacci {}; /**< ~0.543689013 `1 / tribonacci` */
static constexpr T C_catalan        {}; /**< ~0.915965594 */
static constexpr T C_apery          {}; /**< ~1.202056903 `zeta(3)` */
static constexpr T C_gompertz       {}; /**< ~0.596347362 `-e * eint(-1)` */
static constexpr T C_lemniscate     {}; /**< ~2.622057554 */
static constexpr T C_2lemniscate    {}; /**< ~5.244115109 `2 * lemniscate` */
static constexpr T C_lemniscate2    {}; /**< ~1.311028777 `1/2 * lemniscate` */
static constexpr T C_gauss          {}; /**< ~0.834626842 `lemniscate / pi` */

};

//------------------------------------------------------------------------------
// <long double> Constants
//------------------------------------------------------------------------------

template<> struct constants<long double> {

/* Multiples of pi*/

static constexpr long double C_pi             = 3.1415926535897932384626433832795028841972e+00L; /**< ~3.141592654 */
static constexpr long double C_2pi            = 6.2831853071795864769252867665590057683943e+00L; /**< ~6.283185307 `2 * pi` */
static constexpr long double C_pi2            = 1.5707963267948966192313216916397514420986e+00L; /**< ~1.570796327 `1/2 * pi` */
static constexpr long double C_pi4            = 7.8539816339744830961566084581987572104929e-01L; /**< ~0.785398163 `1/4 * pi` */
static constexpr long double C_3pi4           = 2.3561944901923449288469825374596271631479e+00L; /**< ~2.356194490 `3/4 * pi` */
static constexpr long double C_pi3            = 1.0471975511965977461542144610931676280657e+00L; /**< ~1.047197551 `1/3 * pi` */

/* Inverse and sqrt pi */

static constexpr long double C_inv_pi         = 3.1830988618379067153776752674502872406892e-01L; /**< ~0.318309886 `1 / pi` */
static constexpr long double C_inv_2pi        = 1.5915494309189533576888376337251436203446e-01L; /**< ~0.159154943 `1 / 2pi` */
static constexpr long double C_sqrtpi         = 1.7724538509055160272981674833411451827975e+00L; /**< ~1.772453851 `sqrt(pi)` */
static constexpr long double C_sqrt2pi        = 2.5066282746310005024157652848110452530070e+00L; /**< ~2.506628275 `sqrt(2pi)` */
static constexpr long double C_inv_sqrtpi     = 5.6418958354775628694807945156077258584405e-01L; /**< ~0.564189584 `1 / sqrt(pi)` */
static constexpr long double C_inv_sqrt2pi    = 3.9894228040143267793994605993438186847586e-01L; /**< ~0.398942280 `1 / sqrt(2pi)` */

/* Logarithms and Exponents */

static constexpr long double C_e              = 2.7182818284590452353602874713526624977572e+00L; /**< ~2.718281828 Eulers number */
static constexpr long double C_inv_e          = 3.6787944117144232159552377016146086744581e-01L; /**< ~0.367879441 `1 / e` */
static constexpr long double C_ln2            = 6.9314718055994530941723212145817656807550e-01L; /**< ~0.693147181 `ln(2)` */
static constexpr long double C_ln3            = 1.0986122886681096913952452369225257046475e+00L; /**< ~1.098612289 `ln(3)` */
static constexpr long double C_ln10           = 2.3025850929940456840179914546843642076011e+00L; /**< ~2.302585093 `ln(10)` */
static constexpr long double C_log2e          = 1.4426950408889634073599246810018921374266e+00L; /**< ~1.442695041 `log2(e)` */
static constexpr long double C_log3e          = 9.1023922662683739361424016573610700061264e-01L; /**< ~0.910239227 `log3(e)` */
static constexpr long double C_log10e         = 4.3429448190325182765112891891660508229440e-01L; /**< ~0.434294482 `log10(e)` */

/* Square Roots */

static constexpr long double C_sqrt2          = 1.4142135623730950488016887242096980785697e+00L; /**< ~1.414213562 `sqrt(2)` */
static constexpr long double C_sqrt3          = 1.7320508075688772935274463415058723669428e+00L; /**< ~1.732050808 `sqrt(3)` */
static constexpr long double C_sqrt5          = 2.2360679774997896964091736687312762354406e+00L; /**< ~2.236067977 `sqrt(5)` */
static constexpr long double C_sqrt6          = 2.4494897427831780981972840747058913919659e+00L; /**< ~2.449489743 `sqrt(6)` */
static constexpr long double C_inv_sqrt2      = 7.0710678118654752440084436210484903928484e-01L; /**< ~0.707106781 `1 / sqrt(2)` or `1/2 * sqrt(2)` */
static constexpr long double C_inv_sqrt3      = 5.7735026918962576450914878050195745564760e-01L; /**< ~0.577350269 `1 / sqrt(3)` */
static constexpr long double C_inv_sqrt5      = 4.4721359549995793928183473374625524708812e-01L; /**< ~0.447213595 `1 / sqrt(5)` */
static constexpr long double C_inv_sqrt6      = 4.0824829046386301636621401245098189866099e-01L; /**< ~0.408248290 `1 / sqrt(6)` */

/* Cube Roots */

static constexpr long double C_cbrt2          = 1.2599210498948731647672106072782283505703e+00L; /**< ~1.259921050 `cbrt(2)` */
static constexpr long double C_cbrt3          = 1.4422495703074083823216383107801095883919e+00L; /**< ~1.442249570 `cbrt(3)` */
static constexpr long double C_cbrt5          = 1.7099759466766969893531088725438601098681e+00L; /**< ~1.709975947 `cbrt(5)` */
static constexpr long double C_cbrt6          = 1.8171205928321396588912117563272605024282e+00L; /**< ~1.817120593 `cbrt(6)` */
static constexpr long double C_inv_cbrt2      = 7.9370052598409973737585281963615413019575e-01L; /**< ~0.793700526 `1 / cbrt(2)` */
static constexpr long double C_inv_cbrt3      = 6.9336127435063470484335227478596179544594e-01L; /**< ~0.693361274 `1 / cbrt(3)` */
static constexpr long double C_inv_cbrt5      = 5.8480354764257321310135747202758455570610e-01L; /**< ~0.584803548 `1 / cbrt(5)` */
static constexpr long double C_inv_cbrt6      = 5.5032120814910444731243499206818082614115e-01L; /**< ~0.550321208 `1 / cbrt(6)` */

/* Additional Mathematical Constants */

static constexpr long double C_egamma         = 5.7721566490153286060651209008240243104216e-01L; /**< ~0.577215665 Euler-Mascheroni constant */
static constexpr long double C_phi            = 1.6180339887498948482045868343656381177203e+00L; /**< ~1.618033989 Golden Ratio */
static constexpr long double C_tribonacci     = 1.8392867552141611325518525646532866004242e+00L; /**< ~1.839286755 */
static constexpr long double C_inv_tribonacci = 5.4368901269207636157085597180174798652520e-01L; /**< ~0.543689013 `1 / tribonacci` */
static constexpr long double C_catalan        = 9.1596559417721901505460351493238411077415e-01L; /**< ~0.915965594 */
static constexpr long double C_apery          = 1.2020569031595942853997381615114499907650e+00L; /**< ~1.202056903 `zeta(3)` */
static constexpr long double C_gompertz       = 5.9634736232319407434107849936927937607418e-01L; /**< ~0.596347362 `-e * eint(-1)` */
static constexpr long double C_lemniscate     = 2.6220575542921198104648395898911194136828e+00L; /**< ~2.622057554 */
static constexpr long double C_2lemniscate    = 5.2441151085842396209296791797822388273655e+00L; /**< ~5.244115109 `2 * lemniscate` */
static constexpr long double C_lemniscate2    = 1.3110287771460599052324197949455597068414e+00L; /**< ~1.311028777 `1/2 * lemniscate` */
static constexpr long double C_gauss          = 8.3462684167407318628142973279904680899399e-01L; /**< ~0.834626842 `lemniscate / pi` */

};

//------------------------------------------------------------------------------
// <double> Constants
//------------------------------------------------------------------------------

template<> struct constants<double> {



};

//------------------------------------------------------------------------------
// <float> Constants
//------------------------------------------------------------------------------

template<> struct constants<float> {

};

} /* LDF */

#endif /* LDF_CONSTANTS_HPP */
