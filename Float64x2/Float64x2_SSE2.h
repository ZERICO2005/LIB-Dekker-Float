/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/
#ifndef FLOAT64X2_SSE2_H
#define FLOAT64X2_SSE2_H

/**
 * @brief Double-Float64 AVX Dekker Float implementation.
 * Source: Creel "Double it Like Dekker" on YouTube.
 *
 * @note Requires AVX or later.
 * @warning -Ofast may break this library. -O3 compiles okay on gcc and clang.
 */

#include "Float64x2_def.h"
#include "../Float64/Float64_SSE2.h"

#include <stdint.h>

#if (!defined(__SSE2__) && defined(__GNUC__))
	#error "__SSE2__ is not enabled in your compiler. Try -msse2"
#endif

#include <emmintrin.h>

#ifdef __SSE4_1__
	#include <smmintrin.h>
#endif
#ifdef __SSE4_2__
	#include <nmmintrin.h>
#endif
#ifdef __AVX__
	#include <immintrin.h>
#endif

#ifdef __cplusplus
	extern "C" {
#endif

//------------------------------------------------------------------------------
// __m128dx2 struct
//------------------------------------------------------------------------------

/**
 * @brief Holds four Double-Float64 dekker floats
 */
typedef struct __m128dx2 {
	__m128d hi;
	__m128d lo;
} __m128dx2;

//------------------------------------------------------------------------------
// __m128d blendv replacement
//------------------------------------------------------------------------------

#ifdef __SSE4_1__

static inline __m128d _internal_mm_blendv_pd(__m128d false_case, __m128d true_case, __m128d mask) {
	return _mm_blendv_pd(false_case, true_case, mask);
}

#else

static inline __m128d _internal_mm_blendv_pd(__m128d false_case, __m128d true_case, __m128d mask) {
	return _mm_or_pd(_mm_andnot_pd(false_case, mask), _mm_and_pd(true_case, mask));
}

#endif

//------------------------------------------------------------------------------
// __m128dx2 set1 functions
//------------------------------------------------------------------------------

static inline __m128dx2 _mm128x2_setzero_pdx2(void) {
	__m128dx2 ret;
	ret.hi = _mm_setzero_pd();
	ret.lo = _mm_setzero_pd();
	return ret;
}

static inline __m128dx2 _mm128x2_set1_pdx2(Float64x2 val) {
	__m128dx2 ret;
	ret.hi = _mm_set1_pd(val.hi);
	ret.lo = _mm_set1_pd(val.lo);
	return ret;
}

/** deprecated */
static inline __m128dx2 _mm128x2_set1_pd_pd(double hi, double lo) {
	__m128dx2 ret;
	ret.hi = _mm_set1_pd(hi);
	ret.lo = _mm_set1_pd(lo);
	return ret;
}

static inline __m128dx2 _mm128x2_set1_pd(double x) {
	__m128dx2 ret;
	ret.hi = _mm_set1_pd(x);
	ret.lo = _mm_setzero_pd();
	return ret;
}

static inline __m128dx2 _mm128x2_set1_epi64x(long long x) {
	__m128dx2 ret;
	ret.hi = _mm_castsi128_pd(_mm_set1_epi64x(x));
	ret.lo = _mm_castsi128_pd(_mm_set1_epi64x(x));
	return ret;
}

//------------------------------------------------------------------------------
// __m128dx2 set functions
//------------------------------------------------------------------------------

/** deprecated */
static inline __m128dx2 _mm128x2_set_pd_pd(
	double hi_1, double lo_1, double hi_0, double lo_0
) {
	__m128dx2 ret;
	ret.hi = _mm_set_pd(hi_1, hi_0);
	ret.lo = _mm_set_pd(lo_1, lo_0);
	return ret;
}

static inline __m128dx2 _mm128x2_set_pd(
	double e1, double e0
) {
	__m128dx2 ret;
	ret.hi = _mm_set_pd(e1, e0);
	ret.lo = _mm_setzero_pd();
	return ret;
}

static inline __m128dx2 _mm128x2_set_epi64x(
	long long hi_1, long long lo_1, long long hi_0, long long lo_0
) {
	__m128dx2 ret;
	ret.hi = _mm_castsi128_pd(_mm_set_epi64x(hi_1, hi_0));
	ret.lo = _mm_castsi128_pd(_mm_set_epi64x(lo_1, lo_0));
	return ret;
}

//------------------------------------------------------------------------------
// __m128dx2 setr (set reverse) functions
//------------------------------------------------------------------------------

/** deprecated */
static inline __m128dx2 _mm128x2_setr_pd_pd(
	double hi_1, double lo_1, double hi_0, double lo_0
) {
	__m128dx2 ret;
	ret.hi = _mm_setr_pd(hi_1, hi_0);
	ret.lo = _mm_setr_pd(lo_1, lo_0);
	return ret;
}

static inline __m128dx2 _mm128x2_setr_pd(
	double x1, double x0
) {
	__m128dx2 ret;
	ret.hi = _mm_setr_pd(x1, x0);
	ret.lo = _mm_setzero_pd();
	return ret;
}

static inline __m128dx2 _mm128x2_setr_epi64x(
	long long hi_1, long long lo_1, long long hi_0, long long lo_0
) {
	__m128dx2 ret;
	ret.hi = _mm_castsi128_pd(_mm_set_epi64x(hi_0, hi_1));
	ret.lo = _mm_castsi128_pd(_mm_set_epi64x(lo_0, lo_1));
	return ret;
}

//------------------------------------------------------------------------------
// __m128dx2 load operations
//------------------------------------------------------------------------------

#if 0
/* Unimplemented */

/**
 * @note mem_addr must be aligned on a 16-byte boundary or a general-protection
 * exception may be generated. However, this may change to be a 32-byte boundry
 * in future implementations.
 *
 * @author This code was provided by an answer from stackoverflow:
 * https://stackoverflow.com/a/78839249
 * Which can be found under a CC BY-SA 4.0 license:
 * https://creativecommons.org/licenses/by-sa/4.0/
 */
static inline __m128dx2 _mm128x2_load_pd(const double* mem_addr) {
	__m128d v0 = _mm_castpd128_pd256(_mm_load_pd(mem_addr));
	__m128d v1 = _mm_castpd128_pd256(_mm_load_pd(mem_addr + 2));
	__m128d temp;
	temp = _mm_load_pd(mem_addr + 4);
	v0 = _mm_insertf128_pd(v0, temp, 1);
	temp = _mm_load_pd(mem_addr + 6);
	v1 = _mm_insertf128_pd(v1, temp, 1);

	__m128dx2 val;
	val.hi = _mm_unpacklo_pd(v0, v1);
	val.lo = _mm_unpackhi_pd(v0, v1);
	return val;
}

/**
 * @author This code was provided by an answer from stackoverflow:
 * https://stackoverflow.com/a/78839249
 * Which can be found under a CC BY-SA 4.0 license:
 * https://creativecommons.org/licenses/by-sa/4.0/
 */
static inline __m128dx2 _mm128x2_loadu_pd(const double* mem_addr) {
	__m128d v0 = _mm_loadu_pd(mem_addr);
	__m128d v1 = _mm_loadu_pd(mem_addr + 2);
	__m128d temp;
	temp = _mm_loadu_pd(mem_addr + 4);
	v0 = _mm_insertf128_pd(v0, temp, 1);
	temp = _mm_loadu_pd(mem_addr + 6);
	v1 = _mm_insertf128_pd(v1, temp, 1);

	__m128dx2 val;
	val.hi = _mm_unpacklo_pd(v0, v1);
	val.lo = _mm_unpackhi_pd(v0, v1);
	return val;
}

/**
 * @note mem_addr must be aligned on a 16-byte boundary or a general-protection
 * exception may be generated. However, this may change to be a 32-byte boundry
 * in future implementations.
 */
static inline __m128dx2 _mm128x2_load_pdx2(const Float64x2* mem_addr) {
	return _mm128x2_load_pd((const double*)((const void*)mem_addr));
}

static inline __m128dx2 _mm128x2_loadu_pdx2(const Float64x2* mem_addr) {
	return _mm128x2_loadu_pd((const double*)((const void*)mem_addr));
}

#endif

/**
 * @note mem_addr must be aligned on a 32-byte boundary or a general-protection
 * exception may be generated.
 */
static inline __m128dx2 _mm128x2_load_raw_pd(const double* mem_addr) {
	__m128dx2 val;
	val.hi = _mm_load_pd(mem_addr);
	mem_addr += sizeof(__m128d) / sizeof(double);
	val.lo = _mm_load_pd(mem_addr);
	return val;
}

static inline __m128dx2 _mm128x2_loadu_raw_pd(const double* mem_addr) {
	__m128dx2 val;
	val.hi = _mm_loadu_pd(mem_addr);
	mem_addr += sizeof(__m128d) / sizeof(double);
	val.lo = _mm_loadu_pd(mem_addr);
	return val;
}

//------------------------------------------------------------------------------
// __m128dx2 store operations
//------------------------------------------------------------------------------

#if 0
/* Unimplemented */

/**
 * @note mem_addr must be aligned on a 32-byte boundary or a general-protection
 * exception may be generated.
 *
 * @author This code was provided by an answer from stackoverflow:
 * https://stackoverflow.com/a/78839249
 * Which can be found under a CC BY-SA 4.0 license:
 * https://creativecommons.org/licenses/by-sa/4.0/
 */
static inline void _mm128x2_store_pd(double* mem_addr, __m128dx2 val) {
	// hi.x, lo.x, hi.z, lo.z
	__m128d v0 = _mm_unpacklo_pd(val.hi, val.lo);
	// hi.y, lo.y, hi.w, lo.w
	__m128d v1 = _mm_unpackhi_pd(val.hi, val.lo);
	__m128d tmp;
	// hi.z, lo.z, hi.w, lo.w
	tmp = _mm_permute2f128_pd(v0, v1, 0x31);
	_mm_store_pd(mem_addr + 4, tmp);
	// hi.x, lo.x, hi.y, lo.y
	tmp = _mm_insertf128_pd(v0, _mm_castpd256_pd128(v1), 1);
	_mm_store_pd(mem_addr, tmp);
}

/**
 * @author This code was provided by an answer from stackoverflow:
 * https://stackoverflow.com/a/78839249
 * Which can be found under a CC BY-SA 4.0 license:
 * https://creativecommons.org/licenses/by-sa/4.0/
 */
static inline void _mm128x2_storeu_pd(double* mem_addr, __m128dx2 val) {
	// hi.x, lo.x, hi.z, lo.z
	__m128d v0 = _mm_unpacklo_pd(val.hi, val.lo);
	// hi.y, lo.y, hi.w, lo.w
	__m128d v1 = _mm_unpackhi_pd(val.hi, val.lo);
	__m128d temp;
	// hi.z, lo.z, hi.w, lo.w
	temp = _mm_permute2f128_pd(v0, v1, 0x31);
	_mm_storeu_pd(mem_addr + 4, temp);
	// hi.x, lo.x, hi.y, lo.y
	temp = _mm_insertf128_pd(v0, _mm_castpd256_pd128(v1), 1);
	_mm_storeu_pd(mem_addr, temp);
}

/**
 * @note mem_addr must be aligned on a 32-byte boundary or a general-protection
 * exception may be generated.
 */
static inline void _mm128x2_store_pdx2(Float64x2* mem_addr, __m128dx2 val) {
	_mm128x2_store_pd((double*)((void*)mem_addr), val);
}

static inline void _mm128x2_storeu_pdx2(Float64x2* mem_addr, __m128dx2 val) {
	_mm128x2_storeu_pd((double*)((void*)mem_addr), val);
}

#endif

/**
 * @note mem_addr must be aligned on a 32-byte boundary or a general-protection
 * exception may be generated.
 */
static inline void _mm_store_raw_pdx2(double* mem_addr, __m128dx2 x) {
	_mm_store_pd(mem_addr, x.hi);
	mem_addr += sizeof(__m128d) / sizeof(double);
	_mm_store_pd(mem_addr, x.lo);
}

static inline void _mm_storeu_raw_pdx2(double* mem_addr, __m128dx2 x) {
	_mm_storeu_pd(mem_addr, x.hi);
	mem_addr += sizeof(__m128d) / sizeof(double);
	_mm_storeu_pd(mem_addr, x.lo);
}

//------------------------------------------------------------------------------
// __m128dx2 bitwise operations
//------------------------------------------------------------------------------

/**
 * @brief bitwise not `~x`
 */
static inline __m128dx2 _mm128x2_not_pdx2(__m128dx2 x) {
	x.hi = _mm_not_pd(x.hi);
	x.lo = _mm_not_pd(x.lo);
	return x;
}

/**
 * @brief bitwise and `x & y`
 */
static inline __m128dx2 _mm128x2_and_pdx2(__m128dx2 x, __m128dx2 y) {
	x.hi = _mm_and_pd(x.hi, y.hi);
	x.lo = _mm_and_pd(x.lo, y.lo);
	return x;
}

/**
 * @brief bitwise andnot `x & ~y`
 */
static inline __m128dx2 _mm128x2_andnot_pdx2(__m128dx2 x, __m128dx2 y) {
	x.hi = _mm_andnot_pd(x.hi, y.hi);
	x.lo = _mm_andnot_pd(x.lo, y.lo);
	return x;
}

/**
 * @brief bitwise or `x | y`
 */
static inline __m128dx2 _mm128x2_or_pdx2(__m128dx2 x, __m128dx2 y) {
	x.hi = _mm_or_pd(x.hi, y.hi);
	x.lo = _mm_or_pd(x.lo, y.lo);
	return x;
}

/**
 * @brief bitwise xor `x ^ y`
 */
static inline __m128dx2 _mm128x2_xor_pdx2(__m128dx2 x, __m128dx2 y) {
	x.hi = _mm_xor_pd(x.hi, y.hi);
	x.lo = _mm_xor_pd(x.lo, y.lo);
	return x;
}

//------------------------------------------------------------------------------
// __m128dx2 comparison extend
//------------------------------------------------------------------------------

/**
 * @brief Copies cmp to val[0 - 1]. Used for extending comparison results.
 */
static inline __m128dx2 _mm128x2_cmp_extend_pd(__m128d cmp) {
	__m128dx2 ret = {cmp, cmp};
	return ret;
}

//------------------------------------------------------------------------------
// __m128dx2 comparison functions
//------------------------------------------------------------------------------

/* __m128dx2 compare __m128dx2 */

	/**
	 * @brief _CMP_ORD_Q
	 */
	static inline __m128d _mm_cmpord_pdx2(__m128dx2 x, __m128dx2 y) {
		__m128d cmp_hi = _mm_cmpord_pd(x.hi, y.hi);
		__m128d cmp_lo = _mm_cmpord_pd(x.lo, y.lo);
		return _mm_and_pd(cmp_hi, cmp_lo);
	}

	/**
	 * @brief _CMP_UNORD_Q
	 */
	static inline __m128d _mm_cmpunord_pdx2(__m128dx2 x, __m128dx2 y) {
		__m128d cmp_hi = _mm_cmpunord_pd(x.hi, y.hi);
		__m128d cmp_lo = _mm_cmpunord_pd(x.lo, y.lo);
		return _mm_or_pd(cmp_hi, cmp_lo);
	}

	/**
	 * @brief _CMP_EQ_OQ
	 */
	static inline __m128d _mm_cmpeq_pdx2(__m128dx2 x, __m128dx2 y) {
		__m128d cmp_hi = _mm_cmpeq_pd(x.hi, y.hi);
		__m128d cmp_lo = _mm_cmpeq_pd(x.lo, y.lo);
		return _mm_and_pd(cmp_hi, cmp_lo);
	}

	/**
	 * @brief _CMP_NEQ_OQ
	 */
	static inline __m128d _mm_cmpneq_pdx2(__m128dx2 x, __m128dx2 y) {
		__m128d cmp_hi = _mm_cmpneq_pd(x.hi, y.hi);
		__m128d cmp_lo = _mm_cmpneq_pd(x.lo, y.lo);
		return _mm_or_pd(cmp_hi, cmp_lo);
	}

#ifdef __AVX__

	/**
	 * @brief _CMP_NEQ_UQ
	 */
	static inline __m128d _mm_cmplg_pdx2(__m128dx2 x, __m128dx2 y) {
		__m128d cmp_hi = _mm_cmp_pd(x.hi, y.hi, _CMP_NEQ_UQ);
		__m128d cmp_lo = _mm_cmp_pd(x.lo, y.lo, _CMP_NEQ_UQ);
		return _mm_or_pd(cmp_hi, cmp_lo);
	}

	/**
	 * @brief _CMP_EQ_UQ
	 */
	static inline __m128d _mm_cmpnlg_pdx2(__m128dx2 x, __m128dx2 y) {
		__m128d cmp_hi = _mm_cmp_pd(x.hi, y.hi, _CMP_EQ_UQ);
		__m128d cmp_lo = _mm_cmp_pd(x.lo, y.lo, _CMP_EQ_UQ);
		return _mm_and_pd(cmp_hi, cmp_lo);
	}

#else

	/**
	 * @brief _CMP_EQ_UQ
	 */
	static inline __m128d _mm_cmplg_pdx2(__m128dx2 x, __m128dx2 y) {
		__m128d cmp_hi = _mm_or_pd(_mm_cmplt_pd(x.hi, y.hi), _mm_cmpgt_pd(x.hi, y.hi));
		__m128d cmp_lo = _mm_cmpneq_pd(x.lo, y.lo);
		return _mm_or_pd(cmp_hi, cmp_lo);
	}

	/**
	 * @brief _CMP_NEQ_UQ
	 */
	static inline __m128d _mm_cmpnlg_pdx2(__m128dx2 x, __m128dx2 y) {
		__m128d cmp_hi = _mm_and_pd(_mm_cmpnlt_pd(x.hi, y.hi), _mm_cmpngt_pd(x.hi, y.hi));
		__m128d cmp_lo = _mm_cmpeq_pd(x.lo, y.lo);
		return _mm_and_pd(cmp_hi, cmp_lo);
	}

#endif

	/**
	 * @brief _CMP_LT_OQ
	 */
	static inline __m128d _mm_cmplt_pdx2(__m128dx2 x, __m128dx2 y) {
		return _mm_or_pd(
			_mm_cmplt_pd(x.hi, y.hi),
			_mm_and_pd(
				_mm_cmpeq_pd(x.hi, y.hi),
				_mm_cmplt_pd(x.lo, y.lo)
			)
		);
	}

	/**
	 * @brief _CMP_LE_OQ
	 */
	static inline __m128d _mm_cmple_pdx2(__m128dx2 x, __m128dx2 y) {
		return _mm_or_pd(
			_mm_cmplt_pd(x.hi, y.hi),
			_mm_and_pd(
				_mm_cmpeq_pd(x.hi, y.hi),
				_mm_cmple_pd(x.lo, y.lo)
			)
		);
	}

	/**
	 * @brief _CMP_GT_OQ
	 */
	static inline __m128d _mm_cmpgt_pdx2(__m128dx2 x, __m128dx2 y) {
		return _mm_or_pd(
			_mm_cmpgt_pd(x.hi, y.hi),
			_mm_and_pd(
				_mm_cmpeq_pd(x.hi, y.hi),
				_mm_cmpgt_pd(x.lo, y.lo)
			)
		);
	}

	/**
	 * @brief _CMP_GE_OQ
	 */
	static inline __m128d _mm_cmpge_pdx2(__m128dx2 x, __m128dx2 y) {
		return _mm_or_pd(
			_mm_cmpgt_pd(x.hi, y.hi),
			_mm_and_pd(
				_mm_cmpeq_pd(x.hi, y.hi),
				_mm_cmpge_pd(x.lo, y.lo)
			)
		);
	}

	/**
	 * @brief _CMP_NLT_UQ
	 */
	static inline __m128d _mm_cmpnlt_pdx2(__m128dx2 x, __m128dx2 y) {
		return _mm_and_pd(
			_mm_cmpnlt_pd(x.hi, y.hi),
			_mm_or_pd(
				_mm_cmpneq_pd(x.hi, y.hi),
				_mm_cmpnlt_pd(x.lo, y.lo)
			)
		);
	}

	/**
	 * @brief _CMP_NLE_UQ
	 */
	static inline __m128d _mm_cmpnle_pdx2(__m128dx2 x, __m128dx2 y) {
		return _mm_and_pd(
			_mm_cmpnlt_pd(x.hi, y.hi),
			_mm_or_pd(
				_mm_cmpneq_pd(x.hi, y.hi),
				_mm_cmpnle_pd(x.lo, y.lo)
			)
		);
	}

	/**
	 * @brief _CMP_NGT_UQ
	 */
	static inline __m128d _mm_cmpngt_pdx2(__m128dx2 x, __m128dx2 y) {
		return _mm_and_pd(
			_mm_cmpngt_pd(x.hi, y.hi),
			_mm_or_pd(
				_mm_cmpneq_pd(x.hi, y.hi),
				_mm_cmpngt_pd(x.lo, y.lo)
			)
		);
	}

	/**
	 * @brief _CMP_NGE_UQ
	 */
	static inline __m128d _mm_cmpnge_pdx2(__m128dx2 x, __m128dx2 y) {
		return _mm_and_pd(
			_mm_cmpngt_pd(x.hi, y.hi),
			_mm_or_pd(
				_mm_cmpneq_pd(x.hi, y.hi),
				_mm_cmpnge_pd(x.lo, y.lo)
			)
		);
	}

/* __m128dx2 compare __m128d */

	/**
	 * @brief _CMP_ORD_Q
	 */
	static inline __m128d _mm_cmpord_pdx2_pd(__m128dx2 x, __m128d y) {
		return _mm_cmpord_pd(x.hi, y);
	}

	/**
	 * @brief _CMP_UNORD_Q
	 */
	static inline __m128d _mm_cmpunord_pdx2_pd(__m128dx2 x, __m128d y) {
		return _mm_cmpunord_pd(x.hi, y);
	}

	/**
	 * @brief _CMP_EQ_OQ
	 */
	static inline __m128d _mm_cmpeq_pdx2_pd(__m128dx2 x, __m128d y) {
		__m128d cmp_hi = _mm_cmpeq_pd(x.hi, y);
		__m128d cmp_lo = _mm_cmpeq_pd(x.lo, _mm_setzero_pd());
		return _mm_and_pd(cmp_hi, cmp_lo);
	}

	/**
	 * @brief _CMP_NEQ_OQ
	 */
	static inline __m128d _mm_cmpneq_pdx2_pd(__m128dx2 x, __m128d y) {
		__m128d cmp_hi = _mm_cmpneq_pd(x.hi, y);
		__m128d cmp_lo = _mm_cmpneq_pd(x.lo, _mm_setzero_pd());
		return _mm_or_pd(cmp_hi, cmp_lo);
	}

	/**
	 * @brief _CMP_NEQ_UQ
	 */
	static inline __m128d _mm_cmplg_pdx2_pd(__m128dx2 x, __m128d y) {
		__m128d cmp_hi = _mm_cmplg_pd(x.hi, y);
		__m128d cmp_lo = _mm_cmplg_pd(x.lo, _mm_setzero_pd());
		return _mm_or_pd(cmp_hi, cmp_lo);
	}

	/**
	 * @brief _CMP_EQ_UQ
	 */
	static inline __m128d _mm_cmpnlg_pdx2_pd(__m128dx2 x, __m128d y) {
		__m128d cmp_hi = _mm_cmpnlg_pd(x.hi, y);
		__m128d cmp_lo = _mm_cmpnlg_pd(x.lo, _mm_setzero_pd());
		return _mm_and_pd(cmp_hi, cmp_lo);
	}

		/**
	 * @brief _CMP_LT_OQ
	 */
	static inline __m128d _mm_cmplt_pdx2_pd(__m128dx2 x, __m128d y) {
		return _mm_or_pd(
			_mm_cmplt_pd(x.hi, y),
			_mm_and_pd(
				_mm_cmpeq_pd(x.hi, y),
				_mm_cmplt_pd(x.lo, _mm_setzero_pd())
			)
		);
	}

	/**
	 * @brief _CMP_LE_OQ
	 */
	static inline __m128d _mm_cmple_pdx2_pd(__m128dx2 x, __m128d y) {
		return _mm_or_pd(
			_mm_cmplt_pd(x.hi, y),
			_mm_and_pd(
				_mm_cmpeq_pd(x.hi, y),
				_mm_cmple_pd(x.lo, _mm_setzero_pd())
			)
		);
	}

	/**
	 * @brief _CMP_GT_OQ
	 */
	static inline __m128d _mm_cmpgt_pdx2_pd(__m128dx2 x, __m128d y) {
		return _mm_or_pd(
			_mm_cmpgt_pd(x.hi, y),
			_mm_and_pd(
				_mm_cmpeq_pd(x.hi, y),
				_mm_cmpgt_pd(x.lo, _mm_setzero_pd())
			)
		);
	}

	/**
	 * @brief _CMP_GE_OQ
	 */
	static inline __m128d _mm_cmpge_pdx2_pd(__m128dx2 x, __m128d y) {
		return _mm_or_pd(
			_mm_cmpgt_pd(x.hi, y),
			_mm_and_pd(
				_mm_cmpeq_pd(x.hi, y),
				_mm_cmpge_pd(x.lo, _mm_setzero_pd())
			)
		);
	}

	/**
	 * @brief _CMP_NLT_UQ
	 */
	static inline __m128d _mm_cmpnlt_pdx2_pd(__m128dx2 x, __m128d y) {
		return _mm_or_pd(
			_mm_cmpnlt_pd(x.hi, y),
			_mm_and_pd(
				_mm_cmpneq_pd(x.hi, y),
				_mm_cmpnlt_pd(x.lo, _mm_setzero_pd())
			)
		);
	}

	/**
	 * @brief _CMP_NLE_UQ
	 */
	static inline __m128d _mm_cmpnle_pdx2_pd(__m128dx2 x, __m128d y) {
		return _mm_and_pd(
			_mm_cmpnlt_pd(x.hi, y),
			_mm_or_pd(
				_mm_cmpneq_pd(x.hi, y),
				_mm_cmpnle_pd(x.lo, _mm_setzero_pd())
			)
		);
	}

	/**
	 * @brief _CMP_NGT_UQ
	 */
	static inline __m128d _mm_cmpngt_pdx2_pd(__m128dx2 x, __m128d y) {
		return _mm_and_pd(
			_mm_cmpngt_pd(x.hi, y),
			_mm_or_pd(
				_mm_cmpneq_pd(x.hi, y),
				_mm_cmpngt_pd(x.lo, _mm_setzero_pd())
			)
		);
	}

	/**
	 * @brief _CMP_NGE_UQ
	 */
	static inline __m128d _mm_cmpnge_pdx2_pd(__m128dx2 x, __m128d y) {
		return _mm_and_pd(
			_mm_cmpngt_pd(x.hi, y),
			_mm_or_pd(
				_mm_cmpneq_pd(x.hi, y),
				_mm_cmpnge_pd(x.lo, _mm_setzero_pd())
			)
		);
	}

/* __m128d compare __m128dx2 */

	/**
	 * @brief _CMP_ORD_Q
	 */
	static inline __m128d _mm_cmpord_pd_pdx2(__m128d x, __m128dx2 y) {
		return _mm_cmpord_pd(x, y.hi);
	}

	/**
	 * @brief _CMP_UNORD_Q
	 */
	static inline __m128d _mm_cmpunord_pd_pdx2(__m128d x, __m128dx2 y) {
		return _mm_cmpunord_pd(x, y.hi);
	}

	/**
	 * @brief _CMP_EQ_OQ
	 */
	static inline __m128d _mm_cmpeq_pd_pdx2(__m128d x, __m128dx2 y) {
		__m128d cmp_hi = _mm_cmpeq_pd(x, y.hi);
		__m128d cmp_lo = _mm_cmpeq_pd(_mm_setzero_pd(), y.lo);
		return _mm_and_pd(cmp_hi, cmp_lo);
	}

	/**
	 * @brief _CMP_NEQ_OQ
	 */
	static inline __m128d _mm_cmpneq_pd_pdx2(__m128d x, __m128dx2 y) {
		__m128d cmp_hi = _mm_cmpneq_pd(x, y.hi);
		__m128d cmp_lo = _mm_cmpneq_pd(_mm_setzero_pd(), y.lo);
		return _mm_or_pd(cmp_hi, cmp_lo);
	}

	/**
	 * @brief _CMP_NEQ_UQ
	 */
	static inline __m128d _mm_cmplg_pd_pdx2(__m128d x, __m128dx2 y) {
		__m128d cmp_hi = _mm_cmplg_pd(x, y.hi);
		__m128d cmp_lo = _mm_cmplg_pd(_mm_setzero_pd(), y.lo);
		return _mm_or_pd(cmp_hi, cmp_lo);
	}

	/**
	 * @brief _CMP_EQ_UQ
	 */
	static inline __m128d _mm_cmpeqnlg_pd_pdx2(__m128d x, __m128dx2 y) {
		__m128d cmp_hi = _mm_cmpnlg_pd(x, y.hi);
		__m128d cmp_lo = _mm_cmpnlg_pd(_mm_setzero_pd(), y.lo);
		return _mm_and_pd(cmp_hi, cmp_lo);
	}

		/**
	 * @brief _CMP_LT_OQ
	 */
	static inline __m128d _mm_cmplt_pd_pdx2(__m128d x, __m128dx2 y) {
		return _mm_or_pd(
			_mm_cmplt_pd(x, y.hi),
			_mm_and_pd(
				_mm_cmpeq_pd(x, y.hi),
				_mm_cmplt_pd(_mm_setzero_pd(), y.lo)
			)
		);
	}

	/**
	 * @brief _CMP_LE_OQ
	 */
	static inline __m128d _mm_cmple_pd_pdx2(__m128d x, __m128dx2 y) {
		return _mm_or_pd(
			_mm_cmplt_pd(x, y.hi),
			_mm_and_pd(
				_mm_cmpeq_pd(x, y.hi),
				_mm_cmple_pd(_mm_setzero_pd(), y.lo)
			)
		);
	}

	/**
	 * @brief _CMP_GT_OQ
	 */
	static inline __m128d _mm_cmpgt_pd_pdx2(__m128d x, __m128dx2 y) {
		return _mm_or_pd(
			_mm_cmpgt_pd(x, y.hi),
			_mm_and_pd(
				_mm_cmpeq_pd(x, y.hi),
				_mm_cmpgt_pd(_mm_setzero_pd(), y.lo)
			)
		);
	}

	/**
	 * @brief _CMP_GE_OQ
	 */
	static inline __m128d _mm_cmpge_pd_pdx2(__m128d x, __m128dx2 y) {
		return _mm_or_pd(
			_mm_cmpgt_pd(x, y.hi),
			_mm_and_pd(
				_mm_cmpeq_pd(x, y.hi),
				_mm_cmpge_pd(_mm_setzero_pd(), y.lo)
			)
		);
	}

	/**
	 * @brief _CMP_NLT_UQ
	 */
	static inline __m128d _mm_cmpnlt_pd_pdx2(__m128d x, __m128dx2 y) {
		return _mm_or_pd(
			_mm_cmpnlt_pd(x, y.hi),
			_mm_and_pd(
				_mm_cmpneq_pd(x, y.hi),
				_mm_cmpnlt_pd(_mm_setzero_pd(), y.lo)
			)
		);
	}

	/**
	 * @brief _CMP_NLE_UQ
	 */
	static inline __m128d _mm_cmpnle_pd_pdx2(__m128d x, __m128dx2 y) {
		return _mm_and_pd(
			_mm_cmpnlt_pd(x, y.hi),
			_mm_or_pd(
				_mm_cmpneq_pd(x, y.hi),
				_mm_cmpnle_pd(_mm_setzero_pd(), y.lo)
			)
		);
	}

	/**
	 * @brief _CMP_NGT_UQ
	 */
	static inline __m128d _mm_cmpngt_pd_pdx2(__m128d x, __m128dx2 y) {
		return _mm_and_pd(
			_mm_cmpngt_pd(x, y.hi),
			_mm_or_pd(
				_mm_cmpneq_pd(x, y.hi),
				_mm_cmpngt_pd(_mm_setzero_pd(), y.lo)
			)
		);
	}

	/**
	 * @brief _CMP_NGE_UQ
	 */
	static inline __m128d _mm_cmpnge_pd_pdx2(__m128d x, __m128dx2 y) {
		return _mm_and_pd(
			_mm_cmpngt_pd(x, y.hi),
			_mm_or_pd(
				_mm_cmpneq_pd(x, y.hi),
				_mm_cmpnge_pd(_mm_setzero_pd(), y.lo)
			)
		);
	}

//------------------------------------------------------------------------------
// __m128dx2 compare to zero functions
//------------------------------------------------------------------------------

/**
 * @brief _CMP_EQ_OQ
 * @note Assumes that if x.hi is zero then x.lo is also zero.
 */
static inline __m128d _mm_cmpeq_zero_pdx2(__m128dx2 x) {
	return _mm_cmpeq_pd(x.hi, _mm_setzero_pd());
}
/**
 * @brief _CMP_NEQ_OQ
 * @note Assumes that if x.hi is zero then x.lo is also zero.
 */
static inline __m128d _mm_cmpneq_zero_pdx2(__m128dx2 x) {
	return _mm_cmpneq_pd(x.hi, _mm_setzero_pd());
}
/**
 * @brief _CMP_NEQ_UQ
 * @note Assumes that if x.hi is zero then x.lo is also zero.
 */
static inline __m128d _mm_cmplg_zero_pdx2(__m128dx2 x) {
	return _mm_cmplg_pd(x.hi, _mm_setzero_pd());
}
/**
 * @brief _CMP_EQ_UQ
 * @note Assumes that if x.hi is zero then x.lo is also zero.
 */
static inline __m128d _mm_cmpnlg_zero_pdx2(__m128dx2 x) {
	return _mm_cmpnlg_pd(x.hi, _mm_setzero_pd());
}

/**
 * @brief _CMP_LT_OQ
 * @note Assumes that if x.hi is zero then x.lo is also zero.
 */
static inline __m128d _mm_cmplt_zero_pdx2(__m128dx2 x) {
	return _mm_cmplt_pd(x.hi, _mm_setzero_pd());
}
/**
 * @brief _CMP_LE_OQ
 * @note Assumes that if x.hi is zero then x.lo is also zero.
 */
static inline __m128d _mm_cmple_zero_pdx2(__m128dx2 x) {
	return _mm_cmple_pd(x.hi, _mm_setzero_pd());
}
/**
 * @brief _CMP_GT_OQ
 * @note Assumes that if x.hi is zero then x.lo is also zero.
 */
static inline __m128d _mm_cmpgt_zero_pdx2(__m128dx2 x) {
	return _mm_cmpgt_pd(x.hi, _mm_setzero_pd());
}
/**
 * @brief _CMP_GE_OQ
 * @note Assumes that if x.hi is zero then x.lo is also zero.
 */
static inline __m128d _mm_cmpge_zero_pdx2(__m128dx2 x) {
	return _mm_cmpge_pd(x.hi, _mm_setzero_pd());
}

/**
 * @brief _CMP_NLT_UQ
 * @note Assumes that if x.hi is zero then x.lo is also zero.
 */
static inline __m128d _mm_cmpnlt_zero_pdx2(__m128dx2 x) {
	return _mm_cmpnlt_pd(x.hi, _mm_setzero_pd());
}
/**
 * @brief _CMP_NLE_UQ
 * @note Assumes that if x.hi is zero then x.lo is also zero.
 */
static inline __m128d _mm_cmpnle_zero_pdx2(__m128dx2 x) {
	return _mm_cmpnle_pd(x.hi, _mm_setzero_pd());
}
/**
 * @brief _CMP_NGT_UQ
 * @note Assumes that if x.hi is zero then x.lo is also zero.
 */
static inline __m128d _mm_cmpngt_zero_pdx2(__m128dx2 x) {
	return _mm_cmpngt_pd(x.hi, _mm_setzero_pd());
}
/**
 * @brief _CMP_NGE_UQ
 * @note Assumes that if x.hi is zero then x.lo is also zero.
 */
static inline __m128d _mm_cmpnge_zero_pdx2(__m128dx2 x) {
	return _mm_cmpnge_pd(x.hi, _mm_setzero_pd());
}

//------------------------------------------------------------------------------
// __m128dx2 basic arithmetic
//------------------------------------------------------------------------------

static inline __m128dx2 _mm128x2_negate_pdx2(__m128dx2 x) {
	const __m128d sign_bit_mask = _mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x8000000000000000));
	x.hi = _mm_xor_pd(x.hi, sign_bit_mask);
	x.lo = _mm_xor_pd(x.lo, sign_bit_mask);
	return x;
}

