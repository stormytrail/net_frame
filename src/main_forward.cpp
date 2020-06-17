#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "base_layer.h"
#include "layers/inner_product_layer.h"

using namespace std;

int main(){


	BaseLayer* a = new InnerProductLayer();

	vector<Atom> input,output;
	a->Forward(input,output);



	return 0;
}
