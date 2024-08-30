#include <immintrin.h>
#include <math.h>
#include "Float64_AVX.h"


static inline __m256d _mm256_cbrt_pd(__m256d x) {
	double val[4];
	_mm256_store_pd(val, x);
	val[0] = cbrt(val[0]);
	val[1] = cbrt(val[1]);
	val[2] = cbrt(val[2]);
	val[3] = cbrt(val[3]);
	return _mm256_load_pd(val);
}