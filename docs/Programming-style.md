Updated: 2024/09/13

If you want to contribute or add code to LIB-Dekker-Float, it is reccomended that you follow this programming-style guide.

# General Formatting

## Indentation and Column-Width

LIB-Dekker-Float uses Tabs for indentation. Tabs are assumed to be 4 spaces wide.

If you do use spaces for indentation, use either 4 or 8 spaces for indentation. Please do not use 2 spaces per tab.

Keeping things to 80 columns is nice, but in general, try to keep code and documentation to less than 100 columns wide. 120 columns is fine on occasion if it improve readability.

## Comment Format

Use doxygen for comment formmating.

## Date and Time Format

The date and time should follow `YYYY/MM/DD HH:MM:SS`, `YYYY-MM-DD_HH-MM-SS`, or ISO-8601. For example: `2024/12/31 23:59:59`.

If you choose to use a different format, please spell out the month. For example: `December 31st, 2024`.

## Casing

`snake_case` is the most common casing used in LIB-Dekker-Float. Generally speaking, any casing style may be used as long as it is readable.

Common use cases:
* `snake_case`, `camel_Snake_Case`, and `camelCase` are commonly used for variables, local constants, and functions.
* `Pascal_Snake_Case`, and `PascalCase` are commonly used for local/global constants, and functions.
* `ALL_CAPS` is commonly used for global constants, and macros.

Never use `lowercase` or `UPPERCASE`. They hinder readability as they don't have a way of separating individual words.

# Code Formatting

## Keyword useage

Please do not omit the braces from if, for, while, etc statements.
```c++
// Okay
if (cond) {
	i++;
}

// Don't do this
if (cond)
	i++;
```

## Pointers and References

Formatting for pointers and references are based off the following examples: `uint64_t* value`, `double& num`, `const char* restrict const str`.

It is okay if other formats such as `uint64_t *value` or `uint64_t * value` are used, but please do not use `uint64_t*value`.

## Function Parameters

If you have a long list of parameters for a function, please format it in one of the following ways:
```c++
// Single line
void func(char* str, int x, int y, int z, float value);

// Next line
void func(
	char* str, int x, int y, int z, float value
);

// Grouped
void func(
	char* str,
	int x, int y, int z,
	float value
);

// Separate lines
void func(
	char* str,
	int x,
	int y,
	int z,
	float value
);
```
