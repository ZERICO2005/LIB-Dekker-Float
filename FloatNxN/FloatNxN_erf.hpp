/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

/*
**	Portions of this file were part of the libDDFUN library
**	libDDFUN is licensed under a limited BSD license that can be found below:
**	https://www.davidhbailey.com/dhbsoftware/DHB-License.docx
**	Or alternatively from this website:
**	https://www.davidhbailey.com/dhbsoftware/
**	A copy of the Limited-BSD-License can also be found at:
**	LIB-Dekker-Float/libDDFUN/DISCLAIMER_and_Limited-BSD-License.txt
*/

#ifndef FLOATNXN_ERF_HPP
#define FLOATNXN_ERF_HPP

#include <cstdio>
#include <limits>

#include "../LDF/LDF_type_info.hpp"
#include "../LDF/LDF_constants.hpp"

#include "FloatNxN_fortran_def.h"

template<typename FloatNxN, typename FloatBase>
static inline FloatNxN double_odd_factorial(int k) {
	FloatNxN ret = static_cast<FloatBase>(1.0);
	FloatBase k_mult = static_cast<FloatBase>(3.0);
	for (int i = 1; i < k; i++) {
		ret *= k_mult;
		k_mult += static_cast<FloatBase>(2.0);
	}
	return ret;
}

//------------------------------------------------------------------------------
// FloatNxN erf and erfc
//------------------------------------------------------------------------------

/** 
 * @author Taken from libDDFUN ddfune.f90 which can be found under a
 * Limited-BSD license from https://www.davidhbailey.com/dhbsoftware/
 * @remarks It appears that the exact same implementation is used in
 * libQDFUN as well.
 */
template<
	typename FloatNxN, typename FloatBase,
	int max_iter
>
static inline FloatNxN libDDFUN_erf(const FloatNxN& z) {
	//   This evaluates the erf function, using a combination of two series.
	//   In particular, the algorithm is
	//   (where B = FloatNxN_Count * FloatN_Mantissa_Bits, and
	//   dcon is a constant defined below):
	//
	//   if (z == 0) {
	//     erf = 0;
	//   } else if (z > sqrt(B*log(2))) {
	//     erf = 1;
	//   } else if (z < -sqrt(B*log(2))) {
	//     erf = -1;
	//   } else if (abs(z) < B/dcon + 8) {
	//     erf = 2 / (sqrt(pi)*exp(z^2)) * Sum_{k>=0} 2^k * z^(2*k+1);
	//             / (1.3....(2*k+1));
	//   } else {
	//     erf = 1 - 1 / (sqrt(pi)*exp(z^2));
	//             * Sum_{k>=0} (-1)^k * (1.3...(2*k-1)) / (2^k * z^(2*k+1));
	//   }

	// FloatNxN, intent(in):: z
	// FloatNxN, intent(out):: terf
	FloatNxN terf;
	
	constexpr FloatBase dcon = static_cast<FloatBase>(100.0); /**< Unknown magic number */
	FloatBase d1, d2;
	FloatNxN t5, t6;

	// int dd_nw, dd_nw1;
	// dd_nw = FloatNxN_count;
	// dd_nw1 = std::min(dd_nw + 1, FloatNxN_count);
	const FloatBase target_epsilon = ldexp(
		static_cast<FloatBase>(1.0),
		-LDF::LDF_Type_Info<FloatNxN>::FloatBase_Count * std::numeric_limits<FloatBase>::digits
	);

	d1 = trunc(static_cast<FloatBase>(1.0) + sqrt(
		static_cast<FloatBase>(std::numeric_limits<FloatNxN>::digits) * LDF::const_ln2<FloatBase>()
	));
	d2 = trunc((
		static_cast<FloatBase>(std::numeric_limits<FloatNxN>::digits) / dcon
	) + static_cast<FloatBase>(8.0));

	if (isequal_zero(z)) { // sign(z) == 0
		// z == 0.0
		return static_cast<FloatBase>(0.0);
	}
	if ((isinf(z) && isgreater_zero(z)) || z > d1) {
		// z == +inf
		return static_cast<FloatBase>(1.0);
	}
	if ((isinf(z) && isless_zero(z)) || z < -d1) {
		// z == -inf
		return static_cast<FloatBase>(-1.0);
	}
	
	const FloatNxN z2 = square(z);

	if (z < d2) {
		FloatNxN taylor_sum = static_cast<FloatBase>(0.0);

		call_dd_dmc(static_cast<FloatBase>(1.0e10), 0, t5);

		FloatNxN taylor_val = z;
		const FloatNxN z2_mul2 = mul_pwr2(z2, static_cast<FloatBase>(2.0));
		FloatBase k_mult = static_cast<FloatBase>(1.0);
		for (int k = 0; k <= max_iter; k++) {
			if (k > 0) {
				taylor_val *= z2_mul2;
				taylor_val /= k_mult;
			}
			taylor_sum += taylor_val;
			t6 = taylor_val / taylor_sum;
			
			// Unordered comparisions protect against NAN
			if (!(t6 > target_epsilon) || t6 >= t5) {
				// goto JMP_120;
				break;
			}
			t5 = t6;
			k_mult += static_cast<FloatBase>(2.0);
		}
		

	// write (dd_ldb, 3) 1, max_iter;
	// 3 format ('*** DDERFR: iteration limit exceeded',2i10);
	// call_dd_abrt
	// /* label */ JMP_120:

		terf = mul_pwr2(taylor_sum, static_cast<FloatBase>(2.0)) * (LDF::const_inv_sqrtpi<FloatNxN>() * exp(-z2));
	} else {
		/**
		 * @remarks Performs this approximation:
		 * erf(x) = 1 - e^(-x^2) / sqrt(pi)
		 * This works when x is sufficiently large
		 */
		FloatNxN t2, t3, t4;
		t2 = static_cast<FloatBase>(1.0);
		t3 = fabs(z);

		FloatNxN taylor_sum = t3;
		FloatBase k_mult = static_cast<FloatBase>(-1.0);

		t5 = static_cast<FloatBase>(1.0);

		for (int k = 0; k <= max_iter; k++) {
			t2 *= k_mult;
			t3 /= t2;
			t4 = t2 * t3;
			taylor_sum += t4;
			t6 = t4 / taylor_sum;

			// printf(
			// 	"%4d: t1: % -#12.6Lg t2: % -#12.6Lg t3: % -#12.6Lg t4: % -#12.6Lg t5: % -#12.6Lg t6: % -#12.6Lg\n",
			// 	k, (long double)taylor_sum, (long double)t2, (long double)t3, (long double)t4, (long double)t5, (long double)t6
			// );

			// Unordered comparisions protect against NAN
			if (!(t6 > target_epsilon) || t6 >= t5) {
				// goto JMP_130;
				break;
			}
			t5 = t6;
			k_mult -= static_cast<FloatBase>(2.0);
		}

	// write (dd_ldb, 3) 2, max_iter;
	// call_dd_abrt
	// /* label */ JMP_130:

		terf = static_cast<FloatBase>(1.0) - (
			taylor_sum * (LDF::const_inv_sqrtpi<FloatNxN>() * exp(-z2))
		);
		if (isless_zero(z)) { // sign(z) < 0
			terf = -terf;
		}
	}

	return terf;
}

