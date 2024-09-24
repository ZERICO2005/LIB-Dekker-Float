/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef LDF_INPUT_LIMITS_HPP
#define LDF_INPUT_LIMITS_HPP

/**
 * @brief contains the minimum and maximum input values that won't round to
 * 0.0, 1.0, infinity, etc.
 */
namespace LDF {
namespace LDF_Input_Limits {
	template<typename Input_Type, typename Ret_Type> inline constexpr Ret_Type exp_min();
	template<typename Input_Type, typename Ret_Type> inline constexpr Ret_Type exp_max();
	template<typename Input_Type, typename Ret_Type> inline constexpr Ret_Type expm1_min();
	template<typename Input_Type, typename Ret_Type> inline constexpr Ret_Type expm1_max();
	template<typename Input_Type, typename Ret_Type> inline constexpr Ret_Type atan_max();
	template<typename Input_Type, typename Ret_Type> inline constexpr Ret_Type tanh_max();
	template<typename Input_Type, typename Ret_Type> inline constexpr Ret_Type erf_max();
	template<typename Input_Type, typename Ret_Type> inline constexpr Ret_Type erfc_min();
	template<typename Input_Type, typename Ret_Type> inline constexpr Ret_Type erfc_max();
} /* LDF_Input_Limits */
} /* LDF */

#endif /* LDF_ARITHMETIC_HPP */
