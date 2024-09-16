/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#include <limits>
#include <math.h>
#include <algorithm>
#include <cstdio>
#include <float.h>
#include <cfloat>
#include <ios>
#include <numbers>

#include <stdint.h>

#include <iostream>

#include <ctime>
#include <chrono>
inline int64_t getNanoTime(void) { 
	using nanoseconds = std::chrono::duration<int64_t, std::nano>;
	auto now = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<nanoseconds>(now.time_since_epoch()).count();
}

#define MPFR_WANT_FLOAT128

#include "Float80x2/Float80x2_def.h"

#include "Float32/Float32.h"
#include "Float64/Float64.h"

#if 1
#include "Float32x2/Float32x2.hpp"
#endif

#include "Float64x2/Float64x2.hpp"

#if 1

#include "Float64x2/Float64x2.h"

// #include "Float64x4/Float64x4.hpp"

#ifdef Enable_Float80
	#include "Float80x2/Float80x2.hpp"
#endif
#ifdef Enable_Float128
	#include "Float128x2/Float128x2.hpp"
#endif

#include "Float32x4/Float32x4.hpp"
#include "Float64x4/Float64x4.h"
#include "Float64x4/Float64x4.hpp"
#include "Float64x6/Float64x6.hpp"

// Deprecated since it runs slower than mpfr_t. It could be faster than the overhead from C++ wrappers for mpfr_t
// #include "Float80x4/Float80x4.h"

#include "Float64x4/Float64x4_AVX.h"
#include "Float64x2/Float64x2_AVX.h"

#include "util_mpfr/auto_include_FloatX_mpfr.h"

#include "test_function.hpp"


#include "FloatNx2_demo.hpp"

#include "FloatNx2_math_demo.hpp"

#include "precision_test.hpp"

#endif

#if 1
#include "generate_constants.hpp"
#endif

#if 1

void run_demo(void) {
	FloatNxN_demo<Float32x2>(
		"Float32x2_demo",
		"%+.50" PRIFloat32x2 "f",
		"% .*" PRIFloat32x2 "f 14-digits", 17,
		stringTo_Float32x2,
		Float32x2_snprintf
	);
	
	FloatNxN_demo<Float64x2>(
		"Float64x2_demo",
		"%+.50" PRIFloat64x2 "f",
		"% .*" PRIFloat64x2 "f 32-digits", 35,
		stringTo_Float64x2,
		Float64x2_snprintf
	);

	#ifdef Enable_Float80
		FloatNxN_demo<Float80x2>(
			"Float80x2_demo",
			"%+.50" PRIFloat80x2 "f",
			"% .*" PRIFloat80x2 "f 38-digits", 41,
			stringTo_Float80x2,
			Float80x2_snprintf
		);
	#endif
}

void run_math_demo(unsigned int seed) {
	FloatNxN_math_demo<double>(
		seed,
		"Float64_control",
		"%+.*" PRIFloat64 "f",
		snprintf
	);
	FloatNxN_math_demo<Float32x2>(
		seed,
		"Float32x2_math_demo",
		"%+.*" PRIFloat32x2 "f",
		Float32x2_snprintf
	);
	FloatNxN_math_demo<Float64x2>(
		seed,
		"Float64x2_math_demo",
		"%+.*" PRIFloat64x2 "f",
		Float64x2_snprintf
	);
	#ifdef Enable_Float80
		FloatNxN_math_demo<Float80x2>(
			seed,
			"Float80x2_math_demo",
			"%+.*" PRIFloat80x2 "f",
			Float80x2_snprintf
		);
	#endif
}

#endif



void run_generate_constants(void) {
	generate_constants<Float64x4, fp64>("Float64x4");
}

#if 0

void get_fact(void) {
	#if 0
		#if 1
			for (unsigned long i = 1; i <= 99; i += 2) {
				FloatMPFR f;
				mpfr_fac_ui(f.value, i, MPFR_RNDN);
				mpfr_d_div(f.value, 1.0, f.value, MPFR_RNDN);
				Float80x2 num = mpfr_get_float80x2(f.value, MPFR_RNDN);
				printf(
					"/* %2lu! */ {%-24.15LaL,%+-25.15LaL},\n", i,
					num.hi, num.lo
				);
			}
		#else
			for (unsigned long i = 0; i <= 99; i += 1) {
				FloatMPFR f;
				mpfr_fac_ui(f.value, i, MPFR_RNDN);
				mpfr_d_div(f.value, 1.0, f.value, MPFR_RNDN);
				Float64x4 num = mpfr_get_float64x4(f.value, MPFR_RNDN);
				printf(
					"/* %2lu! */ {%-22.13a,%+-23.13a,%+-23.13a,%+-23.13a},\n", i,
					num.val[0], num.val[1], num.val[2], num.val[3]
				);
			}
		#endif
	#else
		#if 1
		for (unsigned long i = 0; i <= 256; i += 1) {
			FloatMPFR f;
			mpfr_set_ui(f.value, i, MPFR_RNDN);
			mpfr_div_ui(f.value, f.value, 1024, MPFR_RNDN);
			mpfr_cospi(f.value, f.value, MPFR_RNDN);
			Float80x2 num = mpfr_get_float80x2(f.value, MPFR_RNDN);
			printf(
				"/* %3lu */ {%-22.15LaL,%+-23.15LaL},\n", i,
				num.hi, num.lo
			);
		}
		#else
		for (unsigned long i = 0; i <= 256; i += 1) {
			FloatMPFR f;
			mpfr_set_ui(f.value, i, MPFR_RNDN);
			mpfr_div_ui(f.value, f.value, 1024, MPFR_RNDN);
			mpfr_sinpi(f.value, f.value, MPFR_RNDN);
			Float64x4 num = mpfr_get_float64x4(f.value, MPFR_RNDN);
			printf(
				"/* sin(pi * %3lu/1024) */ {%-20.13a,%+-22.13a,%+-23.13a,%+-23.13a},\n", i,
				num.val[0], num.val[1], num.val[2], num.val[3]
			);
		}
		#endif
	#endif
}

