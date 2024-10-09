/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#include <stdint.h>
#include <limits>
#include <type_traits>
#include <stdint.h>

#include <cstdio>
#include "../../Float64x2/Float64x2.hpp"
#include "../../Float80x2/Float80x2.hpp"

typedef float fp32;

//------------------------------------------------------------------------------
// FP32x2 struct
//------------------------------------------------------------------------------

typedef struct FP32x2 {
	fp32 hi;
	fp32 lo;

/* Constructors */
	FP32x2() = default;

	constexpr inline FP32x2(const fp32 value_hi, const fp32 value_lo) :
		hi(value_hi), lo(value_lo) {}

	// inline FP32x2(const fp32 value_hi, const fp32 value_lo) {
	// 	hi = value_hi;
	// 	lo = value_lo;
	// }

	constexpr inline FP32x2(const fp32 (&values)[2]) :
		hi(values[0]), lo(values[1]) {}

	constexpr inline FP32x2(const fp32 value) :
		hi(value), lo(0.0f) {}

	
	// inline FP32x2(const fp32 value) {
	// 	hi = value;
	// }
/* Casts */

	constexpr inline operator fp32() const {
		return this->hi;
	}

} FP32x2;

typedef struct FP32x4 {
	fp32 val[4];
	FP32x4() = default;

/* Common Constructors */

	constexpr inline FP32x4(const fp32 value) :
		val{value, 0.0f, 0.0f, 0.0f} {}

	constexpr inline FP32x4(
		const fp32 val_0, const fp32 val_1, const fp32 val_2, const fp32 val_3
	) : val{val_0, val_1, val_2, val_3} {}

	constexpr inline FP32x4(const fp32 (&values)[4]) :
		val{values[0], values[1], values[2], values[3]} {}

/* constexpr Template Constructors (Primative Integers) */

// 	template <typename T, typename std::enable_if<
// 		(std::is_integral<T>::value) &&
// 		(std::numeric_limits<T>::digits <= std::numeric_limits<fp32>::digits)
// 	>::type* = nullptr> constexpr inline FP32x4(const T& value) :
// 		val{static_cast<fp32>(value), 0.0f, 0.0f, 0.0f} {}

// 	template <typename T, typename std::enable_if<
// 		(std::is_integral<T>::value) &&
// 		(std::numeric_limits<T>::digits <= std::numeric_limits<fp32>::digits * 2) &&
// 		(std::numeric_limits<T>::digits > std::numeric_limits<fp32>::digits)
// 	>::type* = nullptr> FP32x4(const T& value) :
// 		val{
// 			static_cast<fp32>(value),
// 			static_cast<fp32>(value - static_cast<T>(val[0])),
// 			0.0f,
// 			0.0f
// 		} {}

// 	template <typename T, typename std::enable_if<
// 		(std::is_integral<T>::value) &&
// 		(std::numeric_limits<T>::digits <= std::numeric_limits<fp32>::digits * 3) &&
// 		(std::numeric_limits<T>::digits > std::numeric_limits<fp32>::digits * 2)
// 	>::type* = nullptr> constexpr inline FP32x4(const T& value) :
// 		val{
// 			static_cast<fp32>(value),
// 			static_cast<fp32>(value - static_cast<T>(val[0])),
// 			static_cast<fp32>(value - static_cast<T>(val[0]) - static_cast<__float80>(val[1])),
// 			0.0f
// 		} {}

// 	template <typename T, typename std::enable_if<
// 		(std::is_integral<T>::value) &&
// 		(std::numeric_limits<T>::digits > std::numeric_limits<fp32>::digits * 3)
// 	>::type* = nullptr> constexpr inline FP32x4(const T& value) :
// 		val{
// 			static_cast<fp32>(value),
// 			static_cast<fp32>(value - static_cast<T>(val[0])),
// 			static_cast<fp32>(value - static_cast<T>(val[0]) - static_cast<T>(val[1])),
// 			static_cast<fp32>(value - static_cast<T>(val[0]) - static_cast<T>(val[1]) - static_cast<T>(val[2]))
// 		} {}

// /* Template Constructors */

// 	template <typename T, typename std::enable_if<
// 		!(std::is_integral<T>::value) &&
// 		(std::numeric_limits<T>::digits <= std::numeric_limits<fp32>::digits)
// 	>::type* = nullptr> inline FP32x4(const T& value) :
// 		val{static_cast<fp32>(value), 0.0f, 0.0f, 0.0f} {}

// 	template <typename T, typename std::enable_if<
// 		!(std::is_integral<T>::value) &&
// 		(std::numeric_limits<T>::digits <= std::numeric_limits<fp32>::digits * 2) &&
// 		(std::numeric_limits<T>::digits > std::numeric_limits<fp32>::digits)
// 	>::type* = nullptr> inline FP32x4(const T& value) :
// 		val{
// 			static_cast<fp32>(value),
// 			static_cast<fp32>(value - static_cast<T>(val[0])),
// 			0.0f,
// 			0.0f
// 		} {}

// 	template <typename T, typename std::enable_if<
// 		!(std::is_integral<T>::value) &&
// 		(std::numeric_limits<T>::digits <= std::numeric_limits<fp32>::digits * 3) &&
// 		(std::numeric_limits<T>::digits > std::numeric_limits<fp32>::digits * 2)
// 	>::type* = nullptr> inline FP32x4(const T& value) :
// 		val{
// 			static_cast<fp32>(value),
// 			static_cast<fp32>(value - static_cast<T>(val[0])),
// 			static_cast<fp32>(value - static_cast<T>(val[0]) - static_cast<__float80>(val[1])),
// 			0.0f
// 		} {}

// 	template <typename T, typename std::enable_if<
// 		!(std::is_integral<T>::value) &&
// 		(std::numeric_limits<T>::digits > std::numeric_limits<fp32>::digits * 3)
// 	>::type* = nullptr> inline FP32x4(const T& value) :
// 		val{
// 			static_cast<fp32>(value),
// 			static_cast<fp32>(value - static_cast<T>(val[0])),
// 			static_cast<fp32>(value - static_cast<T>(val[0]) - static_cast<T>(val[1])),
// 			static_cast<fp32>(value - static_cast<T>(val[0]) - static_cast<T>(val[1]) - static_cast<T>(val[2]))
// 		} {}

/* Common Casts */

	constexpr inline operator fp32() const {
		return this->val[0];
	}

	inline operator FP32x2() const {
		printf("L: %d\n", __LINE__);
		return FP32x2(this->val[0], this->val[1]);
	}

/* constexpr Template Casts (Primative Integers) */

	// template <typename T, typename std::enable_if<
	// 	!(std::is_integral<T>::value) &&
	// 	(std::numeric_limits<T>::digits <= std::numeric_limits<fp32>::digits)
	// >::type* = nullptr> constexpr inline operator T() const {
	// 	return this->val[0];
	// }

/* Template Casts */

} FP32x4;

