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

#ifndef FLOATNXN_CYL_BESSEL_HPP
#define FLOATNXN_CYL_BESSEL_HPP

#include "../LDF/LDF_type_info.hpp"
#include "../LDF/LDF_constants.hpp"

#include <limits>
#include <cmath>

#include "FloatNxN_fortran_def.h"


template<
	typename FloatNxN, typename FloatBase,
	int max_iter
>
static inline FloatNxN libDDFUN_besselinr(const int nu, const FloatNxN& rr) {

	//  This evaluates the modified Bessel function BesselI (NU,RR).
	//  NU is an integer. The algorithm is DLMF formula 10.25.2 for modest RR,
	//  and DLMF 10.40.1 for large RR, relative to precision.

	// implicit none
	// integer, intent(in):: nu
	// FloatNxN, intent(in):: rr;
	// FloatNxN, intent(out):: ss;
	// integer, parameter:: max_iter = 1000000
	FloatNxN ss;
	constexpr FloatBase dfrac = static_cast<FloatBase>(1.5);
	constexpr FloatBase pi = static_cast<FloatBase>(3.1415926535897932385);
	int ic1, k, nua, n1;
	FloatBase d1;
	FloatNxN f1, f2, sum, td, tn, t1, t2, t3, t4, rra, tc1, tc2, tc3, target_epsilon;

	constexpr int dd_nwx = LDF::LDF_Type_Info<FloatNxN>::FloatBase_Count;
	constexpr int dd_nbt = std::numeric_limits<FloatBase>::digits;
	constexpr FloatBase dd_dpw = static_cast<FloatBase>(std::numeric_limits<FloatBase>::digits) * static_cast<FloatBase>(0.30102999566398119521373889472449);

	// End of declaration
	int dd_nw, dd_nw1, dd_nw2;



	dd_nw = dd_nwx;

	//  Check for RR = 0.

	if (call_dd_sgn (rr) == 0) {
		// write (ddldb, 2);
		// 2 format ('*** DDBESSELINR: Second argument is zero');
		// call_dd_abrt
		printf("Line: %d *** DDBESSELINR: Second argument is zero\n", __LINE__);
		return std::numeric_limits<FloatNxN>::quiet_NaN();
	}

	dd_nw1 = std::min(dd_nw + 1, dd_nwx);
	nua = abs (nu);
	call_dd_dmc (static_cast<FloatBase>(2.0), 0, tc1);
	call_dd_npwr (tc1, -dd_nw1*dd_nbt, target_epsilon);
	call_dd_abs (rr, rra);
	call_dd_mdc (rra, d1, n1);
	d1 = ldexp(d1, n1);

	if (d1 < dfrac * dd_nw1 * dd_dpw) {
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, tn);
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, f1);
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, f2);
		call_dd_mul (rra, rra, t2);
		call_dd_muld (t2, static_cast<FloatBase>(0.25), t1);

		for (k = 1; k <= nua; k++) {
			call_dd_muld (f2, fortran_dble (k), t2);
			call_dd_eq (t2, f2);
		}

		call_dd_mul (f1, f2, td);
		call_dd_div (tn, td, t2);
		call_dd_eq (t2, sum);

		for (k = 1; k <= max_iter; k++) {
			call_dd_muld (f1, fortran_dble (k), t2);
			call_dd_eq (t2, f1);
			call_dd_muld (f2, fortran_dble (k + nua), t2);
			call_dd_eq (t2, f2);
			call_dd_mul (t1, tn, t2);
			call_dd_eq (t2, tn);
			call_dd_mul (f1, f2, td);
			call_dd_div (tn, td, t2);
			call_dd_add (sum, t2, t3);
			call_dd_eq (t3, sum);

			call_dd_abs (t2, tc1);
			call_dd_mul (target_epsilon, sum, tc3);
			call_dd_abs (tc3, tc2);
			call_dd_cpr (tc1, tc2, ic1);
			if (ic1 <= 0) goto JMP_100;
		}

		// write (ddldb, 4);
		// 4 format ('*** DDBESSELINR: Loop end error 1');
		// call_dd_abrt
		printf("Line: %d *** DDBESSELINR: Loop end error 1\n", __LINE__);
		return std::numeric_limits<FloatNxN>::quiet_NaN();

	/* continue */ JMP_100:

		call_dd_muld (rra, static_cast<FloatBase>(0.5), t1);
		call_dd_npwr (t1, nua, t2);
		call_dd_mul (sum, t2, t3);
	} else {
	// sum1 = mpreal (static_cast<FloatBase>(1.0), mpnw);
	// t1 = mpreal (static_cast<FloatBase>(4.0) * fortran_dble (nua)**2, mpnw);
	// t2 = mpreal (static_cast<FloatBase>(1.0), mpnw);
	// t3 = mpreal (static_cast<FloatBase>(1.0), mpnw);

		call_dd_dmc (static_cast<FloatBase>(1.0), 0, sum);
		d1 = static_cast<FloatBase>(4.0) * square(fortran_dble (nua));
		call_dd_dmc (d1, 0, t1);
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, tn);
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, td);

		for (k = 1; k <= max_iter; k++) {
	// t2 = -t2 * (t1 - (static_cast<FloatBase>(2.0) * k - static_cast<FloatBase>(1.0))**2);
	// t3 = t3 * fortran_dble (k) * static_cast<FloatBase>(8.0) * xa
	// t4 = t2 / t3
	// sum1 = sum1 + t4

			d1 = static_cast<FloatBase>(2.0) * k - static_cast<FloatBase>(1.0);
			call_dd_dmc (d1, 0, t2);
			call_dd_mul (t2, t2, t3);
			call_dd_sub (t1, t3, t2);
			call_dd_mul (tn, t2, t3);
			call_dd_neg (t3, tn);
			call_dd_muld (rra, static_cast<FloatBase>(8.0) * k, t2);
			call_dd_mul (td, t2, t3);
			call_dd_eq (t3, td);
			call_dd_div (tn, td, t4);
			call_dd_add (sum, t4, t3);
			call_dd_eq (t3, sum);

	//  if (abs (t4) / abs (sum1) < target_epsilon) goto JMP_110;

			call_dd_abs (t4, tc1);
			call_dd_mul (target_epsilon, sum, tc3);
			call_dd_abs (tc3, tc2);
			call_dd_cpr (tc1, tc2, ic1);
			if (ic1 <= 0) goto JMP_110;
		}

	// write (ddldb, 5);
	// 5 format ('*** DDBESSELINR: Loop end error 2');
	// call_dd_abrt
	printf("Line: %d *** DDBESSELINR: Loop end error 2\n", __LINE__);
	return std::numeric_limits<FloatNxN>::quiet_NaN();

	/* continue */ JMP_110:

	//t1 = exp (xa) / sqrt (static_cast<FloatBase>(2.0) * mppi (mpnw) * xa);
	//besseli = t1 * sum1

		call_dd_exp (rra, t1);
		call_dd_muld (LDF::const_pi<FloatNxN>(), static_cast<FloatBase>(2.0), t2);
		call_dd_mul (t2, rra, t3);
		call_dd_sqrt (t3, t4);
		call_dd_div (t1, t4, t2);
		call_dd_mul (t2, sum, t3);
	}

	//if (x < static_cast<FloatBase>(0.0) && fortran_mod (nu, 2) != 0) besseli = - besseli

	if (call_dd_sgn (rr) < 0 && fortran_mod (nu, 2) != 0) {
		call_dd_neg (t3, t4);
		call_dd_eq (t4, t3);
	}

	call_dd_eq (t3, ss);

	return ss;
}

template<
	typename FloatNxN, typename FloatBase,
	int max_iter
