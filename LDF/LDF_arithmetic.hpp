/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef LDF_ARITHMETIC_HPP
#define LDF_ARITHMETIC_HPP

/* LIB-Dekker-Float namespace */
namespace LDF {

//------------------------------------------------------------------------------
// Basic Arithmetic
//------------------------------------------------------------------------------

/** @brief `x + y` Addition */
template <typename Ret_Type, typename OP1_Type, typename OP2_Type>
Ret_Type add(const OP1_Type& x, const OP2_Type& y);

/** @brief `x - y` Subtraction */
template <typename Ret_Type, typename OP1_Type, typename OP2_Type>
Ret_Type sub(const OP1_Type& x, const OP2_Type& y);

/** @brief `x * y` Multipliction */
template <typename Ret_Type, typename OP1_Type, typename OP2_Type>
Ret_Type mul(const OP1_Type& x, const OP2_Type& y);

/** @brief `x / y` Division */
template <typename Ret_Type, typename OP1_Type, typename OP2_Type>
Ret_Type div(const OP1_Type& x, const OP2_Type& y);

/**
 * @brief `x * x` Square
 * Optimized routine for squaring Dekker-Floats.
 */
template <typename Ret_Type, typename Input_Type>
Ret_Type square(const Input_Type& x);

/**
 * @brief `1 / x` Reciprocal
 * Optimized routine for calculating the reciprocal of a Dekker-Float.
 */
template <typename Ret_Type, typename Input_Type>
Ret_Type recip(const Input_Type& x);

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero.
 * Optimized routine for multiplying a Dekker-Float by a known power of two.
 */
template <typename Ret_Type, typename OP1_Type, typename OP2_Type>
constexpr Ret_Type mul_pwr2(const OP1_Type& x, const OP2_Type& y);

//------------------------------------------------------------------------------
// Bitwise Operations
//------------------------------------------------------------------------------

/** @brief `~x` Performs a bitwise NOT */
template <typename T>
T bitwise_not(const T& x);

/** @brief `x & y` Performs a bitwise AND */
template <typename Ret_Type, typename Arg_Type>
Ret_Type bitwise_and(const Ret_Type& x, const Arg_Type& y);

/** @brief `x & ~y` Performs a bitwise ANDNOT */
template <typename Ret_Type, typename Arg_Type>
Ret_Type bitwise_andnot(const Ret_Type& x, const Arg_Type& y);

/** @brief `x | y` Performs a bitwise OR */
template <typename Ret_Type, typename Arg_Type>
Ret_Type bitwise_or(const Ret_Type& x, const Arg_Type& y);

/** @brief `x ^ y` Performs a bitwise XOR */
template <typename Ret_Type, typename Arg_Type>
Ret_Type bitwise_xor(const Ret_Type& x, const Arg_Type& y);

} /* LIB-Dekker-Float namespace */

//------------------------------------------------------------------------------
// <float> Template Specializations
//------------------------------------------------------------------------------

/** @brief `x + y` Addition */
template <>
inline constexpr float LDF::add<float, float, float>(const float& x, const float& y) {
	return x + y;
}

/** @brief `x - y` Subtraction */
template <>
inline constexpr float LDF::sub<float, float, float>(const float& x, const float& y) {
	return x - y;
}

/** @brief `x * y` Multipliction */
template <>
inline constexpr float LDF::mul<float, float, float>(const float& x, const float& y) {
	return x * y;
}

/** @brief `x / y` Division */
template <>
inline constexpr float LDF::div<float, float, float>(const float& x, const float& y) {
	return x / y;
}

/** @brief `x * x` Square */
template <>
inline constexpr float LDF::square<float, float>(const float& x) {
	return x * x;
}

/** @brief `1 / x` Reciprocal */
template <>
inline constexpr float LDF::recip<float, float>(const float& x) {
	return static_cast<float>(1.0) / x;
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero.
 */
template <>
inline constexpr float LDF::mul_pwr2<float, float, float>(const float& x, const float& y) {
	return x * y;
}

//------------------------------------------------------------------------------
// <double> Template Specializations
//------------------------------------------------------------------------------

/** @brief `x + y` Addition */
template <>
inline constexpr double LDF::add<double, double, double>(const double& x, const double& y) {
	return x + y;
}

/** @brief `x - y` Subtraction */
template <>
inline constexpr double LDF::sub<double, double, double>(const double& x, const double& y) {
	return x - y;
}

/** @brief `x * y` Multipliction */
template <>
inline constexpr double LDF::mul<double, double, double>(const double& x, const double& y) {
	return x * y;
}

/** @brief `x / y` Division */
template <>
inline constexpr double LDF::div<double, double, double>(const double& x, const double& y) {
	return x / y;
}

/** @brief `x * x` Square */
template <>
inline constexpr double LDF::square<double, double>(const double& x) {
	return x * x;
}

/** @brief `1 / x` Reciprocal */
template <>
inline constexpr double LDF::recip<double, double>(const double& x) {
	return static_cast<double>(1.0) / x;
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero.
 */
template <>
inline constexpr double LDF::mul_pwr2<double, double, double>(const double& x, const double& y) {
	return x * y;
}

//------------------------------------------------------------------------------
// <long double> Template Specializations
//------------------------------------------------------------------------------

/** @brief `x + y` Addition */
template <>
inline constexpr long double LDF::add<long double, long double, long double>(const long double& x, const long double& y) {
	return x + y;
}

/** @brief `x - y` Subtraction */
template <>
inline constexpr long double LDF::sub<long double, long double, long double>(const long double& x, const long double& y) {
	return x - y;
}

/** @brief `x * y` Multipliction */
template <>
inline constexpr long double LDF::mul<long double, long double, long double>(const long double& x, const long double& y) {
	return x * y;
}

/** @brief `x / y` Division */
template <>
inline constexpr long double LDF::div<long double, long double, long double>(const long double& x, const long double& y) {
	return x / y;
}

/** @brief `x * x` Square */
template <>
inline constexpr long double LDF::square<long double, long double>(const long double& x) {
	return x * x;
}

/** @brief `1 / x` Reciprocal */
template <>
inline constexpr long double LDF::recip<long double, long double>(const long double& x) {
	return static_cast<long double>(1.0) / x;
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero.
 */
template <>
inline constexpr long double LDF::mul_pwr2<long double, long double, long double>(const long double& x, const long double& y) {
	return x * y;
}

#endif /* LDF_ARITHMETIC_HPP */
