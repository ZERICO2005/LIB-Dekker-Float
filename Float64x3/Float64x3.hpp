/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

/*
**	Portions of this file were part of the libQD library, licensed
**	under a modifed BSD license that can be found below:
**	https://www.davidhbailey.com/dhbsoftware/LBNL-BSD-License.docx
**	Or alternatively from this website:
**	https://www.davidhbailey.com/dhbsoftware/
**	A copy of the LBNL-BSD-License can also be found at:
**	LIB-Dekker-Float/libQD/LBNL-BSD-License.txt
*/

#ifndef FLOAT64X3_HPP
#define FLOAT64X3_HPP

#include "Float64x3_def.h"
#include "Float64x3.h"
#include "../Float64x2/Float64x2.hpp"

#include <cstdint>
#include <cmath>

#include "../LDF/LDF_arithmetic.hpp"

//------------------------------------------------------------------------------
// Float64x3 LDF Type Information
//------------------------------------------------------------------------------

#include "../LDF/LDF_type_info.hpp"
namespace LDF {
	template<> struct LDF_Type_Info<Float64x3> {
		static constexpr int FloatBase_Count = 3;
		static constexpr bool to_string_implemented = false;
		static constexpr bool from_string_implemented = false;
		static constexpr bool arithmetic_implemented = false;
		static constexpr bool numeric_limits_implemented = true;
		static constexpr bool bitwise_implemented = true;
		static constexpr bool constants_implemented = false;
		static constexpr bool basic_C99_math_implemented = false;
		static constexpr bool accurate_C99_math_implemented = false;
	};
}

//------------------------------------------------------------------------------
// Float64x3 String Operations
//------------------------------------------------------------------------------

#include "Float64x3_string.h"

#if __cplusplus >= 200809L
/**
 * @brief Wrapper for stringTo_Float64x3
 */
inline Float64x3 operator""_FP64X3(const char* str, std::size_t) {
	return stringTo_Float64x3(str, nullptr);
}
#endif

#include <istream>
/**
 * @brief Wrapper for stringTo_Float64x3
 */
std::istream& operator>>(std::istream& stream, Float64x3& value);

#include <ostream>
/**
 * @brief Wrapper for Float64x3_snprintf
 */
std::ostream& operator<<(std::ostream& stream, const Float64x3& value);

//------------------------------------------------------------------------------
// Float64x3 Compairison
//------------------------------------------------------------------------------

inline constexpr bool operator==(const Float64x3& x, const Float64x3& y) {
	return (
		x.val[0] == y.val[0] && x.val[1] == y.val[1] &&
		x.val[2] == y.val[2]
	);
}
inline constexpr bool operator!=(const Float64x3& x, const Float64x3& y) {
	return (
		x.val[0] != y.val[0] || x.val[1] != y.val[1] ||
		x.val[2] != y.val[2]
	);
}
inline constexpr bool operator<(const Float64x3& x, const Float64x3& y) {
	return 
		(x.val[0] < y.val[0] || (x.val[0] == y.val[0] &&
			(x.val[1] < y.val[1] || (x.val[1] == y.val[1] &&
				x.val[2] < y.val[2]
			))
		));
}
inline constexpr bool operator<=(const Float64x3& x, const Float64x3& y) {
	return 
		(x.val[0] < y.val[0] || (x.val[0] == y.val[0] &&
			(x.val[1] < y.val[1] || (x.val[1] == y.val[1] &&
				x.val[2] <= y.val[2]
			))
		));
}
inline constexpr bool operator>(const Float64x3& x, const Float64x3& y) {
	return 
		(x.val[0] > y.val[0] || (x.val[0] == y.val[0] &&
			(x.val[1] > y.val[1] || (x.val[1] == y.val[1] &&
				x.val[2] > y.val[2]
			))
		));
}
inline constexpr bool operator>=(const Float64x3& x, const Float64x3& y) {
	return 
		(x.val[0] > y.val[0] || (x.val[0] == y.val[0] &&
			(x.val[1] > y.val[1] || (x.val[1] == y.val[1] &&
				x.val[2] >= y.val[2]
			))
		));
}

//------------------------------------------------------------------------------
// Float64x3 Compairison Float64x2
//------------------------------------------------------------------------------

inline constexpr bool operator==(const Float64x3& x, const Float64x2& y) {
	return (x.val[0] == y.hi && x.val[1] == y.lo && x.val[2] == 0.0);
}
inline constexpr bool operator!=(const Float64x3& x, const Float64x2& y) {
	return (x.val[0] != y.hi || x.val[1] != y.lo || x.val[2] != 0.0);
}
inline constexpr bool operator<(const Float64x3& x, const Float64x2& y) {
	return
		(x.val[0] == y.hi) ? (
			(x.val[1] == y.lo) ? (
				x.val[2] < 0.0
			) : (x.val[1] < y.lo)
		) : (x.val[0] < y.hi);
}
inline constexpr bool operator<=(const Float64x3& x, const Float64x2& y) {
	return
		(x.val[0] == y.hi) ? (
			(x.val[1] == y.lo) ? (
				x.val[2] <= 0.0
			) : (x.val[1] < y.lo)
		) : (x.val[0] < y.hi);
}
inline constexpr bool operator>(const Float64x3& x, const Float64x2& y) {
	return
		(x.val[0] == y.hi) ? (
			(x.val[1] == y.lo) ? (
				x.val[2] > 0.0
			) : (x.val[1] > y.lo)
		) : (x.val[0] > y.hi);
}
inline constexpr bool operator>=(const Float64x3& x, const Float64x2& y) {
	return
		(x.val[0] == y.hi) ? (
			(x.val[1] == y.lo) ? (
				x.val[2] >= 0.0
			) : (x.val[1] > y.lo)
		) : (x.val[0] > y.hi);
}



inline constexpr bool operator==(const Float64x2& x, const Float64x3& y) {
	return (x.hi == y.val[0] && x.lo == y.val[1] && 0.0 == y.val[2]);
}
inline constexpr bool operator!=(const Float64x2& x, const Float64x3& y) {
	return (x.hi != y.val[0] || x.lo != y.val[1] || 0.0 != y.val[2]);
}
inline constexpr bool operator<(const Float64x2& x, const Float64x3& y) {
	return
		(x.hi == y.val[0]) ? (
			(x.lo == y.val[1]) ? (
				0.0  < y.val[2]
			) : (x.lo < y.val[1])
		) : (x.hi < y.val[0]);
}
inline constexpr bool operator<=(const Float64x2& x, const Float64x3& y) {
	return
		(x.hi == y.val[0]) ? (
			(x.lo == y.val[1]) ? (
				0.0  <= y.val[2]
			) : (x.lo < y.val[1])
		) : (x.hi < y.val[0]);
}
inline constexpr bool operator>(const Float64x2& x, const Float64x3& y) {
	return
		(x.hi == y.val[0]) ? (
			(x.lo == y.val[1]) ? (
				0.0  > y.val[2]
			) : (x.lo > y.val[1])
		) : (x.hi > y.val[0]);
}
inline constexpr bool operator>=(const Float64x2& x, const Float64x3& y) {
	return
		(x.hi == y.val[0]) ? (
			(x.lo == y.val[1]) ? (
				0.0  >= y.val[2]
			) : (x.lo > y.val[1])
		) : (x.hi > y.val[0]);
}

