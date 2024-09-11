/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

/*
**	Portions of this file were part of the libQD and libDDFUN library
**
**	libQD is licensed under a modifed BSD license that can be found below:
**	https://www.davidhbailey.com/dhbsoftware/LBNL-BSD-License.docx
**	Or alternatively from this website:
**	https://www.davidhbailey.com/dhbsoftware/
**	A copy of the LBNL-BSD-License can also be found at:
**	LIB-Dekker-Float/libQD/LBNL-BSD-License.txt
**
**	libDDFUN is licensed under a limited BSD license that can be found below:
**	https://www.davidhbailey.com/dhbsoftware/DHB-License.docx
**	Or alternatively from this website:
**	https://www.davidhbailey.com/dhbsoftware/
**	A copy of the Limited-BSD-License can also be found at:
**	LIB-Dekker-Float/libDDFUN/DISCLAIMER_and_Limited-BSD-License.txt
*/

#include <Float80x2/Float80x2.hpp>
#include <limits>
#include <math.h>
#include <cmath>
#include <stdlib.h>
#include <cstdlib>

#include <cassert>

// TEMP //
	#include <cfenv>
	#include <iostream>
// TEMP //

#include "Float64x2_def.h"
#include "Float64x2.h"
#include "Float64x2.hpp"
#include "Float64x2_string.h"

#include "../Float64x4/Float64x4.hpp"

//------------------------------------------------------------------------------
// Float64x2 math.h functions
//------------------------------------------------------------------------------

// static constexpr Float64x2 inv_fact[] = {
// /*  3! */ { 1.66666666666666657e-01,  9.25185853854297066e-18},
// /*  4! */ { 4.16666666666666644e-02,  2.31296463463574266e-18},
// /*  5! */ { 8.33333333333333322e-03,  1.15648231731787138e-19},
// /*  6! */ { 1.38888888888888894e-03, -5.30054395437357706e-20},
// /*  7! */ { 1.98412698412698413e-04,  1.72095582934207053e-22},
// /*  8! */ { 2.48015873015873016e-05,  2.15119478667758816e-23},
// /*  9! */ { 2.75573192239858925e-06, -1.85839327404647208e-22},
// /* 10! */ { 2.75573192239858883e-07,  2.37677146222502973e-23},
// /* 11! */ { 2.50521083854417202e-08, -1.44881407093591197e-24},
// /* 12! */ { 2.08767569878681002e-09, -1.20734505911325997e-25},
// /* 13! */ { 1.60590438368216133e-10,  1.25852945887520981e-26},
// /* 14! */ { 1.14707455977297245e-11,  2.06555127528307454e-28},
// /* 15! */ { 7.64716373181981641e-13,  7.03872877733453001e-30},
// /* 16! */ { 4.77947733238738525e-14,  4.39920548583408126e-31},
// /* 17! */ { 2.81145725434552060e-15,  1.65088427308614326e-31},
// };

/**
 * @remarks The original inv_fact went from 3! to 17!
 */
static constexpr Float64x2 inv_fact[] = {
// /*  0! */ {0x1.0000000000000p+0  ,+0x0.0000000000000p+0  },
// /*  1! */ {0x1.0000000000000p+0  ,+0x0.0000000000000p+0  },
// /*  2! */ {0x1.0000000000000p-1  ,+0x0.0000000000000p+0  },
/*  3! */ {0x1.5555555555555p-3  ,+0x1.5555555555555p-57 },
/*  4! */ {0x1.5555555555555p-5  ,+0x1.5555555555555p-59 },
/*  5! */ {0x1.1111111111111p-7  ,+0x1.1111111111111p-63 },
/*  6! */ {0x1.6c16c16c16c17p-10 ,-0x1.f49f49f49f49fp-65 },
/*  7! */ {0x1.a01a01a01a01ap-13 ,+0x1.a01a01a01a01ap-73 },
/*  8! */ {0x1.a01a01a01a01ap-16 ,+0x1.a01a01a01a01ap-76 },
/*  9! */ {0x1.71de3a556c734p-19 ,-0x1.c154f8ddc6c00p-73 },
/* 10! */ {0x1.27e4fb7789f5cp-22 ,+0x1.cbbc05b4fa99ap-76 },
/* 11! */ {0x1.ae64567f544e4p-26 ,-0x1.c062e06d1f209p-80 },
/* 12! */ {0x1.1eed8eff8d898p-29 ,-0x1.2aec959e14c06p-83 },
/* 13! */ {0x1.6124613a86d09p-33 ,+0x1.f28e0cc748ebep-87 },
/* 14! */ {0x1.93974a8c07c9dp-37 ,+0x1.05d6f8a2efd1fp-92 },
/* 15! */ {0x1.ae7f3e733b81fp-41 ,+0x1.1d8656b0ee8cbp-97 },
/* 16! */ {0x1.ae7f3e733b81fp-45 ,+0x1.1d8656b0ee8cbp-101},
/* 17! */ {0x1.952c77030ad4ap-49 ,+0x1.ac981465ddc6cp-103},
/* 18! */ {0x1.6827863b97d97p-53 ,+0x1.eec01221a8b0bp-107},
/* 19! */ {0x1.2f49b46814157p-57 ,+0x1.2650f61dbdcb4p-112},
/* 20! */ {0x1.e542ba4020225p-62 ,+0x1.ea72b4afe3c2fp-120},
/* 21! */ {0x1.71b8ef6dcf572p-66 ,-0x1.d043ae40c4647p-120},
/* 22! */ {0x1.0ce396db7f853p-70 ,-0x1.aebcdbd20331cp-124},
/* 23! */ {0x1.761b41316381ap-75 ,-0x1.3423c7d91404fp-130},
/* 24! */ {0x1.f2cf01972f578p-80 ,-0x1.9ada5fcc1ab14p-135},
/* 25! */ {0x1.3f3ccdd165fa9p-84 ,-0x1.58ddadf344487p-139},
/* 26! */ {0x1.88e85fc6a4e5ap-89 ,-0x1.71c37ebd16540p-143},
/* 27! */ {0x1.d1ab1c2dccea3p-94 ,+0x1.054d0c78aea14p-149},
/* 28! */ {0x1.0a18a2635085dp-98 ,+0x1.b9e2e28e1aa54p-153},
/* 29! */ {0x1.259f98b4358adp-103,+0x1.eaf8c39dd9bc5p-157},
/* 30! */ {0x1.3932c5047d60ep-108,+0x1.832b7b530a627p-162},
/* 31! */ {0x1.434d2e783f5bcp-113,+0x1.0b87b91be9affp-167},
/* 32! */ {0x1.434d2e783f5bcp-118,+0x1.0b87b91be9affp-172},
/* 33! */ {0x1.3981254dd0d52p-123,-0x1.2b1f4c8015a2fp-177},
/* 34! */ {0x1.2710231c0fd7ap-128,+0x1.3f8a2b4af9d6bp-184},
/* 35! */ {0x1.0dc59c716d91fp-133,+0x1.419e3fad3f031p-188},
/* 36! */ {0x1.df983290c2ca9p-139,+0x1.5835c6895393bp-194},
/* 37! */ {0x1.9ec8d1c94e85bp-144,-0x1.670e9d4784ec6p-201},
/* 38! */ {0x1.5d4acb9c0c3abp-149,-0x1.6ec2c8f5b13b2p-205},
/* 39! */ {0x1.1e99449a4bacep-154,-0x1.fefbb89514b3cp-210},
/* 40! */ {0x1.ca8ed42a12ae3p-160,+0x1.a07244abad2abp-224},
/* 41! */ {0x1.65e61c39d0241p-165,-0x1.c0ed181727269p-220},
/* 42! */ {0x1.10af527530de8p-170,+0x1.b626c912ee5c8p-225},
/* 43! */ {0x1.95db45257e512p-176,+0x1.6e5d72b6f79b9p-231},
/* 44! */ {0x1.272b1b03fec6ap-181,+0x1.3f67cc9f9fdb8p-235},
/* 45! */ {0x1.a3cb872220648p-187,-0x1.c7f4e85b8e6cdp-241},
/* 46! */ {0x1.240804f659510p-192,+0x1.8b291b93c9718p-246},
/* 47! */ {0x1.8da8e0a127ebap-198,-0x1.21d2eac9d275cp-252},
/* 48! */ {0x1.091b406b6ff26p-203,+0x1.e973637973b18p-257},
/* 49! */ {0x1.5a42f0dfeb086p-209,-0x1.35ae015f78f6ep-264},
/* 50! */ {0x1.bb36f6e12cd78p-215,+0x1.02f85029a29b0p-270}
};
static constexpr size_t n_inv_fact = sizeof(inv_fact) / sizeof(inv_fact[0]);

