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
		int iDataNum = 1;
		for (int i = 0;i < vAtomShape.size();i++){
			this->shape_[i] = vAtomShape[i];
			iDataNum *= vAtomShape[i];
		}
		this->data = (float*)malloc(sizeof(float) * iDataNum);
		return;
	}

//	~Atom(){
//		free(this->data);
//		this->data = NULL;
//		return;
//	}

};
