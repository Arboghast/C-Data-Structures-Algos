
#include "Field.h"

#include <iostream>
#include <vector>

using namespace std;

int main() {
	vector<vector<int>> mat;
	for (int i = 1; i < 6; i++) {
		vector<int> temp;
		for (int j = 4; j < 9; j++)
		{
			temp.push_back(j);
		}
		mat.push_back(temp);
	}

	Field test1(mat);
	//cout << test1;

	Field test2(move(mat));

	cout << test2.Weight(1, 2, 4, 0) << endl;

	cout << test2.PathCost() << endl << test2 << endl;
}