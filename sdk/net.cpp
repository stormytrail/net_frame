#include "net.h"

Net::Net(){
	this->num_layers = 0;
	this->layers_ = NULL;

	return;
}

void Net::Init(vector<LayerParam> layer_params){

	this->num_layers = layer_params.size();
	this->layers_ = (BaseLayer*)malloc(sizeof(BaseLayer) * this->num_layers);

	for (size_t i = 0;i < num_layers;i++){
		BaseLayer* cur_layer = (BaseLayer*)LayerGenerator(layer_params[i]);
		this->layer_index.insert(pair<string,int> (cur_layer->layer_name,i));

		{
			vector<Atom*> pointer_cur_out;
			for (size_t j = 0;j < layer_params[i].output_size();j++){
				Atom* pointer_atom = new Atom();
				this->atoms.push_back(pointer_atom);
				pointer_cur_out.push_back(pointer_atom);
			}
			this->pointer_out_atom.push_back(pointer_cur_out);
		}

		{
			if (cur_layer->layer_name == ""){
				continue;
			}

			vector<Atom*> pointer_cur_in;
			for (size_t j = 0;j < layer_params[i].input_size();j++){
				size_t bottom_layer_index = layer_index[layer_params[i].bottom_layer_names[j]];
				for (size_t pos = 0;pos < pointer_out_atom[bottom_layer_index].size();pos++){
					pointer_cur_in.push_back(pointer_out_atom[bottom_layer_index][pos]);
				}
			}
			pointer_in_atom.push_back(pointer_cur_in);

		}

	}



	//if one layer just generate one atom at a time
	//what if the layer generate multi atoms,like rnn, lstm?
	//whatever, finish the stage 1 first
	this->output_atoms.resize(this->num_layers);


	for (size_t i = 0;i < this->num_layers;i++){
		BaseLayer cur_layer = (BaseLayer*)LayerGenerator(layer_params[i];);
		this->layer_index.insert(pair<string,int>(cur_layer->layer_name,i));		
		output_layer[i].push_back(&this->output_atoms[i]);

		//so, the initial of layers must be in the topological sort?
		for (size_t pos_input_atom = 0;pos_input_atom < layer_params[i].num_input_layers.size();i++){
			string cur_input_layer_name = layer_params[i].num_input_layers[pos_input_atom];
			size_t layer_index = this->layer_index[cur_input_layer_name];
			//there is one assumption, each layer has just one output
			Atom* input_pointer = output_layer[layer_index][0];
			//there is a assumption, the definition of input sequence for each layer must in the correct sequence
			//like the concat layer
			input_layer[i].push_back(input_pointer);

		}

	}

	return;
}