static constexpr Float64x2 inv_fact_even[] = {
// /*  0! */ {0x1.0000000000000p+0  ,+0x0.0000000000000p+0  },
// /*  2! */ {0x1.0000000000000p-1  ,+0x0.0000000000000p+0  },
/*  4! */ {0x1.5555555555555p-5  ,+0x1.5555555555555p-59 },
/*  6! */ {0x1.6c16c16c16c17p-10 ,-0x1.f49f49f49f49fp-65 },
/*  8! */ {0x1.a01a01a01a01ap-16 ,+0x1.a01a01a01a01ap-76 },
/* 10! */ {0x1.27e4fb7789f5cp-22 ,+0x1.cbbc05b4fa99ap-76 },
/* 12! */ {0x1.1eed8eff8d898p-29 ,-0x1.2aec959e14c06p-83 },
/* 14! */ {0x1.93974a8c07c9dp-37 ,+0x1.05d6f8a2efd1fp-92 },
/* 16! */ {0x1.ae7f3e733b81fp-45 ,+0x1.1d8656b0ee8cbp-101},
/* 18! */ {0x1.6827863b97d97p-53 ,+0x1.eec01221a8b0bp-107},
/* 20! */ {0x1.e542ba4020225p-62 ,+0x1.ea72b4afe3c2fp-120},
/* 22! */ {0x1.0ce396db7f853p-70 ,-0x1.aebcdbd20331cp-124},
/* 24! */ {0x1.f2cf01972f578p-80 ,-0x1.9ada5fcc1ab14p-135},
/* 26! */ {0x1.88e85fc6a4e5ap-89 ,-0x1.71c37ebd16540p-143},
/* 28! */ {0x1.0a18a2635085dp-98 ,+0x1.b9e2e28e1aa54p-153},
/* 30! */ {0x1.3932c5047d60ep-108,+0x1.832b7b530a627p-162},
/* 32! */ {0x1.434d2e783f5bcp-118,+0x1.0b87b91be9affp-172},
/* 34! */ {0x1.2710231c0fd7ap-128,+0x1.3f8a2b4af9d6bp-184},
/* 36! */ {0x1.df983290c2ca9p-139,+0x1.5835c6895393bp-194},
/* 38! */ {0x1.5d4acb9c0c3abp-149,-0x1.6ec2c8f5b13b2p-205},
/* 40! */ {0x1.ca8ed42a12ae3p-160,+0x1.a07244abad2abp-224},
/* 42! */ {0x1.10af527530de8p-170,+0x1.b626c912ee5c8p-225},
/* 44! */ {0x1.272b1b03fec6ap-181,+0x1.3f67cc9f9fdb8p-235},
/* 46! */ {0x1.240804f659510p-192,+0x1.8b291b93c9718p-246},
/* 48! */ {0x1.091b406b6ff26p-203,+0x1.e973637973b18p-257},
/* 50! */ {0x1.bb36f6e12cd78p-215,+0x1.02f85029a29b0p-270}
};
static constexpr size_t n_inv_fact_even = sizeof(inv_fact_even) / sizeof(inv_fact_even[0]);

static constexpr Float64x2 inv_fact_odd[] = {
// /*  1! */ {0x1.0000000000000p+0  ,+0x0.0000000000000p+0  },
/*  3! */ {0x1.5555555555555p-3  ,+0x1.5555555555555p-57 },
/*  5! */ {0x1.1111111111111p-7  ,+0x1.1111111111111p-63 },
/*  7! */ {0x1.a01a01a01a01ap-13 ,+0x1.a01a01a01a01ap-73 },
/*  9! */ {0x1.71de3a556c734p-19 ,-0x1.c154f8ddc6c00p-73 },
/* 11! */ {0x1.ae64567f544e4p-26 ,-0x1.c062e06d1f209p-80 },
/* 13! */ {0x1.6124613a86d09p-33 ,+0x1.f28e0cc748ebep-87 },
/* 15! */ {0x1.ae7f3e733b81fp-41 ,+0x1.1d8656b0ee8cbp-97 },
/* 17! */ {0x1.952c77030ad4ap-49 ,+0x1.ac981465ddc6cp-103},
/* 19! */ {0x1.2f49b46814157p-57 ,+0x1.2650f61dbdcb4p-112},
/* 21! */ {0x1.71b8ef6dcf572p-66 ,-0x1.d043ae40c4647p-120},
/* 23! */ {0x1.761b41316381ap-75 ,-0x1.3423c7d91404fp-130},
/* 25! */ {0x1.3f3ccdd165fa9p-84 ,-0x1.58ddadf344487p-139},
/* 27! */ {0x1.d1ab1c2dccea3p-94 ,+0x1.054d0c78aea14p-149},
/* 29! */ {0x1.259f98b4358adp-103,+0x1.eaf8c39dd9bc5p-157},
/* 31! */ {0x1.434d2e783f5bcp-113,+0x1.0b87b91be9affp-167},
/* 33! */ {0x1.3981254dd0d52p-123,-0x1.2b1f4c8015a2fp-177},
/* 35! */ {0x1.0dc59c716d91fp-133,+0x1.419e3fad3f031p-188},
/* 37! */ {0x1.9ec8d1c94e85bp-144,-0x1.670e9d4784ec6p-201},
/* 39! */ {0x1.1e99449a4bacep-154,-0x1.fefbb89514b3cp-210},
/* 41! */ {0x1.65e61c39d0241p-165,-0x1.c0ed181727269p-220},
/* 43! */ {0x1.95db45257e512p-176,+0x1.6e5d72b6f79b9p-231},
/* 45! */ {0x1.a3cb872220648p-187,-0x1.c7f4e85b8e6cdp-241},
/* 47! */ {0x1.8da8e0a127ebap-198,-0x1.21d2eac9d275cp-252},
/* 49! */ {0x1.5a42f0dfeb086p-209,-0x1.35ae015f78f6ep-264}
};
static constexpr size_t n_inv_fact_odd = sizeof(inv_fact_odd) / sizeof(inv_fact_odd[0]);

/** 
 * @brief Exponential.  Computes exp(x) in double-double precision.
 *
 * @author Taken from libQD dd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 *
 * @remarks This was originally the exp(x) function itself. I realized that
 * this function is able to properly calculate expm1(x) when x is between
 * -0.5ln(2) and +0.5ln(2). So the function has been modified so it can be used
 * by both the exp(x) and the expm1(x) function.
 */
