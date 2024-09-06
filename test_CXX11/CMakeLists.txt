# Unsure on what the true minimum actually is
cmake_minimum_required(VERSION 3.12)

set(SRC_DIR "./src")
set(INCLUDE_DIR "./include")

set(PROJECT_NAME "Dekker-Float-Test")
project(${PROJECT_NAME})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

### Configuration ###

	# x87 __float80 (long double)
	set(FEATURE_Float80       "")

	# GCC quadmath __float128
#	set(FEATURE_Float128      "")
	
	# MPFR converts between dekker-floats and strings
	set(FEATURE_FloatMPFR     "")

	# Enable if your terminal supports color
	set(FEATURE_ColorDiagnostics "")

# Compiling
	set(CMAKE_C_COMPILER "gcc")
	set(CMAKE_CXX_COMPILER "g++")

# Set C and C++ standards
	set(CMAKE_C_STANDARD 99)
	set(CMAKE_CXX_STANDARD 11)

# Compiler Flags
	set(OPT_FLAG -O3)
	set(MARCH_FLAGS -msse2 -mavx)

# Source Files
	file(GLOB_RECURSE SRC_FILES
		"${SRC_DIR}/*.c" "${SRC_DIR}/*.cpp"
		"${SRC_DIR}/../../Float32/*.c" "${SRC_DIR}/../../Float32/*.cpp"
		"${SRC_DIR}/../../Float64/*.c" "${SRC_DIR}/../../Float64/*.cpp"
		"${SRC_DIR}/../../Float32x2/*.c" "${SRC_DIR}/../../Float32x2/*.cpp"
		"${SRC_DIR}/../../Float64x2/*.c" "${SRC_DIR}/../../Float64x2/*.cpp"
		"${SRC_DIR}/../../Float64x4/*.c" "${SRC_DIR}/../../Float64x4/*.cpp"
		"${SRC_DIR}/../../Float80x2/*.c" "${SRC_DIR}/../../Float80x2/*.cpp"
	)

	add_executable(${PROJECT_NAME} ${SRC_FILES})

# Packages and Macros
	if(DEFINED FEATURE_ColorDiagnostics)
		set(FLAG_ColorDiagnostics "-fdiagnostics-color=always")
	else()
		set(FLAG_ColorDiagnostics "")
	endif()

	if(DEFINED FEATURE_Float80)
		target_compile_definitions(${PROJECT_NAME} PRIVATE Enable_Float80)
	endif()

	if(DEFINED FEATURE_Float128)
		set(LIB_QuadMath "quadmath")
		target_compile_definitions(${PROJECT_NAME} PRIVATE Enable_Float128)
	else()
		set(LIB_QuadMath "")
	endif()

	if(DEFINED FEATURE_FloatMPFR)
		set(LIB_MPFR "-lmpfr -lgmp")
		target_compile_definitions(${PROJECT_NAME} PRIVATE Enable_FloatMPFR)
	else()
		set(LIB_MPFR "")
	endif()

# Compile Options

	set(WARNING_FLAGS
		-Wall -Wextra -Wpedantic -Wshadow
		-Wfloat-conversion
		-Wconversion
		-Wformat=2
		-Winfinite-recursion
		-Wunreachable-code
		# Add extra warnings below
	)
	set(WARNING_IGNORE_FLAGS
		# Supress extra warnings below
		-Wno-c++17-extensions
	)

	set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   ${FLAG_ColorDiagnostics}")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAG_ColorDiagnostics}")

	include_directories(SYSTEM "./../")

	target_compile_options(${PROJECT_NAME} PRIVATE
		${OPT_FLAG} ${MARCH_FLAGS}
		${FLAG_ColorDiagnostics}
		${WARNING_FLAGS} ${WARNING_IGNORE_FLAGS}
	)

	target_link_libraries(${PROJECT_NAME} PRIVATE
		${LIB_QuadMath}
		${LIB_MPFR}
	)
