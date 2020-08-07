#include "matrix_operation.h"

#include <iostream>
using namespace std;

void matrix_transpose(const float* src,size_t M,size_t N,float* dest){
	for (size_t i = 0;i < M;i++){
		for (size_t j = 0;j < N;j++){
			dest[j * M + i] = src[i * N + j];
		}
	}
	return;
}

void c_sgemm(size_t M,size_t N,size_t K,float alpha,float* A,size_t lda,float* B,size_t ldb,float beta,float* C,size_t ldc){

	int i,j,k;
	float* col_a = (float*)malloc(sizeof(float) * M);
	float* row_b = (float*)malloc(sizeof(float) * N);

	float* pa,*pb,*pc;

	pc = C;
	for(i = 0;i < M;i++){
		for (j = 0;j < N;j++){
			pc[j] = pc[j] * beta;
		}
		pc = pc + N;
	}

	for (i = 0;i < K;i++){
		pc = C;
		pa = A + i;
		pb = B + i * N;
		for (j = 0;j < M;j++){
			col_a[j] = *pa;
			pa += K;
		}
		for (j = 0;j < N;j++){
			row_b[j] = pb[j];
		}

		for (j = 0;j < M;j++){
			for (k = 0;k < N;k++){
				pc[k] = pc[k] + col_a[j] * row_b[k];
			}
			pc += N;
		}
	}


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
