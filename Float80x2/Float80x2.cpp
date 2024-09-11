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
#include "Float80x2_string.h"

#include "Float80x2_LUT.hpp"

#include <cmath>


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

	m = std::floor(x.hi * Float80x2_log2e.hi + static_cast<fp80>(0.5));
	Float80x2 r = mul_pwr2(x - Float80x2_ln2 * m, recip_k);
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
		return Float80x2_e;
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
	if (fabs(x) < static_cast<fp80>(0.5) * Float80x2_ln2) {
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

	if (x.hi <= static_cast<fp80>(0.0)) {
		if (x == static_cast<fp80>(0.0)) {
			return -std::numeric_limits<Float80x2>::infinity();
		}
		// Float64x2::error("(Float80x2::log): Non-positive argument.");
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
	Float80x2 z = round(a / Float80x2_2pi);
	Float80x2 r = a - Float80x2_2pi * z;

	// approximately reduce modulo pi/2 and then modulo pi/1024
	fp80 q = std::floor(r.hi / Float80x2_pi2.hi + static_cast<fp80>(0.5));
	Float80x2 t = r - Float80x2_pi2 * q;
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
	Float80x2 z = round(a / Float80x2_2pi);
	Float80x2 r = a - Float80x2_2pi * z;

	// approximately reduce modulo pi/2 and then modulo pi/1024
	fp80 q = std::floor(r.hi / Float80x2_pi2.hi + static_cast<fp80>(0.5));
	Float80x2 t = r - Float80x2_pi2 * q;
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

	// approximately reduce by 2*pi
	Float80x2 z = round(a / Float80x2_2pi);
	Float80x2 t = a - Float80x2_2pi * z;

	// approximately reduce by pi/2 and then by pi/1024.
	fp80 q = std::floor(t.hi / Float80x2_pi2.hi + static_cast<fp80>(0.5));
	t -= Float80x2_pi2 * q;
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
// Float80x2 erf and erfc
//------------------------------------------------------------------------------

#include "../FloatNxN/FloatNxN_erf.hpp"

Float80x2 erf(const Float80x2& x) {
	return libDDFUN_erf<
		Float80x2, fp80, 2,
		4096
	>(
		x,
		Float80x2_sqrtpi, Float80x2_ln2.hi,
		std::numeric_limits<Float80x2>::epsilon().hi * 0x1.0p-2L
	);
}

Float80x2 erfc(const Float80x2& x) {
	return libDDFUN_erfc<
		Float80x2, fp80, 2,
		4096
	>(
		x,
		Float80x2_sqrtpi, Float80x2_ln2.hi,
		std::numeric_limits<Float80x2>::epsilon().hi * 0x1.0p-2L
	);
}

//------------------------------------------------------------------------------
// Float80x2 tgamma
//------------------------------------------------------------------------------

#include "../FloatNxN/FloatNxN_tgamma.hpp"

Float80x2 tgamma(const Float80x2& t) {
	return libDQFUN_tgamma<
		Float80x2, fp80, 2,
		100000
	>(
		t,
		Float80x2_pi, Float80x2_ln2.hi
	);
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
