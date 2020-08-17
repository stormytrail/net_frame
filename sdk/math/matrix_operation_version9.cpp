#include "matrix_operation.h"

void matrix_transpose(const float* src,size_t M,size_t N,float* dest){
	for (size_t i = 0;i < M;i++){
		for (size_t j = 0;j < N;j++){
			dest[j * M + i] = src[i * N + j];
		}
	}
	return;
}

void AddDot4x4(int M,int N,int K,float *A,int p_m,float *B,int p_n,float *C);

void c_sgemm(size_t M,size_t N,size_t K,float alpha,float* A,size_t lda,float* B,size_t ldb,float beta,float* C,size_t ldc){
	int i,j;
	int cm,cn;
	for (j = 0;j < N;j+=4){
		for (i = 0;i < M;i+= 4){
			AddDot4x4(M,N,K,A,i,B,j,C);
		}
	}
	return;
}

#include <mmintrin.h>
#include <xmmintrin.h>  // SSE
#include <pmmintrin.h>  // SSE2
#include <emmintrin.h>  // SSE3

void AddDot4x4(int M,int N,int K,float *A,int p_m,float *B,int p_n,float *C){
	int p;

	__m128 c_p0_sum,c_p1_sum,c_p2_sum,c_p3_sum;
	__m128 a_0p,a_1p,a_2p,a_3p;
	__m128 b_p;

	//init
	c_p0_sum = _mm_setzero_ps();
	c_p1_sum = _mm_setzero_ps();
	c_p2_sum = _mm_setzero_ps();
	c_p3_sum = _mm_setzero_ps();

	float* pa = A + (K * p_m);
	float* pb = B + p_n;
	float* pc = C + (N * p_m) + p_n;

	for (p = 0;p < K;p++){
		a_0p = _mm_load1_ps(pa);
		a_1p = _mm_load1_ps(pa + K);
		a_2p = _mm_load1_ps(pa + 2 * K);
		a_3p = _mm_load1_ps(pa + 3 * K);

		b_p = _mm_load_ps(pb);

		c_p0_sum += a_0p * b_p;
		c_p1_sum += a_1p * b_p;
		c_p2_sum += a_2p * b_p;
		c_p3_sum += a_3p * b_p;

		pa = pa + 1;
		pb = pb + N;
	}

	_mm_storeu_ps(pc,c_p0_sum);
	_mm_storeu_ps(pc + N,c_p1_sum);
	_mm_storeu_ps(pc + 2 * N,c_p2_sum);
	_mm_storeu_ps(pc + 3 * N,c_p3_sum);

	return;
}


void common_c_sgemm(size_t M,size_t N,size_t K,float alpha,float* A,size_t lda,float* B,size_t ldb,float beta,float* C,size_t ldc){
	for (size_t i = 0;i < M;i++){
		for (size_t j = 0;j < N;j++){
			C[i * N + j] *= beta;
			for (size_t k = 0;k < K;k++){
				C[i * N + j] += A[i * K + k] * B[k * N + j];
			}
		}
	}

	return;
}
