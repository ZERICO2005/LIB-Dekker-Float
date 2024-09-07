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

#include "Float64x4.h"
#include "Float64x4.hpp"

// The sin and cos tables were quite large
#include "Float64x4_LUT.hpp"
#include "Float64x4_def.h"
#include "Float64x4_string.h"

#include <cmath>
#include <limits>

/** 
 * @author Taken from libQD qd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
static inline Float64x4 taylor_expm1(const Float64x4& x, fp64& m) {
	/* Strategy:  We first reduce the size of x by noting that
		 
					exp(kr + m * log(2)) = 2^m * exp(r)^k

		 where m and k are integers.  By choosing m appropriately
		 we can make |kr| <= log(2) / 2 = 0.346574.  Then exp(r) is 
		 evaluated using the familiar Taylor series.  Reducing the 
		 argument substantially speeds up the convergence.       */

	// constexpr fp64 k = 0x1.0p+16;
	constexpr fp64 recip_k = 0x1.0p-16;

	m = std::floor(x.val[0] * Float64x4_log2e.val[0] + 0.5);
	Float64x4 r = mul_pwr2(x - Float64x4_ln2 * m, recip_k);
	Float64x4 s, p, t;
	fp64 thresh = recip_k * std::numeric_limits<Float64x4>::epsilon().val[0];

	p = square(r);
	s = r + mul_pwr2(p, 0.5);
	int i = 0;
	do {
		p *= r;
		t = p * inv_fact[i++];
		s += t;
	} while (std::fabs(t.val[0]) > thresh && i < 9);

	s = mul_pwr2(s, 2.0) + square(s);
	s = mul_pwr2(s, 2.0) + square(s);
	s = mul_pwr2(s, 2.0) + square(s);
	s = mul_pwr2(s, 2.0) + square(s);

	s = mul_pwr2(s, 2.0) + square(s);
	s = mul_pwr2(s, 2.0) + square(s);
	s = mul_pwr2(s, 2.0) + square(s);
	s = mul_pwr2(s, 2.0) + square(s);

	s = mul_pwr2(s, 2.0) + square(s);
	s = mul_pwr2(s, 2.0) + square(s);
	s = mul_pwr2(s, 2.0) + square(s);
	s = mul_pwr2(s, 2.0) + square(s);

	s = mul_pwr2(s, 2.0) + square(s);
	s = mul_pwr2(s, 2.0) + square(s);
	s = mul_pwr2(s, 2.0) + square(s);
	s = mul_pwr2(s, 2.0) + square(s);

	return s;
}

Float64x4 exp(const Float64x4& x) {
	if (x.val[0] <= -709.79) {
		// Gives a better approximation near extreme values
		return exp(x.val[0]);
	}
	/* ln(2^1023 * (1 + (1 - 2^-52)))) = ~709.782712893 */
	if (x.val[0] >= 709.79) {
		return std::numeric_limits<Float64x4>::infinity();
	}
	if (dekker_equal_zero(x)) {
		return static_cast<Float64x4>(1.0);
	}
	if (x == 1.0) {
		return Float64x4_e;
	}

	fp64 m;
	Float64x4 ret = taylor_expm1(x, m);
	ret += 1.0;
	return ldexp(ret, static_cast<int>(m));
}

Float64x4 expm1(const Float64x4& x) {
	if (x.val[0] <= -709.79) {
		return static_cast<Float64x4>(-1.0);
	}
	if (x.val[0] >= 709.79) {
		return std::numeric_limits<Float64x4>::infinity();
	}
	if (dekker_equal_zero(x)) {
		return static_cast<Float64x4>(0.0);
	}

	fp64 m;
	Float64x4 ret = taylor_expm1(x, m);
	if (fabs(x) < static_cast<fp64>(0.5) * Float64x4_ln2) {
		return ret; // expm1 to higher accuracy
	}
	ret += 1.0;
	ret = ldexp(ret, static_cast<int>(m));
	return ret - 1.0; // expm1 to standard accuracy
}

