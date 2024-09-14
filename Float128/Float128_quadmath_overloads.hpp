/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/
#ifndef FLOAT128_QUADMATH_OVERLOADS_HPP
#define FLOAT128_QUADMATH_OVERLOADS_HPP

/**
 * @note Overloads for the bessel functions j0(), j1(), jn(), y0(), y1(), yn()
 * are not defined to prevent conflicts with global variables of the same name.
 */

#include <quadmath.h>

/* Arithmetic */
inline __float128 fmax(__float128 x, __float128 y) { return fmaxq(x, y); }
inline __float128 fmin(__float128 x, __float128 y) { return fminq(x, y); }
inline __float128 fabs(__float128 x) { return fabsq(x); }
inline __float128 fdim(__float128 x, __float128 y) { return fdimq(x, y); }
inline __float128 fma(__float128 x, __float128 y, __float128 z) { return fmaq(x, y, z); }
inline __float128 copysign(__float128 x, __float128 y) { return copysignq(x, y); }
inline __float128 sqrt(__float128 x) { return sqrtq(x); }
inline __float128 cbrt(__float128 x) { return cbrtq(x); }
inline __float128 hypot(__float128 x, __float128 y) { return hypotq(x, y); }
/* Trigonometry */
inline __float128  sin (__float128 x) { return  sinq (x); }
inline __float128  cos (__float128 x) { return  cosq (x); }
inline __float128  tan (__float128 x) { return  tanq (x); }
inline __float128 asin (__float128 x) { return asinq (x); }
inline __float128 acos (__float128 x) { return acosq (x); }
inline __float128 atan (__float128 x) { return atanq (x); }
inline __float128  sinh(__float128 x) { return  sinhq(x); }
inline __float128  cosh(__float128 x) { return  coshq(x); }
inline __float128  tanh(__float128 x) { return  tanhq(x); }
inline __float128 asinh(__float128 x) { return asinhq(x); }
inline __float128 acosh(__float128 x) { return acoshq(x); }
inline __float128 atanh(__float128 x) { return atanhq(x); }
inline __float128 atan2(__float128 y, __float128 x) { return atan2q(y, x); }
inline void sincos(__float128 x, __float128* p_sin, __float128* p_cos) { sincosq(x, p_sin, p_cos); }
/* Logarithms and Exponents */
inline __float128 log  (__float128 x) { return logq  (x); }
inline __float128 log1p(__float128 x) { return log1pq(x); }
inline __float128 logb (__float128 x) { return logbq (x); }
inline __float128 log2 (__float128 x) { return log2q (x); }
inline __float128 log10(__float128 x) { return log10q(x); }
inline __float128 exp  (__float128 x) { return expq  (x); }
inline __float128 expm1(__float128 x) { return expm1q(x); }
inline __float128 exp2 (__float128 x) { return exp2q (x); }
inline __float128 pow(__float128 x, __float128 y) { return powq(x, y); }
/* Rounding */
inline __float128 trunc(__float128 x) { return truncq(x); }
inline __float128 floor(__float128 x) { return floorq(x); }
inline __float128 ceil (__float128 x) { return ceilq (x); }
inline __float128 rint (__float128 x) { return rintq (x); }
inline __float128 round(__float128 x) { return roundq(x); }
inline long lrint (__float128 x) { return lrintq (x); }
inline long lround(__float128 x) { return lroundq(x); }
inline long long llrint (__float128 x) { return llrintq (x); }
inline long long llround(__float128 x) { return llroundq(x); }
/* Integer and Remainder */
inline __float128 fmod(__float128 x, __float128  y) { return fmodq(x, y); }
inline __float128 modf(__float128 x, __float128* int_part) { return modfq(x, int_part); }
inline __float128 nearbyint(__float128 x) { return nearbyintq(x); }
inline __float128 nextafter(__float128 x, __float128 y) { return nextafterq(x, y); }
inline __float128 remainder(__float128 x, __float128 y) { return remainderq(x, y); }
inline __float128 remquo(__float128 x, __float128 y, int* quo) { return remquoq(x, y, quo); }
/* Float Exponents */
inline int ilogb(__float128 x) { return ilogbq(x); }
inline __float128 frexp  (__float128 x, int* exp) { return frexpq  (x, exp); }
inline __float128 ldexp  (__float128 x, int  exp) { return ldexpq  (x, exp); }
inline __float128 scalbn (__float128 x, int  exp) { return scalbnq (x, exp); }
inline __float128 scalbln(__float128 x, long exp) { return scalblnq(x, exp); }
/* Tests */
inline bool signbit(__float128 x) { return (signbitq(x) != 0); }
inline bool isfinite(__float128 x) { return (finiteq(x) != 0); }
inline bool isinf(__float128 x) { return (isinfq(x) != 0); }
inline bool isnan(__float128 x) { return (isnanq(x) != 0); }
inline bool issignaling(__float128 x) { return (issignalingq(x) != 0); }
/* Transcendental Functions */
inline __float128 erf (__float128 x) { return erfq (x); }
inline __float128 erfc(__float128 x) { return erfcq(x); }
inline __float128 lgamma(__float128 x) { return lgammaq(x); }
inline __float128 tgamma(__float128 x) { return tgammaq(x); }

#endif /* FLOAT128_QUADMATH_OVERLOADS_HPP */
