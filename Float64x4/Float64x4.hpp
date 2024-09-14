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

#ifndef FLOAT64X4_HPP
#define FLOAT64X4_HPP

#include "Float64x4_def.h"
#include "Float64x4.h"
#include "../Float64x2/Float64x2.hpp"

#include <cstdint>
#include <cmath>

#include "../LDF/LDF_arithmetic.hpp"

//------------------------------------------------------------------------------
// Float64x4 LDF Type Information
//------------------------------------------------------------------------------

#include "../LDF/LDF_type_info.hpp"
namespace LDF {
	template<> struct LDF_Type_Info<Float64x4> {
		static constexpr int FloatBase_Count = 4;
		static constexpr bool to_string_implemented = true;
		static constexpr bool from_string_implemented = true;
		static constexpr bool arithmetic_implemented = true;
		static constexpr bool numeric_limits_implemented = true;
		static constexpr bool bitwise_implemented = true;
		static constexpr bool constants_implemented = true;
		static constexpr bool basic_C99_math_implemented = true;
		static constexpr bool accurate_C99_math_implemented = false;
	};
}

//------------------------------------------------------------------------------
// Float64x4 String Operations
//------------------------------------------------------------------------------

#include "Float64x4_string.h"

#if __cplusplus >= 200809L
/**
 * @brief Wrapper for stringTo_Float64x4
 */
inline Float64x4 operator""_FP64X4(const char* str, std::size_t) {
	return stringTo_Float64x4(str, nullptr);
}
#endif

#include <istream>
/**
 * @brief Wrapper for stringTo_Float64x4
 */
std::istream& operator>>(std::istream& stream, Float64x4& value);

#include <ostream>
/**
 * @brief Wrapper for Float64x4_snprintf
 */
std::ostream& operator<<(std::ostream& stream, const Float64x4& value);

//------------------------------------------------------------------------------
// Float64x4 Compairison
//------------------------------------------------------------------------------

inline constexpr bool operator==(const Float64x4& x, const Float64x4& y) {
	return (
		x.val[0] == y.val[0] && x.val[1] == y.val[1] &&
		x.val[2] == y.val[2] && x.val[3] == y.val[3]
	);
}
inline constexpr bool operator!=(const Float64x4& x, const Float64x4& y) {
	return (
		x.val[0] != y.val[0] || x.val[1] != y.val[1] ||
		x.val[2] != y.val[2] || x.val[3] != y.val[3]
	);
}
inline constexpr bool operator<(const Float64x4& x, const Float64x4& y) {
	return
		(x.val[0] == y.val[0]) ? (
			(x.val[1] == y.val[1]) ? (
				(x.val[2] == y.val[2]) ? (
					x.val[3] < y.val[3]
				) : (x.val[2] < y.val[2])
			) : (x.val[1] < y.val[1])
		) : (x.val[0] < y.val[0]);
}
inline constexpr bool operator<=(const Float64x4& x, const Float64x4& y) {
	return
		(x.val[0] == y.val[0]) ? (
			(x.val[1] == y.val[1]) ? (
				(x.val[2] == y.val[2]) ? (
					x.val[3] <= y.val[3]
				) : (x.val[2] < y.val[2])
			) : (x.val[1] < y.val[1])
		) : (x.val[0] < y.val[0]);
}
inline constexpr bool operator>(const Float64x4& x, const Float64x4& y) {
	return
		(x.val[0] == y.val[0]) ? (
			(x.val[1] == y.val[1]) ? (
				(x.val[2] == y.val[2]) ? (
					x.val[3] > y.val[3]
				) : (x.val[2] > y.val[2])
			) : (x.val[1] > y.val[1])
		) : (x.val[0] > y.val[0]);
}
inline constexpr bool operator>=(const Float64x4& x, const Float64x4& y) {
	return
		(x.val[0] == y.val[0]) ? (
			(x.val[1] == y.val[1]) ? (
				(x.val[2] == y.val[2]) ? (
					x.val[3] >= y.val[3]
				) : (x.val[2] > y.val[2])
			) : (x.val[1] > y.val[1])
		) : (x.val[0] > y.val[0]);
}

//------------------------------------------------------------------------------
// Float64x4 Compairison Float64x2
//------------------------------------------------------------------------------

inline constexpr bool operator==(const Float64x4& x, const Float64x2& y) {
	return (x.val[0] == y.hi && x.val[1] == y.lo && x.val[2] == 0.0);
}
inline constexpr bool operator!=(const Float64x4& x, const Float64x2& y) {
	return (x.val[0] != y.hi || x.val[1] != y.lo || x.val[2] != 0.0);
}
inline constexpr bool operator<(const Float64x4& x, const Float64x2& y) {
	return
		(x.val[0] == y.hi) ? (
			(x.val[1] == y.lo) ? (
				(x.val[2] == 0.0 ) ? (
					x.val[3] < 0.0
				) : (x.val[2] < 0.0 )
			) : (x.val[1] < y.lo)
		) : (x.val[0] < y.hi);
}
inline constexpr bool operator<=(const Float64x4& x, const Float64x2& y) {
	return
		(x.val[0] == y.hi) ? (
			(x.val[1] == y.lo) ? (
				(x.val[2] == 0.0 ) ? (
					x.val[3] <= 0.0
				) : (x.val[2] < 0.0 )
			) : (x.val[1] < y.lo)
		) : (x.val[0] < y.hi);
}
inline constexpr bool operator>(const Float64x4& x, const Float64x2& y) {
	return
		(x.val[0] == y.hi) ? (
			(x.val[1] == y.lo) ? (
				(x.val[2] == 0.0 ) ? (
					x.val[3] > 0.0
				) : (x.val[2] > 0.0 )
			) : (x.val[1] > y.lo)
		) : (x.val[0] > y.hi);
}
inline constexpr bool operator>=(const Float64x4& x, const Float64x2& y) {
	return
		(x.val[0] == y.hi) ? (
			(x.val[1] == y.lo) ? (
				(x.val[2] == 0.0 ) ? (
					x.val[3] >= 0.0
				) : (x.val[2] > 0.0 )
			) : (x.val[1] > y.lo)
		) : (x.val[0] > y.hi);
}



