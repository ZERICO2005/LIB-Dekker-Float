/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef FLOAT64_AVX_HPP
#define FLOAT64_AVX_HPP

#include <smmintrin.h>
#if (!defined(__AVX__) && defined(__GNUC__))
	#error "__AVX__ is not enabled in your compiler. Try -mavx"
#endif

#include <stdint.h>
#include <immintrin.h>
#include <limits>

#include "Float64_AVX.h"

struct Float64_AVX {
	__m256d val;
	Float64_AVX() = default;
	
	Float64_AVX(__m256d x) :
		val(x) {}

	Float64_AVX(double x) :
		val(_mm256_set1_pd(x)) {}
	
	Float64_AVX(__m256i x) :
		val(_mm256_castsi256_pd(x)) {}
	
	Float64_AVX(uint64_t x) :
		val(_mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)x))) {}
	
	Float64_AVX(int64_t x) :
		val(_mm256_castsi256_pd(_mm256_set1_epi64x(x))) {}

	operator __m256d() const {
		return val;
	}
};

//------------------------------------------------------------------------------
// Float64_AVX Specialized Constructors
//------------------------------------------------------------------------------

/* Numeric */

static inline Float64_AVX Float64_AVX_Restrict_Numeric(Float64_AVX x) {
	return Float64_AVX(x);
}

static inline Float64_AVX Float64_AVX_Restrict_Numeric(__m256d x) {
	return Float64_AVX(x);
}

static inline Float64_AVX Float64_AVX_Restrict_Numeric(double x) {
	return Float64_AVX(x);
}

/* Bitwise */

static inline Float64_AVX Float64_AVX_Restrict_Bitwise(Float64_AVX x) {
	return Float64_AVX(x);
}

static inline Float64_AVX Float64_AVX_Restrict_Bitwise(__m256d x) {
	return Float64_AVX(x);
}

static inline Float64_AVX Float64_AVX_Restrict_Bitwise(__m256i x) {
	return Float64_AVX(x);
}

static inline Float64_AVX Float64_AVX_Restrict_Bitwise(uint64_t x) {
	return Float64_AVX(x);
}

static inline Float64_AVX Float64_AVX_Restrict_Bitwise(int64_t x) {
	return Float64_AVX(x);
}


//------------------------------------------------------------------------------
// Float64_AVX std::numeric_limits
//------------------------------------------------------------------------------

namespace std {
	template <>
	class numeric_limits<Float64_AVX> {
	public:
		static constexpr bool is_signed = std::numeric_limits<double>::is_signed;
		static constexpr bool is_integer = std::numeric_limits<double>::is_integer;
		static constexpr bool is_exact = std::numeric_limits<double>::is_exact;
		static constexpr bool has_infinity = std::numeric_limits<double>::has_infinity;
		static constexpr bool has_quiet_NaN = std::numeric_limits<double>::has_quiet_NaN;
		static constexpr bool has_signaling_NaN = std::numeric_limits<double>::has_signaling_NaN;
		static constexpr std::float_denorm_style has_denorm = std::numeric_limits<double>::has_denorm;
		static constexpr bool is_bounded = std::numeric_limits<double>::is_bounded;
		static constexpr int digits = std::numeric_limits<double>::digits;
		#if __cplusplus >= 201103L
		static constexpr int digits10 = std::numeric_limits<double>::digits10;
		#endif
		static constexpr int max_digits10 = std::numeric_limits<double>::max_digits10;
		static constexpr int radix = std::numeric_limits<double>::radix;
		static constexpr int min_exponent   = std::numeric_limits<double>::min_exponent;
		static constexpr int min_exponent10 = std::numeric_limits<double>::min_exponent10;
		static constexpr int max_exponent   = std::numeric_limits<double>::max_exponent;
		static constexpr int max_exponent10 = std::numeric_limits<double>::max_exponent10;
		static constexpr bool traps = std::numeric_limits<double>::traps;
		
		inline static Float64_AVX min() {
			return Float64_AVX(_mm256_set1_pd(std::numeric_limits<double>::min()));
		}
		inline static Float64_AVX max() {
			return Float64_AVX(_mm256_set1_pd(std::numeric_limits<double>::max()));
		}
		#if __cplusplus >= 201103L
		inline static Float64_AVX lowest() {
			return Float64_AVX(_mm256_set1_pd(std::numeric_limits<double>::lowest()));
		}
		#endif
		inline static Float64_AVX epsilon() {
			return Float64_AVX(_mm256_set1_pd(std::numeric_limits<double>::epsilon()));
		}
		inline static Float64_AVX round_error() {
			return Float64_AVX(_mm256_set1_pd(std::numeric_limits<double>::round_error()));
		}
		inline static Float64_AVX infinity() {
			return Float64_AVX(_mm256_set1_pd(std::numeric_limits<double>::infinity()));
		}
		inline static Float64_AVX quiet_NaN() {
			return Float64_AVX(_mm256_set1_pd(std::numeric_limits<double>::quiet_NaN()));
		}
		inline static Float64_AVX signaling_NaN() {
			return Float64_AVX(_mm256_set1_pd(std::numeric_limits<double>::signaling_NaN()));
		}
		inline static Float64_AVX denorm_min() {
			return Float64_AVX(_mm256_set1_pd(std::numeric_limits<double>::denorm_min()));
		}
	};
}

//------------------------------------------------------------------------------
// Float64_AVX C++20 numbers
//------------------------------------------------------------------------------

