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
