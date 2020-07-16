#include "base_layer.h"
#pragma once
class CrossEntropyLayer : public BaseLayer{
public:

	//input[0] groundtruth;input[1] prediction
	//output[0] batch_size * 1
	virtual void Forward(const vector<Atom*>& input,const vector<Atom*>& output);
	virtual void Backward(const vector<Atom*>& input,const vector<Atom*>& output);

	explicit CrossEntropyLayer(LayerParam *param):BaseLayer(param){
		return;
	}
};
