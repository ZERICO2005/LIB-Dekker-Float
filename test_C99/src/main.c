/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#include "Float64x2/Float64x2_AVX.h"
#include "Float64x2/Float64x2.h"
#include "Float64x4/Float64x4_AVX.h"
#include "Float64x4/Float64x4.h"

#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <string.h>

#include <stdint.h>
#include <time.h>

int64_t getNanoTime(void) {
    struct timespec tp;
    if (clock_gettime(CLOCK_REALTIME, &tp) == 0) {
        int64_t nanoTime = (int64_t)tp.tv_sec * (int64_t)1000000000 + (int64_t)tp.tv_nsec;
        return nanoTime;
    } else {
        perror("clock_gettime");
        return 0;
    }
}

void func(void) {
	#if 1
		Float64x2 val[4] = {
			{1.0, 0.0}, {2.0, 0.0}, {3.0, 0.0}, {-1.0, 0.0}
		};
		__m256dx2 calc = _mm256x2_load_pdx2(val);

		int64_t start = getNanoTime();
		__m256dx2 result;
		// 16777216 tests took around 4.084s compared to 15.994s for the non-AVX exp function.
		for (int t = 0; t < 1 /* 256 */; t++) {
			result = _mm256x2_exp_pdx2(calc);
		}
		int64_t finish = getNanoTime();
		printf("Time: %.3lfms\n", (fp64)(finish - start) * 1.0e-6);

		_mm256x2_store_pdx2(val, result);
		char buf[999];
		Float64x2_snprintf(buf, sizeof(buf), "%+54.50" PRIFloat64x2 "f", val[0]);
		printf("[%s]\n", buf);
		Float64x2_snprintf(buf, sizeof(buf), "%+54.50" PRIFloat64x2 "f", val[1]);
		printf("[%s]\n", buf);
		Float64x2_snprintf(buf, sizeof(buf), "%+54.50" PRIFloat64x2 "f", val[2]);
		printf("[%s]\n", buf);
		Float64x2_snprintf(buf, sizeof(buf), "%+54.50" PRIFloat64x2 "f", val[3]);
		printf("[%s]\n", buf);
	#else
		Float64x4 val[4] = {
			{{1.0, 0.0, 0.0, 0.0}}, {{2.0, 0.0, 0.0, 0.0}}, {{3.0, 0.0, 0.0, 0.0}}, {{4.0, 0.0, 0.0, 0.0}}
		};
		__m256dx4 calc = _mm256x4_load_pdx4(val);
		__m256dx4 result = _mm256x4_exp_pdx4(calc);
		_mm256x4_store_pdx4(val, result);
		for (size_t i = 0; i < 4; i++) {
			printf(
				"[%zu]: %-+20.13e %-+20.13e %-+20.13e %-+20.13e\n", i,
				val[i].val[0], val[i].val[1], val[i].val[2], val[i].val[3]
			);
		}
	#endif
}

int main(void) {
	// __attribute__((unused)) char buf[999];
	// Float64x2 x = {1.0, DBL_MIN};
	// // x = Float64x2_exp(x);
	// Float64x2_snprintf(buf, sizeof(buf), "%+-9.320" PRIFloat64x2 "f", x);
	// printf("[%s]\n", buf);
	// printf("%g %g\n", x.hi, x.lo);
	
	func();

	fflush(stdout);
	return 0;
}
