#pragma once
#include <iostream>
#include <unordered_map>;

class KeywordsInFile
{
	public:
		class Frequency {
			public:
				int total_frequency;
				std::unordered_map<int,int> local_frequency; //line_numbers are the keys
				Frequency() :total_frequency(0) {}
		};

		KeywordsInFile(std::string keywords, std::string text);
		KeywordsInFile() = delete;
		bool KeywordFound(std::string keyword);
		int KeywordInLine(std::string keyword, int line);
		int TotalOccurrences(std::string keyword);

		//A friend function is permitted full access to private members of a class.
		//friend functions are outside the scope of the class, in global scope
		friend std::ostream& operator<<(std::ostream& os, const KeywordsInFile& K); //operator overloaded

	private:
		std::unordered_map<std::string, KeywordsInFile::Frequency*> hashmap; //keyword <-> data pairs
};

