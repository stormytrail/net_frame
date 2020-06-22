#include "layers/softmax_layer.h"

void SoftmaxLayer :: Forward(const vector<Atom>& input,vector<Atom>& output){
	float* max_val = (float*)malloc(sizeof(float) * input[0].shape_[0]);

	{
		float* data = input[0].data;
		for (size_t i = 0;i < input[0].shape_[0];i++){
			max_val[i] = data[0];
			for (size_t j = 1;j < input[0].shape_[1];j++){
				if (data[j] > max_val[i]){max_val[i] = data[j];}
			}
			data += input[0].shape_[1];
		}
	}

	{
		size_t num_data = input[0].shape_[0] * input[0].shape_[1];
		memcpy(output[0].data,input[0].data,num_data);
	}

	{
		float* data = output[0].data;
		for (size_t i = 0;i < input[0].shape_[0];i++){
			for (size_t j = 0;j < input[0].shape_[1];j++){
				data[j] -= max_val[i];
			}
			data += input[0].shape_[1];
		}
	}

	float* sum_row = (float*)molloc(sizeof(float) * input[0].shape_[0]);
	memset(sum_row,0,sizeof(float) * input[0].shape_[0]);
	{
		float* data = output[0].data;
		for (size_t i = 0;i < input[0].shape_[0];i++){
			for (size_t j = 0;j < input[0].shape_[1];j++){
				data[j] = exp(data[j]);
				sum_row[i] += data[j];
			}
			data += input[0].shape_[1];
		}

		data = output[0].data;
		for (size_t i = 0;i < input[0].shape_[0];i++){
			for (size_t j = 0;j < input[0].shape_[1];j++){
				data[j] /= sum_row[i];
			}
			data += input[0].shape_[1];
		}
	}

	free(max_val);
	free(sum_row);

	return;
}

void Backward(const vector<Atom>& input,const vector<Atom>& output){

	return;
}
