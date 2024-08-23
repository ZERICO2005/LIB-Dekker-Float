/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef MPFR_CONVERT_HPP
#define MPFR_CONVERT_HPP

#if defined(__float128) || defined(_Float128)
	#define MPFR_WANT_FLOAT128
#endif
#include <mpfr.h>

#include <cstdint>

/**
 * @brief Sets a mpfr_t to a template value.
 * @returns 0 if exact, >0 if rounded up, <0 if rounded down
 */
template <typename T>
inline int mpfr_set_type(mpfr_t rop, const T& op, const mpfr_rnd_t rnd);

/**
 * @brief Returns a template value from a mpfr_t
 */
template <typename T>
inline T mpfr_get_type(mpfr_srcptr op, const mpfr_rnd_t rnd);

//------------------------------------------------------------------------------
// floating point specializations
//------------------------------------------------------------------------------

template <>
inline int mpfr_set_type<float>(mpfr_t rop, const float& op, const mpfr_rnd_t rnd) {
	return mpfr_set_flt(rop, op, rnd);
}
template <>
inline float mpfr_get_type<float>(mpfr_srcptr op, const mpfr_rnd_t rnd) {
	return mpfr_get_flt(op, rnd);
}

template <>
inline int mpfr_set_type<double>(mpfr_t rop, const double& op, const mpfr_rnd_t rnd) {
	return mpfr_set_d(rop, op, rnd);
}
template <>
inline double mpfr_get_type<double>(mpfr_srcptr op, const mpfr_rnd_t rnd) {
	return mpfr_get_d(op, rnd);
}

template <>
inline int mpfr_set_type<long double>(mpfr_t rop, const long double& op, const mpfr_rnd_t rnd) {
	return mpfr_set_ld(rop, op, rnd);
}
template <>
inline long double mpfr_get_type<long double>(mpfr_srcptr op, const mpfr_rnd_t rnd) {
	return mpfr_get_ld(op, rnd);
}

#ifdef __float80
template <>
inline int mpfr_set_type<__float80>(mpfr_t rop, const __float80& op, const mpfr_rnd_t rnd) {
	return mpfr_set_ld(rop, op, rnd);
}
template <>
inline __float80 mpfr_get_type<__float80>(mpfr_srcptr op, const mpfr_rnd_t rnd) {
	return mpfr_get_ld(op, rnd);
}
#endif

#ifdef _Float80
template <>
inline int mpfr_set_type<_Float80>(mpfr_t rop, const _Float80& op, const mpfr_rnd_t rnd) {
	return mpfr_set_ld(rop, op, rnd);
}
template <>
inline _Float80 mpfr_get_type<_Float80>(mpfr_srcptr op, const mpfr_rnd_t rnd) {
	return mpfr_get_ld(op, rnd);
}
#endif

#ifdef __float128
template <>
inline int mpfr_set_type<__float128>(mpfr_t rop, const __float128& op, const mpfr_rnd_t rnd) {
	return mpfr_set_float128(rop, op, rnd);
}
template <>
inline _Float128 mpfr_get_type<_Float128>(mpfr_srcptr op, const mpfr_rnd_t rnd) {
	return mpfr_get_float128(op, rnd);
}
#endif

#ifdef _Float128
template <>
inline int mpfr_set_type<_Float128>(mpfr_t rop, const _Float128& op, const mpfr_rnd_t rnd) {
	return mpfr_set_float128(rop, op, rnd);
}
template <>
inline _Float128 mpfr_get_type<_Float128>(mpfr_srcptr op, const mpfr_rnd_t rnd) {
	return mpfr_get_float128(op, rnd);
}
#endif

//------------------------------------------------------------------------------
// integer specializations
//------------------------------------------------------------------------------

template <>
inline int mpfr_set_type<unsigned long>(mpfr_t rop, const unsigned long& op, const mpfr_rnd_t rnd) {
	return mpfr_set_ui(rop, op, rnd);
}
template <>
inline unsigned long mpfr_get_type<unsigned long>(mpfr_srcptr op, const mpfr_rnd_t rnd) {
	return mpfr_get_ui(op, rnd);
}

template <>
inline int mpfr_set_type<long>(mpfr_t rop, const long& op, const mpfr_rnd_t rnd) {
	return mpfr_set_si(rop, op, rnd);
}
template <>
inline long mpfr_get_type<long>(mpfr_srcptr op, const mpfr_rnd_t rnd) {
	return mpfr_get_si(op, rnd);
}

template <>
inline int mpfr_set_type<unsigned int>(mpfr_t rop, const unsigned int& op, const mpfr_rnd_t rnd) {
	return mpfr_set_ui(rop, (unsigned long)op, rnd);
}
template <>
inline unsigned int mpfr_get_type<unsigned int>(mpfr_srcptr op, const mpfr_rnd_t rnd) {
	return (unsigned int)mpfr_get_ui(op, rnd);
}

template <>
inline int mpfr_set_type<int>(mpfr_t rop, const int& op, const mpfr_rnd_t rnd) {
	return mpfr_set_si(rop, (long)op, rnd);
}
template <>
inline int mpfr_get_type<int>(mpfr_srcptr op, const mpfr_rnd_t rnd) {
	return (int)mpfr_get_si(op, rnd);
}

#endif /* MPFR_CONVERT_HPP */