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

	float *pc,*pa,*pb;
	int ks = 4,kt = K / ks,k_res = K % ks;
	int k_loop_max = kt * ks;

	float *c_buffer = (float*)malloc(sizeof(float) * ks);
	float *b_buffer = (float*)malloc(sizeof(float) * K);

	int pb_index,pc_index;

	pb = B;
	pc = C;
	for (j = 0;j < N;j++){
		pb_index = j;
		for (k = 0;k < k_loop_max;k+=ks){
			b_buffer[k] = pb[pb_index];
			b_buffer[k+1] = pb[pb_index + N];
			b_buffer[k+2] = pb[pb_index + 2 * N];
			b_buffer[k+3] = pb[pb_index + 3 * N];
			pb_index += 4 * N;
		}
		for (k = k_loop_max;k < K;k++){
			b_buffer[k] = pb[pb_index];
			pb_index += N;
		}

		pc_index = j;

		pa = A;
		for (i = 0;i < M;i++){
			for (k = 0;k < k_loop_max;k+=ks){
				c_buffer[0] = pa[k] * b_buffer[k];
				c_buffer[1] = pa[k+1]*b_buffer[k+1];
				c_buffer[2] = pa[k+2]*b_buffer[k+2];
				c_buffer[3] = pa[k+3] * b_buffer[k+3];
				pc[pc_index] = c_buffer[0] + c_buffer[1] + c_buffer[2] + c_buffer[3] + pc[pc_index];
			}
			for (k = k_loop_max;k < K;k++){
				pc[pc_index] = pc[pc_index] + pa[k] * b_buffer[k];
			}
			pa = pa + K;
			pc_index += N;
		}
	}

	free(b_buffer);free(c_buffer);

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
