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

void func(void) {
	Float64x2 val[4] = {
		{1.0, 0.0}, {2.0, 0.0}, {3.0, 0.0}, {4.0, 0.0}
	};
	__m256dx2 calc = _mm256x2_load_pdx2(val);
	__m256dx2 result = _mm256x2_exp_pdx2(calc);
	_mm256x2_store_pdx2(val, result);
	char buf[999];
	Float64x2_snprintf(buf, sizeof(buf), "%+9.20Df", val[0]);
	printf("[%s]\n", buf);
	Float64x2_snprintf(buf, sizeof(buf), "%+9.20Df", val[1]);
	printf("[%s]\n", buf);
	Float64x2_snprintf(buf, sizeof(buf), "%+9.20Df", val[2]);
	printf("[%s]\n", buf);
	Float64x2_snprintf(buf, sizeof(buf), "%+9.20Df", val[3]);
	printf("[%s]\n", buf);
}

int main(void) {
	__attribute__((unused)) char buf[999];
	Float64x2 x = {1.0, DBL_MIN};
	Float64x2_snprintf(buf, sizeof(buf), "%+9.320Df", x);
	printf("[%s]\n", buf);
	printf("%g %g\n", x.hi, x.lo);
	
	func();

	fflush(stdout);
	return 0;
}
