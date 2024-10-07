/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef LDF_STATIC_ASSERT_H
#define LDF_STATIC_ASSERT_H

#include "../LDF_config.h"

/**
 * @brief Portable static_assert
 */

#ifndef LDF_static_assert
	#ifdef static_assert
		#define LDF_static_assert(bool_constexpr, unevaluated_string)\
			static_assert(bool_constexpr, unevaluated_string)
	#elif defined(__cplusplus) && __cplusplus >= 200410L
		#define LDF_static_assert(bool_constexpr, unevaluated_string)\
			static_assert(bool_constexpr, unevaluated_string)
	#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L
		#define LDF_static_assert(bool_constexpr, unevaluated_string)\
			static_assert(bool_constexpr, unevaluated_string)
	#else
		#define LDF_static_assert(bool_constexpr, unevaluated_string)
	#endif
#endif

#endif /* LDF_RESTRICT_H */
