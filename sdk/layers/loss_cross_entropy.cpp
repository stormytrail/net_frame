#include "layers/loss_cross_entropy.h"

void CrossEntropyLayer :: Forward(const vector<Atom>& input,vector<Atom>& output){
	float* ground_truth = input[0].data;
	float* predict = input[1].data;
	for (size_t i = 0;i < input[0].shape_[0];i++){
		output[0].data_[i] = 0;
		for (size_t j = 0;j < input[0].shape_[1];j++){
			output[0].data_[i] += ground_truth[j] * log(predict[j]);
		}
		ground_truth += input[0].shape_[1];
		predict += input[0].shape_[1];
	}

	return;
}

void CrossEntropyLayer :: Backward(const vector<Atom>& input,const vector<Atom>& output){
	for (size_t i = 0;i < ;i++){
		for (size_t j = 0;j < ;j++){

		}
	}

	return;
}
