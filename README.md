README.md updated: 2024/09/07

LIB-Dekker-Float contains a variety of Dekker-Float implementations to boost precision and performance in your C/C++ program.

This library is still under development, so it may or may not work with your program out of the box quite yet. Additionally, some math.h functions are unimplemented or rely on casting to other types.

The floating point implementations are tested on GCC and Clang with `-Wall -Wextra -Wpedantic`.

`.hpp` files are for `C++11` or later, and `.h` files are for `C99` or later and `C++11` or later. The C++ implementations support operator overloading.

Available Precisions:
* Float32x2
* Float64x2
* Float64x4
* Float80x2 (x86/x86_x64)

SIMD Types:
* Float64x2 AVX (x86/x86_x64)
* Float64x4 AVX (x86/x86_x64)

Under Development:
* Float128x2 (Requires quadmath)
* Float64x2 SSE2 (x86/x86_x64)
* Float64x4 SSE2 (x86/x86_x64)
* Float32x4

# Attribution

Some of the code is based on the quad-double and double-double implementations from libQD and libDDFUN. They can be found at https://www.davidhbailey.com/dhbsoftware/.

libQD is licensed under a modifed BSD license which can be obtained from: https://www.davidhbailey.com/dhbsoftware/LBNL-BSD-License.docx. A copy of the LBNL-BSD-License is can also be found at `LIB-Dekker-Float/libQD/LBNL-BSD-License.txt`.

libDDFUN is licensed under a limited BSD license which can be obtained from: https://www.davidhbailey.com/dhbsoftware/DHB-License.docx. A copy of the Limited-BSD-License can also be found at `LIB-Dekker-Float/libDDFUN/DISCLAIMER_and_Limited-BSD-License.txt`

# Test Code

The `./test_CXX11` and `./test_C99` folders contain some basic code to test the libraries. However, no tests/asserts are configured or setup yet.

# LDF namespace

The LDF namespace (LIB-Dekker-Float) in C++ provides templates for `add`, `sub`, `mul`, `div`, `square`, `recip`, `mul_pwr2`, and bitwise operations. The templates follow this pattern: `<Ret_Type, OP1_Type, OP2_Type, ...>`.

The LDF templates expose some functions that can't be accessed through operator overloads. For example, `double / double` can't be overloaded to return `Float64x4` instead of `double`; so instead, one would call `LDF::div<Float64x4, double, double>(x, y)`. This allows `double / double` to be calculated to `Float64x4` precision. As another example, `LDF::square<Float64x2, double>(x)` is able to efficiently square a `double` to `Float64x2` precision.

# String Operations

snprintf, stringTo, std::cout, and std::cin functions are provided for converting to and from a string.

To convert a `Float64x2` to a string, you can use `snprintf_Float64x2(buf, sizeof(buf), "%.20" PRIFloat64x2 "f")`, which will print 20 digits after the decimal point.

To convert a string to a `Float64x2`, you can use `Float64x2 value = stringTo_Float64x2("1.2345e3")`. In C++, you can also use string literals `Float64x2 value = "1.2345e3"_FP64X2`.

## snprintf specifiers:

* PRIFloat32x2  "DS"
* PRIFloat32x4  "QS"
* PRIFloat64x2  "DD"
* PRIFloat64x4  "QD"
* PRIFloat80x2  "DX"
* PRIFloat128x2 "DQ"

An extended list of snprintf specifiers can be found at `LIB-Dekker-Float/docs/Proposed-type-names.txt`

# MPFR Conversion Functions

Header files to convert to and from `mpfr_t` are available, and follow a familiar syntax:
```c
#include <mpfr.h>
// Sets a mpfr_t to a Float64x4 value
int mpfr_set_float64x4(mpfr_t rop, Float64x4 op, mpfr_rnd_t rnd);

// Returns a Float64x4 value from a mpfr_t
Float64x4 mpfr_get_float64x4(mpfr_srcptr op, mpfr_rnd_t rnd);
```
C++ template functions are also included:
```c++
#include "util_mpfr/mpfr_convert.hpp"

// Sets a mpfr_t to a Float64x4 value
template <> int mpfr_set_type<Float64x4>(mpfr_t rop, const Float64x4& op, mpfr_rnd_t rnd);

// Returns a Float64x4 value from a mpfr_t
template <> Float64x4 mpfr_get_type<Float64x4>(mpfr_srcptr op, mpfr_rnd_t rnd);
```

# Math Functions

Dekker floats have a very small epsilon. This allows them to represent values such as `1.0 + FLOAT_MIN`, which would otherwise be difficult to represent with non-Dekker floats. For example, `1.0 + FLOAT32_MIN` would require a ~128bit mantissa to represent with a standard floating point type, while `1.0 + FLOAT128_MIN` requires a ~16384bit mantissa to represent without Dekker floats.

Some math functions may offer multiple variants to balance between speed and accuracy:
* `quick` Follows a cray style error bound.
* `accurate` Follows a ieee style error bound.
