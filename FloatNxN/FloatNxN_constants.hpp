/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef FLOATNXN_CONSTANTS_HPP
#define FLOATNXN_CONSTANTS_HPP

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

/* LIB-Dekker-Float namespace */
namespace LDF {

/* Multiples of pi */
template<typename T> inline constexpr T const_pi         ; /**< ~3.141592654 */
template<typename T> inline constexpr T const_2pi        ; /**< ~6.283185307 */
template<typename T> inline constexpr T const_pi2        ; /**< ~1.570796327 */
template<typename T> inline constexpr T const_pi4        ; /**< ~0.785398163 */
template<typename T> inline constexpr T const_3pi4       ; /**< ~2.356194490 */
template<typename T> inline constexpr T const_pi3        ; /**< ~1.047197551 */

/* Inverse and sqrt pi */
template<typename T> inline constexpr T const_inv_pi     ; /**< ~0.318309886 */
template<typename T> inline constexpr T const_inv_2pi    ; /**< ~0.159154943 */
template<typename T> inline constexpr T const_sqrtpi     ; /**< ~1.772453851 */
template<typename T> inline constexpr T const_sqrt2pi    ; /**< ~2.506628275 */
template<typename T> inline constexpr T const_inv_sqrtpi ; /**< ~0.564189584 */
template<typename T> inline constexpr T const_inv_sqrt2pi; /**< ~0.398942280 */

/* Exponent and Logarithms */
template<typename T> inline constexpr T const_e          ; /**< ~2.718281828 */
template<typename T> inline constexpr T const_inv_e      ; /**< ~0.367879441 */
template<typename T> inline constexpr T const_ln2        ; /**< ~0.693147181 */
template<typename T> inline constexpr T const_ln3        ; /**< ~1.098612289 */
template<typename T> inline constexpr T const_ln10       ; /**< ~2.302585093 */
template<typename T> inline constexpr T const_log2e      ; /**< ~1.442695041 */
template<typename T> inline constexpr T const_log3e      ; /**< ~0.910239227 */
template<typename T> inline constexpr T const_log10e     ; /**< ~0.434294482 */

/* Square Roots */
template<typename T> inline constexpr T const_sqrt2      ; /**< ~1.414213562 */
template<typename T> inline constexpr T const_sqrt3      ; /**< ~1.732050808 */
template<typename T> inline constexpr T const_sqrt5      ; /**< ~2.236067977 */
template<typename T> inline constexpr T const_sqrt6      ; /**< ~2.449489743 */
template<typename T> inline constexpr T const_inv_sqrt2  ; /**< ~0.707106781 */
template<typename T> inline constexpr T const_inv_sqrt3  ; /**< ~0.577350269 */
template<typename T> inline constexpr T const_inv_sqrt5  ; /**< ~0.447213595 */
template<typename T> inline constexpr T const_inv_sqrt6  ; /**< ~0.408248290 */

/* Cube Roots */
template<typename T> inline constexpr T const_cbrt2      ; /**< ~1.414213562 */
template<typename T> inline constexpr T const_cbrt3      ; /**< ~1.732050808 */
template<typename T> inline constexpr T const_cbrt5      ; /**< ~2.236067977 */
template<typename T> inline constexpr T const_cbrt6      ; /**< ~2.449489743 */
template<typename T> inline constexpr T const_inv_cbrt2  ; /**< ~0.793700526 */
template<typename T> inline constexpr T const_inv_cbrt3  ; /**< ~0.693361274 */
template<typename T> inline constexpr T const_inv_cbrt5  ; /**< ~0.584803548 */
template<typename T> inline constexpr T const_inv_cbrt6  ; /**< ~0.550321208 */

/* Additional Mathematical Constants */
template<typename T> inline constexpr T const_egamma     ; /**< ~0.577215665 */
template<typename T> inline constexpr T const_phi        ; /**< ~1.618033989 */
template<typename T> inline constexpr T const_tribonacci ; /**< ~1.839286755 */
template<typename T> inline constexpr T const_catalan    ; /**< ~0.915965594 */
template<typename T> inline constexpr T const_apery      ; /**< ~1.202056903 */
template<typename T> inline constexpr T const_gompertz   ; /**< ~5.151464323 */
template<typename T> inline constexpr T const_gauss      ; /**< ~0.834626842 */
template<typename T> inline constexpr T const_lemniscate ; /**< ~2.622057554 */
template<typename T> inline constexpr T const_2lemniscate; /**< ~5.244115109 */
template<typename T> inline constexpr T const_lemniscate2; /**< ~1.311028777 */

}

//------------------------------------------------------------------------------
// <long double> Constants
//------------------------------------------------------------------------------

