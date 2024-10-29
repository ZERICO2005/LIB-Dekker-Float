/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef FLOATNXN_PRECISION_TEST_HPP
#define FLOATNXN_PRECISION_TEST_HPP

#include <_mingw_stat64.h>
#include <cstdio>
#include <math.h>
#include <cmath>
#include <limits>
#include "../../util_mpfr/MPFR_Float.hpp"
#include "../../util_mpfr/mpfr_convert.hpp"

#define linearInterpolation(x, x0, x1, y0, y1) \
	((y0) + ( (((y1) - (y0)) * ((x) - (x0))) / ((x1) - (x0)) ))


#if 1
	#include <stdbool.h>
	#include <math.h>

	/**
	 * @remarks Newtons iteration will typically divide by 3.0, but I found that
	 * multiplying by ~0.3328 gives a more accurate result somehow. This is rather
	 * convienient since multiplication is faster than division.
	 */
	#define magic_third 0.3328f

	// Used for range reduction `2^112`
	#define around_2_pow_112 5.192296858534e+33f

	/**
	 * @remarks Minimum precision: 21.415037 bits at both +4.251052856e+02 and
	 * +7.969426579e+17 for cbrtf.
	 * The previous method of powf(x, 1.0f / 3.0f) had a minimum precision of
	 * 21.0 bits at +4.037431946e+02, and a minimum precision 19.299560 bits
	 * at +1.187444200e+07, slowly losing precision at larger magnitudes.
	 * @note Precision tested with 32bit floats on x86_64
	 */
	float M_cbrtf(const float x)
	{
		if (x == 0.0f || !isfinite(x)) {
			// Perserves signed zeros, inf, and NaN
			return x;
		}
		
		const float fabs_x = fabsf(x);
		bool range_reduce = (fabs_x >= around_2_pow_112);
		
		const float scaled_x = range_reduce ? ldexpf(fabs_x, -24) : fabs_x;
		const float scaled_x_mul_2 = 2.0f * scaled_x;

		int expon = ilogbf(scaled_x);
		
		/**
		 * @remarks Adds one for rounding purposes
		 * @note trunc rounds in the opposite direction when expon is negative
		 */
		expon += (expon < 0) ? -1 : 1;
		expon /= 3;

		float guess = ldexpf(1.0f, expon);
		float guess_cubed;

		/* Halley iteration */
		guess_cubed = guess * guess * guess;
		guess = guess * ((guess_cubed + scaled_x_mul_2) / (2.0f * guess_cubed + scaled_x));

		/* Newton iteration */
		guess = magic_third * ((scaled_x / (guess * guess)) + 2.0f * guess);

		/* Halley iteration */
		guess_cubed = guess * guess * guess;
		guess = guess * ((guess_cubed + scaled_x_mul_2) / (2.0f * guess_cubed + scaled_x));
		
		/* Newton iteration */
		guess = ((scaled_x / (guess * guess)) + 2.0f * guess) / 3.0f;

		if (range_reduce) {
			guess = ldexpf(guess, 8);
		}

		return signbit(x) ? -guess : guess;
	}

#else
	#include	<errno.h>
	#include	<math.h>

	#define	log2	0.693147180559945e0f
	#define	ln10	2.30258509299404f
	#define	sqrto2	0.707106781186548e0f
	#define	p0	-0.240139179559211e2f
	#define	p1	0.309572928215377e2f
	#define	p2	-0.963769093368687e1f
	#define	p3	0.421087371217980e0f
	#define	q0	-0.120069589779605e2f
	#define	q1	0.194809660700890e2f
	#define	q2	-0.891110902798312e1f

	float M_logf(float arg)
	{
		float x,z, zsq, temp;
		int exp;

		if (arg <= 0.0f) {
			errno = EDOM;
			return -HUGE_VALF;
		}
		x = frexpf(arg, & exp);
		if ( x < sqrto2 ){
			x *= 2;
			exp--;
		}

		z = (x-1)/(x+1);
		zsq = z*z;

		temp = ((p3*zsq + p2)*zsq + p1)*zsq + p0;
		temp = temp/(((1.0f*zsq + q2)*zsq + q1)*zsq + q0);
		temp = temp*z + (float)exp * log2;
		return temp;
	}

	#define	z0	0.20803843466947e7f
	#define	z1	0.30286971697440e5f
	#define	z2	0.60614853300611e2f
	#define	w0	0.60027203602388e7f
	#define	w1	0.32772515180829e6f
	#define	w2	0.17492876890931e4f
	#define	log2e	1.44269504088896f
	#define	sqrt2	1.41421356237310f
	#define	mmaxf	10000

	float M_expf(float arg) {
		float fraction;
		float temp1, temp2, xsq;
		int ent;

		if ( arg == 0.0 ){
			return 1.0;
		}
		if ( arg < -mmaxf ){
			return 0.0;
		}
		if ( arg > mmaxf ){
			errno = ERANGE;
			return HUGE_VALF;
		}
		arg *= log2e;
		ent = (int)floorf( arg );
		fraction = arg - (float)ent - 0.5f;
		xsq = fraction * fraction;
		temp1 = ((z2 * xsq + z1) * xsq + z0) * fraction;
		temp2 = ((1.0f * xsq + w2) * xsq + w1) * xsq + w0;
		return ldexpf( sqrt2 * (temp2+temp1) / (temp2-temp1), ent );
	}


	float M_powf(float arg1, float arg2) {
		float result;
		int32_t temp;

		if ( arg1 > 0.0f ){
			return M_expf( arg2 * log( arg1 ) );
		}
		if ( arg1 < 0.0f ){
			temp = (int32_t)arg2;
			if ( temp == (int32_t)arg2 ){
				result = M_expf( arg2 * M_logf( -arg1 ) );
				return temp & 1 ? -result : result;
			}
			errno = EDOM;
		}
		if ( arg2 <= 0.0f ){
			errno = EDOM;
		}
		return 0.0f;
	}


	float M_cbrtf(float x) {
		return M_powf(x, 0.3333333333333333333333333333f);
	}
