#include "KeywordsInFile.h"
#include <locale>
#include <fstream>
#include <string>
#include <unordered_map>

KeywordsInFile::KeywordsInFile(std::string keywords, std::string text) //Time:O(N+M) Space:O(N*M)
{
    std::ifstream keyword_stream;
    keyword_stream.open(keywords, std::ifstream::in);

    std::string new_keyword;
    char c;
    while (keyword_stream.get(c)) {
        if (!isalpha(c)) {
            if (!new_keyword.empty()) {
                Frequency* freq = new Frequency();
                std::pair<std::string, KeywordsInFile::Frequency*> pair(new_keyword, freq);
                hashmap.insert(pair); 
                
                new_keyword.clear();
            }
        }
        else {
            new_keyword += c;
            if (keyword_stream.peek() == EOF) {
                Frequency* freq = new Frequency();
                std::pair<std::string, KeywordsInFile::Frequency*> pair(new_keyword, freq);
                hashmap.insert(pair); 

                new_keyword.clear();
            }
        }
    }

    keyword_stream.close();



    std::ifstream text_stream;
    text_stream.open(text, std::ifstream::in);

    unsigned int line_number = 1;
    std::string line;
    while (std::getline(text_stream, line)) {
        std::string word;
        for (int i = 0; i < line.size(); i++) {
            if (!isalpha(line[i])) {
                if (!word.empty()) {
                    auto itr = hashmap.find(word);
                    if (itr != hashmap.end()) {
                        KeywordsInFile::Frequency* temp = itr->second;
                        temp->total_frequency++;
                        temp->local_frequency[line_number]++;
                    }
                    word.clear();
                }
            }
            else {
                word += line[i];
                if (i + 1 == line.size()){
                    auto itr = hashmap.find(word);
                    if (itr != hashmap.end()) {
                        auto temp = itr->second;
                        temp->total_frequency++;
                        temp->local_frequency[line_number]++;
                    }
                    word.clear();
                }
            }
        }
        line_number++;
    }

    text_stream.close();
}

bool KeywordsInFile::KeywordFound(std::string keyword)  //O(1) O(1)
{
    return hashmap.find(keyword) != hashmap.end();
}

int KeywordsInFile::KeywordInLine(std::string keyword, int line) //O(1) O(1)
{
    if (!KeywordFound(keyword)) {
        std::cout << "Keyword Does Not Exist" << std::endl;
        return -1;
    }
    return hashmap.find(keyword)->second->local_frequency[line];
}

int KeywordsInFile::TotalOccurrences(std::string keyword) //O(1) O(1)
{
    if (!KeywordFound(keyword)) {
        std::cout << "Keyword Does Not Exist" << std::endl;
        return -1;
    }
    return hashmap.find(keyword)->second->total_frequency;
}

std::ostream& operator<<(std::ostream& os, const KeywordsInFile& K) 
{
    for (auto it = K.hashmap.begin(); it != K.hashmap.end(); ++it)
    {
        os << it->first << ": " << it->second->total_frequency << std::endl;
    }

    return os;
}
