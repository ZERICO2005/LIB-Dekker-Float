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
#include "Float64x2/Float64x2.hpp"

#include <cstdint>
#include <cmath>

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
	return (
		x.val[0] == y.hi && x.val[1] == y.lo &&
		x.val[2] == 0.0  && x.val[3] == 0.0 
	);
}
inline constexpr bool operator!=(const Float64x4& x, const Float64x2& y) {
	return (
		x.val[0] != y.hi || x.val[1] != y.lo ||
		x.val[2] != 0.0  || x.val[3] != 0.0 
	);
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
	return (
		x.hi == y.val[0] && x.lo == y.val[1] &&
		0.0  == y.val[2] && 0.0  == y.val[3]
	);
}
inline constexpr bool operator!=(const Float64x2& x, const Float64x4& y) {
	return (
		x.hi != y.val[0] || x.lo != y.val[1] ||
		0.0  != y.val[2] || 0.0  != y.val[3]
	);
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
	return (
		x.val[0] == y   && x.val[1] == 0.0 &&
		x.val[2] == 0.0 && x.val[3] == 0.0
	);
}
inline constexpr bool operator!=(const Float64x4& x, const fp64 y) {
	return (
		x.val[0] != y   || x.val[1] != 0.0 ||
		x.val[2] != 0.0 || x.val[3] != 0.0
	);
}
inline constexpr bool operator<(const Float64x4& x, const fp64 y) {
	return
		(x.val[0] == y  ) ? (
			(x.val[1] == 0.0) ? (
				(x.val[2] == 0.0) ? (
					x.val[3] < 0.0
				) : (x.val[2] < 0.0)
			) : (x.val[1] < 0.0)
		) : (x.val[0] < y  );
}
inline constexpr bool operator<=(const Float64x4& x, const fp64 y) {
	return
		(x.val[0] == y  ) ? (
			(x.val[1] == 0.0) ? (
				(x.val[2] == 0.0) ? (
					x.val[3] <= 0.0
				) : (x.val[2] < 0.0)
			) : (x.val[1] < 0.0)
		) : (x.val[0] < y  );
}
inline constexpr bool operator>(const Float64x4& x, const fp64 y) {
	return
		(x.val[0] == y  ) ? (
			(x.val[1] == 0.0) ? (
				(x.val[2] == 0.0) ? (
					x.val[3] > 0.0
				) : (x.val[2] > 0.0)
			) : (x.val[1] > 0.0)
		) : (x.val[0] > y  );
}
inline constexpr bool operator>=(const Float64x4& x, const fp64 y) {
	return
		(x.val[0] == y  ) ? (
			(x.val[1] == 0.0) ? (
				(x.val[2] == 0.0) ? (
					x.val[3] >= 0.0
				) : (x.val[2] > 0.0)
			) : (x.val[1] > 0.0)
		) : (x.val[0] > y  );
}



inline constexpr bool operator==(const fp64 x, const Float64x4& y) {
	return (
		x   == y.val[0] && 0.0 == y.val[1] &&
		0.0 == y.val[2] && 0.0 == y.val[3]
	);
}
inline constexpr bool operator!=(const fp64 x, const Float64x4& y) {
	return (
		x   != y.val[0] || 0.0 != y.val[1] ||
		0.0 != y.val[2] || 0.0 != y.val[3]
	);
}
inline constexpr bool operator<(const fp64 x, const Float64x4& y) {
	return
		(x   == y.val[0]) ? (
			(0.0 == y.val[1]) ? (
				(0.0 == y.val[2]) ? (
					0.0 < y.val[3]
				) : (0.0 < y.val[2])
			) : (0.0 < y.val[1])
		) : (x   < y.val[0]);
}
inline constexpr bool operator<=(const fp64 x, const Float64x4& y) {
	return
		(x   == y.val[0]) ? (
			(0.0 == y.val[1]) ? (
				(0.0 == y.val[2]) ? (
					0.0 <= y.val[3]
				) : (0.0 < y.val[2])
			) : (0.0 < y.val[1])
		) : (x   < y.val[0]);
}
inline constexpr bool operator>(const fp64 x, const Float64x4& y) {
	return
		(x   == y.val[0]) ? (
			(0.0 == y.val[1]) ? (
				(0.0 == y.val[2]) ? (
					0.0 > y.val[3]
				) : (0.0 > y.val[2])
			) : (0.0 > y.val[1])
		) : (x   > y.val[0]);
}
inline constexpr bool operator>=(const fp64 x, const Float64x4& y) {
	return
		(x   == y.val[0]) ? (
			(0.0 == y.val[1]) ? (
				(0.0 == y.val[2]) ? (
					0.0 >= y.val[3]
				) : (0.0 > y.val[2])
			) : (0.0 > y.val[1])
		) : (x   > y.val[0]);
}

