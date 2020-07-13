#include "net_common.h"
#include "atom.h"
#pragma once
enum LAYER_TYPE {conv2d,maxpooling2d};

class BaseLayer{
public:
	virtual void Forward(const vector<Atom*>& input,const vector<Atom*>& output) = 0;
	virtual void Backward(const vector<Atom*>& input,const vector<Atom*>& output) = 0;

	//constructed function
	BaseLayer()
	explicit void BaseLayer(const LayerParam& param) : layer_param_(param);

private:
	string layer_name_;
	LAYER_TYPE layer_type_;
	LayerParam* layer_param_;
	vector<Atom*> atoms_;
};

void BaseLayer::BaseLayer(const LayerParam& param){
	layer_name_ = param.layer_name_;
	layer_type_ = param.layer_type_;
	
	for (size_t pos_atom = 0;pos_atom < param.param_num_;pos_atom++){
		Atom* cur_atom = new Atom();
		atoms_.push_back(cur_atom);
	}

	return;
}
