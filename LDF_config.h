/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef LDF_CONFIG_H
#define LDF_CONFIG_H

/**
 * @brief LDF_config.h is used to configure the LIB-Dekker-Float library.
 */

//------------------------------------------------------------------------------
// Compilation Options
//------------------------------------------------------------------------------

/**
 * define to 1 to force Enable
 * define to 0 to force Disable
 * leave undefined for Automatic
 */

// #define LDF_TOGGLE_CXX17_MATH_SPEC_FUNCS  0
// #define LDF_TOGGLE_CXX20_NUMBERS          0
// #define LDF_TOGGLE_CXX17_IF_CONSTEXPR     0

//------------------------------------------------------------------------------
// C/C++ Keyword Overrides
//------------------------------------------------------------------------------

/**
 * uncomment to override
 * leave undefined for Automatic
 */

/**
 * Provides the C99 `restrict` keyword in C++
 */
// #define LDF_restrict __restrict

/**
 * Defines C++11 `constexpr`
 */
// #define LDF_CXX11_constexpr constexpr

/**
 * Defines C++14 relaxed `constexpr`
 */
// #define LDF_CXX14_constexpr constexpr

/**
 * Defines the C23 `constexpr` keyword
 */
// #define LDF_C23_constexpr constexpr

//------------------------------------------------------------------------------
// Floating Point Types
//------------------------------------------------------------------------------

/**
 * Enable/Disable floating point types
 * define to 1 to force Enable
 * define to 0 to force Disable
 * leave undefined for Automatic
 */

// #define LDF_TOGGLE_FLOAT32     0
// #define LDF_TOGGLE_FLOAT64     0
// #define LDF_TOGGLE_FLOAT80     0
// #define LDF_TOGGLE_FLOAT128    0

// #define LDF_TOGGLE_FLOAT16     0
// #define LDF_TOGGLE_BFLOAT16    0

// #define LDF_TOGGLE_DECIMAL32   0
// #define LDF_TOGGLE_DECIMAL64   0
// #define LDF_TOGGLE_DECIMAL128  0

/**
 * Override floating point types
 */

// #define LDF_OVERRIDE_FLOAT32     float
// #define LDF_OVERRIDE_FLOAT64     double
// #define LDF_OVERRIDE_FLOAT80     __float80
// #define LDF_OVERRIDE_FLOAT128    __float128

// #define LDF_OVERRIDE_FLOAT16     float16_t
// #define LDF_OVERRIDE_BFLOAT16    bfloat16_t

// #define LDF_OVERRIDE_DECIMAL32   _Decimal32
// #define LDF_OVERRIDE_DECIMAL64   _Decimal64
// #define LDF_OVERRIDE_DECIMAL128  _Decimal128

/**
 * Override format strings
 */

// #define PRIFloat32     ""
// #define PRIFloat64     "l"
// #define PRIFloat80     "L"
// #define PRIFloat128    "Q"

// #define PRIFloat16     ""
// #define PRIBFloat16    ""

// #define PRIDecimal32   ""
// #define PRIDecimal64   ""
// #define PRIDecimal128  ""

#endif /* LDF_CONFIG_H */