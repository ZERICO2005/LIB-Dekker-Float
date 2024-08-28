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

#include <limits>
#include <math.h>
#include <cmath>
#include <stdlib.h>
#include <cstdlib>

#include "Float64x2.hpp"
#include "Float64x2_def.h"


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
// /*  0! */ {+0x1.00000000000000p+0  , +0x0.00000000000000p+0  },
// /*  1! */ {+0x1.00000000000000p+0  , +0x0.00000000000000p+0  },
// /*  2! */ {+0x1.00000000000000p-1  , +0x0.00000000000000p+0  },
/*  3! */ {+0x1.55555555555550p-3  , +0x1.55555555555550p-57 },
/*  4! */ {+0x1.55555555555550p-5  , +0x1.55555555555550p-59 },
/*  5! */ {+0x1.11111111111110p-7  , +0x1.11111111111110p-63 },
/*  6! */ {+0x1.6c16c16c16c160p-10 , +0x1.82d82d82d82d80p-63 },
/*  7! */ {+0x1.a01a01a01a01a0p-13 , +0x1.a01a01a01a01a0p-73 },
/*  8! */ {+0x1.a01a01a01a01a0p-16 , +0x1.a01a01a01a01a0p-76 },
/*  9! */ {+0x1.71de3a556c7330p-19 , +0x1.1f5583911ca000p-72 },
/* 10! */ {+0x1.27e4fb7789f5c0p-22 , +0x1.cbbc05b4fa9990p-76 },
/* 11! */ {+0x1.ae64567f544e30p-26 , +0x1.1fce8fc9706fb0p-79 },
/* 12! */ {+0x1.1eed8eff8d8970p-29 , +0x1.6a89b530f59fd0p-82 },
/* 13! */ {+0x1.6124613a86d090p-33 , +0x1.f28e0cc748ebd0p-87 },
/* 14! */ {+0x1.93974a8c07c9d0p-37 , +0x1.05d6f8a2efd1f0p-92 },
/* 15! */ {+0x1.ae7f3e733b81f0p-41 , +0x1.1d8656b0ee8ca0p-97 },
/* 16! */ {+0x1.ae7f3e733b81f0p-45 , +0x1.1d8656b0ee8ca0p-101},
/* 17! */ {+0x1.952c77030ad4a0p-49 , +0x1.ac981465ddc6b0p-103},
/* 18! */ {+0x1.6827863b97d970p-53 , +0x1.eec01221a8b0a0p-107},
/* 19! */ {+0x1.2f49b468141570p-57 , +0x1.2650f61dbdcb30p-112},
/* 20! */ {+0x1.e542ba40202250p-62 , +0x1.ea72b4afe3c2e0p-120},
/* 21! */ {+0x1.71b8ef6dcf5710p-66 , +0x1.17de28df9dcdc0p-119},
/* 22! */ {+0x1.0ce396db7f8520p-70 , +0x1.28a19216fe6710p-123},
/* 23! */ {+0x1.761b4131638190p-75 , +0x1.b2f70e09bafec0p-128},
/* 24! */ {+0x1.f2cf01972f5770p-80 , +0x1.9949680cf953b0p-133},
/* 25! */ {+0x1.3f3ccdd165fa80p-84 , +0x1.a9c894832eede0p-137},
/* 26! */ {+0x1.88e85fc6a4e590p-89 , +0x1.471e40a174d600p-142},
/* 27! */ {+0x1.d1ab1c2dccea30p-94 , +0x1.054d0c78aea130p-149},
/* 28! */ {+0x1.0a18a2635085d0p-98 , +0x1.b9e2e28e1aa540p-153},
/* 29! */ {+0x1.259f98b4358ad0p-103, +0x1.eaf8c39dd9bc40p-157},
/* 30! */ {+0x1.3932c5047d60e0p-108, +0x1.832b7b530a6270p-162},
/* 31! */ {+0x1.434d2e783f5bc0p-113, +0x1.0b87b91be9aff0p-167},
/* 32! */ {+0x1.434d2e783f5bc0p-118, +0x1.0b87b91be9aff0p-172},
/* 33! */ {+0x1.3981254dd0d510p-123, +0x1.6a7059bff52e80p-176},
/* 34! */ {+0x1.2710231c0fd7a0p-128, +0x1.3f8a2b4af9d6b0p-184},
/* 35! */ {+0x1.0dc59c716d91f0p-133, +0x1.419e3fad3f0310p-188},
/* 36! */ {+0x1.df983290c2ca90p-139, +0x1.5835c6895393a0p-194},
/* 37! */ {+0x1.9ec8d1c94e85a0p-144, +0x1.e98f162b87b130p-197},
/* 38! */ {+0x1.5d4acb9c0c3aa0p-149, +0x1.d227a6e149d890p-202},
/* 39! */ {+0x1.1e99449a4bacd0p-154, +0x1.c02088ed5d6980p-207},
/* 40! */ {+0x1.ca8ed42a12ae30p-160, +0x1.a07244abad2ab0p-224},
/* 41! */ {+0x1.65e61c39d02400p-165, +0x1.8fc4b9fa363650p-218},
/* 42! */ {+0x1.10af527530de80p-170, +0x1.b626c912ee5c80p-225},
/* 43! */ {+0x1.95db45257e5120p-176, +0x1.6e5d72b6f79b90p-231},
/* 44! */ {+0x1.272b1b03fec6a0p-181, +0x1.3f67cc9f9fdb70p-235},
/* 45! */ {+0x1.a3cb8722206470p-187, +0x1.1c058bd238c990p-240},
/* 46! */ {+0x1.240804f6595100p-192, +0x1.8b291b93c97180p-246},
/* 47! */ {+0x1.8da8e0a127eb90p-198, +0x1.6f168a9b16c510p-251},
/* 48! */ {+0x1.091b406b6ff260p-203, +0x1.e973637973b170p-257},
/* 49! */ {+0x1.5a42f0dfeb0850p-209, +0x1.b2947fa821c240p-262},
/* 50! */ {+0x1.bb36f6e12cd780p-215, +0x1.02f85029a29b00p-270}
};
static constexpr size_t n_inv_fact = sizeof(inv_fact) / sizeof(inv_fact[0]);

