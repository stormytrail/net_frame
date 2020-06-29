#include "layers/inner_product_layer.h"

void InnerProductLayer :: Forward(const vector<Atom>& input,vector<Atom>& output){
	{
		//affine
		size_t M = input[0].shape_[0];
		size_t K = this->atoms_[0].shape_[0];
		size_t N = this->atoms_[0].shape_[1];
		c_sgemm(M,N,K,1.0,input[0].data,M,this->atoms_[0].data,K,0.,output[0].data,M);
	}

	return;
}
void InnerProductLayer :: Backward(const vector<Atom>& input,const vector<Atom>& output){
	size_t batch_size = input[0].shape_[0];

	//w
	{
		float* x_trans = (float*)malloc(sizeof(float) * );
		for (size_t i = 0;i < input[0].shape_[0];i++){
			for (size_t j = 0;j < inpus[0].shape_[1];j++){
				x_trans[j * input[0].shape_[0] + i] = input[0].data[i * inpus[0].shape_[1] + j];
			}
		}

		//xT * e
		size_t M = input[0].shape_[1],K = input[0].shape_[0],N = output[0].shape_[1];
		float *A = x_trans,*B = output[0].diff_,*C = this->atoms_[0].diff_;
		c_sgemm(M,N,K,1,A,K,B,N,0,C,N);

		free(x_trans);
	}
	
	//x
	{
		float* w_trans = (float*)malloc(sizeof(float) * * );
		for (size_t i = 0;i < this->atoms[0].shape_[0];i++){
			for (size_t j = 0;j < this->atoms[0].shape_[1];j++){
				w_trans[j * this->atoms[0].shape_[0] + i] = this->atoms[0].data[i * this->atoms[0].shape_[1]];
			}
		}

		//e * wT
		size_t M = output[0].shape_[0],K = output[0].shape_[1],N = this->atoms[0].shape_[1];
		float *A = output[0].diff_,*B = w_trans,*C = input[0].diff_;
		c_sgemm(M,N,K,1,A,K,B,N,0,C,N);

		free(w_trans);
	}
	return;
}
