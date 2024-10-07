/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

/*
**	Portions of this file were part of the libDDFUN and libDQFUN libraries
**
**	libDDFUN is licensed under a limited BSD license that can be found below:
**	https://www.davidhbailey.com/dhbsoftware/DHB-License.docx
**	Or alternatively from this website:
**	https://www.davidhbailey.com/dhbsoftware/
**	A copy of the Limited-BSD-License can also be found at:
**	LIB-Dekker-Float/libDDFUN/DISCLAIMER_and_Limited-BSD-License.txt
**
**	libDQFUN is licensed under a limited BSD license that can be found below:
**	https://www.davidhbailey.com/dhbsoftware/DHB-License.docx
**	Or alternatively from this website:
**	https://www.davidhbailey.com/dhbsoftware/
**	A copy of the Limited-BSD-License can also be found at:
**	LIB-Dekker-Float/libDQFUN/DISCLAIMER_and_Limited-BSD-License.txt
*/

/**
 * @brief This header file defines macros to make it easier to convert Fortran to C++
 */

#ifndef FLOATNXN_FORTRAN_DEF_H
#define FLOATNXN_FORTRAN_DEF_H

#include <cassert>

//------------------------------------------------------------------------------
// Fortran Macros
//------------------------------------------------------------------------------

#define fortran_dble(x) static_cast<FloatBase>(x)

#define fortran_mod(x, y) x % y

#define fortran_aint(x) trunc(x)
#define fortran_nint(x) round(x)

//------------------------------------------------------------------------------
// libDDFUN Macros
//------------------------------------------------------------------------------

/* Unary */

#define call_dd_eq(x, ret) ret = x
#define call_dd_neg(x, ret) ret = -x
#define call_dd_abs(x, ret) ret = fabs(x)
#define call_dd_exp(x, ret) ret = exp(x)
#define call_dd_log(x, ret) ret = log(x)
#define call_dd_sqrt(x, ret) ret = sqrt(x)

/* Arithmetic */

#define call_dd_add(x, y, ret) ret = x + y
#define call_dd_sub(x, y, ret) ret = x - y
#define call_dd_mul(x, y, ret) ret = x * y
#define call_dd_div(x, y, ret) ret = x / y

#define call_dd_addd(x, y, ret) ret = x + y
#define call_dd_subd(x, y, ret) ret = x - y
#define call_dd_muld(x, y, ret) ret = x * y
#define call_dd_divd(x, y, ret) ret = x / y

/* Math Functions */

#define call_dd_cssnr(theta, ret_cos, ret_sin) sincos(theta, ret_sin, ret_cos)
#define call_dd_npwr(x, n, ret) ret = pown(x, n)
#define call_dd_power(x, y, ret) ret = pow(x, y)
#define call_dd_gammar(x, ret) ret = tgamma(x)

#define call_dd_besselinr(x, y, ret) ret = cyl_bessel_i(static_cast<FloatNxN>(x), y)
#define call_dd_besseljnr(x, y, ret) ret = cyl_bessel_j(static_cast<FloatNxN>(x), y)
#define call_dd_besselknr(x, y, ret) ret = cyl_bessel_k(static_cast<FloatNxN>(x), y)
#define call_dd_besselynr(x, y, ret) ret = cyl_neumann(static_cast<FloatNxN>(x), y)

#define call_dd_besselir(x, y, ret) ret = cyl_bessel_i(x, y)
#define call_dd_besseljr(x, y, ret) ret = cyl_bessel_j(x, y)
#define call_dd_besselkr(x, y, ret) ret = cyl_bessel_k(x, y)
#define call_dd_besselyr(x, y, ret) ret = cyl_neumann(x, y)

//------------------------------------------------------------------------------
// libQDFUN Macros
//------------------------------------------------------------------------------

/* Unary */

#define call_dq_eq(x, ret) ret = x
#define call_dq_neg(x, ret) ret = -x
#define call_dq_abs(x, ret) ret = fabs(x)
#define call_dq_exp(x, ret) ret = exp(x)
#define call_dq_log(x, ret) ret = log(x)
#define call_dq_sqrt(x, ret) ret = sqrt(x)

/* Arithmetic */

#define call_dq_add(x, y, ret) ret = x + y
#define call_dq_sub(x, y, ret) ret = x - y
#define call_dq_mul(x, y, ret) ret = x * y
#define call_dq_div(x, y, ret) ret = x / y

#define call_dq_addd(x, y, ret) ret = x + y
#define call_dq_subd(x, y, ret) ret = x - y
#define call_dq_muld(x, y, ret) ret = x * y
#define call_dq_divd(x, y, ret) ret = x / y

/* Math Functions */