void constructor_test(void) {
	float       f32 = 123.0f;
	// double      f64 = 123.0;
	// long double f80 = 123.0L;
	// __float128  f128 = static_cast<__float128>(123.0L);
	// uint8_t     u8 = 123;
	// int8_t      i8 = 123;
	// uint16_t    u16 = 123;
	// int16_t     i16 = 123;
	// uint32_t    u32 = 123;
	// int32_t     i32 = 123;
	// uint64_t    u64 = 123;
	// int64_t     i64 = 123;
	// __int128_t  u128 = 123;
	// __int128_t  i128 = 123;
	FP32x2   f32x2 = 123.0f;
	// Float64x2   f64x2 = 123.0;
	// Float80x2   f80x2 = 123.0L;

	/* Constructors */

	FP32x4 value;
	value = FP32x4(f32  );
	// value = FP32x4(f64  );
	// value = FP32x4(f80  );
	// value = FP32x4(f128 );
	// value = FP32x4(u8   );
	// value = FP32x4(i8   );
	// value = FP32x4(u16  );
	// value = FP32x4(i16  );
	// value = FP32x4(u32  );
	// value = FP32x4(i32  );
	// value = FP32x4(u64  );
	// value = FP32x4(i64  );
	// value = FP32x4(u128 );
	// value = FP32x4(i128 );
	value = FP32x4(f32x2);
	// value = FP32x4(f64x2);
	// value = FP32x4(f80x2);

	/* Casts */
	f32   = (float      )value;
	// f64   = (double     )value;
	// f80   = (long double)value;
	// f128  = (__float128 )value;
	// u8    = (uint8_t    )value;
	// i8    = (int8_t     )value;
	// u16   = (uint16_t   )value;
	// i16   = (int16_t    )value;
	// u32   = (uint32_t   )value;
	// i32   = (int32_t    )value;
	// u64   = (uint64_t   )value;
	// i64   = (int64_t    )value;
	// u128  = (__int128_t )value;
	// i128  = (__int128_t )value;
	printf("F\n");
	f32x2 = static_cast<FP32x2>(value);
	printf("F\n");
	// f64x2 = (Float64x2  )value;
	// f80x2 = (Float80x2  )value;
}
