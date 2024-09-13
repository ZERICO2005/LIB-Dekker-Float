/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef AUTO_INCLUDE_FLOATX_MPFR_H
#define AUTO_INCLUDE_FLOATX_MPFR_H

/**
 * @file FloatX_auto_mpfr_include.h
 *
 * @brief Automatically includes FloatX_mpfr.h if the type has been declared.
 */

#ifdef FLOAT32X2_DEF_H
	#include "Float32x2/Float32x2_mpfr.h"
#endif
#ifdef FLOAT32X4_DEF_H
	#include "Float32x4/Float32x4_mpfr.h"
#endif
#ifdef FLOAT64X2_DEF_H
	#include "Float64x2/Float64x2_mpfr.h"
#endif
#ifdef FLOAT64X4_DEF_H
	#include "Float64x4/Float64x4_mpfr.h"
#endif
#ifdef FLOAT64X6_DEF_H
	#include "Float64x6/Float64x6_mpfr.h"
#endif
#ifdef FLOAT80X2_DEF_H
	#include "Float80x2/Float80x2_mpfr.h"
#endif
#ifdef FLOAT128X2_DEF_H
	#include "Float128x2/Float128x2_mpfr.h"
#endif

#endif /* AUTO_INCLUDE_FLOATX_MPFR_H */
