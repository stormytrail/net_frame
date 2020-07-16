#include "net_common.h"

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

		default:
			cout << "what" << endl;
			break;

	}

	return ans;
}
