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
#include "Float64x6_constants.hpp"

//------------------------------------------------------------------------------
// Float64x6 LDF Type Information
//------------------------------------------------------------------------------

#include "../LDF/LDF_type_info.hpp"
namespace LDF {
	template<> struct LDF_Type_Info<Float64x6> {
		static constexpr int FloatBase_Count = 6;
		static constexpr bool to_string_implemented = false;
		static constexpr bool from_string_implemented = false;
		static constexpr bool arithmetic_implemented = false;
		static constexpr bool numeric_limits_implemented = false;
		static constexpr bool bitwise_implemented = true;
		static constexpr bool constants_implemented = true;
		static constexpr bool basic_C99_math_implemented = false;
		static constexpr bool accurate_C99_math_implemented = false;
	};
}

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

template<typename T> inline constexpr T const_pi            (); /**< ~3.141592654 */
template<typename T> inline constexpr T const_2pi           (); /**< ~6.283185307 */
template<typename T> inline constexpr T const_pi2           (); /**< ~1.570796327 */
template<typename T> inline constexpr T const_pi4           (); /**< ~0.785398163 */
template<typename T> inline constexpr T const_3pi4          (); /**< ~2.356194490 */
template<typename T> inline constexpr T const_pi3           (); /**< ~1.047197551 */

template<typename T> inline constexpr T const_inv_pi        (); /**< ~0.318309886 */
template<typename T> inline constexpr T const_inv_2pi       (); /**< ~0.159154943 */
template<typename T> inline constexpr T const_sqrtpi        (); /**< ~1.772453851 */
template<typename T> inline constexpr T const_sqrt2pi       (); /**< ~2.506628275 */
template<typename T> inline constexpr T const_inv_sqrtpi    (); /**< ~0.564189584 */
template<typename T> inline constexpr T const_inv_sqrt2pi   (); /**< ~0.398942280 */

template<typename T> inline constexpr T const_e             (); /**< ~2.718281828 */
template<typename T> inline constexpr T const_inv_e         (); /**< ~0.367879441 */
template<typename T> inline constexpr T const_ln2           (); /**< ~0.693147181 */
template<typename T> inline constexpr T const_ln3           (); /**< ~1.098612289 */
template<typename T> inline constexpr T const_ln10          (); /**< ~2.302585093 */
template<typename T> inline constexpr T const_log2e         (); /**< ~1.442695041 */
template<typename T> inline constexpr T const_log3e         (); /**< ~0.910239227 */
template<typename T> inline constexpr T const_log10e        (); /**< ~0.434294482 */

template<typename T> inline constexpr T const_sqrt2         (); /**< ~1.414213562 */
template<typename T> inline constexpr T const_sqrt3         (); /**< ~1.732050808 */
template<typename T> inline constexpr T const_sqrt5         (); /**< ~2.236067977 */
template<typename T> inline constexpr T const_sqrt6         (); /**< ~2.449489743 */
template<typename T> inline constexpr T const_inv_sqrt2     (); /**< ~0.707106781 */
template<typename T> inline constexpr T const_inv_sqrt3     (); /**< ~0.577350269 */
template<typename T> inline constexpr T const_inv_sqrt5     (); /**< ~0.447213595 */
template<typename T> inline constexpr T const_inv_sqrt6     (); /**< ~0.408248290 */

template<typename T> inline constexpr T const_cbrt2         (); /**< ~1.259921050 */
template<typename T> inline constexpr T const_cbrt3         (); /**< ~1.442249570 */
template<typename T> inline constexpr T const_cbrt5         (); /**< ~1.709975947 */
template<typename T> inline constexpr T const_cbrt6         (); /**< ~1.817120593 */
template<typename T> inline constexpr T const_inv_cbrt2     (); /**< ~0.793700526 */
template<typename T> inline constexpr T const_inv_cbrt3     (); /**< ~0.693361274 */
template<typename T> inline constexpr T const_inv_cbrt5     (); /**< ~0.584803548 */
template<typename T> inline constexpr T const_inv_cbrt6     (); /**< ~0.550321208 */

