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

#ifndef FLOATNXN_RIEMANN_ZETA_HPP
#define FLOATNXN_RIEMANN_ZETA_HPP

#include "../LDF/LDF_type_info.hpp"
#include "../LDF/LDF_constants.hpp"
#include "../LDF/LDF_arithmetic.hpp"

#include <limits>
#include <cmath>
#include <cstdio>

#include "FloatNxN_fortran_def.h"

/**
 * @brief Computes the riemann_zeta function for integer arguments
 * @note this function is unimplemented
 */
template <
	typename FloatNxN, typename FloatBase,
	int max_iter
>
static inline FloatNxN libDDFUN_riemann_zeta_integer(const int iss) {
	switch (iss) {
		case -1: // -1 / 12
			return LDF::recip<FloatNxN, FloatBase>(static_cast<FloatBase>(-12.0));
		case 0: // -1 / 2
			return static_cast<FloatBase>(-0.5);
		case 1: // +inf
			return std::numeric_limits<FloatNxN>::infinity();
		case 2: // Basel Constant `pi^2 / 6`
			return square(LDF::const_pi<FloatNxN>()) / static_cast<FloatBase>(6.0);
		case 3: // Apery's Constant
			return LDF::const_apery<FloatNxN>();
	}

	//  This returns the zeta function of the integer argument ISS using an algorithm
	//  due to Peter Borwein.

	// integer, intent(in):: iss
	// real (ddknd), intent(out):: zz;
	// integer, parameter:: max_iter = 1000000
	FloatNxN zz;

	constexpr int dd_nwx = LDF::LDF_Type_Info<FloatNxN>::FloatBase_Count;
	constexpr int dd_nbt = std::numeric_limits<FloatBase>::digits;
	constexpr FloatBase dd_dpw = static_cast<FloatBase>(std::numeric_limits<FloatBase>::digits) * static_cast<FloatBase>(0.30102999566398119521373889472449);

	constexpr FloatBase dfrac = static_cast<FloatBase>(1.0) + dd_dpw;
	int i, ic1, j, n, itt;
	FloatBase d1, sgn_value;
	FloatNxN s, t1, t2, t3, t4, t5, tn, tc1, tc2, tc3, target_epsilon;

	// End of declaration
	int dd_nw, dd_nw1;



	dd_nw = dd_nwx;

	dd_nw1 = std::min(dd_nw + 1, dd_nwx);
	call_dd_dmc (static_cast<FloatBase>(2.0), 0, tc1);
	call_dd_npwr (tc1, -dd_nw1*dd_nbt, target_epsilon);

	// if (iss == 1) {
	// 	// write (ddldb, 2);
	// 	// 2 format ('*** DDZETAINTR: argument is 1');
	// 	// call_dd_abrt
	// 	// printf("Line: %d *** DDZETAINTR: argument is 1\n", __LINE__);
	// 	return std::numeric_limits<FloatNxN>::quiet_NaN();
	// }

	if (iss < 0) {

	//  If argument is a negative even integer, the result is zero.

		if (iss % 2 == 0) {
			return static_cast<FloatBase>(0.0);
		}

	//  Otherwise if arg < 0, compute zeta(1-is), and later apply Riemann's formula.

		itt = 1 - iss;
	} else {
		itt = iss;
	}

	// Check if argument is large enough that computing with definition is faster.

	d1 = dd_nbt * dd_nw * log (static_cast<FloatBase>(2.0)) / log (static_cast<FloatBase>(2.0) * dd_nbt * dd_nw / static_cast<FloatBase>(3.0));

	if (itt > d1) {

	//  Evaluate the infinite series.

		call_dd_dmc (static_cast<FloatBase>(1.0), 0, t1);

		for (i = 2; i <= max_iter; i++) {
			call_dd_dmc (fortran_dble(i), 0, t4);
			call_dd_npwr (t4, itt, t2);
			t3 = recip(t2);
			call_dd_add (t1, t3, t2);
			call_dd_eq (t2, t1);

			call_dd_abs (t3, tc1);
			call_dd_mul (target_epsilon, t1, tc3);
			call_dd_abs (tc3, tc2);
			call_dd_cpr (tc1, tc2, ic1);
			if (ic1 <= 0) {
				goto JMP_200;
			}
		}

		// write (ddldb, 3) 1, max_iter
		// 3 format ('*** DDZETAINTR: iteration limit exceeded',2i10);
		// call_dd_abrt
		printf("Line: %d *** DDZETAINTR: iteration limit exceeded %d\n", __LINE__, max_iter);
		return std::numeric_limits<FloatNxN>::quiet_NaN();
	}

	n = static_cast<int>(dfrac * static_cast<FloatBase>(dd_nw1));
	call_dd_dmc (static_cast<FloatBase>(2.0), 0, t1);
	call_dd_npwr (t1, n, tn);
	call_dd_neg (tn, t1);
	call_dd_dmc (static_cast<FloatBase>(0.0), 0, t2);
	call_dd_dmc (static_cast<FloatBase>(0.0), 0, s);

	sgn_value = static_cast<FloatBase>(1.0);

	for (j = 0; j <= 2 * n - 1; j++) {
		call_dd_dmc (fortran_dble(j + 1), 0, t4);
		call_dd_npwr (t4, itt, t3);
		call_dd_div (t1, t3, t4);
		call_dd_muld (t4, sgn_value, t5);
		call_dd_add (s, t5, t4);
		call_dd_eq (t4, s);
		sgn_value = -sgn_value;

		if (j < n - 1) {
			call_dd_dmc (static_cast<FloatBase>(0.0), 0, t2);
		} else if (j == n - 1) {
			call_dd_dmc (static_cast<FloatBase>(1.0), 0, t2);
		} else {
			call_dd_muld (t2, fortran_dble(2 * n - j), t3);
			call_dd_divd (t3, fortran_dble(j + 1 - n), t2);
		}

		call_dd_add (t1, t2, t3);
		call_dd_eq (t3, t1);
	}

	call_dd_dmc (static_cast<FloatBase>(2.0), 0, t2);
	call_dd_npwr (t2, 1 - itt, t4);
	t2 = static_cast<FloatBase>(1.0) - t4;
	call_dd_mul (tn, t2, t3);
	call_dd_div (s, t3, t1);
	call_dd_neg (t1, t2);
	call_dd_eq (t2, t1);

	//  If original argument was negative, apply Riemann's formula.

	if (iss < 0) {
		call_dd_dmc (static_cast<FloatBase>(1.0), 0, t3);
		for(i = 1; i <= itt - 1; i++) {
			call_dd_muld (t3, fortran_dble(i), t4);
			call_dd_eq (t4, t3);
		}

		call_dd_mul (t1, t3, t2);
		call_dd_muld (LDF::const_pi<FloatNxN>(), fortran_dble(itt), t1);
		call_dd_muld (t1, static_cast<FloatBase>(0.5), t3);
		call_dd_cssnr (t3, t4, t5);
		call_dd_mul (t2, t4, t1);
		call_dd_muld (LDF::const_pi<FloatNxN>(), static_cast<FloatBase>(2.0), t2);
		call_dd_npwr (t2, itt, t3);
		call_dd_div (t1, t3, t2);
		call_dd_muld (t2, static_cast<FloatBase>(2.0), t1);
	}

	/* continue */ JMP_200:

	call_dd_eq (t1, zz);
	return zz;
}

