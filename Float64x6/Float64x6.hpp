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

#ifndef FLOAT64X6_HPP
#define FLOAT64X6_HPP

#include "Float64x6_def.h"
#include "Float64x6.h"
#include "../Float64x2/Float64x2.hpp"
#include "../Float64x4/Float64x4.hpp"

#include <cstdint>
#include <cmath>

#include "../FloatNxN/FloatNxN_arithmetic.hpp"

//------------------------------------------------------------------------------
// Float64x6 String Operations
//------------------------------------------------------------------------------

#if 0

#include "Float64x6_string.h"

#if __cplusplus >= 200809L
/**
 * @brief Wrapper for stringTo_Float64x6
 */
inline Float64x6 operator""_FP64X6(const char* str, std::size_t) {
	return stringTo_Float64x6(str, nullptr);
}
#endif

#include <istream>
/**
 * @brief Wrapper for stringTo_Float64x6
 */
std::istream& operator>>(std::istream& stream, Float64x6& value);

#include <ostream>
/**
 * @brief Wrapper for Float64x6_snprintf
 */
std::ostream& operator<<(std::ostream& stream, const Float64x6& value);

#endif

//------------------------------------------------------------------------------
// Float64x6 Compairison
//------------------------------------------------------------------------------

inline constexpr bool operator==(const Float64x6& x, const Float64x6& y) {
	return (
		x.val[0] == y.val[0] && x.val[1] == y.val[1] &&
		x.val[2] == y.val[2] && x.val[3] == y.val[3] &&
		x.val[4] == y.val[4] && x.val[5] == y.val[5]
	);
}
inline constexpr bool operator!=(const Float64x6& x, const Float64x6& y) {
	return (
		x.val[0] != y.val[0] || x.val[1] != y.val[1] ||
		x.val[2] != y.val[2] || x.val[3] != y.val[3] ||
		x.val[4] != y.val[4] || x.val[5] != y.val[5]
	);
}
inline constexpr bool operator<(const Float64x6& x, const Float64x6& y) {
	return
		(x.val[0] == y.val[0]) ? (
			(x.val[1] == y.val[1]) ? (
				(x.val[2] == y.val[2]) ? (
					(x.val[3] == y.val[3]) ? (
						(x.val[4] == y.val[4]) ? (
							x.val[5] < y.val[5]
						) : (x.val[4] < y.val[4])
					) : (x.val[3] < y.val[3])
				) : (x.val[2] < y.val[2])
			) : (x.val[1] < y.val[1])
		) : (x.val[0] < y.val[0]);
}
inline constexpr bool operator<=(const Float64x6& x, const Float64x6& y) {
	return
		(x.val[0] == y.val[0]) ? (
			(x.val[1] == y.val[1]) ? (
				(x.val[2] == y.val[2]) ? (
					(x.val[3] == y.val[3]) ? (
						(x.val[4] == y.val[4]) ? (
							x.val[5] <= y.val[5]
						) : (x.val[4] < y.val[4])
					) : (x.val[3] < y.val[3])
				) : (x.val[2] < y.val[2])
			) : (x.val[1] < y.val[1])
		) : (x.val[0] < y.val[0]);
}
inline constexpr bool operator>(const Float64x6& x, const Float64x6& y) {
	return
		(x.val[0] == y.val[0]) ? (
			(x.val[1] == y.val[1]) ? (
				(x.val[2] == y.val[2]) ? (
					(x.val[3] == y.val[3]) ? (
						(x.val[4] == y.val[4]) ? (
							x.val[5] > y.val[5]
						) : (x.val[4] > y.val[4])
					) : (x.val[3] > y.val[3])
				) : (x.val[2] > y.val[2])
			) : (x.val[1] > y.val[1])
		) : (x.val[0] > y.val[0]);
}
inline constexpr bool operator>=(const Float64x6& x, const Float64x6& y) {
	return
		(x.val[0] == y.val[0]) ? (
			(x.val[1] == y.val[1]) ? (
				(x.val[2] == y.val[2]) ? (
					(x.val[3] == y.val[3]) ? (
						(x.val[4] == y.val[4]) ? (
							x.val[5] >= y.val[5]
						) : (x.val[4] > y.val[4])
					) : (x.val[3] > y.val[3])
				) : (x.val[2] > y.val[2])
			) : (x.val[1] > y.val[1])
		) : (x.val[0] > y.val[0]);
}

//------------------------------------------------------------------------------
// Float64x6 Compairison fp64
//------------------------------------------------------------------------------

inline constexpr bool operator==(const Float64x6& x, const fp64 y) {
	return (x.val[0] == y && x.val[1] == 0.0);
}
inline constexpr bool operator!=(const Float64x6& x, const fp64 y) {
	return (x.val[0] != y || x.val[1] != 0.0);
}
inline constexpr bool operator<(const Float64x6& x, const fp64 y) {
	return (x.val[0] < y || (x.val[0] == y && x.val[1] < 0.0));
}
inline constexpr bool operator<=(const Float64x6& x, const fp64 y) {
	return (x.val[0] < y || (x.val[0] == y && x.val[1] <= 0.0));
}
inline constexpr bool operator>(const Float64x6& x, const fp64 y) {
	return (x.val[0] > y || (x.val[0] == y && x.val[1] > 0.0));
}
inline constexpr bool operator>=(const Float64x6& x, const fp64 y) {
	return (x.val[0] > y || (x.val[0] == y && x.val[1] >= 0.0));
}

