/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#include "../../util_mpfr/MPFR_Float.hpp"
#include "../../util_mpfr/mpfr_convert.hpp"

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
#include <limits>
#include <stdio.h>
#include <cstdio>

#if 0
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
#if 1
mpfr_printf("%s %.40Re\n", label, src.value);
#else
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
#endif
}

template<typename FloatX>
void generate_constants(const char* name) {
	FloatMPFR num;
	#if 1
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

#else

template<typename FloatX, typename FloatBase>
void output_constant(const char* label, __attribute__((unused)) const char* name, FloatMPFR src, const char* comment = nullptr) {
	constexpr bool enable_comment = true;
	const int label_width = 14;
	(void)label_width; // Gets rid of unused variable warnings
#if 0
	#if 0
		mpfr_printf(
			"template<typename T> inline constexpr T const_%-*s();",
			label_width, label
		);
		printf(" /**< ~%.9Lf", mpfr_get_ld(src.value, MPFR_RNDN));
		if (comment != nullptr && enable_comment) { printf(" %s", comment); }
		printf(" */\n");
	#else
		printf("/** ~%.9Lf", mpfr_get_ld(src.value, MPFR_RNDN));
		if (comment != nullptr && enable_comment) { printf(" %s", comment); }
		printf(" */\n");
		#if 0

		mpfr_printf(
			"template<> inline constexpr long double const_%-*s<long double>() { return %.40ReL; }\n",
			label_width, label, src.value
		);
		#elif 0
		mpfr_printf(
			"template<> inline constexpr double const_%-*s<double>() { return %.21Re; }\n",
			label_width, label, src.value
		);
		#else
		mpfr_printf(
			"template<> inline constexpr float const_%-*s<float>() { return %.11Ref; }\n",
			label_width, label, src.value
		);
		#endif
	#endif
#else
	FloatX dst_value = mpfr_get_type<FloatX>(src.value, MPFR_RNDN);
	const FloatBase* dst = reinterpret_cast<FloatBase*>(&dst_value);
	const int precision = std::numeric_limits<FloatBase>::max_digits10 + 1;
	const int width = 7 + precision;
	
	printf("/** ~%.9Lf", mpfr_get_ld(src.value, MPFR_RNDN));
	if (comment != nullptr && enable_comment) { printf(" %s", comment); }
	printf(" */\n");
	
	printf(
		"template<> inline constexpr %s const_%-s<%s>() { return {\n",
		name, label, name
	);
	for (int i = 0; i < 6; i++) {
		char dst_buf[999];
		if (i != 0) { printf(",\n"); }
		snprintf(dst_buf, sizeof(dst_buf), "\t%-+*.*e", width, precision, dst[i]);
		printf("%s", dst_buf);
	};
	printf("\n}; }\n\n");
#endif
}

static const char lemniscate_const_text[] =
"2.622057554292119810464839589891119413682754951431623162816821703800790587070"\
"41425023029553296142909344613575267178321805560895690139393569470111943477523"\
"58404226414971649069519368999799321460723831213908102062218974296008565545398";

template<typename FloatX, typename FloatBase>
void generate_constants(const char* name) {
	FloatMPFR num;
	FloatMPFR temp;
	constexpr bool print_headings = true;
	const char prefix_ln[] = "\n";
	const char suffix_ln[] = "\n\n";

if (print_headings) { printf("%s/* Multiples of pi*/%s", prefix_ln, suffix_ln); }

	mpfr_const_pi(num.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("pi", name, num);

	mpfr_mul_d(num.value, num.value, 2.0, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("2pi", name, num, "`2 * pi`");

	mpfr_div_d(num.value, num.value, 4.0, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("pi2", name, num, "`1/2 * pi`");

	mpfr_div_d(num.value, num.value, 2.0, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("pi4", name, num, "`1/4 * pi`");

	mpfr_mul_d(num.value, num.value, 3.0, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("3pi4", name, num, "`3/4 * pi`");

	mpfr_const_pi(num.value, MPFR_RNDN);
	mpfr_div_d(num.value, num.value, 3.0, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("pi3", name, num, "`1/3 * pi`");

if (print_headings) { printf("%s/* Inverse and sqrt pi */%s", prefix_ln, suffix_ln); }

	mpfr_const_pi(num.value, MPFR_RNDN);
	mpfr_d_div(num.value, 1.0, num.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("inv_pi", name, num, "`1 / pi`");

	mpfr_div_d(num.value, num.value, 2.0, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("inv_2pi", name, num, "`1 / 2pi`");

/* sqrtpi constants */

	mpfr_const_pi(num.value, MPFR_RNDN);
	mpfr_sqrt(num.value, num.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("sqrtpi", name, num, "`sqrt(pi)`");

	mpfr_const_pi(num.value, MPFR_RNDN);
	mpfr_mul_d(num.value, num.value, 2.0, MPFR_RNDN);
	mpfr_sqrt(num.value, num.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("sqrt2pi", name, num, "`sqrt(2pi)`");

/* inv_sqrtpi constants */

	mpfr_const_pi(num.value, MPFR_RNDN);
	mpfr_sqrt(num.value, num.value, MPFR_RNDN);
	mpfr_d_div(num.value, 1.0, num.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("inv_sqrtpi", name, num, "`1 / sqrt(pi)`");

	mpfr_const_pi(num.value, MPFR_RNDN);
	mpfr_mul_d(num.value, num.value, 2.0, MPFR_RNDN);
	mpfr_sqrt(num.value, num.value, MPFR_RNDN);
	mpfr_d_div(num.value, 1.0, num.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("inv_sqrt2pi", name, num, "`1 / sqrt(2pi)`");

if (print_headings) { printf("%s/* Logarithms and Exponents */%s", prefix_ln, suffix_ln); }

	num = 1.0;
	mpfr_exp(num.value, num.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("e", name, num, "Eulers number");
	mpfr_d_div(num.value, 1.0, num.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("inv_e", name, num, "`1 / e`");

	mpfr_const_log2(num.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("ln2", name, num, "`ln(2)`");

	num = 3.0;
	mpfr_log(num.value, num.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("ln3", name, num, "`ln(3)`");

	num = 10.0;
	mpfr_log(num.value, num.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("ln10", name, num, "`ln(10)`");

	mpfr_const_log2(num.value, MPFR_RNDN);
	mpfr_d_div(num.value, 1.0, num.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("log2e", name, num, "`log2(e)`");

	num = 3.0;
	mpfr_log(num.value, num.value, MPFR_RNDN);
	mpfr_d_div(num.value, 1.0, num.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("log3e", name, num, "`log3(e)`");

	num = 10.0;
	mpfr_log(num.value, num.value, MPFR_RNDN);
	mpfr_d_div(num.value, 1.0, num.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("log10e", name, num, "`log10(e)`");

	// num = 10.0;
	// mpfr_log2(num.value, num.value, MPFR_RNDN);
	// output_constant<FloatX, FloatBase>("log2_10", name, num);

	// num = 2.0;
	// mpfr_log10(num.value, num.value, MPFR_RNDN);
	// output_constant<FloatX, FloatBase>("log10_2", name, num);

if (print_headings) { printf("%s/* Square Roots */%s", prefix_ln, suffix_ln); }

	num = 2.0;
	mpfr_sqrt(num.value, num.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("sqrt2", name, num, "`sqrt(2)`");

	num = 3.0;
	mpfr_sqrt(num.value, num.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("sqrt3", name, num, "`sqrt(3)`");

	num = 5.0;
	mpfr_sqrt(num.value, num.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("sqrt5", name, num, "`sqrt(5)`");

	num = 6.0;
	mpfr_sqrt(num.value, num.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("sqrt6", name, num, "`sqrt(6)`");

/* Inverse Square Roots */

	num = 2.0;
	mpfr_sqrt(num.value, num.value, MPFR_RNDN);
	mpfr_d_div(num.value, 1.0, num.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("inv_sqrt2", name, num, "`1 / sqrt(2)` or `1/2 * sqrt(2)`");

	num = 3.0;
	mpfr_sqrt(num.value, num.value, MPFR_RNDN);
	mpfr_d_div(num.value, 1.0, num.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("inv_sqrt3", name, num, "`1 / sqrt(3)`");

	num = 5.0;
	mpfr_sqrt(num.value, num.value, MPFR_RNDN);
	mpfr_d_div(num.value, 1.0, num.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("inv_sqrt5", name, num, "`1 / sqrt(5)`");

	num = 6.0;
	mpfr_sqrt(num.value, num.value, MPFR_RNDN);
	mpfr_d_div(num.value, 1.0, num.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("inv_sqrt6", name, num, "`1 / sqrt(6)`");

if (print_headings) { printf("%s/* Cube Roots */%s", prefix_ln, suffix_ln); }

	num = 2.0;
	mpfr_cbrt(num.value, num.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("cbrt2", name, num, "`cbrt(2)`");

	num = 3.0;
	mpfr_cbrt(num.value, num.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("cbrt3", name, num, "`cbrt(3)`");

	num = 5.0;
	mpfr_cbrt(num.value, num.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("cbrt5", name, num, "`cbrt(5)`");

	num = 6.0;
	mpfr_cbrt(num.value, num.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("cbrt6", name, num, "`cbrt(6)`");

/* Inverse Cube Roots */

	num = 2.0;
	mpfr_cbrt(num.value, num.value, MPFR_RNDN);
	mpfr_d_div(num.value, 1.0, num.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("inv_cbrt2", name, num, "`1 / cbrt(2)`");

	num = 3.0;
	mpfr_cbrt(num.value, num.value, MPFR_RNDN);
	mpfr_d_div(num.value, 1.0, num.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("inv_cbrt3", name, num, "`1 / cbrt(3)`");

	num = 5.0;
	mpfr_cbrt(num.value, num.value, MPFR_RNDN);
	mpfr_d_div(num.value, 1.0, num.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("inv_cbrt5", name, num, "`1 / cbrt(5)`");

	num = 6.0;
	mpfr_cbrt(num.value, num.value, MPFR_RNDN);
	mpfr_d_div(num.value, 1.0, num.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("inv_cbrt6", name, num, "`1 / cbrt(6)`");

if (print_headings) { printf("%s/* Additional Mathematical Constants */%s", prefix_ln, suffix_ln); }

	mpfr_const_euler(num.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("egamma", name, num, "Euler-Mascheroni constant");

	num = 5.0;
	mpfr_sqrt(num.value, num.value, MPFR_RNDN);
	mpfr_add_d(num.value, num.value, 1.0, MPFR_RNDN);
	mpfr_div_d(num.value, num.value, 2.0, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("phi", name, num, "Golden Ratio");

	num = 33.0;
	mpfr_sqrt(num.value, num.value, MPFR_RNDN);
	mpfr_mul_d(num.value, num.value, 3.0, MPFR_RNDN);
	mpfr_d_sub(temp.value, 19.0, num.value, MPFR_RNDN);
	mpfr_cbrt(temp.value, temp.value, MPFR_RNDN);
	mpfr_add_d(num.value, num.value, 19.0, MPFR_RNDN);
	mpfr_cbrt(num.value, num.value, MPFR_RNDN);
	mpfr_add(num.value, num.value, temp.value, MPFR_RNDN);
	mpfr_add_d(num.value, num.value, 1.0, MPFR_RNDN);
	mpfr_div_d(num.value, num.value, 3.0, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("tribonacci", name, num);

	mpfr_d_div(num.value, 1.0, num.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("inv_tribonacci", name, num, "`1 / tribonacci`");

	mpfr_const_catalan(num.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("catalan", name, num);

	mpfr_zeta_ui(num.value, 3.0, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("apery", name, num, "`zeta(3)`");

	num = -1.0;
	mpfr_eint(num.value, num.value, MPFR_RNDN);
	temp = 1.0;
	mpfr_exp(temp.value, temp.value, MPFR_RNDN);
	mpfr_mul_d(temp.value, temp.value, -1.0, MPFR_RNDN);
	mpfr_mul(num.value, num.value, temp.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("gompertz", name, num, "`-e * eint(-1)`");

	mpfr_set_str(num.value, lemniscate_const_text, 10, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("lemniscate", name, num);

	mpfr_mul_d(num.value, num.value, 2.0, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("2lemniscate", name, num, "`2 * lemniscate`");

	mpfr_div_d(num.value, num.value, 4.0, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("lemniscate2", name, num, "`1/2 * lemniscate`");

	mpfr_const_pi(temp.value, MPFR_RNDN);
	mpfr_set_str(num.value, lemniscate_const_text, 10, MPFR_RNDN);
	mpfr_div(num.value, num.value, temp.value, MPFR_RNDN);
	output_constant<FloatX, FloatBase>("gauss", name, num, "`lemniscate / pi`");

}

#endif
