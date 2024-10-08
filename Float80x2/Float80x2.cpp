/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

/*
**	Portions of this file were part of the libQD library, licensed
**	under a modifed BSD license that can be found below:
**	https://www.davidhbailey.com/dhbsoftware/LBNL-BSD-License.docx
**	Or alternatively from this website:
**	https://www.davidhbailey.com/dhbsoftware/
**	A copy of the LBNL-BSD-License can also be found at:
**	LIB-Dekker-Float/libQD/LBNL-BSD-License.txt
*/

#include "Float80x2.hpp"
#include "Float80x2_def.h"
#include "Float80x2_string.h"

#include "Float80x2_LUT.hpp"

#include <cmath>
#include <cstddef>
#include <limits>


//------------------------------------------------------------------------------
// Float80x2 exp and log
//------------------------------------------------------------------------------

/** 
 * @author Taken from libQD qd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
static inline Float80x2 taylor_expm1(const Float80x2& x, fp80& m) {
	/* Strategy:  We first reduce the size of x by noting that
		 
					exp(kr + m * log(2)) = 2^m * exp(r)^k

		 where m and k are integers.  By choosing m appropriately
		 we can make |kr| <= log(2) / 2 = 0.346574.  Then exp(r) is 
		 evaluated using the familiar Taylor series.  Reducing the 
		 argument substantially speeds up the convergence.       */

	// constexpr fp80 k = 0x1.0p+16L;
	constexpr fp80 recip_k = static_cast<fp80>(0x1.0p-16L);

	m = std::floor(x.hi * LDF::const_log2e<fp80>() + static_cast<fp80>(0.5));
	Float80x2 r = mul_pwr2(x - LDF::const_ln2<Float80x2>() * m, recip_k);
	Float80x2 s, p, t;
	fp80 thresh = recip_k * std::numeric_limits<Float80x2>::epsilon().hi;

	p = square(r);
	s = r + mul_pwr2(p, static_cast<fp80>(0.5));
	int i = 0;
	do {
		p *= r;
		t = p * inv_fact[i++];
		s += t;
	} while (std::fabs(t.hi) > thresh && i < 9);

	s = mul_pwr2(s, static_cast<fp80>(2.0)) + square(s);
	s = mul_pwr2(s, static_cast<fp80>(2.0)) + square(s);
	s = mul_pwr2(s, static_cast<fp80>(2.0)) + square(s);
	s = mul_pwr2(s, static_cast<fp80>(2.0)) + square(s);

	s = mul_pwr2(s, static_cast<fp80>(2.0)) + square(s);
	s = mul_pwr2(s, static_cast<fp80>(2.0)) + square(s);
	s = mul_pwr2(s, static_cast<fp80>(2.0)) + square(s);
	s = mul_pwr2(s, static_cast<fp80>(2.0)) + square(s);

	s = mul_pwr2(s, static_cast<fp80>(2.0)) + square(s);
	s = mul_pwr2(s, static_cast<fp80>(2.0)) + square(s);
	s = mul_pwr2(s, static_cast<fp80>(2.0)) + square(s);
	s = mul_pwr2(s, static_cast<fp80>(2.0)) + square(s);

	s = mul_pwr2(s, static_cast<fp80>(2.0)) + square(s);
	s = mul_pwr2(s, static_cast<fp80>(2.0)) + square(s);
	s = mul_pwr2(s, static_cast<fp80>(2.0)) + square(s);
	s = mul_pwr2(s, static_cast<fp80>(2.0)) + square(s);

	return s;
}

Float80x2 exp(const Float80x2& x) {
	if (x.hi <= static_cast<fp80>(-11356.53L)) {
		// Gives a better approximation near extreme values
		return exp(x.hi);
	}
	/* ln(2^1023 * (1 + (1 - 2^-52)))) = ~11356.523406294 */
	if (x.hi >= static_cast<fp80>(11356.53L)) {
		return std::numeric_limits<Float80x2>::infinity();
	}
	if (isequal_zero(x)) {
		return static_cast<Float80x2>(1.0);
	}
	if (x == static_cast<fp80>(1.0)) {
		return LDF::const_e<Float80x2>();
	}
	if (x == static_cast<fp80>(-1.0)) {
		return LDF::const_inv_e<Float80x2>();
	}

	fp80 m;
	Float80x2 ret = taylor_expm1(x, m);
	ret += static_cast<fp80>(1.0);
	return ldexp(ret, static_cast<int>(m));
}

