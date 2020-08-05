#include <assert.h>
#include "net.h"
#include "layers/layer_generator.h"

Net::Net(){
	srand(time(0));

	this->layer_nums_ = 0;
	this->layers_ = NULL;

	return;
}

void Net :: Init(vector<LayerParam*> layer_params){
	this->layer_nums_ = layer_params.size();
	this->layers_ = (BaseLayer**)malloc(sizeof(BaseLayer*) * layer_nums_);

	this->p_in_atom.resize(layer_nums_);
	this->p_out_atom.resize(layer_nums_);

	//生成中间结果保存atom
	//保存在intermediate_atoms_
	//地址映射保存在intermediate_index
	for (size_t i = 0;i < layer_nums_;i++){
		this->layers_[i] = (BaseLayer*)LayerGenerator(layer_params[i]);
		size_t num_out = layer_params[i]->output_atom_names.size();

		for (size_t index_out = 0;index_out < num_out;index_out++){
			string &atom_name = layer_params[i]->output_atom_names[index_out];
			Atom* p_cur_atom = new Atom(atom_name);

			size_t atom_index = intermediate_atoms_.size();
			this->intermediate_index.insert(pair<string,int>(atom_name,atom_index));
			intermediate_atoms_.push_back(p_cur_atom);

			p_out_atom[i].push_back(p_cur_atom);
		}
	}

	//将每层的输入和中间结果保存atom关联起来
	for (size_t i = 0;i < layer_nums_;i++){
		//单独处理输入层
		if (layer_params[i]->layer_type_ == INPUT_LAYER){
			for (size_t pos_in_atom = 0;pos_in_atom < layer_params[i]->output_atom_names.size();pos_in_atom++){
				string &atom_name = layer_params[i]->output_atom_names[pos_in_atom];
				size_t entry_intermidiatet_index = intermediate_index[atom_name];
				entries_index.insert(pair<string,int>(atom_name,pos_in_atom));
				data_entries.push_back(intermediate_atoms_[entry_intermidiatet_index]);
			}
			continue;
		}

		size_t num_in = layer_params[i]->input_atom_names.size();
		for (size_t index_in = 0;index_in < num_in;index_in++){
			string &atom_name = layer_params[i]->input_atom_names[index_in];
			size_t atom_index = this->intermediate_index[atom_name];
			this->p_in_atom[i].push_back(intermediate_atoms_[atom_index]);

		}
	}
	return;
}

void Net :: ExecuteSequence(const vector<vector<int>>& max_input_dim){
	//tolopy sort
	{
		//not yet

	}

	//resize the intermediate atom
	vector<vector<int> > cur_dim(max_input_dim.size(),vector<int>{MAX_BATCH_SIZE});


	for (size_t i = 0;i < max_input_dim.size();i++){
		cur_dim[i].insert(cur_dim[i].end(),max_input_dim[i].begin(),max_input_dim[i].end()); 
	}




	for (size_t i = 1;i < layer_nums_;i++){
		cur_dim = layers_[i]->OutShape(cur_dim);
		for (size_t j = 0;j < p_out_atom[i].size();j++){
			p_out_atom[i][j]->Reshape(cur_dim[j]);
		}
	}

	return;
}

//有个问题，就是input的数据，什么时候去释放合适
//两次吧，一次是FeedData的时候，一次是析构的时候
//传进来的atom，data指针赋值为NULL
//实现将数值取出，然后和数据脱离，可以被任意操作
void Net :: FeedData(vector<Atom*> &input_data){
	assert(input_data.size() == data_entries.size());

	//free the data space
	for (size_t pos_entry = 0;pos_entry < data_entries.size();pos_entry++){
		data_entries[pos_entry] -> Clear();
	}

	for (size_t pos_entry = 0;pos_entry < data_entries.size();pos_entry++){
		string& cur_name = input_data[pos_entry]->atom_name_;

		map<string,int>::iterator iter = this->entries_index.find(cur_name);
		assert(iter != this->entries_index.end());

		size_t correspond_index = iter->second;
		data_entries[correspond_index] -> SetVal(input_data[pos_entry]);
	}

	//change the batch_size of every intermediate atom according
	//to the current batch_size
	int cur_batch_size = input_data[0]->shape_[0];
	for (int i = 1;i < layer_nums_;i++){
		for (int j = 0;j < p_out_atom[i].size();j++){
			p_out_atom[i][j]->AlterBatchsize(cur_batch_size);
		}
	}

	return;
}