#if __cplusplus >= 201907L
#include <numbers>
namespace std {
	namespace numbers {
		template<> inline Float64_AVX e_v          <Float64_AVX> = _mm256_const_e_pd         (); /**< ~2.718281828 */
		template<> inline Float64_AVX log2e_v      <Float64_AVX> = _mm256_const_log2e_pd     (); /**< ~1.442695041 */
		template<> inline Float64_AVX log10e_v     <Float64_AVX> = _mm256_const_log10e_pd    (); /**< ~0.434294482 */
		template<> inline Float64_AVX pi_v         <Float64_AVX> = _mm256_const_pi_pd        (); /**< ~3.141592654 */
		template<> inline Float64_AVX inv_pi_v     <Float64_AVX> = _mm256_const_inv_pi_pd    (); /**< ~0.318309886 */
		template<> inline Float64_AVX inv_sqrtpi_v <Float64_AVX> = _mm256_const_inv_sqrtpi_pd(); /**< ~0.564189584 */
		template<> inline Float64_AVX ln2_v        <Float64_AVX> = _mm256_const_ln2_pd       (); /**< ~0.693147181 */
		template<> inline Float64_AVX ln10_v       <Float64_AVX> = _mm256_const_ln10_pd      (); /**< ~2.302585093 */
		template<> inline Float64_AVX sqrt2_v      <Float64_AVX> = _mm256_const_sqrt2_pd     (); /**< ~1.414213562 */
		template<> inline Float64_AVX sqrt3_v      <Float64_AVX> = _mm256_const_sqrt3_pd     (); /**< ~1.732050808 */
		template<> inline Float64_AVX inv_sqrt3_v  <Float64_AVX> = _mm256_const_inv_sqrt3_pd (); /**< ~0.577350269 */
		template<> inline Float64_AVX egamma_v     <Float64_AVX> = _mm256_const_egamma_pd    (); /**< ~0.577215665 */
		template<> inline Float64_AVX phi_v        <Float64_AVX> = _mm256_const_phi_pd       (); /**< ~1.618033989 */
	}
}
#endif

//------------------------------------------------------------------------------
// Float64_AVX Sign manipulation
//------------------------------------------------------------------------------

static inline Float64_AVX operator-(Float64_AVX x) {
	// return Float64_AVX(_mm256_xor_pd(
	// 	x.val,
	// 	_mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x8000000000000000))
	// ));
	return Float64_AVX(_mm256_mul_pd(x.val, _mm256_set1_pd(-1.0)));
}

/**
 * @brief `|x|` Returns the absolute value of a __m256d value
 * @remarks _mm256_andnot_pd cannot be used because 0x8000000000000000 gets
 * converted from -0.0 to 0.0 on -Ofast
 */
static inline Float64_AVX fabs(Float64_AVX x) {
	return Float64_AVX(_mm256_and_pd(
		x.val,
		_mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x7FFFFFFFFFFFFFFF))
	));
}

static inline Float64_AVX copysign(Float64_AVX x, Float64_AVX y) {
	return Float64_AVX(_mm256_copysign_pd(x.val, y.val));
}

//------------------------------------------------------------------------------
// Float64_AVX Bitwise
//------------------------------------------------------------------------------

/** `~x` Bitwise NOT */
static inline Float64_AVX operator~(Float64_AVX x) {
	return Float64_AVX(_mm256_xor_pd(
		x.val,
		_mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0xFFFFFFFFFFFFFFFF))
	));
}

/* Float64_AVX with Float64_AVX */

/** `x & y` Bitwise AND */
static inline Float64_AVX operator&(Float64_AVX x, Float64_AVX y) {
	return Float64_AVX(_mm256_and_pd(x.val, y.val));
}
/** `x & ~y` Bitwise ANDNOT */
static inline Float64_AVX operator%(Float64_AVX x, Float64_AVX y) {
	return Float64_AVX(_mm256_andnot_pd(x.val, y.val));
}
/** `x | y` Bitwise OR */
static inline Float64_AVX operator|(Float64_AVX x, Float64_AVX y) {
	return Float64_AVX(_mm256_or_pd(x.val, y.val));
}
/** `x ^ y` Bitwise XOR */
static inline Float64_AVX operator^(Float64_AVX x, Float64_AVX y) {
	return Float64_AVX(_mm256_xor_pd(x.val, y.val));
}

/* Float64_AVX with T */

/** `x & y` Bitwise AND */
template<typename T>
static inline Float64_AVX operator&(Float64_AVX x, T y) {
	return Float64_AVX(_mm256_and_pd(x.val, Float64_AVX_Restrict_Bitwise(y)));
}
/** `x & ~y` Bitwise ANDNOT */
template<typename T>
static inline Float64_AVX operator%(Float64_AVX x, T y) {
	return Float64_AVX(_mm256_andnot_pd(x.val, Float64_AVX_Restrict_Bitwise(y)));
}
/** `x | y` Bitwise OR */
template<typename T>
static inline Float64_AVX operator|(Float64_AVX x, T y) {
	return Float64_AVX(_mm256_or_pd(x.val, Float64_AVX_Restrict_Bitwise(y)));
}
/** `x ^ y` Bitwise XOR */
template<typename T>
static inline Float64_AVX operator^(Float64_AVX x, T y) {
	return Float64_AVX(_mm256_xor_pd(x.val, Float64_AVX_Restrict_Bitwise(y)));
}

/* T with Float64_AVX */

/** `x & y` Bitwise AND */
template<typename T>
static inline Float64_AVX operator&(T x, Float64_AVX y) {
	return Float64_AVX(_mm256_and_pd(Float64_AVX_Restrict_Bitwise(x), y.val));
}
/** `x & ~y` Bitwise ANDNOT */
template<typename T>
static inline Float64_AVX operator%(T x, Float64_AVX y) {
	return Float64_AVX(_mm256_andnot_pd(Float64_AVX_Restrict_Bitwise(x), y.val));
}
/** `x | y` Bitwise OR */
template<typename T>
static inline Float64_AVX operator|(T x, Float64_AVX y) {
	return Float64_AVX(_mm256_or_pd(Float64_AVX_Restrict_Bitwise(x), y.val));
}
/** `x ^ y` Bitwise XOR */
template<typename T>
static inline Float64_AVX operator^(T x, Float64_AVX y) {
	return Float64_AVX(_mm256_xor_pd(Float64_AVX_Restrict_Bitwise(x), y.val));
}

