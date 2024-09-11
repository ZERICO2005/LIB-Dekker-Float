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

#include <limits>

/**
 * @remarks This function computes ldexp(x, n) storing the result
 * as a Float80x2. Although most of the time n is zero, which leads me to
 * believe that this function is just for converting FloatBase to FloatNxN.
 */
template<typename FloatNxN, typename FloatBase>
static inline void call_dd_dmc(const FloatBase x, const int n, FloatNxN& ret) {
	if (n == 0) {
		ret = x;
	} else {
		ret = static_cast<FloatNxN>(ldexp(x, n));
	}
}

/**
 * @brief Three way comparison <=> possibly?
 */
template<typename FloatNxN>
static inline void call_dd_cpr(const FloatNxN& x, const FloatNxN& y, int& ret) {
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
}

/**
 * @brief Three way comparison <=> possibly?
 */
template<typename FloatNxN, typename FloatBase>
static inline void call_dd_cpr(const FloatNxN& x, const FloatBase y_temp, int& ret) {
	// ret = (x < y) ? -1 : (x > y) ? 1 : 0;

	FloatNxN y = y_temp;
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
}

//------------------------------------------------------------------------------
// FloatNxN erf and erfc
//------------------------------------------------------------------------------

#define call_dd_dmc(x, n, ret) ret = x

/** 
 * @author Taken from libDDFUN ddfune.f90 which can be found under a
 * Limited-BSD license from https://www.davidhbailey.com/dhbsoftware/
 * @remarks It appears that the exact same implementation is used in
 * libQDFUN as well.
 */
template<
	typename FloatNxN, typename FloatBase, int FloatBase_count,
	int max_iter