//------------------------------------------------------------------------------
// Float64x4 Compare to Zero
//------------------------------------------------------------------------------

/** @brief Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero */
inline constexpr bool dekker_equal_zero(const Float64x4& x) {
	return (x.val[0] == 0.0);
}
/** @brief Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero */
inline constexpr bool dekker_notequal_zero(const Float64x4& x) {
	return (x.val[0] != 0.0);
}
/** @brief Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero */
inline constexpr bool dekker_less_zero(const Float64x4& x) {
	return (x.val[0] < 0.0);
}
/** @brief Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero */
inline constexpr bool dekker_lessequal_zero(const Float64x4& x) {
	return (x.val[0] <= 0.0);
}
/** @brief Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero */
inline constexpr bool dekker_greater_zero(const Float64x4& x) {
	return (x.val[0] > 0.0);
}
/** @brief Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero */
inline constexpr bool dekker_greaterequal_zero(const Float64x4& x) {
	return (x.val[0] >= 0.0);
}

//------------------------------------------------------------------------------
// Float64x4 Basic Arithmetic
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
	x += 1.0;
	return x;
}

inline Float64x4& operator--(Float64x4& x) {
	x -= 1.0;
	return x;
}

inline Float64x4 operator++(Float64x4& x, int) {
	Float64x4 temp = x;
	x += 1.0;
	return temp;
}

inline Float64x4 operator--(Float64x4& x, int) {
	Float64x4 temp = x;
	x -= 1.0;
	return temp;
}


//------------------------------------------------------------------------------
// Float64x4 specialized arithmetic
//------------------------------------------------------------------------------

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero
 */