Float80x2 expm1(const Float80x2& x) {
	if (x.hi <= static_cast<fp80>(-11356.53L)) {
		return static_cast<Float80x2>(-1.0);
	}
	if (x.hi >= static_cast<fp80>(11356.53L)) {
		return std::numeric_limits<Float80x2>::infinity();
	}
	if (isequal_zero(x)) {
		return static_cast<Float80x2>(0.0);
	}

	fp80 m;
	Float80x2 ret = taylor_expm1(x, m);
	if (fabs(x) < mul_pwr2(static_cast<fp80>(0.5), LDF::const_ln2<Float80x2>())) {
		return ret; // expm1 to higher accuracy
	}
	ret += static_cast<fp80>(1.0);
	ret = ldexp(ret, static_cast<int>(m));
	return ret - static_cast<fp80>(1.0); // expm1 to standard accuracy
}

/** 
 * @brief Logarithm.  Computes log(x) in double-double precision.
 * @note This is a natural logarithm (i.e., base e).
 *
 * @author Taken from libQD dd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float80x2 log(const Float80x2& x) {
	/* Strategy.  The Taylor series for log converges much more
		slowly than that of exp, due to the lack of the factorial
		term in the denominator.  Hence this routine instead tries
		to determine the root of the function

			f(x) = exp(x) - a

		using Newton iteration.  The iteration is given by

			x' = x - f(x)/f'(x) 
			= x - (1 - a * exp(-x))
			= x + a * exp(-x) - 1.
			
		Only one iteration is needed, since Newton's iteration
		approximately doubles the number of digits per iteration. */

	if (x == static_cast<fp80>(1.0)) {
		return static_cast<fp80>(0.0);
	}

	if (islessequal_zero(x)) {
		if (isequal_zero(x)) {
			return -std::numeric_limits<Float80x2>::infinity();
		}
		// Float80x2::error("(Float80x2::log): Non-positive argument.");
		return std::numeric_limits<Float80x2>::quiet_NaN();
	}

	Float80x2 guess = log(x.hi);   /* Initial approximation */
	return guess.hi + x * exp(-guess) - static_cast<fp80>(1.0);
}

//------------------------------------------------------------------------------
// Float80x2 sin and cos
//------------------------------------------------------------------------------

static constexpr Float80x2 taylor_pi1024 = {0xc.90fdaa22168c235p-12L,-0xe.ce675d1fc8f8cbbp-78L};

