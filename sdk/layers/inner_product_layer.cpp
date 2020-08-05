#include "layers/inner_product_layer.h"

void InnerProductLayer :: Forward(vector<Atom*>& input,vector<Atom*>& output){
	{
		//affine
		size_t M = input[0]->shape_[0];
		size_t K = this->atoms_[0]->shape_[0];
		size_t N = this->atoms_[0]->shape_[1];
		c_sgemm(M,N,K,1.0,input[0]->data,M,this->atoms_[0]->data,K,0.,output[0]->data,M);
	}

	return;
}
void InnerProductLayer :: Backward(vector<Atom*>& input,vector<Atom*>& output){
	size_t batch_size = input[0]->shape_[0];

	//w
	{
		float* x_trans = (float*)malloc(sizeof(float) * input[0]->count_);
		matrix_transpose(input[0]->data,input[0]->shape_[0],input[0]->shape_[1],x_trans);

		//xT * e
		size_t M = input[0]->shape_[1],K = input[0]->shape_[0],N = output[0]->shape_[1];
		float *A = x_trans,*B = output[0]->diff_,*C = atoms_[0]->diff_;
		c_sgemm(M,N,K,1,A,K,B,N,0,C,N);

		free(x_trans);
	}

	//x
	{
		float* w_trans = (float*)malloc(sizeof(float) * this->atoms_[0]->count_);
		matrix_transpose(atoms_[0]->data,atoms_[0]->shape_[0],atoms_[0]->shape_[1],w_trans);

		//e * wT
		size_t M = output[0]->shape_[0],K = output[0]->shape_[1],N = this->atoms_[0]->shape_[1];
		float *A = output[0]->diff_,*B = w_trans,*C = input[0]->diff_;

		c_sgemm(M,N,K,1,A,K,B,N,0,C,N);


		free(w_trans);
	}

	return;
}

vector<vector<int>> InnerProductLayer::OutShape(const vector<vector<int>> input_shape){
	int batch_size = input_shape[0][0];
	int out_dim = atoms_[0]->shape_[1];
	vector<vector<int> > out_shape = vector<vector<int>>{vector<int>{batch_size,out_dim}};
	return out_shape;
}