void Net :: Forward(float& loss){
	for (size_t pos_layer = 1;pos_layer < layer_nums_;pos_layer++){
		layers_[pos_layer]->Forward(p_in_atom[pos_layer],p_out_atom[pos_layer]);
	}

	loss = 0;
	for (size_t i = 0;i < p_out_atom[layer_nums_ - 1][0]->shape_[0];i++){
		loss += p_out_atom[layer_nums_ - 1][0]->data[i];
	}

	return;
}

void Net :: Backward(){
	for (size_t pos_layer = layer_nums_ - 1;pos_layer >= 1;pos_layer--){
		layers_[pos_layer]->Backward(p_in_atom[pos_layer],p_out_atom[pos_layer]);
	}
	return;
}

void Net :: ClearDiff(){
	for (size_t pos_layer = 1;pos_layer < layer_nums_;pos_layer++){
		for (size_t pos_atom = 0;pos_atom < layers_[pos_layer]->atoms_.size();pos_atom++){
			layers_[pos_layer]->atoms_[pos_atom]->ClearDiff();
		}
	}
	return;
}

void Net :: Update(){
	for (size_t pos_layer = 1;pos_layer < layer_nums_;pos_layer++){
		for (size_t pos_atom = 0;pos_atom < layers_[pos_layer]->atoms_.size();pos_atom++){
			layers_[pos_layer]->atoms_[pos_atom]->Update();
		}
	}
	return;
}
void Net :: ShowNet(){
	for (int i = 0;i < layer_nums_;i++){
		cout << "layer id : " << i << endl;
		cout << "layer name : " << layers_[i]->layer_name_ << endl;
		cout << "layer type : " << layers_[i]->layer_type_ << endl;

		cout << "num input : " << layers_[i]->layer_param_->input_atom_names.size() << endl;
		cout << "num output : "<< layers_[i]->layer_param_->output_atom_names.size() << endl;

		cout << "in atom names : " << endl;
		for (int j = 0;j < p_in_atom[i].size();j++){
			(p_in_atom[i][j]->PrintName());
		}cout << endl;

		cout << "out atom names : " << endl;
		for (int j = 0; j < p_out_atom[i].size();j++){
			(p_out_atom[i][j] -> PrintName());
		}cout << endl;


		cout << endl;
	}
	return;
}

void Net::CheckForward(){
	cout << "forward details" << endl;
	for (int i = 1;i < layer_nums_;i++){
		cout << "layer :" << i << endl;
		cout <<"input" << endl;
		for (int j = 0;j < p_in_atom[i].size();j++){
			p_in_atom[i][j]->PrintShape();
			p_in_atom[i][j]->PrintData();
			cout << endl;
		}

		cout << "param" << endl;
		for (int j = 0;j < layers_[i]->atoms_.size();j++){
			layers_[i]->atoms_[j]->PrintShape();
			layers_[i]->atoms_[j]->PrintData();
			cout << endl;
		}

		cout << "output" << endl;
		for (int j = 0;j < p_out_atom[i].size();j++){
			p_out_atom[i][j]->PrintShape();
			p_out_atom[i][j] ->PrintData();
			cout << endl;
		}
	}
	cout << "detail finish" << endl;
	return;
}


void Net::PrintDetails(){

	for (int i = 1;i < layer_nums_;i++){
		cout << "layer :" << i << endl;

		cout << "input:" << endl;
		for (int j = 0;j < p_in_atom[i].size();j++){
			cout << "data" << endl;
			p_in_atom[i][j]->PrintData();
			cout << "diff_" << endl;
			p_in_atom[i][j] -> PrintDiff();
			cout << endl;
		}

		cout << "parameter:" << endl;
		for (int j = 0;j < layers_[i]->atoms_.size();j++){
			cout << "weight" << endl;
			layers_[i]->atoms_[j]->PrintData();
			cout << "diff_" << endl;
			layers_[i]->atoms_[j]->PrintDiff();
			cout << endl;
		}

		cout << "output:" << endl;
		for (int j = 0;j < p_out_atom[i].size();j++){
			cout << "data" << endl;
			p_out_atom[i][j]->PrintData();
			cout << "diff" << endl;
			p_out_atom[i][j] -> PrintDiff();
		}
		cout << "finish" << endl << endl;
	}
	return;
}