static inline Float64x2 taylor_expm1(const Float64x2& x, fp64& m) {
	/* Strategy:  We first reduce the size of x by noting that
		
			exp(kr + m * log(2)) = 2^m * exp(r)^k

		where m and k are integers.  By choosing m appropriately
		we can make |kr| <= log(2) / 2 = 0.347.  Then exp(r) is 
		evaluated using the familiar Taylor series.  Reducing the 
		argument substantially speeds up the convergence.       */  

	constexpr fp64 k = 512.0;
	constexpr fp64 inv_k = 1.0 / k;

	m = floor(x.hi * Float64x2_log2e.hi + 0.5);
	Float64x2 r = mul_pwr2(x - Float64x2_ln2 * m, inv_k);
	Float64x2 s, t, p;
	const fp64 thresh = inv_k * std::numeric_limits<Float64x2>::epsilon().hi;

	p = square(r);
	s = r + mul_pwr2(p, 0.5);
	p *= r;
	t = p * inv_fact[0];
	size_t i = 0;
	// Originally set to `i < 5`, adding another term will sometimes improve precision.
	do {
		s += t;
		p *= r;
		++i;
		t = p * inv_fact[i];
	} while (fabs(t.hi) > thresh && (i < 6 && i < n_inv_fact));

	s += t;

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
	// Original return code:
	// s += 1.0;
	// return ldexp(s, static_cast<int>(m));
}

Float64x2 exp(const Float64x2& x) {
	if (x.hi <= -709.79) {
		// Gives a better approximation near extreme values
		return exp(x.hi);
	}
	/* ln(2^1023 * (1 + (1 - 2^-52)))) = ~709.782712893 */
	if (x.hi >= 709.79) {
		return std::numeric_limits<Float64x2>::infinity();
	}
	if (isequal_zero(x)) {
		return static_cast<Float64x2>(1.0);
	}
	if (x == 1.0) {
		return Float64x2_e;
	}

	fp64 m;
	Float64x2 ret = taylor_expm1(x, m);
	ret += 1.0;
	return ldexp(ret, static_cast<int>(m));
}

Float64x2 expm1(const Float64x2& x) {
	if (x.hi <= -709.79) {
		return static_cast<Float64x2>(-1.0);
	}
	if (x.hi >= 709.79) {
		return std::numeric_limits<Float64x2>::infinity();
	}
	if (isequal_zero(x)) {
		return static_cast<Float64x2>(0.0);
	}
	fp64 m;
	Float64x2 ret = taylor_expm1(x, m);
	/**
	 * @remarks Float64x2_ln2.hi is less than Float64x2_ln2. If this were not the
	 * case, then one would have to compare against
	 * nextafter(Float64x2_ln2.hi, 0.0) to ensure the function behaves
	 * correctly when `x` is very close to `ln2`.
	 *
	 * Although it still uses nextafter just to be safe and avoid pontential
	 * rounding errors.
	 */
	if (fabs(x.hi) < static_cast<fp64>(0.5) * std::nextafter(Float64x2_ln2.hi, 0.0)) {
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
 * @author Taken from libQD dd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float64x2 log(const Float64x2& x) {
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

	if (x == static_cast<fp64>(1.0)) {
		return 0.0;
	}

	if (x.hi <= 0.0) {
		if (x == 0.0) {
			return -std::numeric_limits<Float64x2>::infinity();
		}
		// Float64x2::error("(Float64x2::log): Non-positive argument.");
		return std::numeric_limits<Float64x2>::quiet_NaN();
	}

	Float64x2 guess = log(x.hi);   /* Initial approximation */
	return guess.hi + x * exp(-guess) - 1.0;
}

/**
 * @remarks using similar methods to log(x). Haven't figured out how to
 * properly implement log1p without resorting to Float64x4
 */
Float64x2 log1p(const Float64x2& x) {
	if (isequal_zero(x)) {
		return 0.0;
	}
	if (x <= -1.0) {
		if (x == -1.0) {
			return -std::numeric_limits<Float64x2>::infinity();
		}
		// Float64x2::error("(Float64x2::log): Non-positive argument.");
		return std::numeric_limits<Float64x2>::quiet_NaN();
	}
	Float64x4 guess = log1p(x.hi);
	Float64x4 x_plus1 = LDF::add<Float64x4, Float64x2, fp64>(x, 1.0); 
	return guess.val[0] + static_cast<Float64x2>(x_plus1 * exp(-guess) - 1.0);
}


/* Table of sin(k * pi/16) and cos(k * pi/16). */
static constexpr Float64x2 sin_table [4] = {
	{1.950903220161282758e-01, -7.991079068461731263e-18},
	{3.826834323650897818e-01, -1.005077269646158761e-17},
	{5.555702330196021776e-01, +4.709410940561676821e-17},
	{7.071067811865475727e-01, -4.833646656726456726e-17}
};

static constexpr Float64x2 cos_table [4] = {
	{9.807852804032304306e-01, +1.854693999782500573e-17},
	{9.238795325112867385e-01, +1.764504708433667706e-17},
	{8.314696123025452357e-01, +1.407385698472802389e-18},
	{7.071067811865475727e-01, -4.833646656726456726e-17}
};

/** 
 * @brief Computes sin(a) using Taylor series.
 * @note Assumes |a| <= pi/32.
 *
 * @author Taken from libQD dd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
static Float64x2 sin_taylor(const Float64x2& x) {
	const fp64 thresh = 0.5 * fabs(x.hi) * std::numeric_limits<Float64x2>::epsilon().hi;
	Float64x2 x_power, sum, term;

	if (isequal_zero(x)) {
		return 0.0;
	}

	size_t i = 0;
	const Float64x2 neg_x_squared = -square(x);
	x_power = x;

	// sum = x;
	sum = 0.0;
	do {
		x_power *= neg_x_squared;
		term = x_power * inv_fact_odd[i];
		sum += term;
		++i;
	} while (i < n_inv_fact_odd && fabs(term.hi) > thresh);

	// return sum;
	/**
	 * @remarks Adding x towards the end improves the ULP slightly
	 */
	return sum + x;
}

/** 
 * @brief Computes cos(a) using Taylor series.
 * @note Assumes |a| <= pi/32.
 *
 * @author Taken from libQD dd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
static Float64x2 cos_taylor(const Float64x2 &x) {
	const fp64 thresh = 0.5 * std::numeric_limits<Float64x2>::epsilon().hi;
	Float64x2 x_power, sum, term;

	if (isequal_zero(x)) {
		return 1.0;
	}

	const Float64x2 neg_x_squared = -square(x);
	x_power = neg_x_squared;

	// sum = static_cast<fp64>(1.0) + mul_pwr2(x_power, 0.5);
	sum = 0.0;

	size_t i = 0;
	do {
		x_power *= neg_x_squared;
		term = x_power * inv_fact_even[i];
		sum += term;
		++i;
	} while (i < n_inv_fact_even && fabs(term.hi) > thresh);

	// return sum;
	/**
	 * @remarks Adding the first two terms towards the end improves the ULP slightly
	 */
	return (sum + mul_pwr2(neg_x_squared, 0.5)) + static_cast<fp64>(1.0);
}

