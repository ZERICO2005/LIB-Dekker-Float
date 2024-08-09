LIB-Dekker-Float contains a variety of header-only Double-Dekker-Float implementations to boost precision and performance in your C/C++ program.

This library is still under development, so it may or may not work with your program out of the box quite yet. Additionally, some math.h functions are unimplemented or rely on casting to other types.

The floating point implementations are tested on GCC and Clang with `-Wall -Wextra`.

`.hpp` files are for `C++11` or later, and `.h` files are for `C99` or later and `C++11` or later. The C++ implementations support operator overloading.

Available Precisions:
* Float32x2
* Float64x2
* Float80x2 (x86/x86_x64)

SIMD Types:
* Float64x2 AVX (x86/x86_x64)

Under Development:
* Float128x2 (Requires quadmath)
* Float64x2 SSE2 (x86/x86_x64)

# Math Functions

Dekker floats have a very small epsilon. This allows them to represent values such as `1.0 + FLOAT_MIN`, which would otherwise be difficult to represent with non-Dekker floats. For example, `1.0 + FLOAT32_MIN` would require a ~128bit mantissa to represent with a standard floating point type, while `1.0 + FLOAT128_MIN` requires a ~16384bit mantissa to represent without Dekker floats.

Some math functions may offer multiple variants to balance between speed and accuracy:
* `fast` calculates to the number of mantissa bits of the non-Dekker float. Less accurate but faster.
* `standard` calculates to the number of mantissa bits of the Dekker float. Recommended for most use cases.
* `accurate` calculates to the highest precision possible, covering edge cases such as `1.0 + FLOAT_MIN`. Very slow and not recommended.
