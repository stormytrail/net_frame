#include "base_layer.h"

class SoftmaxLayer : public BaseLayer{
public:
	virtual void Forward(const vector<Atom>& input,vector<Atom>& output);
	virtual void Backward(const vector<Atom>& input,const vector<Atom>& output);

	SoftmaxLayer() : BaseLayer(){
		return;
	}
	explicit SoftmaxLayer(const LayerParam& param) : BaseLayer(param){
		return;
	}

};
