#include "base_layer.h"

class SoftmaxLayer : public BaseLayer{
public:
	virtual void Forward(const Atom& input,Atom& output);
	virtual void Backward(const Atom& input,const Atom& output);

	SoftmaxLayer() : BaseLayer(){
		return;
	}
	explicit SoftmaxLayer(const LayerParam& param) : BaseLayer(param){
		return;
	}

};
