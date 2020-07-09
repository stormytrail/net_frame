#include "net_common.h"
#include "atom.h"
#pragma once
enum LAYER_TYPE {conv2d,maxpooling2d};

class BaseLayer{
public:
	virtual void Forward(const vector<Atom>& input,vector<Atom>& output) = 0;
	virtual void Backward(const vector<Atom>& input,const vector<Atom>& output) = 0;

	vector<Atom> atoms_;

	LayerParam layer_param_;
	string layer_name;

	BaseLayer(){
		return;
	};

	explicit BaseLayer(const LayerParam& param) : layer_param_(param){
		for (int i = 0;i < param.num_atom;i++){
			this->atoms_.push_back(Atom(param.atom_shapes[i]));
		}
		return;
	}
};
