/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef FLOATNXN_SNPRINTF_HPP
#define FLOATNXN_SNPRINTF_HPP

#include <cmath>
#include <cstdarg>
#include <cstring>
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <ostream>
#include <vector>

template<
	typename FloatNxN, typename FloatN,
	size_t FloatN_Count
>
class internal_FloatNxN_snprintf {
	static_assert(FloatN_Count >= 2);

	private:
	
	/** Searches for the first %, skips %% */
	static const char* find_format_start(const char* format) {
		if (format == nullptr) { return nullptr; }
		size_t pos = 0;
		while (format[pos] != '\0') {
			if (format[pos] == '%') {
				pos++;
				if (format[pos] != '%') {
					return &format[pos];
				}
			}
			pos++;
		}
		return nullptr;
	}

	/** Parses - + <space> # 0 */
	static const char* parse_flags(
		const char* format,
		bool& left_justify,
		bool& explicit_sign,
		bool& space_sign,
		bool& explicit_decimal_point,
		bool& pad_zeros
	) {
		left_justify = false;
		explicit_sign = false;
		space_sign = false;
		explicit_decimal_point = false;
		pad_zeros = false;
		if (format == nullptr) { return nullptr; }

		size_t pos = 0;
		while (format[pos] != '\0') {
			switch (format[pos]) {
				case '-':
					left_justify = true;
				break;
				case '+':
					explicit_sign = true;
				break;
				case ' ':
					space_sign = true;
				break;
				case '#':
					explicit_decimal_point = true;
				break;
				case '0':
					pad_zeros = true;
				break;
				default:
					return &format[pos];
			}
			pos++;
		}
		return &format[pos];
	}

	/** Sets format width and detects if the width is in a va_arg */
	static const char* parse_width(
		const char* format,
		int& width,
		bool& custom_width
	) {
		width = 0;
		custom_width = false;
		if (format == nullptr) { return nullptr; }

		if (*format == '*') {
			custom_width = true;
			format++; // Return the next character
			return format;
		}
		if (*format >= '1' && *format <= '9') {
			char* end_ptr = nullptr;
			width = (int)strtol(format, &end_ptr, 10);
			if (end_ptr == nullptr) {
				return format;
			}
			return end_ptr; // Return character after integer
		}
		return format;
	}

	/** Sets format precision and detects if the precision is in a va_arg */
	static const char* parse_precision(
		const char* format,
		int& precision,
		bool& custom_precision
	) {
		precision = 6;
		custom_precision = false;
		if (format == nullptr) { return nullptr; }
		
		if (*format != '.') {
			return format;
		}
		format++; // Grab integer after '.'

		if (*format == '*') {
			custom_precision = true;
			format++; // Return the next character
			return format;
		}
		if (*format >= '1' && *format <= '9') {
			char* end_ptr = nullptr;
			precision = (int)strtol(format, &end_ptr, 10);
			if (end_ptr == nullptr) {
				return format;
			}
			return end_ptr; // Return character after integer
		}
		return format;
	}

	/** Searches for the PRIFloatNxN specifier and aAeEfFgG */
	static const char* parse_specifier(
		const char* PRIFloatNxN,
		const char* format,
		char& specifier
	) {
		if (format == nullptr) { return nullptr; }
		specifier = '\0';
		{
			// Compares the two strings manually
			const char* PRI_ptr = PRIFloatNxN;
			const char* fm_ptr = format;
			while (*PRI_ptr == *fm_ptr && *PRI_ptr != '\0' && *fm_ptr != '\0') {
				PRI_ptr++;
				fm_ptr++;
			}
			if (*PRI_ptr != '\0') {
				return format;
			}
			format = fm_ptr; // Pointer to the specifier character
		}
		switch(*format) {
			case 'a':
			case 'A':
			case 'e':
			case 'E':
			case 'f':
			case 'F':
			case 'g':
			case 'G':
				specifier = *format;
				format++;
				return format;
			default:
				return format;
		}
		return format;
	}

	struct FloatNxN_format_param {
		int width; // %*Df
		int precision; // %.*Df
		bool left_justify; // %-Df
		bool explicit_sign; // %+Df
		bool space_sign; // % Df
		bool explicit_decimal_point; // %#Df
		bool pad_zeros; // %0Df
		char specifier; // fFgGeEaA
	};