#endif
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
		mpfr_cbrt(y0_mpfr.value, y0_mpfr.value, MPFR_RNDN);
	}
	{ // Calculate func result
		y1 = M_cbrtf(x);
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
	constexpr size_t points = 65536317;

	long double max_diff = -9999999.0L;
	size_t values_printed = 0;

	long double range =  (long double)FLT_MAX;
	long double offset = (long double)FLT_MAX;

	for (size_t i = 0; i < points; i++) {

		fpX x = (fpX)linearInterpolation(
			(long double)i, 0.0L, (long double)points,
			offset - range,  offset + range
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
		if (diff > max_diff || values_printed == 0 || (isnan(y0) != isnan(y1))) {
			
			if (!std::isnan(diff) && diff > max_diff) {
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

template <typename fpX>
void graph_precision(const size_t points, const long double range, const long double offset) {
	struct graph_point {
		long double x;
		long double diff;
		long double y0;
		long double y1;
	};
	graph_point* data = (graph_point*)calloc(points, sizeof(graph_point));
	if (data == nullptr) {
		printf("calloc failure\n");
		return;
	}

	int64_t start_time = getNanoTime();
	for (size_t i = 0; i < points; i++) {
		
		fpX x = linearInterpolation(
			(long double)i, 0.0L, (long double)points,
			offset - range,  offset + range
		);

		fpX y0;
		fpX y1;
		long double diff =
			calc_precision(static_cast<fpX>(x), y0, y1) -
			static_cast<long double>(ilogb(fabs(static_cast<long double>(y0))));

		if (y0 == static_cast<fpX>(0.0) && y1 == static_cast<fpX>(0.0)) {
			diff = -std::numeric_limits<long double>::infinity();
		}

		data[i].x    = static_cast<long double>(x );
		data[i].diff = static_cast<long double>(diff);
		data[i].y0   = static_cast<long double>(y0);
		data[i].y1   = static_cast<long double>(y1);

		if (i % 100 == 0) {
			printf(
				"%6zu: %+20.15Lf | x = %+15.9Le | %+15.9Le - %+15.9Le = %+15.9Le\n",
				i, diff,
				static_cast<long double>(x),
				static_cast<long double>(y1),
				static_cast<long double>(y0),
				static_cast<long double>(y1 - y0)
			);
		}
	}
	int64_t finish_time = getNanoTime();

	
	FILE* data_file;
	#if 0
		// Use double
		const char path_name[] = "./graph.bin";
		data_file = fopen(path_name, "wb");
		fwrite(data, points, sizeof(graph_point), data_file);
	#else
		// Use long double
		const char path_name[] = "./graph.csv";
		data_file = fopen(path_name, "wb");
		for (size_t i = 0; i < points; i++) {
			fprintf(data_file,
				"% #16.12Lg, % #16.12Lg, % #16.12Lg, % #16.12Lg,\n",
				data[i].x, data[i].diff, data[i].y0, data[i].y1
			);
		}
	#endif
	fclose(data_file);
	printf(
		"Time Taken: %.3lfs. Wrote %zu points to %s\n",
		static_cast<fp64>(finish_time - start_time) * 1.0e-9, points, path_name
	);

	free(data);
	data = nullptr;
}

#endif /* FLOATNXN_PRECISION_TEST_HPP */