static inline __m128dx2 _mm128x2_add_pdx2(__m128dx2 x, __m128dx2 y) {

	__m128d r_hi = _mm_add_pd(x.hi, y.hi);

	__m128d rx_lo = _mm_add_pd(_mm_add_pd(
		_mm_add_pd(_mm_sub_pd(x.hi, r_hi), y.hi),
	y.lo), x.lo);
	__m128d ry_lo = _mm_add_pd(_mm_add_pd(
		_mm_add_pd(_mm_sub_pd(y.hi, r_hi), x.hi),
	x.lo), y.lo);

	const __m128d cmp_result = _mm_cmple_pd(
	 	_mm_fabs_pd(x.hi), _mm_fabs_pd(y.hi)
	);
	__m128d r_lo = _internal_mm_blendv_pd(rx_lo, ry_lo, cmp_result);

	__m128dx2 c;
	c.hi = _mm_add_pd(r_hi, r_lo);
	c.lo = _mm_add_pd(_mm_sub_pd(r_hi, c.hi), r_lo);
	return c;
}

static inline __m128dx2 _mm128x2_sub_pdx2(__m128dx2 x, __m128dx2 y) {
	__m128d r_hi = _mm_sub_pd(x.hi, y.hi);

	__m128d rx_lo = _mm_add_pd(_mm_sub_pd(
		_mm_sub_pd(_mm_sub_pd(x.hi, r_hi), y.hi),
	y.lo), x.lo);

	y.hi = _mm_negate_pd(y.hi);
	__m128d ry_lo = _mm_sub_pd(_mm_add_pd(
		_mm_add_pd(_mm_sub_pd(/* negative */ y.hi, r_hi), x.hi),
	x.lo), y.lo);

	const __m128d cmp_result = _mm_cmple_pd(
	 	_mm_fabs_pd(x.hi), _mm_fabs_pd(y.hi)
	);
	__m128d r_lo = _internal_mm_blendv_pd(rx_lo, ry_lo, cmp_result);

	__m128dx2 c;
	c.hi = _mm_add_pd(r_hi, r_lo);
	c.lo = _mm_add_pd(_mm_sub_pd(r_hi, c.hi), r_lo);
	return c;
}