static constexpr Float64x2 inv_fact_even[] = {
// /*  0! */ {+0x1.00000000000000p+0  , +0x0.00000000000000p+0  },
// /*  2! */ {+0x1.00000000000000p-1  , +0x0.00000000000000p+0  },
/*  4! */ {+0x1.55555555555550p-5  , +0x1.55555555555550p-59 },
/*  6! */ {+0x1.6c16c16c16c160p-10 , +0x1.82d82d82d82d80p-63 },
/*  8! */ {+0x1.a01a01a01a01a0p-16 , +0x1.a01a01a01a01a0p-76 },
/* 10! */ {+0x1.27e4fb7789f5c0p-22 , +0x1.cbbc05b4fa9990p-76 },
/* 12! */ {+0x1.1eed8eff8d8970p-29 , +0x1.6a89b530f59fd0p-82 },
/* 14! */ {+0x1.93974a8c07c9d0p-37 , +0x1.05d6f8a2efd1f0p-92 },
/* 16! */ {+0x1.ae7f3e733b81f0p-45 , +0x1.1d8656b0ee8ca0p-101},
/* 18! */ {+0x1.6827863b97d970p-53 , +0x1.eec01221a8b0a0p-107},
/* 20! */ {+0x1.e542ba40202250p-62 , +0x1.ea72b4afe3c2e0p-120},
/* 22! */ {+0x1.0ce396db7f8520p-70 , +0x1.28a19216fe6710p-123},
/* 24! */ {+0x1.f2cf01972f5770p-80 , +0x1.9949680cf953b0p-133},
/* 26! */ {+0x1.88e85fc6a4e590p-89 , +0x1.471e40a174d600p-142},
/* 28! */ {+0x1.0a18a2635085d0p-98 , +0x1.b9e2e28e1aa540p-153},
/* 30! */ {+0x1.3932c5047d60e0p-108, +0x1.832b7b530a6270p-162},
/* 32! */ {+0x1.434d2e783f5bc0p-118, +0x1.0b87b91be9aff0p-172},
/* 34! */ {+0x1.2710231c0fd7a0p-128, +0x1.3f8a2b4af9d6b0p-184},
/* 36! */ {+0x1.df983290c2ca90p-139, +0x1.5835c6895393a0p-194},
/* 38! */ {+0x1.5d4acb9c0c3aa0p-149, +0x1.d227a6e149d890p-202},
/* 40! */ {+0x1.ca8ed42a12ae30p-160, +0x1.a07244abad2ab0p-224},
/* 42! */ {+0x1.10af527530de80p-170, +0x1.b626c912ee5c80p-225},
/* 44! */ {+0x1.272b1b03fec6a0p-181, +0x1.3f67cc9f9fdb70p-235},
/* 46! */ {+0x1.240804f6595100p-192, +0x1.8b291b93c97180p-246},
/* 48! */ {+0x1.091b406b6ff260p-203, +0x1.e973637973b170p-257},
/* 50! */ {+0x1.bb36f6e12cd780p-215, +0x1.02f85029a29b00p-270}
};
static constexpr size_t n_inv_fact_even = sizeof(inv_fact_even) / sizeof(inv_fact_even[0]);