/** 
 * @brief Computes sin(a) and cos(a) using Taylor series.
 * @note Assumes |a| <= pi/32.
 *
 * @author Taken from libQD dd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
static void sincos_taylor(
	const Float64x2 &a, Float64x2 &p_sin, Float64x2 &p_cos
) {
	if (isequal_zero(a)) {
		p_sin = 0.0;
		p_cos = 1.0;
		return;
	}

	p_sin = sin_taylor(a);
	p_cos = sqrt(static_cast<fp64>(1.0) - square(p_sin));
}

static constexpr Float64x4 Float64x4_pi16 = {0x1.921fb54442d18p-3,+0x1.1a62633145c07p-57,-0x1.f1976b7ed8fbcp-113,+0x1.4cf98e804177dp-167};

static inline void trig_modulo(
	const Float64x2& x, Float64x2& ret, Float64x2& t,
	int& j, int& k
) {
	#if 0
		// approximately reduce modulo 2*pi
		Float64x2 z = round(x / Float64x2_2pi);
		ret = (x - Float64x2_2pi * z);

		// approximately reduce modulo pi/2 and then modulo pi/16.
		fp64 q = floor(ret.hi / Float64x2_pi2.hi + 0.5);
		t = ret - Float64x2_pi2 * q;
		j = static_cast<int>(q);
		q = floor(t.hi / Float64x2_pi16.hi + 0.5);
		t -= Float64x2_pi16 * q;
		k = static_cast<int>(q);
	#elif 0
		// approximately reduce modulo 2*pi
		Float64x4 z = round(x / Float64x4_2pi);
		ret = static_cast<Float64x2>(x - Float64x4_2pi * z);

		// approximately reduce modulo pi/2 and then modulo pi/16.
		fp64 q = floor(ret.hi / Float64x2_pi2.hi + 0.5);
		t = ret - Float64x2_pi2 * q;
		j = static_cast<int>(q);
		q = floor(t.hi / Float64x2_pi16.hi + 0.5);
		t -= Float64x2_pi16 * q;
		k = static_cast<int>(q);
	#elif 0
		// approximately reduce modulo 2*pi
		Float64x4 z = round(x / Float64x4_2pi);
		ret = static_cast<Float64x2>(x - Float64x4_2pi * z);

		// approximately reduce modulo pi/2 and then modulo pi/16.
		Float64x2 q = floor(ret / Float64x2_pi2 + 0.5);
		t = ret - Float64x2_pi2 * q;
		j = static_cast<int>(q);
		q = floor(t / Float64x2_pi16 + 0.5);
		t -= Float64x2_pi16 * q;
		k = static_cast<int>(q);
	#else
		// approximately reduce modulo 2*pi
		Float64x4 z = round(x / Float64x4_2pi);
		Float64x4 ret_temp = x - Float64x4_2pi * z;
		
		// approximately reduce modulo pi/2 and then modulo pi/16.
		Float64x4 q = floor(ret_temp / Float64x4_pi2 + 0.5);
		Float64x4 t_temp = ret_temp - Float64x4_pi2 * q;
		j = static_cast<int>(q);
		q = floor(t / Float64x4_pi16 + 0.5);
		t_temp -= Float64x4_pi16 * q;
		k = static_cast<int>(q);
		ret = static_cast<Float64x2>(ret_temp);
		t = static_cast<Float64x2>(t_temp);
	#endif
}

/** 
 * @author Taken from libQD dd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float64x2 sin(const Float64x2& x) {  

	/* Strategy.  To compute sin(x), we choose integers a, b so that

		x = s + a * (pi/2) + b * (pi/16)

		and |s| <= pi/32.  Using the fact that 

		sin(pi/16) = 0.5 * sqrt(2 - sqrt(2 + sqrt(2)))

		we can compute sin(x) from sin(s), cos(s).  This greatly 
		increases the convergence of the sine Taylor series. */

	if (isequal_zero(x)) {
		return 0.0;
	}

	Float64x2 ret, t;
	int j, k;
	trig_modulo(x, ret, t, j, k);
	unsigned int abs_k = static_cast<unsigned int>(abs(k));

	if (j < -2 || j > 2) {
		// Float64x2::error("(Float64x2::sin): Cannot reduce modulo pi/2.");
		// printf("ERROR: %+#.10Lg Cannot reduce modulo pi/2.\n", static_cast<long double>(x));
		return std::numeric_limits<Float64x2>::quiet_NaN();
	}

	if (abs_k > 4) {
		// Float64x2::error("(Float64x2::sin): Cannot reduce modulo pi/16.");
		// printf("ERROR: %+#.10Lg Cannot reduce modulo pi/16.\n", static_cast<long double>(x));
		return std::numeric_limits<Float64x2>::quiet_NaN();
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

	Float64x2 u(cos_table[abs_k-1].hi, cos_table[abs_k-1].lo);
	Float64x2 v(sin_table[abs_k-1].hi, sin_table[abs_k-1].lo);
	Float64x2 t_sin, t_cos;
	sincos_taylor(t, t_sin, t_cos);

	if (j == 0) {
		if (k > 0) {
			ret = u * t_sin + v * t_cos;
		} else {
			ret = u * t_sin - v * t_cos;
		}
	} else if (j == 1) {
		if (k > 0) {
			ret = u * t_cos - v * t_sin;
		} else {
			ret = u * t_cos + v * t_sin;
		}
	} else if (j == -1) {
		if (k > 0) {
			ret = v * t_sin - u * t_cos;
		} else if (k < 0) {
			ret = -u * t_cos - v * t_sin;
		}
	} else {
		if (k > 0) {
			ret = -u * t_sin - v * t_cos;
		} else {
			ret = v * t_cos - u * t_sin;
		}
	}
	return ret;
}

/** 
 * @author Taken from libQD dd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float64x2 cos(const Float64x2& x) {

	if (isequal_zero(x)) {
		return 1.0;
	}

	Float64x2 ret, t;
	int j, k;
	trig_modulo(x, ret, t, j, k);
	unsigned int abs_k = static_cast<unsigned int>(abs(k));

	if (j < -2 || j > 2) {
		// Float64x2::error("(Float64x2::cos): Cannot reduce modulo pi/2.");
		// printf("ERROR: %+#.10Lg Cannot reduce modulo pi/2.\n", static_cast<long double>(x));
		return std::numeric_limits<Float64x2>::quiet_NaN();
	}

	if (abs_k > 4) {
		// Float64x2::error("(Float64x2::cos): Cannot reduce modulo pi/16.");
		// printf("ERROR: %+#.10Lg Cannot reduce modulo pi/16.\n", static_cast<long double>(x));
		return std::numeric_limits<Float64x2>::quiet_NaN();
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

	Float64x2 t_sin, t_cos;
	sincos_taylor(t, t_sin, t_cos);
	Float64x2 u(cos_table[abs_k-1].hi, cos_table[abs_k-1].lo);
	Float64x2 v(sin_table[abs_k-1].hi, sin_table[abs_k-1].lo);

	if (j == 0) {
		if (k > 0) {
			ret = u * t_cos - v * t_sin;
		} else {
			ret = u * t_cos + v * t_sin;
		}
	} else if (j == 1) {
		if (k > 0) {
			ret = - u * t_sin - v * t_cos;
		} else {
			ret = v * t_cos - u * t_sin;
		}
	} else if (j == -1) {
		if (k > 0) {
			ret = u * t_sin + v * t_cos;
		} else {
			ret = u * t_sin - v * t_cos;
		}
	} else {
		if (k > 0) {
			ret = v * t_sin - u * t_cos;
		} else {
			ret = - u * t_cos - v * t_sin;
		}
	}

	return ret;
}

/** 
 * @author Taken from libQD dd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
void sincos(const Float64x2& x, Float64x2& p_sin, Float64x2& p_cos) {

	if (isequal_zero(x)) {
		p_sin = static_cast<fp64>(0.0);
		p_cos = static_cast<fp64>(1.0);
		return;
	}

	Float64x2 ret, t;
	int j, k;
	trig_modulo(x, ret, t, j, k);
	unsigned int abs_k = static_cast<unsigned int>(abs(k));
	unsigned int abs_j = static_cast<unsigned int>(abs(j));

	if (abs_j > 2) {
		// Float64x2::error("(Float64x2::sincos): Cannot reduce modulo pi/2.");
		p_cos = std::numeric_limits<Float64x2>::quiet_NaN();
		p_sin = std::numeric_limits<Float64x2>::quiet_NaN();
		return;
	}

	if (abs_k > 4) {
		// Float64x2::error("(Float64x2::sincos): Cannot reduce modulo pi/16.");
		p_cos = std::numeric_limits<Float64x2>::quiet_NaN();
		p_sin = std::numeric_limits<Float64x2>::quiet_NaN();
		return;
	}

	Float64x2 t_sin, t_cos;
	Float64x2 sin_val, cos_val;

	sincos_taylor(t, t_sin, t_cos);

	if (abs_k == 0) {
		sin_val = t_sin;
		cos_val = t_cos;
	} else {
		Float64x2 u(cos_table[abs_k-1].hi, cos_table[abs_k-1].lo);
		Float64x2 v(sin_table[abs_k-1].hi, sin_table[abs_k-1].lo);
		if (k > 0) {
			sin_val = u * t_sin + v * t_cos;
			cos_val = u * t_cos - v * t_sin;
		} else {
			sin_val = u * t_sin - v * t_cos;
			cos_val = u * t_cos + v * t_sin;
		}
	}

	if (abs_j == 0) {
		p_sin = sin_val;
		p_cos = cos_val;
	} else if (j == 1) {
		p_sin = cos_val;
		p_cos = -sin_val;
	} else if (j == -1) {
		p_sin = -cos_val;
		p_cos = sin_val;
	} else {
		p_sin = -sin_val;
		p_cos = -cos_val;
	}
}

/** 
 * @author Taken from libQD dd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float64x2 atan(const Float64x2& y) {
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

	if (isequal_zero(y)) {
		return static_cast<fp64>(0.0);
	}

	if (y == static_cast<fp64>(1.0)) {
		return Float64x2_pi4;
	}

	if (y == static_cast<fp64>(-1.0)) {
		return -Float64x2_pi4;
	}

	Float64x2 r = sqrt(static_cast<fp64>(1.0) + square(y));
	Float64x2 xx = recip(r);
	Float64x2 yy = y / r;

	/* Compute double precision approximation to atan. */
	Float64x2 z = atan(y.hi);
	Float64x2 sin_z, cos_z;

	if (fabs(xx.hi) > fabs(yy.hi)) {
		/* Use Newton iteration 1.  z' = z + (y - sin(z)) / cos(z)  */
		sincos(z, sin_z, cos_z);
		z += (yy - sin_z) / cos_z;
	} else {
		/* Use Newton iteration 2.  z' = z - (x - cos(z)) / sin(z)  */
		sincos(z, sin_z, cos_z);
		z -= (xx - cos_z) / sin_z;
	}

	return z;
}