static inline __m128dx2 _mm128x2_dekker_split_pd(__m128d x) {
	#if 0
	// (2^ceil(53 / 2) + 1)
	const __m128d dekker_scale = _mm_set1_pd(134217729.0); 
	__m128d p = _mm_mul_pd(x, dekker_scale);
	__m128dx2 ret;
	ret.hi = _mm_add_pd(_mm_sub_pd(x, p), p);
	ret.lo = _mm_sub_pd(x, ret.hi);

	#else
	// (2^ceil(53 / 2) + 1)
	const __m128d dekker_scale = _mm_set1_pd(134217729.0); 
	__m128d temp = _mm_mul_pd(x, dekker_scale);
	__m128dx2 ret;
	ret.hi = _mm_sub_pd(temp, _mm_sub_pd(temp, x));
	ret.lo = _mm_sub_pd(x, ret.hi);

	#endif
	return ret;
}

// DOUBLE_FLOAT64_AVX_ATTRIBUTE(optimize("-fno-associative"))
// static inline __m128dx2 _mm128x2_dekker_split_pd(__m128d x) {
// 	__m128dx2 r;
// 	r.hi = _mm_andnot_pd(
// 		x,
// 		_mm_castsi128_pd(_mm_set1_epi64x(0x3FFFFFF))
// 	);
// 	r.lo = x - r.hi;
// 	return r;
// }