	static std::string FloatN_string_snprintf(
		const char* format, int precision, FloatN value
	) {
		// This is used to supress -Wformat-non-literal portably
		typedef int (* const snprintf_func)(char *buf, size_t size, const char *format, ...);
		const snprintf_func snprintf_wrapper = snprintf;

		std::string ret = "";
		// Get the size of the string
		int len_str = snprintf_wrapper(nullptr, 0, format, precision, value);
		if (len_str < 0) {
			// snprintf failure
			return ret;
		}

		// Allocates the string/buffer
		size_t size_str = (size_t)len_str + 1;
		char* buf = (char*)calloc(size_str, sizeof(char));
		if (buf == nullptr) {
			// calloc failure
			return ret;
		}

		// Writes the string to the buffer
		if (snprintf_wrapper(buf, size_str, format, precision, value) < 0) {
			// snprintf failure
			free(buf);
			buf = nullptr;
			return ret;
		}

		// Converts to an std::string
		ret.assign(buf);
		free(buf);
		buf = nullptr;
		return ret;
	}

	/**
	 * @brief Assumes |x| >= |y| and that x and y have the same number of decimal places.
	 */
	static std::string sum_decimal_strings(
		std::string x, std::string y,
		bool explicit_decimal_point
	) {
		std::string ret = "";
		if (x.size() <= 1 || y.size() <= 1) {
			// Invalid string
			return ret;
		}

		bool found_decimal_point = false;
		const bool x_sign = (x.at(0) == '-');
		const bool y_sign = (y.at(0) == '-');
		const bool subtraction_mode = (x_sign != y_sign);

		// End of the string
		const char* x_str = x.c_str() + x.size() - 1;
		const char* y_str = y.c_str() + y.size() - 1;

		int carry = 0;

		while (x_str > x.c_str() && y_str > y.c_str()) {
			// Skips over the decimal point
			if (*x_str == '.' && *y_str == '.' && found_decimal_point == false) {
				found_decimal_point = true;
				ret += '.';
				x_str--;
				y_str--;
				continue;
			} else if (
				*x_str < '0' || *x_str > '9' ||
				*y_str < '0' || *y_str > '9'
			) {
				// Invalid character, misaligned decimal points, or double decimal point.
				return ret;
			}

			int x_num = *x_str - '0';
			int y_num = *y_str - '0';
			int num = x_num + carry + (subtraction_mode ? -y_num : y_num);
			carry = num / 10;
			num %= 10;
			if (subtraction_mode && num < 0) {
				num += 10;
				carry--;
			}
			ret += (char)(num + '0');
			x_str--;
			y_str--;
		}
		while (x_str > x.c_str()) {
			int x_num = *x_str - '0';
			int num = x_num + carry;
			carry = num / 10;
			num %= 10;
			if (subtraction_mode && num < 0) {
				num += 10;
				carry--;
			}
			ret += (char)(num + '0');
			x_str--;
		}
		while (carry != 0) {
			int num = carry;
			carry /= 10;
			num %= 10;
			if (subtraction_mode && num < 0) {
				num += 10;
				carry--;
			}
			ret += (char)(num + '0');
		}

		// Remove extra zeros
		size_t padding_index = ret.size() - 1;
		while (ret.at(padding_index) == '0') {
			padding_index--;
		}
		if (ret.at(padding_index) == '.') {
			found_decimal_point = true;
			padding_index++;
		}
		ret = ret.substr(0, padding_index + 1);
		ret += x_sign ? "-" : "+";
		std::reverse(ret.begin(), ret.end());
		if (found_decimal_point == false && explicit_decimal_point == true) {
			ret += '.';
		}
		return ret;
	}


	static std::string FloatNxN_sum_decimal_strings(
		const char* PRIFloatN,
		const FloatNxN_format_param& param,
		const FloatN* const val, const size_t val_count
	) {
		std::string format = "%+.*";
		format += PRIFloatN;
		format += "f";

		std::string sum_str = FloatN_string_snprintf(
			format.c_str(), param.precision, val[0]
		);
		for (size_t i = 1; i < val_count; i++) {
			std::string add_str = FloatN_string_snprintf(
				format.c_str(), param.precision, val[i]
			);
			sum_str = sum_decimal_strings(
				sum_str, add_str, param.explicit_decimal_point
			);
		}
		// Removes the sign used for summing the strings together
		return sum_str.substr(1, sum_str.size());
	}

