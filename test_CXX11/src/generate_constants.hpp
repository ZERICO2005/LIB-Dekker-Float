/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#include "util_mpfr/MPFR_Float.hpp"
#include "util_mpfr/mpfr_convert.hpp"

// template<typename FloatX>
// FloatX FloatMPFR_to_FloatX(FloatMPFR src) {
// 	FloatX dst;
// 	dst.hi = mpfr_get_d(src.value, MPFR_RNDN);
// 	FloatMPFR dst_temp;
// 	mpfr_set_d(dst_temp.value, dst.hi, MPFR_RNDN);
// 	mpfr_sub(src.value, src.value, dst_temp.value, MPFR_RNDN);
// 	dst.lo = mpfr_get_d(src.value, MPFR_RNDN);
// 	return dst;
// }

#include <cstdint>
#include <cinttypes>
#include <stdio.h>
#include <cstdio>

template<typename FloatX>
void output_constant_SIMD(const char* label, FloatX dst) {
	#if 0
		uint32_t* dst_bin = reinterpret_cast<uint32_t*>(dst.val);
		#if 0
			// Float32 SSE2
			printf(
				"\n\n__m128x4 _mm128x4_const_%s_psx4(void) {\n"
				"    __m128x4 ret = {\n"\
				"        _mm_castsi128_ps(_mm_set1_epi32(0x%08" PRIX32 ")),\n"\
				"        _mm_castsi128_ps(_mm_set1_epi32(0x%08" PRIX32 ")),\n"\
				"        _mm_castsi128_ps(_mm_set1_epi32(0x%08" PRIX32 ")),\n"\
				"        _mm_castsi128_ps(_mm_set1_epi32(0x%08" PRIX32 "))\n"\
				"    };\n"\
				"    return ret;\n"\
				"}\n",
				label, dst_bin[0], dst_bin[1], dst_bin[2], dst_bin[3]
			);
		#elif 0
			// Float32 AVX
			printf(
				"\n\n__m256x4 _mm256x4_const_%s_psx4(void) {\n"
				"    __m256x4 ret = {\n"\
				"        _mm256_castsi256_ps(_mm256_set1_epi32(0x%08" PRIX32 ")),\n"\
				"        _mm256_castsi256_ps(_mm256_set1_epi32(0x%08" PRIX32 ")),\n"\
				"        _mm256_castsi256_ps(_mm256_set1_epi32(0x%08" PRIX32 ")),\n"\
				"        _mm256_castsi256_ps(_mm256_set1_epi32(0x%08" PRIX32 "))\n"\
				"    };\n"\
				"    return ret;\n"\
				"}\n",
				label, dst_bin[0], dst_bin[1], dst_bin[2], dst_bin[3]
			);
		#elif 0
			// Float32 AVX512F
			printf(
				"\n\n__m512x4 _mm512x4_const_%s_psx4(void) {\n"
				"    __m512x4 ret = {\n"\
				"        _mm512_castsi512_ps(_mm512_set1_epi32(0x%08" PRIX32 ")),\n"\
				"        _mm512_castsi512_ps(_mm512_set1_epi32(0x%08" PRIX32 ")),\n"\
				"        _mm512_castsi512_ps(_mm512_set1_epi32(0x%08" PRIX32 ")),\n"\
				"        _mm512_castsi512_ps(_mm512_set1_epi32(0x%08" PRIX32 "))\n"\
				"    };\n"\
				"    return ret;\n"\
				"}\n",
				label, dst_bin[0], dst_bin[1], dst_bin[2], dst_bin[3]
			);
		#endif
	#elif 1
		uint64_t* dst_bin = reinterpret_cast<uint64_t*>(dst.val);
		#if 0
			// Float64 SSE2
			printf(
				"\n\n__m128dx4 _mm128x4_const_%s_pdx4(void) {\n"
				"    __m128dx4 ret = {\n"\
				"        _mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x%016" PRIX64 ")),\n"\
				"        _mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x%016" PRIX64 ")),\n"\
				"        _mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x%016" PRIX64 ")),\n"\
				"        _mm_castsi128_pd(_mm_set1_epi64x((int64_t)0x%016" PRIX64 "))\n"\
				"    };\n"\
				"    return ret;\n"\
				"}\n",
				label, dst_bin[0], dst_bin[1], dst_bin[2], dst_bin[3]
			);
		#elif 0
			// Float64 AVX
			printf(
				"\n\n__m256dx4 _mm256x4_const_%s_pdx4(void) {\n"
				"    __m256dx4 ret = {\n"\
				"        _mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x%016" PRIX64 ")),\n"\
				"        _mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x%016" PRIX64 ")),\n"\
				"        _mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x%016" PRIX64 ")),\n"\
				"        _mm256_castsi256_pd(_mm256_set1_epi64x((int64_t)0x%016" PRIX64 "))\n"\
				"    };\n"\
				"    return ret;\n"\
				"}\n",
				label, dst_bin[0], dst_bin[1], dst_bin[2], dst_bin[3]
			);
		#elif 1
			// Float64 AVX512F
			printf(
				"\n\n__m512dx4 _mm512x4_const_%s_pdx4(void) {\n"
				"    __m512dx4 ret = {\n"\
				"        _mm512_castsi512_pd(_mm512_set1_epi64((int64_t)0x%016" PRIX64 ")),\n"\
				"        _mm512_castsi512_pd(_mm512_set1_epi64((int64_t)0x%016" PRIX64 ")),\n"\
				"        _mm512_castsi512_pd(_mm512_set1_epi64((int64_t)0x%016" PRIX64 ")),\n"\
				"        _mm512_castsi512_pd(_mm512_set1_epi64((int64_t)0x%016" PRIX64 "))\n"\
				"    };\n"\
				"    return ret;\n"\
				"}\n",
				label, dst_bin[0], dst_bin[1], dst_bin[2], dst_bin[3]
			);
		#endif
	#endif
}

