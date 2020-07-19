#include "base_layer.h"

#pragma once

class InputLayer : public BaseLayer{
public:
	virtual void Forward(vector<Atom*>& input,vector<Atom*>& output){};
	virtual void Backward(vector<Atom*>& input,vector<Atom*>& output){};

	InputLayer(LayerParam* param) : BaseLayer(param){
		return;
	}
};