/**
 * @brief Computes the riemann_zeta function for real arguments
 * @note this function is unimplemented
 */
template <
	typename FloatNxN, typename FloatBase,
	int max_iter
>
static inline FloatNxN libDDFUN_riemann_zeta(const FloatNxN& ss) {
	//  This returns the zeta function of an MPR argument SS using an algorithm
	//  due to Peter Borwein.

	// real (ddknd), intent(in):: ss;
	// real (ddknd), intent(out):: zz;
	// integer, parameter:: max_iter = 1000000
	FloatNxN zz;

	constexpr int dd_nwx = LDF::LDF_Type_Info<FloatNxN>::FloatBase_Count;
	constexpr int dd_nbt = std::numeric_limits<FloatBase>::digits;
	constexpr FloatBase dd_dpw = static_cast<FloatBase>(std::numeric_limits<FloatBase>::digits) * static_cast<FloatBase>(0.30102999566398119521373889472449);

	constexpr FloatBase dfrac = static_cast<FloatBase>(1.0) + dd_dpw;
	int i, ic1, j, n, n2;
	FloatBase d1, d2;
	FloatNxN s, t1, t2, t3, t4, t5, tn, tt, tc1, tc2, tc3, target_epsilon;
	FloatBase sgn_value;

	// End of declaration
	int dd_nw, dd_nw1;



	dd_nw = dd_nwx;

	dd_nw1 = std::min(dd_nw + 1, dd_nwx);
	call_dd_dmc (static_cast<FloatBase>(2.0), 0, tc1);
	call_dd_npwr (tc1, -dd_nw1*dd_nbt, target_epsilon);

	call_dd_infr (ss, t1, t2);

	// call_dd_cpr (ss, f1, ic1);
	// if (ic1 == 0) {
	// 	// write (ddldb, 2);
	// 	// 2 format ('*** DDZETAR: argument is 1');
	// 	// call_dd_abrt
	// 	// printf("Line: %d *** DDZETAR: argument is 1\n", __LINE__);
	// 	return std::numeric_limits<FloatNxN>::quiet_NaN();
	// }
	if (call_dd_sgn (t2) == 0) {

	//  The argument is an integer value. Call mpzetaintr instead.

		// call_dd_mdc (ss, d1, n1);
		// iss = d1 * static_cast<FloatBase>(2.0)**n1
		// call_dd_zetaintr (iss, t1);
		return libDDFUN_riemann_zeta_integer<FloatNxN, FloatBase, max_iter>(static_cast<int>(ss));

	} else if (call_dd_sgn (ss) < 0) {

	//  If arg < 0, compute zeta(1-ss), and later apply Riemann's formula.

		tt = static_cast<FloatBase>(1.0) - ss;
	} else {
		tt = ss;
	}

	// Check if argument is large enough that computing with definition is faster.

	d1 = dd_nbt * dd_nw * log (static_cast<FloatBase>(2.0)) / log (static_cast<FloatBase>(2.0) * dd_nbt * dd_nw / static_cast<FloatBase>(3.0));
	call_dd_mdc (tt, d2, n2);
	d2 = ldexp(d2, n2);

	if (d2 > d1) {

	//  Evaluate the infinite series.

		call_dd_dmc (static_cast<FloatBase>(1.0), 0, t1);

		for (i = 2; i <= max_iter; i++) {
			call_dd_dmc (fortran_dble(i), 0, t4);
			call_dd_power (t4, tt, t2);
			t3 = recip(t2);
			call_dd_add (t1, t3, t2);
			call_dd_eq (t2, t1);

			call_dd_abs (t3, tc1);
			call_dd_mul (target_epsilon, t1, tc3);
			call_dd_abs (tc3, tc2);
			call_dd_cpr (tc1, tc2, ic1);
			if (ic1 <= 0) {
				goto JMP_200;
			}
		}

		// write (ddldb, 3) 1, max_iter
		// 3 format ('*** DDZETAR: iteration limit exceeded',2i10);
		// call_dd_abrt
		printf("Line: %d *** DDZETAR: iteration limit exceeded %d\n", __LINE__, max_iter);
		return std::numeric_limits<FloatNxN>::quiet_NaN();
	}

	n = static_cast<int>(dfrac * static_cast<FloatBase>(dd_nw1));
	call_dd_dmc (static_cast<FloatBase>(2.0), 0, t1);
	call_dd_npwr (t1, n, tn);
	call_dd_neg (tn, t1);
	call_dd_dmc (static_cast<FloatBase>(0.0), 0, t2);
	call_dd_dmc (static_cast<FloatBase>(0.0), 0, s);

	sgn_value = static_cast<FloatBase>(1.0);

	for (j = 0; j <= 2 * n - 1; j++) {
		call_dd_dmc (fortran_dble(j + 1), 0, t4);
		call_dd_power (t4, tt, t3);
		call_dd_div (t1, t3, t4);
		call_dd_muld (t4, sgn_value, t5);
		call_dd_add (s, t5, t4);
		call_dd_eq (t4, s);
		sgn_value = -sgn_value;

		if (j < n - 1) {
			call_dd_dmc (static_cast<FloatBase>(0.0), 0, t2);
		} else if (j == n - 1) {
			call_dd_dmc (static_cast<FloatBase>(1.0), 0, t2);
		} else {
			call_dd_muld (t2, fortran_dble(2 * n - j), t3);
			call_dd_divd (t3, fortran_dble(j + 1 - n), t2);
		}
		call_dd_add (t1, t2, t3);
		call_dd_eq (t3, t1);
	}

	t3 = static_cast<FloatBase>(1.0) - tt;
	call_dd_dmc (static_cast<FloatBase>(2.0), 0, t2);
	call_dd_power (t2, t3, t4);
	t2 = static_cast<FloatBase>(1.0) - t4;
	call_dd_mul (tn, t2, t3);
	call_dd_div (s, t3, t1);
	call_dd_neg (t1, t2);
	call_dd_eq (t2, t1);

	//  If original argument was negative, apply Riemann's formula.

	if (call_dd_sgn (ss) < 0) {
		call_dd_gammar (tt, t3);
		call_dd_mul (t1, t3, t2);
		call_dd_mul (LDF::const_pi<FloatNxN>(), tt, t1);
		call_dd_muld (t1, static_cast<FloatBase>(0.5), t3);
		call_dd_cssnr (t3, t4, t5);
		call_dd_mul (t2, t4, t1);
		call_dd_muld (LDF::const_pi<FloatNxN>(), static_cast<FloatBase>(2.0), t2);
		call_dd_power (t2, tt, t3);
		call_dd_div (t1, t3, t2);
		call_dd_muld (t2, static_cast<FloatBase>(2.0), t1);
	}

	/* continue */ JMP_200:

	call_dd_eq (t1, zz);
	return zz;
}

#endif /* FLOATNXN_RIEMANN_ZETA_HPP */
