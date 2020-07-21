#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "net.h"
//#include "base_layer.h"

using namespace std;


int main(){
	LayerParam l0,l1,l2,l3;

	l0.layer_name_ = "input";
	l0.layer_type_ = INPUT_LAYER;
	l0.output_atom_names = vector<string> {"data","label"};

	l1.layer_name_ = "inner";
	l1.layer_type_ = INNER_PRODUCT_LAYER;
	l1.input_atom_names = vector<string>{"data"};
	l1.output_atom_names = vector<string>{"inner1"};

	l1.param_num_ = 1;
	l1.param_shape_ = vector<vector<int>>{vector<int>{2,2}};


	l2.layer_name_ = "softmax";
	l2.layer_type_ = SOFTMAX_LAYER;
	l2.input_atom_names = vector<string>{"inner1"};
	l2.output_atom_names = vector<string>{"softmax1"};

	l3.layer_name_ = "loss";
	l3.layer_type_ = LOSS_CROSS_ENTROPY_LAYER;
	l3.input_atom_names = vector<string>{"label","softmax1"};
	l3.output_atom_names = vector<string>{"loss"};

	vector<LayerParam*> layer_params = {&l0,&l1,&l2,&l3};

	Net net;
	net.Init(layer_params);
	
	vector<vector<int>> max_input_dim(1,vector<int>{2});
	net.ExecuteSequence(max_input_dim);

	net.ShowNet();

	//line : x + y = 0
	Atom data("data",vector<int>{3,2});
	Atom label("label",vector<int>{3,2});

	//(1,1)
	data.data[0] = 1;data.data[1] = 1;
	label.data[0] = 1;label.data[1]=0;

	//(-1,-1)
	data.data[2]=-1;data.data[3]=-1;
	label.data[2]=0;label.data[3] = 1;

	//(2,1)
	data.data[4]=2;data.data[5]=1;
	label.data[4]=1;label.data[5]=0;

	vector<Atom*> inputs = {&data,&label};

	cout << "check input" << endl;
	for (int i = 0;i < inputs.size();i++){
		inputs[i]->PrintData();
	}
	cout << "finish check" << endl << endl;

	net.FeedData(inputs);
	cout << "check feed" << endl;
	for (int i = 0;i < net.data_entries.size();i++){
		net.data_entries[i]->PrintName();
		net.data_entries[i]->PrintData();
	}
	cout << "finish check" << endl;

	cout << "check parameter" << endl;
	net.layers_[1]->atoms_[0]->PrintData();

	float loss;
	net.Forward(loss);

	return 0;
}
