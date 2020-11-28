#include "KeywordsInFile.h";
#include <iostream>

using namespace std;

int main() {
	KeywordsInFile* generator = new KeywordsInFile("test1.txt", "test2.txt");

	//Keyword Found Check
	cout << "lorem: " << generator->KeywordFound("lorem") << " Lorem: " << generator->KeywordFound("Lorem") << " ";
	cout << "ipsum: " << generator->KeywordFound("ipsum") << " Ipsum: " << generator->KeywordFound("Ipsum") << " ";
	cout << "dog: " << generator->KeywordFound("dog") << endl;

	//Total Occurances
	cout << "lorem: " << generator->TotalOccurrences("lorem") << " Lorem: " << generator->TotalOccurrences("Lorem") << " ";
	cout << "ipsum: " << generator->TotalOccurrences("ipsum") << " Ipsum: " << generator->TotalOccurrences("Ipsum") << " ";
	cout << "dog: " << generator->TotalOccurrences("dog") << endl;

	//Keyword In Line
	cout << "Lorem: " << generator->KeywordInLine("Lorem",2) << " Lorem: " << generator->KeywordInLine("Lorem",1) << " ";
	cout << "ipsum: " << generator->KeywordInLine("ipsum",3) << " Ipsum: " << generator->KeywordInLine("Ipsum",4) << " ";
	cout << "dog: " << generator->KeywordInLine("dog",3) << endl << endl;

	cout << *generator << endl;

}