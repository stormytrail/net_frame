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

void AddDot4x4(int M,int N,int K,float *A,int p_m,float *B,int p_n,float *C){
	int p;
	register float 
		c_00_reg,  c_01_reg,  c_02_reg,  c_03_reg,
		c_10_reg,  c_11_reg,  c_12_reg,  c_13_reg,
		c_20_reg,  c_21_reg,  c_22_reg,  c_23_reg,
		c_30_reg,  c_31_reg,  c_32_reg,  c_33_reg;
	register float
		a_0p_reg,  a_1p_reg,  a_2p_reg,  a_3p_reg;
	register float
		b_p0_reg,  b_p1_reg,  b_p2_reg,  b_p3_reg;

	//init
	c_00_reg=0.0;  c_01_reg=0.0;  c_02_reg=0.0;  c_03_reg=0.0;
	c_10_reg=0.0;  c_11_reg=0.0;  c_12_reg=0.0;  c_13_reg=0.0;
	c_20_reg=0.0;  c_21_reg=0.0;  c_22_reg=0.0;  c_23_reg=0.0;
	c_30_reg=0.0;  c_31_reg=0.0;  c_32_reg=0.0;  c_33_reg=0.0;

	float* pa = A + (K * p_m);
	float* pb = B + p_n;
	float* pc = C + (N * p_m) + p_n;

	for (p = 0;p < K;p++){
		a_0p_reg = *(pa);a_1p_reg = *(pa + K);a_2p_reg = *(pa + 2 * K);a_3p_reg = *(pa + 3 * K);

		b_p0_reg = *pb;b_p1_reg = *(pb+1);b_p2_reg = *(pb+2);b_p3_reg = *(pb+3);

//		printf("%.1f %.1f %.1f %.1f\n",*pa,*(pa+K),*(pa+2*K),*(pa+3*K));
//		printf("%.1f %.1f %.1f %.1f\n",*pb,*(pb+1),*(pb+2),*(pb+3));

//		printf("\n");

		c_00_reg += a_0p_reg * b_p0_reg;
		c_01_reg += a_0p_reg * b_p1_reg;
		c_02_reg += a_0p_reg * b_p2_reg;
		c_03_reg += a_0p_reg * b_p3_reg;

		c_10_reg += a_1p_reg * b_p0_reg;
		c_11_reg += a_1p_reg * b_p1_reg;
		c_12_reg += a_1p_reg * b_p2_reg;
		c_13_reg += a_1p_reg * b_p3_reg;

		c_20_reg += a_2p_reg * b_p0_reg;
		c_21_reg += a_2p_reg * b_p1_reg;
		c_22_reg += a_2p_reg * b_p2_reg;
		c_23_reg += a_2p_reg * b_p3_reg;

		c_30_reg += a_3p_reg * b_p0_reg;
		c_31_reg += a_3p_reg * b_p1_reg;
		c_32_reg += a_3p_reg * b_p2_reg;
		c_33_reg += a_3p_reg * b_p3_reg;

		pa = pa + 1;
		pb = pb +  N;
	}


//	exit(0);
	
	*(pc) = c_00_reg;  *(pc + 1) = c_01_reg;  *(pc + 2) = c_02_reg;  *(pc + 3) = c_03_reg;
	pc += N;

	*(pc) = c_10_reg;  *(pc + 1) = c_11_reg;  *(pc + 2) = c_12_reg;  *(pc + 3) = c_13_reg;
	pc += N;

	*(pc) = c_20_reg;  *(pc + 1) = c_21_reg;  *(pc + 2) = c_22_reg;  *(pc + 3) = c_23_reg;
	pc += N;

	*(pc) = c_30_reg;  *(pc + 1) = c_31_reg;  *(pc + 2) = c_32_reg;  *(pc + 3) = c_33_reg;

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