inline constexpr bool operator==(const Float64x2& x, const Float64x4& y) {
	return (x.hi == y.val[0] && x.lo == y.val[1] && 0.0 == y.val[2]);
}
inline constexpr bool operator!=(const Float64x2& x, const Float64x4& y) {
	return (x.hi != y.val[0] || x.lo != y.val[1] || 0.0 != y.val[2]);
}
inline constexpr bool operator<(const Float64x2& x, const Float64x4& y) {
	return
		(x.hi == y.val[0]) ? (
			(x.lo == y.val[1]) ? (
				(0.0  == y.val[2]) ? (
					0.0  < y.val[3]
				) : (0.0  < y.val[2])
			) : (x.lo < y.val[1])
		) : (x.hi < y.val[0]);
}
inline constexpr bool operator<=(const Float64x2& x, const Float64x4& y) {
	return
		(x.hi == y.val[0]) ? (
			(x.lo == y.val[1]) ? (
				(0.0  == y.val[2]) ? (
					0.0  <= y.val[3]
				) : (0.0  < y.val[2])
			) : (x.lo < y.val[1])
		) : (x.hi < y.val[0]);
}
inline constexpr bool operator>(const Float64x2& x, const Float64x4& y) {
	return
		(x.hi == y.val[0]) ? (
			(x.lo == y.val[1]) ? (
				(0.0  == y.val[2]) ? (
					0.0  > y.val[3]
				) : (0.0  > y.val[2])
			) : (x.lo > y.val[1])
		) : (x.hi > y.val[0]);
}
inline constexpr bool operator>=(const Float64x2& x, const Float64x4& y) {
	return
		(x.hi == y.val[0]) ? (
			(x.lo == y.val[1]) ? (
				(0.0  == y.val[2]) ? (
					0.0  >= y.val[3]
				) : (0.0  > y.val[2])
			) : (x.lo > y.val[1])
		) : (x.hi > y.val[0]);
}

//------------------------------------------------------------------------------
// Float64x4 Compairison fp64
//------------------------------------------------------------------------------

inline constexpr bool operator==(const Float64x4& x, const fp64 y) {
	return (x.val[0] == y && x.val[1] == 0.0);
}
inline constexpr bool operator!=(const Float64x4& x, const fp64 y) {
	return (x.val[0] != y || x.val[1] != 0.0);
}
inline constexpr bool operator<(const Float64x4& x, const fp64 y) {
	return (x.val[0] < y || (x.val[0] == y && x.val[1] < 0.0));
}
inline constexpr bool operator<=(const Float64x4& x, const fp64 y) {
	return (x.val[0] < y || (x.val[0] == y && x.val[1] <= 0.0));
}
inline constexpr bool operator>(const Float64x4& x, const fp64 y) {
	return (x.val[0] > y || (x.val[0] == y && x.val[1] > 0.0));
}
inline constexpr bool operator>=(const Float64x4& x, const fp64 y) {
	return (x.val[0] > y || (x.val[0] == y && x.val[1] >= 0.0));
}

inline constexpr bool operator==(const fp64 x, const Float64x4& y) {
	return (x == y.val[0] && 0.0 == y.val[1]);
}
inline constexpr bool operator!=(const fp64 x, const Float64x4& y) {
	return (x != y.val[0] || 0.0 != y.val[1]);
}
inline constexpr bool operator<(const fp64 x, const Float64x4& y) {
	return (x < y.val[0] || (x == y.val[0] && 0.0 < y.val[1]));
}
inline constexpr bool operator<=(const fp64 x, const Float64x4& y) {
	return (x < y.val[0] || (x == y.val[0] && 0.0 <= y.val[1]));
}
inline constexpr bool operator>(const fp64 x, const Float64x4& y) {
	return (x > y.val[0] || (x == y.val[0] && 0.0 > y.val[1]));
}
inline constexpr bool operator>=(const fp64 x, const Float64x4& y) {
	return (x > y.val[0] || (x == y.val[0] && 0.0 >= y.val[1]));
}

//------------------------------------------------------------------------------
// Float64x4 Compare to Zero
//------------------------------------------------------------------------------

/** @brief Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero */
inline constexpr bool isequal_zero(const Float64x4& x) {
	return (x.val[0] == 0.0);
}
/** @brief Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero */
inline constexpr bool isnotequal_zero(const Float64x4& x) {
	return (x.val[0] != 0.0);
}
/** @brief Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero */
inline constexpr bool isless_zero(const Float64x4& x) {
	return (x.val[0] < 0.0);
}
/** @brief Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero */
inline constexpr bool islessequal_zero(const Float64x4& x) {
	return (x.val[0] <= 0.0);
}
/** @brief Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero */
inline constexpr bool isgreater_zero(const Float64x4& x) {
	return (x.val[0] > 0.0);
}
/** @brief Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero */
inline constexpr bool isgreaterequal_zero(const Float64x4& x) {
	return (x.val[0] >= 0.0);
}

//------------------------------------------------------------------------------
// Float64x4 LDF Arithmetic
//------------------------------------------------------------------------------

template <> inline
Float64x4 LDF::add<Float64x4, Float64x4, Float64x4>
(const Float64x4& x, const Float64x4& y) {
	return Float64x4_add(x, y);
}

template <> inline
Float64x4 LDF::add<Float64x4, Float64x4, Float64x2>
(const Float64x4& x, const Float64x2& y) {
	return Float64x4_add_dx4_dx2(x, y);
}

template <> inline
Float64x4 LDF::add<Float64x4, Float64x2, Float64x4>
(const Float64x2& x, const Float64x4& y) {
	return Float64x4_add_dx4_d(x, y);
}

template <> inline
Float64x4 LDF::add<Float64x4, Float64x4, fp64>
(const Float64x4& x, const fp64& y) {
	return Float64x4_add_dx2_dx4(x, y);
}

template <> inline
Float64x4 LDF::add<Float64x4, fp64, Float64x4>
(const fp64& x, const Float64x4& y) {
	return Float64x4_add_d_dx4(x, y);
}

/* Subtraction */

template <> inline
Float64x4 LDF::sub<Float64x4, Float64x4, Float64x4>
(const Float64x4& x, const Float64x4& y) {
	return Float64x4_sub(x, y);
}

template <> inline
Float64x4 LDF::sub<Float64x4, Float64x4, Float64x2>
(const Float64x4& x, const Float64x2& y) {
	return Float64x4_sub_dx4_dx2(x, y);
}