inline constexpr bool operator==(const fp64 x, const Float64x6& y) {
	return (x == y.val[0] && 0.0 == y.val[1]);
}
inline constexpr bool operator!=(const fp64 x, const Float64x6& y) {
	return (x != y.val[0] || 0.0 != y.val[1]);
}
inline constexpr bool operator<(const fp64 x, const Float64x6& y) {
	return (x < y.val[0] || (x == y.val[0] && 0.0 < y.val[1]));
}
inline constexpr bool operator<=(const fp64 x, const Float64x6& y) {
	return (x < y.val[0] || (x == y.val[0] && 0.0 <= y.val[1]));
}
inline constexpr bool operator>(const fp64 x, const Float64x6& y) {
	return (x > y.val[0] || (x == y.val[0] && 0.0 > y.val[1]));
}
inline constexpr bool operator>=(const fp64 x, const Float64x6& y) {
	return (x > y.val[0] || (x == y.val[0] && 0.0 >= y.val[1]));
}

//------------------------------------------------------------------------------
// Float64x6 Compare to Zero
//------------------------------------------------------------------------------

/** @brief Assumes that if x.val[0] is zero then x.val[1 - 5] are also zero */
inline constexpr bool isequal_zero(const Float64x6& x) {
	return (x.val[0] == 0.0);
}
/** @brief Assumes that if x.val[0] is zero then x.val[1 - 5] are also zero */
inline constexpr bool isnotequal_zero(const Float64x6& x) {
	return (x.val[0] != 0.0);
}
/** @brief Assumes that if x.val[0] is zero then x.val[1 - 5] are also zero */
inline constexpr bool isless_zero(const Float64x6& x) {
	return (x.val[0] < 0.0);
}
/** @brief Assumes that if x.val[0] is zero then x.val[1 - 5] are also zero */
inline constexpr bool islessequal_zero(const Float64x6& x) {
	return (x.val[0] <= 0.0);
}
/** @brief Assumes that if x.val[0] is zero then x.val[1 - 5] are also zero */
inline constexpr bool isgreater_zero(const Float64x6& x) {
	return (x.val[0] > 0.0);
}
/** @brief Assumes that if x.val[0] is zero then x.val[1 - 5] are also zero */
inline constexpr bool isgreaterequal_zero(const Float64x6& x) {
	return (x.val[0] >= 0.0);
}

//------------------------------------------------------------------------------
// Float64x6 LDF Arithmetic
//------------------------------------------------------------------------------

// template <> inline
// Float64x6 LDF::add<Float64x6, Float64x6, Float64x6>
// (const Float64x6& x, const Float64x6& y) {
// 	return Float64x6_add(x, y);
// }

template <> inline
Float64x6 LDF::add<Float64x6, Float64x6, fp64>
(const Float64x6& x, const fp64& y) {
	return Float64x6_add_dx6_d(x, y);
}

template <> inline
Float64x6 LDF::add<Float64x6, fp64, Float64x6>
(const fp64& x, const Float64x6& y) {
	return Float64x6_add_d_dx6(x, y);
}

/* Subtraction */

// template <> inline
// Float64x6 LDF::add<Float64x6, Float64x6, Float64x6>
// (const Float64x6& x, const Float64x6& y) {
// 	return Float64x6_add(x, y);
// }

template <> inline
Float64x6 LDF::sub<Float64x6, Float64x6, fp64>
(const Float64x6& x, const fp64& y) {
	return Float64x6_sub_dx6_d(x, y);
}

template <> inline
Float64x6 LDF::sub<Float64x6, fp64, Float64x6>
(const fp64& x, const Float64x6& y) {
	return Float64x6_sub_d_dx6(x, y);
}

/* Multiplication */

// template <> inline
// Float64x6 LDF::mul<Float64x6, Float64x6, Float64x6>
// (const Float64x6& x, const Float64x6& y) {
// 	return Float64x6_mul(x, y);
// }

// template <> inline
// Float64x6 LDF::mul<Float64x6, Float64x2, Float64x6>
// (const Float64x2& x, const Float64x6& y) {
// 	return Float64x6_mul_dx6_d(x, y);
// }

// template <> inline
// Float64x6 LDF::mul<Float64x6, fp64, Float64x6>
// (const fp64& x, const Float64x6& y) {
// 	return Float64x6_mul_d_dx6(x, y);
// }

/* Square */

// template <> inline
// Float64x6 LDF::square<Float64x6, Float64x6>
// (const Float64x6& x) {
// 	return Float64x6_square(x);
// }

/* Division */

// template <> inline
// Float64x6 LDF::div<Float64x6, Float64x6, Float64x6>
// (const Float64x6& x, const Float64x6& y) {
// 	return Float64x6_div(x, y);
// }

template <> inline
Float64x6 LDF::div<Float64x6, Float64x6, Float64x2>
(const Float64x6& x, const Float64x2& y) {
	return Float64x6_div_dx6_dx2(x, y);
}

template <> inline
Float64x6 LDF::div<Float64x6, Float64x2, Float64x6>
(const Float64x2& x, const Float64x6& y) {
	return Float64x6_div_dx6_d(x, y);
}

// template <> inline
// Float64x6 LDF::div<Float64x6, Float64x6, fp64>
// (const Float64x6& x, const fp64& y) {
// 	return Float64x6_div_dx2_dx6(x, y);
// }