//------------------------------------------------------------------------------
// Float64x3 Compairison fp64
//------------------------------------------------------------------------------

inline constexpr bool operator==(const Float64x3& x, const fp64 y) {
	return (x.val[0] == y && x.val[1] == 0.0);
}
inline constexpr bool operator!=(const Float64x3& x, const fp64 y) {
	return (x.val[0] != y || x.val[1] != 0.0);
}
inline constexpr bool operator<(const Float64x3& x, const fp64 y) {
	return (x.val[0] < y || (x.val[0] == y && x.val[1] < 0.0));
}
inline constexpr bool operator<=(const Float64x3& x, const fp64 y) {
	return (x.val[0] < y || (x.val[0] == y && x.val[1] <= 0.0));
}
inline constexpr bool operator>(const Float64x3& x, const fp64 y) {
	return (x.val[0] > y || (x.val[0] == y && x.val[1] > 0.0));
}
inline constexpr bool operator>=(const Float64x3& x, const fp64 y) {
	return (x.val[0] > y || (x.val[0] == y && x.val[1] >= 0.0));
}

inline constexpr bool operator==(const fp64 x, const Float64x3& y) {
	return (x == y.val[0] && 0.0 == y.val[1]);
}
inline constexpr bool operator!=(const fp64 x, const Float64x3& y) {
	return (x != y.val[0] || 0.0 != y.val[1]);
}
inline constexpr bool operator<(const fp64 x, const Float64x3& y) {
	return (x < y.val[0] || (x == y.val[0] && 0.0 < y.val[1]));
}
inline constexpr bool operator<=(const fp64 x, const Float64x3& y) {
	return (x < y.val[0] || (x == y.val[0] && 0.0 <= y.val[1]));
}
inline constexpr bool operator>(const fp64 x, const Float64x3& y) {
	return (x > y.val[0] || (x == y.val[0] && 0.0 > y.val[1]));
}
inline constexpr bool operator>=(const fp64 x, const Float64x3& y) {
	return (x > y.val[0] || (x == y.val[0] && 0.0 >= y.val[1]));
}

//------------------------------------------------------------------------------
// Float64x3 Compare to Zero
//------------------------------------------------------------------------------

/** @brief Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero */
inline constexpr bool isequal_zero(const Float64x3& x) {
	return (x.val[0] == 0.0);
}
/** @brief Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero */
inline constexpr bool isnotequal_zero(const Float64x3& x) {
	return (x.val[0] != 0.0);
}
/** @brief Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero */
inline constexpr bool isless_zero(const Float64x3& x) {
	return (x.val[0] < 0.0);
}
/** @brief Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero */
inline constexpr bool islessequal_zero(const Float64x3& x) {
	return (x.val[0] <= 0.0);
}
/** @brief Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero */
inline constexpr bool isgreater_zero(const Float64x3& x) {
	return (x.val[0] > 0.0);
}
/** @brief Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero */
inline constexpr bool isgreaterequal_zero(const Float64x3& x) {
	return (x.val[0] >= 0.0);
}

//------------------------------------------------------------------------------
// Float64x3 LDF Arithmetic
//------------------------------------------------------------------------------

template <> inline
Float64x3 LDF::add<Float64x3, Float64x3, Float64x3>
(const Float64x3& x, const Float64x3& y) {
	return Float64x3_add(x, y);
}

template <> inline
Float64x3 LDF::add<Float64x3, Float64x3, Float64x2>
(const Float64x3& x, const Float64x2& y) {
	return Float64x3_add_dx3_dx2(x, y);
}

template <> inline
Float64x3 LDF::add<Float64x3, Float64x2, Float64x3>
(const Float64x2& x, const Float64x3& y) {
	return Float64x3_add_dx3_d(x, y);
}

template <> inline
Float64x3 LDF::add<Float64x3, Float64x3, fp64>
(const Float64x3& x, const fp64& y) {
	return Float64x3_add_dx2_dx3(x, y);
}

template <> inline
Float64x3 LDF::add<Float64x3, fp64, Float64x3>
(const fp64& x, const Float64x3& y) {
	return Float64x3_add_d_dx3(x, y);
}

/* Subtraction */

template <> inline
Float64x3 LDF::sub<Float64x3, Float64x3, Float64x3>
(const Float64x3& x, const Float64x3& y) {
	return Float64x3_sub(x, y);
}

template <> inline
Float64x3 LDF::sub<Float64x3, Float64x3, Float64x2>
(const Float64x3& x, const Float64x2& y) {
	return Float64x3_sub_dx3_dx2(x, y);
}

template <> inline
Float64x3 LDF::sub<Float64x3, Float64x2, Float64x3>
(const Float64x2& x, const Float64x3& y) {
	return Float64x3_sub_dx3_d(x, y);
}

template <> inline
Float64x3 LDF::sub<Float64x3, Float64x3, fp64>
(const Float64x3& x, const fp64& y) {
	return Float64x3_sub_dx2_dx3(x, y);
}

template <> inline
Float64x3 LDF::sub<Float64x3, fp64, Float64x3>
(const fp64& x, const Float64x3& y) {
	return Float64x3_sub_d_dx3(x, y);
}

/* Multiplication */

#if 0
template <> inline
Float64x3 LDF::mul<Float64x3, Float64x3, Float64x3>
(const Float64x3& x, const Float64x3& y) {
	return Float64x3_mul(x, y);
}

template <> inline
Float64x3 LDF::mul<Float64x3, Float64x3, Float64x2>
(const Float64x3& x, const Float64x2& y) {
	return Float64x3_mul_dx3_dx2(x, y);
}
#endif

template <> inline
Float64x3 LDF::mul<Float64x3, Float64x2, Float64x3>
(const Float64x2& x, const Float64x3& y) {
	return Float64x3_mul_dx3_d(x, y);
}

#if 0
template <> inline
Float64x3 LDF::mul<Float64x3, Float64x3, fp64>
(const Float64x3& x, const fp64& y) {
	return Float64x3_mul_dx2_dx3(x, y);
}
#endif

