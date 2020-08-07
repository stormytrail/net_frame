#include "matrix_operation.h"

int ms = 4,ns = 4,ks = 4;

void matrix_transpose(const float* src,size_t M,size_t N,float* dest){
	for (size_t i = 0;i < M;i++){
		for (size_t j = 0;j < N;j++){
			dest[j * M + i] = src[i * N + j];
		}
	}
	return;
}

void micro_matrix(float* from,size_t M,size_t N,size_t mi,size_t ni,size_t ms,size_t ns,float* to){

	from += mi * N + ni;
	for (int i = 0;i < ms;i++){
		memcpy(to,from,sizeof(float) * ns);
		to += ns;
		from += N;
	}

	return;
}

void 




void c_sgemm(size_t M,size_t N,size_t K,float alpha,float* A,size_t lda,float* B,size_t ldb,float beta,float* C,size_t ldc){

	int mi,ni,ki;

	float* micro_a = (float*)malloc(sizeof(float) * ks * ms);
	float* micro_b = (float*)malloc(sizeof(float) * ks * ns);

	for (ki = 0;ki < K;ki+=ks){
		//A按照ks划分
		for (int ni = 0;ni < N;ni += ns){
			//Bi按照ns划分
			//(ki,ni)
			micro_matrix(B,K,N,ki,ni,ks,ns,micro_b);

			for (mi = 0;mi < M;mi += ms){
				//Ai按照ms划分
				//(mi,ki)
				micro_matrix(A,M,K,mi,ki,ms,ks,micro_a);

			}
		}
	}	

	return;
}
