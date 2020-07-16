#include <iostream>
#include <vector>
#include <string>


using namespace std;



int main(){

	vector<string> a = {"ab","cde","fgh"};
	vector<string*> b(10);

	b[0] = (&a[1]);

	cout << *(b[0]) << endl;

	a[1] = "afdb";
	cout << *(b[0]) << endl;


	return 0;
}
