/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef FLOATNXN_TEST_FUNCTION_HPP
#define FLOATNXN_TEST_FUNCTION_HPP

#include <cstdio>
#include <cmath>

// #include "Float64x2/Float64x2.hpp"
#ifdef Enable_Float80
	#include "Float80x2/Float80x2.hpp"
#endif
#ifdef Enable_Float128
	#include "Float128x2/Float128x2.hpp"
#endif

#include "util_mpfr/MPFR_Float.hpp"
#include <mpfr.h>

// void foo() {
// 	FloatMPFR f;
// 	FloatMPFR e;
// 	e = -1.0;
// 	mpfr_exp(f.value, e.value, MPFR_RNDZ);
// 	Float64x2 num;
// 	num.hi = mpfr_get_d(f.value, MPFR_RNDZ);
// 	mpfr_sub_d(f.value, f.value, num.hi, MPFR_RNDZ);
// 	num.lo = mpfr_get_d(f.value, MPFR_RNDZ);
// 	printf("{%+-24.14a, %+-24.14a};\n", num.hi, num.lo);
// }

#define linearInterpolation(x, x0, x1, y0, y1) \
	((y0) + ( (((y1) - (y0)) * ((x) - (x0))) / ((x1) - (x0)) ))

#include "Float64x2/Float64x2_mpfr.h"
#include "Float64x4/Float64x4_mpfr.h"

#include <cmath>

void test_function(void) {
	constexpr size_t points = 6553;

	FloatMPFR y0, y1;
	FloatMPFR diff_temp;

	fp80 max_diff = -9999999.0L;

	for (size_t i = 0; i < points; i++) {
		#if 1
		fp80 EP =     15.0L;
		fp80 offset = 0.0L;
		#else
		fp80 EP =     +0x0.00000000000800p+0;
		fp80 offset = 3.0L * TAU / 4.0L;
		#endif
		
		fp80 x = linearInterpolation((fp80)i, 0.0L, (fp80)points, offset - EP,  offset + EP);
		// 6.2831 * ((fp64)i / (fp64)(points)) - (12345678901234567891.0 * 0.5 * TAU);

		Float80x2 y = sin(static_cast<Float80x2>(x));


		mpfr_set_float80x2(y0.value, y, MPFR_RNDN);
		y1 = sin((FloatMPFR)x);
		diff_temp = log2(fabs(y0 - y1));
		fp80 diff = mpfr_get_ld(diff_temp.value, MPFR_RNDN);
		if (std::isinf(diff)) {
			diff = -9999.99L;
		}
		char comp_sign = (y0 == y1) ? '=' : ((y0 > y1) ? '>' : '<');
		if (diff > max_diff || (diff >= -204.0L && false) || false) {
			max_diff = diff;
			mpfr_printf(
				"%6zu: %+20.15Lf | %+#25.18Lf | %+#25.18Rg %c%+#25.18Rg\n",
				i,
				diff,
				x,
				y0.value,
				comp_sign,
				y1.value
			);
		}
	}
}


#endif /* FLOATNXN_TEST_FUNCTION_HPP */