	static std::string FloatNxN_write_decimal_string(
		const char* PRIFloatN,
		const FloatNxN_format_param& param, const bool upperCase,
		const FloatN* const val, const size_t val_count
	) {
		// Used for checking for infinity, nan, etc
		FloatN approx_value = static_cast<FloatN>(0.0);
		for (size_t i = 0; i < val_count; i++) {
			approx_value += val[i];
		}

		std::string str = "";

		if (std::signbit(approx_value)) {
			str += '-';
		} else if (param.explicit_sign) {
			str += '+';
		} else if (param.space_sign) {
			str += ' ';
		}

		if (std::isinf(approx_value)) {
			str += upperCase ? "INFINITY" : "infinity";
			return str;
		}
		if (std::isnan(approx_value)) {
			str += upperCase ? "NAN" : "nan";
			return str;
		}
		str += FloatNxN_sum_decimal_strings(
			PRIFloatN, param, val, val_count
		);
		
		size_t len_str = str.length();
		size_t pad_width = (param.width < 0) ? 0 : (size_t)param.width;
		if (len_str >= pad_width) {
			return str;
		}
		
		std::string padded_str = "";
		size_t pad_length = pad_width - len_str;
		const char pad_char = (param.pad_zeros && param.left_justify == false) ? '0' : ' ';
		for (size_t i = 0; i < pad_length; i++) {
			padded_str += pad_char;
		}
		
		if (param.left_justify) {  
			str += padded_str;
			return str;
		}
		padded_str += str;

		return padded_str;
	}

#if 0
	/**
	* @brief Prints decimial/hexadecimal digit
	* @note Assumes base is either 10 or 16 for %f, %F, %a, and %A
	*/
	static char get_digit_from_base(
		int value, int base, bool upperCase
	) {
		assert(base == 10 || base == 16);
		if (value >= 0 && value <= 9) {
			return (char)(value + '0');
		}
		if (base == 16) {
			if (value >= 10 && value <= 16) {
				return (char)(value + (upperCase ? 'A' : 'a') - 10);
			}
		}
		return '?';
	}

	// /**
	// * @brief Increments decimial/hexadecimal digit
	// * @note Assumes base is either 10 or 16 for %f, %F, %a, and %A
	// * @returns true if an overflow occured.
	// */
	// static bool inc_digit_from_base(
	// 	char* digit, int base, bool upperCase
	// ) {
	// 	printf("L: %d %02X %p\n", __LINE__, *digit, digit);
	// 	if (digit == nullptr) { return false; }
	// 	assert(base == 10 || base == 16);
	// 	if (base == 16) {
	// 		printf("L: %d\n", __LINE__);
	// 		if (
	// 			(upperCase == true && *digit == 'F') ||
	// 			(upperCase == false && *digit == 'f')
	// 		) {
	// 			*digit = '0';
	// 			return true; // Overflow
	// 		}
	// 		if (*digit == '9') {
	// 			*digit = (upperCase ? 'A' : 'a');
	// 			return false;
	// 		}
	// 		if (
	// 			(upperCase == true && *digit >= 'A' && *digit <= 'E') ||
	// 			(upperCase == false && *digit >= 'a' && *digit <= 'e')
	// 		) {
	// 			(*digit)++;
	// 			return false;
	// 		}
	// 	} else {
	// 		printf("L: %d\n", __LINE__);
	// 		if (*digit == '9') {
	// 			*digit = '0';
	// 			return true; // Overflow
	// 		}
	// 	}
	// 	printf("L: %d\n", __LINE__);
	// 	if (*digit >= '0' && *digit <= '8') {
	// 		(*digit)++;
	// 		return false;
	// 	}
	// 	printf("L: %d\n", __LINE__);
	// 	return false;
	// }

