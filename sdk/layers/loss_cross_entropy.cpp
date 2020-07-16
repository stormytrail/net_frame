#include "layers/loss_cross_entropy.h"

void CrossEntropyLayer :: Forward(const vector<Atom*>& input,const vector<Atom*>& output){
	float* ground_truth = input[0]->data;
	float* predict = input[1]->data;
	for (size_t i = 0;i < input[0]->shape_[0];i++){
		output[0]->data[i] = 0;
		for (size_t j = 0;j < input[0]->shape_[1];j++){
			output[0]->data_[i] += ground_truth[j] * log(predict[j]);
		}
		output[0]->data[i] = 0 - output[0]->data_[i];

		ground_truth += input[0]->shape_[1];
		predict += input[0]->shape_[1];
	}

	return;
}

void CrossEntropyLayer :: Backward(const vector<Atom*>& input,const vector<Atom*>& output){

	float *diff = input[1]->diff_;

	float *ground_truth = input[0]->data;
	float *predict = input[1]->data;

	int NUM_CLASS = input[0]->shape_[1];

	for (size_t i = 0;i < input[0]->shape_[0];i++){
		for (size_t j = 0;j < input[0]->shape_[1];j++){
			diff[j] = 0 - ground_truth[j] / predict[j];
		}
		diff += NUM_CLASS;
		ground_truth += NUM_CLASS;
		predict += NUM_CLASS;
	}

	return;
}
