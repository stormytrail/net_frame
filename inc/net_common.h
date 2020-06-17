#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <string>

#pragma once

#ifdef NET_SPACE_NAME
#define NETSPACE_BEGIN namespace SPACE_NAME {
#define NETSPACE_END }
#define NETSPACE_USE using namespace SPACE_NAME;
#else
#define NETSPACE_BEGIN
#define NETSPACE_END
#define NETSPACE_USE
#endif


using namespace std;

class LayerParam{
public:
	LayerParam(){}

	explicit LayerParam(const LayerParam& param){
		this->atom_shapes.assign(param.atom_shapes.begin(),param.atom_shapes.end());
		this->num_atom = param.atom_shapes.size();
		return;
	}
	explicit LayerParam(const vector<vector<int>> & param){
		this->atom_shapes.assign(param.begin(),param.end());
		this->num_atom = param.size();
		return;
	}

	vector<vector<int>> atom_shapes;
	int num_atom;
};