/**
 * @brief Computes sin(a) and cos(a) using Taylor series.
 * @note Assumes |a| <= pi/2048.
 *
 * @author Taken from libQD dd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
static void sincos_taylor(const Float80x2& a, Float80x2& sin_a, Float80x2& cos_a) {
	const fp80 thresh = static_cast<fp80>(0.5) * std::numeric_limits<Float80x2>::epsilon().hi * std::fabs(a.hi);
	Float80x2 p, s, t, x;

	if (isequal_zero(a)) {
		sin_a = 0.0;
		cos_a = 1.0;
		return;
	}

	x = -square(a);
	s = a;
	p = a;
	size_t i = 0;
	do {
		p *= x;
		t = p * inv_fact_odd[i];
		s += t;
		++i;
	} while (i < (sizeof(inv_fact_odd) / sizeof(inv_fact_odd[0])) && std::fabs(t.hi) > thresh);

	sin_a = s;
	cos_a = sqrt(static_cast<fp80>(1.0) - square(s));
}

/** 
 * @brief Computes sin(a) using Taylor series.
 * @note Assumes |a| <= pi/2048.
 *
 * @author Taken from libQD qd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
static Float80x2 sin_taylor(const Float80x2& a) {
	const fp80 thresh = 0.5 * std::numeric_limits<Float80x2>::epsilon().hi * std::fabs(a.hi);
	Float80x2 p, s, t, x;

	if (isequal_zero(a)) {
		return 0.0;
	}

	x = -square(a);
	s = a;
	p = a;
	size_t i = 0;
	do {
		p *= x;
		t = p * inv_fact_odd[i];
		s += t;
		++i;
	} while (i < (sizeof(inv_fact_odd) / sizeof(inv_fact_odd[0])) && std::fabs(t.hi) > thresh);

	return s;
}

/** 
 * @brief Computes cos(a) using Taylor series.
 * @note Assumes |a| <= pi/2048.
 *
 * @author Taken from libQD qd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
static Float80x2 cos_taylor(const Float80x2& a) {
	const fp80 thresh = static_cast<fp80>(0.5) * std::numeric_limits<Float80x2>::epsilon().hi;
	Float80x2 p, s, t, x;

	if (isequal_zero(a)) {
		return static_cast<fp80>(1.0) ;
	}

	x = -square(a);
	s = static_cast<fp80>(1.0) + mul_pwr2(x, static_cast<fp80>(0.5));
	p = x;
	size_t i = 0;
	do {
		p *= x;
		t = p * inv_fact_even[i];
		s += t;
		++i;
	} while (i < (sizeof(inv_fact_even) / sizeof(inv_fact_even[0])) && std::fabs(t.hi) > thresh);

	return s;
}


/** 
 * @author Taken from libQD qd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float80x2 sin(const Float80x2& a) {

	/* Strategy.  To compute sin(x), we choose integers a, b so that

			 x = s + a * (pi/2) + b * (pi/1024)

		 and |s| <= pi/2048.  Using a precomputed table of
		 sin(k pi / 1024) and cos(k pi / 1024), we can compute
		 sin(x) from sin(s) and cos(s).  This greatly increases the
		 convergence of the sine Taylor series.                          */

	if (isequal_zero(a)) {
		return static_cast<fp80>(0.0);
	}

	// approximately reduce modulo 2*pi
	Float80x2 z = round(a / LDF::const_2pi<Float80x2>());
	Float80x2 r = a - LDF::const_2pi<Float80x2>() * z;

	// approximately reduce modulo pi/2 and then modulo pi/1024
	fp80 q = std::floor(r.hi / LDF::const_pi2<fp80>() + static_cast<fp80>(0.5));
	Float80x2 t = r - LDF::const_pi2<Float80x2>() * q;
	int j = static_cast<int>(q);
	q = std::floor(t.hi / taylor_pi1024.hi + static_cast<fp80>(0.5));
	t -= taylor_pi1024 * q;
	int k = static_cast<int>(q);
	int abs_k = std::abs(k);

	if (j < -2 || j > 2) {
		// qd_real::error("(qd_real::sin): Cannot reduce modulo pi/2.");
		return std::numeric_limits<Float80x2>::quiet_NaN();
	}

	if (abs_k > 256) {
		// qd_real::error("(qd_real::sin): Cannot reduce modulo pi/1024.");
		return std::numeric_limits<Float80x2>::quiet_NaN();
	}

	if (k == 0) {
		switch (j) {
			case 0:
				return sin_taylor(t);
			case 1:
				return cos_taylor(t);
			case -1:
				return -cos_taylor(t);
			default:
				return -sin_taylor(t);
		}
	}

	Float80x2 sin_t, cos_t;
	Float80x2 u = cos_table[abs_k-1];
	Float80x2 v = sin_table[abs_k-1];
	sincos_taylor(t, sin_t, cos_t);

	if (j == 0) {
		if (k > 0) {
			r = u * sin_t + v * cos_t;
		} else {
			r = u * sin_t - v * cos_t;
		}
	} else if (j == 1) {
		if (k > 0) {
			r = u * cos_t - v * sin_t;
		} else {
			r = u * cos_t + v * sin_t;
		}
	} else if (j == -1) {
		if (k > 0) {
			r = v * sin_t - u * cos_t;
		} else {
			r = - u * cos_t - v * sin_t;
		}
	} else {
		if (k > 0) {
			r = - u * sin_t - v * cos_t;
		} else {
			r = v * cos_t - u * sin_t;
		}
	}

	return r;
}