static constexpr Float64x2 inv_fact_odd[] = {
// /*  1! */ {+0x1.00000000000000p+0  , +0x0.00000000000000p+0  },
/*  3! */ {+0x1.55555555555550p-3  , +0x1.55555555555550p-57 },
/*  5! */ {+0x1.11111111111110p-7  , +0x1.11111111111110p-63 },
/*  7! */ {+0x1.a01a01a01a01a0p-13 , +0x1.a01a01a01a01a0p-73 },
/*  9! */ {+0x1.71de3a556c7330p-19 , +0x1.1f5583911ca000p-72 },
/* 11! */ {+0x1.ae64567f544e30p-26 , +0x1.1fce8fc9706fb0p-79 },
/* 13! */ {+0x1.6124613a86d090p-33 , +0x1.f28e0cc748ebd0p-87 },
/* 15! */ {+0x1.ae7f3e733b81f0p-41 , +0x1.1d8656b0ee8ca0p-97 },
/* 17! */ {+0x1.952c77030ad4a0p-49 , +0x1.ac981465ddc6b0p-103},
/* 19! */ {+0x1.2f49b468141570p-57 , +0x1.2650f61dbdcb30p-112},
/* 21! */ {+0x1.71b8ef6dcf5710p-66 , +0x1.17de28df9dcdc0p-119},
/* 23! */ {+0x1.761b4131638190p-75 , +0x1.b2f70e09bafec0p-128},
/* 25! */ {+0x1.3f3ccdd165fa80p-84 , +0x1.a9c894832eede0p-137},
/* 27! */ {+0x1.d1ab1c2dccea30p-94 , +0x1.054d0c78aea130p-149},
/* 29! */ {+0x1.259f98b4358ad0p-103, +0x1.eaf8c39dd9bc40p-157},
/* 31! */ {+0x1.434d2e783f5bc0p-113, +0x1.0b87b91be9aff0p-167},
/* 33! */ {+0x1.3981254dd0d510p-123, +0x1.6a7059bff52e80p-176},
/* 35! */ {+0x1.0dc59c716d91f0p-133, +0x1.419e3fad3f0310p-188},
/* 37! */ {+0x1.9ec8d1c94e85a0p-144, +0x1.e98f162b87b130p-197},
/* 39! */ {+0x1.1e99449a4bacd0p-154, +0x1.c02088ed5d6980p-207},
/* 41! */ {+0x1.65e61c39d02400p-165, +0x1.8fc4b9fa363650p-218},
/* 43! */ {+0x1.95db45257e5120p-176, +0x1.6e5d72b6f79b90p-231},
/* 45! */ {+0x1.a3cb8722206470p-187, +0x1.1c058bd238c990p-240},
/* 47! */ {+0x1.8da8e0a127eb90p-198, +0x1.6f168a9b16c510p-251},
/* 49! */ {+0x1.5a42f0dfeb0850p-209, +0x1.b2947fa821c240p-262},
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

	const fp64 k = 512.0;
	const fp64 inv_k = 1.0 / k;

	if (x.hi <= -709.0) {
		return static_cast<Float64x2>(0.0);
	}

	if (x.hi >= 709.0) {
		return std::numeric_limits<Float64x2>::infinity();
	}

	if (dekker_equal_zero(x)) {
		return static_cast<fp64>(1.0);
	}

	if (dekker_equal_zero(x)) {
		return Float64x2_euler;
	}

	m = floor(x.hi * Float64x2_log2e.hi + 0.5);
	Float64x2 r = mul_pwr2(x - Float64x2_ln2 * m, inv_k);
	Float64x2 s, t, p;

	p = square(r);
	s = r + mul_pwr2(p, 0.5);
	p *= r;
	t = p * inv_fact[0];
	size_t i = 0;
	do {
		s += t;
		p *= r;
		++i;
		t = p * inv_fact[i];
	} while (fabs(t.hi) > inv_k * std::numeric_limits<Float64x2>::epsilon().hi && (i < 5 && i < n_inv_fact));

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
	fp64 m;
	Float64x2 ret = taylor_expm1(x, m);
	ret += 1.0;
	return ldexp(ret, static_cast<int>(m));
}