static inline __m128dx2 _mm128x2_dekker_mul12_pd(__m128d x, __m128d y) {
	__m128dx2 a = _mm128x2_dekker_split_pd(x);
	__m128dx2 b = _mm128x2_dekker_split_pd(y);
	__m128d p = _mm_mul_pd(a.hi, b.hi);
	__m128d q = _mm_add_pd(
		_mm_mul_pd(a.hi, b.lo), _mm_mul_pd(a.lo, b.hi)
	);

	__m128dx2 r;
	r.hi = _mm_add_pd(p, q);
	r.lo = _mm_add_pd(
		_mm_add_pd(_mm_sub_pd(p, r.hi), q),
		_mm_mul_pd(a.lo, b.lo)
	);
	return r;
}

static inline __m128dx2 _mm128x2_mul_pdx2(__m128dx2 x, __m128dx2 y) {
	__m128dx2 t = _mm128x2_dekker_mul12_pd(x.hi, y.hi);
	__m128d c = _mm_add_pd(_mm_add_pd(
		_mm_mul_pd(x.hi, y.lo), _mm_mul_pd(x.lo, y.hi)
	), t.lo);

	__m128dx2 r;
	r.hi = _mm_add_pd(t.hi, c);
	r.lo = _mm_add_pd(_mm_sub_pd(t.hi, r.hi), c);
	return r;
}

