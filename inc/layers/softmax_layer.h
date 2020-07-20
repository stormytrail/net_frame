#include "base_layer.h"

#pragma once
class SoftmaxLayer : public BaseLayer{
public:
	virtual void Forward(vector<Atom*>& input,vector<Atom*>& output);
	virtual void Backward(vector<Atom*>& input,vector<Atom*>& output);
	virtual vector<vector<int>> OutShape(const vector<vector<int> > input_shapes);

	explicit SoftmaxLayer(LayerParam* param):BaseLayer(param){
		return;
	}

};