/** 
 * @brief Logarithm.  Computes log(x) in double-double precision.
 * @note This is a natural logarithm (i.e., base e).
 *
 * @author Taken from libQD qd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float64x4 log(const Float64x4& x) {
	/* Strategy.  The Taylor series for log converges much more
		 slowly than that of exp, due to the lack of the factorial
		 term in the denominator.  Hence this routine instead tries
		 to determine the root of the function

				 f(x) = exp(x) - a

		 using Newton iteration.  The iteration is given by

				 x' = x - f(x)/f'(x) 
						= x - (1 - a * exp(-x))
						= x + a * exp(-x) - 1.
					 
		 Two iteration is needed, since Newton's iteration 
		 approximately doubles the number of digits per iteration. */

	if (x == 1.0) {
		return 0.0;
	}
	if (dekker_equal_zero(x)) {
		return -std::numeric_limits<Float64x4>::infinity();
	}
	if (dekker_less_zero(x)) {
		// qd_real::error("(qd_real::log): Non-positive argument.");
		return std::numeric_limits<Float64x4>::quiet_NaN();
	}

	Float64x4 guess = std::log(x.val[0]);   /* Initial approximation */

	guess = guess.val[0] + x * exp(-guess) - 1.0;
	guess = guess + x * exp(-guess) - 1.0;
	guess = guess + x * exp(-guess) - 1.0;
	return guess;
}

/**
 * @remarks using similar methods to log(x)
 */
Float64x4 log1p(const Float64x4& x) {
	if (dekker_equal_zero(x)) {
		return 0.0;
	}
	if (x == -1.0) {
		return -std::numeric_limits<Float64x4>::infinity();
	}
	if (x < -1.0) {
		// qd_real::error("(qd_real::log): Non-positive argument.");
		return std::numeric_limits<Float64x4>::quiet_NaN();
	}
	Float64x4 guess = log1p(x.val[0]);
	guess = guess.val[0] + (x + 1.0) * exp(-guess) - 1.0;
	guess = guess + (x + 1.0) * exp(-guess) - 1.0;
	guess = guess + (x + 1.0) * exp(-guess) - 1.0;
	return guess;
}


static constexpr Float64x4 taylor_pi1024 = {0x1.921fb54442d18p-9,+0x1.1a62633145c07p-63,-0x1.f1976b7ed8fbcp-119,+0x1.4cf98e804177dp-173};

