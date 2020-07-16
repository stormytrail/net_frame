#include "net_common.h"
#include "atom.h"
#pragma once

class BaseLayer{
public:
	virtual void Forward(vector<Atom*>& input,vector<Atom*>& output) = 0;
	virtual void Backward(vector<Atom*>& input,vector<Atom*>& output) = 0;

	//constructed function
	BaseLayer();
	explicit BaseLayer(LayerParam* layer_param);

//private:
	LayerParam* layer_param_;
	string layer_name_;
	LAYER_TYPE layer_type_;
	vector<Atom*> atoms_;

	vector<float*> param_diff_buffer_;
};


