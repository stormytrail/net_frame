#include "net_common.h"
#include "base_layer.h"
#include "atom.h"

#pragma once
class Net{
public:
	//function
	Net();

	void Init(vector<LayerParam*> layer_params);

	//整理layers_执行顺序，同时初始化中间结果atom->data的大小
	void ExecuteSequence(const vector<vector<int>>& max_input_dim);

	void FeedData(vector<Atom*> &input_data);
	void Forward(float& loss);
	void Backward();

	void ShowNet();


//private:
	//layers
	size_t layer_nums_;
	BaseLayer** layers_;
	map<string,int> layer_index;

	//intermediate
	vector<Atom*> intermediate_atoms_;
	map<string,size_t> intermediate_index;
	vector<vector<Atom*> > p_out_atom;
	vector<vector<Atom*> > p_in_atom;


	map<string,string> outatom_2_layer_;

	//pointer data inputs
	vector<Atom*> data_entries;
	map<string,int> entries_index;

	BaseLayer** excute_seq;
};
