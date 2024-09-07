/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef FLOATNXN_ARITHMETIC_HPP
#define FLOATNXN_ARITHMETIC_HPP

/* LIB-Dekker-Float namespace */
namespace LDF {

//------------------------------------------------------------------------------
// Basic Arithmetic
//------------------------------------------------------------------------------

/** @brief `x + y` Addition */
template <typename Ret_Type, typename Lhs_Type, typename Rhs_Type>
Ret_Type add(const Lhs_Type& x, const Rhs_Type& y);

/** @brief `x - y` Subtraction */
template <typename Ret_Type, typename Lhs_Type, typename Rhs_Type>
Ret_Type sub(const Lhs_Type& x, const Rhs_Type& y);

/** @brief `x * y` Multipliction */
template <typename Ret_Type, typename Lhs_Type, typename Rhs_Type>
Ret_Type mul(const Lhs_Type& x, const Rhs_Type& y);

/** @brief `x / y` Division */
template <typename Ret_Type, typename Lhs_Type, typename Rhs_Type>
Ret_Type div(const Lhs_Type& x, const Rhs_Type& y);

/** @brief `x * x` Square */
template <typename Ret_Type, typename Input_Type>
Ret_Type square(const Input_Type& x);

/** @brief `1 / x` Reciprocal */
template <typename Ret_Type, typename Input_Type>
Ret_Type recip(const Input_Type& x);

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero.
 */
template <typename Ret_Type, typename Lhs_Type, typename Rhs_Type>
Ret_Type mul_pwr2(const Lhs_Type& x, const Rhs_Type& y);

//------------------------------------------------------------------------------
// Bitwise Operations
//------------------------------------------------------------------------------

/** @brief `~x` Performs a bitwise NOT */
template <typename T>
T bitwise_not(const T& x);

/** @brief `x & y` Performs a bitwise AND */
template <typename T>
T bitwise_and(const T& x, const T& y);

/** @brief `x & ~y` Performs a bitwise ANDNOT */
template <typename T>
T bitwise_andnot(const T& x, const T& y);

/** @brief `x | y` Performs a bitwise OR */
template <typename T>
T bitwise_or(const T& x, const T& y);

/** @brief `x ^ y` Performs a bitwise XOR */
template <typename T>
T bitwise_xor(const T& x, const T& y);

} /* LIB-Dekker-Float namespace */

//------------------------------------------------------------------------------
// <float> Template Specializations
//------------------------------------------------------------------------------

/** @brief `x + y` Addition */
template <>
constexpr inline float LDF::add<float, float, float>(const float& x, const float& y) {
	return x + y;
}

/** @brief `x - y` Subtraction */
template <>
constexpr inline float LDF::sub<float, float, float>(const float& x, const float& y) {
	return x - y;
}

/** @brief `x * y` Multipliction */
template <>
constexpr inline float LDF::mul<float, float, float>(const float& x, const float& y) {
	return x * y;
}

/** @brief `x / y` Division */
template <>
constexpr inline float LDF::div<float, float, float>(const float& x, const float& y) {
	return x / y;
}

/** @brief `x * x` Square */
template <>
constexpr inline float LDF::square<float, float>(const float& x) {
	return x * x;
}

/** @brief `1 / x` Reciprocal */
template <>
constexpr inline float LDF::recip<float, float>(const float& x) {
	return static_cast<float>(1.0) / x;
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero.
 */
template <>
constexpr inline float LDF::mul_pwr2<float, float, float>(const float& x, const float& y) {
	return x * y;
}

//------------------------------------------------------------------------------
// <double> Template Specializations
//------------------------------------------------------------------------------

/** @brief `x + y` Addition */
template <>
constexpr inline double LDF::add<double, double, double>(const double& x, const double& y) {
	return x + y;
}

/** @brief `x - y` Subtraction */
template <>
constexpr inline double LDF::sub<double, double, double>(const double& x, const double& y) {
	return x - y;
}

/** @brief `x * y` Multipliction */
template <>
constexpr inline double LDF::mul<double, double, double>(const double& x, const double& y) {
	return x * y;
}

/** @brief `x / y` Division */
template <>
constexpr inline double LDF::div<double, double, double>(const double& x, const double& y) {
	return x / y;
}

/** @brief `x * x` Square */
template <>
constexpr inline double LDF::square<double, double>(const double& x) {
	return x * x;
}

/** @brief `1 / x` Reciprocal */
template <>
constexpr inline double LDF::recip<double, double>(const double& x) {
	return static_cast<double>(1.0) / x;
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero.
 */
template <>
constexpr inline double LDF::mul_pwr2<double, double, double>(const double& x, const double& y) {
	return x * y;
}

//------------------------------------------------------------------------------
// <long double> Template Specializations
//------------------------------------------------------------------------------

/** @brief `x + y` Addition */
template <>
constexpr inline long double LDF::add<long double, long double, long double>(const long double& x, const long double& y) {
	return x + y;
}

/** @brief `x - y` Subtraction */
template <>
constexpr inline long double LDF::sub<long double, long double, long double>(const long double& x, const long double& y) {
	return x - y;
}

/** @brief `x * y` Multipliction */
template <>
constexpr inline long double LDF::mul<long double, long double, long double>(const long double& x, const long double& y) {
	return x * y;
}

/** @brief `x / y` Division */
template <>
constexpr inline long double LDF::div<long double, long double, long double>(const long double& x, const long double& y) {
	return x / y;
}

/** @brief `x * x` Square */
template <>
constexpr inline long double LDF::square<long double, long double>(const long double& x) {
	return x * x;
}

/** @brief `1 / x` Reciprocal */
template <>
constexpr inline long double LDF::recip<long double, long double>(const long double& x) {
	return static_cast<long double>(1.0) / x;
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero.
 */
template <>
constexpr inline long double LDF::mul_pwr2<long double, long double, long double>(const long double& x, const long double& y) {
	return x * y;
}

#endif /* FLOATNXN_ARITHMETIC_HPP */
