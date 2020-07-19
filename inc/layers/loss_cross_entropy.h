#include "base_layer.h"
#pragma once
class CrossEntropyLayer : public BaseLayer{
public:

	//input[0] groundtruth;input[1] prediction
	//output[0] batch_size * 1
	virtual void Forward(vector<Atom*>& input,vector<Atom*>& output);
	virtual void Backward(vector<Atom*>& input,vector<Atom*>& output);

	CrossEntropyLayer(LayerParam *param):BaseLayer(param){
		return;
	}
};