/** 
 * @author Taken from libQD dd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float64x2 atan2(const Float64x2& y, const Float64x2& x) {
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

	if (isequal_zero(x)) {
	
		if (isequal_zero(y)) {
			// /* Both x and y is zero. */
			// Float64x2::error("(Float64x2::atan2): Both arguments zero.");
			return std::numeric_limits<Float64x2>::quiet_NaN();
		}

		return (isgreater_zero(y)) ? Float64x2_pi2 : -Float64x2_pi2;
	} else if (isequal_zero(y)) {
		return (isgreater_zero(x)) ? Float64x2(0.0) : Float64x2_pi;
	}

	if (x == y) {
		return (isgreater_zero(y)) ? Float64x2_pi4 : -Float64x2_3pi4;
	}

	if (x == -y) {
		return (isgreater_zero(y)) ? Float64x2_3pi4 : -Float64x2_pi4;
	}

	/* Compute double precision approximation to atan. */
	const Float64x2 radius = sqrt(square(x) + square(y));
	Float64x2 z = atan2(y.hi, x.hi);
	Float64x2 sin_z, cos_z;
	sincos(z, sin_z, cos_z);

	if (fabs(x.hi) > fabs(y.hi)) {
		/* Use Newton iteration 1.  z' = z + (y - sin(z)) / cos(z)  */
		z += ((y / radius) - sin_z) / cos_z;
	} else {
		/* Use Newton iteration 2.  z' = z - (x - cos(z)) / sin(z)  */
		z -= ((x / radius) - cos_z) / sin_z;
	}

	return z;
}

/** 
 * @author Taken from libQD dd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float64x2 asin(const Float64x2& x) {
	const Float64x2 abs_x = fabs(x);

	if (abs_x > static_cast<fp64>(1.0)) {
		// Float64x2::error("(Float64x2::asin): Argument out of domain.");
		return std::numeric_limits<Float64x2>::quiet_NaN();
	}

	if (abs_x == static_cast<fp64>(1.0)) {
		return (isgreater_zero(x)) ? Float64x2_pi2 : -Float64x2_pi2;
	}

	return atan2(x, sqrt(static_cast<fp64>(1.0) - square(x)));
}

/** 
 * @author Taken from libQD dd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float64x2 acos(const Float64x2& x) {
	const Float64x2 abs_x = fabs(x);

	if (abs_x > static_cast<fp64>(1.0)) {
		// Float64x2::error("(Float64x2::acos): Argument out of domain.");
		return std::numeric_limits<Float64x2>::quiet_NaN();
	}

	if (abs_x == static_cast<fp64>(1.0)) {
		return (isgreater_zero(x)) ? Float64x2(0.0) : Float64x2_pi;
	}

	return atan2(sqrt(static_cast<fp64>(1.0) - square(x)), x);
}

/** 
 * @author Taken from libQD dd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float64x2 sinh(const Float64x2& x) {
	if (isequal_zero(x)) {
		return static_cast<Float64x2>(0.0);
	}

	if (fabs(x.hi) > static_cast<fp64>(0.05)) {
		Float64x2 ea = exp(x);
		return mul_pwr2((ea - recip(ea)), 0.5);
	}

	/* since x is small, using the above formula gives
		a lot of cancellation.  So use Taylor series.   */
	

	Float64x2 t = x;
	Float64x2 r = square(t);
	const fp64 thresh = fabs(x.hi * std::numeric_limits<Float64x2>::epsilon().hi);

	fp64 m = 3.0;
	t *= r;
	t /= (m - 1.0) * m;

	// Float64x2 s = x + t;
	Float64x2 s = t;

	while (fabs(t.hi) > thresh) {
		m += 2.0;
		t *= r;
		t /= (m - 1.0) * m;

		s += t;
	}

	// return s;
	return s + x; // Adding x towards the end improves the ULP slightly
}

