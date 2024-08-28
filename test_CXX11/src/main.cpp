/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#include <cstdio>
#include <cfloat>
#include <ios>
#include <numbers>

#include "Float32x2/Float32x2.hpp"

#include "Float64x2/Float64x2.hpp"

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

#include "Float64x2/Float64x2_AVX.h"

#include "test_function.hpp"



#define PRIFloat64 "l"

#include "FloatNx2_demo.hpp"

#include "FloatNx2_math_demo.hpp"

#include "util_mpfr/auto_include_FloatX_mpfr.h"

#include "generate_constants.hpp"

void run_demo(void) {
	FloatNx2_demo<Float32x2>(
		"Float32x2_demo",
		"%+.50" PRIFloat32x2 "f",
		"% .*" PRIFloat32x2 "f 14-digits", 17,
		stringTo_Float32x2,
		Float32x2_snprintf
	);
	
	FloatNx2_demo<Float64x2>(
		"Float64x2_demo",
		"%+.50" PRIFloat64x2 "f",
		"% .*" PRIFloat64x2 "f 32-digits", 35,
		stringTo_Float64x2,
		Float64x2_snprintf
	);

	#ifdef Enable_Float80
		FloatNx2_demo<Float80x2>(
			"Float80x2_demo",
			"%+.50" PRIFloat80x2 "f",
			"% .*" PRIFloat80x2 "f 38-digits", 41,
			stringTo_Float80x2,
			Float80x2_snprintf
		);
	#endif
}

void run_math_demo(unsigned int seed) {
	FloatNx2_math_demo<double>(
		seed,
		"Float64_control",
		"%+.*" PRIFloat64 "f",
		snprintf
	);
	FloatNx2_math_demo<Float32x2>(
		seed,
		"Float32x2_math_demo",
		"%+.*" PRIFloat32x2 "f",
		Float32x2_snprintf
	);
	FloatNx2_math_demo<Float64x2>(
		seed,
		"Float64x2_math_demo",
		"%+.*" PRIFloat64x2 "f",
		Float64x2_snprintf
	);
	#ifdef Enable_Float80
		FloatNx2_math_demo<Float80x2>(
			seed,
			"Float80x2_math_demo",
			"%+.*" PRIFloat80x2 "f",
			Float80x2_snprintf
		);
	#endif
}

void run_generate_constants(void) {
	generate_constants<Float32x4>("Float32x4");
}

int main(void) {
	// run_demo();
	// run_math_demo(123456);
	// test_function();

	// run_generate_constants();

	__attribute__((unused)) char buf[999];
	Float64x2 x = {1.0, DBL_MIN};
	Float64x2_snprintf(buf, sizeof(buf), "%+9.320Df", x);
	
	printf("[%s]\n", buf);
	printf("%La\n", LDBL_MAX);

	Float64x2 y = Float64x2_set_d(3.0);
	Float64x4 result = Float64x4_recip_quick_dx2(y);
	mpfr_t p;
	mpfr_init2(p, 512);
	mpfr_set_float64x4(p, result, MPFR_RNDN);
	mpfr_printf("\nFloat64x4: \n1/3 = %.70Rf\n", p);

	fflush(stdout);
	return 0;
}