template <> inline
Float64x4 LDF::sub<Float64x4, Float64x2, Float64x4>
(const Float64x2& x, const Float64x4& y) {
	return Float64x4_sub_dx4_d(x, y);
}

template <> inline
Float64x4 LDF::sub<Float64x4, Float64x4, fp64>
(const Float64x4& x, const fp64& y) {
	return Float64x4_sub_dx2_dx4(x, y);
}

template <> inline
Float64x4 LDF::sub<Float64x4, fp64, Float64x4>
(const fp64& x, const Float64x4& y) {
	return Float64x4_sub_d_dx4(x, y);
}

/* Multiplication */

template <> inline
Float64x4 LDF::mul<Float64x4, Float64x4, Float64x4>
(const Float64x4& x, const Float64x4& y) {
	return Float64x4_mul(x, y);
}

template <> inline
Float64x4 LDF::mul<Float64x4, Float64x4, Float64x2>
(const Float64x4& x, const Float64x2& y) {
	return Float64x4_mul_dx4_dx2(x, y);
}

template <> inline
Float64x4 LDF::mul<Float64x4, Float64x2, Float64x4>
(const Float64x2& x, const Float64x4& y) {
	return Float64x4_mul_dx4_d(x, y);
}

template <> inline
Float64x4 LDF::mul<Float64x4, Float64x4, fp64>
(const Float64x4& x, const fp64& y) {
	return Float64x4_mul_dx2_dx4(x, y);
}

template <> inline
Float64x4 LDF::mul<Float64x4, fp64, Float64x4>
(const fp64& x, const Float64x4& y) {
	return Float64x4_mul_d_dx4(x, y);
}

/* Square */

template <> inline
Float64x4 LDF::square<Float64x4, Float64x4>
(const Float64x4& x) {
	return Float64x4_square(x);
}

/* Division */

template <> inline
Float64x4 LDF::div<Float64x4, Float64x4, Float64x4>
(const Float64x4& x, const Float64x4& y) {
	return Float64x4_div(x, y);
}

template <> inline
Float64x4 LDF::div<Float64x4, Float64x4, Float64x2>
(const Float64x4& x, const Float64x2& y) {
	return Float64x4_div_dx4_dx2(x, y);
}

template <> inline
Float64x4 LDF::div<Float64x4, Float64x2, Float64x4>
(const Float64x2& x, const Float64x4& y) {
	return Float64x4_div_dx4_d(x, y);
}

template <> inline
Float64x4 LDF::div<Float64x4, Float64x4, fp64>
(const Float64x4& x, const fp64& y) {
	return Float64x4_div_dx2_dx4(x, y);
}

template <> inline
Float64x4 LDF::div<Float64x4, fp64, Float64x4>
(const fp64& x, const Float64x4& y) {
	return Float64x4_div_d_dx4(x, y);
}

/* Reciprocal */

template <> inline
Float64x4 LDF::recip<Float64x4, Float64x4>
(const Float64x4& x) {
	return Float64x4_recip(x);
}

//------------------------------------------------------------------------------
// Float64x4 LDF Optimized Arithmetic
//------------------------------------------------------------------------------

template <> inline
Float64x4 LDF::add<Float64x4, Float64x2, Float64x2>
(const Float64x2& x, const Float64x2& y) {
	return Float64x4_add_dx2_dx2(x, y);
}

template <> inline
Float64x4 LDF::add<Float64x4, Float64x2, fp64>
(const Float64x2& x, const fp64& y) {
	return Float64x4_add_dx2_d(x, y);
}

template <> inline
Float64x4 LDF::add<Float64x4, fp64, Float64x2>
(const fp64& x, const Float64x2& y) {
	return Float64x4_add_d_dx2(x, y);
}

template <> inline
Float64x4 LDF::add<Float64x4, fp64, fp64>
(const fp64& x, const fp64& y) {
	return Float64x4_add_d_d(x, y);
}

/* Subtraction */

template <> inline
Float64x4 LDF::sub<Float64x4, Float64x2, Float64x2>
(const Float64x2& x, const Float64x2& y) {
	return Float64x4_sub_dx2_dx2(x, y);
}

template <> inline
Float64x4 LDF::sub<Float64x4, Float64x2, fp64>
(const Float64x2& x, const fp64& y) {
	return Float64x4_sub_dx2_d(x, y);
}

template <> inline
Float64x4 LDF::sub<Float64x4, fp64, Float64x2>
(const fp64& x, const Float64x2& y) {
	return Float64x4_sub_d_dx2(x, y);
}

template <> inline
Float64x4 LDF::sub<Float64x4, fp64, fp64>
(const fp64& x, const fp64& y) {
	return Float64x4_sub_d_d(x, y);
}

/* Multiplication */

template <> inline
Float64x4 LDF::mul<Float64x4, Float64x2, Float64x2>
(const Float64x2& x, const Float64x2& y) {
	return Float64x4_mul_dx2_dx2(x, y);
}

template <> inline
Float64x4 LDF::mul<Float64x4, Float64x2, fp64>
(const Float64x2& x, const fp64& y) {
	return Float64x4_mul_dx2_d(x, y);
}

template <> inline
Float64x4 LDF::mul<Float64x4, fp64, Float64x2>
(const fp64& x, const Float64x2& y) {
	return Float64x4_mul_d_dx2(x, y);
}

template <> inline
Float64x4 LDF::mul<Float64x4, fp64, fp64>
(const fp64& x, const fp64& y) {
	return Float64x4_mul_d_d(x, y);
}

/* Square */

template <> inline
Float64x4 LDF::square<Float64x4, Float64x2>
(const Float64x2& x) {
	return Float64x4_square_dx2(x);
}

template <> inline
Float64x4 LDF::square<Float64x4, fp64>
(const fp64& x) {
	return Float64x4_square_d(x);
}

/* Division */

template <> inline
Float64x4 LDF::div<Float64x4, Float64x2, Float64x2>
(const Float64x2& x, const Float64x2& y) {
	return Float64x4_div_dx2_dx2(x, y);
}

template <> inline
Float64x4 LDF::div<Float64x4, Float64x2, fp64>
(const Float64x2& x, const fp64& y) {
	return Float64x4_div_dx2_d(x, y);
}

template <> inline
Float64x4 LDF::div<Float64x4, fp64, Float64x2>
(const fp64& x, const Float64x2& y) {
	return Float64x4_div_d_dx2(x, y);
}

