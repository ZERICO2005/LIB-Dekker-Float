/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef FLOAT64X2_MATH_LIMITS_HPP
#define FLOAT64X2_MATH_LIMITS_HPP

#include "../LDF/LDF_input_limits.hpp"
#include "Float64x2_def.h"

namespace LDF {
namespace LDF_Input_Limits {

template<> inline constexpr fp64 exp_min<Float64x2, fp64>() {
	return static_cast<fp64>(-709.79);
}
template<> inline constexpr fp64 exp_max<Float64x2, fp64>() {
	return static_cast<fp64>(709.79);
}

template<> inline constexpr fp64 expm1_min<Float64x2, fp64>() {
	return static_cast<fp64>(709.79);
}
template<> inline constexpr fp64 expm1_max<Float64x2, fp64>() {
	return static_cast<fp64>(-709.79);
}

/** @brief ~27.226017 */
template<> inline constexpr fp64 erfc_max<Float64x2, fp64>() {
	return static_cast<fp64>(27.226018);
}

} /* LDF_Input_Limits */
} /* LDF */

#endif /* FLOAT64X2_MATH_LIMITS_HPP */