/** 
 * @author Taken from libQD dd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float64x2 cosh(const Float64x2& x) {
	if (isequal_zero(x)) {
		return static_cast<Float64x2>(1.0);
	}

	Float64x2 ex = exp(x);
	return mul_pwr2(ex + recip(ex), 0.5);
}

/** 
 * @author Taken from libQD dd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float64x2 tanh(const Float64x2& x) {
	if (isequal_zero(x)) {
		return static_cast<Float64x2>(0.0);
	}

	if (fabs(x.hi) > static_cast<fp64>(0.05)) {
		Float64x2 ex = exp(x);
		Float64x2 recip_ex = recip(ex);
		return (ex - recip_ex) / (ex + recip_ex);
	}
	Float64x2 sinh_val, cosh_val;
	sinh_val = sinh(x);
	cosh_val = sqrt(static_cast<fp64>(1.0) + square(sinh_val));
	return sinh_val / cosh_val;
}

/** 
 * @author Taken from libQD dd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
void sinhcosh(const Float64x2& x, Float64x2& p_sinh, Float64x2& p_cosh) {
	if (fabs(x.hi) <= 0.05) {
		p_sinh = sinh(x);
		p_cosh = sqrt(static_cast<fp64>(1.0) + square(x));
	} else {
		Float64x2 ex = exp(x);
		Float64x2 recip_ex = recip(ex);
		p_sinh = mul_pwr2(ex - recip_ex, 0.5);
		p_cosh = mul_pwr2(ex + recip_ex, 0.5);
	}
}

/** 
 * @author Taken from libQD dd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float64x2 asinh(const Float64x2& x) {
	return log(x + sqrt(square(x) + static_cast<fp64>(1.0)));
}

/** 
 * @author Taken from libQD dd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float64x2 acosh(const Float64x2& x) {
	if (x < static_cast<fp64>(1.0)) {
		// Float64x2::error("(Float64x2::acosh): Argument out of domain.");
		return std::numeric_limits<Float64x2>::quiet_NaN();
	}

	return log(x + sqrt(square(x) - static_cast<fp64>(1.0)));
}

/** 
 * @author Taken from libQD dd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float64x2 atanh(const Float64x2& x) {
	if (fabs(x) >= static_cast<fp64>(1.0)) {
		// Float64x2::error("(Float64x2::atanh): Argument out of domain.");
		return std::numeric_limits<Float64x2>::quiet_NaN();
	}
	#if 1
		// Value of ~0.472 found experimentally, but set to 0.48 just to be safe
		if (fabs(x) >= static_cast<fp64>(0.48)) {
			// Accurate for larger numbers
			return mul_pwr2(log((static_cast<fp64>(1.0) + x) / (static_cast<fp64>(1.0) - x)), 0.5);

		}
		// Accurate for smaller numbers
		return mul_pwr2(log1p(x) - log1p(-x), 0.5);
	#else
		#if 1
			// Original code
			return mul_pwr2(log((static_cast<fp64>(1.0) + x) / (static_cast<fp64>(1.0) - x)), 0.5);
		#elif 0
			// Removes division
			return mul_pwr2(
				log(x + 1.0) - log(static_cast<fp64>(1.0) - x), 0.5
			);
		#elif 1
			// Uses log1p
			return mul_pwr2(
				log1p(x) - log1p(-x), 0.5
			);
		#else
			// Can be used with log1p in this form: ln(2x / (1 - x) + 1)
			return mul_pwr2(log1p((mul_pwr2(x, static_cast<fp64>(2.0))) / (static_cast<fp64>(1.0) - x)), 0.5);
		#endif
	#endif
}

//------------------------------------------------------------------------------
// Float64x2 pown
//------------------------------------------------------------------------------

__attribute__((unused)) static inline Float64x2 pown(const Float64x2& x, int n) {
	
	if (n == 0) {
		return 1.0;
	}
	if (isequal_zero(x)) {
		return 0.0;
	}

	Float64x2 r = x;
	Float64x2 s = 1.0;
	// casts to unsigned int since abs(INT_MIN) < 0
	unsigned int N = (unsigned int)((n < 0) ? -n : n);

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
		return (1.0 / s);
	}
	return s;
}

#if 1

//------------------------------------------------------------------------------
// Float64x2 libDDFUN/libDQFUN Fortran90 Functions
//------------------------------------------------------------------------------

#elif 0

__attribute__((unused)) static constexpr int dd_knd =  8; /**< Kind parameter for IEEE double floats (usually 8). */
__attribute__((unused)) static constexpr int dd_ldb =  6; /**< Logical device number for output of error messages. */
__attribute__((unused)) static constexpr int dd_nbt = 53; /**< Number of mantissa bits in DP word. */
__attribute__((unused)) static constexpr int dd_nwx =  2; /**< Number of words in DDR datum. */
__attribute__((unused)) static constexpr fp64 dd_dpw  = 15.954589770191003346328161420398; /**< log10(2^53) Approx. number of digits per DP word. */    
__attribute__((unused)) static constexpr fp64 dd_logb = 36.736800569677101399113302437283; /**< log(2^53) Approx. constant needed for zeta routines in ddfune. */
__attribute__((unused)) static constexpr fp64 dd_rdfz = 0x1.0p-50; /**< 2^-50 "Fuzz" for comparing DP values. */
__attribute__((unused)) static constexpr Float64x2 dd_picon = Float64x2_pi; /**< Two-word DDR value of pi. */
__attribute__((unused)) static constexpr Float64x2 dd_egammacon = Float64x2_egamma; /**< Two-word DDR value of Euler's gamma constant. */

// The value of epsilon used for Float64x2 in the Fortran90 libDDFUN routines.
static constexpr fp64 F90_epsilon = 0x1.0p-106;

// The number of doubles in a Float64x2
static constexpr int Float64x2_count = 2;

// static inline void dd_abrt(void) {
// 	printf("dd_arbt\n");
// }

__attribute__((unused)) static inline Float64x2 pown(const Float64x2& x, int n) {
	
	if (n == 0) {
		return 1.0;
	}
	if (isequal_zero(x)) {
		return 0.0;
	}

	Float64x2 r = x;
	Float64x2 s = 1.0;
	// casts to unsigned int since abs(INT_MIN) < 0
	unsigned int N = (unsigned int)((n < 0) ? -n : n);

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
		return (1.0 / s);
	}
	return s;
}

/**
 * @remarks This function computes ldexp(x, n) storing the result
 * as a Float64x2. Although most of the time n is zero, which leads me to
 * believe that this function is just for converting fp64 to Float64x2.
 */
static inline void call_dd_dmc(const fp64 x, const int n, Float64x2& ret) {
	ret.hi = ldexp(x, n);
	ret.lo = 0.0;
}

/** @brief This returns a DP approximation the DDR number A in the form B * 2^n */
static inline void call_dd_mdc(const Float64x2& x, fp64& y, int& n) {
	y = x.hi;
	n = 0;
}

/**
 * @brief Three way comparison <=> possibly?
 */
