#include "base_layer.h"

class InnerProductLayer : public BaseLayer{
public:
	virtual void Forward();
	virtual void Backward();

	bool has_bias;

	InnerProductLayer():BaseLayer(){return;}

	explicit InnerProductLayer(const LayerParam& param) : BaseLayer(param){
		this->has_bias = param.atom_shapes.size() == 2;
		return;
	}
};