Float64x2 expm1(const Float64x2& x) {
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
	guess = guess.hi + x * exp(-guess) - 1.0;
	return guess;
}

/**
 * @remarks using similar methods to log(x)
 */
Float64x2 log1p(const Float64x2& x) {
	if (dekker_equal_zero(x)) {
		return 0.0;
	}
	if (x <= -1.0) {
		if (x == -1.0) {
			return -std::numeric_limits<Float64x2>::infinity();
		}
		// Float64x2::error("(Float64x2::log): Non-positive argument.");
		return std::numeric_limits<Float64x2>::quiet_NaN();
	}
	Float64x2 guess = log1p(x.hi);
	guess = guess.hi + (x + 1.0) * exp(-guess) - 1.0;
	return guess;
}


/* Table of sin(k * pi/16) and cos(k * pi/16). */
static constexpr Float64x2 sin_table [4] = {
	{1.950903220161282758e-01, -7.991079068461731263e-18},
	{3.826834323650897818e-01, -1.005077269646158761e-17},
	{5.555702330196021776e-01,  4.709410940561676821e-17},
	{7.071067811865475727e-01, -4.833646656726456726e-17}
};

static constexpr Float64x2 cos_table [4] = {
	{9.807852804032304306e-01,  1.854693999782500573e-17},
	{9.238795325112867385e-01,  1.764504708433667706e-17},
	{8.314696123025452357e-01,  1.407385698472802389e-18},
	{7.071067811865475727e-01, -4.833646656726456726e-17}
};

