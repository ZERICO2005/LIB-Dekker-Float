/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#include "MPFR_Float.hpp"

template<typename FloatX>
FloatX FloatMPFR_to_FloatX(FloatMPFR src) {
	FloatX dst;
	dst.hi = mpfr_get_d(src.value, MPFR_RNDN);
	FloatMPFR dst_temp;
	mpfr_set_d(dst_temp.value, dst.hi, MPFR_RNDN);
	mpfr_sub(src.value, src.value, dst_temp.value, MPFR_RNDN);
	dst.lo = mpfr_get_d(src.value, MPFR_RNDN);
	return dst;
}

template<typename FloatX>
void output_constant(const char* label, FloatMPFR src) {
	FloatX dst = FloatMPFR_to_FloatX<FloatX>(src);
	
	#if 1
		printf(
			"template<> inline constexpr Float64x2 %-12s <Float64x2> = "\
			"{%+-24.14a, %+-24.14a};\n",
			label, dst.hi, dst.lo
		);
	#else
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
void generate_constants() {
	FloatMPFR num;

	// e_v
	num = 1.0;
	mpfr_exp(num.value, num.value, MPFR_RNDN);
	output_constant<FloatX>("e_v         ", num);

	// log2e_v
	num = 1.0;
	mpfr_exp(num.value, num.value, MPFR_RNDN);
	mpfr_log2(num.value, num.value, MPFR_RNDN);
	output_constant<FloatX>("log2e_v     ", num);

	// log10e_v
	num = 1.0;
	mpfr_exp(num.value, num.value, MPFR_RNDN);
	mpfr_log10(num.value, num.value, MPFR_RNDN);
	output_constant<FloatX>("log10e_v    ", num);

	// pi_v
	mpfr_const_pi(num.value, MPFR_RNDN);
	output_constant<FloatX>("pi_v        ", num);

	// inv_pi_v
	mpfr_const_pi(num.value, MPFR_RNDN);
	mpfr_d_div(num.value, 1.0, num.value, MPFR_RNDN);
	output_constant<FloatX>("inv_pi_v    ", num);

	// inv_sqrtpi_v
	mpfr_const_pi(num.value, MPFR_RNDN);
	mpfr_sqrt(num.value, num.value, MPFR_RNDN);
	mpfr_d_div(num.value, 1.0, num.value, MPFR_RNDN);
	output_constant<FloatX>("inv_sqrtpi_v", num);
	
	// log2e_v
	mpfr_const_log2(num.value, MPFR_RNDN);
	output_constant<FloatX>("ln2_v       ", num);

	// log10e_v
	num = 10.0;
	mpfr_log(num.value, num.value, MPFR_RNDN);
	output_constant<FloatX>("ln10_v      ", num);

	// sqrt2_v
	num = 2.0;
	mpfr_sqrt(num.value, num.value, MPFR_RNDN);
	output_constant<FloatX>("sqrt2_v     ", num);

	// sqrt3_v
	num = 3.0;
	mpfr_sqrt(num.value, num.value, MPFR_RNDN);
	output_constant<FloatX>("sqrt3_v     ", num);

	// inv_sqrt3_v
	num = 3.0;
	mpfr_sqrt(num.value, num.value, MPFR_RNDN);
	mpfr_d_div(num.value, 1.0, num.value, MPFR_RNDN);
	output_constant<FloatX>("inv_sqrt3_v ", num);

	// egamma_v
	mpfr_const_euler(num.value, MPFR_RNDN);
	output_constant<FloatX>("egamma_v    ", num);

	// phi_v
	num = 5.0;
	mpfr_sqrt(num.value, num.value, MPFR_RNDN);
	mpfr_add_d(num.value, num.value, 1.0, MPFR_RNDN);
	mpfr_div_d(num.value, num.value, 2.0, MPFR_RNDN);
	output_constant<FloatX>("phi_v       ", num);
}