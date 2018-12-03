
#include "dictionary.h"

using namespace std;

void create_dictionary(unordered_set<string> &dictionary, string file_in)
{
    //open dictionary file (lists all words in the english language)
    ifstream fin;
    fin.open(file_in);
    if(!fin.is_open()) {
        cout << "Error opening " + file_in + "!" << endl;
        exit(1);
    }

    //fills up the set with words
    string word;
    while (fin >> word) {
        removeWhitespace(word);
        //if words are made of only letters
        if(std::regex_match(word, std::regex("^[A-Za-z]+$"))){
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            dictionary.insert(word);
        }
    }
}