//------------------------------------------------------------------------------
// Float64_AVX Compound Bitwise
//------------------------------------------------------------------------------

/* Float64_AVX with Float64_AVX */

/** `x & y` Bitwise AND */
static inline Float64_AVX& operator&=(Float64_AVX& x, Float64_AVX y) {
	x.val = _mm256_and_pd(x.val, y.val);
	return x;
}
/** `x & ~y` Bitwise ANDNOT */
static inline Float64_AVX& operator%=(Float64_AVX& x, Float64_AVX y) {
	x.val = _mm256_andnot_pd(x.val, y.val);
	return x;
}
/** `x | y` Bitwise OR */
static inline Float64_AVX& operator|=(Float64_AVX& x, Float64_AVX y) {
	x.val = _mm256_or_pd(x.val, y.val);
	return x;
}
/** `x ^ y` Bitwise XOR */
static inline Float64_AVX& operator^=(Float64_AVX& x, Float64_AVX y) {
	x.val = _mm256_xor_pd(x.val, y.val);
	return x;
}

/* Float64_AVX with T */

/** `x & y` Bitwise AND */
template<typename T>
static inline Float64_AVX& operator&=(Float64_AVX& x, T y) {
	x.val = _mm256_and_pd(x.val, Float64_AVX_Restrict_Bitwise(y));
	return x;
}
/** `x & ~y` Bitwise ANDNOT */
template<typename T>
static inline Float64_AVX& operator%=(Float64_AVX& x, T y) {
	x.val = _mm256_andnot_pd(x.val, Float64_AVX_Restrict_Bitwise(y));
	return x;
}
/** `x | y` Bitwise OR */
template<typename T>
static inline Float64_AVX& operator|=(Float64_AVX& x, T y) {
	x.val = _mm256_or_pd(x.val, Float64_AVX_Restrict_Bitwise(y));
	return x;
}
/** `x ^ y` Bitwise XOR */
template<typename T>
static inline Float64_AVX& operator^=(Float64_AVX& x, T y) {
	x.val = _mm256_xor_pd(x.val, Float64_AVX_Restrict_Bitwise(y));
	return x;
}

//------------------------------------------------------------------------------
// Float64_AVX Logical
//------------------------------------------------------------------------------

/**
 * @brief Performs a boolean NOT. Equivalent to ~signbit(x), returning either
 * all ones or all zeros
 * @note Use ~x for a bitwise NOT
 */
static inline Float64_AVX operator!(Float64_AVX x) {
	return Float64_AVX(_mm256_blendv_pd(
		_mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0xFFFFFFFFFFFFFFFF)),
		_mm256_setzero_pd(),
		x.val
	));
}

/* Float64_AVX with Float64_AVX */

static inline Float64_AVX operator&&(Float64_AVX x, Float64_AVX y) {
	return Float64_AVX(_mm256_and_pd(x.val, y.val));
}
static inline Float64_AVX operator||(Float64_AVX x, Float64_AVX y) {
	return Float64_AVX(_mm256_or_pd(x.val, y.val));
}

/* Float64_AVX with __m256d */

static inline Float64_AVX operator&&(Float64_AVX x, __m256d y) {
	return Float64_AVX(_mm256_and_pd(x.val, y));
}
static inline Float64_AVX operator||(Float64_AVX x, __m256d y) {
	return Float64_AVX(_mm256_or_pd(x.val, y));
}

/* __m256d with Float64_AVX */

static inline Float64_AVX operator&&(__m256d x, Float64_AVX y) {
	return Float64_AVX(_mm256_and_pd(x, y.val));
}
static inline Float64_AVX operator||(__m256d x, Float64_AVX y) {
	return Float64_AVX(_mm256_or_pd(x, y.val));
}

/* Float64_AVX with boolean */

static inline Float64_AVX operator&&(Float64_AVX x, bool y) {
	__m256d b = y ?
		_mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0xFFFFFFFFFFFFFFFF)) :
		_mm256_setzero_pd();
	return Float64_AVX(_mm256_and_pd(x.val, b));
}
static inline Float64_AVX operator||(Float64_AVX x, bool y) {
	__m256d b = y ?
		_mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0xFFFFFFFFFFFFFFFF)) :
		_mm256_setzero_pd();
	return Float64_AVX(_mm256_or_pd(x.val, b));
}

/* boolean with Float64_AVX */

static inline Float64_AVX operator&&(bool x, Float64_AVX y) {
	__m256d b = x ?
		_mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0xFFFFFFFFFFFFFFFF)) :
		_mm256_setzero_pd();
	return Float64_AVX(_mm256_and_pd(b, y.val));
}
static inline Float64_AVX operator||(bool x, Float64_AVX y) {
	__m256d b = x ?
		_mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0xFFFFFFFFFFFFFFFF)) :
		_mm256_setzero_pd();
	return Float64_AVX(_mm256_or_pd(b, y.val));
}

//------------------------------------------------------------------------------
// Float64_AVX Arithmetic
//------------------------------------------------------------------------------

/* Float64_AVX with Float64_AVX */

static inline Float64_AVX operator+(Float64_AVX x, Float64_AVX y) {
	return Float64_AVX(_mm256_add_pd(x.val, y.val));
}

static inline Float64_AVX operator-(Float64_AVX x, Float64_AVX y) {
	return Float64_AVX(_mm256_sub_pd(x.val, y.val));
}

static inline Float64_AVX operator*(Float64_AVX x, Float64_AVX y) {
	return Float64_AVX(_mm256_mul_pd(x.val, y.val));
}

static inline Float64_AVX operator/(Float64_AVX x, Float64_AVX y) {
	return Float64_AVX(_mm256_div_pd(x.val, y.val));
}

