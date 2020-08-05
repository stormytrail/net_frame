#include "layers/softmax_layer.h"

void SoftmaxLayer :: Forward(vector<Atom*>& input,vector<Atom*>& output){
	float* max_val = (float*)malloc(sizeof(float) * input[0]->shape_[0]);

	{
		//find max in softmax_range
		float* data = input[0]->data;
		for (size_t i = 0;i < input[0]->shape_[0];i++){
			max_val[i] = data[0];
			for (size_t j = 1;j < input[0]->shape_[1];j++){
				if (data[j] > max_val[i]){max_val[i] = data[j];}
			}
			data += input[0]->shape_[1];
		}
	}

	{
		//move input data to output
		size_t num_data = input[0]->shape_[0] * input[0]->shape_[1] * sizeof(float);
		memcpy(output[0]->data,input[0]->data,num_data);
	}

	{
		//minus max,to avoid e^x exceeding the float range
		float* data = output[0]->data;
		for (size_t i = 0;i < input[0]->shape_[0];i++){
			for (size_t j = 0;j < input[0]->shape_[1];j++){
				data[j] -= max_val[i];
			}
			data += input[0]->shape_[1];
		}
	}

	float* sum_row = (float*)malloc(sizeof(float) * input[0]->shape_[0]);
	memset(sum_row,0,sizeof(float) * input[0]->shape_[0]);
	{
		float* data = output[0]->data;
		for (size_t i = 0;i < input[0]->shape_[0];i++){
			for (size_t j = 0;j < input[0]->shape_[1];j++){
				data[j] = exp(data[j]);
				sum_row[i] += data[j];
			}
			data += input[0]->shape_[1];
		}

		data = output[0]->data;
		for (size_t i = 0;i < input[0]->shape_[0];i++){
			for (size_t j = 0;j < input[0]->shape_[1];j++){
				data[j] /= sum_row[i];
			}
			data += input[0]->shape_[1];
		}
	}

	free(max_val);
	free(sum_row);

	return;
}

void SoftmaxLayer :: Backward(vector<Atom*>& input,vector<Atom*>& output){

	size_t batch_size = input[0]->shape_[0];
	size_t num_dim = input[0]->shape_[1];

	float* softmax_diff_ = (float*)malloc(sizeof(float) * num_dim * num_dim);

	float* softmax_output = output[0]->data;
	float* grad_softmax_shifter = output[0]->diff_;
	float* grad_input_shifter = input[0]->diff_;

	for (size_t batch_index = 0;batch_index < batch_size;batch_index++){
		for (size_t i = 0;i < num_dim;i++){
			for (size_t j = 0;j < num_dim;j++){
				if (i == j){
					softmax_diff_[i * num_dim + j] = softmax_output[i] * (1 - softmax_output[i]);
				}
				else{
					softmax_diff_[i*num_dim+j]=0-softmax_output[i] * softmax_output[j];
				}
			}
		}

		{
			size_t M=1,N = num_dim,K=num_dim;
			float* A = grad_softmax_shifter;
			float* B = softmax_diff_;
			float* C = grad_input_shifter;

			c_sgemm(M,N,K,1,A,K,B,N,0,C,N);
		}

		softmax_output += num_dim;
		grad_softmax_shifter += num_dim;
		grad_input_shifter += num_dim;
	}
	free(softmax_diff_);
	return;
}

vector<vector<int> > SoftmaxLayer :: OutShape(const vector<vector<int> > input_shapes){
	vector<vector<int> > out_shape;
	out_shape.assign(input_shapes.begin(),input_shapes.end());
	return out_shape;
}
