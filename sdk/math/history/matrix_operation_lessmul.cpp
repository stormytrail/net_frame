#include "matrix_operation.h"

void matrix_transpose(const float* src,size_t M,size_t N,float* dest){
	for (size_t i = 0;i < M;i++){
		for (size_t j = 0;j < N;j++){
			dest[j * M + i] = src[i * N + j];
		}
	}
	return;
}
/*
void c_sgemm(size_t M,size_t N,size_t K,float alpha,float* A,size_t lda,float* B,size_t ldb,float beta,float* C,size_t ldc){
	for (size_t i = 0;i < M;i++){
		for (size_t j = 0;j < N;j++){
			C[j] *= beta;
			int pos = j;
			for (size_t k = 0;k < K;k++){
				C[j] += A[k] * B[pos];
				pos += N;
			}
		}
		C = C + N;
		A = A + K;
	}

	return;
}
*/


void c_sgemm(size_t M,size_t N,size_t K,float alpha,float* A,size_t lda,float* B,size_t ldb,float beta,float* C,size_t ldc){

	float* col_b = (float*)malloc(sizeof(float) * K);
	size_t counter;
	size_t c_counter;
	size_t i,j,k;
	float* a;

	for (j = 0;j < N;j++){
		counter = j;		
		for (i = 0;i < K;i++){
			col_b[i] = B[counter];
			counter += N;
		}
		a = A;

		c_counter = j;
		for (i = 0;i < M;i++){
			C[c_counter] *= beta;
			for (k = 0;k < K;k++){
				C[c_counter] += a[k] * col_b[k];
			}
			a += K;
			c_counter += N;
		}
	}
	free(col_b);
	return;
}

