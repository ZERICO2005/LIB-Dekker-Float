/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#include "Float32x2.hpp"
#include "Float32x2_string.h"

//------------------------------------------------------------------------------
// Float32x2 from string
//------------------------------------------------------------------------------

#include "../FloatNxN/FloatNxN_stringTo.hpp"

Float32x2 stringTo_Float32x2(const char* nPtr, char** endPtr) {
	internal_FloatNxN_stringTo<Float32x2, fp32> stringTo_func;
	return stringTo_func.stringTo_FloatNxN(nPtr, endPtr);
}

std::istream& operator>>(std::istream& stream, Float32x2& value) {
	internal_FloatNxN_stringTo<Float32x2, fp32> func_cin;
	return func_cin.cin_FloatNxN(stream, value);
}

//------------------------------------------------------------------------------
// Float32x2 to string
//------------------------------------------------------------------------------

#include "../FloatNxN/FloatNxN_snprintf.hpp"

int Float32x2_snprintf(char* buf, size_t len, const char* format, ...) {
	va_list args;
	va_start(args, format);
	internal_FloatNxN_snprintf<Float32x2, fp32, 2> func_snprintf;
	int ret_val = func_snprintf.FloatNxN_snprintf(
		PRIFloat32x2, PRIFloat32,
		buf, len, format, args
	);
	va_end(args);
	return ret_val;
}

std::ostream& operator<<(std::ostream& stream, const Float32x2& value) {
	internal_FloatNxN_snprintf<Float32x2, fp32, 2> func_cout;
	return func_cout.FloatNxN_cout(PRIFloat32x2, PRIFloat32, stream, value);
}
