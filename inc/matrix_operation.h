#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <string>
#include <map>
#include <math.h>

#define mc 256
#define kc 128

void matrix_transpose(const float* src,size_t M,size_t N,float* dest);

void c_sgemm(size_t M,size_t N,size_t K,float alpha,float* A,size_t lda,float* B,size_t ldb,float beta,float* C,size_t ldc);

void common_c_sgemm(size_t M,size_t N,size_t K,float alpha,float* A,size_t lda,float* B,size_t ldb,float beta,float* C,size_t ldc);


void micro_matrix(float* from,size_t M,size_t N,size_t mi,size_t ni,size_t ms,size_t ns,float* to);