template<> inline constexpr long double LDF::const_pi          <long double> = 3.1415926535897932384626433832795028841972L;
template<> inline constexpr long double LDF::const_2pi         <long double> = 6.2831853071795864769252867665590057683943L;
template<> inline constexpr long double LDF::const_pi2         <long double> = 1.5707963267948966192313216916397514420986L;
template<> inline constexpr long double LDF::const_pi4         <long double> = 0.7853981633974483096156608458198757210493L;
template<> inline constexpr long double LDF::const_3pi4        <long double> = 2.3561944901923449288469825374596271631479L;
template<> inline constexpr long double LDF::const_pi3         <long double> = 1.0471975511965977461542144610931676280657L;

template<> inline constexpr long double LDF::const_inv_pi      <long double> = 0.3183098861837906715377675267450287240689L;
template<> inline constexpr long double LDF::const_inv_2pi     <long double> = 0.1591549430918953357688837633725143620345L;
template<> inline constexpr long double LDF::const_sqrtpi      <long double> = 1.7724538509055160272981674833411451827975L;
template<> inline constexpr long double LDF::const_sqrt2pi     <long double> = 2.5066282746310005024157652848110452530070L;
template<> inline constexpr long double LDF::const_inv_sqrtpi  <long double> = 0.5641895835477562869480794515607725858441L;
template<> inline constexpr long double LDF::const_inv_sqrt2pi <long double> = 0.3989422804014326779399460599343818684759L;

template<> inline constexpr long double LDF::const_e           <long double> = 2.7182818284590452353602874713526624977572L;
template<> inline constexpr long double LDF::const_inv_e       <long double> = 0.3678794411714423215955237701614608674458L;
template<> inline constexpr long double LDF::const_ln2         <long double> = 0.6931471805599453094172321214581765680755L;
template<> inline constexpr long double LDF::const_ln3         <long double> = 1.0986122886681096913952452369225257046475L;
template<> inline constexpr long double LDF::const_ln10        <long double> = 2.3025850929940456840179914546843642076011L;
template<> inline constexpr long double LDF::const_log2e       <long double> = 1.4426950408889634073599246810018921374266L;
template<> inline constexpr long double LDF::const_log3e       <long double> = 0.9102392266268373936142401657361070006126L;
template<> inline constexpr long double LDF::const_log10e      <long double> = 0.4342944819032518276511289189166050822944L;

template<> inline constexpr long double LDF::const_sqrt2       <long double> = 1.4142135623730950488016887242096980785697L;
template<> inline constexpr long double LDF::const_sqrt3       <long double> = 1.7320508075688772935274463415058723669428L;
template<> inline constexpr long double LDF::const_sqrt5       <long double> = 2.2360679774997896964091736687312762354406L;
template<> inline constexpr long double LDF::const_sqrt6       <long double> = 2.4494897427831780981972840747058913919659L;
template<> inline constexpr long double LDF::const_inv_sqrt2   <long double> = 0.7071067811865475244008443621048490392848L;
template<> inline constexpr long double LDF::const_inv_sqrt3   <long double> = 0.5773502691896257645091487805019574556476L;
template<> inline constexpr long double LDF::const_inv_sqrt5   <long double> = 0.4472135954999579392818347337462552470881L;
template<> inline constexpr long double LDF::const_inv_sqrt6   <long double> = 0.4082482904638630163662140124509818986610L;

template<> inline constexpr long double LDF::const_cbrt2       <long double> = 1.4142135623730950488016887242096980785697L;
template<> inline constexpr long double LDF::const_cbrt3       <long double> = 1.7320508075688772935274463415058723669428L;
template<> inline constexpr long double LDF::const_cbrt5       <long double> = 2.2360679774997896964091736687312762354406L;
template<> inline constexpr long double LDF::const_cbrt6       <long double> = 2.4494897427831780981972840747058913919659L;
template<> inline constexpr long double LDF::const_inv_cbrt2   <long double> = 0.7937005259840997373758528196361541301957L;
template<> inline constexpr long double LDF::const_inv_cbrt3   <long double> = 0.6933612743506347048433522747859617954459L;
template<> inline constexpr long double LDF::const_inv_cbrt5   <long double> = 0.5848035476425732131013574720275845557061L;
template<> inline constexpr long double LDF::const_inv_cbrt6   <long double> = 0.5503212081491044473124349920681808261411L;