/** 
 * @author Taken from libDDFUN ddfune.f90 which can be found under a
 * Limited-BSD license from https://www.davidhbailey.com/dhbsoftware/
 * @remarks It appears that the exact same implementation is used in
 * libQDFUN as well.
 * @brief Uses up to floor(x^2 + 0.5) iterations to calculate erfc(x)
 */
template<
	typename FloatNxN, typename FloatBase,
	int max_iter
>
static inline FloatNxN libDDFUN_erfc(const FloatNxN& z) {
	//   This evaluates the erf function, using a combination of two series.
	//   In particular, the algorithm is
	//   (where B = FloatNxN_Count * FloatN_Mantissa_Bits, and
	//   dcon is a constant defined below):
	//
	//   if (z == 0) {
	//     erfc = 1;
	//   } else if (z > sqrt(B*log(2))) {
	//     erfc = 0;
	//   } else if (z < -sqrt(B*log(2))) {
	//     erfc = 2;
	//   } else if (abs(z) < B/dcon + 8) {
	//     erfc = 1 - 2 / (sqrt(pi)*exp(z^2)) * Sum_{k>=0} 2^k * z^(2*k+1);
	//               / (1.3....(2*k+1));
	//   } else {
	//     erfc = 1 / (sqrt(pi)*exp(z^2));
	//             * Sum_{k>=0} (-1)^k * (1.3...(2*k-1)) / (2^k * z^(2*k+1));
	//   }

	// FloatNxN, intent(in):: z
	// FloatNxN, intent(out):: terfc
	FloatNxN terfc;

	constexpr FloatBase dcon = static_cast<FloatBase>(100.0); /**< Unknown magic number */
	FloatNxN t5, t6;

	// int dd_nw, dd_nw1;
	// dd_nw = Float80x2_count;
	// dd_nw1 = std::min(dd_nw + 1, Float80x2_count);
	const FloatBase target_epsilon = ldexp(
		static_cast<FloatBase>(1.0),
		-LDF::LDF_Type_Info<FloatNxN>::FloatBase_Count * std::numeric_limits<FloatBase>::digits
	);

	__attribute__((unused)) const FloatBase d1 = trunc(static_cast<FloatBase>(1.0) + sqrt(
		static_cast<FloatBase>(std::numeric_limits<FloatNxN>::digits) * LDF::const_ln2<FloatBase>()
	));
	__attribute__((unused)) const FloatBase d2 = trunc((
		static_cast<FloatBase>(std::numeric_limits<FloatNxN>::digits) / dcon
	) + static_cast<FloatBase>(8.0));


	/**
	 * @remarks z will go to +1.0 instead of +2.0 or +0.0 when it is outside
	 * the range of either d1 or d2. I am not sure which one of the two values
	 * it follows.
	 */
	if (isequal_zero(z)) { // sign(z) == 0
		// z == 0.0
		return static_cast<FloatBase>(1.0);
	}
	if ((isinf(z) && isgreater_zero(z)) /* || z > d1 */) {
		// z == +inf
		return static_cast<FloatBase>(0.0);
	}
	if ((isinf(z) && isless_zero(z)) || z < -d1) {
		// z == -inf
		return static_cast<FloatBase>(2.0);
	}

	const FloatNxN z2 = square(z);
#if 0
	if (z < d2) {
#else
	// d2 / 2.0 is a guess
	if (z < d2 / static_cast<FloatBase>(2.0)) {
#endif
		FloatNxN taylor_sum = static_cast<FloatBase>(0.0);
		
		// I'm guessing that it was supposed to check that z < 1.0e10, breaking/returning otherwise.
		// t5 = static_cast<FloatBase>(1.0e10);

		FloatNxN taylor_val = z;

		const FloatNxN z2_mul2 = mul_pwr2(z2, static_cast<FloatBase>(2.0));

		t5 = static_cast<FloatBase>(1.0e10);
		FloatBase k_mult = static_cast<FloatBase>(3.0);
		for (int k = 1; k <= max_iter; k++) {
			taylor_val /= k_mult;
			taylor_val *= z2_mul2;

			taylor_sum += taylor_val;
			t6 = taylor_val / (taylor_sum + z);

			// Unordered comparisions protect against NAN
			if (!(t6 > target_epsilon) || t6 >= t5) {
				// goto JMP_120;
				break;
			}
			t5 = t6;
			
			k_mult += static_cast<FloatBase>(2.0);
		}
		taylor_sum += z;

	// write (dd_ldb, 3) 1, max_iter;
	// 3 format ('*** DDERFCR: iteration limit exceeded',2i10);
	// call_dd_abrt
	// /* label */ JMP_120:

		terfc = static_cast<FloatBase>(1.0) - (
			mul_pwr2(taylor_sum, static_cast<FloatBase>(2.0)) *
			LDF::const_inv_sqrtpi<FloatNxN>() * exp(-z2)
		);
#if 1
	} else if(z < d2) {
		// Best solution until I can resolve the accuracy problems between 0.0 and d2
		return static_cast<FloatNxN>(erfc(static_cast<FloatBase>(z)));
#endif
	} else {
		/**
		 * @author This algorithm was described in this paper
		 * S. Chevillard,
		 * The functions erf and erfc computed with arbitrary precision and explicit error bounds,
		 * Information and Computation,
		 * Volume 216,
		 * 2012,
		 * Pages 72-95,
		 * ISSN 0890-5401,
		 * https://doi.org/10.1016/j.ic.2011.09.001.
		 * (https://www.sciencedirect.com/science/article/pii/S0890540112000697)
		 * 
		 */
		 
		const FloatNxN result_mult = LDF::const_inv_sqrtpi<FloatNxN>() * exp(-z2) / z;
		const FloatNxN z2_mul2 = mul_pwr2(z2, static_cast<FloatBase>(2.0));

		FloatNxN taylor_sum = static_cast<FloatBase>(0.0);
		int term_count = static_cast<int>(static_cast<FloatBase>(
			floor(z2 + static_cast<FloatBase>(0.5))
		));

		FloatBase fact_term = static_cast<FloatBase>(1.0);
		FloatNxN fact_prod = static_cast<FloatBase>(1.0);
		FloatNxN recip_z2_mul2 = recip(z2_mul2);
		for (int i = 1; i <= term_count; i++) {
			fact_prod *= fact_term;
			fact_prod *= recip_z2_mul2;

			taylor_sum += (i % 2 != 0) ? -fact_prod : fact_prod;
			fact_term += static_cast<FloatBase>(2.0);
		}
		
		terfc = result_mult * (static_cast<FloatBase>(1.0) + (taylor_sum));

	}

	return terfc;
}

#endif /* FLOATNXN_ERF_HPP */
