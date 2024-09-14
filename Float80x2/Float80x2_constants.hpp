/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef FLOAT80X2_CONSTANTS_HPP
#define FLOAT80X2_CONSTANTS_HPP

#include "Float80x2_def.h"
#include "../LDF/LDF_constants.hpp"

namespace LDF {

/* Multiples of pi */

/** ~3.141592654 */
template<> inline constexpr Float80x2 const_pi<Float80x2>() { return {
	+3.1415926535897932385128e+00L,
	-5.0165576126683320234518e-20L
}; }

/** ~6.283185307 `2 * pi` */
template<> inline constexpr Float80x2 const_2pi<Float80x2>() { return {
	+6.2831853071795864770256e+00L,
	-1.0033115225336664046904e-19L
}; }

/** ~1.570796327 `1/2 * pi` */
template<> inline constexpr Float80x2 const_pi2<Float80x2>() { return {
	+1.5707963267948966192564e+00L,
	-2.5082788063341660117259e-20L
}; }

/** ~0.785398163 `1/4 * pi` */
template<> inline constexpr Float80x2 const_pi4<Float80x2>() { return {
	+7.8539816339744830962820e-01L,
	-1.2541394031670830058629e-20L
}; }

/** ~2.356194490 `3/4 * pi` */
template<> inline constexpr Float80x2 const_3pi4<Float80x2>() { return {
	+2.3561944901923449289388e+00L,
	-9.1834290719287711875526e-20L
}; }

/** ~1.047197551 `1/3 * pi` */
template<> inline constexpr Float80x2 const_pi3<Float80x2>() { return {
	+1.0471975511965977461348e+00L,
	+1.9418213707289041055409e-20L
}; }

/* Inverse and sqrt pi */

/** ~0.318309886 `1 / pi` */
template<> inline constexpr Float80x2 const_inv_pi<Float80x2>() { return {
	+3.1830988618379067153817e-01L,
	-4.0724457058147680354734e-22L
}; }

/** ~0.159154943 `1 / 2pi` */
template<> inline constexpr Float80x2 const_inv_2pi<Float80x2>() { return {
	+1.5915494309189533576909e-01L,
	-2.0362228529073840177367e-22L
}; }

/** ~1.772453851 `sqrt(pi)` */
template<> inline constexpr Float80x2 const_sqrtpi<Float80x2>() { return {
	+1.7724538509055160273109e+00L,
	-1.2771403532824794589002e-20L
}; }

/** ~2.506628275 `sqrt(2pi)` */
template<> inline constexpr Float80x2 const_sqrt2pi<Float80x2>() { return {
	+2.5066282746310005024714e+00L,
	-5.5632654541425731876540e-20L
}; }

/** ~0.564189584 `1 / sqrt(pi)` */
template<> inline constexpr Float80x2 const_inv_sqrtpi<Float80x2>() { return {
	+5.6418958354775628692397e-01L,
	+2.4104490560134113047112e-20L
}; }

/** ~0.398942280 `1 / sqrt(2pi)` */
template<> inline constexpr Float80x2 const_inv_sqrt2pi<Float80x2>() { return {
	+3.9894228040143267792657e-01L,
	+1.3377944389301195729809e-20L
}; }

/* Logarithms and Exponents */

/** ~2.718281828 Eulers number */
template<> inline constexpr Float80x2 const_e<Float80x2>() { return {
	+2.7182818284590452354282e+00L,
	-6.7880636641277841169900e-20L
}; }

/** ~0.367879441 `1 / e` */
template<> inline constexpr Float80x2 const_inv_e<Float80x2>() { return {
	+3.6787944117144232158306e-01L,
	+1.2466256482800212513333e-20L
}; }

/** ~0.693147181 `ln(2)` */
template<> inline constexpr Float80x2 const_ln2<Float80x2>() { return {
	+6.9314718055994530942869e-01L,
	-1.1458352726798732810946e-20L
}; }

/** ~1.098612289 `ln(3)` */
template<> inline constexpr Float80x2 const_ln3<Float80x2>() { return {
	+1.0986122886681096913605e+00L,
	+3.4749487021420704258158e-20L
}; }

/** ~2.302585093 `ln(10)` */
template<> inline constexpr Float80x2 const_ln10<Float80x2>() { return {
	+2.3025850929940456840363e+00L,
	-1.8347406626957372104707e-20L
}; }

/** ~1.442695041 `log2(e)` */
template<> inline constexpr Float80x2 const_log2e<Float80x2>() { return {
	+1.4426950408889634073877e+00L,
	-2.7727101796451309784544e-20L
}; }

/** ~0.910239227 `log3(e)` */
template<> inline constexpr Float80x2 const_log3e<Float80x2>() { return {
	+9.1023922662683739363658e-01L,
	-2.2339144027483117042400e-20L
}; }

/** ~0.434294482 `log10(e)` */
template<> inline constexpr Float80x2 const_log10e<Float80x2>() { return {
	+4.3429448190325182764548e-01L,
	+5.6495057519187047812683e-21L
}; }

/* Square Roots */

/** ~1.414213562 `sqrt(2)` */
template<> inline constexpr Float80x2 const_sqrt2<Float80x2>() { return {
	+1.4142135623730950487638e+00L,
	+3.7900651177865141592425e-20L
}; }

/** ~1.732050808 `sqrt(3)` */
template<> inline constexpr Float80x2 const_sqrt3<Float80x2>() { return {
	+1.7320508075688772935737e+00L,
	-4.6278954088684061171349e-20L
}; }

/** ~2.236067977 `sqrt(5)` */
template<> inline constexpr Float80x2 const_sqrt5<Float80x2>() { return {
	+2.2360679774997896964144e+00L,
	-5.2463906025733864669684e-21L
}; }

/** ~2.449489743 `sqrt(6)` */
template<> inline constexpr Float80x2 const_sqrt6<Float80x2>() { return {
	+2.4494897427831780981761e+00L,
	+2.1217313223730009519262e-20L
}; }

/** ~0.707106781 `1 / sqrt(2)` or `1/2 * sqrt(2)` */
template<> inline constexpr Float80x2 const_inv_sqrt2<Float80x2>() { return {
	+7.0710678118654752438189e-01L,
	+1.8950325588932570796213e-20L
}; }

/** ~0.577350269 `1 / sqrt(3)` */
template<> inline constexpr Float80x2 const_inv_sqrt3<Float80x2>() { return {
	+5.7735026918962576450651e-01L,
	+2.6437181785303868431917e-21L
}; }

/** ~0.447213595 `1 / sqrt(5)` */
template<> inline constexpr Float80x2 const_inv_sqrt5<Float80x2>() { return {
	+4.4721359549995793927746e-01L,
	+4.3717327419128448764967e-21L
}; }

/** ~0.408248290 `1 / sqrt(6)` */
template<> inline constexpr Float80x2 const_inv_sqrt6<Float80x2>() { return {
	+4.0824829046386301636268e-01L,
	+3.5362188706216682532103e-21L
}; }

/* Cube Roots */

/** ~1.259921050 `cbrt(2)` */
template<> inline constexpr Float80x2 const_cbrt2<Float80x2>() { return {
	+1.2599210498948731647541e+00L,
	+1.3098169398487768067957e-20L
}; }

/** ~1.442249570 `cbrt(3)` */
template<> inline constexpr Float80x2 const_cbrt3<Float80x2>() { return {
	+1.4422495703074083823287e+00L,
	-7.0946545361107274067817e-21L
}; }

/** ~1.709975947 `cbrt(5)` */
template<> inline constexpr Float80x2 const_cbrt5<Float80x2>() { return {
	+1.7099759466766969893611e+00L,
	-8.0238887875586957714544e-21L
}; }

/** ~1.817120593 `cbrt(6)` */
template<> inline constexpr Float80x2 const_cbrt6<Float80x2>() { return {
	+1.8171205928321396589091e+00L,
	-1.7855458348753643451699e-20L
}; }

/** ~0.793700526 `1 / cbrt(2)` */
template<> inline constexpr Float80x2 const_inv_cbrt2<Float80x2>() { return {
	+7.9370052598409973740236e-01L,
	-2.6512129465342319460790e-20L
}; }

/** ~0.693361274 `1 / cbrt(3)` */
template<> inline constexpr Float80x2 const_inv_cbrt3<Float80x2>() { return {
	+6.9336127435063470484094e-01L,
	+2.4137145085538083589401e-21L
}; }

/** ~0.584803548 `1 / cbrt(5)` */
template<> inline constexpr Float80x2 const_inv_cbrt5<Float80x2>() { return {
	+5.8480354764257321312747e-01L,
	-2.6110151956461430002286e-20L
}; }

/** ~0.550321208 `1 / cbrt(6)` */
template<> inline constexpr Float80x2 const_inv_cbrt6<Float80x2>() { return {
	+5.5032120814910444729726e-01L,
	+1.5171804712882384524597e-20L
}; }

/* Additional Mathematical Constants */

/** ~0.577215665 Euler-Mascheroni constant */
template<> inline constexpr Float80x2 const_egamma<Float80x2>() { return {
	+5.7721566490153286061631e-01L,
	-9.7952676215999254707228e-21L
}; }

/** ~1.618033989 Golden Ratio */
template<> inline constexpr Float80x2 const_phi<Float80x2>() { return {
	+1.6180339887498948482072e+00L,
	-2.6231953012866932334842e-21L
}; }

/** ~1.839286755 */
template<> inline constexpr Float80x2 const_tribonacci<Float80x2>() { return {
	+1.8392867552141611326051e+00L,
	-5.3263702049507236461251e-20L
}; }

/** ~0.543689013 `1 / tribonacci` */
template<> inline constexpr Float80x2 const_inv_tribonacci<Float80x2>() { return {
	+5.4368901269207636154767e-01L,
	+2.3185645033592240202527e-20L
}; }

/** ~0.915965594 */
template<> inline constexpr Float80x2 const_catalan<Float80x2>() { return {
	+9.1596559417721901504754e-01L,
	+7.0609264399933192305788e-21L
}; }

/** ~1.202056903 `zeta(3)` */
template<> inline constexpr Float80x2 const_apery<Float80x2>() { return {
	+1.2020569031595942854299e+00L,
	-3.0187658052384475188113e-20L
}; }

/** ~0.596347362 `-e * eint(-1)` */
template<> inline constexpr Float80x2 const_gompertz<Float80x2>() { return {
	+5.9634736232319407434575e-01L,
	-4.6744802907830888984162e-21L
}; }

/** ~2.622057554 */
template<> inline constexpr Float80x2 const_lemniscate<Float80x2>() { return {
	+2.6220575542921198105087e+00L,
	-4.3848148457379483128864e-20L
}; }

/** ~5.244115109 `2 * lemniscate` */
template<> inline constexpr Float80x2 const_2lemniscate<Float80x2>() { return {
	+5.2441151085842396210174e+00L,
	-8.7696296914758966257728e-20L
}; }

/** ~1.311028777 `1/2 * lemniscate` */
template<> inline constexpr Float80x2 const_lemniscate2<Float80x2>() { return {
	+1.3110287771460599052543e+00L,
	-2.1924074228689741564432e-20L
}; }

}

#endif /* FLOAT80X2_CONSTANTS_HPP */
