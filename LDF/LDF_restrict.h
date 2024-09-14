/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef LDF_RESTRICT_H
#define LDF_RESTRICT_H

/**
 * @brief Defines the C99 `restrict` keyword for C++ compilers. You may
 * override LDF_restrict by defining it prior to including this file.
 */

#ifndef LDF_restrict
	#ifndef __cplusplus
		#define LDF_restrict restrict
	#elif defined(__GNUC__)
		#define LDF_restrict __restrict
	#elif defined(_MSC_VER)
		#define LDF_restrict __restrict
	#elif defined(__INTEL_COMPILER)
		#define LDF_restrict __restrict
	#else
		#define LDF_restrict
	#endif
#endif

#endif /* LDF_RESTRICT_H */