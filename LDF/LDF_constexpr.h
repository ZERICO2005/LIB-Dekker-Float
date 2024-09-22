/*
**	Author: zerico2005 (2024)
**	Project: LIB-Dekker-Float
**	License: MIT License
**	A copy of the MIT License should be included with
**	this project. If not, see https://opensource.org/license/MIT
*/

#ifndef LDF_CONSTEXPR_H
#define LDF_CONSTEXPR_H

/**
 * @brief Provides constexpr definitions
 */

#include "../LDF_config.h"

#ifndef LDF_CXX11_constexpr
	#if defined(__cplusplus) && __cplusplus >= 200704L
		#define LDF_CXX11_constexpr constexpr
	#else
		#define LDF_CXX11_constexpr
	#endif
#endif

#ifndef LDF_CXX14_constexpr
	#if defined(__cplusplus) && __cplusplus >= 201304L
		#define LDF_CXX14_constexpr constexpr
	#else
		#define LDF_CXX14_constexpr
	#endif
#endif

#ifndef LDF_C23_constexpr
	#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L
		#define LDF_C23_constexpr constexpr
	#else
		#define LDF_C23_constexpr
	#endif
#endif

#endif /* LDF_CONSTEXPR_H */
