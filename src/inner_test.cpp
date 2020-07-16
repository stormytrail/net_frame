#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "layers/inner_product_layer.h"
//#include "base_layer.h"

using namespace std;

int main(){
/*
	LayerParam p;
	p.layer_name_ = "inner_test";
	p.layer_type_ = INNER_PRODUCT_LAYER;

	p.input_atom_names = vector<string>{"input"};
	p.output_atom_names = vector<string>{"output"};

	p.param_num_ = 1;
	p.param_shape_ = vector<vector<int>>{vector<int>{3,2}};

	BaseLayer* l = new InnerProductLayer(&p);
//	BaseLayer* l = new BaseLayer(&p);


	int counter = 1;
	for (int i = 0;i < l->atoms_[0]->shape_[0];i++){
		for (int j = 0;j < l->atoms_[0]->shape_[1];j++){
			l->atoms_[0]->data[i * l->atoms_[0]->shape_[1] + j] = counter++;
		}
	}
*/

/*
	vector<int> param = {3,2};
	vector<vector<int>> params = {param};
	LayerParam layer_params(params);

	BaseLayer* a = new InnerProductLayer(layer_params);

	int counter = 1;
	for (int i = 0;i < a->atoms_[0].shape_[0];i++){
		for (int j = 0;j < a->atoms_[0].shape_[1];j++){
			a->atoms_[0].data[i * a->atoms_[0].shape_[1] + j] = counter++;
		}
	}

	for (int i = 0;i < a->atoms_[0].shape_[0];i++){
		for (int j = 0;j < a->atoms_[0].shape_[1];j++){
			cout << a->atoms_[0].data[i * a->atoms_[0].shape_[1] + j] << " ";
		}cout << endl;
	}cout << endl;



	vector<int> input_shape = {2,3},output_shape = {2,2};
	Atom input(input_shape),output(output_shape);

	vector<vector<int> > val = {{1,2,3},{4,5,6}};

	for (int i = 0;i < input.shape_[0];i++){
		for (int j = 0;j < input.shape_[1];j++){
			input.data[i * input.shape_[1] + j] = val[i][j];
		}
	}

	vector<Atom> inputs = {input};
	vector<Atom> outputs = {output};

	a->Forward(inputs,outputs);

	for (int i = 0;i < 2;i++){
		for (int j = 0;j < 2;j++){
			cout << output.data[i * 2 + j] << " ";
		}cout << endl;
	}
*/
	return 0;
}