	static std::string FloatNxN_write(
		const FloatNxN_format_param& param,
		FloatNxN value, const int base, const bool upperCase
	) {

		std::string str = "";
		if (value < static_cast<FloatNxN>(0.0)) {
			str += '-';
		} else if (param.explicit_sign) {
			str += '+';
		} else if (param.space_sign) {
			str += ' ';
		}
		if (isinf(value)) {
			str += upperCase ? "INFINITY" : "infinity";
			return str;
		}
		if (isnan(value)) {
			str += upperCase ? "NAN" : "nan";
			return str;
		}
		value = fabs(value);
		FloatNxN value_int = trunc(value);
		FloatNxN value_frac = value - value_int;

		if (value_int == static_cast<FloatNxN>(0.0)) {
			str += '0';
		} else {
			/* Integer Part */
			std::string int_digits = "";
			while (value_int > static_cast<FloatNxN>(0.0)) {
				FloatNxN digit_temp = value_int - (trunc(value_int / (FloatNxN)base) * (FloatNxN)base);
				char digit = get_digit_from_base((int)digit_temp, base, upperCase);
				int_digits += digit;
				value_int = trunc(value_int / (FloatNxN)base);
			}
			reverse(int_digits.begin(), int_digits.end());
			str += int_digits;
		}
		
		if (param.precision != 0) {
			
			/* Fractional/Decimal Part */
			str += '.';
			std::string frac_digits = "";
			for (int d = 0; d < param.precision - 1; d++) {
				if (value_frac == static_cast<FloatNxN>(0.0)) {
					// Rest of the digits will be 0
					frac_digits += '0';
					continue;
				}
				value_frac *= (FloatNxN)base;
				FloatNxN digit_temp = trunc(value_frac);
				char digit = get_digit_from_base((int)digit_temp, base, upperCase);
				frac_digits += digit;
				value_frac = value_frac - trunc(value_frac);
			}
			{ /* Rounds the last digit */
				value_frac *= (FloatNxN)base;
				FloatNxN digit_temp = round(value_frac);
				if ((int)digit_temp == base) {
					/* round()
					char* round_ptr = (char*)frac_digits.c_str();
					frac_digits += '0';
					while (inc_digit_from_base(round_ptr, base, upperCase)) {
						round_ptr--;
					}
					*/
					// /* trunc()
					if (base == 16) {
						frac_digits += upperCase ? 'F' : 'f';
					} else {
						frac_digits += '9';
					}
					// */
				} else {
					char digit = get_digit_from_base((int)digit_temp, base, upperCase);
					frac_digits += digit;
				}
			}
			
			str += frac_digits;
		} else if (param.explicit_decimal_point) {
			str += '.';
		}

		size_t len_str = str.length();
		size_t pad_width = (param.width < 0) ? 0 : (size_t)param.width;
		if (len_str >= pad_width) {
			return str;
		}
		
		std::string padded_str = "";
		size_t pad_length = pad_width - len_str;
		const char pad_char = (param.pad_zeros && param.left_justify == false) ? '0' : ' ';
		for (size_t i = 0; i < pad_length; i++) {
			padded_str += pad_char;
		}
		
		if (param.left_justify) {  
			str += padded_str;
			return str;
		}
		padded_str += str;
		
		return padded_str;
	}
#endif

	public:

	static int FloatNxN_snprintf(
		const char* PRIFloatNxN, const char* PRIFloatN,
		char* buf, size_t len,
		const char* format, va_list args
	) {
		const char* fm_ptr = find_format_start(format);
		if (fm_ptr == nullptr || *fm_ptr == '\0') {
			return -1; // Invalid format
		}

		const char* const fm_start = fm_ptr;

		FloatNxN_format_param param;

		fm_ptr = parse_flags(
			fm_ptr,
			param.left_justify, param.explicit_sign, param.space_sign,
			param.explicit_decimal_point, param.pad_zeros
		);
		bool custom_width;
		fm_ptr = parse_width(fm_ptr, param.width, custom_width);
		if (custom_width) {
			param.width = va_arg(args, int);
			if (param.width < 0) {
				param.left_justify = true;
				param.width = -param.width;
			}
		}
		bool custom_precision;
		fm_ptr = parse_precision(fm_ptr, param.precision, custom_precision);
		if (custom_precision) {
			param.precision = va_arg(args, int);
			if (param.precision < 0) {
				param.precision = 0;
			}
		}
		fm_ptr = parse_specifier(PRIFloatNxN, fm_ptr, param.specifier);

		switch(param.specifier) {
			case 'a':
			case 'A':
			case 'e':
			case 'E':
			case 'f':
			case 'F':
			case 'g':
			case 'G':
				break;
			case '\0':
			default: // Invalid specifier
				// va_end(args);
				strncpy(buf, format, len);
				return (int)strlen(format);
		}
		
		FloatNxN value = va_arg(args, FloatNxN);

		std::string output_str = "";
		if (fm_start > format) { /* Copy text before % */
			size_t copy_amount = (size_t)(fm_start - format);
			output_str.append(format, copy_amount - 1);
		}
		FloatN* const value_array = reinterpret_cast<FloatN*>(&value);
		switch (param.specifier) {
			default:
			case 'f':
				output_str += FloatNxN_write_decimal_string(
					PRIFloatN,
					param, false, value_array, FloatN_Count
				);
				break;
			case 'F':
				output_str += FloatNxN_write_decimal_string(
					PRIFloatN,
					param, true, value_array, FloatN_Count
				);
				break;
			case 'a':
				output_str += "<unsupported %a FloatNxN_snprintf>";
				break;
			case 'A':
				output_str += "<unsupported %A FloatNxN_snprintf>";
				break;
			case 'e':
				output_str += "<unsupported %e FloatNxN_snprintf>";
				break;
			case 'E':
				output_str += "<unsupported %E FloatNxN_snprintf>";
				break;
			case 'g':
				output_str += "<unsupported %g FloatNxN_snprintf>";
				break;
			case 'G':
				output_str += "<unsupported %G FloatNxN_snprintf>";
				break;
		}
		
		{ /* Copy the remainding text after % */
			output_str.append(fm_ptr);
		}
		strncpy(buf, output_str.c_str(), len);

		// va_end(args);
		return (int)strlen(output_str.c_str());
	}

