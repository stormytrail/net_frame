#include "matrix_operation.h"

void matrix_transpose(const float* src,size_t M,size_t N,float* dest){
	for (size_t i = 0;i < M;i++){
		for (size_t j = 0;j < N;j++){
			dest[j * M + i] = src[i * N + j];
		}
	}
	return;
}

void InnerKernel(int m,int n,int k,float* A,int lda,float* B,int ldb,float* C,int ldc);
void AddDot4x4(int k,float* A,int lda,float* B,int ldb,float* C,int ldc);

void PackMatrixB(int k,float* b,int ldb,float* b_to);

#define min(a,b) ((a < b) ? (a) : (b) )

void c_sgemm(size_t M,size_t N,size_t K,float alpha,float* A,size_t lda,float* B,size_t ldb,float beta,float* C,size_t ldc){
	int i,j,p;
	int pb,ib;

	float *a,*b,*c;
	b = B;
	for (p = 0;p < K;p+=kc){
		pb = min(K - p,kc);
		a = A + p;
		c = C;

		for (i = 0;i < M;i += mc){
			ib = min(M - i,mc);

			a = A + (i * lda + p);
			b = B + (p * ldb);
			c = C + (i * ldc);
			InnerKernel(ib,N,pb,a,lda,b,ldb,c,ldc);
			a+=lda;
			c += ldc;
		}
		b+=ldb;

	}
	return;
}

void PackMatrixB(int k,float* b,int ldb,float* b_to){
	int p;

	int index_from = 0;
	int index_to = 0;

	int num_copy = sizeof(float) * 4;

	for (p = 0;p < k;p++){
		memcpy(&b_to[index_to],&b[index_from],num_copy);
		index_from += ldb;
		index_to += 4;
	}

	return;
}

void InnerKernel(int m,int n,int k,float* A,int lda,float* B,int ldb,float* C,int ldc){

	int i,j;
	float packageB[k * 4];

	float* pb = B;

	for (j = 0;j < n;j+=4){
		PackMatrixB(k,pb,ldb,packageB);

		for (i = 0;i < m;i+=4){
			AddDot4x4(k,A+i*lda,lda,packageB,4,C + i*ldc+j,ldc);
		}
		pb += 4;

	}
	return;
}

#include <mmintrin.h>
#include <xmmintrin.h>  // SSE
#include <pmmintrin.h>  // SSE2
#include <emmintrin.h>  // SSE3

void AddDot4x4(int k,float* A,int lda,float* B,int ldb,float* C,int ldc){

	__m128 c_p0_sum,c_p1_sum,c_p2_sum,c_p3_sum;
	__m128 a_0p,a_1p,a_2p,a_3p;
	__m128 b_p;

	float *pa = A,*pb = B,*pc = C;
	//init
	c_p0_sum = _mm_load_ps(pc);
	c_p1_sum = _mm_load_ps(pc + ldc);
	c_p2_sum = _mm_load_ps(pc + 2 * ldc);
	c_p3_sum = _mm_load_ps(pc + 3 * ldc);

	int p;
	for (p = 0;p < k;p++){
		a_0p = _mm_load1_ps(pa);
		a_1p = _mm_load1_ps(pa + lda);
		a_2p = _mm_load1_ps(pa + 2 * lda);
		a_3p = _mm_load1_ps(pa + 3 * lda);

		b_p = _mm_load_ps(pb);

		c_p0_sum += a_0p * b_p;
		c_p1_sum += a_1p * b_p;
		c_p2_sum += a_2p * b_p;
		c_p3_sum += a_3p * b_p;

		pa = pa + 1;
		pb = pb + ldb;

	}
	_mm_storeu_ps(pc,c_p0_sum);
	_mm_storeu_ps(pc + ldc,c_p1_sum);
	_mm_storeu_ps(pc + 2 * ldc,c_p2_sum);
	_mm_storeu_ps(pc + 3 * ldc,c_p3_sum);


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
