/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

/*
**	Portions of this file were part of the libDDFUN library
**	libDDFUN is licensed under a limited BSD license that can be found below:
**	https://www.davidhbailey.com/dhbsoftware/DHB-License.docx
**	Or alternatively from this website:
**	https://www.davidhbailey.com/dhbsoftware/
**	A copy of the Limited-BSD-License can also be found at:
**	LIB-Dekker-Float/libDDFUN/DISCLAIMER_and_Limited-BSD-License.txt
*/

#ifndef FLOATNXN_RIEMANN_ZETA_HPP
#define FLOATNXN_RIEMANN_ZETA_HPP

#include "../LDF/LDF_type_info.hpp"
#include "../LDF/LDF_constants.hpp"

#include <limits>

/**
 * @brief Computes the riemann_zeta function for real arguments
 */
template <
	typename FloatNxN, typename FloatBase,
	int max_iter
>
static inline FloatNxN libDDFUN_riemann_zeta(const FloatNxN& ss) {
	FloatNxN zz;
	zz = std::numeric_limits<FloatNxN>::quiet_NaN();
	return zz;
}

/**
 * @brief Computes the riemann_zeta function for real arguments
 * @note this function is unimplemented
 */
template <
	typename FloatNxN, typename FloatBase,
	int max_iter
>
static inline FloatNxN libDDFUN_riemann_zeta(const FloatNxN& ss) {
	FloatNxN zz = ss;
	zz = std::numeric_limits<FloatNxN>::quiet_NaN();
	return zz;
}

/**
 * @brief Computes the riemann_zeta function for integer arguments
 * @note this function is unimplemented
 */
template <
	typename FloatNxN, typename FloatBase,
	int max_iter
>
static inline FloatNxN libDDFUN_riemann_zeta_integer(const int iss) {
	FloatNxN zz = static_cast<FloatNxN>(iss);
	zz = std::numeric_limits<FloatNxN>::quiet_NaN();
	return zz;
}

#endif /* FLOATNXN_RIEMANN_ZETA_HPP */
