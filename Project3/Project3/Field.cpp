#include "Field.h"

Field::Field(const std::vector<std::vector<int>>& copy)
{
	preComputation(copy);
}

Field::Field(std::vector<std::vector<int>>&& move)
{
	preComputation(move);
}

void Field::preComputation(const std::vector<std::vector<int>>& matrix)
{
	weight.clear();
	weight.resize(matrix.size(), std::vector<int>(matrix[0].size(), 0));
	path.clear();
	path.resize(matrix.size(), std::vector<int>(matrix[0].size(), 0));

	//Both matrices will contain the same values for left col and top row by nature. 
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) {
			if (i == 0 && j == 0) {
				path[i][j] = weight[i][j] = matrix[i][j];
			}
			else if (i == 0) { //left col
				path[i][j] = weight[i][j] = matrix[i][j] + weight[i][j-1];
			}
			else if (j == 0) { //top row
				path[i][j] = weight[i][j] = matrix[i][j] + weight[i-1][j];
			}
			else {
				weight[i][j] = matrix[i][j] + weight[i][j - 1] + weight[i - 1][j] - weight[i-1][j-1];
				path[i][j] = matrix[i][j] + std::min(path[i][j - 1], path[i - 1][j]);
			}
		}
	}
}

int Field::Weight(int x1, int y1, int x2, int y2)
{
	auto xbounds = [&](int t) {
		return t < 0 || t >= weight.size();
	};

	auto ybounds = [&](int t) {
		return t < 0 || t >= weight[t].size();
	};

	if ( ybounds(x1) || xbounds(x1) || ybounds(y2) || xbounds(y2) || xbounds(y1) || ybounds(x2) ) {
		throw std::out_of_range("coordinates are out of bounds");
	}

	int rect1 = (x1 >= 1) ? weight[y1][x1-1] : 0;
	int rect2 = (y2 >= 1) ? weight[y2-1][x2] : 0;
	int rect3 = (x1 >= 1 && y2 >= 1) ? weight[x1 - 1][y2 - 1] : 0;

	return weight[y1][x2] - rect1 - rect2 + rect3;
}

int Field::PathCost()
{
	return path[path.size() - 1][path[0].size() - 1];
}

std::ostream& operator<<(std::ostream& os, Field mat)
{
	for (auto& col : mat.weight)
	{
		for (auto& v : col)
		{
			os << v << " ";
		}
		os << std::endl;
	}

	os << std::endl;

	for (auto& col : mat.path)
	{
		for (auto& v : col)
		{
			os << v << " ";
		}
		os << std::endl;
	}
	return os;
}
