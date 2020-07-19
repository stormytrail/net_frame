#include "net_common.h"
#pragma once
enum DATA_STORAGE_ORDER {ROW_FIRST};
enum PARAM_INIT_METHOD {RANDOM};

using namespace std;

#define RANDOM_RANGE 1009

class Atom{
public:
	string atom_name_;
	vector<int> shape_;
	size_t count_;

	float lr_;
	float* data;
	float* diff_;

	bool updatable;

	//constructed function
	Atom():data(NULL),diff_(NULL),lr_(0.0002){};			//complete
	Atom(const string& atom_name,const vector<int>& shape);		//complete
	Atom(const string& atom_name);					//complete

	void Reshape(const vector<int>& atom_shape);			//complete


	//malloc space for data and diff_
	void Init(PARAM_INIT_METHOD data_init_type);			//complete
	inline void RandomInit();					//complete

	//use diff_ to update data
	void Update();							//not yet

	//free the space of data and diff_
	void Clear();							//complete

	//set data with another Atom, and set the data-pointer of source Atom to NULL
	void SetVal(Atom* val);					//complete

	void PrintData();
	void PrintName();

};


