#include "base_layer.h"

class InnerProductLayer : public BaseLayer{
public:
	virtual void Forward(const Atom& input,Atom& output);
	virtual void Backward(const Atom& input,const Atom& output);

	bool has_bias;

	InnerProductLayer():BaseLayer(){
		this->has_bias = false;
		return;
	}

	explicit InnerProductLayer(const LayerParam& param) : BaseLayer(param){
		this->has_bias = param.atom_shapes.size() == 2;
		return;
	}
};