static inline __m128dx2 _mm128x2_div_pdx2(__m128dx2 x, __m128dx2 y) {
	__m128d u = _mm_div_pd(x.hi, y.hi);
	__m128dx2 t = _mm128x2_dekker_mul12_pd(u, y.hi);
	__m128d l = _mm_div_pd(_mm_sub_pd(
		_mm_add_pd(_mm_sub_pd(_mm_sub_pd(x.hi, t.hi), t.lo), x.lo),
		_mm_mul_pd(u, y.lo)
	), y.hi);

	__m128dx2 r;
	r.hi = _mm_add_pd(u, l);
	r.lo = _mm_add_pd(_mm_sub_pd(u, r.hi), l);
	return r;
}

static inline __m128dx2 _mm128x2_dekker_square12_pd(__m128d x) {
	__m128dx2 a = _mm128x2_dekker_split_pd(x);
	__m128d p = _mm_mul_pd(a.hi, a.hi);
	__m128d q = _mm_mul_pd(
		_mm_set1_pd(2.0), _mm_mul_pd(a.hi, a.lo)
	);

	__m128dx2 r;
	r.hi = _mm_add_pd(p, q);
	r.lo = _mm_add_pd(
		_mm_add_pd(_mm_sub_pd(p, r.hi), q),
		_mm_mul_pd(a.lo, a.lo)
	);
	return r;
}

static inline __m128dx2 _mm128x2_square_pdx2(__m128dx2 x) {
	__m128dx2 t = _mm128x2_dekker_square12_pd(x.hi);
	__m128d c = _mm_add_pd(
		_mm_mul_pd(_mm_set1_pd(2.0), _mm_mul_pd(x.hi, x.lo)), t.lo
	);

	__m128dx2 r;
	r.hi = _mm_add_pd(t.hi, c);
	r.lo = _mm_add_pd(_mm_sub_pd(t.hi, r.hi), c);
	return r;
}

static inline __m128dx2 _mm128x2_recip_pdx2(__m128dx2 y) {
	__m128d u = _mm_div_pd(_mm_set1_pd(1.0), y.hi);
	__m128dx2 t = _mm128x2_dekker_mul12_pd(u, y.hi);
	__m128d l = _mm_div_pd(_mm_sub_pd(
		_mm_sub_pd(_mm_sub_pd(_mm_set1_pd(1.0), t.hi), t.lo),
		_mm_mul_pd(u, y.lo)
	), y.hi);

	__m128dx2 r;
	r.hi = _mm_add_pd(u, l);
	r.lo = _mm_add_pd(_mm_sub_pd(u, r.hi), l);
	return r;
}

//------------------------------------------------------------------------------
// __m128dx2 optimized arithmetic
//------------------------------------------------------------------------------

static inline __m128dx2 _mm128x2_add_pdx2_pd(__m128dx2 x, __m128d y) {
	__m128d r_hi = _mm_add_pd(x.hi, y);

	__m128d rx_lo = _mm_add_pd(
		_mm_add_pd(_mm_sub_pd(x.hi, r_hi), y), x.lo
	);
	__m128d ry_lo = _mm_add_pd(
		_mm_add_pd(_mm_sub_pd(y, r_hi), x.hi),
	x.lo);

	const __m128d cmp_result = _mm_cmple_pd(
	 	_mm_fabs_pd(x.hi), _mm_fabs_pd(y)
	);
	__m128d r_lo = _internal_mm_blendv_pd(rx_lo, ry_lo, cmp_result);

	__m128dx2 c;
	c.hi = _mm_add_pd(r_hi, r_lo);
	c.lo = _mm_add_pd(_mm_sub_pd(r_hi, c.hi), r_lo);
	return c;
}

static inline __m128dx2 _mm128x2_add_pd_pdx2(__m128d x, __m128dx2 y) {
	__m128d r_hi = _mm_add_pd(x, y.hi);

	__m128d rx_lo = _mm_add_pd(
		_mm_add_pd(_mm_sub_pd(x, r_hi), y.hi),
	y.lo);
	__m128d ry_lo = _mm_add_pd(
		_mm_add_pd(_mm_sub_pd(y.hi, r_hi), x), y.lo
	);

	const __m128d cmp_result = _mm_cmple_pd(
	 	_mm_fabs_pd(x), _mm_fabs_pd(y.hi)
	);
	__m128d r_lo = _internal_mm_blendv_pd(rx_lo, ry_lo, cmp_result);

	__m128dx2 c;
	c.hi = _mm_add_pd(r_hi, r_lo);
	c.lo = _mm_add_pd(_mm_sub_pd(r_hi, c.hi), r_lo);
	return c;
}

