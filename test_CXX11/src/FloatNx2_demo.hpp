/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef FLOATNXN_DEMO_HPP
#define FLOATNXN_DEMO_HPP

#include <cstdio>
#include <cfloat>

#include "digits_of_euler.h"

template<typename FloatNxN>
void FloatNxN_demo(
	const char* label,
	const char* format_add,
	const char* format_euler,
	int euler_precision,
	FloatNxN (*stringTo_FloatNxN)(const char*, char**),
	int (*FloatNxN_snprintf)(char* buf, size_t len, const char* format, ...)
) {
	printf("%s:\n", label);
	char buf[999];

	FloatNxN x = static_cast<FloatNxN>(1.0);
	FloatNxN y = static_cast<FloatNxN>(FLT_MIN);
	FloatNxN z = x + y;

	(*FloatNxN_snprintf)(buf, sizeof(buf), format_add, z);
	printf("\t1.0 + FLT_MIN = %s\n", buf);

	FloatNxN euler_number = (*stringTo_FloatNxN)(digits_of_euler, nullptr);
	(*FloatNxN_snprintf)(
		buf, sizeof(buf),
		format_euler,
		euler_precision,
		euler_number
	);
	printf("\tEuler's Number: %s\n", buf);
}

#endif /* FLOATNXN_DEMO_HPP */
