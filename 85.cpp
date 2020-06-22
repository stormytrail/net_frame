#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>

using namespace std;

/*
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (!matrix.size()){return 0;}

	vector<vector<int> > dp(matrix.size(),vector<int>(matrix[0].size(),0));
	vector<vector<int> > width(matrix.size(),vector<int>(matrix[0].size(),0));
	vector<vector<int> > height(matrix.size(),vector<int>(matrix[0].size(),0));

	//init
	if (matrix[0][0] == '1'){
		dp[0][0] = 1;
		width[0][0] = 1;
		height[0][0] = 1;
	}
	else{
		dp[0][0] = 0;
		width[0][0] = 0;
		height[0][0] = 0;
	}
	for (int i = 1;i < matrix.size();i++){
		if (matrix[i][0] == '0'){
			dp[i][0] = 0;
			height[i][0] = 0;
			width[i][0] = 0;
		}
		else{
			dp[i][0] = dp[i - 1][0] + 1;
			height[i][0] = height[i - 1][0] + 1;
			width[i][0] = 1;
		}


	}
	for (int i = 1;i < matrix[0].size();i++){
		if (matrix[0][i] == '0'){
			dp[0][i] = 0;
			height[0][i] = 0;
			width[0][i] = 0;
		}
		else{
			dp[0][i] = dp[0][i - 1] + 1;
			height[0][i] = 1;
			width[0][i] = width[0][i - 1] + 1;
		}
	}

	//counting
	for (int i = 1;i < matrix.size();i++){
		for (int j = 1;j < matrix[0].size();j++){
			if (matrix[i][j] == '0'){
				dp[i][j] = 0;
				width[i][j] = 0;
				height[i][j] = 0;
			}
			else{
				int len_w = width[i - 1][j - 1] < width[i][j - 1] ? width[i - 1][j - 1] : width[i][j - 1];
				if (width[i - 1][j] - 1 < len_w){width[i][j] = width[i - 1][j];}
				else{width[i][j] = len_w + 1;}


				int len_h = height[i - 1][j - 1] < height[i - 1][j] ? height[i - 1][j - 1] : height[i - 1][j];
				if (height[i][j - 1] - 1< len_h){
					height[i][j] = height[i][j - 1];
				}
				else{
					height[i][j] = len_h + 1;
				}

				dp[i][j] = width[i][j] * height[i][j];

			}

		}
	}

	int ans = 0;
	for (int i = 0;i < matrix.size();i++){
		for (int j = 0;j < matrix[0].size();j++){
			if (ans < matrix[i][j]){ans = matrix[i][j];}
		}
	}

cout << "width" << endl;
	for (int i = 0;i < matrix.size();i++){
		for (int j = 0;j < matrix[0].size();j++){
			cout << width[i][j] << " ";
		}cout << endl;
	}
cout << "height" << endl;
	for (int i = 0;i < matrix.size();i++){
		for (int j = 0;j < matrix[0].size();j++){
			cout << width[i][j] << " ";
		}cout << endl;
	}

	return ans;
    }
};
*/

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
	if (matrix.size() == 0){return 0;}
        vector<vector<int> > l(matrix.size(),vector<int>(matrix[0].size(),0));
	vector<vector<int> > up(matrix.size(),vector<int>(matrix[0].size(),0));

	for 



	return ans;
    }
};

int main(){
	Solution s;
	vector<vector<char> > data;
	data.push_back(vector<char>{'1','0','1','0','0'});
	data.push_back(vector<char>{'1','0','1','1','1'});
	data.push_back(vector<char>{'1','1','1','1','1'});
	data.push_back(vector<char>{'1','0','0','1','0'});

	int ans = s.maximalRectangle(data);
	cout << ans << endl;

	return 0;
}
