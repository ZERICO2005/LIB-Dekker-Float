/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef FLOATNXN_PRECISION_TEST_HPP
#define FLOATNXN_PRECISION_TEST_HPP

#include <cstdio>
#include <cmath>
#include <limits>
#include "util_mpfr/MPFR_Float.hpp"
#include "util_mpfr/mpfr_convert.hpp"

/**
 * @brief Compares against MPFR
 * @returns log2(fabs(y1 - y0))
 */
template<typename fpX>
long double calc_precision(fpX x, fpX& ground_truth, fpX& func_result) {
	fpX y0; // ground truth
	fpX y1; // func result

	FloatMPFR y0_mpfr;
	FloatMPFR y1_mpfr;

	mpfr_set_type<fpX>(y0_mpfr.value, x, MPFR_RNDN);

	{ // Calculate ground truth
		mpfr_atanh(y0_mpfr.value, y0_mpfr.value, MPFR_RNDN);
	}
	{ // Calculate func result
		y1 = atanh(x);
	}

	y0 = mpfr_get_type<fpX>(y0_mpfr.value, MPFR_RNDN);
	ground_truth = y0;
	func_result = y1;

	// Convert back to mpfr for accurate ULP calculation
	mpfr_set_type<fpX>(y0_mpfr.value, y0, MPFR_RNDN);
	mpfr_set_type<fpX>(y1_mpfr.value, y1, MPFR_RNDN);

	mpfr_sub(y1_mpfr.value, y1_mpfr.value, y0_mpfr.value, MPFR_RNDN);
	mpfr_abs(y1_mpfr.value, y1_mpfr.value, MPFR_RNDN);
	mpfr_log2(y1_mpfr.value, y1_mpfr.value, MPFR_RNDN);
	long double diff = mpfr_get_ld(y1_mpfr.value, MPFR_RNDN);
	return diff;
}

template <typename fpX>
void precision_test(void) {
	constexpr size_t points = 655361;

	long double max_diff = -9999999.0L;
	size_t values_printed = 0;
	for (size_t i = 0; i < points; i++) {
		long double EP =      0.06L;
		long double offset = -0.4719L;
		
		fpX x = linearInterpolation(
			(long double)i, 0.0L, (long double)points,
			offset - EP,  offset + EP
		);

		fpX y0;
		fpX y1;
		long double diff =
			calc_precision(static_cast<fpX>(x), y0, y1) -
			static_cast<long double>(ilogb(fabs(static_cast<long double>(y0))));

		if (y0 == static_cast<fpX>(0.0) && y1 == static_cast<fpX>(0.0)) {
			diff = -std::numeric_limits<long double>::infinity();
		}
		// char comp_sign = (y0 == y1) ? '=' : ((y0 > y1) ? '>' : '<');
		if (diff > max_diff || values_printed == 0) {
			
			if (!std::isnan(diff)) {
				max_diff = diff;
			}
			printf(
				"%6zu: %+20.15Lf | x = %+15.9Le | %+15.9Le - %+15.9Le = %+15.9Le\n",
				i, diff,
				static_cast<long double>(x),
				static_cast<long double>(y1),
				static_cast<long double>(y0),
				static_cast<long double>(y1 - y0)
			);

			values_printed++;
		}
	}
}

#endif /* FLOATNXN_PRECISION_TEST_HPP */