	private:

	/**
	 * @brief converts a fixed amount arguments into a va_list
	 */
	static int FloatNxN_cout_snprintf(
		const char* PRIFloatNxN, const char* PRIFloatN,
		char* buf, size_t len,
		const char* format, ...
	) {
		va_list args;
		va_start(args, format);
		int ret_val = FloatNxN_snprintf(
			PRIFloatNxN, PRIFloatN,
			buf, len,
			format, args
		);
		va_end(args);
		return ret_val;
	}

	public:

	static std::ostream& FloatNxN_cout(
		const char* PRIFloatNxN, const char* PRIFloatN,
		std::ostream& stream, const FloatNxN& value
	) {
		std::string format_str = "%";
		format_str += (stream.flags() & std::ios_base::showpoint) ? "#" : "";
		format_str += (stream.flags() & std::ios_base::showpos) ? "+" : "";
		// format_str += (stream.flags() & std::ios_base::right) ? "-" : "";
		format_str += "*.*";
		format_str += PRIFloatNxN;
		bool uppercase_format = (stream.flags() & std::ios_base::uppercase) ? true : false;
		bool fixed_format = (stream.flags() & std::ios_base::fixed) ? true : false;
		bool scientific_format = (stream.flags() & std::ios_base::scientific) ? true : false;
		
		char format_specifier = 'f';
		if (fixed_format) {
			if (scientific_format) {
				format_specifier = uppercase_format ? 'A' : 'a';
			} else {
				format_specifier = uppercase_format ? 'F' : 'f';
			}
		} else {
			if (scientific_format) {
				format_specifier = uppercase_format ? 'E' : 'e';
			} else {
				format_specifier = uppercase_format ? 'G' : 'g';
			}
		}
		
		#if 1 /* Only %f and %F have been implemented */
			format_specifier = uppercase_format ? 'F' : 'f';
		#endif
		format_str += format_specifier;
		
		int width = 0; // stream.width();
		int precision = (int)stream.precision(); // cast from size_t to int
		int len_str = FloatNxN_cout_snprintf(
			PRIFloatNxN, PRIFloatN,
			nullptr, 0, format_str.c_str(), width, precision, value
		);
		if (len_str < 0) {
			stream << "Failed to format FloatNxN";
			return stream;
		}
		size_t str_size = (size_t)len_str;
		char* buf = (char*)calloc(str_size + 1, sizeof(char));
		if (buf == nullptr) {
			stream << "Failed to calloc FloatNxN2";
			return stream;
		}
		FloatNxN_cout_snprintf(
			PRIFloatNxN, PRIFloatN,
			buf, str_size, format_str.c_str(), width, precision, value
		);
		stream << buf;
		free(buf);
		buf = nullptr;
		return stream;
	}
};

#endif /* FLOATNXN_SNPRINTF_HPP */