#endif

#if 1
#include <quadmath.h>
void aaa(void) {
	#if 1
	const int count = 65536;
	{
		int64_t start = getNanoTime();
		for (int i = 0; i < count; i++) {
			Float64x4 ret = ((fp64)i / 8192.0);
			ret *= erf(ret);
		}
		int64_t finish = getNanoTime();
		printf("Time: %.3Lfms\n", static_cast<long double>(finish - start) * 1.0e-6L);
	}
	{
		int64_t start = getNanoTime();
		for (int i = 0; i < count; i++) {
			FloatMPFR ret = ((fp64)i / 8192.0);
			ret *= erf(ret);
		}
		int64_t finish = getNanoTime();
		printf("Time: %.3Lfms\n", static_cast<long double>(finish - start) * 1.0e-6L);
	}
	#endif
	#if 0
	fp80 max_diff = -1000.0L;
	for (int i = 0; i < 16777216; i++) {
		Float80x2 x0 = (fp80)i;
		fp128 x1 = (fp128)i;
		x0 = sin(x0);
		x1 = sin(x1);
		fp80 diff = (fp80)log2q(fabsq((fp128)x0 - x1));
		if (diff > max_diff) {
			max_diff = diff;
			printf("%5d: %+24.18Le %+24.18Le | %+11.8Lf\n", i, (fp80)x0, (fp80)x1, diff);
		}
	}
	#endif
}
#endif

#include "../../Float64x6/Float64x6.hpp"

int main(void) {
	printf("\n");
	// aaa();
	// run_demo();
	// run_math_demo(123456);
	
	// test_function();

	// precision_test<Float80x2>();
	graph_precision<Float80x2>(24000, 120.0, 0.0L);

	// run_generate_constants();
	
	// __attribute__((unused)) char buf[999];
	// Float32x2 x = {FLT_MAX, FLT_MIN};
	// Float32x2_snprintf(buf, sizeof(buf), "%+.50Df", x);
	// printf("FLT_MAX + FLT_MIN = [%s]\n", buf);

	#if 0
	{
		Float64x2 r = -0.75;
		for (int i = 0; i < 16; i++) {
			Float64x2 result = tgamma(r);
			std::cout << "tgamma(" << r << ") = " << result << std::endl;
			r += 0.75;
		}
	}
	#endif
	
	#if 0
	__attribute__((unused)) char buf[999];
	
	Float64x2 x = "2.718281828459045235360287471352662497757247093699959574966967627724076630353547594571382"_FP64X2;
	fp64 y = x;
	int exp_x, exp_y;
	x = frexp(x, exp_x);
	y = frexp(y, &exp_y);
	Float64x2_snprintf(buf, sizeof(buf), "%+.50" PRIFloat64x2 "f", x);
	printf(
		"Float64x2: %s * 2^%d\nFloat64  : %+.50f * 2^%d\n",
		buf, exp_x, y, exp_y
	);
	#endif
	#if 0
		// Testing the accuracy of modf
		printf("\n");
		for (int i = 0; i < 130; i++) {
			long double res0 = fmodl((long double)ldexpf(1.2345f, i), (long double)((float)M_PI));
			float       res1 = fmodf(             ldexpf(1.2345f, i),              ((float)M_PI));
			
			float res2 = trunc(ldexpf(1.2345f, i) / (float)M_PI);
			res2 = ldexpf(1.2345f, i) - (float)M_PI * res2;

			// long double res0 = sinl((long double)ldexpf(1.2345f, i));
			// float       res1 = sinf(             ldexpf(1.2345f, i));
			printf(
				"%4d [%+9.6Lf]: %+9.6f - %+9.6f = %+6.2Lf error\n", i,
				res0, res1, res2, log2l(fabsl((long double)res1 - (long double)res2))
			);
		}
	#endif

	// printf("%La\n", LDBL_MAX);

	// Float64x2 y = Float64x2_set_d(3.0);
	// Float64x4 result = Float64x4_recip_quick_dx2(y);
	// mpfr_t p;
	// mpfr_init2(p, 512);
	// mpfr_set_float64x4(p, result, MPFR_RNDN);
	// mpfr_printf("\nFloat64x4: \n1/3 = %.70Rf\n", p);
	
	// get_fact();
	printf("\n");
	fflush(stdout);
	return 0;
}