/* Float64_AVX with T */

template<typename T>
static inline Float64_AVX operator+(Float64_AVX x, T y) {
	return Float64_AVX(_mm256_add_pd(x.val, Float64_AVX_Restrict_Numeric(y).val));
}

template<typename T>
static inline Float64_AVX operator-(Float64_AVX x, T y) {
	return Float64_AVX(_mm256_sub_pd(x.val, Float64_AVX_Restrict_Numeric(y).val));
}

template<typename T>
static inline Float64_AVX operator*(Float64_AVX x, T y) {
	return Float64_AVX(_mm256_mul_pd(x.val, Float64_AVX_Restrict_Numeric(y).val));
}

template<typename T>
static inline Float64_AVX operator/(Float64_AVX x, T y) {
	return Float64_AVX(_mm256_div_pd(x.val, Float64_AVX_Restrict_Numeric(y).val));
}

/* T with Float64_AVX */

template<typename T>
static inline Float64_AVX operator+(T x, Float64_AVX y) {
	return Float64_AVX(_mm256_add_pd(Float64_AVX_Restrict_Numeric(x), y.val));
}

template<typename T>
static inline Float64_AVX operator-(T x, Float64_AVX y) {
	return Float64_AVX(_mm256_sub_pd(Float64_AVX_Restrict_Numeric(x), y.val));
}

template<typename T>
static inline Float64_AVX operator*(T x, Float64_AVX y) {
	return Float64_AVX(_mm256_mul_pd(Float64_AVX_Restrict_Numeric(x), y.val));
}

template<typename T>
static inline Float64_AVX operator/(T x, Float64_AVX y) {
	return Float64_AVX(_mm256_div_pd(Float64_AVX_Restrict_Numeric(x), y.val));
}

//------------------------------------------------------------------------------
// Float64_AVX Compound Assignment
//------------------------------------------------------------------------------

/* Float64_AVX with Float64_AVX */

static inline Float64_AVX& operator+=(Float64_AVX& x, Float64_AVX y) {
	x.val = _mm256_add_pd(x.val, y.val);
	return x;
}
static inline Float64_AVX& operator-=(Float64_AVX& x, Float64_AVX y) {
	x.val = _mm256_sub_pd(x.val, y.val);
	return x;
}
static inline Float64_AVX& operator*=(Float64_AVX& x, Float64_AVX y) {
	x.val = _mm256_mul_pd(x.val, y.val);
	return x;
}
static inline Float64_AVX& operator/=(Float64_AVX& x, Float64_AVX y) {
	x.val = _mm256_div_pd(x.val, y.val);
	return x;
}

/* Float64_AVX with T */

template<typename T>
static inline Float64_AVX& operator+=(Float64_AVX& x, T y) {
	x.val = _mm256_add_pd(x.val, Float64_AVX_Restrict_Numeric(y));
	return x;
}
template<typename T>
static inline Float64_AVX& operator-=(Float64_AVX& x, T y) {
	x.val = _mm256_sub_pd(x.val, Float64_AVX_Restrict_Numeric(y));
	return x;
}
template<typename T>
static inline Float64_AVX& operator*=(Float64_AVX& x, T y) {
	x.val = _mm256_mul_pd(x.val, Float64_AVX_Restrict_Numeric(y));
	return x;
}
template<typename T>
static inline Float64_AVX& operator/=(Float64_AVX& x, T y) {
	x.val = _mm256_div_pd(x.val, Float64_AVX_Restrict_Numeric(y));
	return x;
}

//------------------------------------------------------------------------------
// Float64_AVX Increment and Decrement
//------------------------------------------------------------------------------

inline Float64_AVX& operator++(Float64_AVX& x) {
	x.val = _mm256_add_pd(x.val, _mm256_set1_pd(1.0));
	return x;
}

inline Float64_AVX& operator--(Float64_AVX& x) {
	x.val = _mm256_sub_pd(x.val, _mm256_set1_pd(1.0));
	return x;
}

inline Float64_AVX operator++(Float64_AVX& x, int) {
	Float64_AVX temp = x;
	x.val = _mm256_add_pd(x.val, _mm256_set1_pd(1.0));
	return temp;
}

inline Float64_AVX operator--(Float64_AVX& x, int) {
	Float64_AVX temp = x;
	x.val = _mm256_sub_pd(x.val, _mm256_set1_pd(1.0));
	return temp;
}

//------------------------------------------------------------------------------
// Float64_AVX Classify
//------------------------------------------------------------------------------

static inline Float64_AVX signbit(Float64_AVX x) {
	return Float64_AVX(_mm256_signbit_pd(x.val));
}

/** @brief Returns true if x is finite */
static inline Float64_AVX isfinite(Float64_AVX x) {
	return Float64_AVX(_mm256_isfinite_pd(x.val));
}

/** @brief Returns true if x is +-infinity */
static inline Float64_AVX isinf(Float64_AVX x) {
	return Float64_AVX(_mm256_isinf_pd(x.val));
}

/** @brief Returns true if x is any kind of NaN */
static inline Float64_AVX isnan(Float64_AVX x) {
	return Float64_AVX(_mm256_isnan_pd(x.val));
}

/** @brief Returns true if x is normal */
static inline Float64_AVX isnormal(Float64_AVX x) {
	return Float64_AVX(_mm256_isnormal_pd(x.val));
}

//------------------------------------------------------------------------------
// Float64_AVX Comparisons
//------------------------------------------------------------------------------

/* Float64_AVX compare Float64_AVX */

/** _CMP_EQ_OQ */
static inline Float64_AVX operator==(Float64_AVX x, Float64_AVX y) {
	return Float64_AVX(_mm256_cmp_pd(x.val, y.val, _CMP_EQ_OQ));
}
/** _CMP_NEQ_OQ */
static inline Float64_AVX operator!=(Float64_AVX x, Float64_AVX y) {
	return Float64_AVX(_mm256_cmp_pd(x.val, y.val, _CMP_NEQ_OQ));
}