>
static inline FloatNxN libDDFUN_besselir(const FloatNxN& qq, const FloatNxN& rr) {

	//  This evaluates the modified Bessel function BesselI (QQ,RR) for QQ and RR
	//  both MPR. The algorithm is DLMF formula 10.25.2 for modest RR, and
	//  DLMF 10.40.1 for large RR, relative to precision.

	// implicit none
	// FloatNxN, intent(in):: qq, rr;
	// FloatNxN, intent(out):: ss;
	FloatNxN ss;
	int ic1, i1, i2, k, n1;
	// integer, parameter:: max_iter = 1000000
	constexpr FloatBase dfrac = static_cast<FloatBase>(1.5);
	constexpr FloatBase pi = static_cast<FloatBase>(3.1415926535897932385);
	FloatBase d1;
	FloatNxN f1, f2, sum, td, tn, t1, t2, t3, t4, rra, tc1, tc2, tc3, target_epsilon;

	constexpr int dd_nwx = LDF::LDF_Type_Info<FloatNxN>::FloatBase_Count;
	constexpr int dd_nbt = std::numeric_limits<FloatBase>::digits;
	constexpr FloatBase dd_dpw = static_cast<FloatBase>(std::numeric_limits<FloatBase>::digits) * static_cast<FloatBase>(0.30102999566398119521373889472449);

	// End of declaration
	int dd_nw, dd_nw1, dd_nw2;



	dd_nw = dd_nwx;

	dd_nw1 = std::min(dd_nw + 1, dd_nwx);
	call_dd_dmc (static_cast<FloatBase>(2.0), 0, tc1);
	call_dd_npwr (tc1, -dd_nw1*dd_nbt, target_epsilon);

	//  If QQ is integer, call_mpbesselinr; if qq < 0 and rr <= 0, then error.

	call_dd_infr (qq, t1, t2);
	i1 = call_dd_sgn (qq);
	i2 = call_dd_sgn (rr);
	if (call_dd_sgn (t2) == 0) {
		call_dd_mdc (qq, d1, n1);
		d1 = ldexp(d1, n1);
		n1 = fortran_nint (d1);
		call_dd_besselinr (n1, rr, t3);
		goto JMP_120;
	} else if (i1 < 0 && i2 <= 0) {
		// write (ddldb, 3);
		// 3 format ('*** DDBESSELIR: First argument < 0 and second argument <= 0');
		// call_dd_abrt
		printf("Line: %d *** DDBESSELIR: First argument < 0 and second argument <= 0\n", __LINE__);
		return std::numeric_limits<FloatNxN>::quiet_NaN();
	}

	call_dd_abs (rr, rra);
	call_dd_mdc (rra, d1, n1);
	d1 = ldexp(d1, n1);

	if (d1 < dfrac * dd_nw1 * dd_dpw) {
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, tn);
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, f1);
		call_dd_add (qq, f1, t1);
		call_dd_gammar (t1, f2);
		call_dd_mul (rra, rra, t2);
		call_dd_muld (t2, static_cast<FloatBase>(0.25), t1);

		call_dd_mul (f1, f2, td);
		call_dd_div (tn, td, t2);
		call_dd_eq (t2, sum);

		for (k = 1; k <= max_iter; k++) {
			call_dd_muld (f1, fortran_dble (k), t2);
			call_dd_eq (t2, f1);
			call_dd_dmc (fortran_dble (k), 0, t3);
			call_dd_add (qq, t3, t4);
			call_dd_mul (f2, t4, t3);
			call_dd_eq (t3, f2);
			call_dd_mul (t1, tn, t2);
			call_dd_eq (t2, tn);
			call_dd_mul (f1, f2, td);
			call_dd_div (tn, td, t2);
			call_dd_add (sum, t2, t3);
			call_dd_eq (t3, sum);

			call_dd_abs (t2, tc1);
			call_dd_mul (target_epsilon, sum, tc3);
			call_dd_abs (tc3, tc2);
			call_dd_cpr (tc1, tc2, ic1);
			if (ic1 <= 0) goto JMP_100;
		}

		// write (ddldb, 4);
		// 4 format ('*** DDBESSELIR: Loop end error 1');
		// call_dd_abrt
		printf("Line: %d *** DDBESSELIR: Loop end error 1\n", __LINE__);
		return std::numeric_limits<FloatNxN>::quiet_NaN();

	/* continue */ JMP_100:

		call_dd_muld (rra, static_cast<FloatBase>(0.5), t1);
		call_dd_power (t1, qq, t2);
		call_dd_mul (sum, t2, t3);
	} else {
	// sum1 = mpreal (static_cast<FloatBase>(1.0), mpnw);
	// t1 = mpreal (static_cast<FloatBase>(4.0) * fortran_dble (nua)**2, mpnw);
	// t2 = mpreal (static_cast<FloatBase>(1.0), mpnw);
	// t3 = mpreal (static_cast<FloatBase>(1.0), mpnw);

		call_dd_dmc (static_cast<FloatBase>(1.0), 0, sum);
		call_dd_mul (qq, qq, t2);
		call_dd_muld (t2, static_cast<FloatBase>(4.0), t1);
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, tn);
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, td);

		for (k = 1; k <= max_iter; k++) {
	// t2 = -t2 * (t1 - (static_cast<FloatBase>(2.0) * k - static_cast<FloatBase>(1.0))**2);
	// t3 = t3 * fortran_dble (k) * static_cast<FloatBase>(8.0) * xa
	// t4 = t2 / t3
	// sum1 = sum1 + t4

			d1 = static_cast<FloatBase>(2.0) * k - static_cast<FloatBase>(1.0);
			call_dd_dmc (d1, 0, t2);
			call_dd_mul (t2, t2, t3);
			call_dd_sub (t1, t3, t2);
			call_dd_mul (tn, t2, t3);
			call_dd_neg (t3, tn);
			call_dd_muld (rra, static_cast<FloatBase>(8.0) * k, t2);
			call_dd_mul (td, t2, t3);
			call_dd_eq (t3, td);
			call_dd_div (tn, td, t4);
			call_dd_add (sum, t4, t3);
			call_dd_eq (t3, sum);

	//  if (abs (t4) / abs (sum1) < target_epsilon) goto JMP_110;

			call_dd_abs (t4, tc1);
			call_dd_mul (target_epsilon, sum, tc3);
			call_dd_abs (tc3, tc2);
			call_dd_cpr (tc1, tc2, ic1);
			if (ic1 <= 0) goto JMP_110;
		}

	// write (ddldb, 5);
	// 5 format ('*** DDBESSELIR: Loop end error 2');
	// call_dd_abrt
	printf("Line: %d *** DDBESSELIR: Loop end error 2\n", __LINE__);
	return std::numeric_limits<FloatNxN>::quiet_NaN();

	/* continue */ JMP_110:

	//t1 = exp (xa) / sqrt (static_cast<FloatBase>(2.0) * mppi (mpnw) * xa);
	//besseli = t1 * sum1

		call_dd_exp (rra, t1);
		call_dd_muld (LDF::const_pi<FloatNxN>(), static_cast<FloatBase>(2.0), t2);
		call_dd_mul (t2, rra, t3);
		call_dd_sqrt (t3, t4);
		call_dd_div (t1, t4, t2);
		call_dd_mul (t2, sum, t3);
	}

	/* continue */ JMP_120:

	call_dd_eq (t3, ss);

	return ss;
}

template<
	typename FloatNxN, typename FloatBase,
	int max_iter