/** 
 * @author Taken from libQD qd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float80x2 cos(const Float80x2& a) {

	if (isequal_zero(a)) {
		return static_cast<fp80>(1.0);
	}

	// approximately reduce modulo 2*pi
	Float80x2 z = round(a / LDF::const_2pi<Float80x2>());
	Float80x2 r = a - LDF::const_2pi<Float80x2>() * z;

	// approximately reduce modulo pi/2 and then modulo pi/1024
	fp80 q = std::floor(r.hi / LDF::const_pi2<fp80>() + static_cast<fp80>(0.5));
	Float80x2 t = r - LDF::const_pi2<Float80x2>() * q;
	int j = static_cast<int>(q);
	q = std::floor(t.hi / taylor_pi1024.hi + static_cast<fp80>(0.5));
	t -= taylor_pi1024 * q;
	int k = static_cast<int>(q);
	int abs_k = std::abs(k);

	if (j < -2 || j > 2) {
		// qd_real::error("(qd_real::cos): Cannot reduce modulo pi/2.");
		return std::numeric_limits<Float80x2>::quiet_NaN();
	}

	if (abs_k > 256) {
		// qd_real::error("(qd_real::cos): Cannot reduce modulo pi/1024.");
		return std::numeric_limits<Float80x2>::quiet_NaN();
	}

	if (k == 0) {
		switch (j) {
			case 0:
				return cos_taylor(t);
			case 1:
				return -sin_taylor(t);
			case -1:
				return sin_taylor(t);
			default:
				return -cos_taylor(t);
		}
	}

	Float80x2 sin_t, cos_t;
	sincos_taylor(t, sin_t, cos_t);

	Float80x2 u = cos_table[abs_k-1];
	Float80x2 v = sin_table[abs_k-1];

	if (j == 0) {
		if (k > 0) {
			r = u * cos_t - v * sin_t;
		} else {
			r = u * cos_t + v * sin_t;
		}
	} else if (j == 1) {
		if (k > 0) {
			r = - u * sin_t - v * cos_t;
		} else {
			r = v * cos_t - u * sin_t;
		}
	} else if (j == -1) {
		if (k > 0) {
			r = u * sin_t + v * cos_t;
		} else {
			r = u * sin_t - v * cos_t;
		}
	} else {
		if (k > 0) {
			r = v * sin_t - u * cos_t;
		} else {
			r = - u * cos_t - v * sin_t;
		}
	}

	return r;
}

/** 
 * @author Taken from libQD qd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
void sincos(const Float80x2& a, Float80x2& sin_a, Float80x2& cos_a) {

	if (isequal_zero(a)) {
		sin_a = static_cast<fp80>(0.0);
		cos_a = static_cast<fp80>(1.0);
		return;
	}

	// approximately reduce modulo 2*pi
	Float80x2 z = round(a / LDF::const_2pi<Float80x2>());
	Float80x2 r = a - LDF::const_2pi<Float80x2>() * z;

	// approximately reduce modulo pi/2 and then modulo pi/1024
	fp80 q = std::floor(r.hi / LDF::const_pi2<fp80>() + static_cast<fp80>(0.5));
	Float80x2 t = r - LDF::const_pi2<Float80x2>() * q;
	int j = static_cast<int>(q);
	q = std::floor(t.hi / taylor_pi1024.hi + static_cast<fp80>(0.5));
	t -= taylor_pi1024 * q;
	int k = static_cast<int>(q);
	int abs_k = std::abs(k);

	if (j < -2 || j > 2) {
		// qd_real::error("(qd_real::sincos): Cannot reduce modulo pi/2.");
		cos_a = sin_a = std::numeric_limits<Float80x2>::quiet_NaN();
		return;
	}

	if (abs_k > 256) {
		// qd_real::error("(qd_real::sincos): Cannot reduce modulo pi/1024.");
		cos_a = sin_a = std::numeric_limits<Float80x2>::quiet_NaN();
		return;
	}

	Float80x2 sin_t, cos_t;
	sincos_taylor(t, sin_t, cos_t);

	if (k == 0) {
		if (j == 0) {
			sin_a = sin_t;
			cos_a = cos_t;
		} else if (j == 1) {
			sin_a = cos_t;
			cos_a = -sin_t;
		} else if (j == -1) {
			sin_a = -cos_t;
			cos_a = sin_t;
		} else {
			sin_a = -sin_t;
			cos_a = -cos_t;
		}
		return;
	}

	Float80x2 u = cos_table[abs_k-1];
	Float80x2 v = sin_table[abs_k-1];

	if (j == 0) {
		if (k > 0) {
			sin_a = u * sin_t + v * cos_t;
			cos_a = u * cos_t - v * sin_t;
		} else {
			sin_a = u * sin_t - v * cos_t;
			cos_a = u * cos_t + v * sin_t;
		}
	} else if (j == 1) {
		if (k > 0) {
			cos_a = - u * sin_t - v * cos_t;
			sin_a = u * cos_t - v * sin_t;
		} else {
			cos_a = v * cos_t - u * sin_t;
			sin_a = u * cos_t + v * sin_t;
		}
	} else if (j == -1) {
		if (k > 0) {
			cos_a = u * sin_t + v * cos_t;
			sin_a =  v * sin_t - u * cos_t;
		} else {
			cos_a = u * sin_t - v * cos_t;
			sin_a = - u * cos_t - v * sin_t;
		}
	} else {
		if (k > 0) {
			sin_a = - u * sin_t - v * cos_t;
			cos_a = v * sin_t - u * cos_t;
		} else {
			sin_a = v * cos_t - u * sin_t;
			cos_a = - u * cos_t - v * sin_t;
		}
	}
}

//------------------------------------------------------------------------------
// Float80x2 pown
//------------------------------------------------------------------------------

Float80x2 pown(const Float80x2& x, int n) {
	
	if (n == 0) {
		return static_cast<fp80>(1.0);
	}
	if (isequal_zero(x)) {
		return static_cast<fp80>(0.0);
	}

	Float80x2 r = x;
	Float80x2 s = static_cast<fp80>(1.0);
	// casts to unsigned int since abs(INT_MIN) < 0
	unsigned int N = static_cast<unsigned int>((n < 0) ? -n : n);

	if (N > 1) {
		/* Use binary exponentiation */
		while (N > 0) {
			if (N % 2 == 1) {
				s *= r;
			}
			N /= 2;
			if (N > 0) {
				r = square(r);
			}
		}
	} else {
		s = r;
	}

	/* Compute the reciprocal if n is negative. */
	if (n < 0) {
		return recip(s);
	}
	return s;
}