inline Float64x4 mul_pwr2(const Float64x4& x, const fp64 y) {
	Float64x4 ret;
	ret.val[0] = x.val[0] * y;
	ret.val[1] = x.val[1] * y;
	ret.val[2] = x.val[2] * y;
	ret.val[3] = x.val[3] * y;
	return ret;
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero
 */
inline Float64x4 mul_pwr2(const fp64 x, const Float64x4& y) {
	Float64x4 ret;
	ret.val[0] = x * y.val[0];
	ret.val[1] = x * y.val[1];
	ret.val[2] = x * y.val[2];
	ret.val[3] = x * y.val[3];
	return ret;
}

//------------------------------------------------------------------------------
// Float64x4 bitwise operators
//------------------------------------------------------------------------------

inline Float64x4 bitwise_not(const Float64x4& x) {
	Float64x4 ret = x;
	uint64_t* binary_part = reinterpret_cast<uint64_t*>(&ret);
	binary_part[0] = ~binary_part[0];
	binary_part[1] = ~binary_part[1];
	binary_part[2] = ~binary_part[2];
	binary_part[3] = ~binary_part[3];
	return x;
}

inline Float64x4 bitwise_and(const Float64x4& x, const Float64x4& y) {
	Float64x4 ret = x;
	uint64_t* ret_bin = reinterpret_cast<uint64_t*>(&ret);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	ret_bin[0] &= y_bin[0];
	ret_bin[1] &= y_bin[1];
	ret_bin[2] &= y_bin[2];
	ret_bin[3] &= y_bin[3];
	return x;
}

inline Float64x4 bitwise_andnot(const Float64x4& x, const Float64x4& y) {
	Float64x4 ret = x;
	uint64_t* ret_bin = reinterpret_cast<uint64_t*>(&ret);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	ret_bin[0] &= ~y_bin[0];
	ret_bin[1] &= ~y_bin[1];
	ret_bin[2] &= ~y_bin[2];
	ret_bin[3] &= ~y_bin[3];
	return x;
}

inline Float64x4 bitwise_or(const Float64x4& x, const Float64x4& y) {
	Float64x4 ret = x;
	uint64_t* ret_bin = reinterpret_cast<uint64_t*>(&ret);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	ret_bin[0] |= y_bin[0];
	ret_bin[1] |= y_bin[1];
	ret_bin[2] |= y_bin[2];
	ret_bin[3] |= y_bin[3];
	return x;
}

inline Float64x4 bitwise_xor(const Float64x4& x, const Float64x4& y) {
	Float64x4 ret = x;
	uint64_t* ret_bin = reinterpret_cast<uint64_t*>(&ret);
	const uint64_t* y_bin = reinterpret_cast<const uint64_t*>(&y);
	ret_bin[0] ^= y_bin[0];
	ret_bin[1] ^= y_bin[1];
	ret_bin[2] ^= y_bin[2];
	ret_bin[3] ^= y_bin[3];
	return x;
}

//------------------------------------------------------------------------------
// Float64x4 Constants
//------------------------------------------------------------------------------

/* C++20 <numbers> */

	constexpr Float64x4 Float64x4_e          = {0x1.5bf0a8b145769p+1,+0x1.4d57ee2b1013ap-53,-0x1.618713a31d3e2p-109,+0x1.c5a6d2b53c26dp-163}; /**< ~2.718281828 */
	constexpr Float64x4 Float64x4_log2e      = {0x1.71547652b82fep+0,+0x1.777d0ffda0d24p-56,-0x1.60bb8a5442ab9p-110,-0x1.4b52d3ba6d74dp-166}; /**< ~1.442695041 */
	constexpr Float64x4 Float64x4_log10e     = {0x1.bcb7b1526e50ep-2,+0x1.95355baaafad3p-57,+0x1.ee191f71a3012p-112,+0x1.7268808e8fcb5p-167}; /**< ~0.434294482 */
	constexpr Float64x4 Float64x4_pi         = {0x1.921fb54442d18p+1,+0x1.1a62633145c07p-53,-0x1.f1976b7ed8fbcp-109,+0x1.4cf98e804177dp-163}; /**< ~3.141592654 */
	constexpr Float64x4 Float64x4_inv_pi     = {0x1.45f306dc9c883p-2,-0x1.6b01ec5417056p-56,-0x1.6447e493ad4cep-110,+0x1.e21c820ff28b2p-164}; /**< ~0.318309886 */
	constexpr Float64x4 Float64x4_inv_sqrtpi = {0x1.20dd750429b6dp-1,+0x1.1ae3a914fed80p-57,-0x1.3cbbebf65f145p-112,-0x1.e0c574632f53ep-167}; /**< ~0.564189584 */
	constexpr Float64x4 Float64x4_ln2        = {0x1.62e42fefa39efp-1,+0x1.abc9e3b39803fp-56,+0x1.7b57a079a1934p-111,-0x1.ace93a4ebe5d1p-165}; /**< ~0.693147181 */
	constexpr Float64x4 Float64x4_ln10       = {0x1.26bb1bbb55516p+1,-0x1.f48ad494ea3e9p-53,-0x1.9ebae3ae0260cp-107,-0x1.2d10378be1cf1p-161}; /**< ~2.302585093 */
	constexpr Float64x4 Float64x4_sqrt2      = {0x1.6a09e667f3bcdp+0,-0x1.bdd3413b26456p-54,+0x1.57d3e3adec175p-108,+0x1.2775099da2f59p-164}; /**< ~1.414213562 */
	constexpr Float64x4 Float64x4_sqrt3      = {0x1.bb67ae8584caap+0,+0x1.cec95d0b5c1e3p-54,-0x1.f11db689f2ccfp-110,+0x1.3da4798c720a6p-164}; /**< ~1.732050808 */
	constexpr Float64x4 Float64x4_inv_sqrt3  = {0x1.279a74590331cp-1,+0x1.34863e0792bedp-55,-0x1.a82f9e6c53222p-109,-0x1.cb0f41134253ap-163}; /**< ~0.577350269 */
	constexpr Float64x4 Float64x4_egamma     = {0x1.2788cfc6fb619p-1,-0x1.6cb90701fbfabp-58,-0x1.34a95e3133c51p-112,+0x1.9730064300f7dp-166}; /**< ~0.577215665 */
	constexpr Float64x4 Float64x4_phi        = {0x1.9e3779b97f4a8p+0,-0x1.f506319fcfd19p-55,+0x1.b906821044ed8p-109,-0x1.8bb1b5c0f272cp-165}; /**< ~1.618033989 */

#if __cplusplus >= 201907L
#include <numbers>
namespace std {
	namespace numbers {
		template<> inline constexpr Float64x4 e_v          <Float64x4> = Float64x4_e         ; /**< ~2.718281828 */
		template<> inline constexpr Float64x4 log2e_v      <Float64x4> = Float64x4_log2e     ; /**< ~1.442695041 */
		template<> inline constexpr Float64x4 log10e_v     <Float64x4> = Float64x4_log10e    ; /**< ~0.434294482 */
		template<> inline constexpr Float64x4 pi_v         <Float64x4> = Float64x4_pi        ; /**< ~3.141592654 */
		template<> inline constexpr Float64x4 inv_pi_v     <Float64x4> = Float64x4_inv_pi    ; /**< ~0.318309886 */
		template<> inline constexpr Float64x4 inv_sqrtpi_v <Float64x4> = Float64x4_inv_sqrtpi; /**< ~0.564189584 */
		template<> inline constexpr Float64x4 ln2_v        <Float64x4> = Float64x4_ln2       ; /**< ~0.693147181 */
		template<> inline constexpr Float64x4 ln10_v       <Float64x4> = Float64x4_ln10      ; /**< ~2.302585093 */
		template<> inline constexpr Float64x4 sqrt2_v      <Float64x4> = Float64x4_sqrt2     ; /**< ~1.414213562 */
		template<> inline constexpr Float64x4 sqrt3_v      <Float64x4> = Float64x4_sqrt3     ; /**< ~1.732050808 */
		template<> inline constexpr Float64x4 inv_sqrt3_v  <Float64x4> = Float64x4_inv_sqrt3 ; /**< ~0.577350269 */
		template<> inline constexpr Float64x4 egamma_v     <Float64x4> = Float64x4_egamma    ; /**< ~0.577215665 */
		template<> inline constexpr Float64x4 phi_v        <Float64x4> = Float64x4_phi       ; /**< ~1.618033989 */
	}
}
#endif

constexpr Float64x4 Float64x4_2pi  = {0x1.921fb54442d18p+2,+0x1.1a62633145c07p-52,-0x1.f1976b7ed8fbcp-108,+0x1.4cf98e804177dp-162}; /**< ~6.283185307 */
constexpr Float64x4 Float64x4_pi2  = {0x1.921fb54442d18p+0,+0x1.1a62633145c07p-54,-0x1.f1976b7ed8fbcp-110,+0x1.4cf98e804177dp-164}; /**< ~1.570796327 */
constexpr Float64x4 Float64x4_pi4  = {0x1.921fb54442d18p-1,+0x1.1a62633145c07p-55,-0x1.f1976b7ed8fbcp-111,+0x1.4cf98e804177dp-165}; /**< ~0.785398163 */
constexpr Float64x4 Float64x4_3pi4 = {0x1.2d97c7f3321d2p+1,+0x1.a79394c9e8a0ap-54,+0x1.456737b06ea1ap-108,-0x1.83226a8fe7731p-162}; /**< ~2.356194490 */
constexpr Float64x4 Float64x4_tau  = Float64x4_2pi; /**< ~6.283185307 */

//------------------------------------------------------------------------------
// Float64x4 math.h functions
//------------------------------------------------------------------------------

/* Arithmetic */

	inline constexpr Float64x4 fmax(const Float64x4& x, const Float64x4& y) {
		return (x > y) ? x : y;
	}
	inline constexpr Float64x4 fmax(const Float64x4& x, const Float64x4& y, const Float64x4& z) {
		return (x > y) ?
		((x > z) ? x : z) :
		((y > z) ? y : z);
	}
	inline constexpr Float64x4 fmin(const Float64x4& x, const Float64x4& y) {
		return (x < y) ? x : y;
	}
	inline constexpr Float64x4 fmin(const Float64x4& x, const Float64x4& y, const Float64x4& z) {
		return (x < y) ?
		((x < z) ? x : z) :
		((y < z) ? y : z);
	}
	inline constexpr Float64x4 fabs(const Float64x4& x) {
		return (dekker_less_zero(x)) ? -x : x;
	}
	inline constexpr Float64x4 fdim(const Float64x4& x, const Float64x4& y) {
		return (x > y) ? (x - y) : static_cast<Float64x4>(0.0);
	}
	/** @note Naive implementation of fma (Fused multiply add). May lose precision */
	inline Float64x4 fma(const Float64x4& x, const Float64x4& y, const Float64x4& z) {
		return (x * y) + z;
	}
	inline constexpr Float64x4 copysign(const Float64x4& x, const Float64x4& y) {
		return (dekker_less_zero(x)) != (dekker_less_zero(y)) ? -x : x;
	}
	inline Float64x4 sqrt(const Float64x4& x) {
		return Float64x4_sqrt(x);
	}
	inline Float64x4 cbrt(const Float64x4& x) {
		return Float64x4_cbrt(x);
	}
	/** @note Naive implementation of hypot, may overflow for large inputs */
	inline Float64x2 hypot(const Float64x4& x, const Float64x4& y) {
		return sqrt(
			square(x) + square(y)
		);
	}
	/** @note Naive implementation of hypot, may overflow for large inputs */
	inline Float64x2 hypot(const Float64x4& x, const Float64x4& y, const Float64x4& z) {
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
		return log(x) * Float64x4_log2e;
	}
	inline Float64x4 log10(const Float64x4& x) {
		return log(x) * Float64x4_log10e;
	}
	inline Float64x4 logb(const Float64x4& x) { return logb(x.val[0]); }

	Float64x4 exp(const Float64x4& x);
	Float64x4 expm1(const Float64x4& x);
	inline Float64x4 exp2(const Float64x4& x) {
		return exp(x * Float64x4_ln2);
	}
	inline Float64x4 exp10(const Float64x4& x) {
		return exp(x * Float64x4_ln10);
	}

	inline Float64x4 pow(const Float64x4& x, const Float64x4& y) {
		return exp(y * log(x));
	}
	inline Float64x4 pow(const Float64x4& x, const Float64x2& y) {
		return exp(y * log(x));
	}
	inline Float64x4 pow(const Float64x4& x, const fp64 y) {
		return exp(y * log(x));
	}

/* Tests */

	inline constexpr bool signbit(const Float64x4& x) {
		return dekker_less_zero(x) ? true : false;
	}
	/** Returns true if both x.hi and x.lo are finite */
	inline constexpr bool isfinite(const Float64x4& x) {
		return (
			isfinite(x.val[0]) && isfinite(x.val[1]) &&
			isfinite(x.val[2]) && isfinite(x.val[3])
		);
	}
	/** Returns true if either x.hi or x.lo are infinite */
	inline constexpr bool isinf(const Float64x4& x) {
		return (
			isinf(x.val[0]) || isinf(x.val[1]) ||
			isinf(x.val[2]) || isinf(x.val[3])
		);
	}
	/** Returns true if either x.hi or x.lo are nan */
	inline constexpr bool isnan(const Float64x4& x) {
		return (
			isnan(x.val[0]) || isnan(x.val[1]) ||
			isnan(x.val[2]) || isnan(x.val[3])
		);
	}
	/** Returns true if both x.hi and x.lo are normal */
	inline constexpr bool isnormal(const Float64x4& x) {
		return (
			isnormal(x.val[0]) && isnormal(x.val[1]) &&
			isnormal(x.val[2]) && isnormal(x.val[3])
		);
	}
	/** Returns true if either {x.hi, y.hi} or {x.lo, y.lo} are unordered */
	inline constexpr bool isunordered(const Float64x4& x, const Float64x4& y) {
		return (
			isunordered(x.val[0], y.val[0]) || isunordered(x.val[1], y.val[1]) ||
			isunordered(x.val[2], y.val[2]) || isunordered(x.val[3], y.val[3])
		);
	}
	inline constexpr int fpclassify(const Float64x4& x) {
		return
			isinf(x)             ? FP_INFINITE :
			isnan(x)             ? FP_NAN      :
			dekker_equal_zero(x) ? FP_ZERO     :
			isnormal(x)          ? FP_NORMAL   :
			FP_SUBNORMAL;
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
	inline Float64x4 modf(const Float64x4& x, Float64x4* int_part) {
		Float64x4 trunc_part = trunc(x);
		if (int_part != nullptr) {
			*int_part = trunc_part;
		}
		return x - trunc_part;
	}
	inline Float64x4 nearbyint(const Float64x4& x) {
		return rint(x);
	}
	inline Float64x4 remainder(const Float64x4& x, const Float64x4& y) {
		Float64x4 round_part = round(x / y);
		return x - y * round_part;
	}
	inline Float64x4 remquo(const Float64x4& x, const Float64x4& y, int* quo) {
		Float64x4 q = round(x / y);
		Float64x4 r = x - y * q;
		*quo = static_cast<int>(q.val[0] + q.val[1]);
		return r;
	}

/* Float Exponents */

	/** @brief ilogb(x.val[0]) */
	inline int ilogb(const Float64x4& x) {
		return ilogb(x.val[0]);
	}
	/** @brief frexp(x.val[0], exp) */
	inline Float64x4 frexp(const Float64x4& x, int* exp) {
		return frexp(x.val[0], exp);
	}
	inline Float64x4 ldexp(const Float64x4& x, int exp) {
		Float64x4 ret = x;
		ret.val[0] = ldexp(x.val[0], exp);
		if (isfinite(ret.val[0])) {
			ret.val[1] = ldexp(x.val[1], exp);
			ret.val[2] = ldexp(x.val[2], exp);
			ret.val[3] = ldexp(x.val[3], exp);
			return ret;
		}
		ret.val[1] = x.val[0];
		ret.val[2] = x.val[0];
		ret.val[3] = x.val[0];
		return ret;
	}
	inline Float64x4 scalbn(const Float64x4& x, int exp) {
		Float64x4 ret = x;
		ret.val[0] = scalbn(x.val[0], exp);
		if (isfinite(x.val[0])) {
			ret.val[1] = scalbn(x.val[1], exp);
			ret.val[2] = scalbn(x.val[2], exp);
			ret.val[3] = scalbn(x.val[3], exp);
			return ret;
		}
		ret.val[1] = x.val[0];
		ret.val[2] = x.val[0];
		ret.val[3] = x.val[0];
		return ret;
	}
	inline Float64x4 scalbln(const Float64x4& x, long exp) {
		Float64x4 ret = x;
		ret.val[0] = scalbln(x.val[0], exp);
		if (isfinite(x.val[0])) {
			ret.val[1] = scalbln(x.val[1], exp);
			ret.val[2] = scalbln(x.val[2], exp);
			ret.val[3] = scalbln(x.val[3], exp);
			return ret;
		}
		ret.val[1] = x.val[0];
		ret.val[2] = x.val[0];
		ret.val[3] = x.val[0];
		return ret;
	}

/* Transcendental Functions */
	
	/** 
	 * @note casts to long double for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float64x4 erf(const Float64x4& x) {
		return static_cast<Float64x4>(
			erf(static_cast<long double>(x))
		);
	}
	/** 
	 * @note casts to long double for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float64x4 erfc(const Float64x4& x) {
		return static_cast<Float64x4>(
			erfc(static_cast<long double>(x))
		);
	}
	/** 
	 * @note casts to long double for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float64x4 lgamma(const Float64x4& x) {
		return static_cast<Float64x4>(
			lgamma(static_cast<long double>(x))
		);
	}
	/** 
	 * @note casts to long double for calculation as this function is not
	 * currently implemeneted.
	 */
	inline Float64x4 tgamma(const Float64x4& x) {
		return static_cast<Float64x4>(
			tgamma(static_cast<long double>(x))
		);
	}


#endif /* FLOAT64X4_HPP */