>
static inline FloatNxN libDDFUN_besseljnr(const int nu, const FloatNxN& rr) {

	//  This evaluates the modified Bessel function BesselJ (NU,RR).
	//  NU is an integer. The algorithm is DLMF formula 10.2.2 for modest RR,
	//  and DLMF 10.17.3 for large RR, relative to precision.

	// implicit none
	// integer, intent(in):: nu
	// FloatNxN, intent(in):: rr;
	// FloatNxN, intent(out):: ss;
	// integer, parameter:: max_iter = 1000000
	FloatNxN ss;
	constexpr FloatBase dfrac = static_cast<FloatBase>(1.5);
	constexpr FloatBase pi = static_cast<FloatBase>(3.1415926535897932385);
	int ic1, ic2, k, nua, n1;
	FloatBase d1, d2;
	FloatNxN f1, f2, sum1, sum2, td1, td2, tn1, tn2, t1, t2, t3, t41, t42, t5, rra, rr2, tc1, tc2, tc3, target_epsilon;

	constexpr int dd_nwx = LDF::LDF_Type_Info<FloatNxN>::FloatBase_Count;
	constexpr int dd_nbt = std::numeric_limits<FloatBase>::digits;
	constexpr FloatBase dd_dpw = static_cast<FloatBase>(std::numeric_limits<FloatBase>::digits) * static_cast<FloatBase>(0.30102999566398119521373889472449);

	// End of declaration
	int dd_nw, dd_nw1, dd_nw2;



	dd_nw = dd_nwx;

	//  Check for RR = 0.

	if (call_dd_sgn (rr) == 0) {
		// write (ddldb, 2);
		// 2 format ('*** DDBESSELJNR: Second argument is zero');
		// call_dd_abrt
		printf("Line: %d *** DDBESSELJNR: Second argument is zero\n", __LINE__);
		return std::numeric_limits<FloatNxN>::quiet_NaN();
	}

	dd_nw1 = std::min(2 * dd_nw + 1, dd_nwx);
	nua = abs (nu);
	call_dd_dmc (static_cast<FloatBase>(2.0), 0, tc1);
	call_dd_npwr (tc1, -dd_nw * dd_nbt, target_epsilon);
	call_dd_mdc (rr, d1, n1);
	d1 = fabs(ldexp(d1, n1));

	if (d1 < dfrac * dd_nw1 * dd_dpw) {
		dd_nw1 = std::min(dd_nw + fortran_nint (d1 / (dfrac * dd_dpw)), 2 * dd_nw + 1, dd_nwx);
		call_dd_abs (rr, rra);
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, tn1);
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, f1);
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, f2);
		call_dd_mul (rra, rra, t2);
		call_dd_muld (t2, static_cast<FloatBase>(0.25), t1);

		for (k = 1; k <= nua; k++) {
			call_dd_muld (f2, fortran_dble (k), t2);
			call_dd_eq (t2, f2);
		}

		call_dd_mul (f1, f2, td1);
		call_dd_div (tn1, td1, t2);
		call_dd_eq (t2, sum1);

		for (k = 1; k <= max_iter; k++) {
			call_dd_muld (f1, fortran_dble (k), t2);
			call_dd_eq (t2, f1);
			call_dd_muld (f2, fortran_dble (k + nua), t2);
			call_dd_eq (t2, f2);
			call_dd_mul (t1, tn1, t2);
			call_dd_neg (t2, tn1);
			call_dd_mul (f1, f2, td1);
			call_dd_div (tn1, td1, t2);
			call_dd_add (sum1, t2, t3);
			call_dd_eq (t3, sum1);

			call_dd_abs (t2, tc1);
			call_dd_mul (target_epsilon, sum1, tc3);
			call_dd_abs (tc3, tc2);
			call_dd_cpr (tc1, tc2, ic1);
			if (ic1 <= 0) goto JMP_100;
		}

		// write (ddldb, 4);
		// 4 format ('*** DDBESSELJNR: Loop end error 1');
		// call_dd_abrt
		printf("Line: %d *** DDBESSELJNR: Loop end error 1\n", __LINE__);
		return std::numeric_limits<FloatNxN>::quiet_NaN();

	/* continue */ JMP_100:

		call_dd_muld (rra, static_cast<FloatBase>(0.5), t1);
		call_dd_npwr (t1, nua, t2);
		call_dd_mul (sum1, t2, t3);
	} else {
	//xa2 = xa ** 2
	//t1 = mpreal (static_cast<FloatBase>(4.0) * fortran_dble (nua)**2, mpnw);
	//tn1 = mpreal (static_cast<FloatBase>(1.0), mpnw);
	//tn2 = (t1 - static_cast<FloatBase>(1.0)) / static_cast<FloatBase>(8.0);
	//td1 = mpreal (static_cast<FloatBase>(1.0), mpnw);
	//td2 = xa
	//sum1 = tn1 / td1
	//sum2 = tn2 / t32

		dd_nw1 = std::min(dd_nw + 1, dd_nwx);
		call_dd_abs (rr, rra);
		call_dd_mul (rra, rra, rr2);
		d1 = static_cast<FloatBase>(4.0) * square(fortran_dble (nua));
		call_dd_dmc (d1, 0, t1);
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, tn1);
		call_dd_sub (t1, tn1, t2);
		call_dd_divd (t2, static_cast<FloatBase>(8.0), tn2);
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, td1);
		call_dd_eq (rra, td2);
		call_dd_div (tn1, td1, sum1);
		call_dd_div (tn2, td2, sum2);

		for (k = 1; k <= max_iter; k++) {
	//  tn1 = -tn1 * (t1 - (static_cast<FloatBase>(2.0) * (static_cast<FloatBase>(2.0) * k - static_cast<FloatBase>(1.0)) - static_cast<FloatBase>(1.0))**2) * (t1 - (static_cast<FloatBase>(2.0) * (static_cast<FloatBase>(2.0) * k) - static_cast<FloatBase>(1.0))**2);

			d1 = square(static_cast<FloatBase>(2.0) * (static_cast<FloatBase>(2.0) * k - static_cast<FloatBase>(1.0)) - static_cast<FloatBase>(1.0));
			d2 = square(static_cast<FloatBase>(2.0) * (static_cast<FloatBase>(2.0) * k) - static_cast<FloatBase>(1.0));
			call_dd_dmc (d1, 0, t2);
			call_dd_sub (t1, t2, t3);
			call_dd_dmc (d2, 0, t2);
			call_dd_sub (t1, t2, t5);
			call_dd_mul (t3, t5, t2);
			call_dd_mul (tn1, t2, t3);
			call_dd_neg (t3, tn1);

	//  td1 = td1 * fortran_dble (2 * k - 1) * fortran_dble (2 * k) * static_cast<FloatBase>(64.0) * xa2

			d1 = fortran_dble (2 * k - 1) * fortran_dble (2 * k) * static_cast<FloatBase>(64.0);
			call_dd_muld (td1, d1, t2);
			call_dd_mul (t2, rr2, td1);

	//  t41 = tn1 / td1
	//  sum1 = sum1 + t41

			call_dd_div (tn1, td1, t41);
			call_dd_add (sum1, t41, t2);
			call_dd_eq (t2, sum1);

	//  tn2 = -tn2 * (t1 - (static_cast<FloatBase>(2.0) * (static_cast<FloatBase>(2.0) * k) - static_cast<FloatBase>(1.0))**2) * (t1 - (static_cast<FloatBase>(2.0) * (static_cast<FloatBase>(2.0) * k + static_cast<FloatBase>(1.0)) - static_cast<FloatBase>(1.0))**2);

			d1 = square(static_cast<FloatBase>(2.0) * (static_cast<FloatBase>(2.0) * k) - static_cast<FloatBase>(1.0));
			d2 = square(static_cast<FloatBase>(2.0) * (static_cast<FloatBase>(2.0) * k + static_cast<FloatBase>(1.0)) - static_cast<FloatBase>(1.0));
			call_dd_dmc (d1, 0, t2);
			call_dd_sub (t1, t2, t3);
			call_dd_dmc (d2, 0, t2);
			call_dd_sub (t1, t2, t5);
			call_dd_mul (t3, t5, t2);
			call_dd_mul (tn2, t2, t3);
			call_dd_neg (t3, tn2);

	//  td2 = td2 * fortran_dble (2 * k) * fortran_dble (2 * k + 1) * static_cast<FloatBase>(64.0) * xa2

			d1 = fortran_dble (2 * k) * fortran_dble (2 * k + 1) * static_cast<FloatBase>(64.0);
			call_dd_muld (td2, d1, t2);
			call_dd_mul (t2, rr2, td2);

	// t42 = tn2 / td2
	// sum2 = sum2 + t42

			call_dd_div (tn2, td2, t42);
			call_dd_add (sum2, t42, t2);
			call_dd_eq (t2, sum2);

	// if (abs (t41) / abs (sum1) < target_epsilon && abs (t42) / abs (sum2) < target_epsilon ) goto JMP_110;

			call_dd_abs (t41, tc1);
			call_dd_mul (target_epsilon, sum1, tc3);
			call_dd_abs (tc3, tc2);
			call_dd_cpr (tc1, tc2, ic1);
			call_dd_abs (t42, tc1);
			call_dd_mul (target_epsilon, sum2, tc3);
			call_dd_abs (tc3, tc2);
			call_dd_cpr (tc1, tc2, ic2);
			if (ic1 <= 0 && ic2 <= 0) goto JMP_110;
		}

		// write (ddldb, 5);
		// 5 format ('*** DDBESSELJNR: Loop end error 2');
		// call_dd_abrt
		printf("Line: %d *** DDBESSELJNR: Loop end error 2\n", __LINE__);
		return std::numeric_limits<FloatNxN>::quiet_NaN();
		

	/* continue */ JMP_110:

	//t1 = xa - static_cast<FloatBase>(0.5) * nua * pi - static_cast<FloatBase>(0.25) * pi
	//besselj = sqrt (static_cast<FloatBase>(2.0) / (pi * xa)) * (cos (t1) * sum1 - sin (t1) * sum2);

		call_dd_muld (LDF::const_pi<FloatNxN>(), static_cast<FloatBase>(0.5) * nua, t1);
		call_dd_sub (rra, t1, t2);
		call_dd_muld (LDF::const_pi<FloatNxN>(), static_cast<FloatBase>(0.25), t1);
		call_dd_sub (t2, t1, t3);
		call_dd_cssnr (t3, t41, t42);
		call_dd_mul (t41, sum1, t1);
		call_dd_mul (t42, sum2, t2);
		call_dd_sub (t1, t2, t5);
		call_dd_mul (LDF::const_pi<FloatNxN>(), rra, t1);
		call_dd_dmc (static_cast<FloatBase>(2.0), 0, t2);
		call_dd_div (t2, t1, t3);
		call_dd_sqrt (t3, t1);
		call_dd_mul (t1, t5, t3);
	}

	if (fortran_mod (nu, 2) != 0) {
	// if (nu < 0 && x > static_cast<FloatBase>(0.0) || nu > 0 && x < static_cast<FloatBase>(0.0)) besselj = - besselj

		ic1 = call_dd_sgn (rr);
		if (nu < 0 && ic1 > 0 || nu > 0 && ic1 < 0) {
			call_dd_neg (t3, t2);
			call_dd_eq (t2, t3);
		}
	}

	call_dd_eq (t3, ss);

	return ss;
}

