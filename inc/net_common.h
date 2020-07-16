#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <string>

#include <time.h>

#include  "matrix_operation.h"

#pragma once

#ifdef NET_SPACE_NAME
#define NETSPACE_BEGIN namespace SPACE_NAME {
#define NETSPACE_END }
#define NETSPACE_USE using namespace SPACE_NAME;
#else
#define NETSPACE_BEGIN
#define NETSPACE_END
#define NETSPACE_USE
#endif

using namespace std;

#ifndef MAX_BATCH_SIZE
#define MAX_BATCH_SIZE 64
#endif

enum LAYER_TYPE {INPUT_LAYER,
SOFTMAX_LAYER,INNER_PRODUCT_LAYER,SIGMOID_LOSS_LAYER}; 

class LayerParam{
public:
	LayerParam(){};
	explicit LayerParam(const LayerParam& layer_param);
//private:
	//layer_tag
	LAYER_TYPE layer_type_;
	string layer_name_;

	//input/output names
	vector<string> input_atom_names;
	vector<string> output_atom_names;

	//
	vector<int> input_layer_names;

	//parameter shape
	int param_num_;
	vector<vector<int> > param_shape_;

};

