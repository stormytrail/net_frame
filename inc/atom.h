#include "net_common.h"
#pragma once
enum DATA_STORAGE_ORDER {ROW_FIRST};

using namespace std;

class Atom{
public:
	string atom_name_;
	vector<int> shape_;

	float* data;
	float* diff_;

	bool updatable;

	//constructed function
	Atom():data(NULL){}
	explicit Atom(const AtomParam);

	//malloc space for data and diff_
	void Init()

	//use diff_ to update data
	void Update()

	//free the space of data and diff_
	void Clear();

	//set data with another Atom, and set the data-pointer of source Atom to NULL
	void SetVal(const Atom* val);
};

Atom::Atom()
void Atom::Atom(const AtomParam){

	return;
}

void Atom::Init(){

	return;
}

void Atom:: Clear(){
	free(this->data);
	this->data = NULL;
	free(this->diff_);
	this->diff_ = NULL;

	return;
}

void Atom::SetVal(const Atom* val){
	this->shape_.assign();
	this->data = val -> data;
	val -> data = NULL;

	return;
}