template <> inline
Float64x3 LDF::mul<Float64x3, fp64, Float64x3>
(const fp64& x, const Float64x3& y) {
	return Float64x3_mul_d_dx3(x, y);
}

/* Square */

#if 0
template <> inline
Float64x3 LDF::square<Float64x3, Float64x3>
(const Float64x3& x) {
	return Float64x3_square(x);
}
#endif

/* Division */

template <> inline
Float64x3 LDF::div<Float64x3, Float64x3, Float64x3>
(const Float64x3& x, const Float64x3& y) {
	return Float64x3_div(x, y);
}

template <> inline
Float64x3 LDF::div<Float64x3, Float64x3, Float64x2>
(const Float64x3& x, const Float64x2& y) {
	return Float64x3_div_dx3_dx2(x, y);
}

template <> inline
Float64x3 LDF::div<Float64x3, Float64x2, Float64x3>
(const Float64x2& x, const Float64x3& y) {
	return Float64x3_div_dx3_d(x, y);
}

template <> inline
Float64x3 LDF::div<Float64x3, Float64x3, fp64>
(const Float64x3& x, const fp64& y) {
	return Float64x3_div_dx2_dx3(x, y);
}

template <> inline
Float64x3 LDF::div<Float64x3, fp64, Float64x3>
(const fp64& x, const Float64x3& y) {
	return Float64x3_div_d_dx3(x, y);
}

/* Reciprocal */

template <> inline
Float64x3 LDF::recip<Float64x3, Float64x3>
(const Float64x3& x) {
	return Float64x3_recip(x);
}

//------------------------------------------------------------------------------
// Float64x3 LDF Optimized Arithmetic
//------------------------------------------------------------------------------

template <> inline
Float64x3 LDF::add<Float64x3, Float64x2, Float64x2>
(const Float64x2& x, const Float64x2& y) {
	return Float64x3_add_dx2_dx2(x, y);
}

template <> inline
Float64x3 LDF::add<Float64x3, Float64x2, fp64>
(const Float64x2& x, const fp64& y) {
	return Float64x3_add_dx2_d(x, y);
}

template <> inline
Float64x3 LDF::add<Float64x3, fp64, Float64x2>
(const fp64& x, const Float64x2& y) {
	return Float64x3_add_d_dx2(x, y);
}

template <> inline
Float64x3 LDF::add<Float64x3, fp64, fp64>
(const fp64& x, const fp64& y) {
	return Float64x3_add_d_d(x, y);
}

/* Subtraction */

template <> inline
Float64x3 LDF::sub<Float64x3, Float64x2, Float64x2>
(const Float64x2& x, const Float64x2& y) {
	return Float64x3_sub_dx2_dx2(x, y);
}

template <> inline
Float64x3 LDF::sub<Float64x3, Float64x2, fp64>
(const Float64x2& x, const fp64& y) {
	return Float64x3_sub_dx2_d(x, y);
}

template <> inline
Float64x3 LDF::sub<Float64x3, fp64, Float64x2>
(const fp64& x, const Float64x2& y) {
	return Float64x3_sub_d_dx2(x, y);
}

template <> inline
Float64x3 LDF::sub<Float64x3, fp64, fp64>
(const fp64& x, const fp64& y) {
	return Float64x3_sub_d_d(x, y);
}

/* Multiplication */

#if 0
template <> inline
Float64x3 LDF::mul<Float64x3, Float64x2, Float64x2>
(const Float64x2& x, const Float64x2& y) {
	return Float64x3_mul_dx2_dx2(x, y);
}

template <> inline
Float64x3 LDF::mul<Float64x3, Float64x2, fp64>
(const Float64x2& x, const fp64& y) {
	return Float64x3_mul_dx2_d(x, y);
}
#endif
template <> inline
Float64x3 LDF::mul<Float64x3, fp64, Float64x2>
(const fp64& x, const Float64x2& y) {
	return Float64x3_mul_d_dx2(x, y);
}

template <> inline
Float64x3 LDF::mul<Float64x3, fp64, fp64>
(const fp64& x, const fp64& y) {
	return Float64x3_mul_d_d(x, y);
}

/* Square */

#if 0
template <> inline
Float64x3 LDF::square<Float64x3, Float64x2>
(const Float64x2& x) {
	return Float64x3_square_dx2(x);
}


template <> inline
Float64x3 LDF::square<Float64x3, fp64>
(const fp64& x) {
	return Float64x3_square_d(x);
}
#endif

/* Division */

template <> inline
Float64x3 LDF::div<Float64x3, Float64x2, Float64x2>
(const Float64x2& x, const Float64x2& y) {
	return Float64x3_div_dx2_dx2(x, y);
}

template <> inline
Float64x3 LDF::div<Float64x3, Float64x2, fp64>
(const Float64x2& x, const fp64& y) {
	return Float64x3_div_dx2_d(x, y);
}

template <> inline
Float64x3 LDF::div<Float64x3, fp64, Float64x2>
(const fp64& x, const Float64x2& y) {
	return Float64x3_div_d_dx2(x, y);
}

template <> inline
Float64x3 LDF::div<Float64x3, fp64, fp64>
(const fp64& x, const fp64& y) {
	return Float64x3_div_d_d(x, y);
}


/* Reciprocal */

template <> inline
Float64x3 LDF::recip<Float64x3, Float64x2>
(const Float64x2& x) {
	return Float64x3_recip_dx2(x);
}

template <> inline
Float64x3 LDF::recip<Float64x3, fp64>
(const fp64& x) {
	return Float64x3_recip_d(x);
}

//------------------------------------------------------------------------------
// Float64x3 specialized arithmetic
//------------------------------------------------------------------------------

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero
 */