template<> inline constexpr long double LDF::const_egamma      <long double> = 0.5772156649015328606065120900824024310422L;
template<> inline constexpr long double LDF::const_phi         <long double> = 1.6180339887498948482045868343656381177203L;
template<> inline constexpr long double LDF::const_tribonacci  <long double> = 1.8392867552141611325518525646532866004242L;
template<> inline constexpr long double LDF::const_catalan     <long double> = 0.9159655941772190150546035149323841107741L;
template<> inline constexpr long double LDF::const_apery       <long double> = 1.2020569031595942853997381615114499907650L;
template<> inline constexpr long double LDF::const_gompertz    <long double> = 5.1514643229893288663465085557037892680671L;
template<> inline constexpr long double LDF::const_gauss       <long double> = 0.8346268416740731862814297327990468089940L;
template<> inline constexpr long double LDF::const_lemniscate  <long double> = 2.6220575542921198104648395898911194136828L;
template<> inline constexpr long double LDF::const_2lemniscate <long double> = 5.2441151085842396209296791797822388273655L;
template<> inline constexpr long double LDF::const_lemniscate2 <long double> = 1.3110287771460599052324197949455597068414L;


//------------------------------------------------------------------------------
// <double> Constants
//------------------------------------------------------------------------------
#include <math.h>

template<> inline constexpr double LDF::const_pi          <double> = 3.141592653589793238463;
template<> inline constexpr double LDF::const_2pi         <double> = 6.283185307179586476925;
template<> inline constexpr double LDF::const_pi2         <double> = 1.570796326794896619231;
template<> inline constexpr double LDF::const_pi4         <double> = 0.785398163397448309616;
template<> inline constexpr double LDF::const_3pi4        <double> = 2.356194490192344928847;
template<> inline constexpr double LDF::const_pi3         <double> = 1.047197551196597746154;

template<> inline constexpr double LDF::const_inv_pi      <double> = 0.318309886183790671538;
template<> inline constexpr double LDF::const_inv_2pi     <double> = 0.159154943091895335769;
template<> inline constexpr double LDF::const_sqrtpi      <double> = 1.772453850905516027298;
template<> inline constexpr double LDF::const_sqrt2pi     <double> = 2.506628274631000502416;
template<> inline constexpr double LDF::const_inv_sqrtpi  <double> = 0.564189583547756286948;
template<> inline constexpr double LDF::const_inv_sqrt2pi <double> = 0.398942280401432677940;

template<> inline constexpr double LDF::const_e           <double> = 2.718281828459045235360;
template<> inline constexpr double LDF::const_inv_e       <double> = 0.367879441171442321596;
template<> inline constexpr double LDF::const_ln2         <double> = 0.693147180559945309417;
template<> inline constexpr double LDF::const_ln3         <double> = 1.098612288668109691395;
template<> inline constexpr double LDF::const_ln10        <double> = 2.302585092994045684018;
template<> inline constexpr double LDF::const_log2e       <double> = 1.442695040888963407360;
template<> inline constexpr double LDF::const_log3e       <double> = 0.910239226626837393614;
template<> inline constexpr double LDF::const_log10e      <double> = 0.434294481903251827651;

template<> inline constexpr double LDF::const_sqrt2       <double> = 1.414213562373095048802;
template<> inline constexpr double LDF::const_sqrt3       <double> = 1.732050807568877293527;
template<> inline constexpr double LDF::const_sqrt5       <double> = 2.236067977499789696409;
template<> inline constexpr double LDF::const_sqrt6       <double> = 2.449489742783178098197;
template<> inline constexpr double LDF::const_inv_sqrt2   <double> = 0.707106781186547524401;
template<> inline constexpr double LDF::const_inv_sqrt3   <double> = 0.577350269189625764509;
template<> inline constexpr double LDF::const_inv_sqrt5   <double> = 0.447213595499957939282;
template<> inline constexpr double LDF::const_inv_sqrt6   <double> = 0.408248290463863016366;

template<> inline constexpr double LDF::const_cbrt2       <double> = 1.414213562373095048802;
template<> inline constexpr double LDF::const_cbrt3       <double> = 1.732050807568877293527;
template<> inline constexpr double LDF::const_cbrt5       <double> = 2.236067977499789696409;
template<> inline constexpr double LDF::const_cbrt6       <double> = 2.449489742783178098197;
template<> inline constexpr double LDF::const_inv_cbrt2   <double> = 0.793700525984099737376;
template<> inline constexpr double LDF::const_inv_cbrt3   <double> = 0.693361274350634704843;
template<> inline constexpr double LDF::const_inv_cbrt5   <double> = 0.584803547642573213101;
template<> inline constexpr double LDF::const_inv_cbrt6   <double> = 0.550321208149104447312;

template<> inline constexpr double LDF::const_egamma      <double> = 0.577215664901532860607;
template<> inline constexpr double LDF::const_phi         <double> = 1.618033988749894848205;
template<> inline constexpr double LDF::const_tribonacci  <double> = 1.839286755214161132552;
template<> inline constexpr double LDF::const_catalan     <double> = 0.915965594177219015055;
template<> inline constexpr double LDF::const_apery       <double> = 1.202056903159594285400;
template<> inline constexpr double LDF::const_gompertz    <double> = 5.151464322989328866347;
template<> inline constexpr double LDF::const_gauss       <double> = 0.834626841674073186281;
template<> inline constexpr double LDF::const_lemniscate  <double> = 2.622057554292119810465;
template<> inline constexpr double LDF::const_2lemniscate <double> = 5.244115108584239620930;
template<> inline constexpr double LDF::const_lemniscate2 <double> = 1.311028777146059905232;



