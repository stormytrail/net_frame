#include "net_common.h"

class Net{
public:
	vector<vector<Atom*> > pointer_out_atom;
	vector<vector<Atom*> > pointer_in_atom;
	vector<Atom*> data_entries;

	//intermediate results
	vector<Atom*> atoms_;

	map<string,int> layer_index;

	size_t num_layers;
	BaseLayer* layers_;

	//function
	Net();

	void Init(vector<LayerParam> layer_params);

};