#define call_dq_cssnr(theta, ret_cos, ret_sin) sincos(theta, ret_sin, ret_cos)
#define call_dq_npwr(x, n, ret) ret = pown(x, n)
#define call_dq_power(x, y, ret) ret = pow(x, y)
#define call_dq_gammar(x, ret) ret = tgamma(x)

/* Bessel Functions */

#define call_dq_besselinr(x, y, ret) ret = cyl_bessel_i(static_cast<FloatNxN>(x), y)
#define call_dq_besseljnr(x, y, ret) ret = cyl_bessel_j(static_cast<FloatNxN>(x), y)
#define call_dq_besselknr(x, y, ret) ret = cyl_bessel_k(static_cast<FloatNxN>(x), y)
#define call_dq_besselynr(x, y, ret) ret = cyl_neumann(static_cast<FloatNxN>(x), y)

#define call_dq_besselir(x, y, ret) ret = cyl_bessel_i(x, y)
#define call_dq_besseljr(x, y, ret) ret = cyl_bessel_j(x, y)
#define call_dq_besselkr(x, y, ret) ret = cyl_bessel_k(x, y)
#define call_dq_besselyr(x, y, ret) ret = cyl_neumann(x, y)

//------------------------------------------------------------------------------
// Fortran Routines
//------------------------------------------------------------------------------

template<typename FloatBase>
static inline int call_dd_int_ldexp(const FloatBase x, const int expon) {
	FloatBase ret = ldexp(x, expon);
	// printf("int_ldexp: ret(%lf) = ldexp(%lf, %2d)\n", ret, x, expon);
	assert(ret == static_cast<FloatBase>((static_cast<int>(ret)))); // check that the conversion is exact.
	return static_cast<int>(ret);
}

/**
 * @remarks This function computes ldexp(x, n) storing the result
 * as a FloatNxN. Although most of the time n is zero, which leads me to
 * believe that this function is just for converting FloatBase to FloatNxN.
 */
template<typename FloatNxN, typename FloatBase>
static inline void T_call_dd_dmc(const FloatBase x, const int n, FloatNxN& ret) {
	ret = ldexp(x, n);
}

/** @brief This returns a DP approximation the DDR number A in the form B * 2^n */
template<typename FloatNxN, typename FloatBase>
static inline void T_call_dd_mdc(const FloatNxN& a, FloatBase& b, int& n) {
	#if 1
	b = static_cast<FloatBase>(a);
	n = 0;
	#else
	// This appears to be exactly what the Fortran90 subroutine does.
	b = a.hi;
	n = 0;
	#endif
}

// #define call_dq_sgn(x) x < 0.0 ? -1 : x > 0.0 ? 1 : 0
template<typename FloatNxN>
static inline int call_dd_sgn(const FloatNxN& x) {
	#if 1
		if (isequal_zero(x)) {
			return 0;
		}
		if (isgreater_zero(x)) {
			return 1;
		}
		return -1;
	#else
		if (x.hi == 0.0) {
			return 0;
		}
		if (x.hi > 0.0) {
			return 1;
		}
		return -1;
	#endif
}

/**
 * @brief Three way comparison <=> possibly?
 */
template<typename FloatNxN>
static inline void call_dd_cpr(const FloatNxN& x, const FloatNxN& y, int& ret) {
	#if 1
		if (x < y) {
			ret = -1;
			return;
		}
		if (x == y) {
			ret = 0;
			return;
		}
		ret = 1;
		return;
	#else
		// ret = (x < y) ? -1 : (x > y) ? 1 : 0;

		if (x.hi < y.hi) {
			ret = -1;
		} else if (x.hi == y.hi) {
			if (x.lo < y.lo) {
				ret = -1;
			} else if (x.lo == y.lo) {
				ret = 0;
			} else {
				ret = 1;
			}
		} else {
			ret = 1;
		}
	#endif
}

