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

#include <cmath>
#include <limits>
#include <cassert>

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
// #define call_dq_npwr(x, n, ret) ret = pown(x, n)
#define call_dq_npwr(x, n, ret) ret = pow(x, n)

template<typename FloatBase>
static inline int call_dq_int_ldexp(const FloatBase x, const int expon) {
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
static inline void T_call_dq_dmc(const FloatBase x, const int n, FloatNxN& ret) {
	ret = ldexp(x, n);
}
#define call_dq_dmc(x, n, ret) T_call_dq_dmc<FloatNxN, FloatBase>(x, n, ret)

/** @brief This returns a DP approximation the DDR number A in the form B * 2^n */
template<typename FloatNxN, typename FloatBase>
static inline void T_call_dq_mdc(const FloatNxN& a, FloatBase& b, int& n) {
	#if 1
	b = static_cast<FloatBase>(a);
	n = 0;
	#else
	// This appears to be exactly what the Fortran90 subroutine does.
	b = a.hi;
	n = 0;
	#endif
}
#define call_dq_mdc(a, b, n) T_call_dq_mdc<FloatNxN, FloatBase>(a, b, n)

// #define call_dq_sgn(x) x < 0.0 ? -1 : x > 0.0 ? 1 : 0
template<typename FloatNxN>
static inline int call_dq_sgn(const FloatNxN x) {
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
static inline void call_dq_cpr(const FloatNxN& x, const FloatNxN& y, int& ret) {
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
		goto JMP_120;
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

	/* continue */ JMP_120:
	return;
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
		goto JMP_120;
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

	/* continue */ JMP_120:
	return;
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
		goto JMP_120;
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

	/* continue */ JMP_120:
	return;
#endif
}

#define call_dq_infr(a, b, c) T_call_dd_infr<FloatNxN, FloatBase>(a, b, c)

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
		goto JMP_120;
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

	/* continue */ JMP_120:
	return;
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
		goto JMP_120;
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

	/* continue */ JMP_120:
	return;
#endif
}

#define call_dq_nint(a, b) T_call_dd_nint<FloatNxN, FloatBase>(a, b)

//------------------------------------------------------------------------------
// FloatNxN tgamma
//------------------------------------------------------------------------------

template <
	typename FloatNxN, typename FloatBase, int FloatBase_Count,
	int max_iter
>
static inline FloatNxN libDQFUN_tgamma(
	const FloatNxN& t,
	const FloatNxN dq_picon, const FloatBase al2
) {
	FloatNxN z;
	const int dq_nwx = FloatBase_Count;
	const int dq_nbt = std::numeric_limits<FloatBase>::digits;
	//	 This evaluates the gamma function, using an algorithm of R. W. Potter.
	//	 The argument t must not exceed 10^8 in size (this limit is set below),
	//	 must not be zero, and if negative must not be integer.

	//	 In the parameter statement below:
	//		 max_iter = limit of number of iterations in series; default = 100000.
	//		 con1 = 1/2 * log (10) to DP accuracy.
	//		 dmax = maximum size of input argument.

	// implicit none
	// FloatNxN, intent(in):: t;
	// FloatNxN, intent(out):: z;
	// constexpr int max_iter = 100000;

	// This constant appears to be very conservative
	__attribute__((unused)) constexpr FloatBase dmax = static_cast<FloatBase>(1.0e+8);
	
	int i, i1, ic1, j, nt, n1, n2, n3;
	FloatBase alpha, d1, d2, d3;
	FloatNxN f1, sum1, sum2, tn;
	FloatNxN t1, t2, t3, t4, t5, t6;
	FloatNxN tc1, tc2, tc3, target_epsilon;

	//	End of declaration
	int dq_nw, dq_nw1 /*, dq_nw2 */;



	dq_nw = dq_nwx;

	dq_nw1 = std::min(dq_nw + 1, dq_nwx);
	call_dq_dmc (static_cast<FloatBase>(2.0), 0, tc1);
	call_dq_npwr (tc1, -dq_nw1 * dq_nbt, target_epsilon);

	call_dq_mdc (t, d1, n1);
	d1 = ldexp(d1, n1);
	call_dq_nint (t, t1);
	call_dq_cpr (t, t1, ic1);
	i1 = call_dq_sgn (t);
	if (i1 == 0 || /* d1 > dmax || */ (i1 < 0 && ic1 == 0)) {
		// write (dq_ldb, 2) dmax
		// 2 format ('*** DQGAMMAR: input argument must have absolute value <=',f10.0,','/ &
		// 'must not be zero, and if negative must not be an integer.')
		// call_dq_abrt
		// printf(
		// 	"*** DQGAMMAR: input argument must have absolute value <= %lf, must not be zero, and if negative must not be an integer.\n",
		// 	dmax
		// );
		// return;
	}

	call_dq_dmc (static_cast<FloatBase>(1.0), 0, f1);

	//	 Find the integer and fractional parts of t.

	call_dq_infr (t, t2, t3);

	if (call_dq_sgn (t3) == 0) {

	//	 If t is a positive integer, { apply the usual factorial recursion.

		call_dq_mdc (t2, d2, n2);
		nt = call_dq_int_ldexp(d2, n2);
		call_dq_eq (f1, t1);

		for (i = 2; i <= nt - 1; i++) {
			call_dq_muld (t1, static_cast<FloatBase>(i), t2);
			call_dq_eq (t2, t1);
		}

		call_dq_eq (t1, z);
		goto JMP_120;
	} else if (call_dq_sgn (t) > 0) {

	//	 Apply the identity Gamma[t+1] = t * Gamma[t] to reduce the input argument
	//	 to the unit interval.

		call_dq_mdc (t2, d2, n2);
		nt = call_dq_int_ldexp(d2, n2);
		call_dq_eq (f1, t1);
		call_dq_eq (t3, tn);

		for (i = 1; i <= nt; i++) {
			call_dq_dmc (static_cast<FloatBase>(i), 0, t4);
			call_dq_sub (t, t4, t5);
			call_dq_mul (t1, t5, t6);
			call_dq_eq (t6, t1);
		}
	} else {

	//	 Apply the gamma identity to reduce a negative argument to the unit interval.

		call_dq_sub (f1, t, t4);
		call_dq_infr (t4, t3, t5);
		call_dq_mdc (t3, d3, n3);
		nt = call_dq_int_ldexp(d3, n3);

		call_dq_eq (f1, t1);
		call_dq_sub (f1, t5, t2);
		call_dq_eq (t2, tn);

		for (i = 0; i <= nt - 1; i++) {
			call_dq_dmc (static_cast<FloatBase>(i), 0, t4);
			call_dq_add (t, t4, t5);
			call_dq_div (t1, t5, t6);
			call_dq_eq (t6, t1);
		}
	}

	//	 Calculate alpha = bits of precision * log(2) / 2, { take the next even
	//	 integer value, so that alpha/2 and alpha^2/4 can be calculated exactly in DP.

	alpha = static_cast<FloatBase>(2.0) * trunc(
		static_cast<FloatBase>(0.25) * (dq_nw1 + 1) * dq_nbt * al2 + static_cast<FloatBase>(1.0)
	);
	d2 = static_cast<FloatBase>(0.25) * (alpha * alpha);
	call_dq_eq (tn, t2);
	call_dq_div (f1, t2, t3);
	call_dq_eq (t3, sum1);

	//	 Evaluate the series with t.

	for (j = 1; j <= max_iter; j++) {
		call_dq_dmc (static_cast<FloatBase>(j), 0, t6);
		call_dq_add (t2, t6, t4);
		call_dq_muld (t4, static_cast<FloatBase>(j), t5);
		call_dq_div (t3, t5, t6);
		call_dq_muld (t6, d2, t3);
		call_dq_add (sum1, t3, t4);
		call_dq_eq (t4, sum1);

		call_dq_abs (t3, tc1);
		call_dq_mul (target_epsilon, sum1, tc3);
		call_dq_abs (tc3, tc2);
		call_dq_cpr (tc1, tc2, ic1);
		if (ic1 <= 0) {
			goto JMP_100;
		}
	}

	// write (dq_ldb, 3) 1, max_iter
	// 3 format ('*** DQGAMMAR: iteration limit exceeded',2i10);
	// call_dq_abrt

	printf("*** DQGAMMAR: iteration limit exceeded %d", max_iter);
	return z;

	/* continue */ JMP_100:

	call_dq_neg (tn, t2);
	call_dq_div (f1, t2, t3);
	call_dq_eq (t3, sum2);

	//	 Evaluate the same series with -t.

	for (j = 1; j <= max_iter; j++) {
		call_dq_dmc (static_cast<FloatBase>(j), 0, t6);
		call_dq_add (t2, t6, t4);
		call_dq_muld (t4, static_cast<FloatBase>(j), t5);
		call_dq_div (t3, t5, t6);
		call_dq_muld (t6, d2, t3);
		call_dq_add (sum2, t3, t4);
		call_dq_eq (t4, sum2);

		call_dq_abs (t3, tc1);
		call_dq_mul (target_epsilon, sum2, tc3);
		call_dq_abs (tc3, tc2);
		call_dq_cpr (tc1, tc2, ic1);
		if (ic1 <= 0) {
			goto JMP_110;
		}
	}

	// write (dq_ldb, 3) 2, max_iter
	// call_dq_abrt

	/* continue */ JMP_110:

	//	 Compute sqrt (pi * sum1 / (tn * sin (pi * tn) * sum2))
	//	 and (alpha/2)^tn terms. Also, multiply by the factor t1, from the
	//	 If block above.

	call_dq_eq (dq_picon, t2);
	call_dq_mul (t2, tn, t3);
	call_dq_cssnr (t3, t4, t5);
	call_dq_mul (t5, sum2, t6);
	call_dq_mul (tn, t6, t5);
	call_dq_mul (t2, sum1, t3);
	call_dq_div (t3, t5, t6);
	call_dq_neg (t6, t4);
	call_dq_eq (t4, t6);
	call_dq_sqrt (t6, t2);
	call_dq_dmc (static_cast<FloatBase>(0.5) * alpha, 0, t3);
	call_dq_log (t3, t4);
	call_dq_mul (tn, t4, t5);
	call_dq_exp (t5, t6);
	call_dq_mul (t2, t6, t3);
	call_dq_mul (t1, t3, t4);

	//	 Round to mpnw words precision.

	call_dq_eq (t4, z);

	/* continue */ JMP_120:

	return z;
}

#endif /* FLOATNXN_TGAMMA_HPP */