// template <> inline
// Float64x6 LDF::div<Float64x6, fp64, Float64x6>
// (const fp64& x, const Float64x6& y) {
// 	return Float64x6_div_d_dx6(x, y);
// }

/* Reciprocal */

// template <> inline
// Float64x6 LDF::recip<Float64x6, Float64x6>
// (const Float64x6& x) {
// 	return Float64x6_recip(x);
// }

//------------------------------------------------------------------------------
// Float64x6 LDF Optimized Arithmetic
//------------------------------------------------------------------------------

template <> inline
Float64x6 LDF::add<Float64x6, Float64x4, Float64x4>
(const Float64x4& x, const Float64x4& y) {
	return Float64x6_add_dx4_dx4(x, y);
}

template <> inline
Float64x6 LDF::add<Float64x6, Float64x2, Float64x2>
(const Float64x2& x, const Float64x2& y) {
	return Float64x6_add_dx2_dx2(x, y);
}

template <> inline
Float64x6 LDF::add<Float64x6, Float64x2, fp64>
(const Float64x2& x, const fp64& y) {
	return Float64x6_add_dx2_d(x, y);
}

template <> inline
Float64x6 LDF::add<Float64x6, fp64, Float64x2>
(const fp64& x, const Float64x2& y) {
	return Float64x6_add_d_dx2(x, y);
}

template <> inline
Float64x6 LDF::add<Float64x6, fp64, fp64>
(const fp64& x, const fp64& y) {
	return Float64x6_add_d_d(x, y);
}

/* Subtraction */

template <> inline
Float64x6 LDF::sub<Float64x6, Float64x4, Float64x4>
(const Float64x4& x, const Float64x4& y) {
	return Float64x6_sub_dx4_dx4(x, y);
}

template <> inline
Float64x6 LDF::sub<Float64x6, Float64x2, Float64x2>
(const Float64x2& x, const Float64x2& y) {
	return Float64x6_sub_dx2_dx2(x, y);
}

template <> inline
Float64x6 LDF::sub<Float64x6, Float64x2, fp64>
(const Float64x2& x, const fp64& y) {
	return Float64x6_sub_dx2_d(x, y);
}

template <> inline
Float64x6 LDF::sub<Float64x6, fp64, Float64x2>
(const fp64& x, const Float64x2& y) {
	return Float64x6_sub_d_dx2(x, y);
}

template <> inline
Float64x6 LDF::sub<Float64x6, fp64, fp64>
(const fp64& x, const fp64& y) {
	return Float64x6_sub_d_d(x, y);
}

/* Multiplication */

template <> inline
Float64x6 LDF::mul<Float64x6, Float64x4, Float64x4>
(const Float64x4& x, const Float64x4& y) {
	return Float64x6_mul_dx4_dx4(x, y);
}

template <> inline
Float64x6 LDF::mul<Float64x6, Float64x4, fp64>
(const Float64x4& x, const fp64& y) {
	return Float64x6_mul_dx4_d(x, y);
}

template <> inline
Float64x6 LDF::mul<Float64x6, fp64, Float64x4>
(const fp64& x, const Float64x4& y) {
	return Float64x6_mul_d_dx4(x, y);
}

template <> inline
Float64x6 LDF::mul<Float64x6, Float64x2, Float64x2>
(const Float64x2& x, const Float64x2& y) {
	return Float64x6_mul_dx2_dx2(x, y);
}

template <> inline
Float64x6 LDF::mul<Float64x6, Float64x2, fp64>
(const Float64x2& x, const fp64& y) {
	return Float64x6_mul_dx2_d(x, y);
}

template <> inline
Float64x6 LDF::mul<Float64x6, fp64, Float64x2>
(const fp64& x, const Float64x2& y) {
	return Float64x6_mul_d_dx2(x, y);
}

template <> inline
Float64x6 LDF::mul<Float64x6, fp64, fp64>
(const fp64& x, const fp64& y) {
	return Float64x6_mul_d_d(x, y);
}

/* Square */

template <> inline
Float64x6 LDF::square<Float64x6, Float64x4>
(const Float64x4& x) {
	return Float64x6_square_dx4(x);
}

template <> inline
Float64x6 LDF::square<Float64x6, Float64x2>
(const Float64x2& x) {
	return Float64x6_square_dx2(x);
}

template <> inline
Float64x6 LDF::square<Float64x6, fp64>
(const fp64& x) {
	return Float64x6_square_d(x);
}

/* Division */

// template <> inline
// Float64x6 LDF::div<Float64x6, Float64x2, Float64x2>
// (const Float64x2& x, const Float64x2& y) {
// 	return Float64x6_div_dx2_dx2(x, y);
// }

// template <> inline
// Float64x6 LDF::div<Float64x6, Float64x2, fp64>
// (const Float64x2& x, const fp64& y) {
// 	return Float64x6_div_dx2_d(x, y);
// }

template <> inline
Float64x6 LDF::div<Float64x6, fp64, Float64x2>
(const fp64& x, const Float64x2& y) {
	return Float64x6_div_d_dx2(x, y);
}

template <> inline
Float64x6 LDF::div<Float64x6, fp64, fp64>
(const fp64& x, const fp64& y) {
	return Float64x6_div_d_d(x, y);
}

/* Reciprocal */

// template <> inline
// Float64x6 LDF::recip<Float64x6, Float64x4>
// (const Float64x2& x) {
// 	return Float64x6_recip_dx4(x);
// }

