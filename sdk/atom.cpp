#include "atom.h"

Atom::Atom(const string& atom_name,const vector<int>& shape):lr_(0.0002){
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

Atom::Atom(const string& atom_name):lr_(0.0002){
	atom_name_ = atom_name;

	count_ = 0;
	data = NULL;
	diff_ = NULL;
	return;
}

void Atom::Reshape(const vector<int>& atom_shape){
	shape_.assign(atom_shape.begin(),atom_shape.end());
	count_ = 1;
	for (int i = 0;i < atom_shape.size();i++){
		count_ *= atom_shape[i];
	}

	data = (float*)malloc(sizeof(float) * count_);
	diff_ = (float*)malloc(sizeof(float) * count_);

	return;
}

void Atom :: AlterBatchsize(const int& batch_size){
	shape_[0] = batch_size;
	count_ = 1;
	for (int i = 0;i < shape_.size();i++){
		count_ *= shape_[i];
	}
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
	this->diff_ = val-> diff_;
	this->atom_name_ = val->atom_name_;
	val -> data = NULL;
	val -> diff_ = NULL;
	return;
}

void Atom::Update(){
	for (size_t i = 0;i < count_;i++){
		data[i] -= diff_[i] * lr_;
	}
	return;
}

void Atom::ClearDiff(){
	memset(diff_,0,sizeof(float) * count_);
	return;
}

void Atom :: RandomInit(){
	for (int i = 0;i < count_;i++){
		data[i] = (rand() % (2 * RANDOM_RANGE)) * 1.0 / RANDOM_RANGE - 1;
	}
	return;
}

void Atom :: AscendInit(){
	for (int i = 0;i < count_;i++){
		data[i] = i;
	}
	return;
}

void Atom :: PrintData(){
	for (int i = 0;i < shape_[0];i++){
		for (int j = 0;j < shape_[1];j++){
			cout << data[i * shape_[1] + j] << " ";
		}cout << endl;
	}
	return;
}

void Atom :: PrintName(){
	cout << atom_name_ << endl;

	return;
}

void Atom :: PrintDiff(){
	for (int i = 0;i < shape_[0];i++){
		for (int j = 0;j < shape_[1];j++){
			cout << diff_[i * shape_[1] + j] << " ";
		}cout << endl;
	}
	return;
}

void Atom::PrintShape(){
	for (int i = 0;i < shape_.size();i++){
		cout << shape_[i] << " ";
	}cout << endl;
	return;
}
