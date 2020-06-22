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
	cout << "xixi" << endl;
	return;
}