>
static inline FloatNxN libDDFUN_erf(
	const FloatNxN& z,
	const FloatNxN FloatNxN_sqrtpi,
	const FloatBase FloatBase_ln2,
	const FloatBase target_epsilon
) {
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
	int ic1, ic2, ic3;
	// int n1; // unused?
	FloatBase d1, d2;
	FloatNxN t1, t2, t3, t4, t5, t6;
	FloatNxN tc1;
	// FloatNxN tc2, tc3; // unused?


	// int dd_nw, dd_nw1;
	// dd_nw = FloatNxN_count;
	// dd_nw1 = std::min(dd_nw + 1, FloatNxN_count);

	tc1 = static_cast<FloatBase>(2.0);

	d1 = trunc(static_cast<FloatBase>(1.0) + sqrt(
		static_cast<FloatBase>(std::numeric_limits<FloatNxN>::digits) * FloatBase_ln2
	));
	d2 = trunc((
		static_cast<FloatBase>(std::numeric_limits<FloatNxN>::digits) / dcon
	) + static_cast<FloatBase>(8.0));
	t1 = d1;
	t2 = d2;
	call_dd_cpr(z, t1, ic1);
	// t1(2) = - t1(2);
	t1 = -t1;
	call_dd_cpr(z, t1, ic2);
	call_dd_cpr(z, t2, ic3);

	if (isequal_zero(z)) { // sign(z) == 0
		// z == 0.0
		return static_cast<FloatBase>(0.0);
	}
	if ((isinf(z) && isgreater_zero(z)) || ic1 > 0) {
		// z == +inf
		return static_cast<FloatBase>(1.0);
	}
	if ((isinf(z) && isless_zero(z)) || ic2 < 0) {
		// z == -inf
		return static_cast<FloatBase>(-1.0);
	}
	
	const FloatNxN z2 = square(z);

	if (ic3 < 0) {
		t1 = static_cast<FloatBase>(0.0);
		t2 = z;
		t3 = static_cast<FloatBase>(1.0);
		call_dd_dmc(static_cast<FloatBase>(1.0e10), 0, t5);

		for (int k = 0; k < max_iter; k++) {
			if (k > 0) {
				t6 = mul_pwr2(z2, static_cast<FloatBase>(2.0));
				t2 *= t6;
				d1 = static_cast<FloatBase>(2.0) * static_cast<FloatBase>(k) + static_cast<FloatBase>(1.0);
				t3 *= d1;
			}

			t4 = t2 / t3;
			t1 += t4;
			t6 = t4 / t1;
			call_dd_cpr(t6, static_cast<FloatNxN>(target_epsilon), ic1);
			call_dd_cpr(t6, t5, ic2);
			if (ic1 <= 0 || ic2 >= 0) {
				// goto JMP_120;
				break;
			}
			t5 = t6;
		}

	// write (dd_ldb, 3) 1, max_iter;
	// 3 format ('*** DDERFR: iteration limit exceeded',2i10);
	// call_dd_abrt
	// /* label */ JMP_120:

		t3 = mul_pwr2(t1, static_cast<FloatBase>(2.0));
		t6 = FloatNxN_sqrtpi * exp(z2);
		terf = t3 / t6;
	} else {
		t1 = static_cast<FloatBase>(0.0);
		t2 = static_cast<FloatBase>(1.0);
		t3 = fabs(z);
		call_dd_dmc(static_cast<FloatBase>(1.0e10), 0, t5);

		for (int k = 0; k < max_iter; k++) {
			if (k > 0) {
				d1 = -(static_cast<FloatBase>(2.0) * static_cast<FloatBase>(k) - static_cast<FloatBase>(1.0));
				t2 *= d1;
				t3 *= t2;
			}

			t4 = t2 / t3;
			t1 += t4;
			t6 = t4 / t1;
			call_dd_cpr(t6, target_epsilon, ic1);
			call_dd_cpr(t6, t5, ic2);
			if (ic1 <= 0 || ic2 >= 0) {
				// goto JMP_130;
				break;
			}
			t5 = t6;
		}

	// write (dd_ldb, 3) 2, max_iter;
	// call_dd_abrt
	// /* label */ JMP_130:

		t5 = FloatNxN_sqrtpi * exp(z2);
		t6 = t1 / t5;
		terf = static_cast<FloatBase>(1.0) - t6;
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
 */
template<
	typename FloatNxN, typename FloatBase, int FloatBase_count,
	int max_iter
>
static inline FloatNxN libDDFUN_erfc(
	const FloatNxN& z,
	const FloatNxN FloatNxN_sqrtpi,
	const FloatBase FloatBase_ln2,
	const FloatBase target_epsilon
) {
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
	int ic1, ic2, ic3;
	// int n1; // unused?
	FloatBase d1, d2;
	FloatNxN t1, t2, t3, t4, t5, t6;
	FloatNxN tc1;
	// FloatNxN tc2, tc3; // unused?

	// int dd_nw, dd_nw1;
	// dd_nw = Float80x2_count;
	// dd_nw1 = std::min(dd_nw + 1, Float80x2_count);

	tc1 = static_cast<FloatBase>(2.0);
	d1 = trunc(static_cast<FloatBase>(1.0) + sqrt(
		static_cast<FloatBase>(std::numeric_limits<FloatNxN>::digits) * FloatBase_ln2
	));
	d2 = trunc((
		static_cast<FloatBase>(std::numeric_limits<FloatNxN>::digits) / dcon
	) + static_cast<FloatBase>(8.0));
	t1 = d1;
	t2 = d2;
	call_dd_cpr(z, t1, ic1);
	t1 = -t1;
	call_dd_cpr(z, t1, ic2);
	call_dd_cpr(z, t2, ic3);

	if (isequal_zero(z)) { // sign(z) == 0
		// z == 0.0
		return static_cast<FloatBase>(1.0);
	}
	if ((isinf(z) && isgreater_zero(z)) || ic1 > 0) {
		// z == +inf
		return static_cast<FloatBase>(0.0);
	}
	if ((isinf(z) && isless_zero(z)) || ic2 < 0) {
		// z == -inf
		return static_cast<FloatBase>(2.0);
	}

	const FloatNxN z2 = square(z);

	if (ic3 < 0) {
		t1 = static_cast<FloatBase>(0.0);
		t2 = z;
		t3 = static_cast<FloatBase>(1.0);
		call_dd_dmc(static_cast<FloatBase>(1.0e10), 0, t5);

		for (int k = 0; k < max_iter; k++) {
			if (k > 0) {
				t6 = mul_pwr2(z2, static_cast<FloatBase>(2.0));
				
				t2 *= t6;
				d1 = static_cast<FloatBase>(2.0) * static_cast<FloatBase>(k) + static_cast<FloatBase>(1.0);
				t3 *= d1;
			}

			t4 = t2 / t3;
			t1 += t4;
			t6 = t4 / t1;
			call_dd_cpr(t6, target_epsilon, ic1);
			call_dd_cpr(t6, t5, ic2);
			if (ic1 <= 0 || ic2 >= 0) {
				// goto JMP_120;
				break;
			}
			t5 = t6;
		}

	// write (dd_ldb, 3) 1, max_iter;
	// 3 format ('*** DDERFCR: iteration limit exceeded',2i10);
	// call_dd_abrt
	// /* label */ JMP_120:

		t3 = mul_pwr2(t1, static_cast<FloatBase>(2.0));
		t6 = FloatNxN_sqrtpi * exp(z2);
		terfc = static_cast<FloatBase>(1.0) - (t3 / t6);
	} else {
		t1 = static_cast<FloatBase>(0.0);
		t2 = static_cast<FloatBase>(1.0);
		t3 = fabs(z);
		t5 = static_cast<FloatBase>(1.0e10);

		for (int k = 0; k < max_iter; k++) {
			if (k > 0) {
				d1 = -(static_cast<FloatBase>(2.0) * static_cast<FloatBase>(k) - static_cast<FloatBase>(1.0));
				t2 *= d1;
				t3 *= t2;
			}

			t4 = t2 / t3;
			t1 += t4;
			t6 = t4 / t1;
			call_dd_cpr(t6, target_epsilon, ic1);
			call_dd_cpr(t6, t5, ic2);
			if (ic1 <= 0 || ic2 >= 0) {
				// goto JMP_130;
				break;
			}
			t5 = t6;
		}

	// write (dd_ldb, 3) 2, max_iter;
	// call_dd_abrt
	// /* label */ JMP_130:

		t5 = FloatNxN_sqrtpi * exp(z2);
		terfc = t1 / t5;
		if (isless_zero(z)) { // sign(z) < 0
			terfc = static_cast<FloatBase>(2.0) - terfc;
		}
	}

	return terfc;
}

#endif /* FLOATNXN_ERF_HPP */