template<
	typename FloatNxN, typename FloatBase,
	int max_iter
>
static inline FloatNxN libDDFUN_besseljr(const FloatNxN& qq, const FloatNxN& rr) {

	//  This evaluates the modified Bessel function BesselJ (QQ,RR) for QQ and RR
	//  both MPR. The algorithm is DLMF formula 10.2.2 for modest RR,
	//  and DLMF 10.17.3 for large RR, relative to precision.

	// implicit none
	// FloatNxN, intent(in):: qq, rr;
	// FloatNxN, intent(out):: ss;
	FloatNxN ss;
	int ic1, ic2, i1, i2, k, n1;
	FloatBase d1, d2;
	// integer, parameter:: max_iter = 1000000
	constexpr FloatBase dfrac = static_cast<FloatBase>(1.5);
	constexpr FloatBase pi = static_cast<FloatBase>(3.1415926535897932385);
	FloatNxN f1, f2, sum1, sum2, td1, td2, tn1, tn2, t1, t2, t3, t4, t41, t42, t5, rra, rr2, tc1, tc2, tc3, target_epsilon;

	constexpr int dd_nwx = LDF::LDF_Type_Info<FloatNxN>::FloatBase_Count;
	constexpr int dd_nbt = std::numeric_limits<FloatBase>::digits;
	constexpr FloatBase dd_dpw = static_cast<FloatBase>(std::numeric_limits<FloatBase>::digits) * static_cast<FloatBase>(0.30102999566398119521373889472449);

	// End of declaration
	int dd_nw, dd_nw1, dd_nw2;



	dd_nw = dd_nwx;

	dd_nw1 = std::min(2 * dd_nw + 1, dd_nwx);
	call_dd_dmc (static_cast<FloatBase>(2.0), 0, tc1);
	call_dd_npwr (tc1, -dd_nw * dd_nbt, target_epsilon);

	//  If QQ is integer, call_mpbesseljnr; if RR <= 0, then error.

	call_dd_infr (qq, t1, t2);
	i1 = call_dd_sgn (qq);
	i2 = call_dd_sgn (rr);
	if (call_dd_sgn (t2) == 0) {
		call_dd_mdc (qq, d1, n1);
		d1 = ldexp(d1, n1);
		n1 = fortran_nint (d1);
		call_dd_besseljnr (n1, rr, t3);
		goto JMP_120;
	} else if (i2 <= 0) {
		// write (ddldb, 3);
		// 3 format ('*** DDBESSELJR: Second argument <= 0');
		// call_dd_abrt
		printf("Line: %d *** DDBESSELJR: Second argument <= 0\n", __LINE__);
		return std::numeric_limits<FloatNxN>::quiet_NaN();
	}

	call_dd_mdc (rr, d1, n1);
	d1 = fabs(ldexp(d1, n1));

	if (d1 < dfrac * dd_nw1 * dd_dpw) {
		dd_nw1 = std::min(dd_nw + fortran_nint (d1 / (dfrac * dd_dpw)), 2 * dd_nw + 1, dd_nwx);
		call_dd_abs (rr, rra);
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, tn1);
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, f1);
		call_dd_add (qq, f1, t1);
		call_dd_gammar (t1, f2);
		call_dd_mul (rra, rra, t2);
		call_dd_muld (t2, static_cast<FloatBase>(0.25), t1);

		call_dd_mul (f1, f2, td1);
		call_dd_div (tn1, td1, t2);
		call_dd_eq (t2, sum1);

		for (k = 1; k <= max_iter; k++) {
			call_dd_muld (f1, fortran_dble (k), t2);
			call_dd_eq (t2, f1);
			call_dd_dmc (fortran_dble (k), 0, t3);
			call_dd_add (qq, t3, t4);
			call_dd_mul (f2, t4, t3);
			call_dd_eq (t3, f2);
			call_dd_mul (t1, tn1, t2);
			call_dd_neg (t2, tn1);
			call_dd_mul (f1, f2, td1);
			call_dd_div (tn1, td1, t2);
			call_dd_add (sum1, t2, t3);
			call_dd_eq (t3, sum1);

			call_dd_abs (t2, tc1);
			call_dd_mul (target_epsilon, sum1, tc3);
			call_dd_abs (tc3, tc2);
			call_dd_cpr (tc1, tc2, ic1);
			if (ic1 <= 0) goto JMP_100;
		}

		// write (ddldb, 4);
		// 4 format ('*** DDBESSELJR: Loop end error 1');
		// call_dd_abrt
		printf("Line: %d *** DDBESSELJR: Loop end error 1\n", __LINE__);
		return std::numeric_limits<FloatNxN>::quiet_NaN();

	/* continue */ JMP_100:

		call_dd_muld (rr, static_cast<FloatBase>(0.5), t1);
		call_dd_power (t1, qq, t2);
		call_dd_mul (sum1, t2, t3);
	} else {
	//xa2 = xa ** 2
	//t1 = mpreal (static_cast<FloatBase>(4.0) * fortran_dble (nua)**2, mpnw);
	//tn1 = mpreal (static_cast<FloatBase>(1.0), mpnw);
	//tn2 = (t1 - static_cast<FloatBase>(1.0)) / static_cast<FloatBase>(8.0);
	//td1 = mpreal (static_cast<FloatBase>(1.0), mpnw);
	//td2 = xa
	//sum1 = tn1 / td1
	//sum2 = tn2 / t32

		dd_nw1 = std::min(dd_nw + 1, dd_nwx);
		call_dd_abs (rr, rra);
		call_dd_mul (rra, rra, rr2);
		call_dd_mul (qq, qq, t2);
		call_dd_muld (t2, static_cast<FloatBase>(4.0), t1);
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, tn1);
		call_dd_sub (t1, tn1, t2);
		call_dd_divd (t2, static_cast<FloatBase>(8.0), tn2);
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, td1);
		call_dd_eq (rra, td2);
		call_dd_div (tn1, td1, sum1);
		call_dd_div (tn2, td2, sum2);

		for (k = 1; k <= max_iter; k++) {
	//  tn1 = -tn1 * (t1 - (static_cast<FloatBase>(2.0) * (static_cast<FloatBase>(2.0) * k - static_cast<FloatBase>(1.0)) - static_cast<FloatBase>(1.0))**2) * (t1 - (static_cast<FloatBase>(2.0) * (static_cast<FloatBase>(2.0) * k) - static_cast<FloatBase>(1.0))**2);

			d1 = square(static_cast<FloatBase>(2.0) * (static_cast<FloatBase>(2.0) * k - static_cast<FloatBase>(1.0)) - static_cast<FloatBase>(1.0));
			d2 = square(static_cast<FloatBase>(2.0) * (static_cast<FloatBase>(2.0) * k) - static_cast<FloatBase>(1.0));
			call_dd_dmc (d1, 0, t2);
			call_dd_sub (t1, t2, t3);
			call_dd_dmc (d2, 0, t2);
			call_dd_sub (t1, t2, t5);
			call_dd_mul (t3, t5, t2);
			call_dd_mul (tn1, t2, t3);
			call_dd_neg (t3, tn1);

	//  td1 = td1 * fortran_dble (2 * k - 1) * fortran_dble (2 * k) * static_cast<FloatBase>(64.0) * xa2

			d1 = fortran_dble (2 * k - 1) * fortran_dble (2 * k) * static_cast<FloatBase>(64.0);
			call_dd_muld (td1, d1, t2);
			call_dd_mul (t2, rr2, td1);

	//  t41 = tn1 / td1
	//  sum1 = sum1 + t41

			call_dd_div (tn1, td1, t41);
			call_dd_add (sum1, t41, t2);
			call_dd_eq (t2, sum1);

	//  tn2 = -tn2 * (t1 - (static_cast<FloatBase>(2.0) * (static_cast<FloatBase>(2.0) * k) - static_cast<FloatBase>(1.0))**2) * (t1 - (static_cast<FloatBase>(2.0) * (static_cast<FloatBase>(2.0) * k + static_cast<FloatBase>(1.0)) - static_cast<FloatBase>(1.0))**2);

			d1 = square(static_cast<FloatBase>(2.0) * (static_cast<FloatBase>(2.0) * k) - static_cast<FloatBase>(1.0));
			d2 = square(static_cast<FloatBase>(2.0) * (static_cast<FloatBase>(2.0) * k + static_cast<FloatBase>(1.0)) - static_cast<FloatBase>(1.0));
			call_dd_dmc (d1, 0, t2);
			call_dd_sub (t1, t2, t3);
			call_dd_dmc (d2, 0, t2);
			call_dd_sub (t1, t2, t5);
			call_dd_mul (t3, t5, t2);
			call_dd_mul (tn2, t2, t3);
			call_dd_neg (t3, tn2);

	//  td2 = td2 * fortran_dble (2 * k) * fortran_dble (2 * k + 1) * static_cast<FloatBase>(64.0) * xa2

			d1 = fortran_dble (2 * k) * fortran_dble (2 * k + 1) * static_cast<FloatBase>(64.0);
			call_dd_muld (td2, d1, t2);
			call_dd_mul (t2, rr2, td2);

	// t42 = tn2 / td2
	// sum2 = sum2 + t42

			call_dd_div (tn2, td2, t42);
			call_dd_add (sum2, t42, t2);
			call_dd_eq (t2, sum2);

	// if (abs (t41) / abs (sum1) < target_epsilon && abs (t42) / abs (sum2) < target_epsilon ) goto JMP_110;

			call_dd_abs (t41, tc1);
			call_dd_mul (target_epsilon, sum1, tc3);
			call_dd_abs (tc3, tc2);
			call_dd_cpr (tc1, tc2, ic1);
			call_dd_abs (t42, tc1);
			call_dd_mul (target_epsilon, sum2, tc3);
			call_dd_abs (tc3, tc2);
			call_dd_cpr (tc1, tc2, ic2);
			if (ic1 <= 0 && ic2 <= 0) goto JMP_110;
		}

		// write (ddldb, 5);
		// 5 format ('*** DDBESSELJR: Loop end error 2');
		// call_dd_abrt
		printf("Line: %d *** DDBESSELJR: Loop end error 2\n", __LINE__);
		return std::numeric_limits<FloatNxN>::quiet_NaN();

	/* continue */ JMP_110:

	//t1 = xa - static_cast<FloatBase>(0.5) * nua * pi - static_cast<FloatBase>(0.25) * pi
	//besselj = sqrt (static_cast<FloatBase>(2.0) / (pi * xa)) * (cos (t1) * sum1 - sin (t1) * sum2);

	//  call_mpmuld (mppicon, static_cast<FloatBase>(0.5) * nua, t1, mpnw1);

		call_dd_mul (LDF::const_pi<FloatNxN>(), qq, t2);
		call_dd_muld (t2, static_cast<FloatBase>(0.5), t1);
		call_dd_sub (rra, t1, t2);
		call_dd_muld (LDF::const_pi<FloatNxN>(), static_cast<FloatBase>(0.25), t1);
		call_dd_sub (t2, t1, t3);
		call_dd_cssnr (t3, t41, t42);
		call_dd_mul (t41, sum1, t1);
		call_dd_mul (t42, sum2, t2);
		call_dd_sub (t1, t2, t5);
		call_dd_mul (LDF::const_pi<FloatNxN>(), rra, t1);
		call_dd_dmc (static_cast<FloatBase>(2.0), 0, t2);
		call_dd_div (t2, t1, t3);
		call_dd_sqrt (t3, t1);
		call_dd_mul (t1, t5, t3);
	}

	//if (fortran_mod (nu, 2) != 0) {
	// if (nu < 0 && x > static_cast<FloatBase>(0.0) || nu > 0 && x < static_cast<FloatBase>(0.0)) besselj = - besselj

	//  ic1 = mpsgn (rr);
	//  if (nu < 0 && ic1 > 0 || nu > 0 && ic1 < 0) {
	//    call_mpneg (t3, t2, mpnw1);
	//    call_mpeq (t2, t3, mpnw1);
	//  }
	//}

	/* continue */ JMP_120:

	call_dd_eq (t3, ss);

	return ss;
}