//------------------------------------------------------------------------------
// <float> Constants
//------------------------------------------------------------------------------

template<> inline constexpr float LDF::const_pi          <float> = 3.14159265359f;
template<> inline constexpr float LDF::const_2pi         <float> = 6.28318530718f;
template<> inline constexpr float LDF::const_pi2         <float> = 1.57079632679f;
template<> inline constexpr float LDF::const_pi4         <float> = 0.78539816340f;
template<> inline constexpr float LDF::const_3pi4        <float> = 2.35619449019f;
template<> inline constexpr float LDF::const_pi3         <float> = 1.04719755120f;

template<> inline constexpr float LDF::const_inv_pi      <float> = 0.31830988618f;
template<> inline constexpr float LDF::const_inv_2pi     <float> = 0.15915494309f;
template<> inline constexpr float LDF::const_sqrtpi      <float> = 1.77245385091f;
template<> inline constexpr float LDF::const_sqrt2pi     <float> = 2.50662827463f;
template<> inline constexpr float LDF::const_inv_sqrtpi  <float> = 0.56418958355f;
template<> inline constexpr float LDF::const_inv_sqrt2pi <float> = 0.39894228040f;

template<> inline constexpr float LDF::const_e           <float> = 2.71828182846f;
template<> inline constexpr float LDF::const_inv_e       <float> = 0.36787944117f;
template<> inline constexpr float LDF::const_ln2         <float> = 0.69314718056f;
template<> inline constexpr float LDF::const_ln3         <float> = 1.09861228867f;
template<> inline constexpr float LDF::const_ln10        <float> = 2.30258509299f;
template<> inline constexpr float LDF::const_log2e       <float> = 1.44269504089f;
template<> inline constexpr float LDF::const_log3e       <float> = 0.91023922663f;
template<> inline constexpr float LDF::const_log10e      <float> = 0.43429448190f;

template<> inline constexpr float LDF::const_sqrt2       <float> = 1.41421356237f;
template<> inline constexpr float LDF::const_sqrt3       <float> = 1.73205080757f;
template<> inline constexpr float LDF::const_sqrt5       <float> = 2.23606797750f;
template<> inline constexpr float LDF::const_sqrt6       <float> = 2.44948974278f;
template<> inline constexpr float LDF::const_inv_sqrt2   <float> = 0.70710678119f;
template<> inline constexpr float LDF::const_inv_sqrt3   <float> = 0.57735026919f;
template<> inline constexpr float LDF::const_inv_sqrt5   <float> = 0.44721359550f;
template<> inline constexpr float LDF::const_inv_sqrt6   <float> = 0.40824829046f;

template<> inline constexpr float LDF::const_cbrt2       <float> = 1.41421356237f;
template<> inline constexpr float LDF::const_cbrt3       <float> = 1.73205080757f;
template<> inline constexpr float LDF::const_cbrt5       <float> = 2.23606797750f;
template<> inline constexpr float LDF::const_cbrt6       <float> = 2.44948974278f;
template<> inline constexpr float LDF::const_inv_cbrt2   <float> = 0.79370052598f;
template<> inline constexpr float LDF::const_inv_cbrt3   <float> = 0.69336127435f;
template<> inline constexpr float LDF::const_inv_cbrt5   <float> = 0.58480354764f;
template<> inline constexpr float LDF::const_inv_cbrt6   <float> = 0.55032120815f;

template<> inline constexpr float LDF::const_egamma      <float> = 0.57721566490f;
template<> inline constexpr float LDF::const_phi         <float> = 1.61803398875f;
template<> inline constexpr float LDF::const_tribonacci  <float> = 1.83928675521f;
template<> inline constexpr float LDF::const_catalan     <float> = 0.91596559418f;
template<> inline constexpr float LDF::const_apery       <float> = 1.20205690316f;
template<> inline constexpr float LDF::const_gompertz    <float> = 5.15146432299f;
template<> inline constexpr float LDF::const_gauss       <float> = 0.83462684167f;
template<> inline constexpr float LDF::const_lemniscate  <float> = 2.62205755429f;
template<> inline constexpr float LDF::const_2lemniscate <float> = 5.24411510858f;
template<> inline constexpr float LDF::const_lemniscate2 <float> = 1.31102877715f;

#endif /* FLOATNXN_CONSTANTS_HPP */