//------------------------------------------------------------------------------
// Float80x2 erf and erfc
//------------------------------------------------------------------------------

#include "../FloatNxN/FloatNxN_erf.hpp"

Float80x2 erf(const Float80x2& x) {
	return libDDFUN_erf<
		Float80x2, fp80,
		4096
	>(x);
}

Float80x2 erfc(const Float80x2& x) {
	return libDDFUN_erfc<
		Float80x2, fp80,
		4096
	>(x);
}

//------------------------------------------------------------------------------
// Float80x2 inverf
//------------------------------------------------------------------------------

#if 0

Float80x2 inverf(const Float80x2& x) {
	Float80x2 sum = static_cast<fp80>(0.0);
	const Float80x2 x_squared = square(x);
	Float80x2 x_pow = x;
	for (size_t i = 0; i < 20; i++) {
		sum += x_pow * inverf_table[i];
		x_pow *= x_squared;
	}
	return sum;
}

#elif 1

static inline void inverf_newton(const Float80x2& x, Float80x2& guess, const int max_iter) {
	constexpr Float80x2 sqrt_pi4 = mul_pwr2(LDF::const_sqrtpi<Float80x2>(), static_cast<fp80>(0.5));
	Float80x2 next_guess;
	for (int i = 0; i < max_iter; i++) {
		next_guess = guess - (erf(guess) - x) * exp(square(guess)) * sqrt_pi4;
		// Unordered comparisons protect against NaN
		if (!(fabs(next_guess - guess) > std::numeric_limits<Float80x2>::epsilon().hi)) {
			break;
		}
		guess = next_guess;
	}
}

/**
 * @remarks Calculates an approximation, and the performs newtons method to find inverf
 * @author https://en.wikipedia.org/wiki/Error_function
 */