template<
	typename FloatNxN, typename FloatBase,
	int max_iter
>
static inline FloatNxN libDDFUN_besselknr(const int nu, const FloatNxN& rr) {

	//  This evaluates the modified Bessel function BesselK (NU,RR).
	//  NU is an integer. The algorithm is DLMF formula 10.31.1 for modest RR,
	//  and DLMF 10.40.2 for large RR, relative to precision.

	// implicit none
	// integer, intent(in):: nu
	// FloatNxN, intent(in):: rr;
	// FloatNxN, intent(out):: ss;
	// integer, parameter:: max_iter = 1000000
	FloatNxN ss;
	int ic1, k, nua, n1;
	FloatBase d1;
	constexpr FloatBase dfrac = static_cast<FloatBase>(1.5);
	constexpr FloatBase egam = static_cast<FloatBase>(0.5772156649015328606);
	constexpr FloatBase pi = static_cast<FloatBase>(3.1415926535897932385);
	FloatNxN f1, f2, f3, f4, f5, sum1, sum2, sum3, td, tn, t1, t2, t3, t4, rra, tc1, tc2, tc3, target_epsilon;

	constexpr int dd_nwx = LDF::LDF_Type_Info<FloatNxN>::FloatBase_Count;
	constexpr int dd_nbt = std::numeric_limits<FloatBase>::digits;
	constexpr FloatBase dd_dpw = static_cast<FloatBase>(std::numeric_limits<FloatBase>::digits) * static_cast<FloatBase>(0.30102999566398119521373889472449);

	// End of declaration
	int dd_nw, dd_nw1, dd_nw2;



	dd_nw = dd_nwx;

	//  Check for RR = 0.

	if (call_dd_sgn (rr) == 0) {
		// write (ddldb, 2);
		// 2 format ('*** DDBESSELKNR: Second argument is zero');
		// call_dd_abrt
		printf("Line: %d *** DDBESSELKNR: Second argument is zero\n", __LINE__);
		return std::numeric_limits<FloatNxN>::quiet_NaN();
	}

	dd_nw1 = std::min(dd_nw + 1, dd_nwx);
	nua = abs (nu);
	dd_nw1 = std::min(dd_nw + 1, dd_nwx);
	call_dd_dmc (static_cast<FloatBase>(2.0), 0, tc1);
	call_dd_npwr (tc1, -dd_nw1*dd_nbt, target_epsilon);
	call_dd_abs (rr, rra);
	call_dd_mdc (rra, d1, n1);
	d1 = ldexp(d1, n1);

	if (d1 < dfrac * dd_nw1 * dd_dpw) {
		call_dd_mul (rra, rra, t2);
		call_dd_muld (t2, static_cast<FloatBase>(0.25), t1);
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, f1);
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, f2);
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, f3);
		call_dd_dmc (static_cast<FloatBase>(0.0), 0,  sum1);

		for (k = 1; k <= nua - 1; k++) {
			call_dd_muld (f1, fortran_dble (k), t2);
			call_dd_eq (t2, f1);
		}

		for (k = 0; k <= nua - 1; k++) {
			if (k > 0) {
				call_dd_divd (f1, fortran_dble (nua - k), t2);
				call_dd_eq (t2, f1);
				call_dd_mul (t1, f2, t2);
				call_dd_neg (t2, f2);
				call_dd_muld (f3, fortran_dble (k), t2);
				call_dd_eq (t2, f3);
			}
			call_dd_mul (f1, f2, t3);
			call_dd_div (t3, f3, t2);
			call_dd_add (sum1, t2, t3);
			call_dd_eq (t3, sum1);
		}

		call_dd_muld (sum1, static_cast<FloatBase>(0.5), t2);
		call_dd_muld (rra, static_cast<FloatBase>(0.5), t3);
		call_dd_npwr (t3, nua, t4);
		call_dd_div (t2, t4, sum1);

		call_dd_muld (rra, static_cast<FloatBase>(0.5), t2);
		call_dd_log (t2, t3);
		d1 = pown((-static_cast<FloatBase>(1.0)), (nua + 1));
		call_dd_muld (t3, d1, t2);
		call_dd_besselinr (nua, rra, t3);
		call_dd_mul (t2, t3, sum2);

		call_dd_neg (LDF::const_egamma<FloatNxN>(), f1);
		call_dd_eq (f1, f2);
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, f3);
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, f4);
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, f5);

		for (k = 1; k <= nua; k++) {
			call_dd_dmc (static_cast<FloatBase>(1.0), 0, t2);
			call_dd_divd (t2, fortran_dble (k), t3);
			call_dd_add (f2, t3, t4);
			call_dd_eq (t4, f2);
			call_dd_muld (f5, fortran_dble (k), t2);
			call_dd_eq (t2, f5);
		}

		call_dd_add (f1, f2, t2);
		call_dd_mul (t2, f3, t3);
		call_dd_mul (f4, f5, t4);
		call_dd_div (t3, t4, sum3);

		for (k = 1; k <= max_iter; k++) {
			call_dd_dmc (static_cast<FloatBase>(1.0), 0, t2);
			call_dd_divd (t2, fortran_dble (k), t3);
			call_dd_add (f1, t3, t4);
			call_dd_eq (t4, f1);
			call_dd_divd (t2, fortran_dble (nua + k), t3);
			call_dd_add (f2, t3, t4);
			call_dd_eq (t4, f2);
			call_dd_mul (t1, f3, t2);
			call_dd_eq (t2, f3);
			call_dd_muld (f4, fortran_dble (k), t2);
			call_dd_eq (t2, f4);
			call_dd_muld (f5, fortran_dble (nua + k), t2);
			call_dd_eq (t2, f5);
			call_dd_add (f1, f2, t2);
			call_dd_mul (t2, f3, t3);
			call_dd_mul (f4, f5, t4);
			call_dd_div (t3, t4, t2);
			call_dd_add (sum3, t2, t3);
			call_dd_eq (t3, sum3);

			call_dd_abs (t2, tc1);
			call_dd_mul (target_epsilon, sum3, tc3);
			call_dd_abs (tc3, tc2);
			call_dd_cpr (tc1, tc2, ic1);
			if (ic1 <= 0) goto JMP_100;
		}

		// write (ddldb, 5);
		// 5 format ('*** DDBESSELKNR: Loop end error 1');
		// call_dd_abrt
		printf("Line: %d *** DDBESSELKNR: Loop end error 1\n", __LINE__);
		return std::numeric_limits<FloatNxN>::quiet_NaN();

	/* continue */ JMP_100:

		call_dd_muld (rra, static_cast<FloatBase>(0.5), t2);
		call_dd_npwr (t2, nua, t3);
		d1 = pown((-static_cast<FloatBase>(1.0)), nua) * static_cast<FloatBase>(0.5);
		call_dd_muld (t3, d1, t4);
		call_dd_mul (t4, sum3, t2);
		call_dd_eq (t2, sum3);
		call_dd_add (sum1, sum2, t2);
		call_dd_add (t2, sum3, t3);
	} else {
	// sum1 = mpreal (static_cast<FloatBase>(1.0), mpnw);
	// t1 = mpreal (static_cast<FloatBase>(4.0) * fortran_dble (nua)**2, mpnw);
	// t2 = mpreal (static_cast<FloatBase>(1.0), mpnw);
	// t3 = mpreal (static_cast<FloatBase>(1.0), mpnw);

		call_dd_dmc (static_cast<FloatBase>(1.0), 0, sum1);
		d1 = static_cast<FloatBase>(4.0) * square(fortran_dble (nua));
		call_dd_dmc (d1, 0, t1);
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, tn);
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, td);

		for (k = 1; k <= max_iter; k++) {
	// t2 = t2 * (t1 - (static_cast<FloatBase>(2.0) * k - static_cast<FloatBase>(1.0))**2);
	// t3 = t3 * fortran_dble (k) * static_cast<FloatBase>(8.0) * xa
	// t4 = t2 / t3
	// sum1 = sum1 + t4

			d1 = static_cast<FloatBase>(2.0) * k - static_cast<FloatBase>(1.0);
			call_dd_dmc (d1, 0, t2);
			call_dd_mul (t2, t2, t3);
			call_dd_sub (t1, t3, t2);
			call_dd_mul (tn, t2, t3);
			call_dd_eq (t3, tn);
			call_dd_muld (rra, static_cast<FloatBase>(8.0) * k, t2);
			call_dd_mul (td, t2, t3);
			call_dd_eq (t3, td);
			call_dd_div (tn, td, t4);
			call_dd_add (sum1, t4, t3);
			call_dd_eq (t3, sum1);

	//  if (abs (t4) / abs (sum1) < target_epsilon) goto JMP_110;

			call_dd_abs (t4, tc1);
			call_dd_mul (target_epsilon, sum1, tc3);
			call_dd_abs (tc3, tc2);
			call_dd_cpr (tc1, tc2, ic1);
			if (ic1 <= 0) goto JMP_110;
		}

		// write (ddldb, 6);
		// 6 format ('*** DDBESSELKNR: Loop end error 2');
		// call_dd_abrt
		printf("Line: %d *** DDBESSELKNR: Loop end error 2\n", __LINE__);
		return std::numeric_limits<FloatNxN>::quiet_NaN();

	/* continue */ JMP_110:

	//t1 = sqrt (mppi (mpnw) / (static_cast<FloatBase>(2.0) * xa)) / exp (xa);
	//besseli = t1 * sum1

		call_dd_exp (rra, t1);
		call_dd_muld (rra, static_cast<FloatBase>(2.0), t2);
		call_dd_div (LDF::const_pi<FloatNxN>(), t2, t3);
		call_dd_sqrt (t3, t4);
		call_dd_div (t4, t1, t2);
		call_dd_mul (t2, sum1, t3);
	}

	//if (x < static_cast<FloatBase>(0.0) && fortran_mod (nu, 2) != 0) besselk = - besselk

	if (call_dd_sgn (rr) < 0 && fortran_mod (nu, 2) != 0) {
		call_dd_neg (t3, t4);
		call_dd_eq (t4, t3);
	}
	call_dd_eq (t3, ss);
	return ss;
}