// template <> inline
// Float64x6 LDF::recip<Float64x6, Float64x2>
// (const Float64x2& x) {
// 	return Float64x6_recip_dx2(x);
// }

template <> inline
Float64x6 LDF::recip<Float64x6, fp64>
(const fp64& x) {
	return Float64x6_recip_d(x);
}

//------------------------------------------------------------------------------
// Float64x6 Basic Arithmetic
//------------------------------------------------------------------------------

/* Negation */

inline constexpr Float64x6 operator-(const Float64x6& x) {
	return {-x.val[0], -x.val[1], -x.val[2], -x.val[3], -x.val[4], -x.val[5]};
}

/* Addition */

inline Float64x6 operator+(const Float64x6& x, const Float64x6& y) {
	return Float64x6_add(x, y);
}

inline Float64x6 operator+(const Float64x6& x, const fp64 y) {
	return Float64x6_add_dx6_d(x, y);
}

inline Float64x6 operator+(const fp64 x, const Float64x6& y) {
	return Float64x6_add_d_dx6(x, y);
}

inline Float64x6 operator+(const Float64x6& x, const Float64x4 y) {
	return Float64x6_add_dx6_dx4(x, y);
}

// inline Float64x6 operator+(const Float64x4 x, const Float64x6& y) {
// 	return Float64x6_add_dx4_dx6(x, y);
// }

/* Subtraction */

inline Float64x6 operator-(const Float64x6& x, const Float64x6& y) {
	return Float64x6_sub(x, y);
}

inline Float64x6 operator-(const Float64x6& x, const fp64 y) {
	return Float64x6_sub_dx6_d(x, y);
}

inline Float64x6 operator-(const fp64 x, const Float64x6& y) {
	return Float64x6_sub_d_dx6(x, y);
}

inline Float64x6 operator-(const Float64x6& x, const Float64x4 y) {
	return Float64x6_sub_dx6_dx4(x, y);
}

// inline Float64x6 operator-(const Float64x4 x, const Float64x6& y) {
// 	return Float64x6_sub_dx4_dx6(x, y);
// }

/* Multiplication */

// inline Float64x6 operator*(const Float64x6& x, const Float64x6& y) {
// 	return Float64x6_mul(x, y);
// }

// inline Float64x6 operator*(const Float64x6& x, const fp64 y) {
// 	return Float64x6_mul_dx6_d(x, y);
// }

// inline Float64x6 operator*(const fp64 x, const Float64x6& y) {
// 	return Float64x6_mul_d_dx6(x, y);
// }

/* Square */

// inline Float64x6 square(const Float64x6& x) {
// 	return Float64x6_square(x);
// }

/* Division */

// inline Float64x6 operator/(const Float64x6& x, const Float64x6& y) {
// 	return Float64x6_div(x, y);
// }

inline Float64x6 operator/(const Float64x6& x, const Float64x2& y) {
	return Float64x6_div_dx6_dx2(x, y);
}

inline Float64x6 operator/(const Float64x6& x, const fp64 y) {
	return Float64x6_div_dx6_d(x, y);
}

// inline Float64x6 operator/(const Float64x2& x, const Float64x6& y) {
// 	return Float64x6_div_dx2_dx6(x, y);
// }

// inline Float64x6 operator/(const fp64 x, const Float64x6& y) {
// 	return Float64x6_div_d_dx6(x, y);
// }

/* Reciprocal */

// inline Float64x6 recip(const Float64x6& x) {
// 	return Float64x6_recip(x);
// }

//------------------------------------------------------------------------------
// Float64x6 Compound Assignment
//------------------------------------------------------------------------------

inline Float64x6& operator+=(Float64x6 &x, const Float64x6 &y) {
	x = x + y;
	return x;
}
inline Float64x6& operator-=(Float64x6 &x, const Float64x6 &y) {
	x = x - y;
	return x;
}
// inline Float64x6& operator*=(Float64x6 &x, const Float64x6 &y) {
// 	x = x * y;
// 	return x;
// }
// inline Float64x6& operator/=(Float64x6 &x, const Float64x6 &y) {
// 	x = x / y;
// 	return x;
// }

inline Float64x6& operator+=(Float64x6 &x, const Float64x4 &y) {
	x = x + y;
	return x;
}
inline Float64x6& operator-=(Float64x6 &x, const Float64x4 &y) {
	x = x - y;
	return x;
}
// inline Float64x6& operator*=(Float64x6 &x, const Float64x4 &y) {
// 	x = x * y;
// 	return x;
// }
// inline Float64x6& operator/=(Float64x6 &x, const Float64x4 &y) {
// 	x = x / y;
// 	return x;
// }

// inline Float64x6& operator+=(Float64x6 &x, const Float64x2 &y) {
// 	x = x + y;
// 	return x;
// }
// inline Float64x6& operator-=(Float64x6 &x, const Float64x2 &y) {
// 	x = x - y;
// 	return x;
// }
// inline Float64x6& operator*=(Float64x6 &x, const Float64x2 &y) {
// 	x = x * y;
// 	return x;
// }
inline Float64x6& operator/=(Float64x6 &x, const Float64x2 &y) {
	x = x / y;
	return x;
}