/** _CMP_LT_OS */
static inline Float64_AVX operator<(Float64_AVX x, Float64_AVX y) {
	return Float64_AVX(_mm256_cmp_pd(x.val, y.val, _CMP_LT_OS));
}
/** _CMP_LE_OS */
static inline Float64_AVX operator<=(Float64_AVX x, Float64_AVX y) {
	return Float64_AVX(_mm256_cmp_pd(x.val, y.val, _CMP_LE_OS));
}
/** _CMP_GT_OS */
static inline Float64_AVX operator>(Float64_AVX x, Float64_AVX y) {
	return Float64_AVX(_mm256_cmp_pd(x.val, y.val, _CMP_GT_OS));
}
/** _CMP_GE_OS */
static inline Float64_AVX operator>=(Float64_AVX x, Float64_AVX y) {
	return Float64_AVX(_mm256_cmp_pd(x.val, y.val, _CMP_GE_OS));
}

/** _CMP_UNORD_Q */
static inline Float64_AVX isunordered(Float64_AVX x, Float64_AVX y) {
	return Float64_AVX(_mm256_cmp_pd(x.val, y.val, _CMP_UNORD_Q));
}
/** _CMP_NEQ_UQ */
static inline Float64_AVX islessgreater(Float64_AVX x, Float64_AVX y) {
	return Float64_AVX(_mm256_cmp_pd(x.val, y.val, _CMP_NEQ_UQ));
}

/** _CMP_LT_OQ */
static inline Float64_AVX isless(Float64_AVX x, Float64_AVX y) {
	return Float64_AVX(_mm256_cmp_pd(x.val, y.val, _CMP_LT_OQ));
}
/** _CMP_LE_OQ */
static inline Float64_AVX islessequal(Float64_AVX x, Float64_AVX y) {
	return Float64_AVX(_mm256_cmp_pd(x.val, y.val, _CMP_LE_OQ));
}
/** _CMP_GT_OQ */
static inline Float64_AVX isgreater(Float64_AVX x, Float64_AVX y) {
	return Float64_AVX(_mm256_cmp_pd(x.val, y.val, _CMP_GT_OQ));
}
/** _CMP_GE_OQ */
static inline Float64_AVX isgreaterequal(Float64_AVX x, Float64_AVX y) {
	return Float64_AVX(_mm256_cmp_pd(x.val, y.val, _CMP_GE_OQ));
}

/* Float64_AVX compare T */

/** _CMP_EQ_OQ */
template<typename T>
static inline Float64_AVX operator==(Float64_AVX x, T y) {
	return Float64_AVX(_mm256_cmp_pd(x.val, Float64_AVX_Restrict_Numeric(y).val, _CMP_EQ_OQ));
}
/** _CMP_NEQ_OQ */
template<typename T>
static inline Float64_AVX operator!=(Float64_AVX x, T y) {
	return Float64_AVX(_mm256_cmp_pd(x.val, Float64_AVX_Restrict_Numeric(y).val, _CMP_NEQ_OQ));
}

/** _CMP_LT_OS */
template<typename T>
static inline Float64_AVX operator<(Float64_AVX x, T y) {
	return Float64_AVX(_mm256_cmp_pd(x.val, Float64_AVX_Restrict_Numeric(y).val, _CMP_LT_OS));
}
/** _CMP_LE_OS */
template<typename T>
static inline Float64_AVX operator<=(Float64_AVX x, T y) {
	return Float64_AVX(_mm256_cmp_pd(x.val, Float64_AVX_Restrict_Numeric(y).val, _CMP_LE_OS));
}
/** _CMP_GT_OS */
template<typename T>
static inline Float64_AVX operator>(Float64_AVX x, T y) {
	return Float64_AVX(_mm256_cmp_pd(x.val, Float64_AVX_Restrict_Numeric(y).val, _CMP_GT_OS));
}
/** _CMP_GE_OS */
template<typename T>
static inline Float64_AVX operator>=(Float64_AVX x, T y) {
	return Float64_AVX(_mm256_cmp_pd(x.val, Float64_AVX_Restrict_Numeric(y).val, _CMP_GE_OS));
}

/** _CMP_UNORD_Q */
template<typename T>
static inline Float64_AVX isunordered(Float64_AVX x, T y) {
	return Float64_AVX(_mm256_cmp_pd(x.val, Float64_AVX_Restrict_Numeric(y).val, _CMP_UNORD_Q));
}
/** _CMP_NEQ_UQ */
template<typename T>
static inline Float64_AVX islessgreater(Float64_AVX x, T y) {
	return Float64_AVX(_mm256_cmp_pd(x.val, Float64_AVX_Restrict_Numeric(y).val, _CMP_NEQ_UQ));
}

/** _CMP_LT_OQ */
template<typename T>
static inline Float64_AVX isless(Float64_AVX x, T y) {
	return Float64_AVX(_mm256_cmp_pd(x.val, Float64_AVX_Restrict_Numeric(y).val, _CMP_LT_OQ));
}
/** _CMP_LE_OQ */
template<typename T>
static inline Float64_AVX islessequal(Float64_AVX x, T y) {
	return Float64_AVX(_mm256_cmp_pd(x.val, Float64_AVX_Restrict_Numeric(y).val, _CMP_LE_OQ));
}
/** _CMP_GT_OQ */
template<typename T>
static inline Float64_AVX isgreater(Float64_AVX x, T y) {
	return Float64_AVX(_mm256_cmp_pd(x.val, Float64_AVX_Restrict_Numeric(y).val, _CMP_GT_OQ));
}
/** _CMP_GE_OQ */
template<typename T>
static inline Float64_AVX isgreaterequal(Float64_AVX x, T y) {
	return Float64_AVX(_mm256_cmp_pd(x.val, Float64_AVX_Restrict_Numeric(y).val, _CMP_GE_OQ));
}

