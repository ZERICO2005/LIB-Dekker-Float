/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#include <cstdio>
#include <cmath>

#include "../../Float64x2/Float64x2.hpp"
#include "../../Float64x4/Float64x4.hpp"
#include "../../Float80x2/Float80x2.hpp"
#ifdef Enable_Float80
	#include "Float80x2/Float80x2.hpp"
#endif
#ifdef Enable_Float128
	#define MPFR_WANT_FLOAT128
	#include "Float128x2/Float128x2.hpp"
#endif

#include "generate_inverf_lut.h"

#include "../../util_mpfr/auto_include_FloatX_mpfr.h"
#include "../../util_mpfr/MPFR_Float.hpp"
#include <mpfr.h>


template<typename FloatX, typename FloatBase>
static void output_constant(mpfr_t src, int term) {
	FloatX dst_value = mpfr_get_type<FloatX>(src, MPFR_RNDN);
	const FloatBase* dst = reinterpret_cast<FloatBase*>(&dst_value);
	const int precision = std::numeric_limits<FloatBase>::max_digits10 + 1;
	const int width = 7 + precision;
	
	printf("/* %2d */ {", term);
	char dst_buf[999];
	snprintf(dst_buf, sizeof(dst_buf), "%-*.*Le", width, precision, dst[0]);
	printf("%s,", dst_buf);
	snprintf(dst_buf, sizeof(dst_buf), "%+-*.*Le", width, precision, dst[1]);
	printf("%s},\n", dst_buf);
}

void generate_inverf(const int Precision, const int Maxiumum_Terms, int Digits) {
	if (Digits <= 0) {
		Digits = static_cast<int>(
			ceil(log10(2.0) * static_cast<double>(Precision)) + 1.0
		);
	}

	const mpfr_rnd_t ROUND_MODE = MPFR_RNDN;
	mpfr_t pi_const, pi_power, term_numerator, term_denominator, result;
	mpfr_inits2(static_cast<mpfr_prec_t>(Precision),
		pi_const, pi_power, term_numerator, term_denominator, result,
	nullptr);

	// pi constant
	mpfr_const_pi(pi_const, ROUND_MODE);
	
	// init to sqrt(pi) / 2
	mpfr_set(pi_power, pi_const, ROUND_MODE);
	mpfr_sqrt(pi_power, pi_power, ROUND_MODE);
	mpfr_div_ui(pi_power, pi_power, 2, ROUND_MODE);

	for (int i = 0; i < Maxiumum_Terms; i++) {
		if (inverf_numerator[i][0] == '\0' || inverf_denominator[i][0] == '\0') {
			printf("generate_inverf out of terms %d\n", i);
			return;
		}
		mpfr_set_str(term_numerator, inverf_numerator[i], 10, ROUND_MODE);
		mpfr_set_str(term_denominator, inverf_denominator[i], 10, ROUND_MODE);
		mpfr_mul_2exp(term_denominator, term_denominator, i * 2, ROUND_MODE);
		mpfr_div(result, term_numerator, term_denominator, ROUND_MODE);
		mpfr_mul(result, result, pi_power, ROUND_MODE);
		output_constant<Float80x2, fp80>(result, i);
		// mpfr_printf("/* %3d */ %.*Rf,\n", i, Digits, result);
		mpfr_mul(pi_power, pi_power, pi_const, ROUND_MODE);
	}

	mpfr_clears(
		pi_const, pi_power, term_numerator, term_denominator, result,
	nullptr);
	printf("generated %d inverf terms\n", Maxiumum_Terms);
}

void test_inverf(void) {
	for (int i = -110; i < 110; i++) {
		Float80x2 x = static_cast<fp80>(i) / static_cast<fp80>(10.0);
		#if 0
			Float80x2 y = erfc(x);
			Float80x2 z = inverfc(y);
		#else
			Float80x2 y = erf(x);
			Float80x2 z = inverf(y);
		#endif
		printf("%6.1Lf: %#14.8Lg %#14.8Lg diff: %#14.8Lg log2: %+-7.3Lf\n",
			x.hi, y.hi, z.hi,
			static_cast<fp80>(fabs(z - x)),
			log2(static_cast<fp80>(fabs(z - x))) - static_cast<fp80>(ilogb(x))
		);
	}
}