/**
 * @brief Adds two __m128d values with the result stored as a __m128dx2
 */
static inline __m128dx2 _mm128x2_add_pd_pd(__m128d x, __m128d y) {
	__m128d r_hi = _mm_add_pd(x, y);

	__m128d rx_lo = _mm_add_pd(_mm_sub_pd(x, r_hi), y);
	__m128d ry_lo = _mm_add_pd(_mm_sub_pd(y, r_hi), x);

	const __m128d cmp_result = _mm_cmple_pd(
		_mm_fabs_pd(x), _mm_fabs_pd(y)
	);
	__m128d r_lo = _internal_mm_blendv_pd(rx_lo, ry_lo, cmp_result);

	__m128dx2 c;
	c.hi = _mm_add_pd(r_hi, r_lo);
	c.lo = _mm_add_pd(_mm_sub_pd(r_hi, c.hi), r_lo);
	return c;
}

static inline __m128dx2 _mm128x2_sub_pdx2_pd(__m128dx2 x, __m128d y) {
	__m128d r_hi = _mm_sub_pd(x.hi, y);

	__m128d rx_lo = _mm_add_pd(
		_mm_sub_pd(_mm_sub_pd(x.hi, r_hi), y), x.lo
	);

	y = _mm_negate_pd(y);
	__m128d ry_lo = _mm_add_pd(
		_mm_add_pd(_mm_sub_pd(/* negative */ y, r_hi), x.hi), x.lo
	);

	const __m128d cmp_result = _mm_cmple_pd(
		_mm_fabs_pd(x.hi), _mm_fabs_pd(y)
	);
	__m128d r_lo = _internal_mm_blendv_pd(rx_lo, ry_lo, cmp_result);

	__m128dx2 c;
	c.hi = _mm_add_pd(r_hi, r_lo);
	c.lo = _mm_add_pd(_mm_sub_pd(r_hi, c.hi), r_lo);
	return c;
}

static inline __m128dx2 _mm128x2_sub_pd_pdx2(__m128d x, __m128dx2 y) {
	__m128d r_hi = _mm_sub_pd(x, y.hi);

	__m128d rx_lo = _mm_sub_pd(
		_mm_sub_pd(_mm_sub_pd(x, r_hi), y.hi),
	y.lo);

	y.hi = _mm_negate_pd(y.hi);
	__m128d ry_lo = _mm_sub_pd(
		_mm_add_pd(_mm_sub_pd(/* negative */ y.hi, r_hi), x), y.lo
	);

	const __m128d cmp_result = _mm_cmple_pd(
		_mm_fabs_pd(x), _mm_fabs_pd(y.hi)
	);
	__m128d r_lo = _internal_mm_blendv_pd(rx_lo, ry_lo, cmp_result);

	__m128dx2 c;
	c.hi = _mm_add_pd(r_hi, r_lo);
	c.lo = _mm_add_pd(_mm_sub_pd(r_hi, c.hi), r_lo);
	return c;
}

/**
 * @brief Subtracts two __m128d values with the result stored as a __m128dx2
 */
static inline __m128dx2 _mm128x2_sub_pd_pd(__m128d x, __m128d y) {
	__m128d r_hi = _mm_sub_pd(x, y);

	__m128d rx_lo = _mm_sub_pd(_mm_sub_pd(x, r_hi), y);

	y = _mm_negate_pd(y);
	__m128d ry_lo = _mm_add_pd(_mm_sub_pd(/* negative */ y, r_hi), x);

	const __m128d cmp_result = _mm_cmple_pd(
		_mm_fabs_pd(x), _mm_fabs_pd(y)
	);
	__m128d r_lo = _internal_mm_blendv_pd(rx_lo, ry_lo, cmp_result);

	__m128dx2 c;
	c.hi = _mm_add_pd(r_hi, r_lo);
	c.lo = _mm_add_pd(_mm_sub_pd(r_hi, c.hi), r_lo);
	return c;
}

static inline __m128dx2 _mm128x2_mul_pdx2_pd(__m128dx2 x, __m128d y) {
	__m128dx2 t = _mm128x2_dekker_mul12_pd(x.hi, y);
	__m128d c = _mm_add_pd(_mm_mul_pd(x.lo, y), t.lo);

	__m128dx2 r;
	r.hi = _mm_add_pd(t.hi, c);
	r.lo = _mm_add_pd(_mm_sub_pd(t.hi, r.hi), c);
	return r;
}

static inline __m128dx2 _mm128x2_mul_pd_pdx2(__m128d x, __m128dx2 y) {
	__m128dx2 t = _mm128x2_dekker_mul12_pd(x, y.hi);
	__m128d c = _mm_add_pd(_mm_mul_pd(x, y.lo), t.lo);

	__m128dx2 r;
	r.hi = _mm_add_pd(t.hi, c);
	r.lo = _mm_add_pd(_mm_sub_pd(t.hi, r.hi), c);
	return r;
}

/**
 * @brief Multiplies two __m128d values with the result stored as a __m128dx2
 */
static inline __m128dx2 _mm128x2_mul_pd_pd(__m128d x, __m128d y) {
	return _mm128x2_dekker_mul12_pd(x, y);
}

static inline __m128dx2 _mm128x2_div_pdx2_pd(__m128dx2 x, __m128d y) {
	__m128d u = _mm_div_pd(x.hi, y);
	__m128dx2 t = _mm128x2_dekker_mul12_pd(u, y);
	__m128d l = _mm_div_pd(
		_mm_add_pd(_mm_sub_pd(_mm_sub_pd(x.hi, t.hi), t.lo), x.lo), y
	);

	__m128dx2 r;
	r.hi = _mm_add_pd(u, l);
	r.lo = _mm_add_pd(_mm_sub_pd(u, r.hi), l);
	return r;
}

static inline __m128dx2 _mm128x2_div_pd_pdx2(__m128d x, __m128dx2 y) {
	__m128d u = _mm_div_pd(x, y.hi);
	__m128dx2 t = _mm128x2_dekker_mul12_pd(u, y.hi);
	__m128d l = _mm_div_pd(_mm_sub_pd(
		_mm_sub_pd(_mm_sub_pd(x, t.hi), t.lo),
		_mm_mul_pd(u, y.lo)
	), y.hi);

	__m128dx2 r;
	r.hi = _mm_add_pd(u, l);
	r.lo = _mm_add_pd(_mm_sub_pd(u, r.hi), l);
	return r;
}

/**
 * @brief Divides two __m128d values with the result stored as a __m128dx2
 */
static inline __m128dx2 _mm128x2_div_pd_pd(__m128d x, __m128d y) {
	__m128d u = _mm_div_pd(x, y);
	__m128dx2 t = _mm128x2_dekker_mul12_pd(u, y);
	__m128d l = _mm_div_pd(
		_mm_sub_pd(_mm_sub_pd(x, t.hi), t.lo), y
	);

	__m128dx2 r;
	r.hi = _mm_add_pd(u, l);
	r.lo = _mm_add_pd(_mm_sub_pd(u, r.hi), l);
	return r;
}

/**
 * @brief Squares a __m128d value with the result stored as a __m128dx2
 */
static inline __m128dx2 _mm128x2_square_pd(__m128d x) {
	return _mm128x2_dekker_square12_pd(x);
}

/**
 * @brief Calculates the reciprocal of a __m128d value with the result stored
 * as a __m128dx2
 */
static inline __m128dx2 _mm128x2_recip_pd(__m128d y) {
	__m128d u = _mm_div_pd(_mm_set1_pd(1.0), y);
	__m128dx2 t = _mm128x2_dekker_mul12_pd(u, y);
	__m128d l = _mm_div_pd(
		_mm_sub_pd(_mm_sub_pd(_mm_set1_pd(1.0), t.hi), t.lo), y
	);

	__m128dx2 r;
	r.hi = _mm_add_pd(u, l);
	r.lo = _mm_add_pd(_mm_sub_pd(u, r.hi), l);
	return r;
}

//------------------------------------------------------------------------------
// __m128dx2 specialized arithmetic
//------------------------------------------------------------------------------

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero
 */
static inline __m128dx2 _mm128x2_mul_power2_pdx2_pd(__m128dx2 x, __m128d y) {
	x.hi = _mm_mul_pd(x.hi, y);
	x.lo = _mm_mul_pd(x.lo, y);
	return x;
}

/**
 * @brief Multiplies by a known power of two (such as 2.0, 0.5, etc.) or zero
 */
static inline __m128dx2 _mm128x2_mul_power2_pd_pdx2(__m128d x, __m128dx2 y) {
	y.hi = _mm_mul_pd(x, y.hi);
	y.lo = _mm_mul_pd(x, y.lo);
	return y;
}

//------------------------------------------------------------------------------
// __m128dx2 Mathematical Constants
//------------------------------------------------------------------------------

