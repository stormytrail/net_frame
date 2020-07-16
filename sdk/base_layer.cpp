#include "base_layer.h"

BaseLayer::BaseLayer(LayerParam *layer_param){
	layer_param_ = layer_param;
	layer_name_ = layer_param_->layer_name_;
	layer_type_ = layer_param_->layer_type_;

	param_diff_buffer_.resize(layer_param_->param_num_);
	
	for (size_t i = 0;i < layer_param_->param_num_;i++){
		string &atom_name = layer_param_->output_atom_names[i];
		vector<int> &atom_shape = layer_param_->param_shape_[i];
		Atom* cur_atom = new Atom(atom_name,atom_shape);

		param_diff_buffer_[i] = (float*)malloc(sizeof(float) * MAX_BATCH_SIZE * cur_atom->count_);

		atoms_.push_back(cur_atom);
	}
	return;
}
