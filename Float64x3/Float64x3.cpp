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

#include "Float64x3.h"
#include "Float64x3.hpp"

#include "Float64x3_def.h"
#include "Float64x3_string.h"

#include <cmath>
#include <limits>

//------------------------------------------------------------------------------
// Float64x4 math.h wrapper functions
//------------------------------------------------------------------------------

#if 0
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
void Float64x4_sincos(Float64x4 theta, Float64x4* LDF_restrict p_sin, Float64x4* LDF_restrict p_cos) {
	sincos(theta, *p_sin, *p_cos);
}
Float64x4 Float64x4_tan(Float64x4 x) {
	return tan(x);
}
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
Float64x4 Float64x4_cosh(Float64x4 x) {
	return cosh(x);
}
Float64x4 Float64x4_tanh(Float64x4 x) {
	return tanh(x);
}
void Float64x4_sinhcosh(Float64x4 theta, Float64x4* LDF_restrict p_sinh, Float64x4* LDF_restrict p_cosh) {
	sinhcosh(theta, *p_sinh, *p_cosh);
}

Float64x4 Float64x4_erf(Float64x4 x) {
	return erf(x);
}
Float64x4 Float64x4_erfc(Float64x4 x) {
	return erfc(x);
}
Float64x4 Float64x4_tgamma(Float64x4 x) {
	return tgamma(x);
}
Float64x4 Float64x4_lgamma(Float64x4 x) {
	return lgamma(x);
}
#endif

//------------------------------------------------------------------------------
// Float64x4 from string
//------------------------------------------------------------------------------

#include "../FloatNxN/FloatNxN_stringTo.hpp"

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

#include "../FloatNxN/FloatNxN_snprintf.hpp"

int Float64x3_snprintf(char* buf, size_t len, const char* format, ...) {
	va_list args;
	va_start(args, format);
	internal_FloatNxN_snprintf<Float64x3, fp64, 3> func_snprintf;
	int ret_val = func_snprintf.FloatNxN_snprintf(
		PRIFloat64x4, PRIFloat64,
		buf, len, format, args
	);
	va_end(args);
	return ret_val;
}

std::ostream& operator<<(std::ostream& stream, const Float64x4& value) {
	internal_FloatNxN_snprintf<Float64x3, fp64, 3> func_cout;
	return func_cout.FloatNxN_cout(PRIFloat64x3, PRIFloat64, stream, value);
}
