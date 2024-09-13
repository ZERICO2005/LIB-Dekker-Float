/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef LDF_TYPE_INFO_HPP
#define LDF_TYPE_INFO_HPP

namespace LDF {

template<typename FloatNxN>
struct LDF_Type_Info {
	/** The amount of FloatBase that comprise FloatNxN */
	static constexpr int FloatBase_Count = 0;

	/** If FloatNxN can be converted to a string */
	static constexpr bool to_string_implemented = false;

	/** If a string can be converted to FloatNxN */
	static constexpr bool from_string_implemented = false;

	/**
	 * If add, sub, mul, div, and comparisons operators are implemented for
	 * (FloatNxN, FloatNxN), (FloatNxN, FloatBase), and (FloatBase, FloatNxN)
	 */
	static constexpr bool arithmetic_implemented = false;
	
	/**
	 * If std::numeric_limits is available for FloatNxN
	 */
	static constexpr bool numeric_limits_implemented = false;
	
	/** If bitwise operators are available */
	static constexpr bool bitwise_implemented = false;
	
	/** If mathematical constants have been generated */
	static constexpr bool constants_implemented = false;
	
	/**
	 * If all C99 math functions are implemented and accurate to at least
	 * `(FloatBase_Count - 1) * FloatBase_Mantissa_Bits + 2` bits of precision
	 */
	static constexpr bool basic_C99_math_implemented = false;
	
	/**
	 * If all C99 math functions are implemented and accurate to
	 * `FloatBase_Count * 2` ULP (Units in the last place)
	 */
	static constexpr bool accurate_C99_math_implemented = false;
};

}

#endif /* LDF_TYPE_INFO_HPP */
