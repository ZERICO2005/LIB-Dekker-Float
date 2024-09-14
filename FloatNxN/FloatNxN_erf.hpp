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

/**
 * @brief Three way comparison <=> possibly?
 */
template<typename FloatNxN, typename FloatBase>
static inline void call_dd_cpr(const FloatNxN& x, const FloatBase y, int& ret) {
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
	FloatNxN t1, t2, t3, t4, t5, t6;

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
		t1 = static_cast<FloatBase>(0.0);
		t2 = z;
		t3 = static_cast<FloatBase>(1.0);
		call_dd_dmc(static_cast<FloatBase>(1.0e10), 0, t5);

		const FloatNxN z2_mul2 = mul_pwr2(z2, static_cast<FloatBase>(2.0));
		FloatBase k_mult = static_cast<FloatBase>(1.0);
		for (int k = 0; k <= max_iter; k++) {
			if (k > 0) {
				t2 *= z2_mul2;
				t3 *= k_mult;
			}

			t4 = t2 / t3;
			t1 += t4;
			t6 = t4 / t1;
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

		terf = mul_pwr2(t1, static_cast<FloatBase>(2.0)) * (LDF::const_inv_sqrtpi<FloatNxN>() * exp(-z2));
	} else {
		t1 = static_cast<FloatBase>(0.0);
		t2 = static_cast<FloatBase>(1.0);
		t3 = fabs(z);
		call_dd_dmc(static_cast<FloatBase>(1.0e10), 0, t5);

		FloatBase k_mult = static_cast<FloatBase>(1.0);
		for (int k = 0; k <= max_iter; k++) {
			if (k > 0) {
				t2 *= k_mult;
				t3 *= t2;
			}

			t4 = t2 / t3;
			t1 += t4;
			t6 = t4 / t1;

			if (t6 <= target_epsilon || t6 >= t5) {
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
			t1 * (LDF::const_inv_sqrtpi<FloatNxN>() * exp(-z2))
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
	FloatNxN t2, t3, t5, t6;

	// int dd_nw, dd_nw1;
	// dd_nw = Float80x2_count;
	// dd_nw1 = std::min(dd_nw + 1, Float80x2_count);
	const FloatBase target_epsilon = ldexp(
		static_cast<FloatBase>(1.0),
		-LDF::LDF_Type_Info<FloatNxN>::FloatBase_Count * std::numeric_limits<FloatBase>::digits
	);

	const FloatBase d1 = trunc(static_cast<FloatBase>(1.0) + sqrt(
		static_cast<FloatBase>(std::numeric_limits<FloatNxN>::digits) * LDF::const_ln2<FloatBase>()
	));
	const FloatBase d2 = trunc((
		static_cast<FloatBase>(std::numeric_limits<FloatNxN>::digits) / dcon
	) + static_cast<FloatBase>(8.0));

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

	if (z < d2 || true) {
		FloatNxN taylor_sum = z;
		
		// I'm guessing that it was supposed to check that z < 1.0e10, breaking/returning otherwise.
		// t5 = static_cast<FloatBase>(1.0e10);

		FloatNxN taylor_val = z;

		const FloatNxN z2_mul2 = mul_pwr2(z2, static_cast<FloatBase>(2.0));

		t5 = static_cast<FloatBase>(1.0);
		FloatBase k_mult = static_cast<FloatBase>(0.0);
		for (int k = 1; k <= max_iter; k++) {
			taylor_val *= z2_mul2 / k_mult;

			taylor_sum += taylor_val;
			t6 = taylor_val / taylor_sum;

			if (!(t6 > target_epsilon) || t6 >= t5) {
				// goto JMP_120;
				break;
			}
			t5 = t6;
			k_mult += static_cast<FloatBase>(2.0);
		}

	// write (dd_ldb, 3) 1, max_iter;
	// 3 format ('*** DDERFCR: iteration limit exceeded',2i10);
	// call_dd_abrt
	// /* label */ JMP_120:

		terfc = static_cast<FloatBase>(1.0) - (
			mul_pwr2(taylor_sum, static_cast<FloatBase>(2.0)) *
			LDF::const_inv_sqrtpi<FloatNxN>() * exp(-z2)
		);
	} else {
		
		t2 = static_cast<FloatBase>(1.0);
		t3 = fabs(z);
		FloatNxN t4;

		// I'm guessing that it was supposed to check that z < 1.0e10, breaking/returning otherwise.
		// t5 = static_cast<FloatBase>(1.0e10);
		
		FloatNxN taylor_sum = recip(t3);

		t5 = static_cast<FloatBase>(1.0);

		FloatBase k_mult = static_cast<FloatBase>(-1.0);
		for (int k = 1; k <= max_iter; k++) {
			t2 *= k_mult;
			t3 *= t2;

			t4 = t2 / t3;
			taylor_sum += t4;
			t6 = t4 / taylor_sum;
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

		terfc = taylor_sum * (LDF::const_inv_sqrtpi<FloatNxN>() * exp(-z2));
		if (isless_zero(z)) { // sign(z) < 0
			terfc = static_cast<FloatBase>(2.0) - terfc;
		}
	}

	return terfc;
}

#endif /* FLOATNXN_ERF_HPP */
