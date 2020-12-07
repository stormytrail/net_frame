#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define N 1000

using namespace std;

template<typename T>
void showmatrix(T **a){
	for (int i = 0;i < N;i++){
		for (int j = 0;j < N;j++){
			cout << a[i][j] << " ";
		}cout << endl;
	}cout << endl;
	return;
}

template<typename T>
void genmatrix(T **&a){
	a = (T**)malloc(sizeof(T*) * N);
	for (int i = 0;i < N;i++){
		a[i] = (T*)malloc(sizeof(T) * N);
		for (int j = 0;j < N;j++){
			a[i][j] = rand() % 2000 - 1000;
		}
	}

	return;
}

template<typename T>
void mulmatrix(T **a,T **b,T **c){
	for (int i = 0;i < N;i++){
		for (int j = 0;j < N;j++){
			c[i][j] = 0;
			for (int k = 0;k < N;k++){
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return;
}

template<typename T1,typename T2>
void quanzation(int dim,T1** a,T2** ia,T2* za,T1* sa){

	for (int i = 0;i < N;i++){
		T1 min_val = 2000,max_val = -2000;
		for (int j = 0;j < N;j++){
			if (dim == 0){
				min_val = min(min_val,a[i][j]);
				max_val = max(max_val,a[i][j]);
			}
			else{
				min_val = min(min_val,a[j][i]);
				max_val = max(max_val,a[j][i]);
			}
		}
		sa[i] = (max_val - min_val) / (127 * 2);
		za[i] = (max_val / sa[i]) - 127;
		for (int j = 0;j < N;j++){
			if (dim == 0){
				ia[i][j] = a[i][j] / sa[i] - za[i];
			}
			else{
				ia[j][i] = a[j][i] / sa[i] - za[i];
			}
		}
	}
	return;
}

void int2float(int** ia,int* za,float* sa,int** ib,int* zb,float* sb,int **ic,float** c){
	for (int i = 0;i < N;i++){
		for (int j = 0;j < N;j++){
			float s = sa[i] * sb[j];
			for (int k = 0;k < N;k++){
				ic[i][j] = ic[i][j] - za[i] * ib[k][j] - zb[j] * ia[i][k] + za[i]*zb[j];
			}
			c[i][j] = s * ic[i][j];
		}
	}
	return;
}

template<typename T>
void showvector(T* a){
	for (int i = 0;i < N;i++){
		cout << a[i] << " ";
	}cout << endl;
	return;
}

void intmul(int** ia,int* za,float*sa,int**ib,int *zb,float*sb,float**c){
	for (int i = 0;i < N;i++){
		for (int j = 0;j < N;j++){
			c[i][j] = 0;
			for (int k = 0;k < N;k++){
				c[i][j] =  c[i][j] + (ia[i][k] * ib[k][j] - za[i]*ib[k][j] - zb[j]*ia[i][k] + za[i]*zb[j]);
			}
			c[i][j] = c[i][j] * sa[i] * sb[j];			


		}
	}
	return ;
}

int main(){
	float **a;
	float **b;
	float **c;

	genmatrix<float>(a);
	genmatrix<float>(b);
	genmatrix<float>(c);
//	cout << "a" << endl;
//	showmatrix(a);
//	cout << "b" << endl;
//	showmatrix(b);

	mulmatrix(a,b,c);
	cout << "c" << endl;
	showmatrix(c);
	
	int **ia,**ib,*za,*zb;
	float *sa,*sb;
	genmatrix<int>(ia);genmatrix(ib);
	za = (int*)malloc(sizeof(int) * N);
	zb = (int*)malloc(sizeof(int) * N);
	sa = (float*)malloc(sizeof(float) * N);
	sb = (float*)malloc(sizeof(float) * N);

	quanzation(0,a,ia,za,sa);
	quanzation(1,b,ib,zb,sb);

//	cout << endl << "ia" << endl;
//	showmatrix(ia);
//	showvector(za);
//	showvector(sa);
//	cout << endl;

//	cout << endl << "ib" << endl;
//	showmatrix(ib);
//	showvector(zb);
//	showvector(sb);
//	cout << endl;

	int **ic;
	genmatrix<int>(ic);
	mulmatrix(ia,ib,ic);

	cout << "ic" << endl;
//	showmatrix(ic);

	float **c2;
	genmatrix<float>(c2);
//	int2float(ia,za,sa,ib,zb,sb,ic,c2);
	intmul(ia,za,sa,ib,zb,sb,c2);

	cout << "c2" << endl;
	showmatrix(c2);
	return 0;
}
