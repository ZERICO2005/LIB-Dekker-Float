Updated: 2024/09/23

This document covers how math operations work on Dekker-float types. Some of it loosely follows ieee-754, libQD, and the C/C++ standards. Other behaviour is harder to define for Dekker-floats however, due to some of the properties they have.

Note: This page does not cover arithmetic operators.

Terminology:
* `FloatNxN`: the Dekker-float type
* `FloatBase`: the floating point type that comprises a Dekker-float type.
* `hi`: The most significant or largest field of the Dekker-float type.
* `lo`: The least significant or smallest field of the Dekker-float type.
* `field`: The floats that comprise a Dekker-float.
* `normalized`: The Dekker-float type has each field in descending order. This allows assumptions and optimizations to be made.

# Unimplemented Functions

The following functions are unimplemented, or are not proven to work. Feel free to contribute your suggestions to these functions:

* `FloatNxN nextafter(FloatNxN x, FloatNxN y)`
* `FloatNxN nexttoward(FloatNxN x, long double y)`
* `FloatNxN fma(FloatNxN x, FloatNxN y, FloatNxN z)`

# Floating Point Classification

Most of the classification functions check the `hi` field of a Dekker-float type. The input is assumed to be normalized. The `isnormal` function however will check all fields of the Dekker-float.

## signbit

`bool signbit(FloatNxN x)`

The `signbit` function shall call `signbit(x.hi)`

## isfinite

`bool isfinite(FloatNxN x)`

The `isfinite` function shall call `isfinite(x.hi)`

## isinf

`bool isinf(FloatNxN x)`

The `isinf` function shall call `isinf(x.hi)`

## isnan

`bool isnan(FloatNxN x)`

The `isnan` function shall call `isnan(x.hi)`

## issignaling

`bool issignaling(FloatNxN x)`

The `issignaling` function shall call `issignaling(x.hi)`

## isnormal

`bool isnormal(FloatNxN x)`

The `isnormal` function should return `true` if all fields are `normal` or `zero`. However, it shall return `false` if all fields are `zero`.

## isunordered

`bool isunordered(FloatNxN x, FloatNxN y)`

The `isunordered` function shall call `isunordered(x.hi, y.hi)`

## fpclassify

The `fpclassify` function is currently implemented as follows:

```c++
int fpclassify(FloatNxN x) {
	return
		isinf(x)        ? FP_INFINITE :
		isnan(x)        ? FP_NAN      :
		isequal_zero(x) ? FP_ZERO     :
		isnormal(x)     ? FP_NORMAL   :
		FP_SUBNORMAL;
}
```

# Basic Math Functions

## negate

`FloatNxN negate(FloatNxN x)`

Negating a Dekker-float type is performed by negating all fields of the Dekker-float.

## fabs

`FloatNxN fabs(FloatNxN x)`

Negates the dekker float if `signbit(x)` returns `true`

## copysign

The `copysign` function copies the sign from `y` to `x`. It is implemented as follows:

```c++
FloatNxN fdim(FloatNxN x, FloatNxN y) {
	return (signbit(x) != signbit(y)) ? -x : x;
}
```

## fdim

The `fdim` function returns the positive difference of `x` and `y`. It is implemented as follows:

```c++
FloatNxN fdim(FloatNxN x, FloatNxN y) {
	return (x > y) ? (x - y) : 0.0;
}
```

## nextafter

`FloatNxN nextafter(FloatNxN x, FloatNxN y)`

The `nextafter` function returns the next representable value after `x` in the direction of `y`. If `x == y`, `x` is returned. This function could be implemented by performing `std::nextafter` on the `lo` field, and normalizing the result, but this is unproven to work.

## nexttoward

`FloatNxN nexttoward(FloatNxN x, long double y)`

The `nexttoward` function may be tricky, and there may have to be three versions of the function:
1. Where `long double` can represent all values of `FloatNxN` (Which is rare). For example `Float16x2` and `Float64`.
2. Where `FloatNxN` can represent all values that `long double` can represent. For example `Float80x2` and `Float128`.
3. Where `long double` and `FloatNxN` both have values that the other type cannot represent (Most common). For example `Float32x2` and `Float128`.