/* T compare Float64_AVX */

/** _CMP_EQ_OQ */
template<typename T>
static inline Float64_AVX operator==(T x, Float64_AVX y) {
	return Float64_AVX(_mm256_cmp_pd(Float64_AVX_Restrict_Numeric(x).val, y.val, _CMP_EQ_OQ));
}
/** _CMP_NEQ_OQ */
template<typename T>
static inline Float64_AVX operator!=(T x, Float64_AVX y) {
	return Float64_AVX(_mm256_cmp_pd(Float64_AVX_Restrict_Numeric(x).val, y.val, _CMP_NEQ_OQ));
}

/** _CMP_LT_OS */
template<typename T>
static inline Float64_AVX operator<(T x, Float64_AVX y) {
	return Float64_AVX(_mm256_cmp_pd(Float64_AVX_Restrict_Numeric(x).val, y.val, _CMP_LT_OS));
}
/** _CMP_LE_OS */
template<typename T>
static inline Float64_AVX operator<=(T x, Float64_AVX y) {
	return Float64_AVX(_mm256_cmp_pd(Float64_AVX_Restrict_Numeric(x).val, y.val, _CMP_LE_OS));
}
/** _CMP_GT_OS */
template<typename T>
static inline Float64_AVX operator>(T x, Float64_AVX y) {
	return Float64_AVX(_mm256_cmp_pd(Float64_AVX_Restrict_Numeric(x).val, y.val, _CMP_GT_OS));
}
/** _CMP_GE_OS */
template<typename T>
static inline Float64_AVX operator>=(T x, Float64_AVX y) {
	return Float64_AVX(_mm256_cmp_pd(Float64_AVX_Restrict_Numeric(x).val, y.val, _CMP_GE_OS));
}

/** _CMP_UNORD_Q */
template<typename T>
static inline Float64_AVX isunordered(T x, Float64_AVX y) {
	return Float64_AVX(_mm256_cmp_pd(Float64_AVX_Restrict_Numeric(x).val, y.val, _CMP_UNORD_Q));
}
/** _CMP_NEQ_UQ */
template<typename T>
static inline Float64_AVX islessgreater(T x, Float64_AVX y) {
	return Float64_AVX(_mm256_cmp_pd(Float64_AVX_Restrict_Numeric(x).val, y.val, _CMP_NEQ_UQ));
}

/** _CMP_LT_OQ */
template<typename T>
static inline Float64_AVX isless(T x, Float64_AVX y) {
	return Float64_AVX(_mm256_cmp_pd(Float64_AVX_Restrict_Numeric(x).val, y.val, _CMP_LT_OQ));
}
/** _CMP_LE_OQ */
template<typename T>
static inline Float64_AVX islessequal(T x, Float64_AVX y) {
	return Float64_AVX(_mm256_cmp_pd(Float64_AVX_Restrict_Numeric(x).val, y.val, _CMP_LE_OQ));
}
/** _CMP_GT_OQ */
template<typename T>
static inline Float64_AVX isgreater(T x, Float64_AVX y) {
	return Float64_AVX(_mm256_cmp_pd(Float64_AVX_Restrict_Numeric(x).val, y.val, _CMP_GT_OQ));
}
/** _CMP_GE_OQ */
template<typename T>
static inline Float64_AVX isgreaterequal(T x, Float64_AVX y) {
	return Float64_AVX(_mm256_cmp_pd(Float64_AVX_Restrict_Numeric(x).val, y.val, _CMP_GE_OQ));
}

//------------------------------------------------------------------------------
// Float64_AVX fmax, fmin, and fdim
//------------------------------------------------------------------------------

/* Float64_AVX and Float64_AVX */

/**
 * @brief Returns the fmax of x and y. Correctly handling NaN and signed zeros.
 * You may use _mm256_max_pd as a faster alternative.
 */
static inline Float64_AVX fmax(Float64_AVX x, Float64_AVX y) {
	return Float64_AVX(_mm256_fmax_pd(x.val, y.val));
}

/**
 * @brief Returns the fmin of x and y. Correctly handling NaN and signed zeros.
 * You may use _mm256_min_pd as a faster alternative.
 */
static inline Float64_AVX fmin(Float64_AVX x, Float64_AVX y) {
	return Float64_AVX(_mm256_fmin_pd(x.val, y.val));
}

static inline Float64_AVX fdim(Float64_AVX x, Float64_AVX y) {
	return Float64_AVX(_mm256_fdim_pd(x.val, y.val));
}

/* Float64_AVX and T */

/**
 * @brief Returns the fmax of x and y. Correctly handling NaN and signed zeros.
 * You may use _mm256_max_pd as a faster alternative.
 */
template<typename T>
static inline Float64_AVX fmax(Float64_AVX x, T y) {
	return Float64_AVX(_mm256_fmax_pd(x.val, Float64_AVX_Restrict_Numeric(y).val));
}

/**
 * @brief Returns the fmin of x and y. Correctly handling NaN and signed zeros.
 * You may use _mm256_min_pd as a faster alternative.
 */
template<typename T>
static inline Float64_AVX fmin(Float64_AVX x, T y) {
	return Float64_AVX(_mm256_fmin_pd(x.val, Float64_AVX_Restrict_Numeric(y).val));
}

template<typename T>
static inline Float64_AVX fdim(Float64_AVX x, T y) {
	return Float64_AVX(_mm256_fdim_pd(x.val, Float64_AVX_Restrict_Numeric(y).val));
}

/* T and Float64_AVX */

/**
 * @brief Returns the fmax of x and y. Correctly handling NaN and signed zeros.
 * You may use _mm256_max_pd as a faster alternative.
 */