inline Float64x6& operator+=(Float64x6 &x, const fp64 y) {
	x = x + y;
	return x;
}
inline Float64x6& operator-=(Float64x6 &x, const fp64 y) {
	x = x - y;
	return x;
}
// inline Float64x6& operator*=(Float64x6 &x, const fp64 y) {
// 	x = x * y;
// 	return x;
// }
inline Float64x6& operator/=(Float64x6 &x, const fp64 y) {
	x = x / y;
	return x;
}

/* Increment/Decrement */

inline Float64x6& operator++(Float64x6& x) {
	x += 1.0;
	return x;
}

inline Float64x6& operator--(Float64x6& x) {
	x -= 1.0;
	return x;
}

inline Float64x6 operator++(Float64x6& x, int) {
	Float64x6 temp = x;
	x += 1.0;
	return temp;
}

inline Float64x6 operator--(Float64x6& x, int) {
	Float64x6 temp = x;
	x -= 1.0;
	return temp;
}


//------------------------------------------------------------------------------
// Float64x6 specialized arithmetic
//------------------------------------------------------------------------------

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero
 */
inline Float64x6 mul_pwr2(const Float64x6& x, const fp64 y) {
	Float64x6 ret;
	for (int i = 0; i <= 5; i++) {
		ret.val[i] = x.val[i] * y;
	}
	return ret;
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero
 */
inline Float64x6 mul_pwr2(const fp64 x, const Float64x6& y) {
	Float64x6 ret;
	for (int i = 0; i <= 5; i++) {
		ret.val[i] = x * y.val[i];
	}
	return ret;
}

//------------------------------------------------------------------------------
// Float64x6 bitwise operators
//------------------------------------------------------------------------------

template <> inline
Float64x6 LDF::bitwise_not<Float64x6>
(const Float64x6& x) {
	Float64x6 ret = x;
	uint64_t* binary_part = reinterpret_cast<uint64_t*>(&ret);
	for (int i = 0; i <= 5; i++) {
		binary_part[i] = ~binary_part[i];
	}
	return ret;
}

template <> inline
Float64x6 LDF::bitwise_and<Float64x6, Float64x6>
(const Float64x6& x, const Float64x6& y) {
	Float64x6 ret = x;
	uint64_t* ret_bin = reinterpret_cast<uint64_t*>(&ret);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	for (int i = 0; i <= 5; i++) {
		ret_bin[i] &= y_bin[i];
	}
	return ret;
}

template <> inline
Float64x6 LDF::bitwise_andnot<Float64x6, Float64x6>
(const Float64x6& x, const Float64x6& y) {
	Float64x6 ret = x;
	uint64_t* ret_bin = reinterpret_cast<uint64_t*>(&ret);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	for (int i = 0; i <= 5; i++) {
		ret_bin[i] &= ~y_bin[i];
	}
	return ret;
}

template <> inline
Float64x6 LDF::bitwise_or<Float64x6, Float64x6>
(const Float64x6& x, const Float64x6& y) {
	Float64x6 ret = x;
	uint64_t* ret_bin = reinterpret_cast<uint64_t*>(&ret);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	for (int i = 0; i <= 5; i++) {
		ret_bin[i] |= y_bin[i];
	}
	return ret;
}

template <> inline
Float64x6 LDF::bitwise_xor<Float64x6, Float64x6>
(const Float64x6& x, const Float64x6& y) {
	Float64x6 ret = x;
	uint64_t* ret_bin = reinterpret_cast<uint64_t*>(&ret);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	for (int i = 0; i <= 5; i++) {
		ret_bin[i] ^= y_bin[i];
	}
	return ret;
}

template <> inline
Float64x6 LDF::bitwise_and<Float64x6, fp64>
(const Float64x6& x, const fp64& y) {
	Float64x6 ret = x;
	uint64_t* ret_bin = reinterpret_cast<uint64_t*>(&ret);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	for (int i = 0; i <= 5; i++) {
		ret_bin[i] &= *y_bin;
	}
	return ret;
}

template <> inline
Float64x6 LDF::bitwise_andnot<Float64x6, fp64>
(const Float64x6& x, const fp64& y) {
	Float64x6 ret = x;
	uint64_t* ret_bin = reinterpret_cast<uint64_t*>(&ret);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	for (int i = 0; i <= 5; i++) {
		ret_bin[i] &= ~(*y_bin);
	}
	return ret;
}

template <> inline
Float64x6 LDF::bitwise_or<Float64x6, fp64>
(const Float64x6& x, const fp64& y) {
	Float64x6 ret = x;
	uint64_t* ret_bin = reinterpret_cast<uint64_t*>(&ret);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	for (int i = 0; i <= 5; i++) {
		ret_bin[i] |= *y_bin;
	}
	return ret;
}

template <> inline
Float64x6 LDF::bitwise_xor<Float64x6, fp64>
(const Float64x6& x, const fp64& y) {
	Float64x6 ret = x;
	uint64_t* ret_bin = reinterpret_cast<uint64_t*>(&ret);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	for (int i = 0; i <= 5; i++) {
		ret_bin[i] ^= *y_bin;
	}
	return ret;
}

//------------------------------------------------------------------------------
// Float64x6 Constants
//------------------------------------------------------------------------------

/* C++20 <numbers> */

	constexpr Float64x6 Float64x6_e          = {0x1.5bf0a8b145769p+1,+0x1.4d57ee2b1013ap-53,-0x1.618713a31d3e2p-109,+0x1.c5a6d2b53c26dp-163,0.0,0.0}; /**< ~2.718281828 */
	constexpr Float64x6 Float64x6_log2e      = {0x1.71547652b82fep+0,+0x1.777d0ffda0d24p-56,-0x1.60bb8a5442ab9p-110,-0x1.4b52d3ba6d74dp-166,0.0,0.0}; /**< ~1.442695041 */
	constexpr Float64x6 Float64x6_log10e     = {0x1.bcb7b1526e50ep-2,+0x1.95355baaafad3p-57,+0x1.ee191f71a3012p-112,+0x1.7268808e8fcb5p-167,0.0,0.0}; /**< ~0.434294482 */
	constexpr Float64x6 Float64x6_pi         = {0x1.921fb54442d18p+1,+0x1.1a62633145c07p-53,-0x1.f1976b7ed8fbcp-109,+0x1.4cf98e804177dp-163,0.0,0.0}; /**< ~3.141592654 */
	constexpr Float64x6 Float64x6_inv_pi     = {0x1.45f306dc9c883p-2,-0x1.6b01ec5417056p-56,-0x1.6447e493ad4cep-110,+0x1.e21c820ff28b2p-164,0.0,0.0}; /**< ~0.318309886 */
	constexpr Float64x6 Float64x6_inv_sqrtpi = {0x1.20dd750429b6dp-1,+0x1.1ae3a914fed80p-57,-0x1.3cbbebf65f145p-112,-0x1.e0c574632f53ep-167,0.0,0.0}; /**< ~0.564189584 */
	constexpr Float64x6 Float64x6_ln2        = {0x1.62e42fefa39efp-1,+0x1.abc9e3b39803fp-56,+0x1.7b57a079a1934p-111,-0x1.ace93a4ebe5d1p-165,0.0,0.0}; /**< ~0.693147181 */
	constexpr Float64x6 Float64x6_ln10       = {0x1.26bb1bbb55516p+1,-0x1.f48ad494ea3e9p-53,-0x1.9ebae3ae0260cp-107,-0x1.2d10378be1cf1p-161,0.0,0.0}; /**< ~2.302585093 */
	constexpr Float64x6 Float64x6_sqrt2      = {0x1.6a09e667f3bcdp+0,-0x1.bdd3413b26456p-54,+0x1.57d3e3adec175p-108,+0x1.2775099da2f59p-164,0.0,0.0}; /**< ~1.414213562 */
	constexpr Float64x6 Float64x6_sqrt3      = {0x1.bb67ae8584caap+0,+0x1.cec95d0b5c1e3p-54,-0x1.f11db689f2ccfp-110,+0x1.3da4798c720a6p-164,0.0,0.0}; /**< ~1.732050808 */
	constexpr Float64x6 Float64x6_inv_sqrt3  = {0x1.279a74590331cp-1,+0x1.34863e0792bedp-55,-0x1.a82f9e6c53222p-109,-0x1.cb0f41134253ap-163,0.0,0.0}; /**< ~0.577350269 */
	constexpr Float64x6 Float64x6_egamma     = {0x1.2788cfc6fb619p-1,-0x1.6cb90701fbfabp-58,-0x1.34a95e3133c51p-112,+0x1.9730064300f7dp-166,0.0,0.0}; /**< ~0.577215665 */
	constexpr Float64x6 Float64x6_phi        = {0x1.9e3779b97f4a8p+0,-0x1.f506319fcfd19p-55,+0x1.b906821044ed8p-109,-0x1.8bb1b5c0f272cp-165,0.0,0.0}; /**< ~1.618033989 */

#if __cplusplus >= 201907L
#include <numbers>
namespace std {
	namespace numbers {
		template<> inline constexpr Float64x6 e_v          <Float64x6> = Float64x6_e         ; /**< ~2.718281828 */
		template<> inline constexpr Float64x6 log2e_v      <Float64x6> = Float64x6_log2e     ; /**< ~1.442695041 */
		template<> inline constexpr Float64x6 log10e_v     <Float64x6> = Float64x6_log10e    ; /**< ~0.434294482 */
		template<> inline constexpr Float64x6 pi_v         <Float64x6> = Float64x6_pi        ; /**< ~3.141592654 */
		template<> inline constexpr Float64x6 inv_pi_v     <Float64x6> = Float64x6_inv_pi    ; /**< ~0.318309886 */
		template<> inline constexpr Float64x6 inv_sqrtpi_v <Float64x6> = Float64x6_inv_sqrtpi; /**< ~0.564189584 */
		template<> inline constexpr Float64x6 ln2_v        <Float64x6> = Float64x6_ln2       ; /**< ~0.693147181 */
		template<> inline constexpr Float64x6 ln10_v       <Float64x6> = Float64x6_ln10      ; /**< ~2.302585093 */
		template<> inline constexpr Float64x6 sqrt2_v      <Float64x6> = Float64x6_sqrt2     ; /**< ~1.414213562 */
		template<> inline constexpr Float64x6 sqrt3_v      <Float64x6> = Float64x6_sqrt3     ; /**< ~1.732050808 */
		template<> inline constexpr Float64x6 inv_sqrt3_v  <Float64x6> = Float64x6_inv_sqrt3 ; /**< ~0.577350269 */
		template<> inline constexpr Float64x6 egamma_v     <Float64x6> = Float64x6_egamma    ; /**< ~0.577215665 */
		template<> inline constexpr Float64x6 phi_v        <Float64x6> = Float64x6_phi       ; /**< ~1.618033989 */
	}
}
#endif

constexpr Float64x6 Float64x6_sqrtpi = {0x1.c5bf891b4ef6bp+0,-0x1.618f13eb7ca89p-54,-0x1.b1f0071b7aae4p-110,-0x1.389b5a46bdfe8p-165,0.0,0.0}; /**< ~1.772453851 */

constexpr Float64x6 Float64x6_2pi    = {0x1.921fb54442d18p+2,+0x1.1a62633145c07p-52,-0x1.f1976b7ed8fbcp-108,+0x1.4cf98e804177dp-162,0.0,0.0}; /**< ~6.283185307 */
constexpr Float64x6 Float64x6_pi2    = {0x1.921fb54442d18p+0,+0x1.1a62633145c07p-54,-0x1.f1976b7ed8fbcp-110,+0x1.4cf98e804177dp-164,0.0,0.0}; /**< ~1.570796327 */
constexpr Float64x6 Float64x6_pi4    = {0x1.921fb54442d18p-1,+0x1.1a62633145c07p-55,-0x1.f1976b7ed8fbcp-111,+0x1.4cf98e804177dp-165,0.0,0.0}; /**< ~0.785398163 */
constexpr Float64x6 Float64x6_3pi4   = {0x1.2d97c7f3321d2p+1,+0x1.a79394c9e8a0ap-54,+0x1.456737b06ea1ap-108,-0x1.83226a8fe7731p-162,0.0,0.0}; /**< ~2.356194490 */
constexpr Float64x6 Float64x6_tau    = Float64x6_2pi; /**< ~6.283185307 */

//------------------------------------------------------------------------------
// Float64x6 math.h functions
//------------------------------------------------------------------------------

/* Floating Point Classify */

	/** @brief Returns true if x is negative */
	inline constexpr bool signbit(const Float64x6& x) {
		return std::signbit(x.val[0]);
	}

	/** @brief Returns true if x is finite */
	inline constexpr bool isfinite(const Float64x6& x) {
		return std::isfinite(x.val[0]);
	}

	/** @brief Returns true if x is +-infinity */
	inline constexpr bool isinf(const Float64x6& x) {
		return std::isinf(x.val[0]);
	}

	/** @brief Returns true if x is any kind of NaN */
	inline constexpr bool isnan(const Float64x6& x) {
		return std::isnan(x.val[0]);
	}

	/** @brief Returns true if x is normal */
	inline constexpr bool isnormal(const Float64x6& x) {
		return (
			std::isnormal(x.val[0]) && std::isnormal(x.val[1]) &&
			std::isnormal(x.val[2]) && std::isnormal(x.val[3]) &&
			std::isnormal(x.val[3]) && std::isnormal(x.val[4])
		);
	}

	/** @brief Returns true if x and y are unordered */
	inline constexpr bool isunordered(const Float64x6& x, const Float64x6& y) {
		return std::isunordered(x.val[0], y.val[0]);
	}

	inline constexpr int fpclassify(const Float64x6& x) {
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
	inline constexpr Float64x6 fmax(const Float64x6& x, const Float64x6& y) {
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
	inline constexpr Float64x6 fmin(const Float64x6& x, const Float64x6& y) {
		return
			(x > y) ? y :
			(y > x) ? x :
			isnan(x) ? y :
			isnan(y) ? x :
			signbit(x) ? x : y;
	}

/* Arithmetic */

	inline constexpr Float64x6 fmax(const Float64x6& x, const Float64x6& y, const Float64x6& z) {
		return fmax(fmax(x, y), z);
	}
	inline constexpr Float64x6 fmin(const Float64x6& x, const Float64x6& y, const Float64x6& z) {
		return fmin(fmin(x, y), z);
	}
	inline constexpr Float64x6 fabs(const Float64x6& x) {
		return (isless_zero(x)) ? -x : x;
	}

	inline constexpr Float64x6 fdim(const Float64x6& x, const Float64x6& y) {
		return (x > y) ? (x - y) : static_cast<Float64x6>(0.0);
	}

	// /** @note Naive implementation of fma (Fused multiply add). May lose precision */
	// inline Float64x6 fma(const Float64x6& x, const Float64x6& y, const Float64x6& z) {
	// 	return (x * y) + z;
	// }

	inline constexpr Float64x6 copysign(const Float64x6& x, const Float64x6& y) {
		return (isless_zero(x)) != (isless_zero(y)) ? -x : x;
	}
	// inline Float64x6 sqrt(const Float64x6& x) {
	// 	return Float64x6_sqrt(x);
	// }
	// inline Float64x6 cbrt(const Float64x6& x) {
	// 	return Float64x6_cbrt(x);
	// }

	// /** @note Naive implementation of hypot, may overflow for large inputs */
	// inline Float64x2 hypot(const Float64x6& x, const Float64x6& y) {
	// 	return sqrt(
	// 		square(x) + square(y)
	// 	);
	// }

	// /** @note Naive implementation of hypot, may overflow for large inputs */
	// inline Float64x2 hypot(const Float64x6& x, const Float64x6& y, const Float64x6& z) {
	// 	return sqrt(
	// 		square(x) + square(y) + square(z)
	// 	);
	// }

/* Comparison */

	inline constexpr bool isgreater(const Float64x6& x, const Float64x6& y) {
		return (x > y);
	}
	inline constexpr bool isgreaterequal(const Float64x6& x, const Float64x6& y) {
		return (x >= y);
	}
	inline constexpr bool isless(const Float64x6& x, const Float64x6& y) {
		return (x < y);
	}
	inline constexpr bool islessequal(const Float64x6& x, const Float64x6& y) {
		return (x <= y);
	}
	inline constexpr bool islessgreater(const Float64x6& x, const Float64x6& y) {
		return (x < y) || (x > y);
	}

/* Rounding */

	/** 
	 * @author Taken from libQD which can be found under a
	 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
	 */
	inline Float64x6 trunc(const Float64x6& x) {
		return Float64x6_trunc(x);
	}

	/** 
	 * @author Taken from libQD which can be found under a
	 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
	 */
	inline Float64x6 floor(const Float64x6& x) {
		return Float64x6_floor(x);
	}
	
	/** 
	 * @author Taken from libQD which can be found under a
	 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
	 */
	inline Float64x6 ceil(const Float64x6& x) {
		return Float64x6_ceil(x);
	}
	/** 
	 * @author Taken from libQD which can be found under a
	 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
	 */
	inline Float64x6 round(const Float64x6& x) {
		return Float64x6_round(x);
	}
	inline Float64x6 rint(const Float64x6& x) {
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
	inline long lround(const Float64x6& x) {
		return static_cast<long>(round(x));
	}
	inline long lrint(const Float64x6& x) {
		return static_cast<long>(rint(x));
	}
	inline long long llround(const Float64x6& x) {
		return static_cast<long long>(round(x));
	}
	inline long long llrint(const Float64x6& x) {
		return static_cast<long long>(rint(x));
	}

/* Integer and Remainder */

	// inline Float64x6 fmod(const Float64x6& x, const Float64x6& y) {
	// 	Float64x6 trunc_part = trunc(x / y);
	// 	return x - y * trunc_part;
	// }
	// inline Float64x6 modf(const Float64x6& x, Float64x6& int_part) {
	// 	Float64x6 trunc_part = trunc(x);
	// 	int_part = trunc_part;
	// 	return x - trunc_part;
	// }
	// inline Float64x6 nearbyint(const Float64x6& x) {
	// 	return rint(x);
	// }
	// inline Float64x6 remainder(const Float64x6& x, const Float64x6& y) {
	// 	Float64x6 round_part = round(x / y);
	// 	return x - y * round_part;
	// }
	// inline Float64x6 remquo(const Float64x6& x, const Float64x6& y, int& quo) {
	// 	Float64x6 q = round(x / y);
	// 	Float64x6 r = x - y * q;
	// 	quo = static_cast<int>(q.val[0] + q.val[1]);
	// 	return r;
	// }

/* Float Exponents */

	/**
	 * @brief Extracts the exponent of a Float64x6 value to compute the
	 * binary logarithm.
	 */
	inline int ilogb(const Float64x6& x) {
		return ilogb(x.val[0] + (x.val[1] + (x.val[2] + x.val[3])));
	}
	/**
	 * @brief Returns a normalized Float64x6 value and the exponent in
	 * the form [0.0, 1.0) * 2^expon
	 */
	inline Float64x6 frexp(const Float64x6& x, int& expon) {
		Float64x6 ret;
		expon = ilogb(x.val[0] + (x.val[1] + (x.val[2] + x.val[3]))) + 1;
		ret.val[0] = ldexp(x.val[0], -(expon));
		ret.val[1] = ldexp(x.val[1], -(expon));
		ret.val[2] = ldexp(x.val[2], -(expon));
		ret.val[3] = ldexp(x.val[3], -(expon));
		return ret;
	}
	/**
	 * @brief Multiplies a Float64x6 value by 2^expon
	 */
	inline Float64x6 ldexp(const Float64x6& x, int expon) {
		Float64x6 ret;
		ret.val[0] = ldexp(x.val[0], expon);
		ret.val[1] = isfinite(x.val[0]) ? ldexp(x.val[1], expon) : x.val[0];
		ret.val[2] = isfinite(x.val[0]) ? ldexp(x.val[2], expon) : x.val[0];
		ret.val[3] = isfinite(x.val[0]) ? ldexp(x.val[3], expon) : x.val[0];
		return ret;
	}
	/**
	 * @brief Multiplies a Float64x6 value by FLT_RADIX^expon
	 */
	inline Float64x6 scalbn(const Float64x6& x, int expon) {
		Float64x6 ret;
		ret.val[0] = scalbn(x.val[0], expon);
		ret.val[1] = isfinite(x.val[0]) ? scalbn(x.val[1], expon) : x.val[0];
		ret.val[2] = isfinite(x.val[0]) ? scalbn(x.val[2], expon) : x.val[0];
		ret.val[3] = isfinite(x.val[0]) ? scalbn(x.val[3], expon) : x.val[0];
		return ret;
	}
	/**
	 * @brief Multiplies a Float64x6 value by FLT_RADIX^expon
	 */
	inline Float64x6 scalbln(const Float64x6& x, long expon) {
		Float64x6 ret;
		ret.val[0] = scalbln(x.val[0], expon);
		ret.val[1] = isfinite(x.val[0]) ? scalbln(x.val[1], expon) : x.val[0];
		ret.val[2] = isfinite(x.val[0]) ? scalbln(x.val[2], expon) : x.val[0];
		ret.val[3] = isfinite(x.val[0]) ? scalbln(x.val[3], expon) : x.val[0];
		return ret;
	}

#endif /* FLOAT64X6_HPP */
