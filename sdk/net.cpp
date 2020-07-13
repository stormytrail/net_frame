#include "net.h"

Net::Net(){
	this->layers_nums_ = 0;
	this->layers_ = NULL;

	return;
}

void Net :: Init(vector<LayerParam*> layer_params){
	this->layer_nums_ = layer_params.size();
	this->layers_ = (BaseLayer**)malloc(sizeof(BaseLayeri*) * layer_nums_);

	this->p_in_atom.resize(layer_nums_);
	this->p_out_atom.resize(layer_nums_);

	for (size_t i = 0;i < layer_nums_;i++){
		this->layers_[i] = (BaseLayer*)LayerGenerator(layer_params[i]);
		size_t num_out = layer_params[i].output_atom_names.size();

		for (size_t index_out = 0;index_out < num_out;index_out++){
			Atom* p_cur_atom = new Atom();
			string &atom_name = layer_params[i].output_atom_names[index_out];
			size_t atom_index = intermediate_atoms_.size();
			this->intermediate_index.insert(pair<string,int>(atom_name,atom_index));
			intermediate_atoms_.push_back(p_cur_atom);

			p_out_atom[i].push_back(p_cur_atom);
		}
	}

	for (size_t i = 0;i < layer_nums_;i++){
		if (layer_params[i].layer_name_ == "Input"){
			for (size_t pos_in_atom = 0;pos_in_atom < layer_params[i].output_atom_names.size();pos_in_atom++){
				string &atom_name = layer_params[i].output_atom_names[pos_in_atom];
				size_t entry_intermidiatet_index = intermediate_index[atom_name];
				entries_index.push_back(atom_name,pos_in_atom);
				data_entries.push_back(intermediate_atoms_[entry_intermidiatet_index]);
			}
			continue;
		}

		size_t num_in = layer_params[i].input_atom_names.size();
		for (size_t index_in = 0;index_in < num_in;index_in++){
			string &atom_name = layer_params[i].input_atom_names[index_in];
			size_t atom_index = this->intermediate_atoms_[atom_name];
			this->p_in_atom.push_back(intermediate_atoms_[atom_index]);

		}
	}
	return;
}

void Net :: ExecuteSequence(){
	map<string,vector<string>> in_degree;
	map<string,vector<string>> out_degree;

	for (size_t pos_layer = 0;pos_layer < layer_nums_;pos_layer++){
		in_degree.insert(pair<string,vector<string>> (cur_name,vector<string>{}));
		out_degree.insert(pair<string,vector<string>> (cur_name,vector<string>{}));
	}

	vector<string> seq_name;
	for (size_t pos_layer = 0;pos_layer < layer_nums_;pos_layer++){
		string &cur_name = layers_[pos_layer]->layer_name;

		size_t in_layer_num = layer_[pos_layer].input_layer_names.size();
		for (size_t in_layer = 0;in_layer < in_layer_num;in_layer++){
			string &in_layer_name = layer_[pos_layer].input_layer_names[in_layer];

			in_degree[cur_name].push_back(in_layer_namme);
			out_degree[in_layer_name].push_back(cur_name);
		}
		
		if (in_degree[cur_name].size() == 0){seq_name.push_back(cur_name);}
	}

	



	return;
}

//有个问题，就是input的数据，什么时候去释放合适
//两次吧，一次是FeedData的时候，一次是析构的时候
//传进来的atom，data指针赋值为NULL
//实现将数值取出，然后和数据脱离，可以被任意操作
void Net :: FeedData(const vector<Atom*> &input_data){
	assert(input_data.size() == data_entries.size());

	//free the data space
	for (size_t pos_entry = 0;pos_entry < data_entries.size();pos_entry++){
		data_entries[pos_entry] -> Clear();
	}

	for (size_t pos_entry = 0;pos_entry < data_entries.size();pos_entry++){
		string& cur_name = input_data[i].atom_name_;
		map<string,int>::iterator iter = this->data_entries.find(cur_name);
		assert(iter != this->data_entries.end());

		size_t correspond_index = iter->second;
		data_entries[correspond_index] -> SetVal(input_data[i]);
	}

	return;
}

void Net :: Forward(float& loss){

	for (size_t pos_layer = 1;pos_layer < layer_nums_;pos_layer++){
		execute_seq[pos_layer]->Forward();
	}

	return;
}