/** @brief similar to modf `c = modf(a, b)` */
template<typename FloatNxN, typename FloatBase>
static inline void T_call_dd_infr(const FloatNxN& a, FloatNxN& b, FloatNxN& c) {
#if 1
	c = modf(a, b);
	return;
#elif 0
	//   Sets B to the integer part of the DDR number A and sets C equal to the
	//   fractional part of A. Note that if A = -3.3, then B = -3 and C = -0.3.

	// implicit none
	// FloatNxN, intent(in):: a;
	// FloatNxN, intent(out):: b, c;

	/**
	 * @remarks I am guessing t105 was supposed to be
	 * FloatNxN_mantissa_bits - 1, representing the largest exact integer
	 */
	const FloatBase largest_ipwr2 = ldexp(
		static_cast<FloatBase>(1.0),
		std::numeric_limits<FloatNxN>::digits - 1
	);
	#if 0
		// Doesn't work?
		const FloatNxN largest_integer = LDF::sub<FloatNxN, FloatBase, FloatBase>(
			largest_ipwr2, static_cast<FloatBase>(1.0)
		);
	#else
		const FloatNxN largest_integer = largest_ipwr2;
	#endif

	int ic;
	FloatNxN f, s0, s1;
	
	// static FloatNxN con = FloatNxN(t105) + FloatNxN(t52);
	// save con
	// data con / t105, t52/

	//   Check if  A  is zero.

	if (isequal_zero(a))  {
		b = static_cast<FloatBase>(0.0);
		c = static_cast<FloatBase>(0.0);
		return;
	}

	if (static_cast<FloatBase>(a) >= largest_ipwr2) {
		// write (dd_ldb, 1);
		// 1 format ('*** DDINFR: Argument is too large.');
		// call_dq_abrt
		printf("%s\n", "*** DDINFR: Argument is too large.");
		return;
	}
	
	f = static_cast<FloatBase>(1.0);
	if (isgreater_zero(a)) {
		call_dq_add (a, largest_integer, s0);
		call_dq_sub (s0, largest_integer, b);
		call_dq_cpr (a, b, ic);
		if (ic >= 0) {
			call_dq_sub (a, b, c);
		} else {
			call_dq_sub (b, f, s1);
			b = s1;
			call_dq_sub (a, b, c);
		}
	} else {
		call_dq_sub (a, largest_integer, s0);
		call_dq_add (s0, largest_integer, b);
		call_dq_cpr (a, b, ic);
		if (ic <= 0) {
			call_dq_sub (a, b, c);
		} else {
			call_dq_add (b, f, s1);
			b = s1;
			call_dq_sub (a, b, c);
		}
	}
#elif 1
	//   Sets B to the integer part of the DDR number A and sets C equal to the
	//   fractional part of A. Note that if A = -3.3, then B = -3 and C = -0.3.

	// implicit none
	// FloatNxN, intent(in):: a;
	// FloatNxN, intent(out):: b, c;
	constexpr FloatBase t105 = ldexp(static_cast<FloatBase>(1.0), 105);
	constexpr FloatBase t52 = ldexp(static_cast<FloatBase>(1.0), 52);
	int ic;
	FloatNxN f, s0, s1;
	
	static FloatNxN con = FloatNxN(t105) + FloatNxN(t52);
	// save con
	// data con / t105, t52/

	//   Check if  A  is zero.

	if (isequal_zero(a))  {
		b = static_cast<FloatBase>(0.0);
		c = static_cast<FloatBase>(0.0);
		return;
	}

	if (static_cast<FloatBase>(a) >= t105) {
		// write (dd_ldb, 1);
		// 1 format ('*** DDINFR: Argument is too large.');
		// call_dq_abrt
		printf("%s\n", "*** DDINFR: Argument is too large.");
		return;
	}
	
	f = static_cast<FloatBase>(1.0);
	if (isgreater_zero(a)) {
		call_dq_add (a, con, s0);
		call_dq_sub (s0, con, b);
		call_dq_cpr (a, b, ic);
		if (ic >= 0) {
			call_dq_sub (a, b, c);
		} else {
			call_dq_sub (b, f, s1);
			b = s1;
			call_dq_sub (a, b, c);
		}
	} else {
		call_dq_sub (a, con, s0);
		call_dq_add (s0, con, b);
		call_dq_cpr (a, b, ic);
		if (ic <= 0) {
			call_dq_sub (a, b, c);
		} else {
			call_dq_add (b, f, s1);
			b = s1;
			call_dq_sub (a, b, c);
		}
	}
#else
	// Original code
	//   Sets B to the integer part of the DDR number A and sets C equal to the
	//   fractional part of A. Note that if A = -3.3, then B = -3 and C = -0.3.

	// implicit none
	// FloatNxN, intent(in):: a;
	// FloatNxN, intent(out):: b, c;
	constexpr FloatBase t105 = ldexp(static_cast<FloatBase>(1.0), 105);
	constexpr FloatBase t52 = ldexp(static_cast<FloatBase>(1.0), 52);
	int ic;
	FloatNxN f, s0, s1;
	
	static FloatNxN con = {t105, t52};
	// save con
	// data con / t105, t52/

	//   Check if  A  is zero.

	if (a.hi == static_cast<FloatBase>(0.0))  {
		b.hi = static_cast<FloatBase>(0.0);
		b.lo = static_cast<FloatBase>(0.0);
		c.hi = static_cast<FloatBase>(0.0);
		c.lo = static_cast<FloatBase>(0.0);
		return;
	}

	if (a.hi >= t105) {
		// write (dd_ldb, 1);
		// 1 format ('*** DDINFR: Argument is too large.');
		// call_dq_abrt
		printf("%s\n", "*** DDINFR: Argument is too large.");
		return;
	}

	f.hi = static_cast<FloatBase>(1.0);
	f.lo = static_cast<FloatBase>(0.0);
	if (a.hi > static_cast<FloatBase>(0.0)) {
		call_dq_add (a, con, s0);
		call_dq_sub (s0, con, b);
		call_dq_cpr (a, b, ic);
		if (ic >= 0) {
			call_dq_sub (a, b, c);
		} else {
			call_dq_sub (b, f, s1);
			b.hi = s1.hi;
			b.lo = s1.lo;
			call_dq_sub (a, b, c);
		}
	} else {
		call_dq_sub (a, con, s0);
		call_dq_add (s0, con, b);
		call_dq_cpr (a, b, ic);
		if (ic <= 0) {
			call_dq_sub (a, b, c);
		} else {
			call_dq_add (b, f, s1);
			b.hi = s1.hi;
			b.lo = s1.lo;
			call_dq_sub (a, b, c);
		}
	}
#endif
}


