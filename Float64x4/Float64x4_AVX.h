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

#ifndef FLOAT64X4_AVX_H
#define FLOAT64X4_AVX_H

/**
 * @note Requires AVX or later.
 * @warning -Ofast may break this library. -O3 compiles okay on gcc and clang.
 */

#include "Float64x4_def.h"
#include "../Float64x2/Float64x2_AVX.h"

#include <stdint.h>

#if (!defined(__AVX__) && defined(__GNUC__))
	#error "__AVX__ is not enabled in your compiler. Try -mavx"
#endif

#include <immintrin.h>

//------------------------------------------------------------------------------
// __m256dx4 restrict
//------------------------------------------------------------------------------

/**
 * @brief __M256DX4_RESTRICT defines the restrict keyword for C++ compilers.
 * You may define it before including this header to use your compilers version
 * of C++ restrict, or to disable C++ restrict for this header entirely.
 */

#ifndef __M256DX4_RESTRICT
	#ifndef __cplusplus
		#define __M256DX4_RESTRICT restrict
	#elif defined(__GNUC__)
		#define __M256DX4_RESTRICT __restrict
	#elif defined(_MSC_VER)
		#define __M256DX4_RESTRICT __restrict
	#elif defined(__INTEL_COMPILER)
		#define __M256DX4_RESTRICT __restrict
	#else 
		#define __M256DX4_RESTRICT
	#endif
#endif