template<typename FloatX>
void output_constant(const char* label, __attribute__((unused)) const char* name, FloatMPFR src) {
	FloatX dst = mpfr_get_type<FloatX>(src.value, MPFR_RNDN);
	#if 0
	output_constant_SIMD(label, dst);
	#elif 1
		#if 0
		printf(
			"template<> inline constexpr %s %-12s <%s> = "\
			"{%-16.7a, %+-17.7a, %+-17.7a, %+-17.7a};\n",
			name, label, name, dst.val[0], dst.val[1], dst.val[2], dst.val[3]
		);
		#elif 1
		printf(
			"template<> inline constexpr %s %-12s <%s> = "\
			"{%-22.13a, %+-23.13a, %+-23.13a, %+-23.13a};\n",
			name, label, name, dst.val[0], dst.val[1], dst.val[2], dst.val[3]
		);
		#endif
	#elif 0
		char dst_hi[999];
		char dst_lo[999];
		quadmath_snprintf(dst_hi, sizeof(dst_hi), "%+-39.29Qa", dst.hi);
		quadmath_snprintf(dst_lo, sizeof(dst_lo), "%+-39.29Qa", dst.lo);
		printf(
			"template<> inline constexpr Float64x2 %-12s <Float64x2> = "\
			"{%s, %s};\n",
			label, dst_hi, dst_lo
		);
	#endif
}