static inline void call_dd_cpr(const Float64x2& x, const Float64x2& y, int& ret) {
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
 * @brief probably modf
 */
static inline void call_dd_infr(const Float64x2& x, Float64x2& ret_int, Float64x2& ret_frac) {
	//   Sets B to the integer part of the DDR number A and sets C equal to the
	//   fractional part of A. Note that if A = -3.3, then B = -3 and C = -0.3.
	
	// Float64x2, intent(in):: x.lo
	// Float64x2, intent(out):: ret_int.lo, ret_frac.lo
	constexpr fp64 t105 = 0x1.0p+105;
	constexpr fp64 t52  = 0x1.0p+52;
	int ic;
	Float64x2 f, s0, s1;

	// real (ddknd) con(2)
	// save con
	// data con / t105, t52/
	/* static */ Float64x2 con; // I am not sure why con is static
	con = {t105, t52};

	//   Check if  A  is zero.

	if (x.hi == 0.0) {
		ret_int.hi = 0.0;
		ret_int.lo = 0.0;
		ret_frac.hi = 0.0;
		ret_frac.lo = 0.0;
		return;
		// goto JMP_120;
	}

	// if (x.hi >= t105) {
	// 	write (dd_ldb, 1)
	// 	1 format ('*** DDINFR: Argument is too large.')
	// 	call_dd_abrt
	// 	return
	// }

	f.hi = 1.0;
	f.lo = 0.0;
	if (x.hi > 0.0) {
		s0 = x + con;
		ret_int = s0 - con;
		call_dd_cpr(x, ret_int, ic);
		if (ic >= 0) {
			ret_frac = x - ret_int;
		} else {
			s1 = ret_int - f;
			ret_int.hi = s1.hi;
			ret_int.lo = s1.lo;
		}
	} else {
		s0 = x - con;
		ret_int = s0 + con;
		call_dd_cpr(x, ret_int, ic);
		if (ic <= 0) {
			ret_frac = x - ret_int;
		} else {
			s1 = ret_int + f;
			ret_int.hi = s1.hi;
			ret_int.lo = s1.lo;
			ret_frac = x - ret_int;
		}
	}

	// /* label */ JMP_120:
}

static inline void call_dd_infr(const Float64x2& x, Float64x2& ret_int, Float64x2& ret_frac) {
	ret_frac = modf(x, ret_int);
}


static inline int call_dd_int_ldexp(const fp64 x, const int expon) {
	fp64 ret = ldexp(x, expon);
	// printf("int_ldexp: ret(%lf) = ldexp(%lf, %2d)\n", ret, x, expon);
	assert(ret == (fp64)((int)ret)); // check that the conversion is exact.
	return (int)ret;
}

// #define call_dd_sgn(x) x < 0.0 ? -1 : x > 0.0 ? 1 : 0
static inline int call_dd_sgn(const fp64 x) {
	if (x == 0.0) {
		return 0;
	}
	if (x < 0.0) {
		return -1;
	}
	if (x > 0.0) {
		return 1;
	}
	printf("ERROR: call_dd_sgn %#+14.8lg\n", x);
	return 0;
}

#define call_dd_eq(x, ret) ret = x
#define call_dd_neg(x, ret) ret = -x
#define call_dd_abs(x, ret) ret = fabs(x)
#define call_dd_round(x, ret) ret = round(x)
#define call_dd_exp(x, ret) ret = exp(x)
#define call_dd_log(x, ret) ret = log(x)
#define call_dd_sqrt(x, ret) ret = sqrt(x)

#define call_dd_add(x, y, ret) ret = x + y
#define call_dd_sub(x, y, ret) ret = x - y
#define call_dd_mul(x, y, ret) ret = x * y
#define call_dd_div(x, y, ret) ret = x / y

#define call_dd_addd(x, y, ret) ret = x + y
#define call_dd_subd(x, y, ret) ret = x - y
#define call_dd_muld(x, y, ret) ret = x * y
#define call_dd_divd(x, y, ret) ret = x / y

#define call_dd_cssnr(theta, ret_cos, ret_sin) sincos(theta, ret_sin, ret_cos)

/*
 * Couldn't get it to work, integer arguments seem to be off by 2 instead of 1,
 * then any non-integer values seem to be off slightly or return NaN's. The
 * NaN's might originate from division by a denormilized (very small) numbers.
 */

/** 
 * @author Taken from libDDFUN ddfune.f90 which can be found under a
 * Limited-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float64x2 tgamma(const Float64x2& t) {
	feenableexcept(FE_DIVBYZERO);
	//   This evaluates the gamma function, using an algorithm of R. W. Potter.
	//   The argument t must not exceed 10^8 in size (this limit is set below),
	//   must not be zero, and if negative must not be integer.

	//   In the parameter statement below:
	//     max_iter = limit of number of iterations in series; default = 100000.
	//     con1 = 1/2 * log (10) to DP accuracy.
	//     dmax = maximum size of input argument.

	// Float64x2, intent(in):: t
	// Float64x2, intent(out):: z
	Float64x2 z;
	constexpr int max_iter = 1024;
	
	constexpr fp64 dmax = 1.0e+8;
	int i1, ic1, nt, n1, n2, n3;
	fp64 alpha, d1, d2, d3;
	Float64x2 f1, sum1, sum2, tn;
	Float64x2 t1, t2, t3, t4, t5, t6;
	Float64x2 tc1, tc2, tc3;

	// Float64x2 dd_epsilon;

	// int dd_nw, dd_nw1;
	// dd_nw = dd_nwx;
	// dd_nw1 = std::min(dd_nw + 1, dd_nwx);

	// call_dd_dmc(2.0, 0, tc1);
	// dd_epsilon = pown(tc1, -dd_nw1 * dd_nbt);

	call_dd_mdc(t, d1, n1);
	d1 = ldexp(d1, n1);

	// call_dd_round(t, t1);
		t1.hi = round(t.hi);
		t1.lo = round(t.lo);

	call_dd_cpr(t, t1, ic1);
	i1 = call_dd_sgn(t);
	if (i1 == 0 || d1 > dmax || (i1 < 0 && ic1 == 0)) {
		printf("err: i1(%d) ic1(%d) d1(%lf)\n", i1, ic1, d1);
		// write (dd_ldb, 2) dmax
		// 2 format ('*** DDGAMMAR: input argument must have absolute value <=',f10.0,','/ &
		// 'must not be zero, and if negative must not be an integer.')
		// call_dd_abrt
		return std::numeric_limits<Float64x2>::quiet_NaN();
	}

	call_dd_dmc(1.0, 0, f1);

	//   Find the int and fractional parts of t.

	call_dd_infr(t, t2, t3);

	// std::cout << "t: " << t << " t2: " << t2 << " t3: " << t3 << std::endl;

	if (call_dd_sgn(t3) == 0) {
		//   If t is a positive int, then apply the usual factorial recursion.

		call_dd_mdc(t2, d2, n2);
		nt = call_dd_int_ldexp(d2, n2);
		call_dd_eq(f1, t1);

		for(int i = 2; i < nt - 1; i++) {
			call_dd_muld(t1, static_cast<fp64>(i), t2);
			call_dd_eq(t2, t1);
		}

		call_dd_eq(t1, z);
		printf("JMP_POSITIVE_INT\n");
		return z;
	}

	if (call_dd_sgn(t) > 0) {

		//   Apply the identity Gamma[t+1] = t * Gamma[t] to reduce the input argument
		//   to the unit interval.

		call_dd_mdc(t2, d2, n2);
		nt = call_dd_int_ldexp(d2, n2);
		printf("t > 0: %-+#14.8lg\n", ldexp(d2, n2));
		call_dd_eq(f1, t1);
		call_dd_eq(t3, tn);

		for(int i = 1; i < nt; i++) {
			call_dd_dmc(static_cast<fp64>(i), 0, t4);
			call_dd_sub(t, t4, t5);
			call_dd_mul(t1, t5, t6);
			call_dd_eq(t6, t1);
		}

	} else {

		//   Apply the gamma identity to reduce a negative argument to the unit interval.

		call_dd_sub(f1, t, t4);
		call_dd_infr(t4, t3, t5);
		call_dd_mdc(t3, d3, n3);
		nt = call_dd_int_ldexp(d3, n3);
		printf("t < 0: %-+#14.8lg\n", ldexp(d3, n3));
		call_dd_eq(f1, t1);
		call_dd_sub(f1, t5, t2);
		call_dd_eq(t2, tn);

		for(int i = 0; i < nt - 1; i++) {
			call_dd_dmc(static_cast<fp64>(i), 0, t4);
			call_dd_add(t, t4, t5);
			call_dd_div(t1, t5, t6);
			call_dd_eq(t6, t1);
		}
	}

	//   Calculate alpha = bits of precision * log(2) / 2, then take the next even
	//   int value, so that alpha/2 and alpha^2/4 can be calculated exactly in DP.
	// digits = nbt
	// alpha = 2.0 * trunc(0.25 * static_cast<fp64>(dd_nw1 + 1) * std::numeric_limits<fp64>::digits * Float64x2_ln2.hi + 1.0);
	alpha = 2.0 * trunc(0.25 * (dd_nwx + 0) * dd_nbt * 0.69314718055994530942 + 1.0);
	// d2 = ldexp(0.25, static_cast<int>(alpha)); // 0.25e0 * alpha ** 2;
	d2 = 0.25 * alpha * alpha;
	call_dd_eq(tn, t2);
	call_dd_div(f1, t2, t3);
	call_dd_eq(t3, sum1);

	//   Evaluate the series with t.

	for(int j = 1; j < max_iter; j++) {
		call_dd_dmc(static_cast<fp64>(j), 0, t6);
		call_dd_add(t2, t6, t4);
		call_dd_muld(t4, static_cast<fp64>(j), t5);
		call_dd_div(t3, t5, t6);
		call_dd_muld(t6, d2, t3);
		call_dd_add(sum1, t3, t4);
		call_dd_eq(t4, sum1);

		call_dd_abs(t3, tc1);
		call_dd_mul(F90_epsilon, sum1, tc3);
		call_dd_abs(tc3, tc2);
		call_dd_cpr(tc1, tc2, ic1);
		if (ic1 <= 0) {
			printf("JMP_100 %-+#14.8lg\n", sum1.hi);
			goto JMP_100;
		}
	}

	// write (ddldb, 3) 1, max_iter
	// 3 format ('*** DDGAMMAR: iteration limit exceeded',2i10)
	// call_dd_abrt

	/* label */ JMP_100:

	call_dd_neg(tn, t2);
	call_dd_div(f1, t2, t3);
	call_dd_eq(t3, sum2);

	printf("f1: %-+#14.8lg sum2: %-+#14.8lg\n", f1.hi, sum2.hi);

	//   Evaluate the same series with -t.
	printf("t2: %-+#14.8lg t3: %-+#14.8lg\n", t2.hi, t3.hi);
	for(int j = 1; j < max_iter; j++) {
		// printf("%d: %-+#14.8lg\n", j, sum2.hi);
		call_dd_dmc(static_cast<fp64>(j), 0, t6);
		call_dd_add(t2, t6, t4);
		call_dd_muld(t4, static_cast<fp64>(j), t5);
		call_dd_div(t3, t5, t6);
		call_dd_muld(t6, d2, t3);
		call_dd_add(sum2, t3, t4);
		call_dd_eq(t4, sum2);

		call_dd_abs(t3, tc1);
		call_dd_mul(F90_epsilon, sum2, tc3);
		call_dd_abs(tc3, tc2);
		call_dd_cpr(tc1, tc2, ic1);
		if (ic1 <= 0) {
			printf("JMP_110 %-+#14.8lg\n", sum2.hi);
			goto JMP_110;
		}
	}

	// write (ddldb, 3) 2, max_iter
	// call_dd_abrt

	/* label */ JMP_110:

	//   Compute sqrt (pi * sum1 / (tn * sin (pi * tn) * sum2))
	//   and (alpha/2)^tn terms. Also, multiply by the factor t1, from the
	//   If block above.
	// std::cout << "calc: " << sqrt((Float64x2_pi * sum1) / (tn * sin(Float64x2_pi * tn) * sum2)) << std::endl;
	#if 0
		// Original
		call_dd_eq(Float64x2_pi, t2);
		call_dd_mul(t2, tn, t3);
		call_dd_cssnr(t3, t4, t5);
		call_dd_mul(t5, sum2, t6);
		call_dd_mul(tn, t6, t5);
		call_dd_mul(t2, sum1, t3);
		call_dd_div(t3, t5, t6);
		call_dd_neg(t6, t4);
		call_dd_eq(t4, t6);
		call_dd_sqrt(t6, t2);
		call_dd_dmc(0.5 * alpha, 0, t3);
		call_dd_log(t3, t4);
		call_dd_mul(tn, t4, t5);
		call_dd_exp(t5, t6);
		call_dd_mul(t2, t6, t3);
		call_dd_mul(t1, t3, t4);
	#else
		call_dd_cssnr((Float64x2_pi * tn), t4, t5);
		call_dd_mul(t5, sum2, t6);
		call_dd_mul(tn, t6, t5);
		call_dd_div((Float64x2_pi * sum1), t5, t6);
		call_dd_neg(t6, t4);
		call_dd_eq(t4, t6);
		call_dd_sqrt(t6, t2);

		const fp64 half_alpha = 0.5 * alpha;
		t4 = log(static_cast<Float64x2>(half_alpha));

		call_dd_mul(tn, t4, t5);
		call_dd_exp(t5, t6);
		call_dd_mul(t2, t6, t3);
		call_dd_mul(t1, t3, t4);
	#endif

	//   Round to mpnw words precision.

	call_dd_eq(t4, z);

	return z;
}