Float80x2 inverf(const Float80x2& x) {
	if (isequal_zero(x)) {
		return x;
	}
	// Unordered NLE catches NaN's
	if (!(fabs(x) < static_cast<fp80>(1.0))) {
		if (x == static_cast<fp80>(1.0)) {
			return std::numeric_limits<Float80x2>::infinity();
		}
		if (x == static_cast<fp80>(-1.0)) {
			return -std::numeric_limits<Float80x2>::infinity();
		}
		return std::numeric_limits<Float80x2>::quiet_NaN();
	}

	#if 0
		Float80x2 guess;
		if (x > static_cast<fp80>(9.0)) {
			guess = x;
			inverf_newton(x, guess, 1000);
		} else {
			// alternate value 0.140012
			const fp80 alpha = static_cast<fp80>(0.147);
			// 2 / (pi * alpha)
			const Float80x2 alpha_term = static_cast<fp80>(2.0) / (LDF::const_pi<Float80x2>() * alpha);

			// ln(1 - x^2) == log1p(-x^2)
			const Float80x2 log_term = log1p(-square(x));
			
			// alpha_term + log_term / 2
			const Float80x2 alpha_log_term = alpha_term + mul_pwr2(log_term, static_cast<fp80>(0.5));

			guess = sqrt(
				sqrt(square(alpha_log_term) - log_term / alpha) - alpha_log_term
			);
			inverf_newton(x, guess, 32);
		}
	#else
		// Rough approximation
		Float80x2 guess = sqrt(log(recip(static_cast<fp80>(1.0) - square(x))));
		if (isless_zero(x)) {
			guess = -guess;
		}
		inverf_newton(x, guess, 32);
	#endif

	/**
	 * @remarks since erf(inf) approaches 1.0 instead of 0.0 like erfc(inf),
	 * there appears to be some precision issues, which outputs random large
	 * values with the wrong signage. The incorrect signage can be used to
	 * sort-of detect arithmetic errors from inverf_newton.
	 */
	if (signbit(x) != signbit(guess) || isnan(x)) {
		return signbit(x) ?
			-std::numeric_limits<Float80x2>::infinity() :
			 std::numeric_limits<Float80x2>::infinity();
	}
	return guess;
}

#endif

static int64_t total_itr = 0;

static inline void inverfc_newton(const Float80x2& x, Float80x2& guess, const int max_iter) {
	constexpr Float80x2 sqrt_pi4 = mul_pwr2(LDF::const_sqrtpi<Float80x2>(), static_cast<fp80>(0.5));
	Float80x2 next_guess;
	for (int i = 0; i < max_iter; i++) {
		total_itr++;
		next_guess = guess + (erfc(guess) - x) * exp(square(guess)) * sqrt_pi4;
		// Unordered comparisons protect against NaN
		if (!(fabs(next_guess - guess) > std::numeric_limits<Float80x2>::epsilon().hi)) {
			break;
		}
		guess = next_guess;
	}
}

Float80x2 inverfc(const Float80x2& x) {
	if (islessequal_zero(x)) {
		if (isequal_zero(x)) {
			return std::numeric_limits<Float80x2>::infinity();
		}
		return std::numeric_limits<Float80x2>::quiet_NaN();
	}
	if (x >= static_cast<fp80>(2.0)) {
		if (x == static_cast<fp80>(2.0)) {
			return -std::numeric_limits<Float80x2>::infinity();
		}
		return std::numeric_limits<Float80x2>::quiet_NaN();
	}
	// Probably more accurate, and avoids the asymptotes around 1.0 for inverfc
	if (x.hi >= static_cast<fp80>(0.5)) {
		return inverf(static_cast<fp80>(1.0) - x);
	}

	const Float80x2 log_half_x = log(mul_pwr2(static_cast<fp80>(0.5), x));
	const Float80x2 sqrt_neg_log_half_x = sqrt(-log_half_x);

	/**
	 * @remarks Tweaking this value can reduce the average iterations used. It
	 * subtracts a value between 0.0 and 0.289179 from the guess to get a better
	 * approximation.
	 */
	// 0.023178 is the error in the guess when calculating inverfc(erfc(106.4))
	const fp80 underestimate_value = static_cast<fp80>(0.023178);
	Float80x2 guess = sqrt_neg_log_half_x - log_half_x / mul_pwr2(static_cast<fp80>(2.0), sqrt_neg_log_half_x) - underestimate_value;

	inverfc_newton(x, guess, 32);
	printf("Total itr %8lld ", total_itr);
	return guess;
}

//------------------------------------------------------------------------------
// Float80x2 tgamma
//------------------------------------------------------------------------------

#include "../FloatNxN/FloatNxN_tgamma.hpp"

Float80x2 tgamma(const Float80x2& t) {
	return libDQFUN_tgamma<
		Float80x2, fp80,
		100000
	>(t);
}

//------------------------------------------------------------------------------
// Float80x2 incgamma
//------------------------------------------------------------------------------

#include "../FloatNxN/FloatNxN_incgamma.hpp"

Float80x2 incgamma(const Float80x2& s, const Float80x2& z) {
	return libDDFUN_incgamma<
		Float80x2, fp80,
		1000000
	>(s, z);
}

//------------------------------------------------------------------------------
// Float80x2 expint
//------------------------------------------------------------------------------

