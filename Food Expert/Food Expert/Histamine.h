#pragma once
#include <string>

enum class SEVERITY {};

class Histamine
{
	public:
		enum class HIST_TYPE{};

	private:
		Histamine::HIST_TYPE type;
		SEVERITY severity;
		std::string name;
		Histamine *related; //Linked List
};

