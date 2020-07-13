#include "net_common.h"

class Net{
public:
	//function
	Net();

	void Init(vector<LayerParam*> layer_params);

	void ExecuteSequence();

	void FeedData(const vector<Atom*> &input_data);
	void Forward(float& loss);
	void Backward();

private:
	//layers
	size_t layer_nums_;
	BaseLayer** layers_;
	map<string,int> layer_index;

	//intermediate
	vector<Atom*> intermediate_atoms_;
	map<string,size_t> intermediate_index;
	vector<vector<Atom*> > p_out_atom;
	vector<vector<Atom*> > p_in_atom;

	//pointer data inputs
	vector<Atom*> data_entries;
	map<string,int> entries_index;

	BaseLayer** excute_seq;
};
