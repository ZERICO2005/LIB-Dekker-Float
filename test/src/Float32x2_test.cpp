/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#include "../../Float32x2/double_Float32.hpp"
#include <cfloat>
#include <cstdio>

#include "digits_of_euler.h"

void Float32x2_test(void) {
	printf("Float32x2_test:\n");
	Float32x2 x = static_cast<Float32x2>(1.0);
	Float32x2 y = static_cast<Float32x2>(FLT_MIN);
	Float32x2 z = x + y;
	char buf[999];
	Float32x2_snprintf(buf, sizeof(buf), "%+.50" PRIFloat32x2 "f", z);
	printf("1.0 + FLT_MIN = %s\n", buf);

	Float32x2 euler = stringTo_Float32x2(digits_of_euler);
	Float32x2_snprintf(buf, sizeof(buf), "%+.50" PRIFloat32x2 "f", euler);
	printf("Euler's Number: %s\n", buf);
}