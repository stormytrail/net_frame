#include "net_common.h"
#pragma once
enum DATA_STORAGE_ORDER {ROW_FIRST};

using namespace std;

class Atom{
public:
	float* data;
	vector<int> shape_;

	float* diff_;

	Atom():data(NULL){}
	Atom(vector<int> vAtomShape){
		size_t iDataNum = 1;
		this->shape_.assign(vAtomShape.begin(),vAtomShape.end());
		for (int i = 0;i < vAtomShape.size();i++){
			iDataNum *= vAtomShape[i];
		}
		this->data = (float*)malloc(sizeof(float) * iDataNum);

		if (this->data == NULL){
			cout << "error in initial" << endl;
		}

		iDataNum = MAX_BATCH_SIZE;
		for (int i = 1;i < vAtomShape.size();i++){
			iDataNum *= vAtomShape[i];
		}
		this->diff_ = (float*)malloc(sizeof(float) * iDataNum);
		if (this->diff_ == NULL){
			cout << "error in diff_" << endl;
		}

		return;
	}

//	~Atom(){
//		free(this->data);
//		this->data = NULL;
//		return;
//	}

};