template <> inline
Float64x4 LDF::div<Float64x4, fp64, fp64>
(const fp64& x, const fp64& y) {
	return Float64x4_div_d_d(x, y);
}


/* Reciprocal */

template <> inline
Float64x4 LDF::recip<Float64x4, Float64x2>
(const Float64x2& x) {
	return Float64x4_recip_dx2(x);
}

template <> inline
Float64x4 LDF::recip<Float64x4, fp64>
(const fp64& x) {
	return Float64x4_recip_d(x);
}

//------------------------------------------------------------------------------
// Float64x4 specialized arithmetic
//------------------------------------------------------------------------------

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero
 */
template <> inline constexpr
Float64x4 LDF::mul_pwr2<Float64x4, Float64x4, fp64>
(const Float64x4& x, const fp64& y) {
	return {
		x.val[0] * y,
		x.val[1] * y,
		x.val[2] * y,
		x.val[3] * y
	};
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero
 */
template <> inline constexpr
Float64x4 LDF::mul_pwr2<Float64x4, fp64, Float64x4>
(const fp64& x, const Float64x4& y) {
	return {
		x * y.val[0],
		x * y.val[1],
		x * y.val[2],
		x * y.val[3]
	};
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero.
 * The result is stored as a Float64x4
 */
template <> inline constexpr
Float64x4 LDF::mul_pwr2<Float64x4, fp64, fp64>
(const fp64& x, const fp64& y) {
	return {
		x * y,
		static_cast<fp64>(0.0),
		static_cast<fp64>(0.0),
		static_cast<fp64>(0.0)
	};
}

//------------------------------------------------------------------------------
// Float64x4 Arithmetic Operator Overloads
//------------------------------------------------------------------------------

/* Negation */

inline constexpr Float64x4 operator-(const Float64x4& x) {
	return {-x.val[0], -x.val[1], -x.val[2], -x.val[3]};
}

/* Addition */

inline Float64x4 operator+(const Float64x4& x, const Float64x4& y) {
	return Float64x4_add(x, y);
}

inline Float64x4 operator+(const Float64x4& x, const Float64x2& y) {
	return Float64x4_add_dx4_dx2(x, y);
}
inline Float64x4 operator+(const Float64x4& x, const fp64 y) {
	return Float64x4_add_dx4_d(x, y);
}

inline Float64x4 operator+(const Float64x2& x, const Float64x4& y) {
	return Float64x4_add_dx2_dx4(x, y);
}

inline Float64x4 operator+(const fp64 x, const Float64x4& y) {
	return Float64x4_add_d_dx4(x, y);
}

/* Subtraction */

inline Float64x4 operator-(const Float64x4& x, const Float64x4& y) {
	return Float64x4_sub(x, y);
}

inline Float64x4 operator-(const Float64x4& x, const Float64x2& y) {
	return Float64x4_sub_dx4_dx2(x, y);
}
inline Float64x4 operator-(const Float64x4& x, const fp64 y) {
	return Float64x4_sub_dx4_d(x, y);
}

inline Float64x4 operator-(const Float64x2& x, const Float64x4& y) {
	return Float64x4_sub_dx2_dx4(x, y);
}

inline Float64x4 operator-(const fp64 x, const Float64x4& y) {
	return Float64x4_sub_d_dx4(x, y);
}

/* Multiplication */

inline Float64x4 operator*(const Float64x4& x, const Float64x4& y) {
	return Float64x4_mul(x, y);
}

inline Float64x4 operator*(const Float64x4& x, const Float64x2& y) {
	return Float64x4_mul_dx4_dx2(x, y);
}
inline Float64x4 operator*(const Float64x4& x, const fp64 y) {
	return Float64x4_mul_dx4_d(x, y);
}

inline Float64x4 operator*(const Float64x2& x, const Float64x4& y) {
	return Float64x4_mul_dx2_dx4(x, y);
}

inline Float64x4 operator*(const fp64 x, const Float64x4& y) {
	return Float64x4_mul_d_dx4(x, y);
}

/* Square */

inline Float64x4 square(const Float64x4& x) {
	return Float64x4_square(x);
}

/* Division */

inline Float64x4 operator/(const Float64x4& x, const Float64x4& y) {
	return Float64x4_div(x, y);
}

inline Float64x4 operator/(const Float64x4& x, const Float64x2& y) {
	return Float64x4_div_dx4_dx2(x, y);
}
inline Float64x4 operator/(const Float64x4& x, const fp64 y) {
	return Float64x4_div_dx4_d(x, y);
}

inline Float64x4 operator/(const Float64x2& x, const Float64x4& y) {
	return Float64x4_div_dx2_dx4(x, y);
}

inline Float64x4 operator/(const fp64 x, const Float64x4& y) {
	return Float64x4_div_d_dx4(x, y);
}

/* Reciprocal */

inline Float64x4 recip(const Float64x4& x) {
	return Float64x4_recip(x);
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero
 */
inline constexpr Float64x4 mul_pwr2(const Float64x4& x, const fp64 y) {
	return LDF::mul_pwr2<Float64x4, Float64x4, fp64>(x, y);
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero
 */
inline constexpr Float64x4 mul_pwr2(const fp64 x, const Float64x4& y) {
	return LDF::mul_pwr2<Float64x4, fp64, Float64x4>(x, y);
}

//------------------------------------------------------------------------------
// Float64x4 Compound Assignment
//------------------------------------------------------------------------------

inline Float64x4& operator+=(Float64x4 &x, const Float64x4 &y) {
	x = x + y;
	return x;
}
inline Float64x4& operator-=(Float64x4 &x, const Float64x4 &y) {
	x = x - y;
	return x;
}
inline Float64x4& operator*=(Float64x4 &x, const Float64x4 &y) {
	x = x * y;
	return x;
}
inline Float64x4& operator/=(Float64x4 &x, const Float64x4 &y) {
	x = x / y;
	return x;
}

inline Float64x4& operator+=(Float64x4 &x, const Float64x2 &y) {
	x = x + y;
	return x;
}
inline Float64x4& operator-=(Float64x4 &x, const Float64x2 &y) {
	x = x - y;
	return x;
}
inline Float64x4& operator*=(Float64x4 &x, const Float64x2 &y) {
	x = x * y;
	return x;
}
inline Float64x4& operator/=(Float64x4 &x, const Float64x2 &y) {
	x = x / y;
	return x;
}

inline Float64x4& operator+=(Float64x4 &x, const fp64 y) {
	x = x + y;
	return x;
}
inline Float64x4& operator-=(Float64x4 &x, const fp64 y) {
	x = x - y;
	return x;
}
inline Float64x4& operator*=(Float64x4 &x, const fp64 y) {
	x = x * y;
	return x;
}
inline Float64x4& operator/=(Float64x4 &x, const fp64 y) {
	x = x / y;
	return x;
}

/* Increment/Decrement */

inline Float64x4& operator++(Float64x4& x) {
	x += static_cast<fp64>(1.0);
	return x;
}

inline Float64x4& operator--(Float64x4& x) {
	x -= static_cast<fp64>(1.0);
	return x;
}

inline Float64x4 operator++(Float64x4& x, int) {
	Float64x4 temp = x;
	x += static_cast<fp64>(1.0);
	return temp;
}

inline Float64x4 operator--(Float64x4& x, int) {
	Float64x4 temp = x;
	x -= static_cast<fp64>(1.0);
	return temp;
}

//------------------------------------------------------------------------------
// Float64x4 bitwise operators
//------------------------------------------------------------------------------

template <> inline
Float64x4 LDF::bitwise_not<Float64x4>
(const Float64x4& x) {
	Float64x4 ret = x;
	uint64_t* binary_part = reinterpret_cast<uint64_t*>(&ret);
	binary_part[0] = ~binary_part[0];
	binary_part[1] = ~binary_part[1];
	binary_part[2] = ~binary_part[2];
	binary_part[3] = ~binary_part[3];
	return ret;
}

template <> inline
Float64x4 LDF::bitwise_and<Float64x4, Float64x4>
(const Float64x4& x, const Float64x4& y) {
	Float64x4 ret = x;
	uint64_t* ret_bin = reinterpret_cast<uint64_t*>(&ret);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	ret_bin[0] &= y_bin[0];
	ret_bin[1] &= y_bin[1];
	ret_bin[2] &= y_bin[2];
	ret_bin[3] &= y_bin[3];
	return ret;
}

template <> inline
Float64x4 LDF::bitwise_andnot<Float64x4, Float64x4>
(const Float64x4& x, const Float64x4& y) {
	Float64x4 ret = x;
	uint64_t* ret_bin = reinterpret_cast<uint64_t*>(&ret);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	ret_bin[0] &= ~y_bin[0];
	ret_bin[1] &= ~y_bin[1];
	ret_bin[2] &= ~y_bin[2];
	ret_bin[3] &= ~y_bin[3];
	return ret;
}

template <> inline
Float64x4 LDF::bitwise_or<Float64x4, Float64x4>
(const Float64x4& x, const Float64x4& y) {
	Float64x4 ret = x;
	uint64_t* ret_bin = reinterpret_cast<uint64_t*>(&ret);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	ret_bin[0] |= y_bin[0];
	ret_bin[1] |= y_bin[1];
	ret_bin[2] |= y_bin[2];
	ret_bin[3] |= y_bin[3];
	return ret;
}

template <> inline
Float64x4 LDF::bitwise_xor<Float64x4, Float64x4>
(const Float64x4& x, const Float64x4& y) {
	Float64x4 ret = x;
	uint64_t* ret_bin = reinterpret_cast<uint64_t*>(&ret);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	ret_bin[0] ^= y_bin[0];
	ret_bin[1] ^= y_bin[1];
	ret_bin[2] ^= y_bin[2];
	ret_bin[3] ^= y_bin[3];
	return ret;
}

template <> inline
Float64x4 LDF::bitwise_and<Float64x4, fp64>
(const Float64x4& x, const fp64& y) {
	Float64x4 ret = x;
	uint64_t* ret_bin = reinterpret_cast<uint64_t*>(&ret);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	ret_bin[0] &= *y_bin;
	ret_bin[1] &= *y_bin;
	ret_bin[2] &= *y_bin;
	ret_bin[3] &= *y_bin;
	return ret;
}

template <> inline
Float64x4 LDF::bitwise_andnot<Float64x4, fp64>
(const Float64x4& x, const fp64& y) {
	Float64x4 ret = x;
	uint64_t* ret_bin = reinterpret_cast<uint64_t*>(&ret);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	ret_bin[0] &= ~(*y_bin);
	ret_bin[1] &= ~(*y_bin);
	ret_bin[2] &= ~(*y_bin);
	ret_bin[3] &= ~(*y_bin);
	return ret;
}

template <> inline
Float64x4 LDF::bitwise_or<Float64x4, fp64>
(const Float64x4& x, const fp64& y) {
	Float64x4 ret = x;
	uint64_t* ret_bin = reinterpret_cast<uint64_t*>(&ret);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	ret_bin[0] |= *y_bin;
	ret_bin[1] |= *y_bin;
	ret_bin[2] |= *y_bin;
	ret_bin[3] |= *y_bin;
	return ret;
}

template <> inline
Float64x4 LDF::bitwise_xor<Float64x4, fp64>
(const Float64x4& x, const fp64& y) {
	Float64x4 ret = x;
	uint64_t* ret_bin = reinterpret_cast<uint64_t*>(&ret);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	ret_bin[0] ^= *y_bin;
	ret_bin[1] ^= *y_bin;
	ret_bin[2] ^= *y_bin;
	ret_bin[3] ^= *y_bin;
	return ret;
}

//------------------------------------------------------------------------------
// Float64x4 Limits
//------------------------------------------------------------------------------

namespace std {
template <> class numeric_limits<Float64x4> {
public:
	static constexpr bool is_signed = true;
	static constexpr bool is_integer = false;
	static constexpr bool is_exact = false;
	static constexpr bool has_infinity = std::numeric_limits<fp64>::has_infinity;
	static constexpr bool has_quiet_NaN = std::numeric_limits<fp64>::has_quiet_NaN;
	static constexpr bool has_signaling_NaN = std::numeric_limits<fp64>::has_signaling_NaN;
	static constexpr std::float_denorm_style has_denorm = std::numeric_limits<fp64>::has_denorm;
	static constexpr bool is_bounded = true;
	static constexpr int digits = 212; // 4 * (52 mantissa bits + 1 implicit bit)
	#if __cplusplus >= 201103L
	static constexpr int digits10 = 63; // floor(mantissa bits * log10(2))
	#endif
	/**
	 * @brief Dekker floats can represent FLT_MAX + FLT_MIN exactly, which
	 * is why an absurd amount of digits may be required.
	 */
	static constexpr int max_digits10 =
		std::numeric_limits<fp64>::max_exponent10 - std::numeric_limits<fp64>::min_exponent10 + std::numeric_limits<fp64>::digits10 + 1;
	static constexpr int radix = std::numeric_limits<fp64>::radix;
	static constexpr int min_exponent   = std::numeric_limits<fp64>::min_exponent   + 3 * 53;
	static constexpr int min_exponent10 = std::numeric_limits<fp64>::min_exponent10 + 48 /* ceil((3 * 53) * log10(2)) */;
	static constexpr int max_exponent   = std::numeric_limits<fp64>::max_exponent  ;
	static constexpr int max_exponent10 = std::numeric_limits<fp64>::max_exponent10;
	static constexpr bool traps = std::numeric_limits<fp64>::traps;
	inline static constexpr Float64x4 min() {
		/** 
		 * @remarks libQD lists this as the minimum value that is fully
		 * normalized, although I am not sure if this is the best
		 * definition to use for min()
		 */
		return {
			std::numeric_limits<fp64>::min() * static_cast<fp64>(0x1.0p+159),
			std::numeric_limits<fp64>::min() * static_cast<fp64>(0x1.0p+106),
			std::numeric_limits<fp64>::min() * static_cast<fp64>(0x1.0p+53),
			std::numeric_limits<fp64>::min()
		};
		// return {std::numeric_limits<fp64>::min(), static_cast<fp64>(0.0)};
	}

	inline static constexpr Float64x4 max() {
		return {
			std::numeric_limits<fp64>::max(),
			std::numeric_limits<fp64>::max() * static_cast<fp64>(0x1.0p-54),
			std::numeric_limits<fp64>::max() * static_cast<fp64>(0x1.0p-108),
			std::numeric_limits<fp64>::max() * static_cast<fp64>(0x1.0p-162),
		};
	}
	#if __cplusplus >= 201103L
	inline static constexpr Float64x4 lowest() { return -max(); }
	#endif
	inline static constexpr Float64x4 epsilon() {
		// DBL_EPSILON seems to be 0x1.0p-52
		return {static_cast<fp64>(0x1.0p-208), static_cast<fp64>(0.0), static_cast<fp64>(0.0), static_cast<fp64>(0.0)};
	}
	inline static constexpr Float64x4 round_error() {
		return {static_cast<fp64>(0.5), static_cast<fp64>(0.0), static_cast<fp64>(0.0), static_cast<fp64>(0.0)};
	}
	inline static constexpr Float64x4 infinity() {
		return {
			std::numeric_limits<fp64>::infinity(),
			std::numeric_limits<fp64>::infinity(),
			std::numeric_limits<fp64>::infinity(),
			std::numeric_limits<fp64>::infinity()
		};
	}
	inline static constexpr Float64x4 quiet_NaN() {
		return {
			std::numeric_limits<fp64>::quiet_NaN(),
			std::numeric_limits<fp64>::quiet_NaN(),
			std::numeric_limits<fp64>::quiet_NaN(),
			std::numeric_limits<fp64>::quiet_NaN()
		};
	}
	inline static constexpr Float64x4 signaling_NaN() {
		return {
			std::numeric_limits<fp64>::signaling_NaN(),
			std::numeric_limits<fp64>::signaling_NaN(),
			std::numeric_limits<fp64>::signaling_NaN(),
			std::numeric_limits<fp64>::signaling_NaN()
		};
	}
	inline static constexpr Float64x4 denorm_min() {
		return {
			std::numeric_limits<fp64>::denorm_min(),
			static_cast<fp64>(0.0),
			static_cast<fp64>(0.0),
			static_cast<fp64>(0.0)
		};
	}
};
}

//------------------------------------------------------------------------------
// Float64x4 Constants
//------------------------------------------------------------------------------

#include "Float64x4_constants.hpp"

#if __cplusplus >= 201907L
#include <numbers>
namespace std {
	namespace numbers {
		template<> inline constexpr Float64x4 e_v          <Float64x4> = LDF::const_e         <Float64x4>(); /**< ~2.718281828 */
		template<> inline constexpr Float64x4 log2e_v      <Float64x4> = LDF::const_log2e     <Float64x4>(); /**< ~1.442695041 */
		template<> inline constexpr Float64x4 log10e_v     <Float64x4> = LDF::const_log10e    <Float64x4>(); /**< ~0.434294482 */
		template<> inline constexpr Float64x4 pi_v         <Float64x4> = LDF::const_pi        <Float64x4>(); /**< ~3.141592654 */
		template<> inline constexpr Float64x4 inv_pi_v     <Float64x4> = LDF::const_inv_pi    <Float64x4>(); /**< ~0.318309886 */
		template<> inline constexpr Float64x4 inv_sqrtpi_v <Float64x4> = LDF::const_inv_sqrtpi<Float64x4>(); /**< ~0.564189584 */
		template<> inline constexpr Float64x4 ln2_v        <Float64x4> = LDF::const_ln2       <Float64x4>(); /**< ~0.693147181 */
		template<> inline constexpr Float64x4 ln10_v       <Float64x4> = LDF::const_ln10      <Float64x4>(); /**< ~2.302585093 */
		template<> inline constexpr Float64x4 sqrt2_v      <Float64x4> = LDF::const_sqrt2     <Float64x4>(); /**< ~1.414213562 */
		template<> inline constexpr Float64x4 sqrt3_v      <Float64x4> = LDF::const_sqrt3     <Float64x4>(); /**< ~1.732050808 */
		template<> inline constexpr Float64x4 inv_sqrt3_v  <Float64x4> = LDF::const_inv_sqrt3 <Float64x4>(); /**< ~0.577350269 */
		template<> inline constexpr Float64x4 egamma_v     <Float64x4> = LDF::const_egamma    <Float64x4>(); /**< ~0.577215665 */
		template<> inline constexpr Float64x4 phi_v        <Float64x4> = LDF::const_phi       <Float64x4>(); /**< ~1.618033989 */
	}
}
#endif

//------------------------------------------------------------------------------
// Float64x4 math.h functions
//------------------------------------------------------------------------------

/* Floating Point Classify */

	/** @brief Returns true if x is negative */
	inline constexpr bool signbit(const Float64x4& x) {
		return std::signbit(x.val[0]);
	}

	/** @brief Returns true if x is finite */
	inline constexpr bool isfinite(const Float64x4& x) {
		return std::isfinite(x.val[0]);
	}

	/** @brief Returns true if x is +-infinity */
	inline constexpr bool isinf(const Float64x4& x) {
		return std::isinf(x.val[0]);
	}

	/** @brief Returns true if x is any kind of NaN */
	inline constexpr bool isnan(const Float64x4& x) {
		return std::isnan(x.val[0]);
	}

	/** @brief Returns true if x is normal */
	inline constexpr bool isnormal(const Float64x4& x) {
		return (
			std::isnormal(x.val[0]) && std::isnormal(x.val[1]) &&
			std::isnormal(x.val[2]) && std::isnormal(x.val[3])
		);
	}

	/** @brief Returns true if x and y are unordered */
	inline constexpr bool isunordered(const Float64x4& x, const Float64x4& y) {
		return std::isunordered(x.val[0], y.val[0]);
	}

	inline constexpr int fpclassify(const Float64x4& x) {
		return
			isinf(x)             ? FP_INFINITE :
			isnan(x)             ? FP_NAN      :
			isequal_zero(x) ? FP_ZERO     :
			isnormal(x)          ? FP_NORMAL   :
			FP_SUBNORMAL;
	}

/* fmax and fmin */

	/**
	 * @brief Returns the fmax of x and y. Correctly handling NaN and signed zeros.
	 * You may use std::max as a faster alternative.
	 */
	inline constexpr Float64x4 fmax(const Float64x4& x, const Float64x4& y) {
		return
			(x < y) ? y :
			(y < x) ? x :
			isnan(x) ? y :
			isnan(y) ? x :
			signbit(x) ? y : x;
	}

	/**
	 * @brief Returns the fmin of x and y. Correctly handling NaN and signed zeros.
	 * You may use std::min as a faster alternative.
	 */
	inline constexpr Float64x4 fmin(const Float64x4& x, const Float64x4& y) {
		return
			(x > y) ? y :
			(y > x) ? x :
			isnan(x) ? y :
			isnan(y) ? x :
			signbit(x) ? x : y;
	}

/* Arithmetic */

	inline constexpr Float64x4 fmax(const Float64x4& x, const Float64x4& y, const Float64x4& z) {
		return fmax(fmax(x, y), z);
	}
	inline constexpr Float64x4 fmin(const Float64x4& x, const Float64x4& y, const Float64x4& z) {
		return fmin(fmin(x, y), z);
	}
	inline constexpr Float64x4 fabs(const Float64x4& x) {
		return (isless_zero(x)) ? -x : x;
	}
	inline constexpr Float64x4 fdim(const Float64x4& x, const Float64x4& y) {
		return (x > y) ? (x - y) : static_cast<Float64x4>(0.0);
	}

	/**
	 * @brief `(x * y) + z` Performs a Fused-Multiply-Add operation, avoiding
	 * rounding errors.
	 * @note Uses Float64x6 for calculations, which may cause this function to
	 * run slowly.
	 */
	Float64x4 fma(const Float64x4& x, const Float64x4& y, const Float64x4& z);

	inline constexpr Float64x4 copysign(const Float64x4& x, const Float64x4& y) {
		return (isless_zero(x)) != (isless_zero(y)) ? -x : x;
	}
	inline Float64x4 sqrt(const Float64x4& x) {
		return Float64x4_sqrt(x);
	}
	inline Float64x4 cbrt(const Float64x4& x) {
		return Float64x4_cbrt(x);
	}
	/** @note Naive implementation of hypot, may overflow for large inputs */
	inline Float64x4 hypot(const Float64x4& x, const Float64x4& y) {
		return sqrt(
			square(x) + square(y)
		);
	}
	/** @note Naive implementation of hypot, may overflow for large inputs */
	inline Float64x4 hypot(const Float64x4& x, const Float64x4& y, const Float64x4& z) {
		return sqrt(
			square(x) + square(y) + square(z)
		);
	}

/* Trigonometry */

	Float64x4  sin (const Float64x4& x);
	Float64x4  cos (const Float64x4& x);
	void sincos(const Float64x4& x, Float64x4& p_sin , Float64x4& p_cos );
	inline Float64x4 tan(const Float64x4& x) {
		Float64x4 sin_val, cos_val;
		sincos(x, sin_val, cos_val);
		return sin_val / cos_val;
	}
	Float64x4 asin (const Float64x4& x);
	Float64x4 acos (const Float64x4& x);
	Float64x4 atan (const Float64x4& x);
	Float64x4  sinh(const Float64x4& x);
	Float64x4  cosh(const Float64x4& x);
	void sinhcosh(const Float64x4& x, Float64x4& p_sinh, Float64x4& p_cosh);
	Float64x4  tanh(const Float64x4& x);
	Float64x4 asinh(const Float64x4& x);
	Float64x4 acosh(const Float64x4& x);
	Float64x4 atanh(const Float64x4& x);
	Float64x4 atan2(const Float64x4& y, const Float64x4& x);

/* Logarithms and Exponents */

	Float64x4 log(const Float64x4& x);
	Float64x4 log1p(const Float64x4& x);
	inline Float64x4 log2(const Float64x4& x) {
		return log(x) * LDF::const_log2e<Float64x4>();
	}
	inline Float64x4 log10(const Float64x4& x) {
		return log(x) * LDF::const_log10e<Float64x4>();
	}
	inline Float64x4 logb(const Float64x4& x) { return logb(x.val[0]); }

	Float64x4 exp(const Float64x4& x);
	Float64x4 expm1(const Float64x4& x);
	inline Float64x4 exp2(const Float64x4& x) {
		return exp(x * LDF::const_ln2<Float64x4>());
	}
	inline Float64x4 exp10(const Float64x4& x) {
		return exp(x * LDF::const_ln10<Float64x4>());
	}

	inline Float64x4 pow(const Float64x4& x, const Float64x4& y) {
		return isequal_zero(x) ? (
			isequal_zero(y) ? static_cast<Float64x4>(1.0) : static_cast<Float64x4>(0.0)
		) : exp(y * log(x));
	}
	inline Float64x4 pow(const Float64x4& x, const Float64x2& y) {
		return isequal_zero(x) ? (
			isequal_zero(y) ? static_cast<Float64x4>(1.0) : static_cast<Float64x4>(0.0)
		) : exp(y * log(x));
	}
	inline Float64x4 pow(const Float64x4& x, const fp64 y) {
		return isequal_zero(x) ? (
			(y == static_cast<fp64>(0.0)) ? static_cast<Float64x4>(1.0) : static_cast<Float64x4>(0.0)
		) : exp(y * log(x));
	}

/* Comparison */

	inline constexpr bool isgreater(const Float64x4& x, const Float64x4& y) {
		return (x > y);
	}
	inline constexpr bool isgreaterequal(const Float64x4& x, const Float64x4& y) {
		return (x >= y);
	}
	inline constexpr bool isless(const Float64x4& x, const Float64x4& y) {
		return (x < y);
	}
	inline constexpr bool islessequal(const Float64x4& x, const Float64x4& y) {
		return (x <= y);
	}
	inline constexpr bool islessgreater(const Float64x4& x, const Float64x4& y) {
		return (x < y) || (x > y);
	}

/* Rounding */

	/** 
	 * @author Taken from libQD which can be found under a
	 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
	 */
	inline Float64x4 trunc(const Float64x4& x) {
		return Float64x4_trunc(x);
	}

	/** 
	 * @author Taken from libQD which can be found under a
	 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
	 */
	inline Float64x4 floor(const Float64x4& x) {
		return Float64x4_floor(x);
	}
	
	/** 
	 * @author Taken from libQD which can be found under a
	 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
	 */
	inline Float64x4 ceil(const Float64x4& x) {
		return Float64x4_ceil(x);
	}
	/** 
	 * @author Taken from libQD which can be found under a
	 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
	 */
	inline Float64x4 round(const Float64x4& x) {
		return Float64x4_round(x);
	}
	inline Float64x4 rint(const Float64x4& x) {
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
	inline long lround(const Float64x4& x) {
		return static_cast<long>(round(x));
	}
	inline long lrint(const Float64x4& x) {
		return static_cast<long>(rint(x));
	}
	inline long long llround(const Float64x4& x) {
		return static_cast<long long>(round(x));
	}
	inline long long llrint(const Float64x4& x) {
		return static_cast<long long>(rint(x));
	}

/* Integer and Remainder */

	inline Float64x4 fmod(const Float64x4& x, const Float64x4& y) {
		Float64x4 trunc_part = trunc(x / y);
		return x - y * trunc_part;
	}
	inline Float64x4 modf(const Float64x4& x, Float64x4& int_part) {
		Float64x4 trunc_part = trunc(x);
		int_part = trunc_part;
		return x - trunc_part;
	}
	inline Float64x4 nearbyint(const Float64x4& x) {
		return rint(x);
	}
	inline Float64x4 remainder(const Float64x4& x, const Float64x4& y) {
		Float64x4 round_part = round(x / y);
		return x - y * round_part;
	}
	inline Float64x4 remquo(const Float64x4& x, const Float64x4& y, int& quo) {
		Float64x4 q = round(x / y);
		Float64x4 r = x - y * q;
		quo = static_cast<int>(q.val[0] + q.val[1]);
		return r;
	}

/* Float Exponents */

	/**
	 * @brief Extracts the exponent of a Float64x4 value to compute the
	 * binary logarithm.
	 */
	inline int ilogb(const Float64x4& x) {
		return ilogb(x.val[0] + (x.val[1] + (x.val[2] + x.val[3])));
	}
	/**
	 * @brief Returns a normalized Float64x4 value and the exponent in
	 * the form [0.0, 1.0) * 2^expon
	 */
	inline Float64x4 frexp(const Float64x4& x, int& expon) {
		Float64x4 ret;
		expon = ilogb(x.val[0] + (x.val[1] + (x.val[2] + x.val[3]))) + 1;
		ret.val[0] = ldexp(x.val[0], -(expon));
		ret.val[1] = ldexp(x.val[1], -(expon));
		ret.val[2] = ldexp(x.val[2], -(expon));
		ret.val[3] = ldexp(x.val[3], -(expon));
		return ret;
	}
	/**
	 * @brief Multiplies a Float64x4 value by 2^expon
	 */
	inline Float64x4 ldexp(const Float64x4& x, int expon) {
		Float64x4 ret;
		ret.val[0] = ldexp(x.val[0], expon);
		ret.val[1] = isfinite(x.val[0]) ? ldexp(x.val[1], expon) : x.val[0];
		ret.val[2] = isfinite(x.val[0]) ? ldexp(x.val[2], expon) : x.val[0];
		ret.val[3] = isfinite(x.val[0]) ? ldexp(x.val[3], expon) : x.val[0];
		return ret;
	}
	/**
	 * @brief Multiplies a Float64x4 value by FLT_RADIX^expon
	 */
	inline Float64x4 scalbn(const Float64x4& x, int expon) {
		Float64x4 ret;
		ret.val[0] = scalbn(x.val[0], expon);
		ret.val[1] = isfinite(x.val[0]) ? scalbn(x.val[1], expon) : x.val[0];
		ret.val[2] = isfinite(x.val[0]) ? scalbn(x.val[2], expon) : x.val[0];
		ret.val[3] = isfinite(x.val[0]) ? scalbn(x.val[3], expon) : x.val[0];
		return ret;
	}
	/**
	 * @brief Multiplies a Float64x4 value by FLT_RADIX^expon
	 */
	inline Float64x4 scalbln(const Float64x4& x, long expon) {
		Float64x4 ret;
		ret.val[0] = scalbln(x.val[0], expon);
		ret.val[1] = isfinite(x.val[0]) ? scalbln(x.val[1], expon) : x.val[0];
		ret.val[2] = isfinite(x.val[0]) ? scalbln(x.val[2], expon) : x.val[0];
		ret.val[3] = isfinite(x.val[0]) ? scalbln(x.val[3], expon) : x.val[0];
		return ret;
	}

/* Transcendental Functions */
	
	Float64x4 erf(const Float64x4& x);

	Float64x4 erfc(const Float64x4& x);

	Float64x4 tgamma(const Float64x4& x);

	/** 
	 * @note naive implementation of lgamma(x)
	 */
	inline Float64x4 lgamma(const Float64x4& x) {
		return log(fabs(tgamma(x)));
	}

#endif /* FLOAT64X4_HPP */