/** 
 * @brief Computes sin(a) using Taylor series.
 * @note Assumes |a| <= pi/32.
 *
 * @author Taken from libQD dd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
static Float64x2 sin_taylor(const Float64x2 &a) {
	const fp64 thresh = 0.5 * fabs(a.hi) * std::numeric_limits<Float64x2>::epsilon().hi;
	Float64x2 r, s, t, x;

	if (dekker_equal_zero(a)) {
		return 0.0;
	}

	size_t i = 0;
	x = -square(a);
	s = a;
	r = a;
	do {
		r *= x;
		t = r * inv_fact_odd[i];
		s += t;
		++i;
	} while (i < n_inv_fact_odd && fabs(t.hi) > thresh);

	return s;
}

/** 
 * @brief Computes cos(a) using Taylor series.
 * @note Assumes |a| <= pi/32.
 *
 * @author Taken from libQD dd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
static Float64x2 cos_taylor(const Float64x2 &a) {
	const fp64 thresh = 0.5 * std::numeric_limits<Float64x2>::epsilon().hi;
	Float64x2 r, s, t, x;

	if (dekker_equal_zero(a)) {
		return 1.0;
	}

	x = -square(a);
	r = x;
	s = static_cast<fp64>(1.0) + mul_pwr2(r, 0.5);
	size_t i = 0;
	do {
		r *= x;
		t = r * inv_fact_even[i];
		s += t;
		++i;
	} while (i < n_inv_fact_even && fabs(t.hi) > thresh);

	return s;
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
	if (dekker_equal_zero(a)) {
		p_sin = 0.0;
		p_cos = 1.0;
		return;
	}

	p_sin = sin_taylor(a);
	p_cos = sqrt(static_cast<fp64>(1.0) - square(p_sin));
}

#if 0

static inline Float64x2 trig_fmod(Float64x2 x, Float64x2 y) {
	Float64x2 floor_part = floor(x / y);
	return x - (y * floor_part);
}

Float64x2 sin(const Float64x2& x) {
	// printf("\n\t%+-23.14a %+-23.14a\n", x.hi, x.lo);
	Float64x2 comp;
	comp = trig_fmod(x, Float64x2_tau);
	// printf("\t%+-23.14a %+-23.14a\n", comp.hi, comp.lo);
	bool neg_flag = (Float64x2_tau2 <= comp) ? true : false;
	comp = trig_fmod(x, Float64x2_tau2);
	// printf("\t%+-23.14a %+-23.14a\n", comp.hi, comp.lo);
	// comp == static_cast<fp64>(0.0)
	bool flip_side = (
		Float64x2_tau4 <= comp &&
		dekker_notequal_zero(comp)
	) ? true : false;
	x = trig_fmod(x, Float64x2_tau4);
	printf("\t%+-23.14a %+-23.14a\n", x.hi, x.lo);
	flip_side = (
		dekker_notequal_zero(comp)
	) ? flip_side : false;
	x = flip_side ? (Float64x2_tau4 - x) : x;
	Float64x2 ret = x;
	Float64x2 x_pow = x;
	const Float64x2 neg_x_sqr = -square(x);
	size_t i = 0;
	do {
		x_pow *= neg_x_sqr;
		ret += x_pow * inv_fact_odd[i];
		i++;
	} while (i < n_inv_fact_odd && i < 16);
	ret = neg_flag ? -ret : ret;
	return ret;
}

#endif

#if 0

Float64x2 sin(const Float64x2& x) {
	x = fmod(x, Float64x2_tau);
	Float64x2 ret_hi = x;
	Float64x2 ret_lo = 0.0;
	Float64x2 x_pow = x;
	const Float64x2 neg_x_sqr = -square(x);
	
	
	x_pow *= neg_x_sqr;
	ret_hi += x_pow * inv_fact_odd[0];

	x_pow *= neg_x_sqr;
	ret_hi += x_pow * inv_fact_odd[1];
	size_t i = 2;
	do {
		x_pow *= neg_x_sqr;

			ret_lo += x_pow * inv_fact_odd[i];
		
		i++;
	} while (/* i < n_inv_fact && */ i < 16);
	// 32 = 2^-104.1270 max-error
	// 34 = 2^-104.1312 max-error
	return ret_hi + ret_lo;
}

#endif

#if 1

/** 
 * @author Taken from libQD dd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float64x2 sin(const Float64x2& a) {  

	/* Strategy.  To compute sin(x), we choose integers a, b so that

		x = s + a * (pi/2) + b * (pi/16)

		and |s| <= pi/32.  Using the fact that 

		sin(pi/16) = 0.5 * sqrt(2 - sqrt(2 + sqrt(2)))

		we can compute sin(x) from sin(s), cos(s).  This greatly 
		increases the convergence of the sine Taylor series. */

	if (dekker_equal_zero(a)) {
		return 0.0;
	}

	// approximately reduce modulo 2*pi
	Float64x2 z = round(a / Float64x2_2pi);
	Float64x2 r = a - Float64x2_2pi * z;

	// approximately reduce modulo pi/2 and then modulo pi/16.
	Float64x2 t;
	fp64 q = floor(r.hi / Float64x2_pi2.hi + 0.5);
	t = r - Float64x2_pi2 * q;
	int j = static_cast<int>(q);
	q = floor(t.hi / Float64x2_pi16.hi + 0.5);
	t -= Float64x2_pi16 * q;
	int k = static_cast<int>(q);
	int abs_k = abs(k);

	if (j < -2 || j > 2) {
		// Float64x2::error("(Float64x2::sin): Cannot reduce modulo pi/2.");
		return std::numeric_limits<Float64x2>::quiet_NaN();
	}

	if (abs_k > 4) {
		// Float64x2::error("(Float64x2::sin): Cannot reduce modulo pi/16.");
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
			r = u * t_sin + v * t_cos;
		} else {
			r = u * t_sin - v * t_cos;
		}
	} else if (j == 1) {
		if (k > 0) {
			r = u * t_cos - v * t_sin;
		} else {
			r = u * t_cos + v * t_sin;
		}
	} else if (j == -1) {
		if (k > 0) {
			r = v * t_sin - u * t_cos;
		} else if (k < 0) {
			r = -u * t_cos - v * t_sin;
		}
	} else {
		if (k > 0) {
			r = -u * t_sin - v * t_cos;
		} else {
			r = v * t_cos - u * t_sin;
		}
	}
	return r;
}
#endif

