#include "net_common.h"

#include "layers/input_layer.h"
#include "layers/inner_product_layer.h"
#include "layers/loss_cross_entropy.h"
#include "layers/softmax_layer.h"

#pragma once

void* LayerGenerator(LayerParam* layer_param){
	void* ans = NULL;

	switch (layer_param->layer_type_){
		case INNER_PRODUCT_LAYER:
			ans = new InnerProductLayer(layer_param);
			break;
		case INPUT_LAYER:
			ans = new InputLayer(layer_param);
			break;
		case SOFTMAX_LAYER:
			ans = new SoftmaxLayer(layer_param);
			break;
		case LOSS_CROSS_ENTROPY_LAYER:
			ans = new CrossEntropyLayer(layer_param);
			break;
		default:
			cout << "what" << endl;
			break;
	}

	return ans;
}
