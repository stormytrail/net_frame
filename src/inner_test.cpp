#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "layers/inner_product_layer.h"
//#include "base_layer.h"

using namespace std;

void atom_show(Atom* a){
	for (int i = 0;i < a->shape_[0];i++){
		for (int j = 0;j < a->shape_[1];j++){
			cout << a->data[i*a->shape_[1] + j] << " ";
		}cout << endl;
	}cout << endl;

	return ;
}

int main(){

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


	Atom* a_input = new Atom("input",vector<int>{2,3});
	Atom* a_output = new Atom("output",vector<int>{2,2});

{
	int pos = 0;
	for (int i = 0;i < a_input->shape_[0];i++){
		for (int j = 0;j < a_input->shape_[1];j++){
			a_input->data[pos] = pos;
			pos++;
		}
	}
}

	vector<Atom*> input = {a_input};
	vector<Atom*> output = {a_output};

	l->Forward(input,output);

	atom_show(a_input);
	atom_show(l->atoms_[0]);
	atom_show(a_output);

	return 0;
}
