#include "layers/softmax_layer.h"

void SoftmaxLayer :: Forward(const Atom& input,Atom& output){


	float* max_val = (float*)malloc(sizeof(float) * input.shape_[0]);

	{
		float* data = input.data;
		for (size_t i = 0;i < input.shape_[0];i++){
			max_val[i] = data[0];
			for (size_t j = 1;j < input.shape_[1];j++){
				if (data[j] > max_val[i]){max_val[i] = data[j];}
			}
			data += input.shape_[1];
		}
	}

	{
		size_t num_data = input.shape_[0] * input.shape_[1];
		memcpy(output.data,input.data,num_data);
	}

	{
		float* data = output.data;
		for (size_t i = 0;i < input.shape_[0];i++){
			for (size_t j = 0;j < input.shape_[1];j++){
				data[j] -= max_val[i];
			}
			data += input.shape_[1];
		}
	}

	free(max_val);

	return;
}

void Backward(const Atom& input,const Atom& output){

	return;
}
