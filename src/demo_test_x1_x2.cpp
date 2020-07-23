#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "net.h"
//#include "base_layer.h"

using namespace std;


int main(){
	LayerParam l0,l1,l2,l3;

	{
	//initial layer parameter
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
	}

	vector<LayerParam*> layer_params = {&l0,&l1,&l2,&l3};
	Net net;
	net.Init(layer_params);
	
	vector<vector<int>> max_input_dim(1,vector<int>{2});
	net.ExecuteSequence(max_input_dim);

	//generate train data
	int num_train = 1000;
	float* train_data = (float*)malloc(sizeof(float) * 2 * num_train);
	float* train_label = (float*)malloc(sizeof(float) * 2 * num_train);

	int data_range = 10;

	for (int i = 0;i < num_train;i++){
		train_data[2 * i] = rand() % (2 * data_range) - data_range;
		train_data[2 * i + 1] = rand() % (2 * data_range) - data_range;
		bool flag = (train_data[2 * i] + train_data[2 * i + 1]) > 0 ? true : false;
		if (flag){
			train_label[2 * i] = 1;
			train_label[2 * i + 1] = 0;
		}
		else{
			train_label[2 * i] = 0;
			train_label[2 * i + 1] = 1;
		}
	}

	int num_iter = 10;
	int num_steps = num_train / MAX_BATCH_SIZE + (num_train % MAX_BATCH_SIZE ? 1 : 0);
	while (num_iter--){

		float* train_data_shifter = train_data;
		float* train_label_shifter = train_label;

		float iter_loss;

		for (int i = 0;i < num_steps;i++){
			int num_res = num_train - MAX_BATCH_SIZE * i;
			int cur_batch_size = num_res > MAX_BATCH_SIZE ? MAX_BATCH_SIZE : num_res;

//			cout << cur_batch_size << endl;


			Atom data("data",vector<int>{cur_batch_size,2});
			Atom label("label",vector<int>{cur_batch_size,2});

			memcpy(data.data,train_data_shifter,sizeof(float) * cur_batch_size*2);
			memcpy(label.data,train_label_shifter,sizeof(float) * cur_batch_size*2);
			train_data_shifter += cur_batch_size * 2;
			train_label_shifter += cur_batch_size * 2;

			vector<Atom*> inputs = {&data,&label};
			net.FeedData(inputs);

//			cout << "finish forward" << endl;

			float loss = 0;
			net.Forward(loss);

//			cout << loss << endl;
			iter_loss = loss;

			net.ClearDiff();
//			cout << "finish clear diff" << endl;

			net.Backward();

//			cout << "finish backward" << endl;

			net.Update();

//			cout << "finish update" << endl;

		}
		cout << iter_loss << endl;
	}

	net.layers_[1]->atoms_[0]->PrintData();

	return 0;
}
