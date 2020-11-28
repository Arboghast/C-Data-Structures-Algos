#pragma once

#include <vector>
#include <ostream>
class Field
{
	private:
		std::vector<std::vector<int>> weight;
		std::vector<std::vector<int>> path;

	public:
		Field(const std::vector<std::vector<int>>& copy); //calls preComputation func

		Field(std::vector<std::vector<int>>&& move); //calls preComputation func

		void preComputation(const std::vector<std::vector<int>>& matrix); //Time:O(N) Space:O(N)

		int Weight(int x1, int y1, int x2, int y2); //Time:O(1) Space:O(1)

		int PathCost(); //Time:O(1) Space:O(1)

		friend std::ostream& operator<<(std::ostream& os, Field mat);
};