template<
	typename FloatNxN, typename FloatBase,
	int max_iter
>
static inline FloatNxN libDDFUN_besselkr(const FloatNxN& qq, const FloatNxN& rr) {

	//  This evaluates the Bessel function BesselK (QQ,RR) for QQ and RR
	//  both MPR. This uses DLMF formula 10.27.4.

	// implicit none
	// FloatNxN, intent(in):: qq, rr;
	// FloatNxN, intent(out):: ss;
	FloatNxN ss;
	int i1, i2, n1;
	FloatBase d1;
	FloatNxN t1, t2, t3, t4;

	constexpr int dd_nwx = LDF::LDF_Type_Info<FloatNxN>::FloatBase_Count;
	constexpr int dd_nbt = std::numeric_limits<FloatBase>::digits;
	constexpr FloatBase dd_dpw = static_cast<FloatBase>(std::numeric_limits<FloatBase>::digits) * static_cast<FloatBase>(0.30102999566398119521373889472449);

	// End of declaration
	int dd_nw, dd_nw1, dd_nw2;



	dd_nw = dd_nwx;

	dd_nw1 = std::min(dd_nw + 1, dd_nwx);

	//  If QQ is integer, call_mpbesselknr; if qq < 0 and rr <= 0, then error.

	call_dd_infr (qq, t1, t2);
	i1 = call_dd_sgn (qq);
	i2 = call_dd_sgn (rr);
	if (call_dd_sgn (t2) == 0) {
		call_dd_mdc (qq, d1, n1);
		d1 = ldexp(d1, n1);
		n1 = fortran_nint (d1);
		call_dd_besselknr (n1, rr, t1);
		goto JMP_120;
	} else if (i1 < 0 && i2 <= 0) {
		// write (ddldb, 2);
		// 2 format ('*** DDBESSELKR: First argument < 0 and second argument <= 0');
		// call_dd_abrt
		printf("Line: %d *** DDBESSELKR: First argument < 0 and second argument <= 0\n", __LINE__);
		return std::numeric_limits<FloatNxN>::quiet_NaN();
	}

	call_dd_neg (qq, t1);
	call_dd_besselir (t1, rr, t2);
	call_dd_besselir (qq, rr, t3);
	call_dd_sub (t2, t3, t4);
	call_dd_mul (qq, LDF::const_pi<FloatNxN>(), t1);
	call_dd_cssnr (t1, t2, t3);
	call_dd_div (t4, t3, t2);
	call_dd_mul (LDF::const_pi<FloatNxN>(), t2, t3);
	call_dd_muld (t3, static_cast<FloatBase>(0.5), t1);

	/* continue */ JMP_120:

	call_dd_eq (t1, ss);
	return ss;
}

