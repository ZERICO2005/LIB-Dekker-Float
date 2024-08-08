# Unsure on what the true minimum actually is
cmake_minimum_required(VERSION 3.12)

set(SRC_DIR "./src")
set(INCLUDE_DIR "./include")

set(PROJECT_NAME "Dekker-Float-Test")
project(${PROJECT_NAME})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

### Configuration ###

	# x87 __float80 (long double)
#	set(FEATURE_Float80       "")

	# GCC quadmath __float128
#	set(FEATURE_Float128      "")
	
	# MPFR converts between dekker-floats and strings
#	set(FEATURE_FloatMPFR     "")

# Compiling
	set(CMAKE_C_COMPILER "gcc")
	set(CMAKE_CXX_COMPILER "g++")

# Set C and C++ standards
	set(CMAKE_C_STANDARD 99)
	set(CMAKE_CXX_STANDARD 11)

# Compiler Flags
	set(OPT_FLAG -O2)
	set(MARCH_FLAGS -msse2)

# Source Files
	file(GLOB_RECURSE SRC_FILES
		"${SRC_DIR}/*.c" "${SRC_DIR}/*.cpp"
	)

	add_executable(${PROJECT_NAME} ${SRC_FILES})

# Packages and Macros
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
		-Wall -Wextra -Wshadow
		# Add extra warnings below

	)
	set(WARNING_IGNORE_FLAGS
		# Supress extra warnings below

	)

	set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}  ")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

	target_compile_options(${PROJECT_NAME} PRIVATE
		${OPT_FLAG} ${MARCH_FLAGS}
		${WARNING_FLAGS} ${WARNING_IGNORE_FLAGS}
	)

	target_link_libraries(${PROJECT_NAME} PRIVATE
		${LIB_QuadMath}
		${LIB_MPFR}
	)
