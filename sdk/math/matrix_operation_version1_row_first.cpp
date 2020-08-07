#include "matrix_operation.h"

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

	float *pc = C;
	float *pa = A,*pb = B;
	int ks = 4,kt = K / ks,k_res = K % ks;
	int k_loop_max = kt * ks;

	float *c_buffer = (float*)malloc(sizeof(float) * ks);

	int pb_index;
	for (i = 0;i < M;i++){
		for (j = 0;j < N;j++){
			pc[j] = beta * pc[j];

			pb_index = j;
			for (k = 0;k < k_loop_max;k+= ks){
				c_buffer[0] = pa[k] * pb[pb_index];
				c_buffer[1] = pa[k+1] * pb[pb_index + N];
				c_buffer[2] = pa[k+2] * pb[pb_index + 2 * N];
				c_buffer[3] = pa[k+3] * pb[pb_index + 3* N];
				pc[j] = c_buffer[0] + c_buffer[1] + c_buffer[2] + c_buffer[3] + pc[j];
				pb_index += 4 * N;
			}
			for (k = k_loop_max;k < K;k++){
				pc[j] = pc[j] + pa[k] * pb[pb_index];
				pb_index += N;
			}
		}
		pc += N;
		pa += K;
	}

	free(c_buffer);
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