#ifdef __cplusplus
	extern "C" {
#endif

/**
 * @brief Holds four Quad-Float64 dekker floats
 */
typedef struct __m256dx4 {
	__m256d val[4];
} __m256dx4;

//------------------------------------------------------------------------------
// __m256dx4 set1 functions
//------------------------------------------------------------------------------

inline __m256dx4 _mm256x4_setzero_pdx4(void) {
	__m256dx4 ret;
	ret.val[0] = _mm256_setzero_pd();
	ret.val[1] = _mm256_setzero_pd();
	ret.val[2] = _mm256_setzero_pd();
	ret.val[3] = _mm256_setzero_pd();
	return ret;
}

inline __m256dx4 _mm256x4_set1_pdx4(const Float64x4 value) {
	__m256dx4 ret;
	ret.val[0] = _mm256_set1_pd(value.val[0]);
	ret.val[1] = _mm256_set1_pd(value.val[1]);
	ret.val[2] = _mm256_set1_pd(value.val[2]);
	ret.val[3] = _mm256_set1_pd(value.val[3]);
	return ret;
}

inline __m256dx4 _mm256x4_set1_pdx2(const Float64x2 value) {
	__m256dx4 ret;
	ret.val[0] = _mm256_set1_pd(value.hi);
	ret.val[1] = _mm256_set1_pd(value.lo);
	ret.val[2] = _mm256_setzero_pd();
	ret.val[3] = _mm256_setzero_pd();
	return ret;
}


inline __m256dx4 _mm256x4_set1_pd(double x) {
	__m256dx4 ret;
	ret.val[0] = _mm256_set1_pd(x);
	ret.val[1] = _mm256_setzero_pd();
	ret.val[2] = _mm256_setzero_pd();
	ret.val[3] = _mm256_setzero_pd();
	return ret;
}

inline __m256dx4 _mm256x4_set1_epi64x(long long x) {
	__m256dx4 ret;
	ret.val[0] = _mm256_castsi256_pd(_mm256_set1_epi64x(x));
	ret.val[1] = _mm256_castsi256_pd(_mm256_set1_epi64x(x));
	ret.val[2] = _mm256_castsi256_pd(_mm256_set1_epi64x(x));
	ret.val[3] = _mm256_castsi256_pd(_mm256_set1_epi64x(x));
	return ret;
}

//------------------------------------------------------------------------------
// __m256dx4 set functions
//------------------------------------------------------------------------------

inline __m256dx4 _mm256x4_set_pdx4(
	const Float64x4 e3, const Float64x4 e2, const Float64x4 e1, const Float64x4 e0
) {
	__m256dx4 ret;
	ret.val[0] = _mm256_set_pd(e3.val[0], e2.val[0], e1.val[0], e0.val[0]);
	ret.val[1] = _mm256_set_pd(e3.val[1], e2.val[1], e1.val[1], e0.val[1]);
	ret.val[2] = _mm256_set_pd(e3.val[2], e2.val[2], e1.val[2], e0.val[2]);
	ret.val[3] = _mm256_set_pd(e3.val[3], e2.val[3], e1.val[3], e0.val[3]);
	return ret;
}

inline __m256dx4 _mm256x4_set_pdx2(
	const Float64x2 e3, const Float64x2 e2, const Float64x2 e1, const Float64x2 e0
) {
	__m256dx4 ret;
	ret.val[0] = _mm256_set_pd(e3.hi, e2.hi, e1.hi, e0.hi);
	ret.val[1] = _mm256_set_pd(e3.lo, e2.lo, e1.lo, e0.lo);
	ret.val[2] = _mm256_setzero_pd();
	ret.val[3] = _mm256_setzero_pd();
	return ret;
}

inline __m256dx4 _mm256x4_set_pd(
	double e3, double e2, double e1, double e0
) {
	__m256dx4 ret;
	ret.val[0] = _mm256_set_pd(e3, e2, e1, e0);
	ret.val[1] = _mm256_setzero_pd();
	ret.val[2] = _mm256_setzero_pd();
	ret.val[3] = _mm256_setzero_pd();
	return ret;
}

inline __m256dx4 _mm256x4_set_epi64x(
	const long long e3[4], const long long e2[4], const long long e1[4], const long long e0[4]
) {
	__m256dx4 ret;
	ret.val[0] = _mm256_castsi256_pd(_mm256_set_epi64x(e3[0], e2[0], e1[0], e0[0]));
	ret.val[1] = _mm256_castsi256_pd(_mm256_set_epi64x(e3[1], e2[1], e1[1], e0[1]));
	ret.val[2] = _mm256_castsi256_pd(_mm256_set_epi64x(e3[2], e2[2], e1[2], e0[2]));
	ret.val[3] = _mm256_castsi256_pd(_mm256_set_epi64x(e3[3], e2[3], e1[3], e0[3]));
	return ret;
}

//------------------------------------------------------------------------------
// __m256dx4 setr (set reverse) functions
//------------------------------------------------------------------------------

inline __m256dx4 _mm256x4_setr_pdx4(
	const Float64x4 e3, const Float64x4 e2, const Float64x4 e1, const Float64x4 e0
) {
	__m256dx4 ret;
	ret.val[0] = _mm256_setr_pd(e3.val[0], e2.val[0], e1.val[0], e0.val[0]);
	ret.val[1] = _mm256_setr_pd(e3.val[1], e2.val[1], e1.val[1], e0.val[1]);
	ret.val[2] = _mm256_setr_pd(e3.val[2], e2.val[2], e1.val[2], e0.val[2]);
	ret.val[3] = _mm256_setr_pd(e3.val[3], e2.val[3], e1.val[3], e0.val[3]);
	return ret;
}

inline __m256dx4 _mm256x4_setr_pdx2(
	const Float64x2 e3, const Float64x2 e2, const Float64x2 e1, const Float64x2 e0
) {
	__m256dx4 ret;
	ret.val[0] = _mm256_setr_pd(e3.hi, e2.hi, e1.hi, e0.hi);
	ret.val[1] = _mm256_setr_pd(e3.lo, e2.lo, e1.lo, e0.lo);
	ret.val[2] = _mm256_setzero_pd();
	ret.val[3] = _mm256_setzero_pd();
	return ret;
}

inline __m256dx4 _mm256x4_setr_pd(
	double e3, double e2, double e1, double e0
) {
	__m256dx4 ret;
	ret.val[0] = _mm256_setr_pd(e3, e2, e1, e0);
	ret.val[1] = _mm256_setzero_pd();
	ret.val[2] = _mm256_setzero_pd();
	ret.val[3] = _mm256_setzero_pd();
	return ret;
}

inline __m256dx4 _mm256x4_setr_epi64x(
	const long long e3[4], const long long e2[4], const long long e1[4], const long long e0[4]
) {
	__m256dx4 ret;
	ret.val[0] = _mm256_castsi256_pd(_mm256_setr_epi64x(e3[0], e2[0], e1[0], e0[0]));
	ret.val[1] = _mm256_castsi256_pd(_mm256_setr_epi64x(e3[1], e2[1], e1[1], e0[1]));
	ret.val[2] = _mm256_castsi256_pd(_mm256_setr_epi64x(e3[2], e2[2], e1[2], e0[2]));
	ret.val[3] = _mm256_castsi256_pd(_mm256_setr_epi64x(e3[3], e2[3], e1[3], e0[3]));
	return ret;
}

//------------------------------------------------------------------------------
// __m256dx4 load operations
//------------------------------------------------------------------------------

/**
 * @note mem_addr must be aligned on a 32-byte boundary or a general-protection
 * exception may be generated.
 */
inline __m256dx4 _mm256x4_load_raw_pd(const double* mem_addr) {
	__m256dx4 ret;
	ret.val[0] = _mm256_load_pd(mem_addr);
	mem_addr += sizeof(__m256d) / sizeof(double);
	ret.val[1] = _mm256_load_pd(mem_addr);
	mem_addr += sizeof(__m256d) / sizeof(double);
	ret.val[2] = _mm256_load_pd(mem_addr);
	mem_addr += sizeof(__m256d) / sizeof(double);
	ret.val[3] = _mm256_load_pd(mem_addr);
	return ret;
}

inline __m256dx4 _mm256x4_loadu_raw_pd(const double* mem_addr) {
	__m256dx4 ret;
	ret.val[0] = _mm256_loadu_pd(mem_addr);
	mem_addr += sizeof(__m256d) / sizeof(double);
	ret.val[1] = _mm256_loadu_pd(mem_addr);
	mem_addr += sizeof(__m256d) / sizeof(double);
	ret.val[2] = _mm256_loadu_pd(mem_addr);
	mem_addr += sizeof(__m256d) / sizeof(double);
	ret.val[3] = _mm256_loadu_pd(mem_addr);
	return ret;
}

//------------------------------------------------------------------------------
// __m256dx4 store operations
//------------------------------------------------------------------------------

/**
 * @note mem_addr must be aligned on a 32-byte boundary or a general-protection
 * exception may be generated.
 */
inline void _mm256_store_raw_pdx4(double* mem_addr, __m256dx4 x) {
	_mm256_store_pd(mem_addr, x.val[0]);
	mem_addr += sizeof(__m256d) / sizeof(double);
	_mm256_store_pd(mem_addr, x.val[1]);
	mem_addr += sizeof(__m256d) / sizeof(double);
	_mm256_store_pd(mem_addr, x.val[2]);
	mem_addr += sizeof(__m256d) / sizeof(double);
	_mm256_store_pd(mem_addr, x.val[3]);
}

inline void _mm256_storeu_raw_pdx4(double* mem_addr, __m256dx4 x) {
	_mm256_storeu_pd(mem_addr, x.val[0]);
	mem_addr += sizeof(__m256d) / sizeof(double);
	_mm256_storeu_pd(mem_addr, x.val[1]);
	mem_addr += sizeof(__m256d) / sizeof(double);
	_mm256_storeu_pd(mem_addr, x.val[2]);
	mem_addr += sizeof(__m256d) / sizeof(double);
	_mm256_storeu_pd(mem_addr, x.val[3]);
}

//------------------------------------------------------------------------------
// __m256dx4 bitwise operations
//------------------------------------------------------------------------------

/**
 * @brief bitwise not `~x`
 */
inline __m256dx4 _mm256x4_not_pdx4(__m256dx4 x) {
	x.val[0] = _mm256_andnot_pd(x.val[0], _mm256_setzero_pd());
	x.val[1] = _mm256_andnot_pd(x.val[1], _mm256_setzero_pd());
	x.val[2] = _mm256_andnot_pd(x.val[2], _mm256_setzero_pd());
	x.val[3] = _mm256_andnot_pd(x.val[3], _mm256_setzero_pd());
	return x;
}

/**
 * @brief bitwise and `x & y`
 */
inline __m256dx4 _mm256x4_and_pdx4(__m256dx4 x, const __m256dx4 y) {
	x.val[0] = _mm256_and_pd(x.val[0], y.val[0]);
	x.val[1] = _mm256_and_pd(x.val[1], y.val[1]);
	x.val[2] = _mm256_and_pd(x.val[2], y.val[2]);
	x.val[3] = _mm256_and_pd(x.val[3], y.val[3]);
	return x;
}

/**
 * @brief bitwise andnot `x & ~y`
 */
inline __m256dx4 _mm256x4_andnot_pdx4(__m256dx4 x, const __m256dx4 y) {
	x.val[0] = _mm256_andnot_pd(x.val[0], y.val[0]);
	x.val[1] = _mm256_andnot_pd(x.val[1], y.val[1]);
	x.val[2] = _mm256_andnot_pd(x.val[2], y.val[2]);
	x.val[3] = _mm256_andnot_pd(x.val[3], y.val[3]);
	return x;
}

/**
 * @brief bitwise or `x | y`
 */
inline __m256dx4 _mm256x4_or_pdx4(__m256dx4 x, const __m256dx4 y) {
	x.val[0] = _mm256_or_pd(x.val[0], y.val[0]);
	x.val[1] = _mm256_or_pd(x.val[1], y.val[1]);
	x.val[2] = _mm256_or_pd(x.val[2], y.val[2]);
	x.val[3] = _mm256_or_pd(x.val[3], y.val[3]);
	return x;
}

/**
 * @brief bitwise xor `x ^ y`
 */
inline __m256dx4 _mm256x4_xor_pdx4(__m256dx4 x, const __m256dx4 y) {
	x.val[0] = _mm256_xor_pd(x.val[0], y.val[0]);
	x.val[1] = _mm256_xor_pd(x.val[1], y.val[1]);
	x.val[2] = _mm256_xor_pd(x.val[2], y.val[2]);
	x.val[3] = _mm256_xor_pd(x.val[3], y.val[3]);
	return x;
}

//------------------------------------------------------------------------------
// __m256dx4 reduced comparison functions
//------------------------------------------------------------------------------

	/**
	 * @brief _CMP_EQ_UQ
	 */
	inline __m256d _mm256_cmpeq_pdx4(__m256dx4 x, __m256dx4 y) {
		return _mm256_and_pd(
			_mm256_and_pd(
				_mm256_cmp_pd(x.val[0], y.val[0], _CMP_EQ_UQ),
				_mm256_cmp_pd(x.val[1], y.val[1], _CMP_EQ_UQ)
			),
			_mm256_and_pd(
				_mm256_cmp_pd(x.val[2], y.val[2], _CMP_EQ_UQ),
				_mm256_cmp_pd(x.val[3], y.val[3], _CMP_EQ_UQ)
			)
		);
	}

	/**
	 * @brief _CMP_NEQ_UQ
	 */
	inline __m256d _mm256_cmpneq_pdx4(__m256dx4 x, __m256dx4 y) {
		return _mm256_or_pd(
			_mm256_or_pd(
				_mm256_cmp_pd(x.val[0], y.val[0], _CMP_NEQ_UQ),
				_mm256_cmp_pd(x.val[1], y.val[1], _CMP_NEQ_UQ)
			),
			_mm256_or_pd(
				_mm256_cmp_pd(x.val[2], y.val[2], _CMP_NEQ_UQ),
				_mm256_cmp_pd(x.val[3], y.val[3], _CMP_NEQ_UQ)
			)
		);
	}

	/**
	 * @brief _CMP_ORD_Q
	 */
	inline __m256d _mm256_cmpord_pdx4(__m256dx4 x, __m256dx4 y) {
		return _mm256_and_pd(
			_mm256_and_pd(
				_mm256_cmp_pd(x.val[0], y.val[0], _CMP_ORD_Q),
				_mm256_cmp_pd(x.val[1], y.val[1], _CMP_ORD_Q)
			),
			_mm256_and_pd(
				_mm256_cmp_pd(x.val[2], y.val[2], _CMP_ORD_Q),
				_mm256_cmp_pd(x.val[3], y.val[3], _CMP_ORD_Q)
			)
		);
	}

	/**
	 * @brief _CMP_UNORD_Q
	 */
	inline __m256d _mm256_cmpunord_pdx4(__m256dx4 x, __m256dx4 y) {
		return _mm256_or_pd(
			_mm256_or_pd(
				_mm256_cmp_pd(x.val[0], y.val[0], _CMP_UNORD_Q),
				_mm256_cmp_pd(x.val[1], y.val[1], _CMP_UNORD_Q)
			),
			_mm256_or_pd(
				_mm256_cmp_pd(x.val[2], y.val[2], _CMP_UNORD_Q),
				_mm256_cmp_pd(x.val[3], y.val[3], _CMP_UNORD_Q)
			)
		);
	}

	/**
	 * @brief _CMP_LT_OQ
	 */
	inline __m256d _mm256_cmplt_pdx4(__m256dx4 x, __m256dx4 y) {
		__m256d cmp_lt_0 = _mm256_cmp_pd(x.val[0], y.val[0], _CMP_LT_OQ);
		__m256d cmp_eq_0 = _mm256_cmp_pd(x.val[0], y.val[0], _CMP_EQ_OQ);
		__m256d cmp_lt_1 = _mm256_cmp_pd(x.val[1], y.val[1], _CMP_LT_OQ);
		__m256d cmp_eq_1 = _mm256_cmp_pd(x.val[1], y.val[1], _CMP_EQ_OQ);
		__m256d cmp_lt_2 = _mm256_cmp_pd(x.val[2], y.val[2], _CMP_LT_OQ);
		__m256d cmp_eq_2 = _mm256_cmp_pd(x.val[2], y.val[2], _CMP_EQ_OQ);
		__m256d cmp_lt_3 = _mm256_cmp_pd(x.val[3], y.val[3], _CMP_LT_OQ);
		return _mm256_or_pd(cmp_lt_0, _mm256_and_pd(cmp_eq_0,
			_mm256_or_pd(cmp_lt_1, _mm256_and_pd(cmp_eq_1,
				_mm256_or_pd(cmp_lt_2, _mm256_and_pd(cmp_eq_2, cmp_lt_3))
			))
		));
	}

	/**
	 * @brief _CMP_LE_OQ
	 */
	inline __m256d _mm256_cmple_pdx4(__m256dx4 x, __m256dx4 y) {
		__m256d cmp_lt_0 = _mm256_cmp_pd(x.val[0], y.val[0], _CMP_LT_OQ);
		__m256d cmp_eq_0 = _mm256_cmp_pd(x.val[0], y.val[0], _CMP_EQ_OQ);
		__m256d cmp_lt_1 = _mm256_cmp_pd(x.val[1], y.val[1], _CMP_LT_OQ);
		__m256d cmp_eq_1 = _mm256_cmp_pd(x.val[1], y.val[1], _CMP_EQ_OQ);
		__m256d cmp_lt_2 = _mm256_cmp_pd(x.val[2], y.val[2], _CMP_LT_OQ);
		__m256d cmp_eq_2 = _mm256_cmp_pd(x.val[2], y.val[2], _CMP_EQ_OQ);
		__m256d cmp_le_3 = _mm256_cmp_pd(x.val[3], y.val[3], _CMP_LE_OQ);
		return _mm256_or_pd(cmp_lt_0, _mm256_and_pd(cmp_eq_0,
			_mm256_or_pd(cmp_lt_1, _mm256_and_pd(cmp_eq_1,
				_mm256_or_pd(cmp_lt_2, _mm256_and_pd(cmp_eq_2, cmp_le_3))
			))
		));
	}

	/**
	 * @brief _CMP_GT_OQ
	 */
	inline __m256d _mm256_cmpgt_pdx4(__m256dx4 x, __m256dx4 y) {
		__m256d cmp_gt_0 = _mm256_cmp_pd(x.val[0], y.val[0], _CMP_GT_OQ);
		__m256d cmp_eq_0 = _mm256_cmp_pd(x.val[0], y.val[0], _CMP_EQ_OQ);
		__m256d cmp_gt_1 = _mm256_cmp_pd(x.val[1], y.val[1], _CMP_GT_OQ);
		__m256d cmp_eq_1 = _mm256_cmp_pd(x.val[1], y.val[1], _CMP_EQ_OQ);
		__m256d cmp_gt_2 = _mm256_cmp_pd(x.val[2], y.val[2], _CMP_GT_OQ);
		__m256d cmp_eq_2 = _mm256_cmp_pd(x.val[2], y.val[2], _CMP_EQ_OQ);
		__m256d cmp_gt_3 = _mm256_cmp_pd(x.val[3], y.val[3], _CMP_GT_OQ);
		return _mm256_or_pd(cmp_gt_0, _mm256_and_pd(cmp_eq_0,
			_mm256_or_pd(cmp_gt_1, _mm256_and_pd(cmp_eq_1,
				_mm256_or_pd(cmp_gt_2, _mm256_and_pd(cmp_eq_2, cmp_gt_3))
			))
		));
	}

	/**
	 * @brief _CMP_GE_OQ
	 */
	inline __m256d _mm256_cmpge_pdx4(__m256dx4 x, __m256dx4 y) {
		__m256d cmp_gt_0 = _mm256_cmp_pd(x.val[0], y.val[0], _CMP_GT_OQ);
		__m256d cmp_eq_0 = _mm256_cmp_pd(x.val[0], y.val[0], _CMP_EQ_OQ);
		__m256d cmp_gt_1 = _mm256_cmp_pd(x.val[1], y.val[1], _CMP_GT_OQ);
		__m256d cmp_eq_1 = _mm256_cmp_pd(x.val[1], y.val[1], _CMP_EQ_OQ);
		__m256d cmp_gt_2 = _mm256_cmp_pd(x.val[2], y.val[2], _CMP_GT_OQ);
		__m256d cmp_eq_2 = _mm256_cmp_pd(x.val[2], y.val[2], _CMP_EQ_OQ);
		__m256d cmp_ge_3 = _mm256_cmp_pd(x.val[3], y.val[3], _CMP_GE_OQ);
		return _mm256_or_pd(cmp_gt_0, _mm256_and_pd(cmp_eq_0,
			_mm256_or_pd(cmp_gt_1, _mm256_and_pd(cmp_eq_1,
				_mm256_or_pd(cmp_gt_2, _mm256_and_pd(cmp_eq_2, cmp_ge_3))
			))
		));
	}

/* __m256dx4 compare __m256dx2 */

	/**
	 * @brief _CMP_EQ_UQ
	 */
	inline __m256d _mm256_cmpeq_pdx4_pdx2(__m256dx4 x, __m256dx2 y) {
		return _mm256_and_pd(
			_mm256_and_pd(
				_mm256_cmp_pd(x.val[0], y.hi, _CMP_EQ_UQ),
				_mm256_cmp_pd(x.val[1], y.lo, _CMP_EQ_UQ)
			),
			_mm256_and_pd(
				_mm256_cmp_pd(x.val[2], _mm256_setzero_pd(), _CMP_EQ_UQ),
				_mm256_cmp_pd(x.val[3], _mm256_setzero_pd(), _CMP_EQ_UQ)
			)
		);
	}

	/**
	 * @brief _CMP_NEQ_UQ
	 */
	inline __m256d _mm256_cmpneq_pdx4_pdx2(__m256dx4 x, __m256dx2 y) {
		return _mm256_or_pd(
			_mm256_or_pd(
				_mm256_cmp_pd(x.val[0], y.hi, _CMP_NEQ_UQ),
				_mm256_cmp_pd(x.val[1], y.lo, _CMP_NEQ_UQ)
			),
			_mm256_or_pd(
				_mm256_cmp_pd(x.val[2], _mm256_setzero_pd(), _CMP_NEQ_UQ),
				_mm256_cmp_pd(x.val[3], _mm256_setzero_pd(), _CMP_NEQ_UQ)
			)
		);
	}

	/**
	 * @brief _CMP_ORD_Q
	 */
	inline __m256d _mm256_cmpord_pdx4_pdx2(__m256dx4 x, __m256dx2 y) {
		return _mm256_and_pd(
			_mm256_and_pd(
				_mm256_cmp_pd(x.val[0], y.hi, _CMP_ORD_Q),
				_mm256_cmp_pd(x.val[1], y.lo, _CMP_ORD_Q)
			),
			_mm256_and_pd(
				_mm256_cmp_pd(x.val[2], _mm256_setzero_pd(), _CMP_ORD_Q),
				_mm256_cmp_pd(x.val[3], _mm256_setzero_pd(), _CMP_ORD_Q)
			)
		);
	}

	/**
	 * @brief _CMP_UNORD_Q
	 */
	inline __m256d _mm256_cmpunord_pdx4_pdx2(__m256dx4 x, __m256dx2 y) {
		return _mm256_or_pd(
			_mm256_or_pd(
				_mm256_cmp_pd(x.val[0], y.hi, _CMP_UNORD_Q),
				_mm256_cmp_pd(x.val[1], y.lo, _CMP_UNORD_Q)
			),
			_mm256_or_pd(
				_mm256_cmp_pd(x.val[2], _mm256_setzero_pd(), _CMP_UNORD_Q),
				_mm256_cmp_pd(x.val[3], _mm256_setzero_pd(), _CMP_UNORD_Q)
			)
		);
	}

	/**
	 * @brief _CMP_LT_OQ
	 */
	inline __m256d _mm256_cmplt_pdx4_pdx2(__m256dx4 x, __m256dx2 y) {
		__m256d cmp_lt_0 = _mm256_cmp_pd(x.val[0], y.hi, _CMP_LT_OQ);
		__m256d cmp_eq_0 = _mm256_cmp_pd(x.val[0], y.hi, _CMP_EQ_OQ);
		__m256d cmp_lt_1 = _mm256_cmp_pd(x.val[1], y.lo, _CMP_LT_OQ);
		__m256d cmp_eq_1 = _mm256_cmp_pd(x.val[1], y.lo, _CMP_EQ_OQ);
		__m256d cmp_lt_2 = _mm256_cmp_pd(x.val[2], _mm256_setzero_pd(), _CMP_LT_OQ);
		__m256d cmp_eq_2 = _mm256_cmp_pd(x.val[2], _mm256_setzero_pd(), _CMP_EQ_OQ);
		__m256d cmp_lt_3 = _mm256_cmp_pd(x.val[3], _mm256_setzero_pd(), _CMP_LT_OQ);
		return _mm256_or_pd(cmp_lt_0, _mm256_and_pd(cmp_eq_0,
			_mm256_or_pd(cmp_lt_1, _mm256_and_pd(cmp_eq_1,
				_mm256_or_pd(cmp_lt_2, _mm256_and_pd(cmp_eq_2, cmp_lt_3))
			))
		));
	}

	/**
	 * @brief _CMP_LE_OQ
	 */
	inline __m256d _mm256_cmple_pdx4_pdx2(__m256dx4 x, __m256dx2 y) {
		__m256d cmp_lt_0 = _mm256_cmp_pd(x.val[0], y.hi, _CMP_LT_OQ);
		__m256d cmp_eq_0 = _mm256_cmp_pd(x.val[0], y.hi, _CMP_EQ_OQ);
		__m256d cmp_lt_1 = _mm256_cmp_pd(x.val[1], y.lo, _CMP_LT_OQ);
		__m256d cmp_eq_1 = _mm256_cmp_pd(x.val[1], y.lo, _CMP_EQ_OQ);
		__m256d cmp_lt_2 = _mm256_cmp_pd(x.val[2], _mm256_setzero_pd(), _CMP_LT_OQ);
		__m256d cmp_eq_2 = _mm256_cmp_pd(x.val[2], _mm256_setzero_pd(), _CMP_EQ_OQ);
		__m256d cmp_le_3 = _mm256_cmp_pd(x.val[3], _mm256_setzero_pd(), _CMP_LE_OQ);
		return _mm256_or_pd(cmp_lt_0, _mm256_and_pd(cmp_eq_0,
			_mm256_or_pd(cmp_lt_1, _mm256_and_pd(cmp_eq_1,
				_mm256_or_pd(cmp_lt_2, _mm256_and_pd(cmp_eq_2, cmp_le_3))
			))
		));
	}

	/**
	 * @brief _CMP_GT_OQ
	 */
	inline __m256d _mm256_cmpgt_pdx4_pdx2(__m256dx4 x, __m256dx2 y) {
		__m256d cmp_gt_0 = _mm256_cmp_pd(x.val[0], y.hi, _CMP_GT_OQ);
		__m256d cmp_eq_0 = _mm256_cmp_pd(x.val[0], y.hi, _CMP_EQ_OQ);
		__m256d cmp_gt_1 = _mm256_cmp_pd(x.val[1], y.lo, _CMP_GT_OQ);
		__m256d cmp_eq_1 = _mm256_cmp_pd(x.val[1], y.lo, _CMP_EQ_OQ);
		__m256d cmp_gt_2 = _mm256_cmp_pd(x.val[2], _mm256_setzero_pd(), _CMP_GT_OQ);
		__m256d cmp_eq_2 = _mm256_cmp_pd(x.val[2], _mm256_setzero_pd(), _CMP_EQ_OQ);
		__m256d cmp_gt_3 = _mm256_cmp_pd(x.val[3], _mm256_setzero_pd(), _CMP_GT_OQ);
		return _mm256_or_pd(cmp_gt_0, _mm256_and_pd(cmp_eq_0,
			_mm256_or_pd(cmp_gt_1, _mm256_and_pd(cmp_eq_1,
				_mm256_or_pd(cmp_gt_2, _mm256_and_pd(cmp_eq_2, cmp_gt_3))
			))
		));
	}

	/**
	 * @brief _CMP_GE_OQ
	 */
	inline __m256d _mm256_cmpge_pdx4_pdx2(__m256dx4 x, __m256dx2 y) {
		__m256d cmp_gt_0 = _mm256_cmp_pd(x.val[0], y.hi, _CMP_GT_OQ);
		__m256d cmp_eq_0 = _mm256_cmp_pd(x.val[0], y.hi, _CMP_EQ_OQ);
		__m256d cmp_gt_1 = _mm256_cmp_pd(x.val[1], y.lo, _CMP_GT_OQ);
		__m256d cmp_eq_1 = _mm256_cmp_pd(x.val[1], y.lo, _CMP_EQ_OQ);
		__m256d cmp_gt_2 = _mm256_cmp_pd(x.val[2], _mm256_setzero_pd(), _CMP_GT_OQ);
		__m256d cmp_eq_2 = _mm256_cmp_pd(x.val[2], _mm256_setzero_pd(), _CMP_EQ_OQ);
		__m256d cmp_ge_3 = _mm256_cmp_pd(x.val[3], _mm256_setzero_pd(), _CMP_GE_OQ);
		return _mm256_or_pd(cmp_gt_0, _mm256_and_pd(cmp_eq_0,
			_mm256_or_pd(cmp_gt_1, _mm256_and_pd(cmp_eq_1,
				_mm256_or_pd(cmp_gt_2, _mm256_and_pd(cmp_eq_2, cmp_ge_3))
			))
		));
	}

/* __m256dx2 compare __m256dx4 */

	/**
	 * @brief _CMP_EQ_UQ
	 */
	inline __m256d _mm256_cmpeq_pdx2_pdx4(__m256dx2 x, __m256dx4 y) {
		return _mm256_and_pd(
			_mm256_and_pd(
				_mm256_cmp_pd(x.hi, y.val[0], _CMP_EQ_UQ),
				_mm256_cmp_pd(x.lo, y.val[1], _CMP_EQ_UQ)
			),
			_mm256_and_pd(
				_mm256_cmp_pd(_mm256_setzero_pd(), y.val[2], _CMP_EQ_UQ),
				_mm256_cmp_pd(_mm256_setzero_pd(), y.val[3], _CMP_EQ_UQ)
			)
		);
	}

	/**
	 * @brief _CMP_NEQ_UQ
	 */
	inline __m256d _mm256_cmpneq_pdx2_pdx4(__m256dx2 x, __m256dx4 y) {
		return _mm256_or_pd(
			_mm256_or_pd(
				_mm256_cmp_pd(x.hi, y.val[0], _CMP_NEQ_UQ),
				_mm256_cmp_pd(x.lo, y.val[1], _CMP_NEQ_UQ)
			),
			_mm256_or_pd(
				_mm256_cmp_pd(_mm256_setzero_pd(), y.val[2], _CMP_NEQ_UQ),
				_mm256_cmp_pd(_mm256_setzero_pd(), y.val[3], _CMP_NEQ_UQ)
			)
		);
	}

	/**
	 * @brief _CMP_ORD_Q
	 */
	inline __m256d _mm256_cmpord_pdx2_pdx4(__m256dx2 x, __m256dx4 y) {
		return _mm256_and_pd(
			_mm256_and_pd(
				_mm256_cmp_pd(x.hi, y.val[0], _CMP_ORD_Q),
				_mm256_cmp_pd(x.lo, y.val[1], _CMP_ORD_Q)
			),
			_mm256_and_pd(
				_mm256_cmp_pd(_mm256_setzero_pd(), y.val[2], _CMP_ORD_Q),
				_mm256_cmp_pd(_mm256_setzero_pd(), y.val[3], _CMP_ORD_Q)
			)
		);
	}

	/**
	 * @brief _CMP_UNORD_Q
	 */
	inline __m256d _mm256_cmpunord_pdx2_pdx4(__m256dx2 x, __m256dx4 y) {
		return _mm256_or_pd(
			_mm256_or_pd(
				_mm256_cmp_pd(x.hi, y.val[0], _CMP_UNORD_Q),
				_mm256_cmp_pd(x.lo, y.val[1], _CMP_UNORD_Q)
			),
			_mm256_or_pd(
				_mm256_cmp_pd(_mm256_setzero_pd(), y.val[2], _CMP_UNORD_Q),
				_mm256_cmp_pd(_mm256_setzero_pd(), y.val[3], _CMP_UNORD_Q)
			)
		);
	}

	/**
	 * @brief _CMP_LT_OQ
	 */
	inline __m256d _mm256_cmplt_pdx2_pdx4(__m256dx2 x, __m256dx4 y) {
		__m256d cmp_lt_0 = _mm256_cmp_pd(x.hi, y.val[0], _CMP_LT_OQ);
		__m256d cmp_eq_0 = _mm256_cmp_pd(x.hi, y.val[0], _CMP_EQ_OQ);
		__m256d cmp_lt_1 = _mm256_cmp_pd(x.lo, y.val[1], _CMP_LT_OQ);
		__m256d cmp_eq_1 = _mm256_cmp_pd(x.lo, y.val[1], _CMP_EQ_OQ);
		__m256d cmp_lt_2 = _mm256_cmp_pd(_mm256_setzero_pd(), y.val[2], _CMP_LT_OQ);
		__m256d cmp_eq_2 = _mm256_cmp_pd(_mm256_setzero_pd(), y.val[2], _CMP_EQ_OQ);
		__m256d cmp_lt_3 = _mm256_cmp_pd(_mm256_setzero_pd(), y.val[3], _CMP_LT_OQ);
		return _mm256_or_pd(cmp_lt_0, _mm256_and_pd(cmp_eq_0,
			_mm256_or_pd(cmp_lt_1, _mm256_and_pd(cmp_eq_1,
				_mm256_or_pd(cmp_lt_2, _mm256_and_pd(cmp_eq_2, cmp_lt_3))
			))
		));
	}

	/**
	 * @brief _CMP_LE_OQ
	 */
	inline __m256d _mm256_cmple_pdx2_pdx4(__m256dx2 x, __m256dx4 y) {
		__m256d cmp_lt_0 = _mm256_cmp_pd(x.hi, y.val[0], _CMP_LT_OQ);
		__m256d cmp_eq_0 = _mm256_cmp_pd(x.hi, y.val[0], _CMP_EQ_OQ);
		__m256d cmp_lt_1 = _mm256_cmp_pd(x.lo, y.val[1], _CMP_LT_OQ);
		__m256d cmp_eq_1 = _mm256_cmp_pd(x.lo, y.val[1], _CMP_EQ_OQ);
		__m256d cmp_lt_2 = _mm256_cmp_pd(_mm256_setzero_pd(), y.val[2], _CMP_LT_OQ);
		__m256d cmp_eq_2 = _mm256_cmp_pd(_mm256_setzero_pd(), y.val[2], _CMP_EQ_OQ);
		__m256d cmp_le_3 = _mm256_cmp_pd(_mm256_setzero_pd(), y.val[3], _CMP_LE_OQ);
		return _mm256_or_pd(cmp_lt_0, _mm256_and_pd(cmp_eq_0,
			_mm256_or_pd(cmp_lt_1, _mm256_and_pd(cmp_eq_1,
				_mm256_or_pd(cmp_lt_2, _mm256_and_pd(cmp_eq_2, cmp_le_3))
			))
		));
	}

	/**
	 * @brief _CMP_GT_OQ
	 */
	inline __m256d _mm256_cmpgt_pdx2_pdx4(__m256dx2 x, __m256dx4 y) {
		__m256d cmp_gt_0 = _mm256_cmp_pd(x.hi, y.val[0], _CMP_GT_OQ);
		__m256d cmp_eq_0 = _mm256_cmp_pd(x.hi, y.val[0], _CMP_EQ_OQ);
		__m256d cmp_gt_1 = _mm256_cmp_pd(x.lo, y.val[1], _CMP_GT_OQ);
		__m256d cmp_eq_1 = _mm256_cmp_pd(x.lo, y.val[1], _CMP_EQ_OQ);
		__m256d cmp_gt_2 = _mm256_cmp_pd(_mm256_setzero_pd(), y.val[2], _CMP_GT_OQ);
		__m256d cmp_eq_2 = _mm256_cmp_pd(_mm256_setzero_pd(), y.val[2], _CMP_EQ_OQ);
		__m256d cmp_gt_3 = _mm256_cmp_pd(_mm256_setzero_pd(), y.val[3], _CMP_GT_OQ);
		return _mm256_or_pd(cmp_gt_0, _mm256_and_pd(cmp_eq_0,
			_mm256_or_pd(cmp_gt_1, _mm256_and_pd(cmp_eq_1,
				_mm256_or_pd(cmp_gt_2, _mm256_and_pd(cmp_eq_2, cmp_gt_3))
			))
		));
	}

	/**
	 * @brief _CMP_GE_OQ
	 */
	inline __m256d _mm256_cmpge_pdx2_pdx4(__m256dx2 x, __m256dx4 y) {
		__m256d cmp_gt_0 = _mm256_cmp_pd(x.hi, y.val[0], _CMP_GT_OQ);
		__m256d cmp_eq_0 = _mm256_cmp_pd(x.hi, y.val[0], _CMP_EQ_OQ);
		__m256d cmp_gt_1 = _mm256_cmp_pd(x.lo, y.val[1], _CMP_GT_OQ);
		__m256d cmp_eq_1 = _mm256_cmp_pd(x.lo, y.val[1], _CMP_EQ_OQ);
		__m256d cmp_gt_2 = _mm256_cmp_pd(_mm256_setzero_pd(), y.val[2], _CMP_GT_OQ);
		__m256d cmp_eq_2 = _mm256_cmp_pd(_mm256_setzero_pd(), y.val[2], _CMP_EQ_OQ);
		__m256d cmp_ge_3 = _mm256_cmp_pd(_mm256_setzero_pd(), y.val[3], _CMP_GE_OQ);
		return _mm256_or_pd(cmp_gt_0, _mm256_and_pd(cmp_eq_0,
			_mm256_or_pd(cmp_gt_1, _mm256_and_pd(cmp_eq_1,
				_mm256_or_pd(cmp_gt_2, _mm256_and_pd(cmp_eq_2, cmp_ge_3))
			))
		));
	}

/* __m256dx4 compare __m256d */

	/**
	 * @brief _CMP_EQ_UQ
	 */
	inline __m256d _mm256_cmpeq_pdx4_pd(__m256dx4 x, __m256d y) {
		return _mm256_and_pd(
			_mm256_and_pd(
				_mm256_cmp_pd(x.val[0], y, _CMP_EQ_UQ),
				_mm256_cmp_pd(x.val[1], _mm256_setzero_pd(), _CMP_EQ_UQ)
			),
			_mm256_and_pd(
				_mm256_cmp_pd(x.val[2], _mm256_setzero_pd(), _CMP_EQ_UQ),
				_mm256_cmp_pd(x.val[3], _mm256_setzero_pd(), _CMP_EQ_UQ)
			)
		);
	}

	/**
	 * @brief _CMP_NEQ_UQ
	 */
	inline __m256d _mm256_cmpneq_pdx4_pd(__m256dx4 x, __m256d y) {
		return _mm256_or_pd(
			_mm256_or_pd(
				_mm256_cmp_pd(x.val[0], y, _CMP_NEQ_UQ),
				_mm256_cmp_pd(x.val[1], _mm256_setzero_pd(), _CMP_NEQ_UQ)
			),
			_mm256_or_pd(
				_mm256_cmp_pd(x.val[2], _mm256_setzero_pd(), _CMP_NEQ_UQ),
				_mm256_cmp_pd(x.val[3], _mm256_setzero_pd(), _CMP_NEQ_UQ)
			)
		);
	}

	/**
	 * @brief _CMP_ORD_Q
	 */
	inline __m256d _mm256_cmpord_pdx4_pd(__m256dx4 x, __m256d y) {
		return _mm256_and_pd(
			_mm256_and_pd(
				_mm256_cmp_pd(x.val[0], y, _CMP_ORD_Q),
				_mm256_cmp_pd(x.val[1], _mm256_setzero_pd(), _CMP_ORD_Q)
			),
			_mm256_and_pd(
				_mm256_cmp_pd(x.val[2], _mm256_setzero_pd(), _CMP_ORD_Q),
				_mm256_cmp_pd(x.val[3], _mm256_setzero_pd(), _CMP_ORD_Q)
			)
		);
	}

	/**
	 * @brief _CMP_UNORD_Q
	 */
	inline __m256d _mm256_cmpunord_pdx4_pd(__m256dx4 x, __m256d y) {
		return _mm256_or_pd(
			_mm256_or_pd(
				_mm256_cmp_pd(x.val[0], y, _CMP_UNORD_Q),
				_mm256_cmp_pd(x.val[1], _mm256_setzero_pd(), _CMP_UNORD_Q)
			),
			_mm256_or_pd(
				_mm256_cmp_pd(x.val[2], _mm256_setzero_pd(), _CMP_UNORD_Q),
				_mm256_cmp_pd(x.val[3], _mm256_setzero_pd(), _CMP_UNORD_Q)
			)
		);
	}

	/**
	 * @brief _CMP_LT_OQ
	 */
	inline __m256d _mm256_cmplt_pdx4_pd(__m256dx4 x, __m256d y) {
		__m256d cmp_lt_0 = _mm256_cmp_pd(x.val[0], y, _CMP_LT_OQ);
		__m256d cmp_eq_0 = _mm256_cmp_pd(x.val[0], y, _CMP_EQ_OQ);
		__m256d cmp_lt_1 = _mm256_cmp_pd(x.val[1], _mm256_setzero_pd(), _CMP_LT_OQ);
		__m256d cmp_eq_1 = _mm256_cmp_pd(x.val[1], _mm256_setzero_pd(), _CMP_EQ_OQ);
		__m256d cmp_lt_2 = _mm256_cmp_pd(x.val[2], _mm256_setzero_pd(), _CMP_LT_OQ);
		__m256d cmp_eq_2 = _mm256_cmp_pd(x.val[2], _mm256_setzero_pd(), _CMP_EQ_OQ);
		__m256d cmp_lt_3 = _mm256_cmp_pd(x.val[3], _mm256_setzero_pd(), _CMP_LT_OQ);
		return _mm256_or_pd(cmp_lt_0, _mm256_and_pd(cmp_eq_0,
			_mm256_or_pd(cmp_lt_1, _mm256_and_pd(cmp_eq_1,
				_mm256_or_pd(cmp_lt_2, _mm256_and_pd(cmp_eq_2, cmp_lt_3))
			))
		));
	}

	/**
	 * @brief _CMP_LE_OQ
	 */
	inline __m256d _mm256_cmple_pdx4_pd(__m256dx4 x, __m256d y) {
		__m256d cmp_lt_0 = _mm256_cmp_pd(x.val[0], y, _CMP_LT_OQ);
		__m256d cmp_eq_0 = _mm256_cmp_pd(x.val[0], y, _CMP_EQ_OQ);
		__m256d cmp_lt_1 = _mm256_cmp_pd(x.val[1], _mm256_setzero_pd(), _CMP_LT_OQ);
		__m256d cmp_eq_1 = _mm256_cmp_pd(x.val[1], _mm256_setzero_pd(), _CMP_EQ_OQ);
		__m256d cmp_lt_2 = _mm256_cmp_pd(x.val[2], _mm256_setzero_pd(), _CMP_LT_OQ);
		__m256d cmp_eq_2 = _mm256_cmp_pd(x.val[2], _mm256_setzero_pd(), _CMP_EQ_OQ);
		__m256d cmp_le_3 = _mm256_cmp_pd(x.val[3], _mm256_setzero_pd(), _CMP_LE_OQ);
		return _mm256_or_pd(cmp_lt_0, _mm256_and_pd(cmp_eq_0,
			_mm256_or_pd(cmp_lt_1, _mm256_and_pd(cmp_eq_1,
				_mm256_or_pd(cmp_lt_2, _mm256_and_pd(cmp_eq_2, cmp_le_3))
			))
		));
	}

	/**
	 * @brief _CMP_GT_OQ
	 */
	inline __m256d _mm256_cmpgt_pdx4_pd(__m256dx4 x, __m256d y) {
		__m256d cmp_gt_0 = _mm256_cmp_pd(x.val[0], y, _CMP_GT_OQ);
		__m256d cmp_eq_0 = _mm256_cmp_pd(x.val[0], y, _CMP_EQ_OQ);
		__m256d cmp_gt_1 = _mm256_cmp_pd(x.val[1], _mm256_setzero_pd(), _CMP_GT_OQ);
		__m256d cmp_eq_1 = _mm256_cmp_pd(x.val[1], _mm256_setzero_pd(), _CMP_EQ_OQ);
		__m256d cmp_gt_2 = _mm256_cmp_pd(x.val[2], _mm256_setzero_pd(), _CMP_GT_OQ);
		__m256d cmp_eq_2 = _mm256_cmp_pd(x.val[2], _mm256_setzero_pd(), _CMP_EQ_OQ);
		__m256d cmp_gt_3 = _mm256_cmp_pd(x.val[3], _mm256_setzero_pd(), _CMP_GT_OQ);
		return _mm256_or_pd(cmp_gt_0, _mm256_and_pd(cmp_eq_0,
			_mm256_or_pd(cmp_gt_1, _mm256_and_pd(cmp_eq_1,
				_mm256_or_pd(cmp_gt_2, _mm256_and_pd(cmp_eq_2, cmp_gt_3))
			))
		));
	}

	/**
	 * @brief _CMP_GE_OQ
	 */
	inline __m256d _mm256_cmpge_pdx4_pd(__m256dx4 x, __m256d y) {
		__m256d cmp_gt_0 = _mm256_cmp_pd(x.val[0], y, _CMP_GT_OQ);
		__m256d cmp_eq_0 = _mm256_cmp_pd(x.val[0], y, _CMP_EQ_OQ);
		__m256d cmp_gt_1 = _mm256_cmp_pd(x.val[1], _mm256_setzero_pd(), _CMP_GT_OQ);
		__m256d cmp_eq_1 = _mm256_cmp_pd(x.val[1], _mm256_setzero_pd(), _CMP_EQ_OQ);
		__m256d cmp_gt_2 = _mm256_cmp_pd(x.val[2], _mm256_setzero_pd(), _CMP_GT_OQ);
		__m256d cmp_eq_2 = _mm256_cmp_pd(x.val[2], _mm256_setzero_pd(), _CMP_EQ_OQ);
		__m256d cmp_ge_3 = _mm256_cmp_pd(x.val[3], _mm256_setzero_pd(), _CMP_GE_OQ);
		return _mm256_or_pd(cmp_gt_0, _mm256_and_pd(cmp_eq_0,
			_mm256_or_pd(cmp_gt_1, _mm256_and_pd(cmp_eq_1,
				_mm256_or_pd(cmp_gt_2, _mm256_and_pd(cmp_eq_2, cmp_ge_3))
			))
		));
	}

/* __m256d compare __m256dx4 */

	/**
	 * @brief _CMP_EQ_UQ
	 */
	inline __m256d _mm256_cmpeq_pd_pdx4(__m256d x, __m256dx4 y) {
		return _mm256_and_pd(
			_mm256_and_pd(
				_mm256_cmp_pd(x, y.val[0], _CMP_EQ_UQ),
				_mm256_cmp_pd(_mm256_setzero_pd(), y.val[1], _CMP_EQ_UQ)
			),
			_mm256_and_pd(
				_mm256_cmp_pd(_mm256_setzero_pd(), y.val[2], _CMP_EQ_UQ),
				_mm256_cmp_pd(_mm256_setzero_pd(), y.val[3], _CMP_EQ_UQ)
			)
		);
	}

	/**
	 * @brief _CMP_NEQ_UQ
	 */
	inline __m256d _mm256_cmpneq_pd_pdx4(__m256d x, __m256dx4 y) {
		return _mm256_or_pd(
			_mm256_or_pd(
				_mm256_cmp_pd(x, y.val[0], _CMP_NEQ_UQ),
				_mm256_cmp_pd(_mm256_setzero_pd(), y.val[1], _CMP_NEQ_UQ)
			),
			_mm256_or_pd(
				_mm256_cmp_pd(_mm256_setzero_pd(), y.val[2], _CMP_NEQ_UQ),
				_mm256_cmp_pd(_mm256_setzero_pd(), y.val[3], _CMP_NEQ_UQ)
			)
		);
	}

	/**
	 * @brief _CMP_ORD_Q
	 */
	inline __m256d _mm256_cmpord_pd_pdx4(__m256d x, __m256dx4 y) {
		return _mm256_and_pd(
			_mm256_and_pd(
				_mm256_cmp_pd(x, y.val[0], _CMP_ORD_Q),
				_mm256_cmp_pd(_mm256_setzero_pd(), y.val[1], _CMP_ORD_Q)
			),
			_mm256_and_pd(
				_mm256_cmp_pd(_mm256_setzero_pd(), y.val[2], _CMP_ORD_Q),
				_mm256_cmp_pd(_mm256_setzero_pd(), y.val[3], _CMP_ORD_Q)
			)
		);
	}

	/**
	 * @brief _CMP_UNORD_Q
	 */
	inline __m256d _mm256_cmpunord_pd_pdx4(__m256d x, __m256dx4 y) {
		return _mm256_or_pd(
			_mm256_or_pd(
				_mm256_cmp_pd(x, y.val[0], _CMP_UNORD_Q),
				_mm256_cmp_pd(_mm256_setzero_pd(), y.val[1], _CMP_UNORD_Q)
			),
			_mm256_or_pd(
				_mm256_cmp_pd(_mm256_setzero_pd(), y.val[2], _CMP_UNORD_Q),
				_mm256_cmp_pd(_mm256_setzero_pd(), y.val[3], _CMP_UNORD_Q)
			)
		);
	}

	/**
	 * @brief _CMP_LT_OQ
	 */
	inline __m256d _mm256_cmplt_pd_pdx4(__m256d x, __m256dx4 y) {
		__m256d cmp_lt_0 = _mm256_cmp_pd(x, y.val[0], _CMP_LT_OQ);
		__m256d cmp_eq_0 = _mm256_cmp_pd(x, y.val[0], _CMP_EQ_OQ);
		__m256d cmp_lt_1 = _mm256_cmp_pd(_mm256_setzero_pd(), y.val[1], _CMP_LT_OQ);
		__m256d cmp_eq_1 = _mm256_cmp_pd(_mm256_setzero_pd(), y.val[1], _CMP_EQ_OQ);
		__m256d cmp_lt_2 = _mm256_cmp_pd(_mm256_setzero_pd(), y.val[2], _CMP_LT_OQ);
		__m256d cmp_eq_2 = _mm256_cmp_pd(_mm256_setzero_pd(), y.val[2], _CMP_EQ_OQ);
		__m256d cmp_lt_3 = _mm256_cmp_pd(_mm256_setzero_pd(), y.val[3], _CMP_LT_OQ);
		return _mm256_or_pd(cmp_lt_0, _mm256_and_pd(cmp_eq_0,
			_mm256_or_pd(cmp_lt_1, _mm256_and_pd(cmp_eq_1,
				_mm256_or_pd(cmp_lt_2, _mm256_and_pd(cmp_eq_2, cmp_lt_3))
			))
		));
	}

	/**
	 * @brief _CMP_LE_OQ
	 */
	inline __m256d _mm256_cmple_pd_pdx4(__m256d x, __m256dx4 y) {
		__m256d cmp_lt_0 = _mm256_cmp_pd(x, y.val[0], _CMP_LT_OQ);
		__m256d cmp_eq_0 = _mm256_cmp_pd(x, y.val[0], _CMP_EQ_OQ);
		__m256d cmp_lt_1 = _mm256_cmp_pd(_mm256_setzero_pd(), y.val[1], _CMP_LT_OQ);
		__m256d cmp_eq_1 = _mm256_cmp_pd(_mm256_setzero_pd(), y.val[1], _CMP_EQ_OQ);
		__m256d cmp_lt_2 = _mm256_cmp_pd(_mm256_setzero_pd(), y.val[2], _CMP_LT_OQ);
		__m256d cmp_eq_2 = _mm256_cmp_pd(_mm256_setzero_pd(), y.val[2], _CMP_EQ_OQ);
		__m256d cmp_le_3 = _mm256_cmp_pd(_mm256_setzero_pd(), y.val[3], _CMP_LE_OQ);
		return _mm256_or_pd(cmp_lt_0, _mm256_and_pd(cmp_eq_0,
			_mm256_or_pd(cmp_lt_1, _mm256_and_pd(cmp_eq_1,
				_mm256_or_pd(cmp_lt_2, _mm256_and_pd(cmp_eq_2, cmp_le_3))
			))
		));
	}

	/**
	 * @brief _CMP_GT_OQ
	 */
	inline __m256d _mm256_cmpgt_pd_pdx4(__m256d x, __m256dx4 y) {
		__m256d cmp_gt_0 = _mm256_cmp_pd(x, y.val[0], _CMP_GT_OQ);
		__m256d cmp_eq_0 = _mm256_cmp_pd(x, y.val[0], _CMP_EQ_OQ);
		__m256d cmp_gt_1 = _mm256_cmp_pd(_mm256_setzero_pd(), y.val[1], _CMP_GT_OQ);
		__m256d cmp_eq_1 = _mm256_cmp_pd(_mm256_setzero_pd(), y.val[1], _CMP_EQ_OQ);
		__m256d cmp_gt_2 = _mm256_cmp_pd(_mm256_setzero_pd(), y.val[2], _CMP_GT_OQ);
		__m256d cmp_eq_2 = _mm256_cmp_pd(_mm256_setzero_pd(), y.val[2], _CMP_EQ_OQ);
		__m256d cmp_gt_3 = _mm256_cmp_pd(_mm256_setzero_pd(), y.val[3], _CMP_GT_OQ);
		return _mm256_or_pd(cmp_gt_0, _mm256_and_pd(cmp_eq_0,
			_mm256_or_pd(cmp_gt_1, _mm256_and_pd(cmp_eq_1,
				_mm256_or_pd(cmp_gt_2, _mm256_and_pd(cmp_eq_2, cmp_gt_3))
			))
		));
	}

	/**
	 * @brief _CMP_GE_OQ
	 */
	inline __m256d _mm256_cmpge_pd_pdx4(__m256d x, __m256dx4 y) {
		__m256d cmp_gt_0 = _mm256_cmp_pd(x, y.val[0], _CMP_GT_OQ);
		__m256d cmp_eq_0 = _mm256_cmp_pd(x, y.val[0], _CMP_EQ_OQ);
		__m256d cmp_gt_1 = _mm256_cmp_pd(_mm256_setzero_pd(), y.val[1], _CMP_GT_OQ);
		__m256d cmp_eq_1 = _mm256_cmp_pd(_mm256_setzero_pd(), y.val[1], _CMP_EQ_OQ);
		__m256d cmp_gt_2 = _mm256_cmp_pd(_mm256_setzero_pd(), y.val[2], _CMP_GT_OQ);
		__m256d cmp_eq_2 = _mm256_cmp_pd(_mm256_setzero_pd(), y.val[2], _CMP_EQ_OQ);
		__m256d cmp_ge_3 = _mm256_cmp_pd(_mm256_setzero_pd(), y.val[3], _CMP_GE_OQ);
		return _mm256_or_pd(cmp_gt_0, _mm256_and_pd(cmp_eq_0,
			_mm256_or_pd(cmp_gt_1, _mm256_and_pd(cmp_eq_1,
				_mm256_or_pd(cmp_gt_2, _mm256_and_pd(cmp_eq_2, cmp_ge_3))
			))
		));
	}

//------------------------------------------------------------------------------
// __m256dx4 full comparison functions
//------------------------------------------------------------------------------

/* __m256dx4 compare __m256dx4 */

	/**
	 * @brief _CMP_EQ_UQ
	 */
	inline __m256dx4 _mm256x4_cmpeq_pdx4(__m256dx4 x, __m256dx4 y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmpeq_pdx4(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_NEQ_UQ
	 */
	inline __m256dx4 _mm256x4_cmpneq_pdx4(__m256dx4 x, __m256dx4 y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmpneq_pdx4(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_ORD_Q
	 */
	inline __m256dx4 _mm256x4_cmpord_pdx4(__m256dx4 x, __m256dx4 y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmpord_pdx4(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_UNORD_Q
	 */
	inline __m256dx4 _mm256x4_cmpunord_pdx4(__m256dx4 x, __m256dx4 y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmpunord_pdx4(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_LT_OQ
	 */
	inline __m256dx4 _mm256x4_cmplt_pdx4(__m256dx4 x, __m256dx4 y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmplt_pdx4(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_LE_OQ
	 */
	inline __m256dx4 _mm256x4_cmple_pdx4(__m256dx4 x, __m256dx4 y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmple_pdx4(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_GT_OQ
	 */
	inline __m256dx4 _mm256x4_cmpgt_pdx4(__m256dx4 x, __m256dx4 y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmpgt_pdx4(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_GE_OQ
	 */
	inline __m256dx4 _mm256x4_cmpge_pdx4(__m256dx4 x, __m256dx4 y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmpge_pdx4(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}

/* __m256dx4 compare __m256dx2 */

	/**
	 * @brief _CMP_EQ_UQ
	 */
	inline __m256dx4 _mm256x4_cmpeq_pdx4_pdx2(__m256dx4 x, __m256dx2 y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmpeq_pdx4_pdx2(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_NEQ_UQ
	 */
	inline __m256dx4 _mm256x4_cmpneq_pdx4_pdx2(__m256dx4 x, __m256dx2 y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmpneq_pdx4_pdx2(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_ORD_Q
	 */
	inline __m256dx4 _mm256x4_cmpord_pdx4_pdx2(__m256dx4 x, __m256dx2 y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmpord_pdx4_pdx2(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_UNORD_Q
	 */
	inline __m256dx4 _mm256x4_cmpunord_pdx4_pdx2(__m256dx4 x, __m256dx2 y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmpunord_pdx4_pdx2(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_LT_OQ
	 */
	inline __m256dx4 _mm256x4_cmplt_pdx4_pdx2(__m256dx4 x, __m256dx2 y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmplt_pdx4_pdx2(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_LE_OQ
	 */
	inline __m256dx4 _mm256x4_cmple_pdx4_pdx2(__m256dx4 x, __m256dx2 y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmple_pdx4_pdx2(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_GT_OQ
	 */
	inline __m256dx4 _mm256x4_cmpgt_pdx4_pdx2(__m256dx4 x, __m256dx2 y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmpgt_pdx4_pdx2(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_GE_OQ
	 */
	inline __m256dx4 _mm256x4_cmpge_pdx4_pdx2(__m256dx4 x, __m256dx2 y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmpge_pdx4_pdx2(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}

/* __m256dx2 compare __m256dx4 */

	/**
	 * @brief _CMP_EQ_UQ
	 */
	inline __m256dx4 _mm256x4_cmpeq_pdx2_pdx4(__m256dx2 x, __m256dx4 y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmpeq_pdx2_pdx4(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_NEQ_UQ
	 */
	inline __m256dx4 _mm256x4_cmpneq_pdx2_pdx4(__m256dx2 x, __m256dx4 y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmpneq_pdx2_pdx4(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_ORD_Q
	 */
	inline __m256dx4 _mm256x4_cmpord_pdx2_pdx4(__m256dx2 x, __m256dx4 y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmpord_pdx2_pdx4(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_UNORD_Q
	 */
	inline __m256dx4 _mm256x4_cmpunord_pdx2_pdx4(__m256dx2 x, __m256dx4 y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmpunord_pdx2_pdx4(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_LT_OQ
	 */
	inline __m256dx4 _mm256x4_cmplt_pdx2_pdx4(__m256dx2 x, __m256dx4 y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmplt_pdx2_pdx4(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_LE_OQ
	 */
	inline __m256dx4 _mm256x4_cmple_pdx2_pdx4(__m256dx2 x, __m256dx4 y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmple_pdx2_pdx4(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_GT_OQ
	 */
	inline __m256dx4 _mm256x4_cmpgt_pdx2_pdx4(__m256dx2 x, __m256dx4 y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmpgt_pdx2_pdx4(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_GE_OQ
	 */
	inline __m256dx4 _mm256x4_cmpge_pdx2_pdx4(__m256dx2 x, __m256dx4 y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmpge_pdx2_pdx4(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}

/* __m256dx4 compare __m256d */

	/**
	 * @brief _CMP_EQ_UQ
	 */
	inline __m256dx4 _mm256x4_cmpeq_pdx4_pd(__m256dx4 x, __m256d y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmpeq_pdx4_pd(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_NEQ_UQ
	 */
	inline __m256dx4 _mm256x4_cmpneq_pdx4_pd(__m256dx4 x, __m256d y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmpneq_pdx4_pd(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_ORD_Q
	 */
	inline __m256dx4 _mm256x4_cmpord_pdx4_pd(__m256dx4 x, __m256d y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmpord_pdx4_pd(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_UNORD_Q
	 */
	inline __m256dx4 _mm256x4_cmpunord_pdx4_pd(__m256dx4 x, __m256d y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmpunord_pdx4_pd(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_LT_OQ
	 */
	inline __m256dx4 _mm256x4_cmplt_pdx4_pd(__m256dx4 x, __m256d y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmplt_pdx4_pd(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_LE_OQ
	 */
	inline __m256dx4 _mm256x4_cmple_pdx4_pd(__m256dx4 x, __m256d y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmple_pdx4_pd(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_GT_OQ
	 */
	inline __m256dx4 _mm256x4_cmpgt_pdx4_pd(__m256dx4 x, __m256d y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmpgt_pdx4_pd(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_GE_OQ
	 */
	inline __m256dx4 _mm256x4_cmpge_pdx4_pd(__m256dx4 x, __m256d y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmpge_pdx4_pd(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}

/* __m256d compare __m256dx4 */

	/**
	 * @brief _CMP_EQ_UQ
	 */
	inline __m256dx4 _mm256x4_cmpeq_pd_pdx4(__m256d x, __m256dx4 y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmpeq_pd_pdx4(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_NEQ_UQ
	 */
	inline __m256dx4 _mm256x4_cmpneq_pd_pdx4(__m256d x, __m256dx4 y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmpneq_pd_pdx4(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_ORD_Q
	 */
	inline __m256dx4 _mm256x4_cmpord_pd_pdx4(__m256d x, __m256dx4 y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmpord_pd_pdx4(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_UNORD_Q
	 */
	inline __m256dx4 _mm256x4_cmpunord_pd_pdx4(__m256d x, __m256dx4 y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmpunord_pd_pdx4(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_LT_OQ
	 */
	inline __m256dx4 _mm256x4_cmplt_pd_pdx4(__m256d x, __m256dx4 y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmplt_pd_pdx4(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_LE_OQ
	 */
	inline __m256dx4 _mm256x4_cmple_pd_pdx4(__m256d x, __m256dx4 y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmple_pd_pdx4(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_GT_OQ
	 */
	inline __m256dx4 _mm256x4_cmpgt_pd_pdx4(__m256d x, __m256dx4 y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmpgt_pd_pdx4(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_GE_OQ
	 */
	inline __m256dx4 _mm256x4_cmpge_pd_pdx4(__m256d x, __m256dx4 y) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmpge_pd_pdx4(x, y);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}

//------------------------------------------------------------------------------
// __m256dx4 compare to zero functions
//------------------------------------------------------------------------------

/* reduced comparison */

	/**
	 * @brief _CMP_EQ_UQ
	 * @note Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero.
	 */
	inline __m256d _mm256_cmpeq_zero_pdx4(__m256dx4 x) {
		return _mm256_cmp_pd(x.val[0], _mm256_setzero_pd(), _CMP_EQ_UQ);
	}
	/**
	 * @brief _CMP_NEQ_UQ
	 * @note Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero.
	 */
	inline __m256d _mm256_cmpneq_zero_pdx4(__m256dx4 x) {
		return _mm256_cmp_pd(x.val[0], _mm256_setzero_pd(), _CMP_NEQ_UQ);
	}
	/**
	 * @brief _CMP_LT_OQ
	 * @note Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero.
	 */
	inline __m256d _mm256_cmplt_zero_pdx4(__m256dx4 x) {
		return _mm256_cmp_pd(x.val[0], _mm256_setzero_pd(), _CMP_LT_OQ);
	}
	/**
	 * @brief _CMP_LE_OQ
	 * @note Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero.
	 */
	inline __m256d _mm256_cmple_zero_pdx4(__m256dx4 x) {
		return _mm256_cmp_pd(x.val[0], _mm256_setzero_pd(), _CMP_LE_OQ);
	}
	/**
	 * @brief _CMP_GT_OQ
	 * @note Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero.
	 */
	inline __m256d _mm256_cmpgt_zero_pdx4(__m256dx4 x) {
		return _mm256_cmp_pd(x.val[0], _mm256_setzero_pd(), _CMP_GT_OQ);
	}
	/**
	 * @brief _CMP_GE_OQ
	 * @note Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero.
	 */
	inline __m256d _mm256_cmpge_zero_pdx4(__m256dx4 x) {
		return _mm256_cmp_pd(x.val[0], _mm256_setzero_pd(), _CMP_GE_OQ);
	}

/* full comparison */

	/**
	 * @brief _CMP_EQ_UQ
	 * @note Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero.
	 */
	inline __m256dx4 _mm256x4_cmpeq_zero_pdx4(__m256dx4 x) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmpeq_zero_pdx4(x);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_NEQ_UQ
	 * @note Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero.
	 * @note Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero.
	 */
	inline __m256dx4 _mm256x4_cmpneq_zero_pdx4(__m256dx4 x) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmpneq_zero_pdx4(x);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_LT_OQ
	 * @note Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero.
	 */
	inline __m256dx4 _mm256x4_cmplt_zero_pdx4(__m256dx4 x) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmplt_zero_pdx4(x);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_LE_OQ
	 * @note Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero.
	 */
	inline __m256dx4 _mm256x4_cmple_zero_pdx4(__m256dx4 x) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmple_zero_pdx4(x);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_GT_OQ
	 * @note Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero.
	 */
	inline __m256dx4 _mm256x4_cmpgt_zero_pdx4(__m256dx4 x) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmpgt_zero_pdx4(x);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}
	/**
	 * @brief _CMP_GE_OQ
	 * @note Assumes that if x.val[0] is zero then x.val[1 - 3] are also zero.
	 */
	inline __m256dx4 _mm256x4_cmpge_zero_pdx4(__m256dx4 x) {
		__m256dx4 ret;
		ret.val[0] = _mm256_cmpge_zero_pdx4(x);
		ret.val[1] = ret.val[0];
		ret.val[2] = ret.val[0];
		ret.val[3] = ret.val[0];
		return ret;
	}

//------------------------------------------------------------------------------
// __m256dx4 qd_real functions
//------------------------------------------------------------------------------

/** 
 * @author Taken and/or modified from libQD which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */

/** @brief Computes fl(x + y) and err(x + y).  Assumes |x| >= |y|. */
inline __m256d _mm256_quick_two_sum_pd(const __m256d x, const __m256d y, __m256d* __M256DX4_RESTRICT const err) {
	__m256d s = _mm256_add_pd(x, y);
	*err = _mm256_sub_pd(y, _mm256_sub_pd(s, x));
	return s;
}

/** @brief Computes fl(x - y) and err(x - y).  Assumes |x| >= |y|. */
inline __m256d _mm256_quick_two_diff_pd(const __m256d x, const __m256d y, __m256d* __M256DX4_RESTRICT const err) {
	__m256d s = _mm256_sub_pd(x, y);
	*err = _mm256_sub_pd(y, _mm256_sub_pd(s, x));
	return s;
}

/** @brief Computes fl(x + y) and err(x + y). */
inline __m256d _mm256_two_sum_pd(const __m256d x, const __m256d y, __m256d* __M256DX4_RESTRICT const err) {
	__m256d s = _mm256_add_pd(x, y);
	__m256d bb = _mm256_sub_pd(s, x);
	*err = _mm256_add_pd(_mm256_sub_pd(x, _mm256_sub_pd(s, bb)), _mm256_sub_pd(y, bb));
	return s;
}

/** @brief Computes fl(x - y) and err(x - y). */
inline __m256d _mm256_two_diff_pd(const __m256d x, const __m256d y, __m256d* __M256DX4_RESTRICT const err) {
	__m256d s = _mm256_sub_pd(x, y);
	__m256d bb = _mm256_sub_pd(s, x);
	*err = _mm256_sub_pd(_mm256_sub_pd(x, _mm256_sub_pd(s, bb)), _mm256_add_pd(y, bb));
	return s;
}

/** @brief Computes fl(x * y) and err(x * y). */
inline __m256d _mm256_two_prod_pd(const __m256d x, const __m256d y, __m256d* __M256DX4_RESTRICT const err) {
	__m256d p = _mm256_mul_pd(x, y);
	__m256dx2 a = _mm256x2_dekker_split_pd(x);
	__m256dx2 b = _mm256x2_dekker_split_pd(y);
	*err = _mm256_add_pd((_mm256_add_pd(
		_mm256_add_pd(_mm256_sub_pd(_mm256_mul_pd(a.hi, b.hi), p), _mm256_mul_pd(a.hi, b.lo)),
		_mm256_mul_pd(a.lo, b.hi)
	)), _mm256_mul_pd(a.lo, b.lo));
	return p;
}

/** @brief Computes fl(x * x) and err(x * x). Faster than _mm256_two_prod_pd(x, x, err) */
inline __m256d _mm256_two_sqr_pd(const __m256d x, __m256d* __M256DX4_RESTRICT const err) {
	__m256d q = _mm256_mul_pd(x, x);
	__m256dx2 a = _mm256x2_dekker_split_pd(x);
	*err = _mm256_add_pd(_mm256_add_pd(
		_mm256_sub_pd(_mm256_mul_pd(a.hi, a.hi), q),
		_mm256_mul_pd(_mm256_set1_pd(2.0), _mm256_mul_pd(a.hi, a.lo))
	), _mm256_mul_pd(a.lo, a.lo));
	return q;
}

/** 
 * @brief Adds `c` to the dd-pair `(a, b)`. If the result does not fit in two
 * doubles, then the sum is output into `s` and `(a, b)` contains the
 * remainder. Otherwise `s` is zero and `(a, b)` contains the sum.
 */
inline __m256d _mm256_quick_three_accum_pd(
	__m256d* __M256DX4_RESTRICT const a,
	__m256d* __M256DX4_RESTRICT const b,
	const __m256d c
) {
	__m256d s;
	__m256d za, zb; // bool

	s = _mm256_two_sum_pd(*b, c, b);
	s = _mm256_two_sum_pd(*a, s, a);

	za = _mm256_cmp_pd(*a, _mm256_setzero_pd(), _CMP_NEQ_UQ);
	zb = _mm256_cmp_pd(*b, _mm256_setzero_pd(), _CMP_NEQ_UQ);

	*b = _mm256_blendv_pd(*a, *b, zb);
	__m256d cmp_ret = _mm256_and_pd(za, zb);
	*a = _mm256_blendv_pd(s, *a, cmp_ret);
	return _mm256_blendv_pd(_mm256_setzero_pd(), s, cmp_ret);
}

inline void _mm256_three_sum_pd(
	__m256d* __M256DX4_RESTRICT const a,
	__m256d* __M256DX4_RESTRICT const b,
	__m256d* __M256DX4_RESTRICT const c
) {
	__m256d t1, t2, t3;
	t1 = _mm256_two_sum_pd(*a, *b, &t2);
	*a = _mm256_two_sum_pd(*c, t1, &t3);
	*b = _mm256_two_sum_pd(t2, t3, c  );
}

inline void _mm256_three_sum2_pd(
	__m256d* __M256DX4_RESTRICT const a,
	__m256d* __M256DX4_RESTRICT const b,
	__m256d* __M256DX4_RESTRICT const c
) {
	__m256d t1, t2, t3;
	t1 = _mm256_two_sum_pd(*a, *b, &t2);
	*a = _mm256_two_sum_pd(*c, t1, &t3);
	*b = _mm256_add_pd(t2, t3);
}

//------------------------------------------------------------------------------
// __m256dx4 qd_real renormalization
//------------------------------------------------------------------------------

inline void _mm256x4_quick_renorm_pdx4(__m256dx4* __M256DX4_RESTRICT const x) {
	__m256d t0, t1, t2;
	__m256d s;
	s         = x->val[3];
	s         = _mm256_quick_two_sum_pd(x->val[2], s, &t2);
	s         = _mm256_quick_two_sum_pd(x->val[1], s, &t1);
	x->val[0] = _mm256_quick_two_sum_pd(x->val[0], s, &t0);

	s         = _mm256_quick_two_sum_pd(t1, t2, &t1);
	x->val[1] = _mm256_quick_two_sum_pd(t0, s , &t0);
	x->val[2] = _mm256_quick_two_sum_pd(t0, t1, &t0);
	x->val[3] = t0;
}

/**
 * @brief Calls _mm256x4_quick_renorm_pdx4
 * @remarks This function has a lot of branching for SIMD
 */
inline void _mm256x4_renorm_pdx4(__m256dx4* __M256DX4_RESTRICT const x) {
	_mm256x4_quick_renorm_pdx4(x);
	#if 0
	__m256d s0, s1, s2 = 0.0, s3 = 0.0;

	// if (isinf(x->val[0])) {
	// 	return;
	// }

	s0 = _mm256_quick_two_sum_pd(x->val[2], x->val[3], &x->val[3]);
	s0 = _mm256_quick_two_sum_pd(x->val[1], s0, &x->val[2]);
	x->val[0] = _mm256_quick_two_sum_pd(x->val[0], s0, &x->val[1]);

	s0 = x->val[0];
	s1 = x->val[1];



	if (s1 != 0.0) {
		s1 = _mm256_quick_two_sum_pd(s1, x->val[2], &s2);
		if (s2 != 0.0) {
			s2 = _mm256_quick_two_sum_pd(s2, x->val[3], &s3);
		} else {
			s1 = _mm256_quick_two_sum_pd(s1, x->val[3], &s2);
		}
	} else {
		s0 = _mm256_quick_two_sum_pd(s0, x->val[2], &s1);
		if (s1 != 0.0) {
			s1 = _mm256_quick_two_sum_pd(s1, x->val[3], &s2);
		} else {
			s0 = _mm256_quick_two_sum_pd(s0, x->val[3], &s1);
		}
	}

	x->val[0] = s0;
	x->val[1] = s1;
	x->val[2] = s2;
	x->val[3] = s3;
	#endif
}

inline void _mm256x4_quick_renorm_err_pdx4(
	__m256dx4* __M256DX4_RESTRICT const x, __m256d* __M256DX4_RESTRICT const err
) {
	__m256d t0, t1, t2, t3;
	__m256d s;
	s         = _mm256_quick_two_sum_pd(x->val[3], *err, &t3);
	s         = _mm256_quick_two_sum_pd(x->val[2], s   , &t2);
	s         = _mm256_quick_two_sum_pd(x->val[1], s   , &t1);
	x->val[0] = _mm256_quick_two_sum_pd(x->val[0], s   , &t0);

	s         = _mm256_quick_two_sum_pd(t2, t3, &t2);
	s         = _mm256_quick_two_sum_pd(t1, s , &t1);
	x->val[1] = _mm256_quick_two_sum_pd(t0, s , &t0);

	s         = _mm256_quick_two_sum_pd(t1, t2, &t1);
	x->val[2] = _mm256_quick_two_sum_pd(t0, s , &t0);
	
	x->val[3] = _mm256_add_pd(t0, t1);
}

/**
 * @brief Calls _mm256x4_quick_renorm_err_pdx4
 * @remarks This function has a lot of branching for SIMD
 */
inline void _mm256x4_renorm_err_pdx4(
	__m256dx4* __M256DX4_RESTRICT const x,
	__m256d* __M256DX4_RESTRICT const err
) {
	_mm256x4_quick_renorm_err_pdx4(x, err);
	#if 0
	__m256d s0, s1, s2 = 0.0, s3 = 0.0;

	if (isinf(x->val[0])) {
		return;
	}

	s0        = _mm256_quick_two_sum_pd(x->val[3], *err, err       );
	s0        = _mm256_quick_two_sum_pd(x->val[2], s0  , &x->val[3]);
	s0        = _mm256_quick_two_sum_pd(x->val[1], s0  , &x->val[2]);
	x->val[0] = _mm256_quick_two_sum_pd(x->val[0], s0  , &x->val[1]);

	s0 = x->val[0];
	s1 = x->val[1];

	if (s1 != 0.0) {
		s1 = _mm256_quick_two_sum_pd(s1, x->val[2], &s2);
		if (s2 != 0.0) {
		s2 = _mm256_quick_two_sum_pd(s2, x->val[3], &s3);
			if (s3 != 0.0) {
				s3 += *err;
			} else {
				s2 = _mm256_quick_two_sum_pd(s2, *err, &s3);
			}
		} else {
		s1 = _mm256_quick_two_sum_pd(s1, x->val[3], &s2);
			if (s2 != 0.0) {
				s2 = _mm256_quick_two_sum_pd(s2, *err, &s3);
			} else {
				s1 = _mm256_quick_two_sum_pd(s1, *err, &s2);
			}
		}
	} else {
		s0 = _mm256_quick_two_sum_pd(s0, x->val[2], &s1);
		if (s1 != 0.0) {
		s1 = _mm256_quick_two_sum_pd(s1, x->val[3], &s2);
			if (s2 != 0.0) {
				s2 = _mm256_quick_two_sum_pd(s2, *err, &s3);
			} else {
				s1 = _mm256_quick_two_sum_pd(s1, *err, &s2);
			}
		} else {
		s0 = _mm256_quick_two_sum_pd(s0, x->val[3], &s1);
			if (s1 != 0.0) {
				s1 = _mm256_quick_two_sum_pd(s1, *err, &s2);
			} else {
				s0 = _mm256_quick_two_sum_pd(s0, *err, &s1);
			}
		}
	}

	x->val[0] = s0;
	x->val[1] = s1;
	x->val[2] = s2;
	x->val[3] = s3;
	#endif
}

//------------------------------------------------------------------------------
// __m256dx4 Arithmetic
//------------------------------------------------------------------------------

/* Negation */

/**
 * @brief Negates a __m256dx4 value (multiplies by -1.0)
 */
inline __m256dx4 _mm256x4_negate_pdx4(__m256dx4 x) {
	x.val[0] = _mm256_xor_pd(
		x.val[0],
		_mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x8000000000000000))
	);
	x.val[1] = _mm256_xor_pd(
		x.val[1],
		_mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x8000000000000000))
	);
	x.val[2] = _mm256_xor_pd(
		x.val[2],
		_mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x8000000000000000))
	);
	x.val[3] = _mm256_xor_pd(
		x.val[3],
		_mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x8000000000000000))
	);
	return x;
}

//------------------------------------------------------------------------------
// __m256dx4 Addition
//------------------------------------------------------------------------------
/** 
 * @author Taken and/or modified from libQD which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */

/* __m256dx4 + __m256dx4 */

inline __m256dx4 _mm256x4_add_quick_pdx4(__m256dx4 x, __m256dx4 y) {
	/*
	__m256d s0, s1, s2, s3;
	__m256d t0, t1, t2, t3;
	
	s0 = _mm256_two_sum_pd(x.val[0], y.val[0], t0);
	s1 = _mm256_two_sum_pd(x.val[1], y.val[1], t1);
	s2 = _mm256_two_sum_pd(x.val[2], y.val[2], t2);
	s3 = _mm256_two_sum_pd(x.val[3], y.val[3], t3);

	s1 = _mm256_two_sum_pd(s1, t0, t0);
	_mm256_three_sum_pd(s2, t0, t1);
	_mm256_three_sum2_pd(s3, t0, t2);
	t0 = t0 + t1 + t3;

	_mm256x4_renorm_err_pdx4(s0, s1, s2, s3, t0);
	return __m256dx4(s0, s1, s2, s3, t0);
	*/

	/* Same as above, but addition re-organized to minimize
		data dependency ... unfortunately some compilers are
		not very smart to do this automatically */
	__m256dx4 s;
	__m256d t0, t1, t2, t3;

	__m256d v0, v1, v2, v3;
	__m256d u0, u1, u2, u3;
	__m256d w0, w1, w2, w3;

	s.val[0] = _mm256_add_pd(x.val[0], y.val[0]);
	s.val[1] = _mm256_add_pd(x.val[1], y.val[1]);
	s.val[2] = _mm256_add_pd(x.val[2], y.val[2]);
	s.val[3] = _mm256_add_pd(x.val[3], y.val[3]);

	v0 = _mm256_sub_pd(s.val[0], x.val[0]);
	v1 = _mm256_sub_pd(s.val[1], x.val[1]);
	v2 = _mm256_sub_pd(s.val[2], x.val[2]);
	v3 = _mm256_sub_pd(s.val[3], x.val[3]);

	u0 = _mm256_sub_pd(s.val[0], v0);
	u1 = _mm256_sub_pd(s.val[1], v1);
	u2 = _mm256_sub_pd(s.val[2], v2);
	u3 = _mm256_sub_pd(s.val[3], v3);

	w0 = _mm256_sub_pd(x.val[0], u0);
	w1 = _mm256_sub_pd(x.val[1], u1);
	w2 = _mm256_sub_pd(x.val[2], u2);
	w3 = _mm256_sub_pd(x.val[3], u3);

	u0 = _mm256_sub_pd(y.val[0], v0);
	u1 = _mm256_sub_pd(y.val[1], v1);
	u2 = _mm256_sub_pd(y.val[2], v2);
	u3 = _mm256_sub_pd(y.val[3], v3);

	t0 = _mm256_sub_pd(w0, u0);
	t1 = _mm256_sub_pd(w1, u1);
	t2 = _mm256_sub_pd(w2, u2);
	t3 = _mm256_sub_pd(w3, u3);

	s.val[1] = _mm256_two_sum_pd(s.val[1], t0, &t0);
	_mm256_three_sum_pd (&s.val[2], &t0, &t1);
	_mm256_three_sum2_pd(&s.val[3], &t0, &t2);
	t0 = _mm256_add_pd(_mm256_add_pd(t0, t1), t3);

	/* renormalize */
	_mm256x4_renorm_err_pdx4(&s, &t0);
	return s;
}

inline __m256dx4 _mm256x4_add_pdx4(__m256dx4 x, __m256dx4 y) {
	// #ifdef __M256DX4_IEEE_MODE
	// 	return _mm256x4add_accurate_pdx4(x, y);
	// #else
		return _mm256x4_add_quick_pdx4(x, y);
	// #endif
}

/* __m256dx4 + __m256dx2 */

inline __m256dx4 _mm256x4_add_pdx4_pdx2(const __m256dx4 x, const __m256dx2 y) {
	__m256dx4 s;
	__m256d t0, t1;

	s.val[0] = _mm256_two_sum_pd(x.val[0], y.hi, &t0);
	s.val[1] = _mm256_two_sum_pd(x.val[1], y.lo, &t1);

	s.val[1] = _mm256_two_sum_pd(s.val[1], t0, &t0);

	s.val[2] = x.val[2];
	_mm256_three_sum_pd(&s.val[2], &t0, &t1);

	s.val[3] = _mm256_two_sum_pd(t0, x.val[3], &t0);
	t0 = _mm256_add_pd(t0, t1);

	_mm256x4_renorm_err_pdx4(&s, &t0);
	return s;
}

/* __m256dx2 + __m256dx4 */

inline __m256dx4 _mm256x4_add_pdx2_pdx4(const __m256dx2 x, const __m256dx4 y) {
	__m256dx4 s;
	__m256d t0, t1;

	s.val[0] = _mm256_two_sum_pd(x.hi, y.val[0], &t0);
	s.val[1] = _mm256_two_sum_pd(x.lo, y.val[1], &t1);

	s.val[1] = _mm256_two_sum_pd(s.val[1], t0, &t0);

	s.val[2] = y.val[2];
	_mm256_three_sum_pd(&s.val[2], &t0, &t1);

	s.val[3] = _mm256_two_sum_pd(t0, y.val[3], &t0);
	t0 = _mm256_add_pd(t0, t1);

	_mm256x4_renorm_err_pdx4(&s, &t0);
	return s;
}

/* __m256dx4 + __m256d */

inline __m256dx4 _mm256x4_add_pdx4_pd(const __m256dx4 x, const __m256d y) {
	__m256dx4 ret;
	__m256d e;

	ret.val[0] = _mm256_two_sum_pd(x.val[0], y, &e);
	ret.val[1] = _mm256_two_sum_pd(x.val[1], e, &e);
	ret.val[2] = _mm256_two_sum_pd(x.val[2], e, &e);
	ret.val[3] = _mm256_two_sum_pd(x.val[3], e, &e);

	_mm256x4_renorm_err_pdx4(&ret, &e);
	return ret;
}

/* __m256d + __m256dx4 */

inline __m256dx4 _mm256x4_add_pd_pdx4(const __m256d x, const __m256dx4 y) {
	__m256dx4 ret;
	__m256d e;

	ret.val[0] = _mm256_two_sum_pd(x, y.val[0], &e);
	ret.val[1] = _mm256_two_sum_pd(e, y.val[1], &e);
	ret.val[2] = _mm256_two_sum_pd(e, y.val[2], &e);
	ret.val[3] = _mm256_two_sum_pd(e, y.val[3], &e);

	_mm256x4_renorm_err_pdx4(&ret, &e);
	return ret;
}

//------------------------------------------------------------------------------
// __m256dx4 Optimized Addition
//------------------------------------------------------------------------------

/* __m256dx2 + __m256dx2 */

inline __m256dx4 _mm256x4_add_pdx2_pdx2(const __m256dx2 x, const __m256dx2 y) {
	__m256dx4 s;
	__m256d t0, t1;

	s.val[0] = _mm256_two_sum_pd(x.hi, y.hi, &t0);
	s.val[1] = _mm256_two_sum_pd(x.lo, y.lo, &t1);

	s.val[1] = _mm256_two_sum_pd(s.val[1], t0, &t0);
	s.val[2] = _mm256_two_sum_pd(t0, t1, &t0);
	s.val[3] = t0;

	_mm256x4_renorm_err_pdx4(&s, &t1);
	return s;
}

/* __m256dx2 + __m256d */

inline __m256dx4 _mm256x4_add_pdx2_pd(const __m256dx2 x, const __m256d y) {
	__m256dx4 s;
	__m256d t0;

	s.val[0] = _mm256_two_sum_pd(x.hi, y, &t0);
	s.val[1] = x.lo;

	s.val[1] = _mm256_two_sum_pd(s.val[1], t0, &t0);
	s.val[2] = t0;
	s.val[3] = _mm256_setzero_pd();
	return s; // renormalization not needed
}

/* __m256d + __m256dx2 */

inline __m256dx4 _mm256x4_add_pd_pdx2(const __m256d x, const __m256dx2 y) {
	__m256dx4 s;
	__m256d t0;

	s.val[0] = _mm256_two_sum_pd(x, y.hi, &t0);
	s.val[1] = y.lo;

	s.val[1] = _mm256_two_sum_pd(s.val[1], t0, &t0);
	s.val[2] = t0;
	s.val[3] = _mm256_setzero_pd();
	return s; // renormalization not needed
}

/* __m256d + __m256d */

inline __m256dx4 _mm256x4_add_pd_pd(const __m256d x, const __m256d y) {
	__m256dx4 s;
	__m256d t0;

	s.val[0] = _mm256_two_sum_pd(x, y, &t0);
	s.val[1] = t0;
	s.val[2] = _mm256_setzero_pd();
	s.val[3] = _mm256_setzero_pd();
	return s; // renormalization not needed
}

//------------------------------------------------------------------------------
// __m256dx4 Subtraction
//------------------------------------------------------------------------------
/** 
 * @author Taken and/or modified from libQD which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */

/* __m256dx4 - __m256dx4 */

/** @brief Orginally qd_real::sloppy_add */
inline __m256dx4 _mm256x4_sub_quick_pdx4(const __m256dx4 x, const __m256dx4 y) {
	/*
	__m256d s0, s1, s2, s3;
	__m256d t0, t1, t2, t3;
	
	s0 = _mm256_two_sum_pd(x.val[0], y.val[0], t0);
	s1 = _mm256_two_sum_pd(x.val[1], y.val[1], t1);
	s2 = _mm256_two_sum_pd(x.val[2], y.val[2], t2);
	s3 = _mm256_two_sum_pd(x.val[3], y.val[3], t3);

	s1 = _mm256_two_sum_pd(s1, t0, t0);
	_mm256_three_sum_pd(s2, t0, t1);
	_mm256_three_sum2_pd(s3, t0, t2);
	t0 = t0 + t1 + t3;

	_mm256x4_renorm_err_pdx4(s0, s1, s2, s3, t0);
	return __m256dx4(s0, s1, s2, s3, t0);
	*/

	/* Same as above, but addition re-organized to minimize
		data dependency ... unfortunately some compilers are
		not very smart to do this automatically */
	__m256dx4 s;
	__m256d t0, t1, t2, t3;

	__m256d v0, v1, v2, v3;
	__m256d u0, u1, u2, u3;
	__m256d w0, w1, w2, w3;

	s.val[0] = _mm256_sub_pd(x.val[0], y.val[0]);
	s.val[1] = _mm256_sub_pd(x.val[1], y.val[1]);
	s.val[2] = _mm256_sub_pd(x.val[2], y.val[2]);
	s.val[3] = _mm256_sub_pd(x.val[3], y.val[3]);

	v0 = _mm256_sub_pd(s.val[0], x.val[0]);
	v1 = _mm256_sub_pd(s.val[1], x.val[1]);
	v2 = _mm256_sub_pd(s.val[2], x.val[2]);
	v3 = _mm256_sub_pd(s.val[3], x.val[3]);

	u0 = _mm256_sub_pd(s.val[0], v0);
	u1 = _mm256_sub_pd(s.val[1], v1);
	u2 = _mm256_sub_pd(s.val[2], v2);
	u3 = _mm256_sub_pd(s.val[3], v3);

	w0 = _mm256_sub_pd(x.val[0], u0);
	w1 = _mm256_sub_pd(x.val[1], u1);
	w2 = _mm256_sub_pd(x.val[2], u2);
	w3 = _mm256_sub_pd(x.val[3], u3);

	// u is negative
	u0 = _mm256_add_pd(y.val[0], v0);
	u1 = _mm256_add_pd(y.val[1], v1);
	u2 = _mm256_add_pd(y.val[2], v2);
	u3 = _mm256_add_pd(y.val[3], v3);

	t0 = _mm256_sub_pd(w0, u0);
	t1 = _mm256_sub_pd(w1, u1);
	t2 = _mm256_sub_pd(w2, u2);
	t3 = _mm256_sub_pd(w3, u3);

	s.val[1] = _mm256_two_sum_pd(s.val[1], t0, &t0);
	_mm256_three_sum_pd (&s.val[2], &t0, &t1);
	_mm256_three_sum2_pd(&s.val[3], &t0, &t2);
	t0 = _mm256_add_pd(_mm256_add_pd(t0, t1), t3);

	/* renormalize */
	_mm256x4_renorm_err_pdx4(&s, &t0);
	return s;
}

inline __m256dx4 _mm256x4_sub_pdx4(const __m256dx4 x, const __m256dx4 y) {
	// #ifdef __M256DX4_IEEE_MODE
	// 	return _mm256x4_sub_accurate_pdx4(x, y);
	// #else
		return _mm256x4_sub_quick_pdx4(x, y);
	// #endif
}

/* __m256dx4 - __m256dx2 */

inline __m256dx4 _mm256x4_sub_pdx4_pdx2(const __m256dx4 x, const __m256dx2 y) {
	__m256dx4 s;
	__m256d t0, t1;

	s.val[0] = _mm256_two_diff_pd(x.val[0], y.hi, &t0);
	s.val[1] = _mm256_two_diff_pd(x.val[1], y.lo, &t1);

	s.val[1] = _mm256_two_sum_pd(s.val[1], t0, &t0);

	s.val[2] = x.val[2];
	_mm256_three_sum_pd(&s.val[2], &t0, &t1);

	s.val[3] = _mm256_two_sum_pd(t0, x.val[3], &t0);
	t0 = _mm256_add_pd(t0, t1);

	_mm256x4_renorm_err_pdx4(&s, &t0);
	return s;
}

/* __m256dx2 - __m256dx4 */

inline __m256dx4 _mm256x4_sub_pdx2_pdx4(const __m256dx2 x, const __m256dx4 y) {
	__m256dx4 s;
	__m256d t0, t1;

	s.val[0] = _mm256_two_diff_pd(x.hi, y.val[0], &t0);
	s.val[1] = _mm256_two_diff_pd(x.lo, y.val[1], &t1);

	s.val[1] = _mm256_two_sum_pd(s.val[1], t0, &t0);

	s.val[2] = _mm256_negate_pd(y.val[2]);
	_mm256_three_sum_pd(&s.val[2], &t0, &t1);

	s.val[3] = _mm256_two_diff_pd(t0, y.val[3], &t0);
	t0 = _mm256_add_pd(t0, t1);

	_mm256x4_renorm_err_pdx4(&s, &t0);
	return s;
}

/* __m256dx4 - __m256d */

inline __m256dx4 _mm256x4_sub_pdx4_pd(const __m256dx4 x, const __m256d y) {
	__m256dx4 ret;
	__m256d e;

	ret.val[0] = _mm256_two_diff_pd(x.val[0], y, &e);
	ret.val[1] = _mm256_two_sum_pd(x.val[1], e, &e);
	ret.val[2] = _mm256_two_sum_pd(x.val[2], e, &e);
	ret.val[3] = _mm256_two_sum_pd(x.val[3], e, &e);

	_mm256x4_renorm_err_pdx4(&ret, &e);
	return ret;
}

/* __m256d - __m256dx4 */

inline __m256dx4 _mm256x4_sub_pd_pdx4(const __m256d x, const __m256dx4 y) {
	__m256dx4 ret;
	__m256d e;

	ret.val[0] = _mm256_two_diff_pd(x, y.val[0], &e);
	ret.val[1] = _mm256_two_diff_pd(e, y.val[1], &e);
	ret.val[2] = _mm256_two_diff_pd(e, y.val[2], &e);
	ret.val[3] = _mm256_two_diff_pd(e, y.val[3], &e);

	_mm256x4_renorm_err_pdx4(&ret, &e);
	return ret;
}

//------------------------------------------------------------------------------
// __m256dx4 Optimized Subtraction
//------------------------------------------------------------------------------

/* __m256dx2 - __m256dx2 */

inline __m256dx4 _mm256x4_sub_pdx2_pdx2(const __m256dx2 x, const __m256dx2 y) {
	__m256dx4 s;
	__m256d t0, t1;

	s.val[0] = _mm256_two_diff_pd(x.hi, y.hi, &t0);
	s.val[1] = _mm256_two_diff_pd(x.lo, y.lo, &t1);

	s.val[1] = _mm256_two_sum_pd(s.val[1], t0, &t0);
	s.val[2] = _mm256_two_sum_pd(t0, t1, &t0);
	s.val[3] = t0;

	_mm256x4_renorm_err_pdx4(&s, &t1);
	return s;
}

/* __m256dx2 - __m256d */

inline __m256dx4 _mm256x4_sub_pdx2_pd(const __m256dx2 x, const __m256d y) {
	__m256dx4 s;
	__m256d t0;

	s.val[0] = _mm256_two_diff_pd(x.hi, y, &t0);
	s.val[1] = x.lo;

	s.val[1] = _mm256_two_sum_pd(s.val[1], t0, &t0);
	s.val[2] = t0;
	s.val[3] = _mm256_setzero_pd();
	return s; // renormalization not needed
}

/* __m256d - __m256dx2 */

inline __m256dx4 _mm256x4_sub_pd_pdx2(const __m256d x, const __m256dx2 y) {
	__m256dx4 s;
	__m256d t0;

	s.val[0] = _mm256_two_diff_pd(x, y.hi, &t0);
	s.val[1] = _mm256_negate_pd(y.lo);

	s.val[1] = _mm256_two_sum_pd(s.val[1], t0, &t0);
	s.val[2] = t0;
	s.val[3] = _mm256_setzero_pd();
	return s; // renormalization not needed
}

/* __m256d - __m256d */

inline __m256dx4 _mm256x4_sub_pd_pd(const __m256d x, const __m256d y) {
	__m256dx4 s;
	__m256d t0;

	s.val[0] = _mm256_two_diff_pd(x, y, &t0);
	s.val[1] = t0;
	s.val[2] = _mm256_setzero_pd();
	s.val[3] = _mm256_setzero_pd();
	return s; // renormalization not needed
}

//------------------------------------------------------------------------------
// __m256dx4 Multiplication
//------------------------------------------------------------------------------
/** 
 * @author Taken and/or modified from libQD which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */

/* __m256dx4 * __m256dx4 */

/** @brief Orginally qd_real::accurate_mul */
inline __m256dx4 _mm256x4_mul_accurate_pdx4(const __m256dx4 x, const __m256dx4 y) {
	__m256d p0, p1, p2, p3, p4, p5;
	__m256d q0, q1, q2, q3, q4, q5;
	__m256d p6, p7, p8, p9;
	__m256d q6, q7, q8, q9;
	__m256d r0, r1;
	__m256d t0, t1;
	__m256d s0, s1, s2;

	p0 = _mm256_two_prod_pd(x.val[0], y.val[0], &q0);

	p1 = _mm256_two_prod_pd(x.val[0], y.val[1], &q1);
	p2 = _mm256_two_prod_pd(x.val[1], y.val[0], &q2);

	p3 = _mm256_two_prod_pd(x.val[0], y.val[2], &q3);
	p4 = _mm256_two_prod_pd(x.val[1], y.val[1], &q4);
	p5 = _mm256_two_prod_pd(x.val[2], y.val[0], &q5);

	/* Start Accumulation */
	_mm256_three_sum_pd(&p1, &p2, &q0);

	/* Six-Three Sum  of p2, q1, q2, p3, p4, p5. */
	_mm256_three_sum_pd(&p2, &q1, &q2);
	_mm256_three_sum_pd(&p3, &p4, &p5);
	/* compute (s0, s1, s2) = (p2, q1, q2) + (p3, p4, p5). */
	s0 = _mm256_two_sum_pd(p2, p3, &t0);
	s1 = _mm256_two_sum_pd(q1, p4, &t1);
	s2 = _mm256_add_pd(q2, p5);
	s1 = _mm256_two_sum_pd(s1, t0, &t0);
	s2 = _mm256_add_pd(s2, _mm256_add_pd(t0, t1));

	/* O(eps^3) order terms */
	p6 = _mm256_two_prod_pd(x.val[0], y.val[3], &q6);
	p7 = _mm256_two_prod_pd(x.val[1], y.val[2], &q7);
	p8 = _mm256_two_prod_pd(x.val[2], y.val[1], &q8);
	p9 = _mm256_two_prod_pd(x.val[3], y.val[0], &q9);

	/* Nine-Two-Sum of q0, s1, q3, q4, q5, p6, p7, p8, p9. */
	q0 = _mm256_two_sum_pd(q0, q3, &q3);
	q4 = _mm256_two_sum_pd(q4, q5, &q5);
	p6 = _mm256_two_sum_pd(p6, p7, &p7);
	p8 = _mm256_two_sum_pd(p8, p9, &p9);
	/* Compute (t0, t1) = (q0, q3) + (q4, q5). */
	t0 = _mm256_two_sum_pd(q0, q4, &t1);
	t1 = _mm256_add_pd(t1, _mm256_add_pd(q3, q5));
	/* Compute (r0, r1) = (p6, p7) + (p8, p9). */
	r0 = _mm256_two_sum_pd(p6, p8, &r1);
	r1 = _mm256_add_pd(r1, _mm256_add_pd(p7, p9));
	/* Compute (q3, q4) = (t0, t1) + (r0, r1). */
	q3 = _mm256_two_sum_pd(t0, r0, &q4);
	q4 = _mm256_add_pd(q4, _mm256_add_pd(t1, r1));
	/* Compute (t0, t1) = (q3, q4) + s1. */
	t0 = _mm256_two_sum_pd(q3, s1, &t1);
	t1 = _mm256_add_pd(t1, q4);

	/* O(eps^4) terms -- Nine-One-Sum */
	t1 = _mm256_add_pd(t1, _mm256_add_pd(_mm256_add_pd(_mm256_add_pd(_mm256_add_pd(_mm256_add_pd(
	_mm256_add_pd(
		_mm256_add_pd(
			_mm256_mul_pd(x.val[1], y.val[3]),
			_mm256_mul_pd(x.val[2], y.val[2])
		), _mm256_mul_pd(x.val[3], y.val[1])
	), q6), q7), q8), q9), s2));
	
	__m256dx4 ret = {p0, p1, s0, t0};
	_mm256x4_renorm_err_pdx4(&ret, &t1);
	return ret;
}

/** @brief Orginally qd_real::sloppy_mul */
inline __m256dx4 _mm256x4_mul_quick_pdx4(const __m256dx4 x, const __m256dx4 y) {
	__m256d p0, p1, p2, p3, p4, p5;
	__m256d q0, q1, q2, q3, q4, q5;
	__m256d t0, t1;
	__m256d s0, s1, s2;

	p0 = _mm256_two_prod_pd(x.val[0], y.val[0], &q0);

	p1 = _mm256_two_prod_pd(x.val[0], y.val[1], &q1);
	p2 = _mm256_two_prod_pd(x.val[1], y.val[0], &q2);

	p3 = _mm256_two_prod_pd(x.val[0], y.val[2], &q3);
	p4 = _mm256_two_prod_pd(x.val[1], y.val[1], &q4);
	p5 = _mm256_two_prod_pd(x.val[2], y.val[0], &q5);

	/* Start Accumulation */
	_mm256_three_sum_pd(&p1, &p2, &q0);

	/* Six-Three Sum  of p2, q1, q2, p3, p4, p5. */
	_mm256_three_sum_pd(&p2, &q1, &q2);
	_mm256_three_sum_pd(&p3, &p4, &p5);
	/* compute (s0, s1, s2) = (p2, q1, q2) + (p3, p4, p5). */
	s0 = _mm256_two_sum_pd(p2, p3, &t0);
	s1 = _mm256_two_sum_pd(q1, p4, &t1);
	s2 = _mm256_add_pd(q2, p5);
	s1 = _mm256_two_sum_pd(s1, t0, &t0);
	s2 = _mm256_add_pd(s2, _mm256_add_pd(t0, t1));

	/* O(eps^3) order terms */
	s1 = _mm256_add_pd(s1, _mm256_add_pd(_mm256_add_pd(_mm256_add_pd(_mm256_add_pd(
	_mm256_add_pd(
		_mm256_add_pd(
			_mm256_add_pd(
				_mm256_mul_pd(x.val[0], y.val[3]),
				_mm256_mul_pd(x.val[1], y.val[2])
			), _mm256_mul_pd(x.val[2], y.val[1])
		), _mm256_mul_pd(x.val[3], y.val[0])
	), q0), q3), q4), q5));
	__m256dx4 ret = {p0, p1, s0, s1};
	_mm256x4_renorm_err_pdx4(&ret, &s2);
	return ret;
}

inline __m256dx4 _mm256x4_mul_pdx4(const __m256dx4 x, const __m256dx4 y) {
	#ifdef __M256DX4_IEEE_MODE
		return _mm256x4_mul_accurate_pdx4(x, y);
	#else
		return _mm256x4_mul_quick_pdx4(x, y);
	#endif
}

/* __m256dx4 * __m256dx2 */

inline __m256dx4 _mm256x4_mul_pdx4_pdx2(const __m256dx4 x, const __m256dx2 y) {
	__m256dx4 p;
	__m256d p_err;
	__m256d q0, q1, q2, q3, q4;
	__m256d s0, s1, s2;
	__m256d t0, t1;

	p.val[0] = _mm256_two_prod_pd(x.val[0], y.hi, &q0);
	p.val[1] = _mm256_two_prod_pd(x.val[0], y.lo, &q1);
	p.val[2] = _mm256_two_prod_pd(x.val[1], y.hi, &q2);
	p.val[3] = _mm256_two_prod_pd(x.val[1], y.lo, &q3);
	p_err    = _mm256_two_prod_pd(x.val[2], y.hi, &q4);
	
	_mm256_three_sum_pd(&p.val[1], &p.val[2], &q0);
	
	/* Five-Three-Sum */
	_mm256_three_sum_pd(&p.val[2], &p.val[3], &p_err);
	q1 = _mm256_two_sum_pd(q1      , q2, &q2);
	s0 = _mm256_two_sum_pd(p.val[2], q1, &t0);
	s1 = _mm256_two_sum_pd(p.val[3], q2, &t1);
	s1 = _mm256_two_sum_pd(s1      , t0, &t0);
	s2 = _mm256_add_pd(_mm256_add_pd(t0, t1), p_err);
	p.val[2] = s0;

	p.val[3] = _mm256_add_pd(_mm256_add_pd(_mm256_add_pd(
		_mm256_mul_pd(x.val[2], y.hi), _mm256_mul_pd(x.val[3], y.lo)
	), q3), q4);
	_mm256_three_sum2_pd(&p.val[3], &q0, &s1);
	p_err = _mm256_add_pd(q0, s2);

	_mm256x4_renorm_err_pdx4(&p, &p_err);
	return p;
}

/* __m256dx2 * __m256dx4 */

inline __m256dx4 _mm256x4_mul_pdx2_pdx4(const __m256dx2 x, const __m256dx4 y) {
	__m256dx4 p;
	__m256d p_err;
	__m256d q0, q1, q2, q3, q4;
	__m256d s0, s1, s2;
	__m256d t0, t1;

	p.val[0] = _mm256_two_prod_pd(x.hi, y.val[0], &q0);
	p.val[1] = _mm256_two_prod_pd(x.lo, y.val[0], &q1);
	p.val[2] = _mm256_two_prod_pd(x.hi, y.val[1], &q2);
	p.val[3] = _mm256_two_prod_pd(x.lo, y.val[1], &q3);
	p_err    = _mm256_two_prod_pd(x.hi, y.val[2], &q4);
	
	_mm256_three_sum_pd(&p.val[1], &p.val[2], &q0);
	
	/* Five-Three-Sum */
	_mm256_three_sum_pd(&p.val[2], &p.val[3], &p_err);
	q1 = _mm256_two_sum_pd(q1      , q2, &q2);
	s0 = _mm256_two_sum_pd(p.val[2], q1, &t0);
	s1 = _mm256_two_sum_pd(p.val[3], q2, &t1);
	s1 = _mm256_two_sum_pd(s1      , t0, &t0);
	s2 = _mm256_add_pd(_mm256_add_pd(t0, t1), p_err);
	p.val[2] = s0;

	p.val[3] = _mm256_add_pd(_mm256_add_pd(_mm256_add_pd(
		_mm256_mul_pd(y.val[2], x.hi), _mm256_mul_pd(y.val[3], x.lo)
	), q3), q4);
	_mm256_three_sum2_pd(&p.val[3], &q0, &s1);
	p_err = _mm256_add_pd(q0, s2);

	_mm256x4_renorm_err_pdx4(&p, &p_err);
	return p;
}

/* __m256dx4 * __m256d */

inline __m256dx4 _mm256x4_mul_pdx4_pd(const __m256dx4 x, const __m256d y) {
	__m256d p0, p1, p2, p3;
	__m256d q0, q1, q2;
	__m256dx4 s;
	__m256d s_err;

	p0 = _mm256_two_prod_pd(x.val[0], y, &q0);
	p1 = _mm256_two_prod_pd(x.val[1], y, &q1);
	p2 = _mm256_two_prod_pd(x.val[2], y, &q2);
	p3 = _mm256_mul_pd(x.val[3], y);

	s.val[0] = p0;

	s.val[1] = _mm256_two_sum_pd(q0, p1, &s.val[2]);

	_mm256_three_sum_pd(&s.val[2], &q1, &p2);

	_mm256_three_sum2_pd(&q1, &q2, &p3);
	s.val[3] = q1;

	s_err = _mm256_add_pd(q2, p2);

	_mm256x4_renorm_err_pdx4(&s, &s_err);
	return s;
}

/* __m256d * __m256dx4 */

inline __m256dx4 _mm256x4_mul_pd_pdx4(const __m256d x, const __m256dx4 y) {
	__m256d p0, p1, p2, p3;
	__m256d q0, q1, q2;
	__m256dx4 s;
	__m256d s_err;

	p0 = _mm256_two_prod_pd(x, y.val[0], &q0);
	p1 = _mm256_two_prod_pd(x, y.val[1], &q1);
	p2 = _mm256_two_prod_pd(x, y.val[2], &q2);
	p3 = _mm256_mul_pd(x, y.val[3]);

	s.val[0] = p0;

	s.val[1] = _mm256_two_sum_pd(q0, p1, &s.val[2]);

	_mm256_three_sum_pd(&s.val[2], &q1, &p2);

	_mm256_three_sum2_pd(&q1, &q2, &p3);
	s.val[3] = q1;

	s_err = _mm256_add_pd(q2, p2);

	_mm256x4_renorm_err_pdx4(&s, &s_err);
	return s;
}

//------------------------------------------------------------------------------
// __m256dx4 Optimized Mutliplication
//------------------------------------------------------------------------------

/* __m256dx2 * __m256dx2 */

inline __m256dx4 _mm256x4_mul_pdx2_pdx2(const __m256dx2 x, const __m256dx2 y) {
	__m256dx4 p;
	__m256d p_err;
	__m256d q0, q1, q2, q3;
	__m256d s0, s1, s2;
	__m256d t0, t1;

	p.val[0] = _mm256_two_prod_pd(x.hi, y.hi, &q0);
	p.val[1] = _mm256_two_prod_pd(x.lo, y.hi, &q1);
	p.val[2] = _mm256_two_prod_pd(x.hi, y.lo, &q2);
	p.val[3] = _mm256_two_prod_pd(x.lo, y.lo, &q3);
	
	_mm256_three_sum_pd(&p.val[1], &p.val[2], &q0);
	
	/* Five-Three-Sum */
	p.val[2] = _mm256_two_sum_pd(p.val[2], p.val[3], &p.val[3]);
	q1 = _mm256_two_sum_pd(q1      , q2, &q2);
	s0 = _mm256_two_sum_pd(p.val[2], q1, &t0);
	s1 = _mm256_two_sum_pd(p.val[3], q2, &t1);
	s1 = _mm256_two_sum_pd(s1      , t0, &t0);
	s2 = _mm256_add_pd(t0, t1);
	p.val[2] = s0;

	p.val[3] = q3;
	_mm256_three_sum2_pd(&p.val[3], &q0, &s1);
	p_err = _mm256_add_pd(q0, s2);

	_mm256x4_renorm_err_pdx4(&p, &p_err);
	return p;
}

/* __m256dx2 * __m256d */

/**
 * @brief Multiplies a __m256dx2 value with a __m256d value. Storing the result as
 * a __m256dx4 value
 */
inline __m256dx4 _mm256x4_mul_pdx2_pd(const __m256dx2 x, const __m256d y) {
	__m256d p0, p1;
	__m256d q0, q1;
	__m256dx4 s;

	p0 = _mm256_two_prod_pd(x.hi, y, &q0);
	p1 = _mm256_two_prod_pd(x.lo, y, &q1);

	s.val[0] = p0;
	s.val[1] = _mm256_two_sum_pd(q0, p1, &s.val[2]);
	s.val[2] = _mm256_two_sum_pd(s.val[2], q1, &q1);
	s.val[3] = q1;

	_mm256x4_renorm_pdx4(&s);
	return s;
}

/* __m256d * __m256dx2 */

/**
 * @brief Multiplies a __m256d value with a __m256dx2 value. Storing the result as
 * a __m256dx4 value
 */
inline __m256dx4 _mm256x4_mul_pd_pdx2(const __m256d x, const __m256dx2 y) {
	__m256d p0, p1;
	__m256d q0, q1;
	__m256dx4 s;

	p0 = _mm256_two_prod_pd(x, y.hi, &q0);
	p1 = _mm256_two_prod_pd(x, y.lo, &q1);

	s.val[0] = p0;
	s.val[1] = _mm256_two_sum_pd(q0, p1, &s.val[2]);
	s.val[2] = _mm256_two_sum_pd(s.val[2], q1, &q1);
	s.val[3] = q1;

	_mm256x4_renorm_pdx4(&s);
	return s;
}

/* __m256d * __m256d */

/**
 * @brief Multiplies a __m256d value with another __m256d value. Storing the result
 * as a __m256dx4 value.
 * @note __m256dx2 can store the values from this function exactly.
 */
inline __m256dx4 _mm256x4_mul_pd_pd(const __m256d x, const __m256d y) {
	__m256dx4 s;
	s.val[0] = _mm256_two_prod_pd(x, y, &s.val[1]);
	s.val[2] = _mm256_setzero_pd();
	s.val[3] = _mm256_setzero_pd(); 
	return s; // renormalization not needed
}

//------------------------------------------------------------------------------
// __m256dx4 Square
//------------------------------------------------------------------------------
/** 
 * @author Taken/Modified from libQD which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */

inline __m256dx4 _mm256x4_square_pdx4(const __m256dx4 x) {
	__m256dx4 p;
	__m256d p_err_hi, p_err_lo;
	__m256d q0, q1, q2, q3;
	__m256d s0, s1;
	__m256d t0, t1;
	
	p.val[0] = _mm256_two_sqr_pd(x.val[0], &q0);
	// q2 is used as temp storage for 2.0 * x.val[0]
	q2 = _mm256_mul_pd(_mm256_set1_pd(2.0), x.val[0]);
	p.val[1] = _mm256_two_prod_pd(q2, x.val[1], &q1);
	p.val[2] = _mm256_two_prod_pd(q2, x.val[2], &q2);
	p.val[3] = _mm256_two_sqr_pd(x.val[1], &q3);

	p.val[1] = _mm256_two_sum_pd(q0, p.val[1], &q0);

	q0 = _mm256_two_sum_pd(q0, q1, &q1);
	p.val[2] = _mm256_two_sum_pd(p.val[2], p.val[3], &p.val[3]);

	s0 = _mm256_two_sum_pd(q0, p.val[2], &t0);
	s1 = _mm256_two_sum_pd(q1, p.val[3], &t1);

	s1 = _mm256_two_sum_pd(s1, t0, &t0);
	t0 = _mm256_add_pd(t0, t1);

	s1 = _mm256_quick_two_sum_pd(s1, t0, &t0);
	p.val[2] = _mm256_quick_two_sum_pd(s0, s1, &t1);
	p.val[3] = _mm256_quick_two_sum_pd(t1, t0, &q0);

	p_err_hi = _mm256_mul_pd(_mm256_set1_pd(2.0), _mm256_mul_pd(x.val[0], x.val[3]));
	p_err_lo = _mm256_mul_pd(_mm256_set1_pd(2.0), _mm256_mul_pd(x.val[1], x.val[2]));

	p_err_hi = _mm256_two_sum_pd(p_err_hi, p_err_lo, &p_err_lo);
	q2 = _mm256_two_sum_pd(q2, q3, &q3);

	t0 = _mm256_two_sum_pd(p_err_hi, q2, &t1);
	t1 = t1 + p_err_lo + q3;

	p.val[3] = _mm256_two_sum_pd(p.val[3], t0, &p_err_hi);
	p_err_hi = _mm256_add_pd(_mm256_add_pd(p_err_hi, q0), t1);

	_mm256x4_renorm_err_pdx4(&p, &p_err_hi);
	return p;
}

/**
 * @brief Squares a __m256dx2 value with the result stored as a __m256dx4
 */
inline __m256dx4 _mm256x4_square_pdx2(const __m256dx2 x) {
	__m256dx4 p;
	__m256d p_err;
	__m256d q0, q1, q2;
	__m256d s0, s1;
	__m256d t0, t1;
	
	p.val[0] = _mm256_two_sqr_pd(x.hi, &q0);
	p.val[1] = _mm256_two_prod_pd(2.0 * x.hi, x.lo, &q1);
	p.val[2] = _mm256_two_sqr_pd(x.lo, &q2);

	p.val[1] = _mm256_two_sum_pd(q0, p.val[1], &q0);

	q0 = _mm256_two_sum_pd(q0, q1, &q1);
	s0 = _mm256_two_sum_pd(q0, p.val[2], &t0);

	s1 = _mm256_two_sum_pd(q1, t0, &t0);
	s1 = _mm256_quick_two_sum_pd(s1, t0, &t0);
	p.val[2] = _mm256_quick_two_sum_pd(s0, s1, &t1);
	p.val[3] = _mm256_quick_two_sum_pd(t1, t0, &q0);

	p.val[3] = _mm256_two_sum_pd(p.val[3], q2, &p_err);
	p_err = _mm256_add_pd(p_err, q0);

	_mm256x4_renorm_err_pdx4(&p, &p_err);
	return p;
}

/**
 * @brief Squares a __m256d value with the result stored as a __m256dx4.
 * @note __m256dx2 can store the values from this function exactly.
 */
inline __m256dx4 _mm256x4_square_pd(const __m256d x) {
	__m256dx4 p;
	p.val[0] = _mm256_two_sqr_pd(x, &p.val[1]);
	p.val[2] = _mm256_setzero_pd();
	p.val[3] = _mm256_setzero_pd();
	return p; // renormalization not needed
}


//------------------------------------------------------------------------------
// __m256dx4 Division
//------------------------------------------------------------------------------
/** 
 * @author Taken and/or modified from libQD which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */

/* __m256dx4 / __m256dx4 */

/** @brief Orginally qd_real::accurate_div */
inline __m256dx4 _mm256x4_div_accurate_pdx4(const __m256dx4 x, const __m256dx4 y) {
	__m256dx4 q, r;

	q.val[0] = _mm256_div_pd(x.val[0], y.val[0]);
	r = _mm256x4_sub_pdx4(x, _mm256x4_mul_pdx4_pd(y, q.val[0]));

	q.val[1] = _mm256_div_pd(r.val[0], y.val[0]);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx4_pd(y, q.val[1]));

	q.val[2] = _mm256_div_pd(r.val[0], y.val[0]);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx4_pd(y, q.val[2]));

	q.val[3] = _mm256_div_pd(r.val[0], y.val[0]);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx4_pd(y, q.val[3]));

	__m256d err = _mm256_div_pd(r.val[0], y.val[0]);
	_mm256x4_renorm_err_pdx4(&q, &err);
	return q;
}

/** @brief Orginally qd_real::sloppy_div */
inline __m256dx4 _mm256x4_div_quick_pdx4(const __m256dx4 x, const __m256dx4 y) {
	__m256dx4 q, r;

	q.val[0] = _mm256_div_pd(x.val[0], y.val[0]);
	r = _mm256x4_sub_pdx4(x, _mm256x4_mul_pdx4_pd(y, q.val[0]));

	q.val[1] = _mm256_div_pd(r.val[0], y.val[0]);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx4_pd(y, q.val[1]));

	q.val[2] = _mm256_div_pd(r.val[0], y.val[0]);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx4_pd(y, q.val[2]));

	q.val[3] = _mm256_div_pd(r.val[0], y.val[0]);
	_mm256x4_renorm_pdx4(&q);
	return q;
}

inline __m256dx4 _mm256x4_div_pdx4(const __m256dx4 x, const __m256dx4 y) {
	#ifdef __M256DX4_IEEE_MODE
		return _mm256x4_div_accurate_pdx4(x, y);
	#else
		return _mm256x4_div_quick_pdx4(x, y);
	#endif
}

/* __m256dx4 / __m256dx2 */

inline __m256dx4 _mm256x4_div_accurate_pdx4_pdx2(const __m256dx4 x, const __m256dx2 y) {
	__m256dx4 q, r;

	q.val[0] = _mm256_div_pd(x.val[0], y.hi);
	r = _mm256x4_sub_pdx4(x, _mm256x4_mul_pdx2_pd(y, q.val[0]));

	q.val[1] = _mm256_div_pd(r.val[0], y.hi);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx2_pd(y, q.val[1]));

	q.val[2] = _mm256_div_pd(r.val[0], y.hi);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx2_pd(y, q.val[2]));

	q.val[3] = _mm256_div_pd(r.val[0], y.hi);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx2_pd(y, q.val[3]));

	__m256d err = _mm256_div_pd(r.val[0], y.hi);
	_mm256x4_renorm_err_pdx4(&q, &err);
	return q;
}

inline __m256dx4 _mm256x4_div_quick_pdx4_pdx2(const __m256dx4 x, const __m256dx2 y) {
	__m256dx4 q, r;

	q.val[0] = _mm256_div_pd(x.val[0], y.hi);
	r = _mm256x4_sub_pdx4(x, _mm256x4_mul_pdx2_pd(y, q.val[0]));

	q.val[1] = _mm256_div_pd(r.val[0], y.hi);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx2_pd(y, q.val[1]));

	q.val[2] = _mm256_div_pd(r.val[0], y.hi);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx2_pd(y, q.val[2]));

	q.val[3] = _mm256_div_pd(r.val[0], y.hi);
	_mm256x4_renorm_pdx4(&q);
	return q;
}

inline __m256dx4 _mm256x4_div_pdx4_pdx2(const __m256dx4 x, const __m256dx2 y) {
	#ifdef __M256DX4_IEEE_MODE
		return _mm256x4_div_accurate_pdx4_pdx2(x, y);
	#else
		return _mm256x4_div_quick_pdx4_pdx2(x, y);
	#endif
}

/* __m256dx4 / __m256d */

inline __m256dx4 _mm256x4_div_accurate_pdx4_pd(const __m256dx4 x, const __m256d y) {
	__m256dx4 q, r;

	q.val[0] = _mm256_div_pd(x.val[0], y);
	r = _mm256x4_sub_pdx4_pdx2(x, _mm256x2_mul_pd_pd(y, q.val[0]));

	q.val[1] = _mm256_div_pd(r.val[0], y);
	r = _mm256x4_sub_pdx4_pdx2(r, _mm256x2_mul_pd_pd(y, q.val[1]));

	q.val[2] = _mm256_div_pd(r.val[0], y);
	r = _mm256x4_sub_pdx4_pdx2(r, _mm256x2_mul_pd_pd(y, q.val[2]));

	q.val[3] = _mm256_div_pd(r.val[0], y);
	r = _mm256x4_sub_pdx4_pdx2(r, _mm256x2_mul_pd_pd(y, q.val[3]));
	
	__m256d err = _mm256_div_pd(r.val[0], y);
	_mm256x4_renorm_err_pdx4(&q, &err);
	return q;
}

inline __m256dx4 _mm256x4_div_quick_pdx4_pd(const __m256dx4 x, const __m256d y) {
	__m256dx4 q, r;

	q.val[0] = _mm256_div_pd(x.val[0], y);
	r = _mm256x4_sub_pdx4_pdx2(x, _mm256x2_mul_pd_pd(y, q.val[0]));

	q.val[1] = _mm256_div_pd(r.val[0], y);
	r = _mm256x4_sub_pdx4_pdx2(r, _mm256x2_mul_pd_pd(y, q.val[1]));

	q.val[2] = _mm256_div_pd(r.val[0], y);
	r = _mm256x4_sub_pdx4_pdx2(r, _mm256x2_mul_pd_pd(y, q.val[2]));

	q.val[3] = _mm256_div_pd(r.val[0], y);
	_mm256x4_renorm_pdx4(&q);
	return q;
}

inline __m256dx4 _mm256x4_div_pdx4_pd(const __m256dx4 x, const __m256d y) {
	#ifdef __M256DX4_IEEE_MODE
		return _mm256x4_div_accurate_pdx4_pd(x, y);
	#else
		return _mm256x4_div_quick_pdx4_pd(x, y);
	#endif
}

/* __m256dx2 / __m256dx4 */

inline __m256dx4 _mm256x4_div_accurate_pdx2_pdx4(const __m256dx2 x, const __m256dx4 y) {
	__m256dx4 q, r;

	q.val[0] = _mm256_div_pd(x.hi, y.val[0]);
	r = _mm256x4_sub_pdx2_pdx4(x, _mm256x4_mul_pdx4_pd(y, q.val[0]));

	q.val[1] = _mm256_div_pd(r.val[0], y.val[0]);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx4_pd(y, q.val[1]));

	q.val[2] = _mm256_div_pd(r.val[0], y.val[0]);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx4_pd(y, q.val[2]));

	q.val[3] = _mm256_div_pd(r.val[0], y.val[0]);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx4_pd(y, q.val[3]));

	__m256d err = _mm256_div_pd(r.val[0], y.val[0]);
	_mm256x4_renorm_err_pdx4(&q, &err);
	return q;
}

inline __m256dx4 _mm256x4_div_quick_pdx2_pdx4(const __m256dx2 x, const __m256dx4 y) {
	__m256dx4 q, r;

	q.val[0] = _mm256_div_pd(x.hi, y.val[0]);
	r = _mm256x4_sub_pdx2_pdx4(x, _mm256x4_mul_pdx4_pd(y, q.val[0]));

	q.val[1] = _mm256_div_pd(r.val[0], y.val[0]);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx4_pd(y, q.val[1]));

	q.val[2] = _mm256_div_pd(r.val[0], y.val[0]);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx4_pd(y, q.val[2]));

	q.val[3] = _mm256_div_pd(r.val[0], y.val[0]);
	_mm256x4_renorm_pdx4(&q);
	return q;
}

inline __m256dx4 _mm256x4_div_pdx2_pdx4(const __m256dx2 x, const __m256dx4 y) {
	#ifdef __M256DX4_IEEE_MODE
		return _mm256x4_div_accurate_pdx2_pdx4(x, y);
	#else
		return _mm256x4_div_quick_pdx2_pdx4(x, y);
	#endif
}

/* __m256d / __m256dx4 */

inline __m256dx4 _mm256x4_div_accurate_pd_pdx4(const __m256d x, const __m256dx4 y) {
	__m256dx4 q, r;

	q.val[0] = _mm256_div_pd(x, y.val[0]);
	r = _mm256x4_sub_pd_pdx4(x, _mm256x4_mul_pdx4_pd(y, q.val[0]));

	q.val[1] = _mm256_div_pd(r.val[0], y.val[0]);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx4_pd(y, q.val[1]));

	q.val[2] = _mm256_div_pd(r.val[0], y.val[0]);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx4_pd(y, q.val[2]));

	q.val[3] = _mm256_div_pd(r.val[0], y.val[0]);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx4_pd(y, q.val[3]));

	__m256d err = _mm256_div_pd(r.val[0], y.val[0]);
	_mm256x4_renorm_err_pdx4(&q, &err);
	return q;
}

inline __m256dx4 _mm256x4_div_quick_pd_pdx4(const __m256d x, const __m256dx4 y) {
	__m256dx4 q, r;

	q.val[0] = _mm256_div_pd(x, y.val[0]);
	r = _mm256x4_sub_pd_pdx4(x, _mm256x4_mul_pdx4_pd(y, q.val[0]));

	q.val[1] = _mm256_div_pd(r.val[0], y.val[0]);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx4_pd(y, q.val[1]));

	q.val[2] = _mm256_div_pd(r.val[0], y.val[0]);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx4_pd(y, q.val[2]));

	q.val[3] = _mm256_div_pd(r.val[0], y.val[0]);
	_mm256x4_renorm_pdx4(&q);
	return q;
}

inline __m256dx4 _mm256x4_div_pd_pdx4(const __m256d x, const __m256dx4 y) {
	#ifdef __M256DX4_IEEE_MODE
		return _mm256x4_div_accurate_pd_pdx4(x, y);
	#else
		return _mm256x4_div_quick_pd_pdx4(x, y);
	#endif
}

//------------------------------------------------------------------------------
// __m256dx4 Optimized Division
//------------------------------------------------------------------------------

/* __m256dx2 / __m256dx2 */

inline __m256dx4 _mm256x4_div_accurate_pdx2_pdx2(const __m256dx2 x, const __m256dx2 y) {
	__m256dx4 q, r;

	q.val[0] = _mm256_div_pd(x.hi, y.hi);
	r = _mm256x4_sub_pdx2_pdx4(x, _mm256x4_mul_pdx2_pd(y, q.val[0]));

	q.val[1] = _mm256_div_pd(r.val[0], y.hi);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx2_pd(y, q.val[1]));

	q.val[2] = _mm256_div_pd(r.val[0], y.hi);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx2_pd(y, q.val[2]));

	q.val[3] = _mm256_div_pd(r.val[0], y.hi);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx2_pd(y, q.val[3]));

	__m256d err = _mm256_div_pd(r.val[0], y.hi);
	_mm256x4_renorm_err_pdx4(&q, &err);
	return q;
}

inline __m256dx4 _mm256x4_div_quick_pdx2_pdx2(const __m256dx2 x, const __m256dx2 y) {
	__m256dx4 q, r;

	q.val[0] = _mm256_div_pd(x.hi, y.hi);
	r = _mm256x4_sub_pdx2_pdx4(x, _mm256x4_mul_pdx2_pd(y, q.val[0]));

	q.val[1] = _mm256_div_pd(r.val[0], y.hi);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx2_pd(y, q.val[1]));

	q.val[2] = _mm256_div_pd(r.val[0], y.hi);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx2_pd(y, q.val[2]));

	q.val[3] = _mm256_div_pd(r.val[0], y.hi);
	_mm256x4_renorm_pdx4(&q);
	return q;
}

inline __m256dx4 _mm256x4_div_pdx2_pdx2(const __m256dx2 x, const __m256dx2 y) {
	#ifdef __M256DX4_IEEE_MODE
		return _mm256x4_div_accurate_pdx2_pdx2(x, y);
	#else
		return _mm256x4_div_quick_pdx2_pdx2(x, y);
	#endif
}

/* __m256dx2 / __m256d */

inline __m256dx4 _mm256x4_div_accurate_pdx2_pd(const __m256dx2 x, const __m256d y) {
	__m256dx4 q, r;

	q.val[0] = _mm256_div_pd(x.hi, y);
	r = _mm256x4_sub_pdx2_pdx2(x, _mm256x2_mul_pd_pd(y, q.val[0]));

	q.val[1] = _mm256_div_pd(r.val[0], y);
	r = _mm256x4_sub_pdx4_pdx2(r, _mm256x2_mul_pd_pd(y, q.val[1]));

	q.val[2] = _mm256_div_pd(r.val[0], y);
	r = _mm256x4_sub_pdx4_pdx2(r, _mm256x2_mul_pd_pd(y, q.val[2]));

	q.val[3] = _mm256_div_pd(r.val[0], y);
	r = _mm256x4_sub_pdx4_pdx2(r, _mm256x2_mul_pd_pd(y, q.val[3]));

	__m256d err = _mm256_div_pd(r.val[0], y);
	_mm256x4_renorm_err_pdx4(&q, &err);
	return q;
}

inline __m256dx4 _mm256x4_div_quick_pdx2_pd(const __m256dx2 x, const __m256d y) {
	__m256dx4 q, r;

	q.val[0] = _mm256_div_pd(x.hi, y);
	r = _mm256x4_sub_pdx2_pdx2(x, _mm256x2_mul_pd_pd(y, q.val[0]));

	q.val[1] = _mm256_div_pd(r.val[0], y);
	r = _mm256x4_sub_pdx4_pdx2(r, _mm256x2_mul_pd_pd(y, q.val[1]));

	q.val[2] = _mm256_div_pd(r.val[0], y);
	r = _mm256x4_sub_pdx4_pdx2(r, _mm256x2_mul_pd_pd(y, q.val[2]));

	q.val[3] = _mm256_div_pd(r.val[0], y);
	_mm256x4_renorm_pdx4(&q);
	return q;
}

inline __m256dx4 _mm256x4_div_pdx2_pd(const __m256dx2 x, const __m256d y) {
	#ifdef __M256DX4_IEEE_MODE
		return _mm256x4_div_accurate_pdx2_pd(x, y);
	#else
		return _mm256x4_div_quick_pdx2_pd(x, y);
	#endif
}

/* __m256d / __m256dx2 */

inline __m256dx4 _mm256x4_div_accurate_pd_pdx2(const __m256d x, const __m256dx2 y) {
	__m256dx4 q, r;

	q.val[0] = _mm256_div_pd(x, y.hi);
	r = _mm256x4_sub_pd_pdx4(x, _mm256x4_mul_pdx2_pd(y, q.val[0]));

	q.val[1] = _mm256_div_pd(r.val[0], y.hi);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx2_pd(y, q.val[1]));

	q.val[2] = _mm256_div_pd(r.val[0], y.hi);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx2_pd(y, q.val[2]));

	q.val[3] = _mm256_div_pd(r.val[0], y.hi);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx2_pd(y, q.val[3]));

	__m256d err = _mm256_div_pd(r.val[0], y.hi);
	_mm256x4_renorm_err_pdx4(&q, &err);
	return q;
}

inline __m256dx4 _mm256x4_div_quick_pd_pdx2(const __m256d x, const __m256dx2 y) {
	__m256dx4 q, r;

	q.val[0] = _mm256_div_pd(x, y.hi);
	r = _mm256x4_sub_pd_pdx4(x, _mm256x4_mul_pdx2_pd(y, q.val[0]));

	q.val[1] = _mm256_div_pd(r.val[0], y.hi);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx2_pd(y, q.val[1]));

	q.val[2] = _mm256_div_pd(r.val[0], y.hi);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx2_pd(y, q.val[2]));

	q.val[3] = _mm256_div_pd(r.val[0], y.hi);
	_mm256x4_renorm_pdx4(&q);
	return q;
}

inline __m256dx4 _mm256x4_div_pd_pdx2(const __m256d x, const __m256dx2 y) {
	#ifdef __M256DX4_IEEE_MODE
		return _mm256x4_div_accurate_pd_pdx2(x, y);
	#else
		return _mm256x4_div_quick_pd_pdx2(x, y);
	#endif
}

/* __m256d / __m256d */

inline __m256dx4 _mm256x4_div_accurate_pd_pd(const __m256d x, const __m256d y) {
	__m256dx4 q, r;

	q.val[0] = _mm256_div_pd(x, y);
	r = _mm256x4_sub_pd_pdx2(x, _mm256x2_mul_pd_pd(y, q.val[0]));

	q.val[1] = _mm256_div_pd(r.val[0], y);
	r = _mm256x4_sub_pdx4_pdx2(r, _mm256x2_mul_pd_pd(y, q.val[1]));

	q.val[2] = _mm256_div_pd(r.val[0], y);
	r = _mm256x4_sub_pdx4_pdx2(r, _mm256x2_mul_pd_pd(y, q.val[2]));

	q.val[3] = _mm256_div_pd(r.val[0], y);
	r = _mm256x4_sub_pdx4_pdx2(r, _mm256x2_mul_pd_pd(y, q.val[3]));

	__m256d err = _mm256_div_pd(r.val[0], y);
	_mm256x4_renorm_err_pdx4(&q, &err);
	return q;
}

inline __m256dx4 _mm256x4_div_quick_pd_pd(const __m256d x, const __m256d y) {
	__m256dx4 q, r;

	q.val[0] = _mm256_div_pd(x, y);
	r = _mm256x4_sub_pd_pdx2(x, _mm256x2_mul_pd_pd(y, q.val[0]));

	q.val[1] = _mm256_div_pd(r.val[0], y);
	r = _mm256x4_sub_pdx4_pdx2(r, _mm256x2_mul_pd_pd(y, q.val[1]));

	q.val[2] = _mm256_div_pd(r.val[0], y);
	r = _mm256x4_sub_pdx4_pdx2(r, _mm256x2_mul_pd_pd(y, q.val[2]));

	q.val[3] = _mm256_div_pd(r.val[0], y);
	_mm256x4_renorm_pdx4(&q);
	return q;
}

inline __m256dx4 _mm256x4_div_pd_pd(const __m256d x, const __m256d y) {
	#ifdef __M256DX4_IEEE_MODE
		return _mm256x4_div_accurate_pd_pd(x, y);
	#else
		return _mm256x4_div_quick_pd_pd(x, y);
	#endif
}

//------------------------------------------------------------------------------
// __m256dx4 Reciprocal
//------------------------------------------------------------------------------
/** 
 * @author Taken and/or modified from libQD which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */

/* 1.0 / __m256dx4 */

inline __m256dx4 _mm256x4_recip_accurate_pdx4(const __m256dx4 y) {
	__m256dx4 q, r;

	q.val[0] = _mm256_div_pd(_mm256_set1_pd(1.0), y.val[0]);
	r = _mm256x4_sub_pd_pdx4(_mm256_set1_pd(1.0), _mm256x4_mul_pdx4_pd(y, q.val[0]));

	q.val[1] = _mm256_div_pd(r.val[0], y.val[0]);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx4_pd(y, q.val[1]));

	q.val[2] = _mm256_div_pd(r.val[0], y.val[0]);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx4_pd(y, q.val[2]));

	q.val[3] = _mm256_div_pd(r.val[0], y.val[0]);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx4_pd(y, q.val[3]));

	__m256d err = _mm256_div_pd(r.val[0], y.val[0]);
	_mm256x4_renorm_err_pdx4(&q, &err);
	return q;
}

inline __m256dx4 _mm256x4_recip_quick_pdx4(const __m256dx4 y) {
	__m256dx4 q, r;

	q.val[0] = _mm256_div_pd(_mm256_set1_pd(1.0), y.val[0]);
	r = _mm256x4_sub_pd_pdx4(_mm256_set1_pd(1.0), _mm256x4_mul_pdx4_pd(y, q.val[0]));

	q.val[1] = _mm256_div_pd(r.val[0], y.val[0]);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx4_pd(y, q.val[1]));

	q.val[2] = _mm256_div_pd(r.val[0], y.val[0]);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx4_pd(y, q.val[2]));

	q.val[3] = _mm256_div_pd(r.val[0], y.val[0]);
	_mm256x4_renorm_pdx4(&q);
	return q;
}

inline __m256dx4 _mm256x4_recip_pdx4(const __m256dx4 y) {
	#ifdef __M256DX4_IEEE_MODE
		return _mm256x4_recip_accurate_pdx4(y);
	#else
		return _mm256x4_recip_quick_pdx4(y);
	#endif
}

/* 1.0 / __m256dx2 */

inline __m256dx4 _mm256x4_recip_accurate_pdx2(const __m256dx2 y) {
	__m256dx4 q, r;

	q.val[0] = _mm256_div_pd(_mm256_set1_pd(1.0), y.hi);
	r = _mm256x4_sub_pd_pdx4(_mm256_set1_pd(1.0), _mm256x4_mul_pdx2_pd(y, q.val[0]));

	q.val[1] = _mm256_div_pd(r.val[0], y.hi);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx2_pd(y, q.val[1]));

	q.val[2] = _mm256_div_pd(r.val[0], y.hi);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx2_pd(y, q.val[2]));

	q.val[3] = _mm256_div_pd(r.val[0], y.hi);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx2_pd(y, q.val[3]));

	__m256d err = _mm256_div_pd(r.val[0], y.hi);
	_mm256x4_renorm_err_pdx4(&q, &err);
	return q;
}

inline __m256dx4 _mm256x4_recip_quick_pdx2(const __m256dx2 y) {
	__m256dx4 q, r;

	q.val[0] = _mm256_div_pd(_mm256_set1_pd(1.0), y.hi);
	r = _mm256x4_sub_pd_pdx4(_mm256_set1_pd(1.0), _mm256x4_mul_pdx2_pd(y, q.val[0]));

	q.val[1] = _mm256_div_pd(r.val[0], y.hi);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx2_pd(y, q.val[1]));

	q.val[2] = _mm256_div_pd(r.val[0], y.hi);
	r = _mm256x4_sub_pdx4(r, _mm256x4_mul_pdx2_pd(y, q.val[2]));

	q.val[3] = _mm256_div_pd(r.val[0], y.hi);
	_mm256x4_renorm_pdx4(&q);
	return q;
}

inline __m256dx4 _mm256x4_recip_pdx2(const __m256dx2 y) {
	#ifdef __M256DX4_IEEE_MODE
		return _mm256x4_recip_accurate_pdx2(y);
	#else
		return _mm256x4_recip_quick_pdx2(y);
	#endif
}

/* 1.0 / __m256d */

inline __m256dx4 _mm256x4_recip_accurate_pd(const __m256d y) {
	__m256dx4 q, r;

	q.val[0] = _mm256_div_pd(_mm256_set1_pd(1.0), y);
	r = _mm256x4_sub_pd_pdx2(_mm256_set1_pd(1.0), _mm256x2_mul_pd_pd(y, q.val[0]));

	q.val[1] = _mm256_div_pd(r.val[0], y);
	r = _mm256x4_sub_pdx4_pdx2(r, _mm256x2_mul_pd_pd(y, q.val[1]));

	q.val[2] = _mm256_div_pd(r.val[0], y);
	r = _mm256x4_sub_pdx4_pdx2(r, _mm256x2_mul_pd_pd(y, q.val[2]));

	q.val[3] = _mm256_div_pd(r.val[0], y);
	r = _mm256x4_sub_pdx4_pdx2(r, _mm256x2_mul_pd_pd(y, q.val[3]));

	__m256d err = _mm256_div_pd(r.val[0], y);
	_mm256x4_renorm_err_pdx4(&q, &err);
	return q;
}

inline __m256dx4 _mm256x4_recip_quick_pd(const __m256d y) {
	__m256dx4 q, r;

	q.val[0] = _mm256_div_pd(_mm256_set1_pd(1.0), y);
	r = _mm256x4_sub_pd_pdx2(_mm256_set1_pd(1.0), _mm256x2_mul_pd_pd(y, q.val[0]));

	q.val[1] = _mm256_div_pd(r.val[0], y);
	r = _mm256x4_sub_pdx4_pdx2(r, _mm256x2_mul_pd_pd(y, q.val[1]));

	q.val[2] = _mm256_div_pd(r.val[0], y);
	r = _mm256x4_sub_pdx4_pdx2(r, _mm256x2_mul_pd_pd(y, q.val[2]));

	q.val[3] = _mm256_div_pd(r.val[0], y);
	_mm256x4_renorm_pdx4(&q);
	return q;
}

inline __m256dx4 _mm256x4_recip_pd(const __m256d y) {
	#ifdef __M256DX4_IEEE_MODE
		return _mm256x4_recip_accurate_pd(y);
	#else
		return _mm256x4_recip_quick_pd(y);
	#endif
}

//------------------------------------------------------------------------------
// __m256dx4 specialized arithmetic
//------------------------------------------------------------------------------

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero
 */
inline __m256dx4 _mm256x4_mul_power2_pdx4_pd(__m256dx4 x, const __m256d y) {
	x.val[0] *= y;
	x.val[1] *= y;
	x.val[2] *= y;
	x.val[3] *= y;
	return x;
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero
 */
inline __m256dx4 _mm256x4_mul_power2_pd_pdx4(const __m256d x, __m256dx4 y) {
	y.val[0] *= x;
	y.val[1] *= x;
	y.val[2] *= x;
	y.val[3] *= x;
	return y;
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero.
 * The result is stored as a __m256dx4
 */
inline __m256dx4 _mm256x4_mul_power2_pd_pd(const __m256d x, const __m256d y) {
	__m256dx4 ret;
	ret.val[0] = x * y;
	ret.val[1] = _mm256_setzero_pd();
	ret.val[2] = _mm256_setzero_pd();
	ret.val[3] = _mm256_setzero_pd();
	return ret;
}

//------------------------------------------------------------------------------
// __m256dx2 max/min functions
//------------------------------------------------------------------------------

inline __m256dx4 _mm256x4_max_pdx4(__m256dx4 x, __m256dx4 y) {
	const __m256d cmp_max = _mm256_cmplt_pdx4(x, y);
	__m256dx4 ret;
	ret.val[0] = _mm256_blendv_pd(x.val[0], y.val[0], cmp_max);
	ret.val[1] = _mm256_blendv_pd(x.val[1], y.val[1], cmp_max);
	ret.val[2] = _mm256_blendv_pd(x.val[2], y.val[2], cmp_max);
	ret.val[3] = _mm256_blendv_pd(x.val[3], y.val[3], cmp_max);
	return ret;
}

inline __m256dx4 _mm256x2_min_pdx4(__m256dx4 x, __m256dx4 y) {
	const __m256d cmp_min = _mm256_cmpgt_pdx4(x, y);
	__m256dx4 ret;
	ret.val[0] = _mm256_blendv_pd(x.val[0], y.val[0], cmp_min);
	ret.val[1] = _mm256_blendv_pd(x.val[1], y.val[1], cmp_min);
	ret.val[2] = _mm256_blendv_pd(x.val[2], y.val[2], cmp_min);
	ret.val[3] = _mm256_blendv_pd(x.val[3], y.val[3], cmp_min);
	return ret;
}

//------------------------------------------------------------------------------
// __m256dx2 math.h functions
//------------------------------------------------------------------------------

inline __m256dx4 _mm256x4_fabs_pdx4(__m256dx4 x) {
	__m256d cmp_lt = _mm256_cmp_pd(x.val[0], _mm256_setzero_pd(), _CMP_LT_OQ);
	
	__m256d fabs_mask = _mm256_blendv_pd(
		_mm256_set1_pd(1.0), _mm256_set1_pd(-1.0), cmp_lt
	);
	x.val[0] = _mm256_mul_pd(x.val[0], fabs_mask);
	x.val[1] = _mm256_mul_pd(x.val[1], fabs_mask);
	x.val[2] = _mm256_mul_pd(x.val[2], fabs_mask);
	x.val[3] = _mm256_mul_pd(x.val[3], fabs_mask);
	return x;
}

inline __m256dx4 _mm256x4_fdim_pdx4(__m256dx4 x, __m256dx4 y) {
	__m256dx4 ret;
	ret = _mm256x4_sub_pdx4(x, y);
	__m256d cmp_gt = _mm256_cmpgt_pdx4(x, y);
	ret.val[0] = _mm256_blendv_pd(ret.val[0], _mm256_setzero_pd(), cmp_gt);
	ret.val[1] = _mm256_blendv_pd(ret.val[1], _mm256_setzero_pd(), cmp_gt);
	ret.val[2] = _mm256_blendv_pd(ret.val[2], _mm256_setzero_pd(), cmp_gt);
	ret.val[3] = _mm256_blendv_pd(ret.val[3], _mm256_setzero_pd(), cmp_gt);
	return ret;
}

inline __m256dx4 _mm256x4_copysign_pdx4(__m256dx4 x, __m256dx4 y) {
	__m256d negate_mask = _mm256_xor_pd(
		_mm256_cmp_pd(x.val[0], _mm256_setzero_pd(), _CMP_LT_OQ),
		_mm256_cmp_pd(y.val[0], _mm256_setzero_pd(), _CMP_LT_OQ)
	);
	__m256d negate_mul = _mm256_blendv_pd(
		_mm256_set1_pd(1.0), _mm256_set1_pd(-1.0), negate_mask
	);
	x.val[0] = _mm256_mul_pd(x.val[0], negate_mul);
	x.val[1] = _mm256_mul_pd(x.val[1], negate_mul);
	x.val[2] = _mm256_mul_pd(x.val[2], negate_mul);
	x.val[3] = _mm256_mul_pd(x.val[3], negate_mul);
	return x;
}

#ifdef __cplusplus
	}
#endif

#endif /* FLOAT64X4_AVX_H */