/**
 * @brief ~2.718281828 Returns the value of euler's number
 */
static inline __m128dx2 _mm128x2_const_e_pdx2(void) {
	const __m128dx2 ret = {
		_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x4005BF0A8B145769)),
		_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x3CA4D57EE2B1013A))
	};
	return ret;
}

/**
 * @brief ~1.442695041 Returns the value of log2(e)
 */
static inline __m128dx2 _mm128x2_const_log2e_pdx2(void) {
	const __m128dx2 ret = {
		_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x3FF71547652B82FE)),
		_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x3C7777D0FFDA0D24))
	};
	return ret;
}

/**
 * @brief ~0.434294482 Returns the value of log10(e)
 */
static inline __m128dx2 _mm128x2_const_log10e_pdx2(void) {
	const __m128dx2 ret = {
		_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x3FDBCB7B1526E50E)),
		_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x3C695355BAAAFAD3))
	};
	return ret;
}

/**
 * @brief ~3.141592654 Returns the value of pi
 */
static inline __m128dx2 _mm128x2_const_pi_pdx2(void) {
	const __m128dx2 ret = {
		_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x400921FB54442D18)),
		_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x3CA1A62633145C07))
	};
	return ret;
}

/**
 * @brief ~0.318309886 Returns the value of 1 / pi
 */
static inline __m128dx2 _mm128x2_const_inv_pi_pdx2(void) {
	const __m128dx2 ret = {
		_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x3FD45F306DC9C883)),
		_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0xBC76B01EC5417056))
	};
	return ret;
}

/**
 * @brief ~0.564189584 Returns the value of 1 / sqrt(pi)
 */
static inline __m128dx2 _mm128x2_const_inv_sqrtpi_pdx2(void) {
	const __m128dx2 ret = {
		_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x3FE20DD750429B6D)),
		_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x3C61AE3A914FED80))
	};
	return ret;
}

/**
 * @brief ~0.693147181 Returns the value of ln(2)
 */
static inline __m128dx2 _mm128x2_const_ln2_pdx2(void) {
	const __m128dx2 ret = {
		_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x3FE62E42FEFA39EF)),
		_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x3C7ABC9E3B39803F))
	};
	return ret;
}

/**
 * @brief ~2.302585093 Returns the value of ln(10)
 */
static inline __m128dx2 _mm128x2_const_ln10_pdx2(void) {
	const __m128dx2 ret = {
		_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x40026BB1BBB55516)),
		_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0xBCAF48AD494EA3E9))
	};
	return ret;
}

/**
 * @brief ~1.414213562 Returns the value of sqrt(2)
 */
static inline __m128dx2 _mm128x2_const_sqrt2_pdx2(void) {
	const __m128dx2 ret = {
		_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x3FF6A09E667F3BCD)),
		_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0xBC9BDD3413B26456))
	};
	return ret;
}

/**
 * @brief ~1.732050808 Returns the value of sqrt(3)
 */
static inline __m128dx2 _mm128x2_const_sqrt3_pdx2(void) {
	const __m128dx2 ret = {
		_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x3FFBB67AE8584CAA)),
		_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x3C9CEC95D0B5C1E3))
	};
	return ret;
}

/**
 * @brief ~0.577350269 Returns the value of 1 / sqrt(3)
 */
static inline __m128dx2 _mm128x2_const_inv_sqrt3_pdx2(void) {
	const __m128dx2 ret = {
		_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x3FE279A74590331C)),
		_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x3C834863E0792BED))
	};
	return ret;
}

/**
 * @brief ~0.577215665 Returns the value of gamma (The Euler–Mascheroni constant)
 */
static inline __m128dx2 _mm128x2_const_egamma_pdx2(void) {
	const __m128dx2 ret = {
		_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x3FE2788CFC6FB619)),
		_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0xBC56CB90701FBFAB))
	};
	return ret;
}

/**
 * @brief ~1.618033989 Returns the value of phi (The golden ratio)
 */
static inline __m128dx2 _mm128x2_const_phi_pdx2(void) {
	const __m128dx2 ret = {
		_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x3FF9E3779B97F4A8)),
		_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0xBC8F506319FCFD19))
	};
	return ret;
}

//------------------------------------------------------------------------------
// __m128dx2 floating point classify
//------------------------------------------------------------------------------

/* values */

	/**
	 * @brief Returns a __m128dx2 value set to positive infinity
	 */
	static inline __m128dx2 _mm128x2_get_infinity_pdx2(void) {
		__m128dx2 ret = {
			_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x7FF0000000000000)),
			_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x7FF0000000000000))
		};
		return ret;
	}

	/**
	 * @brief Returns a __m128dx2 value set to signaling NaN
	 */
	static inline __m128dx2 _mm128x2_get_sNaN_pdx2(void) {
		__m128dx2 ret = {
			_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x7FF0000000000001)),
			_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x7FF0000000000001))
		};
		return ret;
	}

	/**
	 * @brief Returns a __m128dx2 value set to quiet NaN
	 */
	static inline __m128dx2 _mm128x2_get_qNaN_pdx2(void) {
		__m128dx2 ret = {
			_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x7FF8000000000001)),
			_mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x7FF8000000000001))
		};
		return ret;
	}

/* Float Classify */

	/** @brief Returns true if x is negative */
	static inline __m128d _mm_signbit_pdx2(const __m128dx2 x) {
		return _mm_signbit_pd(x.hi);
	}

	/** @brief Returns true if x is finite */
	static inline __m128d _mm_isfinite_pdx2(const __m128dx2 x) {
		return _mm_isfinite_pd(x.hi);
	}

	/** @brief Returns true if x is +-infinity */
	static inline __m128d _mm_isinf_pdx2(const __m128dx2 x) {
		return _mm_isinf_pd(x.hi);
	}

	/** @brief Returns true if x is any kind of NaN */
	static inline __m128d _mm_isnan_pdx2(const __m128dx2 x) {
		return _mm_isnan_pd(x.hi);
	}

	/** @brief Returns true if x is normal */
	static inline __m128d _mm_isnormal_pdx2(const __m128dx2 x) {
		return _mm_and_pd(
			_mm_isnormal_pd(x.hi),
			_mm_or_pd(
				_mm_isnormal_pd(x.lo),
				_mm_cmpeq_pd(x.lo, _mm_setzero_pd())
			)
		);
	}

	/** @brief Returns true if x is denormal and non-zero */
	static inline __m128d _mm_isdenormal_pdx2(const __m128dx2 x) {
		return _mm_or_pd(
			_mm_isdenormal_pd(x.hi), _mm_isdenormal_pd(x.lo)
		);
	}

	/** @brief Returns true if x and y are unordered */
	static inline __m128d _mm_isunordered_pdx2(const __m128dx2 x, const __m128dx2 y) {
		return _mm_isunordered_pd(x.hi, y.hi);
	}

//------------------------------------------------------------------------------
// __m128dx2 max/min functions
//------------------------------------------------------------------------------

/**
 * @brief Returns the fmax of x and y. Correctly handling NaN and signed zeros.
 * You may use _mm128x2_max_pdx2 as a faster alternative.
 */
static inline __m128dx2 _mm128x2_fmax_pdx2(__m128dx2 x, __m128dx2 y) {
	__m128d fmax_cmp =
		_mm_or_pd(
			_mm_andnot_pd(
				_mm_or_pd(
					_mm_andnot_pd(
						_mm_signbit_pdx2(x),
						_mm_isnan_pdx2(y)
					),
					_mm_isnan_pdx2(x)
				),
				_mm_cmplt_pdx2(y, x)
			),
			_mm_cmplt_pdx2(x, y)
		);
	__m128dx2 ret;
	ret.hi = _internal_mm_blendv_pd(x.hi, y.hi, fmax_cmp);
	ret.lo = _internal_mm_blendv_pd(x.lo, y.lo, fmax_cmp);
	return ret;
}

/**
 * @brief Returns the fmin of x and y. Correctly handling NaN and signed zeros.
 * You may use _mm128x2_min_pdx2 as a faster alternative.
 */
static inline __m128dx2 _mm128x2_fmin_pdx2(__m128dx2 x, __m128dx2 y) {
	__m128d fmin_cmp =
		_mm_or_pd(
			_mm_andnot_pd(
				_mm_or_pd(
					_mm_andnot_pd(
						_mm_signbit_pdx2(x),
						_mm_isnan_pdx2(y)
					),
					_mm_isnan_pdx2(x)
				),
				_mm_cmpgt_pdx2(y, x)
			),
			_mm_cmpgt_pdx2(x, y)
		);
	__m128dx2 ret;
	ret.hi = _internal_mm_blendv_pd(x.hi, y.hi, fmin_cmp);
	ret.lo = _internal_mm_blendv_pd(x.lo, y.lo, fmin_cmp);
	return ret;
}

static inline __m128dx2 _mm128x2_max_pdx2(__m128dx2 x, __m128dx2 y) {
	const __m128d cmp_max = _mm_cmplt_pdx2(x, y);
	__m128dx2 ret;
	ret.hi = _internal_mm_blendv_pd(x.hi, y.hi, cmp_max);
	ret.lo = _internal_mm_blendv_pd(x.lo, y.lo, cmp_max);
	return ret;
}