Float80x2 expint(const Float80x2& x) {
	return libDDFUN_expint<
		Float80x2, fp80,
		1000000
	>(x);
}

//------------------------------------------------------------------------------
// Float80x2 riemann_zeta
//------------------------------------------------------------------------------

#include "../FloatNxN/FloatNxN_riemann_zeta.hpp"

Float80x2 riemann_zeta(const Float80x2& x) {
	return libDDFUN_riemann_zeta<
		Float80x2, fp80,
		1000000
	>(x);
}

//------------------------------------------------------------------------------
// Float80x2 Bessel Functions
//------------------------------------------------------------------------------

#include "../FloatNxN/FloatNxN_cyl_bessel.hpp"

/** @brief regular modified cylindrical Bessel function */
Float80x2 cyl_bessel_i(const Float80x2& nu, const Float80x2& x) {
	return libDDFUN_cyl_bessel_i<
		Float80x2, fp80,
		1000000
	>(nu, x);
}

/** @brief cylindrical Bessel functions (of the first kind) */
Float80x2 cyl_bessel_j(const Float80x2& nu, const Float80x2& x) {
	return libDDFUN_cyl_bessel_j<
		Float80x2, fp80,
		1000000
	>(nu, x);
}

/** @brief irregular modified cylindrical Bessel functions  */
Float80x2 cyl_bessel_k(const Float80x2& nu, const Float80x2& x) {
	return libDDFUN_cyl_bessel_k<
		Float80x2, fp80,
		1000000
	>(nu, x);
}

/** @brief Bessel function of the second kind. */
Float80x2 cyl_neumann(const Float80x2& nu, const Float80x2& x) {
	return libDDFUN_cyl_bessel_y<
		Float80x2, fp80,
		1000000
	>(nu, x);
}

/** @brief regular modified cylindrical Bessel function */
Float80x2 cyl_bessel_i(int nu, const Float80x2& x) {
	return libDDFUN_cyl_bessel_i_integer<
		Float80x2, fp80,
		1000000
	>(nu, x);
}

/** @brief cylindrical Bessel functions (of the first kind) */
Float80x2 cyl_bessel_j(int nu, const Float80x2& x) {
	return libDDFUN_cyl_bessel_j_integer<
		Float80x2, fp80,
		1000000
	>(nu, x);
}

/** @brief irregular modified cylindrical Bessel functions  */
Float80x2 cyl_bessel_k(int nu, const Float80x2& x) {
	return libDDFUN_cyl_bessel_k_integer<
		Float80x2, fp80,
		1000000
	>(nu, x);
}

/** @brief Bessel function of the second kind. */
Float80x2 cyl_neumann(int nu, const Float80x2& x) {
	return libDDFUN_cyl_bessel_y_integer<
		Float80x2, fp80,
		1000000
	>(nu, x);
}

//------------------------------------------------------------------------------
// Float80x2 from string
//------------------------------------------------------------------------------

#include "../FloatNxN/FloatNxN_stringTo.hpp"

Float80x2 stringTo_Float80x2(const char* nPtr, char** endPtr) {
	internal_FloatNxN_stringTo<Float80x2, fp80> stringTo_func;
	return stringTo_func.stringTo_FloatNxN(nPtr, endPtr);
}

std::istream& operator>>(std::istream& stream, Float80x2& value) {
	internal_FloatNxN_stringTo<Float80x2, fp80> func_cin;
	return func_cin.cin_FloatNxN(stream, value);
}

//------------------------------------------------------------------------------
// Float80x2 to string
//------------------------------------------------------------------------------

#include "../FloatNxN/FloatNxN_snprintf.hpp"

int Float80x2_snprintf(char* buf, size_t len, const char* format, ...) {
	va_list args;
	va_start(args, format);
	internal_FloatNxN_snprintf<Float80x2, fp80, 2> func_snprintf;
	int ret_val = func_snprintf.FloatNxN_snprintf(
		PRIFloat80x2, PRIFloat80,
		buf, len, format, args
	);
	va_end(args);
	return ret_val;
}

std::ostream& operator<<(std::ostream& stream, const Float80x2& value) {
	internal_FloatNxN_snprintf<Float80x2, fp80, 2> func_cout;
	return func_cout.FloatNxN_cout(PRIFloat80x2, PRIFloat80, stream, value);
}
