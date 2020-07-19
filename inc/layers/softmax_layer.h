#include "base_layer.h"

#pragma once
class SoftmaxLayer : public BaseLayer{
public:
	virtual void Forward(vector<Atom*>& input,vector<Atom*>& output);
	virtual void Backward(vector<Atom*>& input,vector<Atom*>& output);

	explicit SoftmaxLayer(LayerParam* param):BaseLayer(param){
		return;
	}

};
