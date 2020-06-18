#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "base_layer.h"
#include "layers/inner_product_layer.h"

using namespace std;

int main(){


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

	a->Forward(input,output);

	for (int i = 0;i < 2;i++){
		for (int j = 0;j < 2;j++){
			cout << output.data[i * 2 + j] << " ";
		}cout << endl;
	}

	return 0;
}