/**
 * @brief Computes sin(a) and cos(a) using Taylor series.
 * @note Assumes |a| <= pi/2048.
 *
 * @author Taken from libQD dd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
static void sincos_taylor(const Float64x4& a, Float64x4& sin_a, Float64x4& cos_a) {
	const fp64 thresh = 0.5 * std::numeric_limits<Float64x4>::epsilon().val[0] * std::fabs(a.val[0]);
	Float64x4 p, s, t, x;

	if (dekker_equal_zero(a)) {
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
	} while (i < (sizeof(inv_fact_odd) / sizeof(inv_fact_odd[0])) && std::fabs(t.val[0]) > thresh);

	sin_a = s;
	cos_a = sqrt(1.0 - square(s));
}

/** 
 * @brief Computes sin(a) using Taylor series.
 * @note Assumes |a| <= pi/2048.
 *
 * @author Taken from libQD qd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
static Float64x4 sin_taylor(const Float64x4& a) {
	const fp64 thresh = 0.5 * std::numeric_limits<Float64x4>::epsilon().val[0] * std::fabs(a.val[0]);
	Float64x4 p, s, t, x;

	if (dekker_equal_zero(a)) {
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
	} while (i < (sizeof(inv_fact_odd) / sizeof(inv_fact_odd[0])) && std::fabs(t.val[0]) > thresh);

	return s;
}

/** 
 * @brief Computes cos(a) using Taylor series.
 * @note Assumes |a| <= pi/2048.
 *
 * @author Taken from libQD qd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
static Float64x4 cos_taylor(const Float64x4& a) {
	const fp64 thresh = 0.5 * std::numeric_limits<Float64x4>::epsilon().val[0];
	Float64x4 p, s, t, x;

	if (dekker_equal_zero(a)) {
		return 1.0;
	}

	x = -square(a);
	s = 1.0 + mul_pwr2(x, 0.5);
	p = x;
	size_t i = 0;
	do {
		p *= x;
		t = p * inv_fact_even[i];
		s += t;
		++i;
	} while (i < (sizeof(inv_fact_odd) / sizeof(inv_fact_odd[0])) && std::fabs(t.val[0]) > thresh);

	return s;
}


/** 
 * @author Taken from libQD qd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float64x4 sin(const Float64x4& a) {

	/* Strategy.  To compute sin(x), we choose integers a, b so that

			 x = s + a * (pi/2) + b * (pi/1024)

		 and |s| <= pi/2048.  Using a precomputed table of
		 sin(k pi / 1024) and cos(k pi / 1024), we can compute
		 sin(x) from sin(s) and cos(s).  This greatly increases the
		 convergence of the sine Taylor series.                          */

	if (dekker_equal_zero(a)) {
		return 0.0;
	}

	// approximately reduce modulo 2*pi
	Float64x4 z = round(a / Float64x4_2pi);
	Float64x4 r = a - Float64x4_2pi * z;

	// approximately reduce modulo pi/2 and then modulo pi/1024
	fp64 q = std::floor(r.val[0] / Float64x4_pi2.val[0] + 0.5);
	Float64x4 t = r - Float64x4_pi2 * q;
	int j = static_cast<int>(q);
	q = std::floor(t.val[0] / taylor_pi1024.val[0] + 0.5);
	t -= taylor_pi1024 * q;
	int k = static_cast<int>(q);
	int abs_k = std::abs(k);

	if (j < -2 || j > 2) {
		// qd_real::error("(qd_real::sin): Cannot reduce modulo pi/2.");
		return std::numeric_limits<Float64x4>::quiet_NaN();
	}

	if (abs_k > 256) {
		// qd_real::error("(qd_real::sin): Cannot reduce modulo pi/1024.");
		return std::numeric_limits<Float64x4>::quiet_NaN();
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

	Float64x4 sin_t, cos_t;
	Float64x4 u = cos_table[abs_k-1];
	Float64x4 v = sin_table[abs_k-1];
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
Float64x4 cos(const Float64x4& a) {

	if (dekker_equal_zero(a)) {
		return 1.0;
	}

	// approximately reduce modulo 2*pi
	Float64x4 z = round(a / Float64x4_2pi);
	Float64x4 r = a - Float64x4_2pi * z;

	// approximately reduce modulo pi/2 and then modulo pi/1024
	fp64 q = std::floor(r.val[0] / Float64x4_pi2.val[0] + 0.5);
	Float64x4 t = r - Float64x4_pi2 * q;
	int j = static_cast<int>(q);
	q = std::floor(t.val[0] / taylor_pi1024.val[0] + 0.5);
	t -= taylor_pi1024 * q;
	int k = static_cast<int>(q);
	int abs_k = std::abs(k);

	if (j < -2 || j > 2) {
		// qd_real::error("(qd_real::cos): Cannot reduce modulo pi/2.");
		return std::numeric_limits<Float64x4>::quiet_NaN();
	}

	if (abs_k > 256) {
		// qd_real::error("(qd_real::cos): Cannot reduce modulo pi/1024.");
		return std::numeric_limits<Float64x4>::quiet_NaN();
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

	Float64x4 sin_t, cos_t;
	sincos_taylor(t, sin_t, cos_t);

	Float64x4 u = cos_table[abs_k-1];
	Float64x4 v = sin_table[abs_k-1];

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
void sincos(const Float64x4& a, Float64x4& sin_a, Float64x4& cos_a) {

	if (dekker_equal_zero(a)) {
		sin_a = 0.0;
		cos_a = 1.0;
		return;
	}

	// approximately reduce by 2*pi
	Float64x4 z = round(a / Float64x4_2pi);
	Float64x4 t = a - Float64x4_2pi * z;

	// approximately reduce by pi/2 and then by pi/1024.
	fp64 q = std::floor(t.val[0] / Float64x4_pi2.val[0] + 0.5);
	t -= Float64x4_pi2 * q;
	int j = static_cast<int>(q);
	q = std::floor(t.val[0] / taylor_pi1024.val[0] + 0.5);
	t -= taylor_pi1024 * q;
	int k = static_cast<int>(q);
	int abs_k = std::abs(k);

	if (j < -2 || j > 2) {
		// qd_real::error("(qd_real::sincos): Cannot reduce modulo pi/2.");
		cos_a = sin_a = std::numeric_limits<Float64x4>::quiet_NaN();
		return;
	}

	if (abs_k > 256) {
		// qd_real::error("(qd_real::sincos): Cannot reduce modulo pi/1024.");
		cos_a = sin_a = std::numeric_limits<Float64x4>::quiet_NaN();
		return;
	}

	Float64x4 sin_t, cos_t;
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

	Float64x4 u = cos_table[abs_k-1];
	Float64x4 v = sin_table[abs_k-1];

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

/** 
 * @author Taken from libQD qd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float64x4 atan(const Float64x4& y) {
	if (dekker_equal_zero(y)) {
		return static_cast<fp64>(0.0);
	}

	if (y == static_cast<fp64>(1.0)) {
		return Float64x4_pi4;
	}

	if (y == static_cast<fp64>(-1.0)) {
		return -Float64x4_pi4;
	}

	Float64x4 r = sqrt(static_cast<fp64>(1.0) + square(y));
	Float64x4 xx = recip(r);
	Float64x4 yy = y / r;

	/* Compute double precision approximation to atan. */
	Float64x4 z = std::atan(y.val[0]);
	Float64x4 sin_z, cos_z;

	if (std::fabs(xx.val[0]) > std::fabs(yy.val[0])) {
		/* Use Newton iteration 1.  z' = z + (y - sin(z)) / cos(z)  */
		sincos(z, sin_z, cos_z);
		z += (yy - sin_z) / cos_z;
		sincos(z, sin_z, cos_z);
		z += (yy - sin_z) / cos_z;
		sincos(z, sin_z, cos_z);
		z += (yy - sin_z) / cos_z;
	} else {
		/* Use Newton iteration 2.  z' = z - (x - cos(z)) / sin(z)  */
		sincos(z, sin_z, cos_z);
		z -= (xx - cos_z) / sin_z;
		sincos(z, sin_z, cos_z);
		z -= (xx - cos_z) / sin_z;
		sincos(z, sin_z, cos_z);
		z -= (xx - cos_z) / sin_z;
	}

	return z;
}

/** 
 * @author Taken from libQD qd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float64x4 atan2(const Float64x4& y, const Float64x4& x) {
	/* Strategy: Instead of using Taylor series to compute 
		 arctan, we instead use Newton's iteration to solve
		 the equation

				sin(z) = y/r    or    cos(z) = x/r

		 where r = sqrt(x^2 + y^2).
		 The iteration is given by

				z' = z + (y - sin(z)) / cos(z)          (for equation 1)
				z' = z - (x - cos(z)) / sin(z)          (for equation 2)

		 Here, x and y are normalized so that x^2 + y^2 = 1.
		 If |x| > |y|, then first iteration is used since the 
		 denominator is larger.  Otherwise, the second is used.
	*/

	if (dekker_equal_zero(x)) {
		
		if (dekker_equal_zero(y)) {
			/* Both x and y is zero. */
			// qd_real::error("(qd_real::atan2): Both arguments zero.");
			return std::numeric_limits<Float64x4>::quiet_NaN();
		}

		return (dekker_greater_zero(y)) ? Float64x4_pi2 : -Float64x4_pi2;
	} else if (dekker_equal_zero(y)) {
		return (dekker_greater_zero(x)) ? static_cast<Float64x4>(0.0) : Float64x4_pi;
	}

	if (x == y) {
		return (dekker_greater_zero(y)) ? Float64x4_pi4 : -Float64x4_3pi4;
	}

	if (x == -y) {
		return (dekker_greater_zero(y)) ? Float64x4_3pi4 : -Float64x4_pi4;
	}

	Float64x4 r = sqrt(square(x) + square(y));
	Float64x4 xx = x / r;
	Float64x4 yy = y / r;

	/* Compute double precision approximation to atan. */
	Float64x4 z = std::atan2(y.val[0], x.val[0]);
	Float64x4 sin_z, cos_z;

	if (std::fabs(xx.val[0]) > std::fabs(yy.val[0])) {
		/* Use Newton iteration 1.  z' = z + (y - sin(z)) / cos(z)  */
		sincos(z, sin_z, cos_z);
		z += (yy - sin_z) / cos_z;
		sincos(z, sin_z, cos_z);
		z += (yy - sin_z) / cos_z;
		sincos(z, sin_z, cos_z);
		z += (yy - sin_z) / cos_z;
	} else {
		/* Use Newton iteration 2.  z' = z - (x - cos(z)) / sin(z)  */
		sincos(z, sin_z, cos_z);
		z -= (xx - cos_z) / sin_z;
		sincos(z, sin_z, cos_z);
		z -= (xx - cos_z) / sin_z;
		sincos(z, sin_z, cos_z);
		z -= (xx - cos_z) / sin_z;
	}

	return z;
}

/** 
 * @author Taken from libQD qd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float64x4 asin(const Float64x4& a) {
	Float64x4 abs_a = fabs(a);

	if (abs_a > 1.0) {
		// qd_real::error("(qd_real::asin): Argument out of domain.");
		return std::numeric_limits<Float64x4>::quiet_NaN();
	}

	if (abs_a == 1.0) {
		return (dekker_greater_zero(a)) ? Float64x4_pi2 : -Float64x4_pi2;
	}

	return atan2(a, sqrt(1.0 - square(a)));
}

/** 
 * @author Taken from libQD qd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float64x4 acos(const Float64x4& a) {
	Float64x4 abs_a = fabs(a);

	if (abs_a > 1.0) {
		// qd_real::error("(qd_real::acos): Argument out of domain.");
		return std::numeric_limits<Float64x4>::quiet_NaN();
	}

	if (abs_a == 1.0) {
		return (dekker_greater_zero(a)) ? static_cast<Float64x4>(0.0) : Float64x4_pi;
	}

	return atan2(sqrt(1.0 - square(a)), a);
}

/** 
 * @author Taken from libQD qd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float64x4 sinh(const Float64x4& a) {
	if (dekker_equal_zero(a)) {
		return 0.0;
	}

	if (fabs(a) > 0.05) {
		Float64x4 ea = exp(a);
		return mul_pwr2(ea - recip(ea), 0.5);
	}

	/* Since a is small, using the above formula gives
		 a lot of cancellation.   So use Taylor series. */
	Float64x4 s = a;
	Float64x4 t = a;
	Float64x4 r = square(t);
	fp64 m = 1.0;
	fp64 thresh = std::fabs(a.val[0] * std::numeric_limits<Float64x4>::epsilon().val[0]);

	do {
		m += 2.0;
		t *= r;
		t /= (m-1) * m;

		s += t;
	} while (fabs(t) > thresh);

	return s;
}

/** 
 * @author Taken from libQD qd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float64x4 cosh(const Float64x4& a) {
	if (dekker_equal_zero(a)) {
		return 1.0;
	}

	Float64x4 ea = exp(a);
	return mul_pwr2(ea + recip(ea), 0.5);
}

/** 
 * @author Taken from libQD qd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float64x4 tanh(const Float64x4& x) {
	if (dekker_equal_zero(x)) {
		return static_cast<Float64x4>(0.0);
	}

	if (fabs(x.val[0]) > static_cast<fp64>(0.05)) {
		Float64x4 ex = exp(x);
		Float64x4 recip_ex = recip(ex);
		return (ex - recip_ex) / (ex + recip_ex);
	}
	Float64x4 sinh_val, cosh_val;
	sinh_val = sinh(x);
	cosh_val = sqrt(static_cast<fp64>(1.0) + square(sinh_val));
	return sinh_val / cosh_val;
}

/** 
 * @author Taken from libQD qd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
void sinhcosh(const Float64x4& x, Float64x4& p_sinh, Float64x4& p_cosh) {
	if (fabs(x.val[0]) <= 0.05) {
		p_sinh = sinh(x);
		p_cosh = sqrt(static_cast<fp64>(1.0) + square(x));
	} else {
		Float64x4 ex = exp(x);
		Float64x4 recip_ex = recip(ex);
		p_sinh = mul_pwr2(ex - recip_ex, 0.5);
		p_cosh = mul_pwr2(ex + recip_ex, 0.5);
	}
}

/** 
 * @author Taken from libQD qd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float64x4 asinh(const Float64x4& a) {
	return log(a + sqrt(square(a) + 1.0));
}

/** 
 * @author Taken from libQD qd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float64x4 acosh(const Float64x4& a) {
	if (a < 1.0) {
		// qd_real::error("(qd_real::acosh): Argument out of domain.");
		return std::numeric_limits<Float64x4>::quiet_NaN();
	}

	return log(a + sqrt(square(a) - 1.0));
}

/** 
 * @author Taken from libQD qd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float64x4 atanh(const Float64x4& a) {
	if (fabs(a) >= 1.0) {
		// qd_real::error("(qd_real::atanh): Argument out of domain.");
		return std::numeric_limits<Float64x4>::quiet_NaN();
	}

	return mul_pwr2(log((1.0 + a) / (1.0 - a)), 0.5);
}

//------------------------------------------------------------------------------
// Float64x4 math.h wrapper functions
//------------------------------------------------------------------------------

Float64x4 Float64x4_exp(Float64x4 x) {
	return exp(x);
}
Float64x4 Float64x4_expm1(Float64x4 x) {
	return expm1(x);
}
Float64x4 Float64x4_log(Float64x4 x) {
	return log(x);
}
Float64x4 Float64x4_log1p(Float64x4 x) {
	return log1p(x);
}
Float64x4 Float64x4_sin(Float64x4 x) {
	return sin(x);
}
Float64x4 Float64x4_cos(Float64x4 x) {
	return cos(x);
}
void Float64x4_sincos(Float64x4 theta, Float64x4* p_sin, Float64x4* p_cos) {
	sincos(theta, *p_sin, *p_cos);
}
// tan is inlined
// Float64x4 Float64x4_tan(Float64x4 x) {
// 	return tan(x);
// }
Float64x4 Float64x4_asin(Float64x4 x) {
	return asin(x);
}
Float64x4 Float64x4_acos(Float64x4 x) {
	return acos(x);
}
Float64x4 Float64x4_atan(Float64x4 x) {
	return atan(x);
}
Float64x4 Float64x4_atan2(Float64x4 y, Float64x4 x) {
	return atan2(y, x);
}
Float64x4 Float64x4_sinh(Float64x4 x) {
	return sinh(x);
}
// cosh is inlined
// Float64x4 Float64x4_cosh(Float64x4 x) {
// 	return cosh(x);
// }
Float64x4 Float64x4_tanh(Float64x4 x) {
	return tanh(x);
}
void Float64x4_sinhcosh(Float64x4 theta, Float64x4* p_sinh, Float64x4* p_cosh) {
	sinhcosh(theta, *p_sinh, *p_cosh);
}

//------------------------------------------------------------------------------
// Float64x4 from string
//------------------------------------------------------------------------------

#include "FloatNxN/FloatNxN_stringTo.hpp"

Float64x4 stringTo_Float64x4(const char* nPtr, char** endPtr) {
	internal_FloatNxN_stringTo<Float64x4, fp64> stringTo_func;
	return stringTo_func.stringTo_FloatNxN(nPtr, endPtr);
}

std::istream& operator>>(std::istream& stream, Float64x4& value) {
	internal_FloatNxN_stringTo<Float64x4, fp64> func_cin;
	return func_cin.cin_FloatNxN(stream, value);
}

//------------------------------------------------------------------------------
// Float64x4 to string
//------------------------------------------------------------------------------

#include "FloatNxN/FloatNxN_snprintf.hpp"

int Float64x4_snprintf(char* buf, size_t len, const char* format, ...) {
	va_list args;
	va_start(args, format);
	internal_FloatNxN_snprintf<Float64x4, fp64, 2> func_snprintf;
	int ret_val = func_snprintf.FloatNxN_snprintf(
		PRIFloat64x4, PRIFloat64,
		buf, len, format, args
	);
	va_end(args);
	return ret_val;
}

std::ostream& operator<<(std::ostream& stream, const Float64x4& value) {
	internal_FloatNxN_snprintf<Float64x4, fp64, 2> func_cout;
	return func_cout.FloatNxN_cout(PRIFloat64x4, PRIFloat64, stream, value);
}