/** 
 * @author Taken from libQD dd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float64x2 cos(const Float64x2& a) {

	if (dekker_equal_zero(a)) {
		return 1.0;
	}

	// approximately reduce modulo 2*pi
	Float64x2 z = round(a / Float64x2_2pi);
	Float64x2 ret = a - z * Float64x2_2pi;

	// approximately reduce modulo pi/2 and then modulo pi/16
	Float64x2 t;
	fp64 q = floor(ret.hi / Float64x2_pi2.hi + 0.5);
	t = ret - Float64x2_pi2 * q;
	int j = static_cast<int>(q);
	q = floor(t.hi / Float64x2_pi16.hi + 0.5);
	t -= Float64x2_pi16 * q;
	int k = static_cast<int>(q);
	int abs_k = abs(k);

	if (j < -2 || j > 2) {
		// Float64x2::error("(Float64x2::cos): Cannot reduce modulo pi/2.");
		return std::numeric_limits<Float64x2>::quiet_NaN();
	}

	if (abs_k > 4) {
		// Float64x2::error("(Float64x2::cos): Cannot reduce modulo pi/16.");
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

	if (dekker_equal_zero(x)) {
		p_sin = static_cast<fp64>(0.0);
		p_cos = static_cast<fp64>(1.0);
		return;
	}

	// approximately reduce modulo 2*pi
	Float64x2 z = round(x / Float64x2_2pi);
	Float64x2 ret = x - Float64x2_2pi * z;

	// approximately reduce module pi/2 and pi/16
	Float64x2 t;
	fp64 q = floor(ret.hi / Float64x2_pi2.hi + 0.5);
	t = ret - Float64x2_pi2 * q;
	int j = static_cast<int>(q);
	int abs_j = abs(j);
	q = floor(t.hi / Float64x2_pi16.hi + 0.5);
	t -= Float64x2_pi16 * q;
	int k = static_cast<int>(q);
	int abs_k = abs(k);

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

	if (dekker_equal_zero(y)) {
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

	if (dekker_equal_zero(x)) {
	
		if (dekker_equal_zero(y)) {
			// /* Both x and y is zero. */
			// Float64x2::error("(Float64x2::atan2): Both arguments zero.");
			return std::numeric_limits<Float64x2>::quiet_NaN();
		}

		return (dekker_greater_zero(y)) ? Float64x2_pi2 : -Float64x2_pi2;
	} else if (dekker_equal_zero(y)) {
		return (dekker_greater_zero(x)) ? Float64x2(0.0) : Float64x2_pi;
	}

	if (x == y) {
		return (dekker_greater_zero(y)) ? Float64x2_pi4 : -Float64x2_3pi4;
	}

	if (x == -y) {
		return (dekker_greater_zero(y)) ? Float64x2_3pi4 : -Float64x2_pi4;
	}

	Float64x2 r = sqrt(square(x) + square(y));
	Float64x2 xx = x / r;
	Float64x2 yy = y / r;

	/* Compute double precision approximation to atan. */
	Float64x2 z = atan2(y.hi, x.hi);
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
Float64x2 asin(const Float64x2& a) {
	Float64x2 abs_a = fabs(a);

	if (abs_a > static_cast<fp64>(1.0)) {
		// Float64x2::error("(Float64x2::asin): Argument out of domain.");
		return std::numeric_limits<Float64x2>::quiet_NaN();
	}

	if (abs_a == static_cast<fp64>(1.0)) {
		return (dekker_greater_zero(a)) ? Float64x2_pi2 : -Float64x2_pi2;
	}

	return atan2(a, sqrt(static_cast<fp64>(1.0) - square(a)));
}

