#include <iostream>
#include <sys/time.h>
#include "matrix_operation.h"

using namespace std;

void random_matrix(int m,int n,float* a){
	for (int i = 0;i < m;i++){
		for (int j = 0;j < n;j++){
			a[j] = 2 * (float)drand48() - 1.0;
		}
		a += n;
	}
	return;
}

void ascend_matrix(int m,int n,float* a){
	int counter = 0;
	for (int i = 0;i < m;i++){
		for (int j = 0;j < n;j++){
			a[j] = counter++;
		}
		a += n;
	}
	return;
}

bool compare_matrix(int m,int n,float* a,float* b){
	for (int i = 0;i < m;i++){
		for (int j = 0;j < n;j++){
			float gap = a[i * n + j] - b[i * n + j];
			gap = gap < 0 ? 0 - gap : gap;
			if (gap > 0.1){
				return false;
			}
		}
	}
	return true;
}

void print_matrix(int m,int n,float* a){
	for (int i = 0;i < m;i++){
		for (int j = 0;j < n;j++){
			printf("%03.1f ",a[j]);
		}printf("\n");
		a += n;
	}
	return;
}

int main(){

	int m,n,k;
	int repeat_time = 20;
	int range_low = 50,range_high = 600,stride = 50;

	double gflops;

	m = n = k = 20;
	float *a = (float*)malloc(sizeof(float) * m * k);
	float *b = (float*)malloc(sizeof(float) * k * n);
	float *c = (float*)malloc(sizeof(float) * m * n);

	random_matrix(m,k,a);
	random_matrix(k,n,b);

	common_c_sgemm(m,n,k,1,a,m,b,k,0,c,m);

	float *c_compare = (float*)malloc(sizeof(float) * m * n);

	c_sgemm(m,n,k,1,a,m,b,k,0,c_compare,m);

	bool same = compare_matrix(m,n,c,c_compare);

	printf("%s\n",same ? "correct" : "wrong");

	return 0;
}
