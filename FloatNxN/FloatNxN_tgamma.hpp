/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

/*
**	Portions of this file were part of the libDQFUN library
**	libDQFUN is licensed under a limited BSD license that can be found below:
**	https://www.davidhbailey.com/dhbsoftware/DHB-License.docx
**	Or alternatively from this website:
**	https://www.davidhbailey.com/dhbsoftware/
**	A copy of the Limited-BSD-License can also be found at:
**	LIB-Dekker-Float/libDQFUN/DISCLAIMER_and_Limited-BSD-License.txt
*/

#ifndef FLOATNXN_TGAMMA_HPP
#define FLOATNXN_TGAMMA_HPP

#include "../LDF/LDF_type_info.hpp"
#include "../LDF/LDF_constants.hpp"

#include <cmath>
#include <limits>
#include <cassert>

#include "FloatNxN_fortran_def.h"

//------------------------------------------------------------------------------
// FloatNxN tgamma
//------------------------------------------------------------------------------

/**
 * @brief Computes the Gamma function, or (t - 1)!
 */
template <
	typename FloatNxN, typename FloatBase,
	int max_iter
>
static inline FloatNxN libDQFUN_tgamma(const FloatNxN& t) {
	// This evaluates the gamma function, using an algorithm of R. W. Potter.
	// The argument t must not exceed 10^8 in size (this limit is set below),
	// must not be zero, and if negative must not be integer.

	// In the parameter statement below:
	// 	max_iter = limit of number of iterations in series; default = 100000.
	// 	con1 = 1/2 * log (10) to DP accuracy.
	// 	dmax = maximum size of input argument.

	// FloatNxN, intent(in):: t;
	// FloatNxN, intent(out):: z;
	
	FloatNxN z;
	FloatBase d2;
	FloatNxN taylor_sum, sum_t_pos, sum_t_neg, tn;
	FloatBase target_epsilon;

	target_epsilon = ldexp(
		static_cast<FloatBase>(1.0),
		-LDF::LDF_Type_Info<FloatNxN>::FloatBase_Count * std::numeric_limits<FloatBase>::digits
	);

	// const FloatNxN t_trunc_part = trunc(t);
	FloatNxN t_trunc_part, t_frac_part;

	// Find the integer and fractional parts of t.
	call_dq_infr(t, t_trunc_part, t_frac_part);
	
	// asserts that the conversion to `int` will be exact
	assert(t_trunc_part == static_cast<FloatNxN>((static_cast<int>(t_trunc_part))));

	#if 0
		// Original Code

		// This constant appears to be very conservative
		constexpr FloatBase dmax = static_cast<FloatBase>(1.0e+8);
		FloatBase d1;
		int i1, ic1, n1;

		/**
		 * @remarks Checks if `t` is too large for the algorithm
		 */
		call_dq_mdc(t, d1, n1);
		d1 = ldexp(d1, n1);
		
		call_dq_nint(t, taylor_sum);
		call_dq_cpr(t, taylor_sum, ic1);
		i1 = call_dq_sgn(t);
		if (i1 == 0 || d1 > dmax || (i1 < 0 && ic1 == 0)) {
			// write (dq_ldb, 2) dmax
			// 2 format ('*** DQGAMMAR: input argument must have absolute value <=',f10.0,','/ &
			// 'must not be zero, and if negative must not be an integer.')
			// call_dq_abrt
			printf(
				"*** DQGAMMAR: input argument must have absolute value <= %#Lg, must not be zero, and if negative must not be an integer.\n",
				static_cast<long double>(dmax)
			);
			
			return std::numeric_limits<FloatNxN>::quiet_NaN();
		}
	#endif

	// Checks if `t` is an integer
	if (t_trunc_part == t) {
		if (islessequal_zero(t)) {
			// `t` must be a positive integer
			return std::numeric_limits<FloatNxN>::quiet_NaN();
		}
		// If t is a positive integer, then apply the usual factorial recursion.
		
		const int nt = static_cast<int>(t_trunc_part);

		z = static_cast<FloatBase>(1.0);
		FloatBase term_iter = static_cast<FloatBase>(2.0);
		for (int i = 2; i <= nt - 1; i++) {
			z *= term_iter;
			term_iter++;
		}
		return z;
	}

	// Checks if `t` is an integer multiple of 0.5
	const FloatNxN t_mul2 = mul_pwr2(t, static_cast<FloatBase>(2.0));
	const FloatNxN t_mul2_trunc_part = trunc(t_mul2);
	if (t_mul2_trunc_part == t_mul2) {
		
		const int t_fabs = static_cast<int>(fabs(floor(t)));
		const int term_count = t_fabs * 2 - 1;
		
		z = static_cast<FloatBase>(1.0);
		FloatBase term_iter = static_cast<FloatBase>(1.0);

		// Computes (2n - 1)!!
		for (int i = 0; i < term_count; i += 2) {
			z *= term_iter;
			term_iter += static_cast<FloatBase>(2.0);
		}
		if (isgreater_zero(t)) {
			z = ldexp(z, -t_fabs);
		} else {
			z = ldexp(recip(z), t_fabs);
			if (t_fabs % 2 != 0) {
				z = -z;
			}
		}
		
		// (n + 0.5)! will be a multiple of sqrt(pi)
		return z * LDF::const_sqrtpi<FloatNxN>();
	}

	if (isgreater_zero(t)) {

	// Apply the identity Gamma[t+1] = t * Gamma[t] to reduce the input argument
	// to the unit interval.
		
		const int nt = static_cast<int>(t_trunc_part);

		taylor_sum = static_cast<FloatBase>(1.0);
		tn = t_frac_part;
		
		FloatBase term_iter = static_cast<FloatBase>(1.0);
		for (int i = 1; i <= nt; i++) {
			taylor_sum *= (t - term_iter);
			term_iter++;
		}
	} else {

	// Apply the gamma identity to reduce a negative argument to the unit interval.

		const int nt = static_cast<int>(static_cast<FloatBase>(1.0) - t_trunc_part);
		taylor_sum = static_cast<FloatBase>(1.0);
		tn = static_cast<FloatBase>(1.0) + t_frac_part;

		FloatBase term_iter = static_cast<FloatBase>(0.0);
		for (int i = 0; i <= nt - 1; i++) {
			taylor_sum /= (t + term_iter);
			term_iter++;
		}
	}

	// Calculate alpha = bits of precision * log(2) / 2, { take the next even
	// integer value, so that alpha/2 and alpha^2/4 can be calculated exactly in DP.

	FloatBase alpha = static_cast<FloatBase>(2.0) * trunc(
		static_cast<FloatBase>(1.0) + (static_cast<FloatBase>(
				(LDF::LDF_Type_Info<FloatNxN>::FloatBase_Count + 1) * std::numeric_limits<FloatBase>::digits
		) * LDF::const_ln2<FloatBase>()) * static_cast<FloatBase>(0.25)
	);
	d2 = static_cast<FloatBase>(0.25) * (alpha * alpha);

	/* Evaluate the series with +t */ {
		int iter;
		FloatBase term_iter = static_cast<FloatBase>(1.0);
		FloatNxN term = recip(tn); 
		sum_t_pos = term;
		for (iter = 1; iter <= max_iter; iter++) {
			term /= (tn + term_iter) * term_iter;
			term *= d2;
			sum_t_pos += term;

			if (fabs(term) <= fabs(mul_pwr2(target_epsilon, sum_t_pos))) {
				break;
			}
			term_iter++;
		}
		#if 0
			if (iter > max_iter) {
				// write (dq_ldb, 3) 1, max_iter
				// 3 format ('*** DQGAMMAR: iteration limit exceeded',2i10);
				// call_dq_abrt
				printf("*** DQGAMMAR: +t iteration limit exceeded %d\n", max_iter);
				return z;
			}
		#endif
	}

	/* Evaluate the series with +t */ {

		int iter;
		FloatBase term_iter = static_cast<FloatBase>(1.0);
		FloatNxN term = recip(-tn); 
		sum_t_neg = term;

		for (iter = 1; iter <= max_iter; iter++) {
			term /= (term_iter - tn) * term_iter;
			term *= d2;
			sum_t_neg += term;

			if (fabs(term) <= fabs(mul_pwr2(target_epsilon, sum_t_neg))) {
				break;
			}
			term_iter++;
		}
		#if 0
			if (iter > max_iter) {
				// write (dq_ldb, 3) 2, max_iter
				// call_dq_abrt
				printf("*** DQGAMMAR: -t iteration limit exceeded %d\n", max_iter);
				return z;
			}
		#endif
	}

	// Compute sqrt (pi * sum_t_pos / (tn * sin (pi * tn) * sum_t_neg))
	// and (alpha/2)^tn terms. Also, multiply by the factor taylor_sum, from the
	// If block above.

	z = taylor_sum * (
		sqrt(-(
			(LDF::const_pi<FloatNxN>() * sum_t_pos) / (tn * (sin(LDF::const_pi<FloatNxN>() * tn) * sum_t_neg))
		)) * exp(tn * log(
			static_cast<FloatNxN>(static_cast<FloatBase>(0.5) * alpha)
		))
	);

	// Round to mpnw words precision.

	return z;
}

#endif /* FLOATNXN_TGAMMA_HPP */
