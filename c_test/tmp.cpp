#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <time.h>
#include <assert.h>

using namespace std;

int main(){
	float* val = (float*)malloc(sizeof(float) * 10);
	vector<float> a = {1,2,3,4,5,6};
	for (int i = 0;i < a.size();i++){
		val[i] = a[i];
	}

	float* val_1 = val + 2;
	cout << val_1[0] << endl;


/*
	//assert
	int a = 2;
	assert(a==2);
*/
/*
	//size_t test
	size_t a = 10;
	float b = 20;
	cout << b / a << endl;
*/

/*
	//pointer to const/class
class test{
public:
	int a;
	test(){a=10;return;}
	~test(){return;}
};

void test_fun(const void* a){
	test* b = (test*)a;
	b->a = 20;
}
	test a;
	cout << a.a << endl;

	test_fun(&a);
	cout << a.a << endl;
*/
/*
	//descontruct test
	class test{
	public:
		int a;
		test(){a=10;return;}
		~test(){return;}
	};

	test* a = new test();
	cout << a->a << endl;
	a->~test();
	a->a = 20;
	cout << a->a << endl;
*/

/*
	//assign
	vector<int> a = {1,2,3};
	vector<int> b;
	b.assign(a.begin(),a.end());
	for (int i = 0;i < b.size();i++){
		cout << b[i] << " ";
	}cout << endl;
*/
/*
	//rand
	srand(time(0));
	float a = rand() % 2 - 1;	
	cout << a << endl;
*/
/*
	//new and handle
	void* p = (void*) new vector<int>{1,2,3};
	{
		vector<int> *handle = (vector<int>*)p;
		cout << (*handle)[1] << endl;
	}

	{
		vector<int> &quote = *((vector<int>*)p);
		cout  << quote[0] << endl;

	}
*/

/*
	//vector resize
	vector<int> a = {1,2,3};
	for (int i = 0;i < a.size();i++){
		cout << a[i] << " ";
	}cout << endl;
	a.resize(10);

	for (int i = 0;i < a.size();i++){
		cout << a[i] << " ";
	}cout << endl;
*/
/*
{
	//quote
	int a = 1;
	int &b = a;
	cout << b << endl;
	 = 2;
	cout << b << endl;

	vector<int> c;
	c.resize(10);

	map<string,vector<string>> name;
	name.insert(pair<string,vector<string> > ("abc",vector<string>{}));
}
*/

/*
	//map loop delete
	map<int,int> a;
	a.insert(make_pair(1,2));
	a.insert(make_pair(2,3));
	a.insert(make_pair(3,4));

	map<int,int>::iterator iter;
	for (iter = a.begin();iter != a.end();iter++){
		if (iter->first == 2){
			a.erase(iter);
		}
	}

	for (iter = a.begin();iter != a.end();iter++){
		cout << iter->first << " " << iter->second << endl;
	}
*/
	return 0;
}