template<typename T>
static inline Float64_AVX fmax(T x, Float64_AVX y) {
	return Float64_AVX(_mm256_fmax_pd(Float64_AVX_Restrict_Numeric(x), y.val));
}

/**
 * @brief Returns the fmin of x and y. Correctly handling NaN and signed zeros.
 * You may use _mm256_min_pd as a faster alternative.
 */
template<typename T>
static inline Float64_AVX fmin(T x, Float64_AVX y) {
	return Float64_AVX(_mm256_fmin_pd(Float64_AVX_Restrict_Numeric(x), y.val));
}

template<typename T>
static inline Float64_AVX fdim(T x, Float64_AVX y) {
	return Float64_AVX(_mm256_fdim_pd(Float64_AVX_Restrict_Numeric(x), y.val));
}

//------------------------------------------------------------------------------
// Float64_AVX rounding
//------------------------------------------------------------------------------

static inline Float64_AVX trunc(Float64_AVX x) {
	return Float64_AVX(_mm256_round_pd(x.val, _MM_FROUND_TO_ZERO));
}

static inline Float64_AVX floor(Float64_AVX x) {
	// return Float64_AVX(_mm256_round_pd(x, _MM_FROUND_TO_NEG_INF));
	return Float64_AVX(_mm256_floor_pd(x.val));
}

static inline Float64_AVX ceil(Float64_AVX x) {
	// return Float64_AVX(_mm256_round_pd(x, _MM_FROUND_TO_POS_INF));
	return Float64_AVX(_mm256_ceil_pd(x.val));
}

static inline Float64_AVX round(Float64_AVX x) {
	return Float64_AVX(_mm256_round_pd(x.val, _MM_FROUND_TO_NEAREST_INT));
}

static inline Float64_AVX rint(Float64_AVX x) {
	return Float64_AVX(_mm256_round_pd(x.val, _MM_FROUND_CUR_DIRECTION));
}

static inline Float64_AVX nearbyint(Float64_AVX x) {
	return Float64_AVX(_mm256_round_pd(x.val, _MM_FROUND_CUR_DIRECTION | _MM_FROUND_NO_EXC));
}

//------------------------------------------------------------------------------
// Float64_AVX math.h functions
//------------------------------------------------------------------------------

static inline Float64_AVX sqrt(Float64_AVX x) {
	return Float64_AVX(_mm256_sqrt_pd(x.val));
}

//------------------------------------------------------------------------------
// Float64_AVX math.h functions
//------------------------------------------------------------------------------

#ifdef __FMA__

/* fma */

static inline Float64_AVX fma(Float64_AVX x, Float64_AVX y, Float64_AVX z) {
	return Float64_AVX(_mm256_fmadd_pd(x.val, y.val, z.val));
}

#endif

#ifdef __AVX2__

static inline Float64_AVX nextafter(Float64_AVX x, Float64_AVX y) {
	return Float64_AVX(_mm256_nextafter_pd(x.val, y.val));
}

template<typename T>
static inline Float64_AVX nextafter(Float64_AVX x, T y) {
	return Float64_AVX(_mm256_nextafter_pd(x.val, Float64_AVX(y).val));
}

template<typename T>
static inline Float64_AVX nextafter(T x, Float64_AVX y) {
	return Float64_AVX(_mm256_nextafter_pd(Float64_AVX(x).val, y.val));
}

static inline Float64_AVX nexttoward(Float64_AVX x, long double y) {
	return Float64_AVX(_mm256_nexttoward_pd(x.val, y));
}

#endif

#if 0

/* Won't compile */

template<typename Return_Type>
static inline Return_Type ilogb(Float64_AVX x);

template <>
static inline __m256i ilogb<__m256i>(Float64_AVX x) {
	return _mm256_ilogb_pd_epi64(x.val);
}

template <>
static inline __m128i ilogb<__m128i>(Float64_AVX x) {
	return _mm256_ilogb_pd_epi32(x.val);
}

#endif

#if 0

