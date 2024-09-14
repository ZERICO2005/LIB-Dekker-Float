/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef FLOAT128X2_CONSTANTS_HPP
#define FLOAT128X2_CONSTANTS_HPP

#include "Float128x2_def.h"
#include "../LDF/LDF_constants.hpp"

namespace LDF {

/* Multiples of pi */

/** ~3.141592654 */
template<> inline constexpr Float128x2 const_pi<Float128x2>() { return {
	+3.141592653589793238462643383279502797e+00Q,
	+8.671810130123781024797044026043352254e-35Q
}; }

/** ~6.283185307 `2 * pi` */
template<> inline constexpr Float128x2 const_2pi<Float128x2>() { return {
	+6.283185307179586476925286766559005595e+00Q,
	+1.734362026024756204959408805208670451e-34Q
}; }

/** ~1.570796327 `1/2 * pi` */
template<> inline constexpr Float128x2 const_pi2<Float128x2>() { return {
	+1.570796326794896619231321691639751399e+00Q,
	+4.335905065061890512398522013021676127e-35Q
}; }

/** ~0.785398163 `1/4 * pi` */
template<> inline constexpr Float128x2 const_pi4<Float128x2>() { return {
	+7.853981633974483096156608458198756994e-01Q,
	+2.167952532530945256199261006510838064e-35Q
}; }

/** ~2.356194490 `3/4 * pi` */
template<> inline constexpr Float128x2 const_3pi4<Float128x2>() { return {
	+2.356194490192344928846982537459627098e+00Q,
	+6.503857597592835768597783019532514191e-35Q
}; }

/** ~1.047197551 `1/3 * pi` */
template<> inline constexpr Float128x2 const_pi3<Float128x2>() { return {
	+1.047197551196597746154214461093167663e+00Q,
	-3.529163104582859168587578466601973644e-35Q
}; }

/* Inverse and sqrt pi */

/** ~0.318309886 `1 / pi` */
template<> inline constexpr Float128x2 const_inv_pi<Float128x2>() { return {
	+3.183098861837906715377675267450287370e-01Q,
	-1.288215887632060061256938647831274818e-35Q
}; }

/** ~0.159154943 `1 / 2pi` */
template<> inline constexpr Float128x2 const_inv_2pi<Float128x2>() { return {
	+1.591549430918953357688837633725143685e-01Q,
	-6.441079438160300306284693239156374092e-36Q
}; }

/** ~1.772453851 `sqrt(pi)` */
template<> inline constexpr Float128x2 const_sqrtpi<Float128x2>() { return {
	+1.772453850905516027298167483341145140e+00Q,
	+4.231747027652216542435915821915863222e-35Q
}; }

/** ~2.506628275 `sqrt(2pi)` */
template<> inline constexpr Float128x2 const_sqrt2pi<Float128x2>() { return {
	+2.506628274631000502415765284811045280e+00Q,
	-2.680391201114639692877906820723620075e-35Q
}; }

/** ~0.564189584 `1 / sqrt(pi)` */
template<> inline constexpr Float128x2 const_inv_sqrtpi<Float128x2>() { return {
	+5.641895835477562869480794515607726315e-01Q,
	-4.569123539596073955209741677327511981e-35Q
}; }

/** ~0.398942280 `1 / sqrt(2pi)` */
template<> inline constexpr Float128x2 const_inv_sqrt2pi<Float128x2>() { return {
	+3.989422804014326779399460599343818739e-01Q,
	-5.454804505195824333687850000431337767e-36Q
}; }

/* Logarithms and Exponents */

/** ~2.718281828 Eulers number */
template<> inline constexpr Float128x2 const_e<Float128x2>() { return {
	+2.718281828459045235360287471352662314e+00Q,
	+1.833988252265064107122977367673964162e-34Q
}; }

/** ~0.367879441 `1 / e` */
template<> inline constexpr Float128x2 const_inv_e<Float128x2>() { return {
	+3.678794411714423215955237701614608727e-01Q,
	-5.225501791103472792032999500282608799e-36Q
}; }

/** ~0.693147181 `ln(2)` */
template<> inline constexpr Float128x2 const_ln2<Float128x2>() { return {
	+6.931471805599453094172321214581765751e-01Q,
	-7.008139474549585163412662008771626205e-36Q
}; }

/** ~1.098612289 `ln(3)` */
template<> inline constexpr Float128x2 const_ln3<Float128x2>() { return {
	+1.098612288668109691395245236922525611e+00Q,
	+9.382132487657827240516680942300219206e-35Q
}; }

/** ~2.302585093 `ln(10)` */
template<> inline constexpr Float128x2 const_ln10<Float128x2>() { return {
	+2.302585092994045684017991454684364177e+00Q,
	+3.057325634784946343591167409176082282e-35Q
}; }

/** ~1.442695041 `log2(e)` */
template<> inline constexpr Float128x2 const_log2e<Float128x2>() { return {
	+1.442695040888963407359924681001892043e+00Q,
	+9.409197102061571073516182880930655469e-35Q
}; }

/** ~0.910239227 `log3(e)` */
template<> inline constexpr Float128x2 const_log3e<Float128x2>() { return {
	+9.102392266268373936142401657361070287e-01Q,
	-2.805854477507719651113956064172914701e-35Q
}; }

/** ~0.434294482 `log10(e)` */
template<> inline constexpr Float128x2 const_log10e<Float128x2>() { return {
	+4.342944819032518276511289189166050958e-01Q,
	-1.346786556635126620672947431532677272e-35Q
}; }

/* Square Roots */

/** ~1.414213562 `sqrt(2)` */
template<> inline constexpr Float128x2 const_sqrt2<Float128x2>() { return {
	+1.414213562373095048801688724209697984e+00Q,
	+9.422242548621832065692116736394105681e-35Q
}; }

/** ~1.732050808 `sqrt(3)` */
template<> inline constexpr Float128x2 const_sqrt3<Float128x2>() { return {
	+1.732050807568877293527446341505872322e+00Q,
	+4.478970793639917249561608804910760712e-35Q
}; }

/** ~2.236067977 `sqrt(5)` */
template<> inline constexpr Float128x2 const_sqrt5<Float128x2>() { return {
	+2.236067977499789696409173668731276319e+00Q,
	-8.395342752112953154706661872301378029e-35Q
}; }

/** ~2.449489743 `sqrt(6)` */
template<> inline constexpr Float128x2 const_sqrt6<Float128x2>() { return {
	+2.449489742783178098197284074705891241e+00Q,
	+1.511442143439295193862361326504602252e-34Q
}; }

/** ~0.707106781 `1 / sqrt(2)` or `1/2 * sqrt(2)` */
template<> inline constexpr Float128x2 const_inv_sqrt2<Float128x2>() { return {
	+7.071067811865475244008443621048489922e-01Q,
	+4.711121274310916032846058368197052841e-35Q
}; }

/** ~0.577350269 `1 / sqrt(3)` */
template<> inline constexpr Float128x2 const_inv_sqrt3<Float128x2>() { return {
	+5.773502691896257645091487805019574086e-01Q,
	+4.702873505192032171613832839278465614e-35Q
}; }

/** ~0.447213595 `1 / sqrt(5)` */
template<> inline constexpr Float128x2 const_inv_sqrt5<Float128x2>() { return {
	+4.472135954999579392818347337462552639e-01Q,
	-1.679068550422590630941332374460275699e-35Q
}; }

/** ~0.408248290 `1 / sqrt(6)` */
template<> inline constexpr Float128x2 const_inv_sqrt6<Float128x2>() { return {
	+4.082482904638630163662140124509819056e-01Q,
	-6.908130015799010986560276934672084061e-36Q
}; }

/* Cube Roots */

/** ~1.259921050 `cbrt(2)` */
template<> inline constexpr Float128x2 const_cbrt2<Float128x2>() { return {
	+1.259921049894873164767210607278228341e+00Q,
	+9.815843422019372987681140490626648781e-36Q
}; }

/** ~1.442249570 `cbrt(3)` */
template<> inline constexpr Float128x2 const_cbrt3<Float128x2>() { return {
	+1.442249570307408382321638310780109510e+00Q,
	+7.805467924059426666369609628580936088e-35Q
}; }

/** ~1.709975947 `cbrt(5)` */
template<> inline constexpr Float128x2 const_cbrt5<Float128x2>() { return {
	+1.709975946676696989353108872543860080e+00Q,
	+3.024571962938070519945328763907699129e-35Q
}; }

/** ~1.817120593 `cbrt(6)` */
template<> inline constexpr Float128x2 const_cbrt6<Float128x2>() { return {
	+1.817120592832139658891211756327260503e+00Q,
	-6.847058546194121085132615207992685754e-37Q
}; }

/** ~0.793700526 `1 / cbrt(2)` */
template<> inline constexpr Float128x2 const_inv_cbrt2<Float128x2>() { return {
	+7.937005259840997373758528196361541426e-01Q,
	-1.243438826101202309289918335982059513e-35Q
}; }

/** ~0.693361274 `1 / cbrt(3)` */
template<> inline constexpr Float128x2 const_inv_cbrt3<Float128x2>() { return {
	+6.933612743506347048433522747859618196e-01Q,
	-2.417561658528918366769686903212646247e-35Q
}; }

/** ~0.584803548 `1 / cbrt(5)` */
template<> inline constexpr Float128x2 const_inv_cbrt5<Float128x2>() { return {
	+5.848035476425732131013574720275845878e-01Q,
	-3.205659516676612493465250668915285077e-35Q
}; }

/** ~0.550321208 `1 / cbrt(6)` */
template<> inline constexpr Float128x2 const_inv_cbrt6<Float128x2>() { return {
	+5.503212081491044473124349920681808073e-01Q,
	+1.880211334561702476187416356262882144e-35Q
}; }

/* Additional Mathematical Constants */

/** ~0.577215665 Euler-Mascheroni constant */
template<> inline constexpr Float128x2 const_egamma<Float128x2>() { return {
	+5.772156649015328606065120900824024707e-01Q,
	-3.961817963197208953458334713239101253e-35Q
}; }

/** ~1.618033989 Golden Ratio */
template<> inline constexpr Float128x2 const_phi<Float128x2>() { return {
	+1.618033988749894848204586834365638160e+00Q,
	-4.197671376056476577353330936150689014e-35Q
}; }

/** ~1.839286755 */
template<> inline constexpr Float128x2 const_tribonacci<Float128x2>() { return {
	+1.839286755214161132551852564653286694e+00Q,
	-9.317185790773198211678782012360155929e-35Q
}; }

/** ~0.543689013 `1 / tribonacci` */
template<> inline constexpr Float128x2 const_inv_tribonacci<Float128x2>() { return {
	+5.436890126920763615708559718017479640e-01Q,
	+2.249669026442333963027765624760093023e-35Q
}; }

/** ~0.915965594 */
template<> inline constexpr Float128x2 const_catalan<Float128x2>() { return {
	+9.159655941772190150546035149323841463e-01Q,
	-3.552859622869103700262328499098804065e-35Q
}; }

/** ~1.202056903 `zeta(3)` */
template<> inline constexpr Float128x2 const_apery<Float128x2>() { return {
	+1.202056903159594285399738161511449895e+00Q,
	+9.562380272527827486815909825205585044e-35Q
}; }

/** ~0.596347362 `-e * eint(-1)` */
template<> inline constexpr Float128x2 const_gompertz<Float128x2>() { return {
	+5.963473623231940743410784993692793761e-01Q,
	-1.078400903200283468695741331935299259e-38Q
}; }

/** ~2.622057554 */
template<> inline constexpr Float128x2 const_lemniscate<Float128x2>() { return {
	+2.622057554292119810464839589891119460e+00Q,
	-4.591821769645040520614838739605350282e-35Q
}; }

/** ~5.244115109 `2 * lemniscate` */
template<> inline constexpr Float128x2 const_2lemniscate<Float128x2>() { return {
	+5.244115108584239620929679179782238919e+00Q,
	-9.183643539290081041229677479210700563e-35Q
}; }

/** ~1.311028777 `1/2 * lemniscate` */
template<> inline constexpr Float128x2 const_lemniscate2<Float128x2>() { return {
	+1.311028777146059905232419794945559730e+00Q,
	-2.295910884822520260307419369802675141e-35Q
}; }

}

#endif /* FLOAT128X2_CONSTANTS_HPP */
