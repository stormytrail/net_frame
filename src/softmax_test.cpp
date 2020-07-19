#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "layers/softmax_layer.h"
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
	p.layer_name_ = "softmax";
	p.layer_type_ = SOFTMAX_LAYER;

	p.input_atom_names = vector<string>{"input"};
	p.output_atom_names = vector<string>{"output"};

	BaseLayer* l = new SoftmaxLayer(&p);


	Atom* a_label = new Atom("input",vector<int>{1,3});
	Atom* a_output = new Atom("loss",vector<int>{1,3});

	a_label->data[0] = 10;a_label->data[1] = -3;a_label->data[2] = 2;

	vector<Atom*> input = {a_label};
	vector<Atom*> output = {a_output};

	l->Forward(input,output);

	atom_show(a_label);
	atom_show(a_output);

	return 0;
}