/** @note untested */
static inline Float64_AVX ldexp(const Float64_AVX x_tmp, __m256i expon) {
	const __m256d x = x_tmp.val;
	
	/* Test for denormal values */
	
	const __m256i denormal_test = _mm256_and_si256(
		// Extracts the mantissa bits
		_mm256_castpd_si256(
			_mm256_and_pd(x, _mm256_get_mantissa_mask_pd())
		),
		// Checks that the exponent is zero
		_mm256_cmpeq_epi64(
			_mm256_castpd_si256(
				_mm256_and_pd(x, _mm256_get_exponent_mask_pd())
			), _mm256_setzero_si256()
		)
	);

	__m256i denormal_shift = _mm256_setzero_si256();
	/**
	 * Checks if any numbers are denormal and non-zero. If this returns true,
	 * we can skip this code, otherwise we have to extract the highest set bit
	 * the long way.
	 */
	if (_mm256_movemask_pd(_mm256_castsi256_pd(
		_mm256_cmpeq_epi64(denormal_test, _mm256_setzero_si256())
	)) == 0) {
		// Finds the index of the highest set bit
		denormal_shift = _mm256_add(denormal_shift, _mm256_andnot_si256(
			_mm256_set1_epi64x((int64_t)32)
			_mm256_cmpeq_epi64(_mm256_and_si256(denormal_test,
				_mm256_set1_epi64x((int64_t)0xFFFFFFFF00000000)
			), _mm256_setzero_si256())
		));
		denormal_shift = _mm256_add(denormal_shift, _mm256_andnot_si256(
			_mm256_set1_epi64x((int64_t)16)
			_mm256_cmpeq_epi64(_mm256_and_si256(denormal_test,
				_mm256_set1_epi64x((int64_t)0xFFFF0000FFFF0000)
			), _mm256_setzero_si256())
		));
		denormal_shift = _mm256_add(denormal_shift, _mm256_andnot_si256(
			_mm256_set1_epi64x((int64_t)8)
			_mm256_cmpeq_epi64(_mm256_and_si256(denormal_test,
				_mm256_set1_epi64x((int64_t)0xFF00FF00FF00FF00)
			), _mm256_setzero_si256())
		));
		denormal_shift = _mm256_add(denormal_shift, _mm256_andnot_si256(
			_mm256_set1_epi64x((int64_t)4)
			_mm256_cmpeq_epi64(_mm256_and_si256(denormal_test,
				_mm256_set1_epi64x((int64_t)0xF0F0F0F0F0F0F0F0)
			), _mm256_setzero_si256())
		));
		denormal_shift = _mm256_add(denormal_shift, _mm256_andnot_si256(
			_mm256_set1_epi64x((int64_t)2)
			_mm256_cmpeq_epi64(_mm256_and_si256(denormal_test,
				_mm256_set1_epi64x((int64_t)0xCCCCCCCCCCCCCCCC)
			), _mm256_setzero_si256())
		));
		denormal_shift = _mm256_add(denormal_shift, _mm256_andnot_si256(
			_mm256_set1_epi64x((int64_t)1)
			_mm256_cmpeq_epi64(_mm256_and_si256(denormal_test,
				_mm256_set1_epi64x((int64_t)0xAAAAAAAAAAAAAAAA)
			), _mm256_setzero_si256())
		));
	}

	/* Add the exponents */

	const __m256d ret_original = _mm256_or_pd(
		_mm256_or_pd(_mm256_isinf_pd(x), _mm256_isnan_pd(x)),
		_mm256_cmp_pd(x, _mm256_setzero_pd(), _CMP_EQ_OS)
	);

	// Extract the exponent
	__m256i x_expon = _mm256_castpd_si256(
		_mm256_andnot_pd(x.val, _mm256_get_exponent_mask_pd())
	);


	// Align both exponents to the 16bit boundry
	x_expon = _mm256_srli_epi64(x_expon, 4);
	expon = _mm256_slli_epi64(expon, 48);
	/**
	 * Add the exponents for ldexp via saturation. Any 16bit word that isn't
	 * part of the exponent should be zero.
	 */
	__m256i expon_sum = _mm256_adds_epi16(_mm256_subs_epi16(x_expon, denormal_shift), expon);
	
	// Greater than the largest finite exponent
	const __m256d ret_isinf = _mm256_castsi256_pd(
		_mm256_cmpgt_epi64(expon_sum, _mm256_set1_epi64x((int64_t)0x7FE << (int64_t)48))
	);
	// Greater than the smallest normal exponent
	const __m256d ret_isnormal = _mm256_castsi256_pd(
		_mm256_cmpgt_epi64(expon_sum, _mm256_set1_epi64x((int64_t)0x000 << (int64_t)48))
	);

	const __m256d x_mant = _mm256_and_pd(x, _mm256_get_mantissa_mask_pd());

	// Calculates the subnormal result (This is still wrong)
	__m256i ret_subnormal = _mm256_srli_epi64(_mm256_abs_epi16(expon_sum), 48);
	ret_subnormal = _mm256_srlv_epi64(
		_mm256_slli_epi64(_mm256_castpd_si256(x_mant), 1), ret_subnormal
	);

	// Reset exponent
	expon_sum = _mm256_slli_epi64(x_expon, 4);
	__m256d final_expon = _mm256_or_pd(_mm256_castsi256_pd(expon_sum), x_mant);

	// Sets ret to expon_sum. May overwrite ret with infinity
	__m256d ret = _mm256_blendv_pd(final_expon, _mm256_get_infinity_pd(), ret_isinf);
	// May overwrite ret with subnormal
	ret = _mm256_blendv_pd(ret_subnormal, ret, ret_isnormal);
	// May overwrite ret with original
	ret = _mm256_blendv_pd(ret_subnormal, ret, ret_original);
	return _mm256_copysign_pd(ret, x);
}

#endif

#ifdef __AVX2__

static inline Float64_AVX ldexp(const Float64_AVX x, __m256i expon) {
	return Float64_AVX(_mm256_ldexp_pd_epi64(x.val, expon));
}

static inline Float64_AVX ldexp(Float64_AVX x, __m128i expon) {
	return Float64_AVX(_mm256_ldexp_pd_epi64(x.val, _mm256_cvtepi32_epi64(expon)));
}

static inline Float64_AVX ldexp(Float64_AVX x, int32_t expon) {
	return Float64_AVX(_mm256_ldexp_pd_i32(x.val, expon));
}

static inline Float64_AVX ldexp(Float64_AVX x, int64_t expon) {
	return Float64_AVX(_mm256_ldexp_pd_i32(x.val, (int32_t)expon));
}

/** @brief wraps ldexp(Float64_AVX x, int64_t expon) */
static inline Float64_AVX scalbn(Float64_AVX x, int64_t expon) {
	return ldexp(x, expon);
}

/** @brief wraps ldexp(Float64_AVX x, __m128i expon) */
static inline Float64_AVX scalbn(Float64_AVX x, __m128i expon) {
	return ldexp(x, expon);
}
/** @brief wraps ldexp(Float64_AVX x, __m256i expon) */
static inline Float64_AVX scalbn(Float64_AVX x, __m256i expon) {
	return ldexp(x, expon);
}

#endif

#ifdef __AVX2__

static inline Float64_AVX frexp(Float64_AVX x, __m128i* expon) {
	return Float64_AVX(_mm256_frexp_pd_epi32(x.val, expon));
}
static inline Float64_AVX frexp(Float64_AVX x, __m256i* expon) {
	return Float64_AVX(_mm256_frexp_pd_epi64(x.val, expon));
}

/** @brief wraps ldexp(Float64_AVX x, int32_t expon) */
static inline Float64_AVX scalbn(Float64_AVX x, int32_t expon) {
	return ldexp(x, expon);
}

#endif

#endif /* FLOAT64_AVX_HPP */