template<typename T> inline constexpr T const_egamma        (); /**< ~0.577215665 */
template<typename T> inline constexpr T const_phi           (); /**< ~1.618033989 */
template<typename T> inline constexpr T const_tribonacci    (); /**< ~1.839286755 */
template<typename T> inline constexpr T const_inv_tribonacci(); /**< ~0.543689013 */
template<typename T> inline constexpr T const_catalan       (); /**< ~0.915965594 */
template<typename T> inline constexpr T const_apery         (); /**< ~1.202056903 */
template<typename T> inline constexpr T const_gompertz      (); /**< ~0.596347362 */
template<typename T> inline constexpr T const_lemniscate    (); /**< ~2.622057554 */
template<typename T> inline constexpr T const_2lemniscate   (); /**< ~5.244115109 */
template<typename T> inline constexpr T const_lemniscate2   (); /**< ~1.311028777 */
template<typename T> inline constexpr T const_gauss         (); /**< ~0.834626842 */

namespace LDF {

template<> inline constexpr Float64x6 const_pi<Float64x6>() { return {
	 3.141592653589793116e+00,
	+1.224646799147353207e-16,
	-2.994769809718339666e-33,
	+1.112454220863365282e-49,
	+5.672231979640315744e-66,
	+1.744986216135248601e-83
}; } /**< ~3.141592654 */
template<> inline constexpr Float64x6 const_2pi<Float64x6>() { return {
	 6.283185307179586232e+00,
	+2.449293598294706414e-16,
	-5.989539619436679332e-33,
	+2.224908441726730563e-49,
	+1.134446395928063149e-65,
	+3.489972432270497202e-83
}; } /**< ~6.283185307 */
template<> inline constexpr Float64x6 const_pi2<Float64x6>() { return {
	 1.570796326794896558e+00,
	+6.123233995736766036e-17,
	-1.497384904859169833e-33,
	+5.562271104316826408e-50,
	+2.836115989820157872e-66,
	+8.724931080676243006e-84
}; } /**< ~1.570796327 */
template<> inline constexpr Float64x6 const_pi4           <Float64x6>() { return {
	7.853981633974482790e-01,+3.061616997868383018e-17,-7.486924524295849165e-34,+2.781135552158413204e-50,+1.418057994910078936e-66,+4.362465540338121503e-84
}; } /**< ~0.785398163 */
template<> inline constexpr Float64x6 const_3pi4          <Float64x6>() { return {
	2.356194490192344837e+00,+9.184850993605148438e-17,+3.916898464750400322e-33,-2.586798163270486418e-49,-4.936098881496625656e-67,+1.308739662101436542e-83
}; } /**< ~2.356194490 */
template<> inline constexpr Float64x6 const_pi3           <Float64x6>() { return {
	1.047197551196597853e+00,-1.072081766451090985e-16,-9.982566032394464413e-34,-7.695615360182150485e-50,+1.890743993213438669e-66,-8.203502880647019698e-83
}; } /**< ~1.047197551 */

template<> inline constexpr Float64x6 const_inv_pi        <Float64x6>() { return {
	3.183098861837906912e-01,-1.967867667518248588e-17,-1.072143628289300400e-33,+8.053563926594111967e-50,-1.560276590681971366e-66,+2.837013931191472250e-83
}; } /**< ~0.318309886 */
template<> inline constexpr Float64x6 const_inv_2pi       <Float64x6>() { return {
	1.591549430918953456e-01,-9.839338337591242941e-18,-5.360718141446502002e-34,+4.026781963297055983e-50,-7.801382953409856832e-67,+1.418506965595736125e-83
}; } /**< ~0.159154943 */
template<> inline constexpr Float64x6 const_sqrtpi        <Float64x6>() { return {
	1.772453850905516104e+00,-7.666586499825798697e-17,-1.305833490794542906e-33,-2.611014208782715459e-50,-1.635226728322456135e-66,-1.319908968951995436e-84
}; } /**< ~1.772453851 */
template<> inline constexpr Float64x6 const_sqrt2pi       <Float64x6>() { return {
	2.506628274631000686e+00,-1.832857998045916677e-16,-7.345337700682642697e-33,+5.880128511846697217e-50,+1.701441873594096525e-66,+2.650066430963790315e-83
}; } /**< ~2.506628275 */
template<> inline constexpr Float64x6 const_inv_sqrtpi    <Float64x6>() { return {
	5.641895835477562793e-01,+7.667729806582940611e-18,-2.382842298346843148e-34,-1.003897330827631504e-50,-5.637849999359878193e-67,+1.491253114529702828e-83
}; } /**< ~0.564189584 */
template<> inline constexpr Float64x6 const_inv_sqrt2pi   <Float64x6>() { return {
	3.989422804014327029e-01,-2.492327202277730044e-17,-3.424925447729621017e-34,+3.080222938252878104e-51,-2.963903308026915160e-67,-1.012366222885331172e-83
}; } /**< ~0.398942280 */

template<> inline constexpr Float64x6 const_e             <Float64x6>() { return {
	2.718281828459045091e+00,+1.445646891729250158e-16,-2.127717108038176765e-33,+1.515630159841219144e-49,-9.335381378820847382e-66,-2.021852603357621118e-82
}; } /**< ~2.718281828 */
template<> inline constexpr Float64x6 const_inv_e         <Float64x6>() { return {
	3.678794411714423340e-01,-1.242875367278836258e-17,-5.830044851072742004e-34,-2.826797784901743573e-50,-1.756507513682211809e-66,+3.846150547835715110e-85
}; } /**< ~0.367879441 */
template<> inline constexpr Float64x6 const_ln2           <Float64x6>() { return {
	6.931471805599452862e-01,+2.319046813846299558e-17,+5.707708438416212066e-34,-3.582432210601811423e-50,-1.352169675798862957e-66,+6.080638740240813910e-83
}; } /**< ~0.693147181 */
template<> inline constexpr Float64x6 const_ln3           <Float64x6>() { return {
	1.098612288668109782e+00,-9.071297235001529955e-17,-8.691436473170396324e-34,-2.171042457240107544e-50,-8.042477581389225997e-67,-6.443686469593347935e-83
}; } /**< ~1.098612289 */
template<> inline constexpr Float64x6 const_ln10          <Float64x6>() { return {
	2.302585092994045901e+00,-2.170756223382249351e-16,-9.984262454465776570e-33,-4.023357454450206379e-49,+1.928899528969337192e-65,-5.212570118151255128e-82
}; } /**< ~2.302585093 */
template<> inline constexpr Float64x6 const_log2e         <Float64x6>() { return {
	1.442695040888963387e+00,+2.035527374093103311e-17,-1.061465995611725787e-33,-1.383671678018140168e-50,+9.509563257128723839e-67,-6.180554812704205685e-83
}; } /**< ~1.442695041 */
template<> inline constexpr Float64x6 const_log3e         <Float64x6>() { return {
	9.102392266268374277e-01,-3.406628736007232203e-17,-3.169480364331625582e-34,-1.631816369235663708e-50,+7.313420398045376643e-68,-1.517798051184513188e-84
}; } /**< ~0.910239227 */
template<> inline constexpr Float64x6 const_log10e        <Float64x6>() { return {
	4.342944819032518167e-01,+1.098319650216765073e-17,+3.717181233110958967e-34,+7.734484346504298627e-51,+9.211851210636510972e-68,+3.854714488846810682e-84
}; } /**< ~0.434294482 */

template<> inline constexpr Float64x6 const_sqrt2         <Float64x6>() { return {
	1.414213562373095145e+00,-9.667293313452913451e-17,+4.138675308699413563e-33,+4.935546991468350912e-50,+4.089404286119895809e-67,+3.105543128824933331e-84
}; } /**< ~1.414213562 */
template<> inline constexpr Float64x6 const_sqrt3         <Float64x6>() { return {
	1.732050807568877193e+00,+1.003508422180690280e-16,-1.495954247573389563e-33,+5.306147563296169417e-50,+2.686605845246563101e-66,-2.478595051888444829e-83
}; } /**< ~1.732050808 */
template<> inline constexpr Float64x6 const_sqrt5         <Float64x6>() { return {
	2.236067977499789805e+00,-1.086423040736501230e-16,+5.308650416763130923e-33,-6.609983995004215569e-50,+1.321623789900406164e-66,-1.575905681718208479e-83
}; } /**< ~2.236067977 */
template<> inline constexpr Float64x6 const_sqrt6         <Float64x6>() { return {
	2.449489742783177881e+00,+2.168616518103246086e-16,+8.240049980770320147e-33,-4.434369519944876985e-50,-4.133791270603299758e-66,-2.024042754626873470e-82
}; } /**< ~2.449489743 */
template<> inline constexpr Float64x6 const_inv_sqrt2     <Float64x6>() { return {
	7.071067811865475727e-01,-4.833646656726456726e-17,+2.069337654349706781e-33,+2.467773495734175456e-50,+2.044702143059947904e-67,+1.552771564412466666e-84
}; } /**< ~0.707106781 */
template<> inline constexpr Float64x6 const_inv_sqrt3     <Float64x6>() { return {
	5.773502691896257311e-01,+3.345028073935634473e-17,-2.552976689870847927e-33,-1.533697829015799630e-49,+7.225913778922053356e-66,+1.674413155475472511e-82
}; } /**< ~0.577350269 */
template<> inline constexpr Float64x6 const_inv_sqrt5     <Float64x6>() { return {
	4.472135954999579277e-01,+1.157822992402467192e-17,+7.535812922506684652e-34,-3.032566213459848327e-50,+2.643247579800812263e-67,+3.437062351082659966e-84
}; } /**< ~0.447213595 */
template<> inline constexpr Float64x6 const_inv_sqrt6     <Float64x6>() { return {
	4.082482904638630172e-01,-8.638255191177818720e-19,-6.908130015799011614e-36,+6.276782637017912716e-52,+3.419936361101998303e-69,+2.398341800410987267e-85
}; } /**< ~0.408248290 */

template<> inline constexpr Float64x6 const_cbrt2         <Float64x6>() { return {
	1.259921049894873191e+00,-2.589933375300506918e-17,+9.727808156156372402e-34,+5.932267471174277737e-50,-2.246440688020624924e-66,-2.458434394006098660e-83
}; } /**< ~1.259921050 */
template<> inline constexpr Float64x6 const_cbrt3         <Float64x6>() { return {
	1.442249570307408302e+00,+8.054912676113687134e-17,-2.618247242901535899e-33,-2.824357315193685883e-50,+2.900744408586919721e-67,+1.444064567067935932e-83
}; } /**< ~1.442249570 */
template<> inline constexpr Float64x6 const_cbrt5         <Float64x6>() { return {
	1.709975946676697056e+00,-6.679487771389463610e-17,+4.267291597281299356e-33,+2.263656361985388306e-49,+1.799473831432815999e-65,-1.023585886776559103e-81
}; } /**< ~1.709975947 */
template<> inline constexpr Float64x6 const_cbrt6         <Float64x6>() { return {
	1.817120592832139669e+00,-1.053461653145814723e-17,+5.770942774615513103e-34,+3.354496791720487423e-50,+8.548479073903950772e-67,+5.680350185232122145e-83
}; } /**< ~1.817120593 */
template<> inline constexpr Float64x6 const_inv_cbrt2     <Float64x6>() { return {
	7.937005259840997917e-01,-5.434504097098911493e-17,+4.690480978357969268e-34,+1.341866407751138654e-50,+2.406049381289333864e-67,+4.992203492282150977e-84
}; } /**< ~0.793700526 */
template<> inline constexpr Float64x6 const_inv_cbrt3     <Float64x6>() { return {
	6.933612743506346598e-01,+4.499680387265698707e-17,+7.461963611696051741e-34,-1.650780102808548231e-50,+6.961899480718624787e-67,-4.621037867505127705e-83
}; } /**< ~0.693361274 */
template<> inline constexpr Float64x6 const_inv_cbrt5     <Float64x6>() { return {
	5.848035476425732515e-01,-3.840686705794331653e-17,-1.861690042334640117e-33,-6.874880988134781036e-50,+4.545567304684541433e-66,-1.310051095724338537e-82
}; } /**< ~0.584803548 */
template<> inline constexpr Float64x6 const_inv_cbrt6     <Float64x6>() { return {
	5.503212081491044572e-01,-9.851067964905208562e-18,+5.965810966617877789e-34,+1.805683742763388315e-51,-1.086263325406558592e-67,-7.448530750729387164e-84
}; } /**< ~0.550321208 */

template<> inline constexpr Float64x6 const_egamma        <Float64x6>() { return {
	5.772156649015328655e-01,-4.942915152430644868e-18,-2.322111740706956918e-34,+1.700494743381096356e-50,-4.287892348559799332e-67,-1.957275465032419563e-83
}; } /**< ~0.577215665 */
template<> inline constexpr Float64x6 const_phi           <Float64x6>() { return {
	1.618033988749894903e+00,-5.432115203682506149e-17,+2.654325208381565462e-33,-3.304991997502107784e-50,+6.608118949502030822e-67,-7.879528408591042395e-84
}; } /**< ~1.618033989 */
template<> inline constexpr Float64x6 const_tribonacci    <Float64x6>() { return {
	1.839286755214161184e+00,-5.166128711235951994e-17,+1.640165092040780304e-33,-1.813002943644954296e-50,-1.128119774203387975e-66,+7.722023515147064369e-84
}; } /**< ~1.839286755 */
template<> inline constexpr Float64x6 const_inv_tribonacci<Float64x6>() { return {
	5.436890126920763677e-01,-6.156766738133783152e-18,+1.187931874837851405e-34,-8.252416427936383413e-51,+4.263801369891551482e-67,-2.699266310328856058e-83
}; } /**< ~0.543689013 */
template<> inline constexpr Float64x6 const_catalan       <Float64x6>() { return {
	9.159655941772190113e-01,+3.747558421514983845e-18,-2.281215906674146270e-34,+4.708639405026647471e-51,+2.091934547785599337e-67,+2.851821465459077286e-84
}; } /**< ~0.915965594 */
template<> inline constexpr Float64x6 const_apery         <Float64x6>() { return {
	1.202056903159594237e+00,+4.875891010379531804e-17,-2.985864108294299059e-33,-3.053579984245075500e-50,+1.597688911525348128e-66,+5.210892887477986969e-83
}; } /**< ~1.202056903 */
template<> inline constexpr Float64x6 const_gompertz      <Float64x6>() { return {
	5.963473623231940746e-01,-2.215149147878839757e-19,-1.078400903200283423e-38,-4.530953279294682502e-55,+1.699969254783850492e-71,-9.193580115927408100e-88
}; } /**< ~0.596347362 */
template<> inline constexpr Float64x6 const_lemniscate    <Float64x6>() { return {
	2.622057554292119619e+00,+1.916430959469797945e-16,+9.968917493117175421e-33,+6.099667701471762700e-49,-2.983422300127819649e-66,-3.896174631900110233e-83
}; } /**< ~2.622057554 */
template<> inline constexpr Float64x6 const_2lemniscate   <Float64x6>() { return {
	5.244115108584239238e+00,+3.832861918939595890e-16,+1.993783498623435084e-32,+1.219933540294352540e-48,-5.966844600255639298e-66,-7.792349263800220467e-83
}; } /**< ~5.244115109 */
template<> inline constexpr Float64x6 const_lemniscate2   <Float64x6>() { return {
	1.311028777146059809e+00,+9.582154797348989724e-17,+4.984458746558587710e-33,+3.049833850735881350e-49,-1.491711150063909825e-66,-1.948087315950055117e-83
}; } /**< ~1.311028777 */
template<> inline constexpr Float64x6 const_gauss         <Float64x6>() { return {
	8.346268416740731944e-01,-8.073402861600294328e-18,+6.866557998616691539e-34,+3.347937083364879531e-50,-2.032227941313981209e-66,-1.273398388298843840e-82
}; } /**< ~0.834626842 */

}

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
