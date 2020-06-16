#include "base_layer.h"

class InnerProductLayer : public BaseLayer{
	virtual void Forward();
	virtual void Backward();
};
