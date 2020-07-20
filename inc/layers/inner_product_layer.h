#include "base_layer.h"

#pragma once

class InnerProductLayer : public BaseLayer{
public:
	virtual void Forward(vector<Atom*>& input,vector<Atom*>& output);
	virtual void Backward(vector<Atom*>& input,vector<Atom*>& output);
	virtual vector<vector<int>> OutShape(const vector<vector<int> > input_shapes);

	bool has_bias;

	InnerProductLayer(LayerParam* param) : BaseLayer(param){
		this->has_bias = param->param_shape_.size() == 2;
		return;
	}
};
