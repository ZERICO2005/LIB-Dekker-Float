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

#ifndef FLOATNXN_INCGAMMA_HPP
#define FLOATNXN_INCGAMMA_HPP

#include "../LDF/LDF_type_info.hpp"
#include "../LDF/LDF_constants.hpp"

#include <cmath>
#include <limits>
#include <cassert>
#include <cstdio>

#include "FloatNxN_fortran_def.h"

/**
 * @brief Computes the incomplete Gamma function
 */
template <
	typename FloatNxN, typename FloatBase,
	int max_iter
>
static inline FloatNxN libDDFUN_incgamma(const FloatNxN& s, const FloatNxN& z) {

	// This returns the incomplete gamma function, using a combination of formula
	// 8.7.3 of the DLMF (for modest-sized z), formula 8.11.2 (for large z),
	// a formula from the Wikipedia page for the case S = 0, and another formula
	// from the Wikipedia page for the case S = negative integer. The formula
	// for the case S = 0 requires increased working precision, up to 2.5X normal,
	// depending on the size of Z.
		
	// implicit none
	// real (dd_knd), intent(in):: s(1:2), z(1:2);
	// real (dd_knd), intent(out):: g(1:2);
	FloatNxN g;
	// integer, parameter:: max_iter = 1000000
	constexpr FloatBase dmax = 0.833e0;
	// constexpr FloatBase egam = 0.5772156649015328606e0;
	int ic1, k, nn, n1, n2;
	FloatBase d1, d2, bits;
	FloatNxN t0, t1, t2, t3, t4, t5, f1, tc1, tc2, tc3, target_epsilon;

	// End of declaration
	int dd_nw, dd_nw1;
	// int dd_nw2; // unused?

	constexpr int dd_nwx = LDF::LDF_Type_Info<FloatNxN>::FloatBase_Count;
	constexpr int dd_nbt = std::numeric_limits<FloatBase>::digits;

	dd_nw = dd_nwx;

	n1 = call_dd_sgn (s);
	n2 = call_dd_sgn (z);
	if (n2 == 0 || (n1 != 0 && n2 < 0)) {
		// 	write (dd_ldb, 2);
		// 2 format ('*** DDINCGAMMAR: The second argument must not be zero,'/ &
		// 		'and must not be negative unless the first is zero.');
		// 	call_dd_abrt
		printf("*** DDINCGAMMAR: Loop end error 1\n");
		return std::numeric_limits<FloatNxN>::quiet_NaN();
	}

	dd_nw1 = std::min(dd_nw + 1, dd_nwx);
	call_dd_dmc (static_cast<FloatBase>(2.0), 0, tc1);
	call_dd_npwr (tc1, -dd_nw1 * dd_nbt, target_epsilon);

	call_dd_dmc (static_cast<FloatBase>(1.0), 0, f1);
	call_dd_mdc (z, d1, n1);
	d1 = d1 * ldexp(static_cast<FloatBase>(1.0), n1);
	bits = dd_nw1 * dd_nbt;

	if (abs (d1) < dmax * bits) {

		//  This is for modest-sized z.

		call_dd_infr (s, t1, t2);
		call_dd_cpr (s, t1, ic1);
		call_dd_mdc (s, d2, n2);
		
		// nn = d2 * ldexp(static_cast<FloatBase>(1.0), n2);
		nn = call_dd_int_ldexp(d2, n2);

		if (ic1 == 0 && nn == 1) {

		//  S = 1; result is exp (-z).

			call_dd_neg (z, t0);
			call_dd_exp (t0, t1);
			goto JMP_200;
		} else if (ic1 == 0 && nn <= 0) {

		//   S is zero or a negative integer -- use a different algorithm. In
		//   either event, first compute incgamma for S = 0. For large Z, the
		//   working precision must be increased, up to 2.5X times normal.

		//   mpnw2 = min (mpnw1 + 1.5d0 * d1 / (dmax * bits) * mpnw, 5*mpnw/2+1.d0);
			// dd_nw2 = dd_nw1; // unused?
			call_dd_eq (z, t0);
			call_dd_eq (z, t1);
			call_dd_dmc (static_cast<FloatBase>(1.0), 0, t2);

			for (k = 2; k <= max_iter; k++) {
				if (fortran_mod (k, 2) == 1) {
					d1 = fortran_dble (k);
					call_dd_divd (f1, d1, t3);
					call_dd_add(t2, t3, t4);
					call_dd_eq (t4, t2);
				}
				call_dd_mul (z, t1, t3);
				d1 = static_cast<FloatBase>(2.0) * fortran_dble (k);
				call_dd_divd (t3, d1, t1);
				call_dd_mul (t1, t2, t3);
				call_dd_add(t0, t3, t4);
				call_dd_eq (t4, t0);

				call_dd_abs (t3, tc1);
				call_dd_mul (target_epsilon, t0, tc3);
				call_dd_abs (tc3, tc2);
				call_dd_cpr (tc1, tc2, ic1);
				if (ic1 <= 0) {
					goto JMP_100;
				}
			}

	// 		write (dd_ldb, 4);
	// 4   format ('*** DDINCGAMMAR: Loop end error 1');
	// 		call_dd_abrt
	printf("*** DDINCGAMMAR: Loop end error 1\n");
	return std::numeric_limits<FloatNxN>::quiet_NaN();

	/* continue */ JMP_100:

			call_dd_neg (LDF::const_egamma<FloatNxN>(), t1);
			call_dd_abs (z, t3);
			call_dd_log (t3, t2);
			call_dd_sub (t1, t2, t3);
			call_dd_muld (z, static_cast<FloatBase>(-0.5), t4);
			call_dd_exp (t4, t5);
			call_dd_mul (t5, t0, t4);
			call_dd_add(t3, t4, t1);
			if (nn == 0) {
				goto JMP_200;
			}

			//  S is negative integer (not zero).

			nn = abs (nn);
			call_dd_dmc (static_cast<FloatBase>(1.0), 0, t0);
			call_dd_eq (t0, t2);

			for (k = 1; k <= nn - 1; k++) {
				call_dd_muld (t0, fortran_dble (k), t2);
				call_dd_eq (t2, t0);
			}

			call_dd_muld (t0, fortran_dble (nn), t5);

			for (k = 1; k <= nn - 1; k++) {
				call_dd_mul (t2, z, t3);
				call_dd_divd (t3, fortran_dble (nn - k), t4);
				call_dd_neg (t4, t2);
				call_dd_add(t0, t2, t3);
				call_dd_eq (t3, t0);
			}

			call_dd_exp (z, t2);
			call_dd_div (t0, t2, t3);
			call_dd_npwr (z, nn, t4);
			call_dd_div (t3, t4, t2);

			if (fortran_mod (nn, 2) == 0) {
				call_dd_add(t2, t1, t3);
			} else {
				call_dd_sub (t2, t1, t3);
			}
			call_dd_div (t3, t5, t1);
			goto JMP_200;
		}

		call_dd_gammar (s, t1);
		call_dd_mul (s, t1, t3);
		call_dd_div (f1, t3, t2);
		call_dd_eq (t2, t0);

		for (k = 1; k <= max_iter; k++) {
			call_dd_mul (t2, z, t5);
			call_dd_dmc (fortran_dble (k), 0, t3);
			call_dd_add(s, t3, t4);
			call_dd_div (t5, t4, t2);
			call_dd_add(t0, t2, t3);
			call_dd_eq (t3, t0);

			call_dd_abs (t2, tc1);
			call_dd_mul (target_epsilon, t0, tc3);
			call_dd_abs (tc3, tc2);
			call_dd_cpr (tc1, tc2, ic1);
			if (ic1 <= 0) {
				goto JMP_110;
			}
		}

	// 	write (dd_ldb, 5) max_iter
	// 5   format ('*** DDINCGAMMAR: Loop end error 1');
	// 	call_dd_abrt
	printf("*** DDINCGAMMAR: Loop end error 1\n");
	return std::numeric_limits<FloatNxN>::quiet_NaN();

	/* continue */ JMP_110:

		call_dd_power (z, s, t2);
		call_dd_exp (z, t3);
		call_dd_div (t2, t3, t4);
		call_dd_mul (t4, t0, t5);
		call_dd_sub (f1, t5, t2);
		call_dd_mul (t1, t2, t3);
		call_dd_eq (t3, t1);
		goto JMP_200;
	} else {

		//  This is for large z. Note that if S is a positive integer, this loop
		//  is finite.

		call_dd_dmc (static_cast<FloatBase>(1.0), 0, t0);
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, t1);

		for (k = 1; k <= max_iter; k++) {
			call_dd_dmc (fortran_dble (k), 0, t2);
			call_dd_sub (s, t2, t3);
			call_dd_mul (t1, t3, t4);
			call_dd_div (t4, z, t1);
			call_dd_add(t0, t1, t2);
			call_dd_eq (t2, t0);

			call_dd_abs (t1, tc1);
			call_dd_mul (target_epsilon, t0, tc3);
			call_dd_abs (tc3, tc2);
			call_dd_cpr (tc1, tc2, ic1);
			if (ic1 <= 0) {
				goto JMP_120;
			}
		}

	// 	write (dd_ldb, 6);
	// 6 format ('*** DDINCGAMMAR: Loop end error 3');
	// 	call_dd_abrt
	printf("*** DDINCGAMMAR: Loop end error 3\n");
	return std::numeric_limits<FloatNxN>::quiet_NaN();

	/* continue */ JMP_120:

		call_dd_sub (s, f1, t2);
		call_dd_power (z, t2, t3);
		call_dd_exp (z, t4);
		call_dd_div (t3, t4, t2);
		call_dd_mul (t2, t0, t1);
		goto JMP_200;
	}

	/* continue */ JMP_200:

	call_dd_eq (t1, g);

	return g;
}


template <
	typename FloatNxN, typename FloatBase,
	int max_iter
>
FloatNxN libDDFUN_expint(const FloatNxN& x) {
	// This evaluates the exponential integral function Ei(x):
	// Ei(x) = - incgamma (0, -x)

	if (isequal_zero(x)) {
		// write (ddldb, 2)
		// 2 format ('*** DDEXPINT: argument is zero')
		// call ddabrt
		return std::numeric_limits<FloatNxN>::quiet_NaN();
	}

	return -libDDFUN_incgamma<
		FloatNxN, FloatBase,
		max_iter
	> (static_cast<FloatBase>(0.0), -x);
}

#endif /* FLOATNXN_INCGAMMA_HPP */