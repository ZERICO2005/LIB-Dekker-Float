/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef FLOATNXN_TOSTRING_HPP
#define FLOATNXN_TOSTRING_HPP

#include <cstring>
#include <istream>
#include <climits>
#include <cmath>
#include <limits>

template<typename FloatNxN, typename FloatN>
class internal_FloatNxN_stringTo {
	private:

	/** Case insensitive, returns false on nullptr */
	static bool compare_text(const char* strA, const char* strB) {
		if (strA == nullptr || strB == nullptr) {
			return false;
		}
		if (strA == strB) {
			return true; // Same pointer
		}
		while(*strA != '\0' && *strB != '\0') {
			if (*strA != *strB) {
				// cast to int since -Wformat=2 is too strict
				int charA = (char)*strA;
				int charB = (char)*strB;
				charA = charA + ((charA >= 'a' && charA <= 'z') ? ('a' - 'A') : 0);
				charB = charB + ((charB >= 'a' && charB <= 'z') ? ('a' - 'A') : 0);
				if (charA != charB) {
					return false;
				}
			}
			strA++;
			strB++;
		}
		return true;
	}

	static const char* get_exponent(const char* ptr, int& exponent) {
		exponent = 0;
		bool exp_sign = false;
		if (*ptr == 'E' || *ptr == 'e') {
			ptr++;
			if (*ptr == '-') {
				exp_sign = true;
			}
			if (*ptr == '+' || *ptr == '-') {
				ptr++;
			}
			while (*ptr >= '0' && *ptr <= '9') {
				exponent *= 10;
				exponent += (*ptr - '0');
				ptr++;
			}
		}
		exponent = exp_sign ? -exponent : exponent;
		return ptr;
	}

	static void mult_exp(FloatNxN& value, int exponent) {
		if (exponent == 0) {
			return; // 10^0 == 1.0
		}
		unsigned int repeat = (unsigned int)abs(exponent);
		if (exponent < 0) {
			for (unsigned int i = 0; i < repeat; i++) {
				value /= static_cast<FloatNxN>(10.0);
			}
			return;
		}
		for (unsigned int i = 0; i < repeat; i++) {
			value *= static_cast<FloatNxN>(10.0);
		}
	}

	public:

	/**
	 * @remarks memcpy(endPtr, &nPtr, sizeof(*endPtr)) is used
	 * since *endPtr = (char*)ptr triggers -Wcast-qual
	 */
	static FloatNxN stringTo_FloatNxN(const char* const nPtr, char** const endPtr = nullptr) {
		if (nPtr == nullptr) {
			if (endPtr != nullptr) { *endPtr = nullptr; }
			return static_cast<FloatNxN>(0.0);
		}
		if (*nPtr == '\0') {
			return static_cast<FloatNxN>(0.0);
			if (endPtr != nullptr) { memcpy(endPtr, &nPtr, sizeof(*endPtr)); }
		}
		const char* ptr = nPtr;
		while (*ptr == ' ') {
			ptr++;
		}
		bool sign = (*ptr == '-') ? true : false;
		if (*ptr == '+' || *ptr == '-') {
			ptr++;
		}
		if (compare_text(ptr, "INFINITY")) {
			ptr += sizeof("INFINITY");
			FloatNxN value;
			value.hi = std::numeric_limits<FloatN>::infinity();
			value.lo = std::numeric_limits<FloatN>::infinity();
			value.hi = sign ? -value.hi : value.hi;
			value.lo = sign ? -value.lo : value.lo;
			if (endPtr != nullptr) { memcpy(endPtr, &nPtr, sizeof(*endPtr)); }
			return value;
		}
		if (compare_text(ptr, "NAN")) {
			ptr += sizeof("NAN");
			FloatNxN value;
			value.hi = std::numeric_limits<FloatN>::quiet_NaN();
			value.lo = std::numeric_limits<FloatN>::quiet_NaN();
			value.hi = sign ? -value.hi : value.hi;
			value.lo = sign ? -value.lo : value.lo;
			if (endPtr != nullptr) { memcpy(endPtr, &nPtr, sizeof(*endPtr)); }
			return value;
		}

		FloatNxN int_part = static_cast<FloatNxN>(0.0);
		while (*ptr >= '0' && *ptr <= '9') {
			int_part *= static_cast<FloatNxN>(10.0);
			int_part += (FloatNxN)(*ptr - '0');
			ptr++;
		}
		

		if (*ptr != '.') {
			int exponent;
			ptr = get_exponent(ptr, exponent);
			mult_exp(int_part, exponent);
			int_part.hi = sign ? -int_part.hi : int_part.hi;
			int_part.lo = sign ? -int_part.lo : int_part.lo;
			if (endPtr != nullptr) { memcpy(endPtr, &nPtr, sizeof(*endPtr)); }
			return int_part;
		}
		ptr++; // character after '.'

		FloatNxN frac_part = static_cast<FloatNxN>(0.0);
		FloatNxN pow10_div = static_cast<FloatNxN>(10.0);
		while (*ptr >= '0' && *ptr <= '9') {
			FloatNxN temp_digit = (FloatNxN)(*ptr - '0') / pow10_div;
			if (isfinite(temp_digit) == false) {
				break;
			}
			frac_part += temp_digit;
			pow10_div *= static_cast<FloatNxN>(10.0);
			ptr++;
		}
		while (*ptr >= '0' && *ptr <= '9') {
			ptr++; // Skipping digits that are too small
		}
		frac_part += int_part;
		int exponent;
		ptr = get_exponent(ptr, exponent);
		mult_exp(frac_part, exponent);
		frac_part.hi = sign ? -frac_part.hi : frac_part.hi;
		frac_part.lo = sign ? -frac_part.lo : frac_part.lo;
		if (endPtr != nullptr) { memcpy(endPtr, &nPtr, sizeof(*endPtr)); }
		return frac_part;
	}
	
	static std::istream& cin_FloatNxN(std::istream& stream, FloatNxN& value) {
		std::istream::sentry sentry(stream);

		if (!sentry) {
			value = static_cast<FloatNxN>(0.0);
			return stream;
		}

		std::string num_str;
		stream >> num_str;

		if (num_str.empty()) {
			value = static_cast<FloatNxN>(0.0);
			stream.setstate(std::ios::failbit);
			return stream;
		}

		char* endPtr = nullptr;
		value = stringTo_FloatNxN(num_str.c_str(), &endPtr);

		if (endPtr == num_str.c_str()) {
			value = static_cast<FloatNxN>(0.0);
			stream.setstate(std::ios::failbit);
		}

		return stream;
	}
};

#endif /* FLOATNXN_TOSTRING_HPP */