#endif

//------------------------------------------------------------------------------
// Float64x2 erf and erfc
//------------------------------------------------------------------------------

#include "../FloatNxN/FloatNxN_erf.hpp"

Float64x2 erf(const Float64x2& x) {
	/**
	 * @remarks the lower bound of max_iter for erf seems to be 148. 147 gives
	 * a few results that are accurate to 74bits instead of 108bits or more.
	 * I am not sure why max_iter was set to 10000 initially instead of 1000.
	 * A max_iter of 152 is choosen to cover any missed edge cases, and
	 * because it is a multiple of 4 (Should that help the compiler at all).
	 */
	return libDDFUN_erf<
		Float64x2, fp64, 2,
		256
	>(
		x,
		Float64x2_sqrtpi, Float64x2_ln2.hi,
		std::numeric_limits<Float64x2>::epsilon().hi * 0x1.0p-2
	);
}

Float64x2 erfc(const Float64x2& x) {
	return libDDFUN_erfc<
		Float64x2, fp64, 2,
		256
	>(
		x,
		Float64x2_sqrtpi, Float64x2_ln2.hi,
		std::numeric_limits<Float64x2>::epsilon().hi * 0x1.0p-2
	);
}

//------------------------------------------------------------------------------
// Float64x2 tgamma
//------------------------------------------------------------------------------

#include "../FloatNxN/FloatNxN_tgamma.hpp"

Float64x2 tgamma(const Float64x2& t) {
	return libDQFUN_tgamma<
		Float64x2, fp64, 2,
		100000
	>(
		t,
		Float64x2_pi, Float64x2_ln2.hi
	);
}

//------------------------------------------------------------------------------
// Float64x2 math.h wrapper functions
//------------------------------------------------------------------------------

Float64x2 Float64x2_exp(Float64x2 x) {
	return exp(x);
}
Float64x2 Float64x2_expm1(Float64x2 x) {
	return exp(x);
}
Float64x2 Float64x2_log(Float64x2 x) {
	return log(x);
}
Float64x2 Float64x2_log1p(Float64x2 x) {
	return log1p(x);
}

Float64x2 Float64x2_sin(Float64x2 x) {
	return sin(x);
}
Float64x2 Float64x2_cos(Float64x2 x) {
	return cos(x);
}
void Float64x2_sincos(Float64x2 theta, Float64x2* p_sin, Float64x2* p_cos) {
	sincos(theta, *p_sin, *p_cos);
}
// tan is inlined
// Float64x2 Float64x2_tan(Float64x2 x) {
// 	return tan(x);
// }
Float64x2 Float64x2_asin(Float64x2 x) {
	return asin(x);
}
Float64x2 Float64x2_acos(Float64x2 x) {
	return acos(x);
}
Float64x2 Float64x2_atan(Float64x2 x) {
	return atan(x);
}
Float64x2 Float64x2_atan2(Float64x2 y, Float64x2 x) {
	return atan2(y, x);
}
Float64x2 Float64x2_sinh(Float64x2 x) {
	return sinh(x);
}
// cosh is inlined
// Float64x2 Float64x2_cosh(Float64x2 x) {
// 	return cosh(x);
// }
Float64x2 Float64x2_tanh(Float64x2 x) {
	return tanh(x);
}
void Float64x2_sinhcosh(Float64x2 theta, Float64x2* p_sinh, Float64x2* p_cosh) {
	sinhcosh(theta, *p_sinh, *p_cosh);
}

Float64x2 Float64x2_erf(Float64x2 x) {
	return erf(x);
}
Float64x2 Float64x2_erfc(Float64x2 x) {
	return erfc(x);
}
Float64x2 Float64x2_tgamma(Float64x2 x) {
	return tgamma(x);
}
Float64x2 Float64x2_lgamma(Float64x2 x) {
	return lgamma(x);
}

//------------------------------------------------------------------------------
// Float64x2 from string
//------------------------------------------------------------------------------

#include "../FloatNxN/FloatNxN_stringTo.hpp"

Float64x2 stringTo_Float64x2(const char* nPtr, char** endPtr) {
	internal_FloatNxN_stringTo<Float64x2, fp64> stringTo_func;
	return stringTo_func.stringTo_FloatNxN(nPtr, endPtr);
}

std::istream& operator>>(std::istream& stream, Float64x2& value) {
	internal_FloatNxN_stringTo<Float64x2, fp64> func_cin;
	return func_cin.cin_FloatNxN(stream, value);
}

//------------------------------------------------------------------------------
// Float64x2 to string
//------------------------------------------------------------------------------

#include "../FloatNxN/FloatNxN_snprintf.hpp"

int Float64x2_snprintf(char* buf, size_t len, const char* format, ...) {
	va_list args;
	va_start(args, format);
	internal_FloatNxN_snprintf<Float64x2, fp64, 2> func_snprintf;
	int ret_val = func_snprintf.FloatNxN_snprintf(
		PRIFloat64x2, PRIFloat64,
		buf, len, format, args
	);
	va_end(args);
	return ret_val;
}

std::ostream& operator<<(std::ostream& stream, const Float64x2& value) {
	internal_FloatNxN_snprintf<Float64x2, fp64, 2> func_cout;
	return func_cout.FloatNxN_cout(PRIFloat64x2, PRIFloat64, stream, value);
}