template<
	typename FloatNxN, typename FloatBase,
	int max_iter
>
static inline FloatNxN libDDFUN_besselynr(const int nu, const FloatNxN& rr) {

	//  This evaluates the modified Bessel function BesselY (NU,RR).
	//  NU is an integer. The algorithm is DLMF formula 10.8.1 for modest RR,
	//  and DLMF 10.17.4 for large RR, relative to precision.

	// implicit none
	// integer, intent(in):: nu
	// FloatNxN, intent(in):: rr;
	// FloatNxN, intent(out):: ss;
	// integer, parameter:: max_iter = 1000000
	FloatNxN ss;
	constexpr FloatBase dfrac = static_cast<FloatBase>(1.5);
	constexpr FloatBase egam = static_cast<FloatBase>(0.5772156649015328606);
	constexpr FloatBase pi = static_cast<FloatBase>(3.1415926535897932385);
	int ic1, ic2, k, nua, n1;
	FloatBase d1, d2;
	FloatNxN f1, f2, f3, f4, f5, rra, rr2, sum1, sum2, sum3, td1, td2, tn1, tn2, t1, t2, t3, t4, t41, t42, t5, tc1, tc2, tc3, target_epsilon;

	constexpr int dd_nwx = LDF::LDF_Type_Info<FloatNxN>::FloatBase_Count;
	constexpr int dd_nbt = std::numeric_limits<FloatBase>::digits;
	constexpr FloatBase dd_dpw = static_cast<FloatBase>(std::numeric_limits<FloatBase>::digits) * static_cast<FloatBase>(0.30102999566398119521373889472449);

	// End of declaration
	int dd_nw, dd_nw1, dd_nw2;



	dd_nw = dd_nwx;

	//  Check for RR = 0.

	if (call_dd_sgn (rr) == 0) {
		// write (ddldb, 2);
		// 2 format ('*** DDBESSELYNR: argument is negative or too large');
		// call_dd_abrt
		printf("Line: %d *** DDBESSELYNR: argument is negative or too large\n", __LINE__);
		return std::numeric_limits<FloatNxN>::quiet_NaN();
	}

	dd_nw1 = std::min(2 * dd_nw + 1, dd_nwx);
	nua = abs (nu);
	call_dd_dmc (static_cast<FloatBase>(2.0), 0, tc1);
	call_dd_npwr (tc1, -dd_nw * dd_nbt, target_epsilon);
	call_dd_mdc (rr, d1, n1);
	d1 = fabs(ldexp(d1, n1));

	if (d1 < dfrac * dd_nw1 * dd_dpw) {
		dd_nw1 = std::min(dd_nw + fortran_nint (d1 / (dfrac * dd_dpw)), 2 * dd_nw + 1, dd_nwx);
		call_dd_abs (rr, rra);
		call_dd_mul (rra, rra, t2);
		call_dd_muld (t2, static_cast<FloatBase>(0.25), t1);
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, f1);
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, f2);
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, f3);
		call_dd_dmc (static_cast<FloatBase>(0.0), 0,  sum1);

		for (k = 1; k <= nua - 1; k++) {
			call_dd_muld (f1, fortran_dble (k), t2);
			call_dd_eq (t2, f1);
		}

		for (k = 0; k <= nua - 1; k++) {
			if (k > 0) {
				call_dd_divd (f1, fortran_dble (nua - k), t2);
				call_dd_eq (t2, f1);
				call_dd_mul (t1, f2, t2);
				call_dd_eq (t2, f2);
				call_dd_muld (f3, fortran_dble (k), t2);
				call_dd_eq (t2, f3);
			}
			call_dd_mul (f1, f2, t3);
			call_dd_div (t3, f3, t2);
			call_dd_add (sum1, t2, t3);
			call_dd_eq (t3, sum1);
		}

		call_dd_muld (rra, static_cast<FloatBase>(0.5), t3);
		call_dd_npwr (t3, nua, t4);
		call_dd_div (sum1, t4, t3);
		call_dd_neg (t3, sum1);

		call_dd_muld (rra, static_cast<FloatBase>(0.5), t2);
		call_dd_log (t2, t3);
		call_dd_muld (t3, static_cast<FloatBase>(2.0), t2);
		call_dd_besseljnr (nua, rra, t3);
		call_dd_mul (t2, t3, sum2);

		call_dd_neg (LDF::const_egamma<FloatNxN>(), f1);
		call_dd_eq (f1, f2);
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, f3);
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, f4);
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, f5);

		for (k = 1; k <= nua; k++) {
			call_dd_dmc (static_cast<FloatBase>(1.0), 0, t2);
			call_dd_divd (t2, fortran_dble (k), t3);
			call_dd_add (f2, t3, t4);
			call_dd_eq (t4, f2);
			call_dd_muld (f5, fortran_dble (k), t2);
			call_dd_eq (t2, f5);
		}

		call_dd_add (f1, f2, t2);
		call_dd_mul (t2, f3, t3);
		call_dd_mul (f4, f5, t4);
		call_dd_div (t3, t4, sum3);

		for (k = 1; k <= max_iter; k++) {
			call_dd_dmc (static_cast<FloatBase>(1.0), 0, t2);
			call_dd_divd (t2, fortran_dble (k), t3);
			call_dd_add (f1, t3, t4);
			call_dd_eq (t4, f1);
			call_dd_divd (t2, fortran_dble (nua + k), t3);
			call_dd_add (f2, t3, t4);
			call_dd_eq (t4, f2);
			call_dd_mul (t1, f3, t2);
			call_dd_neg (t2, f3);
			call_dd_muld (f4, fortran_dble (k), t2);
			call_dd_eq (t2, f4);
			call_dd_muld (f5, fortran_dble (nua + k), t2);
			call_dd_eq (t2, f5);
			call_dd_add (f1, f2, t2);
			call_dd_mul (t2, f3, t3);
			call_dd_mul (f4, f5, t4);
			call_dd_div (t3, t4, t2);
			call_dd_add (sum3, t2, t3);
			call_dd_eq (t3, sum3);

			call_dd_abs (t2, tc1);
			call_dd_mul (target_epsilon, sum3, tc3);
			call_dd_abs (tc3, tc2);
			call_dd_cpr (tc1, tc2, ic1);
			if (ic1 <= 0) goto JMP_100;
		}

		// write (ddldb, 6);
		// 6 format ('*** DDBESSELYNR: Loop end error 1');
		// call_dd_abrt
		
		printf("Line: %d *** DDBESSELYNR: Loop end error 1\n", __LINE__);
		return std::numeric_limits<FloatNxN>::quiet_NaN();

	/* continue */ JMP_100:

		call_dd_muld (rra, static_cast<FloatBase>(0.5), t2);
		call_dd_npwr (t2, nua, t3);
		call_dd_mul (t3, sum3, t2);
		call_dd_neg (t2, sum3);

		call_dd_add (sum1, sum2, t2);
		call_dd_add (t2, sum3, t4);
		call_dd_eq (LDF::const_pi<FloatNxN>(), t2);
		call_dd_div (t4, t2, t3);
	} else {

	//xa2 = xa**2
	//t1 = mpreal (static_cast<FloatBase>(4.0) * fortran_dble (nua) ** 2, mpnw);
	//tn1 = mpreal (static_cast<FloatBase>(1.0), mpnw);
	//tn2 = (t1 - static_cast<FloatBase>(1.0)) / static_cast<FloatBase>(8.0);
	//td1 = mpreal (static_cast<FloatBase>(1.0), mpnw);
	//td2 = xa
	//sum1 = tn1 / td1
	//sum2 = tn2 / t32

		dd_nw1 = std::min(dd_nw + 1, dd_nwx);
		call_dd_abs (rr, rra);
		call_dd_mul (rra, rra, rr2);
		d1 = static_cast<FloatBase>(4.0) * square(fortran_dble (nua));
		call_dd_dmc (d1, 0, t1);
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, tn1);
		call_dd_sub (t1, tn1, t2);
		call_dd_divd (t2, static_cast<FloatBase>(8.0), tn2);
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, td1);
		call_dd_eq (rra, td2);
		call_dd_div (tn1, td1, sum1);
		call_dd_div (tn2, td2, sum2);

		for (k = 1; k <= max_iter; k++) {
	//  tn1 = -tn1 * (t1 - (static_cast<FloatBase>(2.0) * (static_cast<FloatBase>(2.0) * k - static_cast<FloatBase>(1.0)) - static_cast<FloatBase>(1.0))**2) * (t1 - (static_cast<FloatBase>(2.0) * (static_cast<FloatBase>(2.0) * k) - static_cast<FloatBase>(1.0))**2);

			d1 = square(static_cast<FloatBase>(2.0) * (static_cast<FloatBase>(2.0) * k - static_cast<FloatBase>(1.0)) - static_cast<FloatBase>(1.0));
			d2 = square(static_cast<FloatBase>(2.0) * (static_cast<FloatBase>(2.0) * k) - static_cast<FloatBase>(1.0));
			call_dd_dmc (d1, 0, t2);
			call_dd_sub (t1, t2, t3);
			call_dd_dmc (d2, 0, t2);
			call_dd_sub (t1, t2, t5);
			call_dd_mul (t3, t5, t2);
			call_dd_mul (tn1, t2, t3);
			call_dd_neg (t3, tn1);

	//  td1 = td1 * fortran_dble (2 * k - 1) * fortran_dble (2 * k) * static_cast<FloatBase>(64.0) * xa2

			d1 = fortran_dble (2 * k - 1) * fortran_dble (2 * k) * static_cast<FloatBase>(64.0);
			call_dd_muld (td1, d1, t2);
			call_dd_mul (t2, rr2, td1);

	//  t41 = tn1 / td1
	//  sum1 = sum1 + t41

			call_dd_div (tn1, td1, t41);
			call_dd_add (sum1, t41, t2);
			call_dd_eq (t2, sum1);

	//  tn2 = -tn2 * (t1 - (static_cast<FloatBase>(2.0) * (static_cast<FloatBase>(2.0) * k) - static_cast<FloatBase>(1.0))**2) * (t1 - (static_cast<FloatBase>(2.0) * (static_cast<FloatBase>(2.0) * k + static_cast<FloatBase>(1.0)) - static_cast<FloatBase>(1.0))**2);

			d1 = square(static_cast<FloatBase>(2.0) * (static_cast<FloatBase>(2.0) * k) - static_cast<FloatBase>(1.0));
			d2 = square(static_cast<FloatBase>(2.0) * (static_cast<FloatBase>(2.0) * k + static_cast<FloatBase>(1.0)) - static_cast<FloatBase>(1.0));
			call_dd_dmc (d1, 0, t2);
			call_dd_sub (t1, t2, t3);
			call_dd_dmc (d2, 0, t2);
			call_dd_sub (t1, t2, t5);
			call_dd_mul (t3, t5, t2);
			call_dd_mul (tn2, t2, t3);
			call_dd_neg (t3, tn2);

	//  td2 = td2 * fortran_dble (2 * k) * fortran_dble (2 * k + 1) * static_cast<FloatBase>(64.0) * xa2

			d1 = fortran_dble (2 * k) * fortran_dble (2 * k + 1) * static_cast<FloatBase>(64.0);
			call_dd_muld (td2, d1, t2);
			call_dd_mul (t2, rr2, td2);

	// t42 = tn2 / td2
	// sum2 = sum2 + t42

			call_dd_div (tn2, td2, t42);
			call_dd_add (sum2, t42, t2);
			call_dd_eq (t2, sum2);

	// if (abs (t41) / abs (sum1) < target_epsilon && abs (t42) / abs (sum2) < target_epsilon ) goto JMP_110;

			call_dd_abs (t41, tc1);
			call_dd_mul (target_epsilon, sum1, tc3);
			call_dd_abs (tc3, tc2);
			call_dd_cpr (tc1, tc2, ic1);
			call_dd_abs (t42, tc1);
			call_dd_mul (target_epsilon, sum2, tc3);
			call_dd_abs (tc3, tc2);
			call_dd_cpr (tc1, tc2, ic2);
			if (ic1 <= 0 && ic2 <= 0) goto JMP_110;
		}

		// write (ddldb, 5);
		// 5 format ('*** DDBESSELYNR: Loop end error 2');
		// call_dd_abrt
		printf("Line: %d *** DDBESSELYNR: Loop end error 2\n", __LINE__);
		return std::numeric_limits<FloatNxN>::quiet_NaN();

	/* continue */ JMP_110:

	//t1 = xa - static_cast<FloatBase>(0.5) * nua * pi - static_cast<FloatBase>(0.25) * pi
	//besselj = sqrt (static_cast<FloatBase>(2.0) / (pi * xa)) * (cos (t1) * sum1 - sin (t1) * sum2);

		call_dd_muld (LDF::const_pi<FloatNxN>(), static_cast<FloatBase>(0.5) * nua, t1);
		call_dd_sub (rra, t1, t2);
		call_dd_muld (LDF::const_pi<FloatNxN>(), static_cast<FloatBase>(0.25), t1);
		call_dd_sub (t2, t1, t3);
		call_dd_cssnr (t3, t41, t42);
		call_dd_mul (t42, sum1, t1);
		call_dd_mul (t41, sum2, t2);
		call_dd_add (t1, t2, t5);
		call_dd_mul (LDF::const_pi<FloatNxN>(), rra, t1);
		call_dd_dmc (static_cast<FloatBase>(2.0), 0, t2);
		call_dd_div (t2, t1, t3);
		call_dd_sqrt (t3, t1);
		call_dd_mul (t1, t5, t3);
	}

	if (fortran_mod (nu, 2) != 0) {
	//  if (nu < 0 && x > static_cast<FloatBase>(0.0) || nu > 0 && x < static_cast<FloatBase>(0.0)) bessely = - bessely

		ic1 = call_dd_sgn (rr);
		if (nu < 0 && ic1 > 0 || nu > 0 && ic1 < 0) {
			call_dd_neg (t3, t4);
			call_dd_eq (t4, t3);
		}
	}

	call_dd_eq (t3, ss);
	return ss;
}

