#include "atom.h"

Atom::Atom(const string& atom_name,const vector<int>& shape){

	atom_name_ = atom_name;
	shape_.assign(shape.begin(),shape.end());
	{
		this->count_ = 1;
		for (int i = 0;i < shape.size();i++){count_ *= shape[i];}
	}

	data = (float*)malloc(sizeof(float) * count_);
	diff_ = (float*)malloc(sizeof(float) * count_);

	memset(diff_,0,sizeof(float) * count_);

	return;
}

void Atom::Init(PARAM_INIT_METHOD data_init_type){
	switch (data_init_type){
		case RANDOM:
			RandomInit();
			break;
		default:
			break;
	}
	return;
}

void Atom :: Clear(){
	free(this->data);
	this->data = NULL;
	free(this->diff_);
	this->diff_ = NULL;

	return;
}


void Atom::SetVal(Atom* val){
	this->shape_.assign(val->shape_.begin(),val->shape_.end());
	this->data = val -> data;
	this->atom_name_ = val->atom_name_;
	val -> data = NULL;
	return;
}

void Atom::Update(){
	for (size_t i = 0;i < count_;i++){
		data[i] += diff_[i] * lr_;
	}
	return;
}

void Atom :: RandomInit(){
	for (int i = 0;i < count_;i++){
		data[i] = (rand() % (2 * RANDOM_RANGE)) * 1.0 / RANDOM_RANGE - 1;
	}
	return;
}
