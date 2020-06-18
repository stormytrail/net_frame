#include "net_common.h"
#pragma once
enum DATA_STORAGE_ORDER {ROW_FIRST};

using namespace std;

class Atom{
public:
	float* data;
	vector<int> shape_;

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

		return;
	}

//	~Atom(){
//		free(this->data);
//		this->data = NULL;
//		return;
//	}

};
