#include "base_layer.h"

#pragma once
class SoftmaxLayer : public BaseLayer{
public:
	virtual void Forward(const vector<Atom*>& input,const vector<Atom*>& output);
	virtual void Backward(const vector<Atom*>& input,const vector<Atom>& output);

	explicit SoftmaxLayer(LayerParam* param):BaseLayer(param){
		return;
	}

};
