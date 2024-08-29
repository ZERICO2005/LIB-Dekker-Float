/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef FLOATNX2_DEMO_HPP
#define FLOATNX2_DEMO_HPP

#include <cstdio>
#include <cfloat>

#include "digits_of_euler.h"

template<typename FloatNx2>
void FloatNx2_demo(
	const char* label,
	const char* format_add,
	const char* format_euler,
	int euler_precision,
	FloatNx2 (*stringTo_FloatNx2)(const char*, char**),
	int (*FloatNx2_snprintf)(char* buf, size_t len, const char* format, ...)
) {
	printf("%s:\n", label);
	char buf[999];

	FloatNx2 x = static_cast<FloatNx2>(1.0);
	FloatNx2 y = static_cast<FloatNx2>(FLT_MIN);
	FloatNx2 z = x + y;

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

#endif /* FLOATNX2_DEMO_HPP */
