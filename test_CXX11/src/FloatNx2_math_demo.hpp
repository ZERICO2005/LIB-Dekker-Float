/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef FLOATNXN_MATH_DEMO_HPP
#define FLOATNXN_MATH_DEMO_HPP

#include <cstdio>
#include <cfloat>
#include <cstdlib>
#include <array>

template<typename FloatNxN>
inline FloatNxN get_rand(void) {
	return static_cast<FloatNxN>(static_cast<double>(rand()) / static_cast<double>(RAND_MAX));
}

template<typename FloatNxN>
void FloatNxN_math_demo(
	unsigned int seed,
	const char* label,
	const char* format,
	int (*FloatNxN_snprintf)(char* buf, size_t len, const char* format, ...)
) {
	srand(seed);
	printf("%s:\n", label);
	
	std::array<FloatNxN, 12> num;
	for (size_t i = 0; i < num.size(); i += 2) {
		num[i + 0] = get_rand<FloatNxN>();
		num[i + 0] -= static_cast<FloatNxN>(0.5);
		num[i + 0] *= static_cast<FloatNxN>(10.0);
		num[i + 1] = get_rand<FloatNxN>();
		num[i + 1] -= static_cast<FloatNxN>(0.5);
		num[i + 1] *= static_cast<FloatNxN>(10.0);
	}
	for (size_t i = 0; i < num.size(); i += 2) {
		char num0[999];
		char num1[999];
		(*FloatNxN_snprintf)(num0, sizeof(num0), format, 30, num[i + 0]);
		(*FloatNxN_snprintf)(num1, sizeof(num1), format, 30, num[i + 1]);
		printf("\t%2zu: %s %s \n", (i / 2) + 1, num0, num1);
	}

	printf("\tfdim(x, y):\n");
	for (size_t i = 0; i < num.size(); i += 2) {
		char result[999];
		(*FloatNxN_snprintf)(result, sizeof(result), format, 10,
			fdim(num[i + 0], num[i + 1])
		);
		printf("\t%2zu: %s\n", (i / 2) + 1, result);
	}

	printf("\ttrunc(x) floor(x) ceil(x):\n");
	for (size_t i = 0; i < num.size(); i += 2) {
		char res_trunc[999];
		char res_floor[999];
		char res_ceil[999];
		(*FloatNxN_snprintf)(res_trunc, sizeof(res_trunc), format, 10,
			trunc(num[i + 0])
		);
		(*FloatNxN_snprintf)(res_floor, sizeof(res_floor), format, 10,
			floor(num[i + 0])
		);
		(*FloatNxN_snprintf)(res_ceil, sizeof(res_ceil), format, 10,
			ceil(num[i + 0])
		);
		printf("\t%2zu: %s %s %s\n", (i / 2) + 1, res_trunc, res_floor, res_ceil);
	}

	printf("\tsqrt(x) cbrt(x) hypot(x, y):\n");
	for (size_t i = 0; i < num.size(); i += 2) {
		char res_sqrt[999];
		char res_cbrt[999];
		char res_hypot[999];
		(*FloatNxN_snprintf)(res_sqrt, sizeof(res_sqrt), format, 40,
			sqrt(fabs(num[i + 0]))
		);
		(*FloatNxN_snprintf)(res_cbrt, sizeof(res_cbrt), format, 40,
			cbrt(num[i + 0])
		);
		(*FloatNxN_snprintf)(res_hypot, sizeof(res_hypot), format, 40,
			hypot(num[i + 0], num[i + 1])
		);
		printf("\t%2zu:\n\t\t%s\n\t\t%s\n\t\t%s\n", (i / 2) + 1, res_sqrt, res_cbrt, res_hypot);
	}
	
	// char buf[999];
	// FloatNxN x = static_cast<FloatNxN>(1.0);
	// x = exp(x);
	// (*FloatNxN_snprintf)(buf, sizeof(buf), format, 40, x);
	// printf("\texp(1.0) = %s\n", buf);
}

#endif /* FLOATNXN_MATH_DEMO_HPP */