template<typename FloatNxN, typename FloatBase>
void T_call_dd_nint(const FloatNxN& a, FloatNxN& b) {
#if 1
	b = round(a);
	return;
#elif 0
	//   This sets B equal to the integer (type DDR) nearest to the DDR number A.

	// implicit none
	// FloatNxN, intent(in):: a(2)
	// FloatNxN, intent(out):: b(2)
	constexpr FloatBase t105 = ldexp(static_cast<FloatBase>(1.0), 105);
	constexpr FloatBase t52 = ldexp(static_cast<FloatBase>(1.0), 52);
	FloatNxN s0;

	static FloatNxN con;
	// save con
	// data con / t105, t52/

	//   Check if  A  is zero.

	if (isequal_zero(a)) {
		b = static_cast<FloatBase>(0.0);
		return;
	}

	if (static_cast<FloatBase>(a) >= t105) {
		// write (ddldb, 1)
		// 1 format ('*** DDNINT: Argument is too large.')
		// call ddabrt
		printf("%s\n", "*** DDNINT: Argument is too large.");
		return;
	}

	if (isgreater_zero(a)) {
		call_dq_add (a, con, s0);
		call_dq_sub (s0, con, b);
	} else {
		call_dq_sub (a, con, s0);
		call_dq_add (s0, con, b);
	}
#else
	//   This sets B equal to the integer (type DDR) nearest to the DDR number A.

	// implicit none
	// FloatNxN, intent(in):: a(2)
	// FloatNxN, intent(out):: b(2)
	constexpr FloatBase t105 = ldexp(static_cast<FloatBase>(1.0), 105);
	constexpr FloatBase t52 = ldexp(static_cast<FloatBase>(1.0), 52);
	FloatNxN s0;

	static FloatNxN con;
	// save con
	// data con / t105, t52/

	//   Check if  A  is zero.

	if (a.hi == static_cast<FloatBase>(0.0)) {
		b.hi = static_cast<FloatBase>(0.0);
		b.lo = static_cast<FloatBase>(0.0);
		return;
	}

	if (a.hi >= t105) {
		// write (ddldb, 1)
		// 1 format ('*** DDNINT: Argument is too large.')
		// call ddabrt
		printf("%s\n", "*** DDNINT: Argument is too large.");
		return;
	}

	if (a.hi > static_cast<FloatBase>(0.0)) {
		call_dq_add (a, con, s0);
		call_dq_sub (s0, con, b);
	} else {
		call_dq_sub (a, con, s0);
		call_dq_add (s0, con, b);
	}
#endif
}

//------------------------------------------------------------------------------
// libDDFUN Routines
//------------------------------------------------------------------------------

#define call_dd_dmc(x, n, ret) T_call_dd_dmc<FloatNxN, FloatBase>(x, n, ret)
#define call_dd_mdc(a, b, n) T_call_dd_mdc<FloatNxN, FloatBase>(a, b, n)
#define call_dd_infr(a, b_int, c_frac) T_call_dd_infr<FloatNxN, FloatBase>(a, b_int, c_frac)
#define call_dq_nint(a, b) T_call_dd_nint<FloatNxN, FloatBase>(a, b)

//------------------------------------------------------------------------------
// libQDFUN Routines
//------------------------------------------------------------------------------

#define call_dq_dmc(x, n, ret) T_call_dd_dmc<FloatNxN, FloatBase>(x, n, ret)
#define call_dq_mdc(a, b, n) T_call_dd_mdc<FloatNxN, FloatBase>(a, b, n)
#define call_dq_infr(a, b_int, c_frac) T_call_dd_infr<FloatNxN, FloatBase>(a, b_int, c_frac)
#define call_dq_nint(a, b) T_call_dd_nint<FloatNxN, FloatBase>(a, b)

#define call_dq_sgn(x) call_dd_sgn(x)
#define call_dq_cpr(x) call_dd_cpr(x)

#endif /* FLOATNXN_FORTRAN_DEF_H */