template<
	typename FloatNxN, typename FloatBase,
	int max_iter
>
static inline FloatNxN libDDFUN_besselyr(const FloatNxN& qq, const FloatNxN& rr) {

	//  This evaluates the modified Bessel function BesselY (QQ,RR).
	//  NU is an integer. The algorithm is DLMF formula 10.2.2.

	// implicit none
	// FloatNxN, intent(in):: qq, rr;
	// FloatNxN, intent(out):: ss;
	FloatNxN ss;
	int i1, i2, n1;
	FloatBase d1;
	FloatNxN t1, t2, t3, t4;

	constexpr int dd_nwx = LDF::LDF_Type_Info<FloatNxN>::FloatBase_Count;
	constexpr int dd_nbt = std::numeric_limits<FloatBase>::digits;
	constexpr FloatBase dd_dpw = static_cast<FloatBase>(std::numeric_limits<FloatBase>::digits) * static_cast<FloatBase>(0.30102999566398119521373889472449);

	// End of declaration
	int dd_nw, dd_nw1, dd_nw2;



	dd_nw = dd_nwx;

	dd_nw1 = std::min(dd_nw + 1, dd_nwx);

	//  If QQ is integer, call_mpbesselynr; if qq < 0 and rr <= 0, then error.

	call_dd_infr (qq, t1, t2);
	i1 = call_dd_sgn (qq);
	i2 = call_dd_sgn (rr);
	if (call_dd_sgn (t2) == 0) {
		call_dd_mdc (qq, d1, n1);
		d1 = ldexp(d1, n1);
		n1 = fortran_nint (d1);
		call_dd_besselynr (n1, rr, t1);
		goto JMP_120;
	} else if (i1 < 0 && i2 <= 0) {
		// write (ddldb, 2);
		// 2 format ('*** DDBESSELYR: First argument < 0 and second argument <= 0');
		// call_dd_abrt
		
		printf("Line: %d *** DDBESSELYR: First argument < 0 and second argument <= 0\n", __LINE__);
		return std::numeric_limits<FloatNxN>::quiet_NaN();
	}

	call_dd_mul (qq, LDF::const_pi<FloatNxN>(), t1);
	call_dd_cssnr (t1, t2, t3);
	call_dd_besseljr (qq, rr, t4);
	call_dd_mul (t4, t2, t1);
	call_dd_neg (qq, t2);
	call_dd_besseljr (t2, rr, t4);
	call_dd_sub (t1, t4, t2);
	call_dd_div (t2, t3, t1);

	/* continue */ JMP_120:

	call_dd_eq (t1, ss);
	return ss;
}


#endif /* FLOATNXN_CYL_BESSEL_HPP */
