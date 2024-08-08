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