template<typename FloatX>
void generate_constants(const char* name) {
	FloatMPFR num;
	#if 0
	// e_v
	num = 1.0;
	mpfr_exp(num.value, num.value, MPFR_RNDN);
	output_constant<FloatX>("e_v         ", name, num);

	// log2e_v
	num = 1.0;
	mpfr_exp(num.value, num.value, MPFR_RNDN);
	mpfr_log2(num.value, num.value, MPFR_RNDN);
	output_constant<FloatX>("log2e_v     ", name, num);

	// log10e_v
	num = 1.0;
	mpfr_exp(num.value, num.value, MPFR_RNDN);
	mpfr_log10(num.value, num.value, MPFR_RNDN);
	output_constant<FloatX>("log10e_v    ", name, num);

	// pi_v
	mpfr_const_pi(num.value, MPFR_RNDN);
	output_constant<FloatX>("pi_v        ", name, num);

	// inv_pi_v
	mpfr_const_pi(num.value, MPFR_RNDN);
	mpfr_d_div(num.value, 1.0, num.value, MPFR_RNDN);
	output_constant<FloatX>("inv_pi_v    ", name, num);

	// inv_sqrtpi_v
	mpfr_const_pi(num.value, MPFR_RNDN);
	mpfr_sqrt(num.value, num.value, MPFR_RNDN);
	mpfr_d_div(num.value, 1.0, num.value, MPFR_RNDN);
	output_constant<FloatX>("inv_sqrtpi_v", name, num);
	
	// log2e_v
	mpfr_const_log2(num.value, MPFR_RNDN);
	output_constant<FloatX>("ln2_v       ", name, num);

	// log10e_v
	num = 10.0;
	mpfr_log(num.value, num.value, MPFR_RNDN);
	output_constant<FloatX>("ln10_v      ", name, num);

	// sqrt2_v
	num = 2.0;
	mpfr_sqrt(num.value, num.value, MPFR_RNDN);
	output_constant<FloatX>("sqrt2_v     ", name, num);

	// sqrt3_v
	num = 3.0;
	mpfr_sqrt(num.value, num.value, MPFR_RNDN);
	output_constant<FloatX>("sqrt3_v     ", name, num);

	// inv_sqrt3_v
	num = 3.0;
	mpfr_sqrt(num.value, num.value, MPFR_RNDN);
	mpfr_d_div(num.value, 1.0, num.value, MPFR_RNDN);
	output_constant<FloatX>("inv_sqrt3_v ", name, num);

	// egamma_v
	mpfr_const_euler(num.value, MPFR_RNDN);
	output_constant<FloatX>("egamma_v    ", name, num);

	// phi_v
	num = 5.0;
	mpfr_sqrt(num.value, num.value, MPFR_RNDN);
	mpfr_add_d(num.value, num.value, 1.0, MPFR_RNDN);
	mpfr_div_d(num.value, num.value, 2.0, MPFR_RNDN);
	output_constant<FloatX>("phi_v       ", name, num);

	#else
		// e_v
	num = 1.0;
	mpfr_exp(num.value, num.value, MPFR_RNDN);
	output_constant<FloatX>("e", name, num);

	// log2e_v
	num = 1.0;
	mpfr_exp(num.value, num.value, MPFR_RNDN);
	mpfr_log2(num.value, num.value, MPFR_RNDN);
	output_constant<FloatX>("log2e", name, num);

	// log10e_v
	num = 1.0;
	mpfr_exp(num.value, num.value, MPFR_RNDN);
	mpfr_log10(num.value, num.value, MPFR_RNDN);
	output_constant<FloatX>("log10e", name, num);

	// pi_v
	mpfr_const_pi(num.value, MPFR_RNDN);
	output_constant<FloatX>("pi", name, num);

	// inv_pi_v
	mpfr_const_pi(num.value, MPFR_RNDN);
	mpfr_d_div(num.value, 1.0, num.value, MPFR_RNDN);
	output_constant<FloatX>("inv_pi", name, num);

	// inv_sqrtpi_v
	mpfr_const_pi(num.value, MPFR_RNDN);
	mpfr_sqrt(num.value, num.value, MPFR_RNDN);
	mpfr_d_div(num.value, 1.0, num.value, MPFR_RNDN);
	output_constant<FloatX>("inv_sqrtpi", name, num);
	
	// log2e_v
	mpfr_const_log2(num.value, MPFR_RNDN);
	output_constant<FloatX>("ln2", name, num);

	// log10e_v
	num = 10.0;
	mpfr_log(num.value, num.value, MPFR_RNDN);
	output_constant<FloatX>("ln10", name, num);

	// sqrt2_v
	num = 2.0;
	mpfr_sqrt(num.value, num.value, MPFR_RNDN);
	output_constant<FloatX>("sqrt2", name, num);

	// sqrt3_v
	num = 3.0;
	mpfr_sqrt(num.value, num.value, MPFR_RNDN);
	output_constant<FloatX>("sqrt3", name, num);

	// inv_sqrt3_v
	num = 3.0;
	mpfr_sqrt(num.value, num.value, MPFR_RNDN);
	mpfr_d_div(num.value, 1.0, num.value, MPFR_RNDN);
	output_constant<FloatX>("inv_sqrt3", name, num);

	// egamma_v
	mpfr_const_euler(num.value, MPFR_RNDN);
	output_constant<FloatX>("egamma", name, num);

	// phi_v
	num = 5.0;
	mpfr_sqrt(num.value, num.value, MPFR_RNDN);
	mpfr_add_d(num.value, num.value, 1.0, MPFR_RNDN);
	mpfr_div_d(num.value, num.value, 2.0, MPFR_RNDN);
	output_constant<FloatX>("phi", name, num);
	#endif
}