/** 
 * @author Taken from libQD dd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float64x2 acos(const Float64x2& a) {
	Float64x2 abs_a = fabs(a);

	if (abs_a > static_cast<fp64>(1.0)) {
		// Float64x2::error("(Float64x2::acos): Argument out of domain.");
		return std::numeric_limits<Float64x2>::quiet_NaN();
	}

	if (abs_a == static_cast<fp64>(1.0)) {
		return (dekker_greater_zero(a)) ? Float64x2(0.0) : Float64x2_pi;
	}

	return atan2(sqrt(static_cast<fp64>(1.0) - square(a)), a);
}

/** 
 * @author Taken from libQD dd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float64x2 sinh(const Float64x2& a) {
	if (dekker_equal_zero(a)) {
		return static_cast<Float64x2>(0.0);
	}

	if (fabs(a.hi) > static_cast<fp64>(0.05)) {
		Float64x2 ea = exp(a);
		return mul_pwr2((ea - recip(ea)), 0.5);
	}

	/* since a is small, using the above formula gives
		a lot of cancellation.  So use Taylor series.   */
	Float64x2 s = a;
	Float64x2 t = a;
	Float64x2 r = square(t);
	fp64 m = 1.0;
	fp64 thresh = fabs(a.hi * std::numeric_limits<Float64x2>::epsilon().hi);

	do {
		m += 2.0;
		t *= r;
		t /= (m - 1.0) * m;

		s += t;
	} while (fabs(t.hi) > thresh);

	return s;

}

/** 
 * @author Taken from libQD dd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float64x2 cosh(const Float64x2& x) {
	if (dekker_equal_zero(x)) {
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
	if (dekker_equal_zero(x)) {
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
Float64x2 asinh(const Float64x2& a) {
	return log(a + sqrt(square(a) + static_cast<fp64>(1.0)));
}

/** 
 * @author Taken from libQD dd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float64x2 acosh(const Float64x2& a) {
	if (a < static_cast<fp64>(1.0)) {
		// Float64x2::error("(Float64x2::acosh): Argument out of domain.");
		return std::numeric_limits<Float64x2>::quiet_NaN();
	}

	return log(a + sqrt(square(a) - static_cast<fp64>(1.0)));
}

/** 
 * @author Taken from libQD dd_real.cpp which can be found under a
 * LBNL-BSD license from https://www.davidhbailey.com/dhbsoftware/
 */
Float64x2 atanh(const Float64x2& a) {
	if (fabs(a) >= static_cast<fp64>(1.0)) {
		// Float64x2::error("(Float64x2::atanh): Argument out of domain.");
		return std::numeric_limits<Float64x2>::quiet_NaN();
	}

	return mul_pwr2(log((static_cast<fp64>(1.0) + a) / (static_cast<fp64>(1.0) - a)), 0.5);
}

//------------------------------------------------------------------------------
// Float64x2 from string
//------------------------------------------------------------------------------

#include "../FloatNx2/FloatNx2_stringTo.hpp"

Float64x2 stringTo_Float64x2(const char* nPtr, char** endPtr) {
	internal_double_FloatN_stringTo<Float64x2, fp64> stringTo_func;
	return stringTo_func.stringTo_FloatNx2(nPtr, endPtr);
}

std::istream& operator>>(std::istream& stream, Float64x2& value) {
	internal_double_FloatN_stringTo<Float64x2, fp64> func_cin;
	return func_cin.cin_FloatNx2(stream, value);
}

//------------------------------------------------------------------------------
// Float64x2 to string
//------------------------------------------------------------------------------

#include "../FloatNx2/FloatNx2_snprintf.hpp"

int Float64x2_snprintf(char* buf, size_t len, const char* format, ...) {
	va_list args;
	va_start(args, format);
	internal_double_FloatN_snprintf<Float64x2, fp64> func_snprintf;
	int ret_val = func_snprintf.FloatNx2_snprintf(
		PRIFloat64x2, buf, len,
		format, args
	);
	va_end(args);
	return ret_val;
}

inline std::ostream& operator<<(std::ostream& stream, const Float64x2& value) {
	internal_double_FloatN_snprintf<Float64x2, fp64> func_cout;
	return func_cout.FloatNx2_cout(PRIFloat64x2, stream, value);
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
