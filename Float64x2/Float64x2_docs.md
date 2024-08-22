Updated 2024/08/20

# Float64x2 Requirements:
* .h files: C99 and later, or C++
* .hpp files: C++11 and later

# Float64x2.h
The C version of Float64x2.

`Float64x2.hpp` is included when compiling in C++.
## Nomenclature
`Float64x2_add`: Adds two `Float64x2` values
`Float64x2_add_dx2_d`: Adds a `Float64x2` value, and a `double` value
`Float64x2_add_d_dx2`: Adds a `double` value, and a `Float64x2` value
`Float64x2_add_d_d`: Adds two `double` values, storing the result as a `Float64x2` value

# Float64x2.hpp
The C++ version of Float64x2. Including operator overloads, constructors, and `std::numeric_limits`.

`Float64x2.h` is also included.

# Float64x2_def.h
Defines the Float64x2 struct for the purposes of forward declaration.

# Float64x2_AVX.h
A vector of four `Float64x2` implemented with AVX SIMD intrisics for x86/x86_64. Uses the `__m256dx2` type.

## Nomenclature
`_mm256x2_add_pdx2`: Adds two `__m256dx2` values
`_mm256x2_add_pdx2_pd`: Adds a `__m256dx2` value, and a `__m256d` value
`_mm256x2_add_pd_pdx2`: Adds a `__m256d` value, and a `__m256dx2` value
`_mm256x2_add_pd_pdx2`: Adds two `__m256d` values, storing the result as a `__m256dx2` value
`_mm256x2_cmpeq_pdx2`: Compares two `__m256dx2` values, storing the result as a `__m256dx2` mask
`_mm256_cmpeq_pdx2`: Compares two `__m256dx2` values, storing the result as a `__m256d` mask

# Float64x2_mpfr.h
Conversion functions between `Float64x2` and `mpfr`. May require `mpfr` and `gmp`.
