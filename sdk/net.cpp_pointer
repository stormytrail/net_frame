#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

enum LAYER_TYPE {conv2d,maxpooling2d};

typedef struct {
	int s,d,k;
}CONV2D_PARAM;

typedef struct {
	int k,s;
}MAXPOOLING2D_PARAM;

typedef struct {
	void* p_layer_params;
	int num_layers;
	LAYER_TYPE* p_layer_type;
}NET_PARAM;

typedef struct{
	float* data_in;
	float* data_buffer;
	NET_PARAM* net_param;

	int len_shape;
	int* shape_;

}NET;

void Conv2dForward(void* net_handle,int index);
void Maxpooling2dForward(void* net_handle,int index);

void NetForward(Net net){
	int (*p)(void* param);
	for (int i = 0;i < net.net_param->num_layers;i++){
		switch (net.net_param->p_layer_type[i]){
			case conv2d:
				p = Conv2dForward;break;
			case maxpooling2d:
				p = Maxpooling2dForward;break;
		}

		(*p)((void*)&net,index);

	}

	return;
}

void Conv2dForward(void* net_handle,int index){
	NET *net = (NET*)net_handle;
	CONV_PARAM *param = (CONV_PARAM*)net->net_param->p_layer_params[index];
	param->s = 1;param->d = 0;param->k = 3;

	net->data_buffer[0] = -1;
	
	memcpy(net->data_in,net->data_buffer,1);
	return;
}

void Maxpooling2dForward(void* net_handle,int index){
	NET *net = (NET*)net_handle;
	MAXPOOLING2D_PARAM *param = (MAXPOOLING2D_PARAM*)net->net_param->p_layer_params[index];
	param->k = 2;param->s = 2;

	net->data_buffer[0] = -1;

	memcpy(net->data_in,net->data_buffer,1);
	return;
}
int main(){
	


};
