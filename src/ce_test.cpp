#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "layers/loss_cross_entropy.h"
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
	p.layer_name_ = "loss_cross_entropy";
	p.layer_type_ = LOSS_CROSS_ENTROPY_LAYER;

	p.input_atom_names = vector<string>{"label","prediction"};
	p.output_atom_names = vector<string>{"output"};

	BaseLayer* l = new CrossEntropyLayer(&p);


	Atom* a_label = new Atom("input",vector<int>{1,3});
	Atom* a_predict = new Atom("predict",vector<int>{1,3});
	Atom* a_output = new Atom("loss",vector<int>{1,1});

	a_label->data[0] = 0.1;a_label->data[1] = 0.2;a_label->data[2] = 0.7;
	a_predict->data[0] = 0.3;a_predict->data[1] = 0.2;a_predict->data[2] = 0.5;

	vector<Atom*> input = {a_label,a_predict};
	vector<Atom*> output = {a_output};

	l->Forward(input,output);

	atom_show(a_label);
	atom_show(a_predict);
	atom_show(a_output);

	return 0;
}