static inline __m128dx2 _mm128x2_min_pdx2(__m128dx2 x, __m128dx2 y) {
	const __m128d cmp_max = _mm_cmpgt_pdx2(x, y);
	__m128dx2 ret;
	ret.hi = _internal_mm_blendv_pd(x.hi, y.hi, cmp_max);
	ret.lo = _internal_mm_blendv_pd(x.lo, y.lo, cmp_max);
	return ret;
}

//------------------------------------------------------------------------------
// __m128dx2 rounding functions
//------------------------------------------------------------------------------

#ifdef __SSE4_1__

/** same as aint(x) */
static inline __m128dx2 _mm128x2_trunc_pdx2(__m128dx2 x) {
	__m128d int_hi = _mm_trunc_pd(x.hi);
	__m128d int_lo = _mm_trunc_pd(x.lo);
	__m128d frac_hi = _mm_sub_pd(x.hi, int_hi);
	__m128d frac_lo = _mm_sub_pd(x.lo, int_lo);
	
	__m128d frac_ge_1 = _mm_cmpge_pd(_mm_add_pd(frac_hi, frac_lo), _mm_set1_pd(1.0));

	__m128dx2 trunc_all = _mm128x2_add_pdx2_pd(_mm128x2_add_pd_pd(
		_internal_mm_blendv_pd(_mm_setzero_pd(), _mm_set1_pd(1.0), frac_ge_1),
		int_lo
	), int_hi);
	return trunc_all;
}

static inline __m128dx2 _mm128x2_floor_pdx2(__m128dx2 x) {
	__m128dx2 int_part = _mm128x2_trunc_pdx2(x);
	
	__m128d cmp_floor;
	cmp_floor = _mm_and_pd(
		_mm_cmplt_pdx2(x, _mm128x2_setzero_pdx2()),
		_mm_cmpneq_pdx2(x, int_part)
	);
	__m128d floor_part = _internal_mm_blendv_pd(
		_mm_setzero_pd(), _mm_set1_pd(1.0), cmp_floor
	);
	return _mm128x2_sub_pdx2_pd(int_part, floor_part);
}

static inline __m128dx2 _mm128x2_ceil_pdx2(__m128dx2 x) {
	__m128dx2 int_part = _mm128x2_trunc_pdx2(x);
	
	__m128d cmp_ceil = _mm_and_pd(
		_mm_cmpgt_pdx2(x, _mm128x2_setzero_pdx2()),
		_mm_cmpneq_pdx2(x, int_part)
	);
	__m128d ceil_part = _internal_mm_blendv_pd(
		_mm_setzero_pd(), _mm_set1_pd(1.0), cmp_ceil
	);
	return _mm128x2_add_pdx2_pd(int_part, ceil_part);
}

/** same as nint(x) */
static inline __m128dx2 _mm128x2_round_pdx2(__m128dx2 x) {
	__m128dx2 round_up = _mm128x2_add_pdx2_pd(_mm128x2_floor_pdx2(x), _mm_set1_pd(0.5));
	__m128dx2 round_dn = _mm128x2_sub_pdx2_pd(_mm128x2_ceil_pdx2 (x), _mm_set1_pd(0.5));
	__m128d cmp_mask = _mm_cmplt_pdx2(x, _mm128x2_setzero_pdx2());
	__m128dx2 ret;
	ret.hi = _internal_mm_blendv_pd(round_up.hi, round_dn.hi, cmp_mask);
	ret.lo = _internal_mm_blendv_pd(round_up.lo, round_dn.lo, cmp_mask);
	return ret;
}

#endif

//------------------------------------------------------------------------------
// __m128dx2 math.h functions
//------------------------------------------------------------------------------

static inline __m128dx2 _mm128x2_fabs_pdx2(__m128dx2 x) {
	const __m128d sign_mask = _mm_and_pd(
		x.hi,
		_mm_get_sign_mask_pd()
	);
	x.hi = _mm_xor_pd(x.hi, sign_mask);
	x.lo = _mm_xor_pd(x.lo, sign_mask);
	return x;
}

static inline __m128dx2 _mm128x2_fdim_pdx2(__m128dx2 x, __m128dx2 y) {
	__m128dx2 ret;
	ret = _mm128x2_sub_pdx2(x, y);
	// returns true when ret > 0.0 or ret is NaN
	__m128d cmp_nle = _mm_cmpnle_zero_pdx2(ret);
	// NaN remains NaN, and -0.0 becomes +0.0
	ret.hi = _mm_and_pd(ret.hi, cmp_nle);
	ret.lo = _mm_and_pd(ret.lo, cmp_nle);
	return ret;
}

static inline __m128dx2 _mm128x2_copysign_pdx2(__m128dx2 x, __m128dx2 y) {
	const __m128d sign_mask = _mm_and_pd(
		_mm_xor_pd(x.hi, y.hi),
		_mm_get_sign_mask_pd()
	);
	x.hi = _mm_xor_pd(x.hi, sign_mask);
	x.lo = _mm_xor_pd(x.lo, sign_mask);
	return x;
}

static inline __m128dx2 _mm128x2_copysign_pdx2_pd(__m128dx2 x, __m128d y) {
	const __m128d sign_mask = _mm_and_pd(
		_mm_xor_pd(x.hi, y),
		_mm_get_sign_mask_pd()
	);
	x.hi = _mm_xor_pd(x.hi, sign_mask);
	x.lo = _mm_xor_pd(x.lo, sign_mask);
	return x;
}

static inline __m128dx2 _mm128x2_sqrt_pdx2(__m128dx2 x) {
	__m128d guess = _mm_sqrt_pd(x.hi);
	return _mm128x2_and_pdx2(
		_mm128x2_mul_power2_pdx2_pd(
			_mm128x2_add_pd_pdx2(guess, _mm128x2_div_pdx2_pd(x, guess)),
			_mm_set1_pd(0.5)
		),
		// returns 0.0 on division by 0.0
		_mm128x2_cmp_extend_pd(
			_mm_cmpneq_pd(guess, _mm_setzero_pd())
		)
	);
}

#if 0
/* Unimplemented */

static inline __m128dx2 _mm128x2_cbrt_pdx2(__m128dx2 x) {
	__m128d guess = _mm_cbrt_pd(x.hi);
	return _mm128x2_and_pdx2(
		_mm128x2_div_pdx2_pd(
			_mm128x2_add_pd_pdx2(
				_mm_mul_pd(
					_mm_set1_pd(2.0), guess
				),
				_mm128x2_div_pdx2(x, _mm128x2_square_pd(guess))
			),
			_mm_set1_pd(3.0)
		),
		// returns 0.0 on division by 0.0
		_mm128x2_cmp_extend_pd(
			_mm_cmpneq_pd(guess, _mm_setzero_pd())
		)
	);
}

#endif

#ifdef __SSE4_1__

/**
 * @brief returns the fractional part of a __m128dx2 value.
 * @note int_part cannot not be NULL
 */
static inline __m128dx2 _mm128x2_modf_pdx2(__m128dx2 x, __m128dx2* int_part) {
	__m128dx2 trunc_part = _mm128x2_trunc_pdx2(x);
	*int_part = trunc_part;
	return _mm128x2_sub_pdx2(x, trunc_part);
}

static inline __m128dx2 _mm128x2_fmod_pdx2(__m128dx2 x, __m128dx2 y) {
	__m128dx2 trunc_part = _mm128x2_trunc_pdx2(_mm128x2_div_pdx2(x, y));
	return _mm128x2_sub_pdx2(x, _mm128x2_mul_pdx2(y, trunc_part));
}

#endif

//------------------------------------------------------------------------------
// __m128dx2 ilogb
//------------------------------------------------------------------------------

#if defined(__SSE4_1__) && defined(__SSE4_2__)

/**
 * @brief Computes ilogb(x) on a __m128dx2 value
 * @returns __m128i int64_t
 */
static inline __m128i _mm128x2_ilogb_pdx2_epi64(__m128dx2 x) {
	return _mm_ilogb_pd_epi64(x.hi);
}

#endif

//------------------------------------------------------------------------------
// __m128dx2 ldexp
//------------------------------------------------------------------------------

#if defined(__SSE4_1__) && defined(__SSE4_2__)

/**
 * @brief Computes ldexp(x, expon)
 */
static inline __m128dx2 _mm128x2_ldexp_pdx2_epi64(__m128dx2 x, __m128i expon) {
	x.hi = _mm_ldexp_pd_epi64(x.hi, expon);
	x.lo = _mm_ldexp_pd_epi64(x.lo, expon);
	return x;
}

#endif

//------------------------------------------------------------------------------
// __m128dx2 frexp
//------------------------------------------------------------------------------

#if defined(__SSE4_1__) && defined(__SSE4_2__)

/**
 * @brief Computes frexp(x, expon) on a __m128dx2 value
 * @returns sign extended __m128i int64_t
 */
static inline __m128dx2 _mm128x2_frexp_pdx2_epi64(__m128dx2 x, __m128i* const expon) {
	x.hi = _mm_frexp_pd_epi64(x.hi, expon);
	x.lo = _mm_ldexp_pd_epi64(x.lo, _mm_sub_epi64(_mm_set1_epi64x((int64_t)1), *expon));
	return x;
}

#endif

#ifdef __cplusplus
}
#endif

#endif /* FLOAT64X2_SSE2_H */