template <> inline constexpr
Float64x3 LDF::mul_pwr2<Float64x3, Float64x3, fp64>
(const Float64x3& x, const fp64& y) {
	return {
		x.val[0] * y,
		x.val[1] * y,
		x.val[2] * y
	};
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero
 */
template <> inline constexpr
Float64x3 LDF::mul_pwr2<Float64x3, fp64, Float64x3>
(const fp64& x, const Float64x3& y) {
	return {
		x * y.val[0],
		x * y.val[1],
		x * y.val[2]
	};
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero.
 * The result is stored as a Float64x3
 */
template <> inline constexpr
Float64x3 LDF::mul_pwr2<Float64x3, fp64, fp64>
(const fp64& x, const fp64& y) {
	return {
		x * y,
		static_cast<fp64>(0.0),
		static_cast<fp64>(0.0)
	};
}

//------------------------------------------------------------------------------
// Float64x3 Arithmetic Operator Overloads
//------------------------------------------------------------------------------

/* Negation */

inline constexpr Float64x3 operator-(const Float64x3& x) {
	return {-x.val[0], -x.val[1], -x.val[2]};
}

/* Addition */

inline Float64x3 operator+(const Float64x3& x, const Float64x3& y) {
	return Float64x3_add(x, y);
}

inline Float64x3 operator+(const Float64x3& x, const Float64x2& y) {
	return Float64x3_add_dx3_dx2(x, y);
}
inline Float64x3 operator+(const Float64x3& x, const fp64 y) {
	return Float64x3_add_dx3_d(x, y);
}

inline Float64x3 operator+(const Float64x2& x, const Float64x3& y) {
	return Float64x3_add_dx2_dx3(x, y);
}

inline Float64x3 operator+(const fp64 x, const Float64x3& y) {
	return Float64x3_add_d_dx3(x, y);
}

/* Subtraction */

inline Float64x3 operator-(const Float64x3& x, const Float64x3& y) {
	return Float64x3_sub(x, y);
}

inline Float64x3 operator-(const Float64x3& x, const Float64x2& y) {
	return Float64x3_sub_dx3_dx2(x, y);
}
inline Float64x3 operator-(const Float64x3& x, const fp64 y) {
	return Float64x3_sub_dx3_d(x, y);
}

inline Float64x3 operator-(const Float64x2& x, const Float64x3& y) {
	return Float64x3_sub_dx2_dx3(x, y);
}

inline Float64x3 operator-(const fp64 x, const Float64x3& y) {
	return Float64x3_sub_d_dx3(x, y);
}

/* Multiplication */

#if 0
inline Float64x3 operator*(const Float64x3& x, const Float64x3& y) {
	return Float64x3_mul(x, y);
}

inline Float64x3 operator*(const Float64x3& x, const Float64x2& y) {
	return Float64x3_mul_dx3_dx2(x, y);
}
#endif

inline Float64x3 operator*(const Float64x3& x, const fp64 y) {
	return Float64x3_mul_dx3_d(x, y);
}

#if 0
inline Float64x3 operator*(const Float64x2& x, const Float64x3& y) {
	return Float64x3_mul_dx2_dx3(x, y);
}
#endif

inline Float64x3 operator*(const fp64 x, const Float64x3& y) {
	return Float64x3_mul_d_dx3(x, y);
}

/* Square */

#if 0
inline Float64x3 square(const Float64x3& x) {
	return Float64x3_square(x);
}
#endif

/* Division */

inline Float64x3 operator/(const Float64x3& x, const Float64x3& y) {
	return Float64x3_div(x, y);
}

inline Float64x3 operator/(const Float64x3& x, const Float64x2& y) {
	return Float64x3_div_dx3_dx2(x, y);
}
inline Float64x3 operator/(const Float64x3& x, const fp64 y) {
	return Float64x3_div_dx3_d(x, y);
}

inline Float64x3 operator/(const Float64x2& x, const Float64x3& y) {
	return Float64x3_div_dx2_dx3(x, y);
}

inline Float64x3 operator/(const fp64 x, const Float64x3& y) {
	return Float64x3_div_d_dx3(x, y);
}

/* Reciprocal */

inline Float64x3 recip(const Float64x3& x) {
	return Float64x3_recip(x);
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero
 */
inline constexpr Float64x3 mul_pwr2(const Float64x3& x, const fp64 y) {
	return LDF::mul_pwr2<Float64x3, Float64x3, fp64>(x, y);
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero
 */
inline constexpr Float64x3 mul_pwr2(const fp64 x, const Float64x3& y) {
	return LDF::mul_pwr2<Float64x3, fp64, Float64x3>(x, y);
}

//------------------------------------------------------------------------------
// Float64x3 Compound Assignment
//------------------------------------------------------------------------------

inline Float64x3& operator+=(Float64x3 &x, const Float64x3 &y) {
	x = x + y;
	return x;
}
inline Float64x3& operator-=(Float64x3 &x, const Float64x3 &y) {
	x = x - y;
	return x;
}
#if 0
inline Float64x3& operator*=(Float64x3 &x, const Float64x3 &y) {
	x = x * y;
	return x;
}
#endif
inline Float64x3& operator/=(Float64x3 &x, const Float64x3 &y) {
	x = x / y;
	return x;
}

inline Float64x3& operator+=(Float64x3 &x, const Float64x2 &y) {
	x = x + y;
	return x;
}
inline Float64x3& operator-=(Float64x3 &x, const Float64x2 &y) {
	x = x - y;
	return x;
}
#if 0
inline Float64x3& operator*=(Float64x3 &x, const Float64x2 &y) {
	x = x * y;
	return x;
}
#endif
inline Float64x3& operator/=(Float64x3 &x, const Float64x2 &y) {
	x = x / y;
	return x;
}

inline Float64x3& operator+=(Float64x3 &x, const fp64 y) {
	x = x + y;
	return x;
}
inline Float64x3& operator-=(Float64x3 &x, const fp64 y) {
	x = x - y;
	return x;
}
inline Float64x3& operator*=(Float64x3 &x, const fp64 y) {
	x = x * y;
	return x;
}
inline Float64x3& operator/=(Float64x3 &x, const fp64 y) {
	x = x / y;
	return x;
}

/* Increment/Decrement */

inline Float64x3& operator++(Float64x3& x) {
	x += static_cast<fp64>(1.0);
	return x;
}

inline Float64x3& operator--(Float64x3& x) {
	x -= static_cast<fp64>(1.0);
	return x;
}

inline Float64x3 operator++(Float64x3& x, int) {
	Float64x3 temp = x;
	x += static_cast<fp64>(1.0);
	return temp;
}

inline Float64x3 operator--(Float64x3& x, int) {
	Float64x3 temp = x;
	x -= static_cast<fp64>(1.0);
	return temp;
}

//------------------------------------------------------------------------------
// Float64x3 bitwise operators
//------------------------------------------------------------------------------

template <> inline
Float64x3 LDF::bitwise_not<Float64x3>
(const Float64x3& x) {
	Float64x3 ret = x;
	uint64_t* binary_part = reinterpret_cast<uint64_t*>(&ret);
	binary_part[0] = ~binary_part[0];
	binary_part[1] = ~binary_part[1];
	binary_part[2] = ~binary_part[2];
	binary_part[3] = ~binary_part[3];
	return ret;
}

template <> inline
Float64x3 LDF::bitwise_and<Float64x3, Float64x3>
(const Float64x3& x, const Float64x3& y) {
	Float64x3 ret = x;
	uint64_t* ret_bin = reinterpret_cast<uint64_t*>(&ret);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	ret_bin[0] &= y_bin[0];
	ret_bin[1] &= y_bin[1];
	ret_bin[2] &= y_bin[2];
	ret_bin[3] &= y_bin[3];
	return ret;
}

template <> inline
Float64x3 LDF::bitwise_andnot<Float64x3, Float64x3>
(const Float64x3& x, const Float64x3& y) {
	Float64x3 ret = x;
	uint64_t* ret_bin = reinterpret_cast<uint64_t*>(&ret);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	ret_bin[0] &= ~y_bin[0];
	ret_bin[1] &= ~y_bin[1];
	ret_bin[2] &= ~y_bin[2];
	ret_bin[3] &= ~y_bin[3];
	return ret;
}

template <> inline
Float64x3 LDF::bitwise_or<Float64x3, Float64x3>
(const Float64x3& x, const Float64x3& y) {
	Float64x3 ret = x;
	uint64_t* ret_bin = reinterpret_cast<uint64_t*>(&ret);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	ret_bin[0] |= y_bin[0];
	ret_bin[1] |= y_bin[1];
	ret_bin[2] |= y_bin[2];
	ret_bin[3] |= y_bin[3];
	return ret;
}

template <> inline
Float64x3 LDF::bitwise_xor<Float64x3, Float64x3>
(const Float64x3& x, const Float64x3& y) {
	Float64x3 ret = x;
	uint64_t* ret_bin = reinterpret_cast<uint64_t*>(&ret);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	ret_bin[0] ^= y_bin[0];
	ret_bin[1] ^= y_bin[1];
	ret_bin[2] ^= y_bin[2];
	ret_bin[3] ^= y_bin[3];
	return ret;
}

template <> inline
Float64x3 LDF::bitwise_and<Float64x3, fp64>
(const Float64x3& x, const fp64& y) {
	Float64x3 ret = x;
	uint64_t* ret_bin = reinterpret_cast<uint64_t*>(&ret);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	ret_bin[0] &= *y_bin;
	ret_bin[1] &= *y_bin;
	ret_bin[2] &= *y_bin;
	ret_bin[3] &= *y_bin;
	return ret;
}

template <> inline
Float64x3 LDF::bitwise_andnot<Float64x3, fp64>
(const Float64x3& x, const fp64& y) {
	Float64x3 ret = x;
	uint64_t* ret_bin = reinterpret_cast<uint64_t*>(&ret);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	ret_bin[0] &= ~(*y_bin);
	ret_bin[1] &= ~(*y_bin);
	ret_bin[2] &= ~(*y_bin);
	ret_bin[3] &= ~(*y_bin);
	return ret;
}

template <> inline
Float64x3 LDF::bitwise_or<Float64x3, fp64>
(const Float64x3& x, const fp64& y) {
	Float64x3 ret = x;
	uint64_t* ret_bin = reinterpret_cast<uint64_t*>(&ret);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	ret_bin[0] |= *y_bin;
	ret_bin[1] |= *y_bin;
	ret_bin[2] |= *y_bin;
	ret_bin[3] |= *y_bin;
	return ret;
}

template <> inline
Float64x3 LDF::bitwise_xor<Float64x3, fp64>
(const Float64x3& x, const fp64& y) {
	Float64x3 ret = x;
	uint64_t* ret_bin = reinterpret_cast<uint64_t*>(&ret);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	ret_bin[0] ^= *y_bin;
	ret_bin[1] ^= *y_bin;
	ret_bin[2] ^= *y_bin;
	ret_bin[3] ^= *y_bin;
	return ret;
}

//------------------------------------------------------------------------------
// Float64x3 Limits
//------------------------------------------------------------------------------

namespace std {
template <> class numeric_limits<Float64x3> {
public:
	static constexpr bool is_signed = true;
	static constexpr bool is_integer = false;
	static constexpr bool is_exact = false;
	static constexpr bool has_infinity = std::numeric_limits<fp64>::has_infinity;
	static constexpr bool has_quiet_NaN = std::numeric_limits<fp64>::has_quiet_NaN;
	static constexpr bool has_signaling_NaN = std::numeric_limits<fp64>::has_signaling_NaN;
	static constexpr std::float_denorm_style has_denorm = std::numeric_limits<fp64>::has_denorm;
	static constexpr bool is_bounded = true;
	static constexpr int digits = 158; // 4 * (52 mantissa bits + 1 implicit bit)
	#if __cplusplus >= 201103L
	static constexpr int digits10 = 48; // floor(mantissa bits * log10(2))
	#endif
	/**
	 * @brief Dekker floats can represent FLT_MAX + FLT_MIN exactly, which
	 * is why an absurd amount of digits may be required.
	 */
	static constexpr int max_digits10 =
		std::numeric_limits<fp64>::max_exponent10 - std::numeric_limits<fp64>::min_exponent10 + std::numeric_limits<fp64>::digits10 + 1;
	static constexpr int radix = std::numeric_limits<fp64>::radix;
	static constexpr int min_exponent   = std::numeric_limits<fp64>::min_exponent   + 2 * 53;
	static constexpr int min_exponent10 = std::numeric_limits<fp64>::min_exponent10 + 32 /* ceil((2 * 53) * log10(2)) */;
	static constexpr int max_exponent   = std::numeric_limits<fp64>::max_exponent  ;
	static constexpr int max_exponent10 = std::numeric_limits<fp64>::max_exponent10;
	static constexpr bool traps = std::numeric_limits<fp64>::traps;
	inline static constexpr Float64x3 min() {
		/** 
		 * @remarks libQD lists this as the minimum value that is fully
		 * normalized, although I am not sure if this is the best
		 * definition to use for min()
		 */
		return {
			std::numeric_limits<fp64>::min() * static_cast<fp64>(0x1.0p+106),
			std::numeric_limits<fp64>::min() * static_cast<fp64>(0x1.0p+53),
			std::numeric_limits<fp64>::min()
		};
		// return {std::numeric_limits<fp64>::min(), static_cast<fp64>(0.0)};
	}

	inline static constexpr Float64x3 max() {
		return {
			std::numeric_limits<fp64>::max(),
			std::numeric_limits<fp64>::max() * static_cast<fp64>(0x1.0p-54),
			std::numeric_limits<fp64>::max() * static_cast<fp64>(0x1.0p-108)
		};
	}
	#if __cplusplus >= 201103L
	inline static constexpr Float64x3 lowest() { return -max(); }
	#endif
	/** @brief `2^-158 == 2^-52 * (2^-53)^2` */
	inline static constexpr Float64x3 epsilon() {
		// DBL_EPSILON seems to be 0x1.0p-52
		return {static_cast<fp64>(0x1.0p-158), static_cast<fp64>(0.0), static_cast<fp64>(0.0)};
	}
	inline static constexpr Float64x3 round_error() {
		return {static_cast<fp64>(0.5), static_cast<fp64>(0.0), static_cast<fp64>(0.0)};
	}
	inline static constexpr Float64x3 infinity() {
		return {
			std::numeric_limits<fp64>::infinity(),
			std::numeric_limits<fp64>::infinity(),
			std::numeric_limits<fp64>::infinity()
		};
	}
	inline static constexpr Float64x3 quiet_NaN() {
		return {
			std::numeric_limits<fp64>::quiet_NaN(),
			std::numeric_limits<fp64>::quiet_NaN(),
			std::numeric_limits<fp64>::quiet_NaN()
		};
	}
	inline static constexpr Float64x3 signaling_NaN() {
		return {
			std::numeric_limits<fp64>::signaling_NaN(),
			std::numeric_limits<fp64>::signaling_NaN(),
			std::numeric_limits<fp64>::signaling_NaN()
		};
	}
	inline static constexpr Float64x3 denorm_min() {
		return {
			std::numeric_limits<fp64>::denorm_min(),
			static_cast<fp64>(0.0),
			static_cast<fp64>(0.0)
		};
	}
};
}

//------------------------------------------------------------------------------
// Float64x3 Constants
//------------------------------------------------------------------------------

#include "Float64x3_constants.hpp"

#if __cplusplus >= 201907L
#include <numbers>
namespace std {
	namespace numbers {
		template<> inline constexpr Float64x3 e_v          <Float64x3> = LDF::const_e         <Float64x3>(); /**< ~2.718281828 */
		template<> inline constexpr Float64x3 log2e_v      <Float64x3> = LDF::const_log2e     <Float64x3>(); /**< ~1.442695041 */
		template<> inline constexpr Float64x3 log10e_v     <Float64x3> = LDF::const_log10e    <Float64x3>(); /**< ~0.434294482 */
		template<> inline constexpr Float64x3 pi_v         <Float64x3> = LDF::const_pi        <Float64x3>(); /**< ~3.141592654 */
		template<> inline constexpr Float64x3 inv_pi_v     <Float64x3> = LDF::const_inv_pi    <Float64x3>(); /**< ~0.318309886 */
		template<> inline constexpr Float64x3 inv_sqrtpi_v <Float64x3> = LDF::const_inv_sqrtpi<Float64x3>(); /**< ~0.564189584 */
		template<> inline constexpr Float64x3 ln2_v        <Float64x3> = LDF::const_ln2       <Float64x3>(); /**< ~0.693147181 */
		template<> inline constexpr Float64x3 ln10_v       <Float64x3> = LDF::const_ln10      <Float64x3>(); /**< ~2.302585093 */
		template<> inline constexpr Float64x3 sqrt2_v      <Float64x3> = LDF::const_sqrt2     <Float64x3>(); /**< ~1.414213562 */
		template<> inline constexpr Float64x3 sqrt3_v      <Float64x3> = LDF::const_sqrt3     <Float64x3>(); /**< ~1.732050808 */
		template<> inline constexpr Float64x3 inv_sqrt3_v  <Float64x3> = LDF::const_inv_sqrt3 <Float64x3>(); /**< ~0.577350269 */
		template<> inline constexpr Float64x3 egamma_v     <Float64x3> = LDF::const_egamma    <Float64x3>(); /**< ~0.577215665 */
		template<> inline constexpr Float64x3 phi_v        <Float64x3> = LDF::const_phi       <Float64x3>(); /**< ~1.618033989 */
	}
}
#endif

//------------------------------------------------------------------------------
// Float64x3 math.h functions
//------------------------------------------------------------------------------

/* Floating Point Classify */

	/** @brief Returns true if x is negative */
	inline constexpr bool signbit(const Float64x3& x) {
		return std::signbit(x.val[0]);
	}

	/** @brief Returns true if x is finite */
	inline constexpr bool isfinite(const Float64x3& x) {
		return std::isfinite(x.val[0]);
	}

	/** @brief Returns true if x is +-infinity */
	inline constexpr bool isinf(const Float64x3& x) {
		return std::isinf(x.val[0]);
	}

	/** @brief Returns true if x is any kind of NaN */
	inline constexpr bool isnan(const Float64x3& x) {
		return std::isnan(x.val[0]);
	}

	/** @brief Returns true if x is normal */
	inline constexpr bool isnormal(const Float64x3& x) {
		return (
			std::isnormal(x.val[0]) &&
			(std::isnormal(x.val[1]) || x.val[1] == static_cast<fp64>(0.0)) &&
			(std::isnormal(x.val[2]) || x.val[2] == static_cast<fp64>(0.0))
		);
	}

	/** @brief Returns true if x and y are unordered */
	inline constexpr bool isunordered(const Float64x3& x, const Float64x3& y) {
		return std::isunordered(x.val[0], y.val[0]);
	}

	inline constexpr int fpclassify(const Float64x3& x) {
		return
			isinf(x)             ? FP_INFINITE :
			isnan(x)             ? FP_NAN      :
			isequal_zero(x)      ? FP_ZERO     :
			isnormal(x)          ? FP_NORMAL   :
			FP_SUBNORMAL;
	}

/* Comparison */

	inline constexpr bool isless(const Float64x3& x, const Float64x3& y) {
		return 
			(std::isless(x.val[0], y.val[0]) || (x.val[0] == y.val[0] &&
				(std::isless(x.val[1], y.val[1]) || (x.val[1] == y.val[1] &&
					std::isless(x.val[2], y.val[2])
				))
			));
	}
	inline constexpr bool islessequal(const Float64x3& x, const Float64x3& y) {
		return 
			(std::isless(x.val[0], y.val[0]) || (x.val[0] == y.val[0] &&
				(std::isless(x.val[1], y.val[1]) || (x.val[1] == y.val[1] &&
					std::islessequal(x.val[2], y.val[2])
				))
			));
	}
	inline constexpr bool isgreater(const Float64x3& x, const Float64x3& y) {
		return 
			(std::isgreater(x.val[0], y.val[0]) || (x.val[0] == y.val[0] &&
				(std::isgreater(x.val[1], y.val[1]) || (x.val[1] == y.val[1] &&
					std::isgreater(x.val[2], y.val[2])
				))
			));
	}
	inline constexpr bool isgreaterequal(const Float64x3& x, const Float64x3& y) {
		return 
			(std::isgreater(x.val[0], y.val[0]) || (x.val[0] == y.val[0] &&
				(std::isgreater(x.val[1], y.val[1]) || (x.val[1] == y.val[1] &&
					std::isgreaterequal(x.val[2], y.val[2])
				))
			));
	}
	inline constexpr bool islessgreater(const Float64x3& x, const Float64x3& y) {
		return (
			std::islessgreater(x.val[0], y.val[0]) || std::islessgreater(x.val[1], y.val[1]) ||
			std::islessgreater(x.val[2], y.val[2])
		);
	}

/* fmax and fmin */

	/**
	 * @brief Returns the fmax of x and y. Correctly handling NaN and signed zeros.
	 * You may use std::max as a faster alternative.
	 */
	inline constexpr Float64x3 fmax(const Float64x3& x, const Float64x3& y) {
		return
			isless(x, y) ? y :
			isless(y, x) ? x :
			isnan(x) ? y :
			isnan(y) ? x :
			signbit(x) ? y : x;
	}

	/**
	 * @brief Returns the fmin of x and y. Correctly handling NaN and signed zeros.
	 * You may use std::min as a faster alternative.
	 */
	inline constexpr Float64x3 fmin(const Float64x3& x, const Float64x3& y) {
		return
			isgreater(x, y) ? y :
			isgreater(y, x) ? x :
			isnan(x) ? y :
			isnan(y) ? x :
			signbit(x) ? x : y;
	}
	inline constexpr Float64x3 fmax(const Float64x3& x, const Float64x3& y, const Float64x3& z) {
		return fmax(fmax(x, y), z);
	}
	inline constexpr Float64x3 fmin(const Float64x3& x, const Float64x3& y, const Float64x3& z) {
		return fmin(fmin(x, y), z);
	}

/* Arithmetic */

	inline constexpr Float64x3 fabs(const Float64x3& x) {
		return signbit(x) ? -x : x;
	}
	inline Float64x3 fdim(const Float64x3& x, const Float64x3& y) {
		return islessequal(x, y) ? static_cast<Float64x3>(0.0) : (x - y);
	}

#if 0
	/**
	 * @brief `(x * y) + z` Performs a Fused-Multiply-Add operation, avoiding
	 * rounding errors.
	 * @note Uses Float64x6 for calculations, which may cause this function to
	 * run slowly.
	 */
	Float64x3 fma(const Float64x3& x, const Float64x3& y, const Float64x3& z);
#endif

	inline constexpr Float64x3 copysign(const Float64x3& x, const Float64x3& y) {
		return (signbit(x) != signbit(y)) ? -x : x;
	}
	inline Float64x3 sqrt(const Float64x3& x) {
		return Float64x3_sqrt(x);
	}
#if 0
	inline Float64x3 cbrt(const Float64x3& x) {
		return Float64x3_cbrt(x);
	}
#endif
#if 0
	/** @note Naive implementation of hypot, may overflow for large inputs */
	inline Float64x3 hypot(const Float64x3& x, const Float64x3& y) {
		return sqrt(
			square(x) + square(y)
		);
	}
	/** @note Naive implementation of hypot, may overflow for large inputs */
	inline Float64x3 hypot(const Float64x3& x, const Float64x3& y, const Float64x3& z) {
		return sqrt(
			square(x) + square(y) + square(z)
		);
	}
#endif

/* Trigonometry */

#if 0

	Float64x3  sin (const Float64x3& x);
	Float64x3  cos (const Float64x3& x);
	void sincos(const Float64x3& x, Float64x3& p_sin , Float64x3& p_cos );
	inline Float64x3 tan(const Float64x3& x) {
		Float64x3 sin_val, cos_val;
		sincos(x, sin_val, cos_val);
		return sin_val / cos_val;
	}
	Float64x3 asin (const Float64x3& x);
	Float64x3 acos (const Float64x3& x);
	Float64x3 atan (const Float64x3& x);
	Float64x3  sinh(const Float64x3& x);
	Float64x3  cosh(const Float64x3& x);
	void sinhcosh(const Float64x3& x, Float64x3& p_sinh, Float64x3& p_cosh);
	Float64x3  tanh(const Float64x3& x);
	Float64x3 asinh(const Float64x3& x);
	Float64x3 acosh(const Float64x3& x);
	Float64x3 atanh(const Float64x3& x);
	Float64x3 atan2(const Float64x3& y, const Float64x3& x);

#endif

/* Logarithms and Exponents */

#if 0
	Float64x3 log(const Float64x3& x);

	/**
	 * @brief Calculates `log(x + 1.0)` without losing precision when x is
	 * close to zero.
	 * @note Accurate to at least 199bits for all inputs. Uses log(x + 1.0) when
	 * |x| > ~0.000305 (5.0 * 2^-14)
	 */
	Float64x3 log1p(const Float64x3& x);
	
	inline Float64x3 log2(const Float64x3& x) {
		return log(x) * LDF::const_log2e<Float64x3>();
	}
	inline Float64x3 log10(const Float64x3& x) {
		return log(x) * LDF::const_log10e<Float64x3>();
	}
	inline Float64x3 logb(const Float64x3& x) { return logb(x.val[0]); }

	Float64x3 exp(const Float64x3& x);
	Float64x3 expm1(const Float64x3& x);
	inline Float64x3 exp2(const Float64x3& x) {
		return exp(x * LDF::const_ln2<Float64x3>());
	}
	inline Float64x3 exp10(const Float64x3& x) {
		return exp(x * LDF::const_ln10<Float64x3>());
	}
#endif

/* Power functions */

#if 0

	/**
	 * @brief `x ^ y` Calculates `x` raised to the power of `y` handling
	 * special values such as `zero ^ zero`, `zero ^ -inf`, `+1.0 ^ NaN`, and etc.
	 */
	Float64x3 pow(const Float64x3& x, const Float64x3& y);

	/**
	 * @brief `x ^ y` Calculates `x` raised to the power of `y` handling
	 * special values such as `zero ^ zero`, `zero ^ -inf`, `+1.0 ^ NaN`, and etc.
	 */
	inline Float64x3 pow(const Float64x3& x, const fp64 y) {
		return pow(x, static_cast<Float64x3>(y));
	}

	/**
	 * @brief `x ^ y` Calculates `x` raised to the power of `y` handling
	 * special values such as `zero ^ zero`, `zero ^ -inf`, `+1.0 ^ NaN`, and etc.
	 */
	inline Float64x3 pow(const fp64 x, const Float64x3& y) {
		return pow(static_cast<Float64x3>(x), y);
	}

	/**
	 * @brief `x ^ y` The ieee-754 2008 `powr` function is the same as `pow`
	 * except it does not handle special values such as `zero ^ zero`,
	 * `zero ^ -inf`, `+1.0 ^ NaN`, and etc.
	 */
	inline Float64x3 powr(const Float64x3& x, const Float64x3& y) {
		return exp(y * log(x));
	}

	/**
	 * @brief `x ^ y` The ieee-754 2008 `powr` function is the same as `pow`
	 * except it does not handle special values such as `zero ^ zero`,
	 * `zero ^ -inf`, `+1.0 ^ NaN`, and etc.
	 */
	inline Float64x3 powr(const Float64x3& x, const fp64 y) {
		return exp(y * log(x));
	}
	
	/**
	 * @brief `x ^ y` The ieee-754 2008 `powr` function is the same as `pow`
	 * except it does not handle special values such as `zero ^ zero`,
	 * `zero ^ -inf`, `+1.0 ^ NaN`, and etc.
	 */
	inline Float64x3 powr(const fp64 x, const Float64x3& y) {
		return exp(y * log(static_cast<Float64x3>(x)));
	}
	
	/**
	 * @brief `x ^ n` The ieee-754 2008 `pown` function raises `x` to the power
	 * of an integer in `O(log(n))` time
	 */
	Float64x3 pown(const Float64x3& x, int n);

	/**
	 * @brief `x ^ 1/n` The ieee-754 2008 `rootn` function calculates 
	 * the integer root of `x`
	 * @note Naive implementation of `rootn(x, n)`, calculates
	 * `pow(x, 1 / n)` when `|n| > 3` or `pow(x, +inf)` when `n == 0`
	 */
	Float64x3 rootn(const Float64x3& x, int n);

#endif

/* Rounding */

	/** 
	 * @author Taken from libQD which can be found under a
	 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
	 */
	inline Float64x3 trunc(const Float64x3& x) {
		return Float64x3_trunc(x);
	}

	/** 
	 * @author Taken from libQD which can be found under a
	 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
	 */
	inline Float64x3 floor(const Float64x3& x) {
		return Float64x3_floor(x);
	}
	
	/** 
	 * @author Taken from libQD which can be found under a
	 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
	 */
	inline Float64x3 ceil(const Float64x3& x) {
		return Float64x3_ceil(x);
	}
	/** 
	 * @author Taken from libQD which can be found under a
	 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
	 */
	inline Float64x3 round(const Float64x3& x) {
		return Float64x3_round(x);
	}
	inline Float64x3 rint(const Float64x3& x) {
		switch (fegetround()) {
			default:
			case FE_TOWARDZERO:
				return trunc(x);
			case FE_DOWNWARD:
				return floor(x);
			case FE_UPWARD:
				return ceil(x);
			case FE_TONEAREST:
				return round(x);
		}
	}
	inline long lround(const Float64x3& x) {
		return static_cast<long>(round(x));
	}
	inline long lrint(const Float64x3& x) {
		return static_cast<long>(rint(x));
	}
	inline long long llround(const Float64x3& x) {
		return static_cast<long long>(round(x));
	}
	inline long long llrint(const Float64x3& x) {
		return static_cast<long long>(rint(x));
	}

/* Integer and Remainder */

#if 0

	inline Float64x3 fmod(const Float64x3& x, const Float64x3& y) {
		Float64x3 trunc_part = trunc(x / y);
		return x - y * trunc_part;
	}
	inline Float64x3 modf(const Float64x3& x, Float64x3& int_part) {
		Float64x3 trunc_part = trunc(x);
		int_part = trunc_part;
		return x - trunc_part;
	}
	inline Float64x3 nearbyint(const Float64x3& x) {
		return rint(x);
	}
	inline Float64x3 remainder(const Float64x3& x, const Float64x3& y) {
		Float64x3 round_part = round(x / y);
		return x - y * round_part;
	}
	inline Float64x3 remquo(const Float64x3& x, const Float64x3& y, int& quo) {
		Float64x3 q = round(x / y);
		Float64x3 r = x - y * q;
		quo = static_cast<int>(q.val[0] + q.val[1]);
		return r;
	}

#endif

/* Float Exponents */

	/**
	 * @brief Extracts the exponent of a Float64x3 value to compute the
	 * binary logarithm.
	 */
	inline int ilogb(const Float64x3& x) {
		return ilogb(x.val[0]);
	}
	/**
	 * @brief Returns a normalized Float64x3 value and the exponent in
	 * the form [0.0, 1.0) * 2^expon
	 */
	inline Float64x3 frexp(const Float64x3& x, int& expon) {
		Float64x3 ret;
		expon = ilogb(x.val[0]) + 1;
		ret.val[0] = ldexp(x.val[0], -(expon));
		ret.val[1] = ldexp(x.val[1], -(expon));
		ret.val[2] = ldexp(x.val[2], -(expon));
		return ret;
	}
	/**
	 * @brief Multiplies a Float64x3 value by 2^expon
	 */
	inline Float64x3 ldexp(const Float64x3& x, int expon) {
		Float64x3 ret;
		ret.val[0] = ldexp(x.val[0], expon);
		ret.val[1] = isfinite(x.val[0]) ? ldexp(x.val[1], expon) : x.val[0];
		ret.val[2] = isfinite(x.val[0]) ? ldexp(x.val[2], expon) : x.val[0];
		return ret;
	}
	/**
	 * @brief Multiplies a Float64x3 value by FLT_RADIX^expon
	 */
	inline Float64x3 scalbn(const Float64x3& x, int expon) {
		Float64x3 ret;
		ret.val[0] = scalbn(x.val[0], expon);
		ret.val[1] = isfinite(x.val[0]) ? scalbn(x.val[1], expon) : x.val[0];
		ret.val[2] = isfinite(x.val[0]) ? scalbn(x.val[2], expon) : x.val[0];
		return ret;
	}
	/**
	 * @brief Multiplies a Float64x3 value by FLT_RADIX^expon
	 */
	inline Float64x3 scalbln(const Float64x3& x, long expon) {
		Float64x3 ret;
		ret.val[0] = scalbln(x.val[0], expon);
		ret.val[1] = isfinite(x.val[0]) ? scalbln(x.val[1], expon) : x.val[0];
		ret.val[2] = isfinite(x.val[0]) ? scalbln(x.val[2], expon) : x.val[0];
		return ret;
	}

/* C99 <math.h> Transcendental Functions */

#if 0

	Float64x3 erf(const Float64x3& x);

	/**
	 * @brief Calculates `1 - erf(x)` without losing precision when `x > 0`.
	 * @note Result will round to zero when `x > ~27.226017`
	 */
	Float64x3 erfc(const Float64x3& x);

	Float64x3 tgamma(const Float64x3& x);

	/** 
	 * @note naive implementation of lgamma(x)
	 */
	inline Float64x3 lgamma(const Float64x3& x) {
		return log(fabs(tgamma(x)));
	}

#endif

#endif /* FLOAT64X3_HPP */
