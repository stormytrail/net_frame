#include "layers/inner_product_layer.h"

void InnerProductLayer :: Forward(const Atom& input,Atom& output){
	{
		//affine
		size_t M = input.shape_[0];
		size_t K = this->atoms_[0].shape_[0];
		size_t N = this->atoms_[0].shape_[1];
		c_sgemm(M,N,K,1.0,input.data,M,this->atoms_[0].data,K,0.,output.data,M);
	}

	return;
}
void InnerProductLayer :: Backward(const Atom& input,const Atom& output){
	cout << "xixi" << endl;
	return;
}
