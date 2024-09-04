/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#include "Float80x2.hpp"
#include "Float80x2_string.h"

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

inline std::ostream& operator<<(std::ostream& stream, const Float80x2& value) {
	internal_FloatNxN_snprintf<Float80x2, fp80, 2> func_cout;
	return func_cout.FloatNxN_cout(PRIFloat80x2, PRIFloat80, stream, value);
}
