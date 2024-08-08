/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#include <cstdio>
#include <cfloat>

#include "../../Float32x2/double_Float32.hpp"
#include "../../Float64x2/double_Float64.hpp"
#ifdef Enable_Float80
	#include "../../Float80x2/double_Float80.hpp"
#endif

#include "digits_of_euler.h"

template<typename FloatNx2>
void FloatNx2_test(
	const char* label,
	const char* format_add,
	const char* format_euler,
	int euler_precision,
	FloatNx2 (*stringTo_FloatNx2)(const char*, char**),
	int (*FloatNx2_snprintf)(char* buf, size_t len, const char* format, ...)
) {
	printf("%s:\n", label);
	FloatNx2 x = static_cast<FloatNx2>(1.0);
	FloatNx2 y = static_cast<FloatNx2>(FLT_MIN);
	FloatNx2 z = x + y;

	char buf[999];
	(*FloatNx2_snprintf)(buf, sizeof(buf), format_add, z);
	printf("\t1.0 + FLT_MIN = %s\n", buf);

	FloatNx2 euler_number = (*stringTo_FloatNx2)(digits_of_euler, nullptr);
	(*FloatNx2_snprintf)(
		buf, sizeof(buf),
		format_euler,
		euler_precision,
		euler_number
	);
	printf("\tEuler's Number: %s\n", buf);
}

int main(void) {
	
	FloatNx2_test<Float32x2>(
		"Float32x2_test",
		"%+.50" PRIFloat32x2 "f",
		"% .*" PRIFloat32x2 "f 14-digits", 17,
		stringTo_Float32x2,
		Float32x2_snprintf
	);
	
	FloatNx2_test<Float64x2>(
		"Float64x2_test",
		"%+.50" PRIFloat64x2 "f",
		"% .*" PRIFloat64x2 "f 32-digits", 35,
		stringTo_Float64x2,
		Float64x2_snprintf
	);

	#ifdef Enable_Float80
		FloatNx2_test<Float80x2>(
			"Float80x2_test",
			"%+.50" PRIFloat80x2 "f",
			"% .*" PRIFloat80x2 "f 38-digits", 41,
			stringTo_Float80x2,
			Float80x2_snprintf
		);
	#endif

	fflush(stdout);
	return 0;
}