/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef FLOAT64_AVX_HPP
#define FLOAT64_AVX_HPP

#if (!defined(__AVX__) && defined(__GNUC__))
	#error "__AVX__ is not enabled in your compiler. Try -mavx"
#endif

#include <stdint.h>
#include <immintrin.h>

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
		inline static constexpr Float64_AVX round_error() {
			return Float64_AVX(_mm256_set1_pd(std::numeric_limits<double>::round_error()));
		}
		inline static constexpr Float64_AVX infinity() {
			return Float64_AVX(_mm256_set1_pd(std::numeric_limits<double>::infinity()));
		}
		inline static constexpr Float64_AVX quiet_NaN() {
			return Float64_AVX(_mm256_set1_pd(std::numeric_limits<double>::quiet_NaN()));
		}
		inline static constexpr Float64_AVX signaling_NaN() {
			return Float64_AVX(_mm256_set1_pd(std::numeric_limits<double>::signaling_NaN()));
		}
		inline static constexpr Float64_AVX denorm_min() {
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
	Float64_AVX ret;
	ret.val = _mm256_xor_pd(x.val,
		_mm256_and_pd(
			_mm256_xor_pd(x.val, y.val),
			_mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x7FFFFFFFFFFFFFFF))
		), y.val
	);
	return ret;
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

static inline Float64_AVX operator!(Float64_AVX x) {
	return Float64_AVX(_mm256_xor_pd(
		x.val,
		_mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0xFFFFFFFFFFFFFFFF))
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
	return Float64_AVX(_mm256_round_pd(x, _MM_FROUND_TO_ZERO));
}

static inline Float64_AVX floor(Float64_AVX x) {
	return Float64_AVX(_mm256_round_pd(x, _MM_FROUND_TO_NEG_INF));
}

static inline Float64_AVX ceil(Float64_AVX x) {
	return Float64_AVX(_mm256_round_pd(x, _MM_FROUND_TO_POS_INF));
}

static inline Float64_AVX round(Float64_AVX x) {
	return Float64_AVX(_mm256_round_pd(x, _MM_FROUND_TO_NEAREST_INT));
}

static inline Float64_AVX rint(Float64_AVX x) {
	return Float64_AVX(_mm256_round_pd(x, _MM_FROUND_CUR_DIRECTION));
}

static inline Float64_AVX nearbyint(Float64_AVX x) {
	return Float64_AVX(_mm256_round_pd(x, _MM_FROUND_CUR_DIRECTION | _MM_FROUND_NO_EXC));
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

#if 0
static inline Float64_AVX nextafter(Float64_AVX x, Float64_AVX y) {
	
}

template<typename Return_Type>
static inline ilogb(Float64_AVX x);

template <>
static inline __m256i ilogb(Float64_AVX x) {

}

template <>
static inline __m128i ilogb(Float64_AVX x) {

}

static inline Float64_AVX ldexp(Float64_AVX x, int32_t expon) {
	
}
static inline Float64_AVX ldexp(Float64_AVX x, __m128i expon) {
	
}
static inline Float64_AVX ldexp(Float64_AVX x, __m256i expon) {
	
}

static inline Float64_AVX frexp(Float64_AVX x, __m128i* expon) {
	
}
static inline Float64_AVX frexp(Float64_AVX x, __m256i* expon) {
	
}

/** @brief wraps ldexp(Float64_AVX x, int32_t expon) */
static inline Float64_AVX scalbn(Float64_AVX x, int32_t expon) {
	return ldexp(Float64_AVX, expon);
}
/** @brief wraps ldexp(Float64_AVX x, __m128i expon) */
static inline Float64_AVX scalbn(Float64_AVX x, __m128i expon) {
	return ldexp(Float64_AVX, expon);
}
/** @brief wraps ldexp(Float64_AVX x, __m256i expon) */
static inline Float64_AVX scalbn(Float64_AVX x, __m256i expon) {
	return ldexp(Float64_AVX, expon);
}

#endif

#endif /* FLOAT64_AVX_HPP */
