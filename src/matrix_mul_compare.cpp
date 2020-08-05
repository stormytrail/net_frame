#include <iostream>
#include <sys/time.h>
#include "matrix_operation.h"

double get_time(){
	struct timeval cur;
	gettimeofday(&cur,NULL);
	double ans = cur.tv_sec + 1.0e-6 * cur.tv_usec;
	return ans;
}

void random_matrix(int m,int n,float* a){
	for (int i = 0;i < m;i++){
		for (int j = 0;j < n;j++){
			a[j] = 2 * (float)drand48() - 1.0;
		}
		a += n;
	}
	return;
}

void print_matrix(int m,int n,float* a){
	for (int i = 0;i < m;i++){
		for (int j = 0;j < n;j++){
			printf("%.5f ",a[j]);
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

	for (int i = range_low;i <= range_high;i += stride){
		m = n = k = i;
		float *a = (float*)malloc(sizeof(float) * m * k);
		float *b = (float*)malloc(sizeof(float) * k * n);
		float *c = (float*)malloc(sizeof(float) * m * n);

		gflops = 2.0 * m * n * k * 1.0e-09;

		double time_best;
		double start_time,end_time,duration;
		for (int rep = 0;rep < repeat_time;rep++){
			start_time = get_time();
			c_sgemm(m,n,k,1,a,m,b,k,0,c,m);
			end_time = get_time();
			duration = end_time - start_time;

			if (rep == 0){
				time_best = duration;
			}
			else{
				time_best = time_best < duration ? time_best : duration;
			}
		}
		printf("%d %lf %lf\n",i,gflops / time_best,time_best);
		free(a);free(b);free(c);
	}

	return 0;
}