The third senario is the most difficult to handle. `Float128` can represent smaller/larger numbers due to its larger expoent range. However, it does not have enough mantissa bits to represent numbers such as `Float32_MIN + Float32_MAX`, which can be represented exactly by `Float32x2`.

## fma

`FloatNxN fma(FloatNxN x, FloatNxN y, FloatNxN z)`

Fused-multiply-add currently uses a naive implementation of using a larger Dekker-float type for calculations, rounding the result back down to `FloatNxN`.

## hypot

`FloatNxN hypot(FloatNxN x, FloatNxN y)`

The `hypot` uses the naive method of `sqrt(square(x) + square(y)`. This may result in overflows, and will need to be corrected.

# Comparison

## isequal (x == y)

Performs an ordered equals comparison.

## isnotequal (x != y)

Performs an ordered not-equals comparison.

## isless (x < y)

Performs an ordered less-than comparison.

## islessequal (x <= y)

Performs an ordered less-than or equals comparison.

## isgreater (x > y)

Performs an ordered greater-than comparison.

## isgreaterequal (x >= y)

Performs an ordered greater-than or equals comparison.

## islessgreater (x < y || x > y)

Performs an unordered not-equals comparison.

# Comparison to Zero

Variants of the previous functions exist specifically for comparing against `zero`. Such as `isequal_zero` or `isgreaterequal_zero`. These functions assume that if the `hi` field is `zero`, then the rest of the fields must also be `zero`.

# Unordered Comparison

## isequal_unord !(x < y || x > y)

Performs an unordered equals comparison.

## isnotequal_unord (x < y || x > y)

Alias for `islessgreater(x, y)`. Performs an unordered not-equals comparison.

## isless_unord !(x >= y)

Performs an unordered less-than comparison.

## islessequal_unord !(x > y)

Performs an unordered less-than or equals comparison.

## isgreater_unord !(x <= y)

Performs an unordered greater-than comparison.

## isgreaterequal_unord !(x < y)

Performs an unordered greater-than or equals comparison.

# Maximum and Minimum

## fmax

The `fmax` function is implemented as follows:

```c++
FloatNxN fmax(FloatNxN& x, FloatNxN y) {
	return
		(x < y) ? y :
		(y < x) ? x :
		isnan(x) ? y :
		isnan(y) ? x :
		signbit(x) ? y : x;
}
```

## fmin

The `fmin` function is implemented as follows:

```c++
FloatNxN fmax(FloatNxN& x, FloatNxN y) {
	return
		(x > y) ? y :
		(y > x) ? x :
		isnan(x) ? y :
		isnan(y) ? x :
		signbit(x) ? y : x;
}
```

# Exponents

## exp

`FloatNxN exp(FloatNxN x)`

Performs range reduction to make the Taylor-series converge faster.

Special return values:
* -inf: `0`
* -1.0: `1 / e`
*  0.0: `1`
* +1.0: `e`

## expm1

`FloatNxN expm1(FloatNxN x)`

Calcualtes `e^x - 1` without losing precision when `x` is close to `zero`. This only works when `|x| < 1/2 * ln(2)`, otherwise uses the naive approach of `exp(x) - 1.0`.

Performs range reduction to make the Taylor-series converge faster.

Special return values:
* -inf: `-1`
*  0.0: `0`
* +inf: `inf`

## log

`FloatNxN log(FloatNxN x)`

Calcualtes the natural logarithm of `x` using newtons method. Returns `nan` if `x < 0.0`

Special return values:
*  0.0: `-inf`
*  1.0: `0`

## log1p

`FloatNxN log1p(FloatNxN x)`

Calcualtes `log(x + 1)` without losing precision when `x` is close to `zero`. Currently uses larger Dekker-float types for calculation. Returns `nan` if `x < -1.0`

Special return values:
* -1.0: `-inf`
*  0.0: `0`
