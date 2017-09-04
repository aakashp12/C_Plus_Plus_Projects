/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>
 #include <iostream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream words(filename); //file stream 
    string line;
    if(words.is_open())
    {
    	while( getline(words, line))    	
    	{
    		string key_val = line;
    		sort(key_val.begin(), key_val.end());
    		
    		dict[key_val].push_back(line);
    	}
    	//words.close();
    }
    else
    	std::cout << "Unable to open file" << std::endl;
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for(auto iter : words)
    {
    	string key_val = iter;
    	string line = key_val;

    	sort(key_val.begin(), key_val.end());

    	dict[key_val].push_back(line);
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
	string key_val = word;
	sort(key_val.begin(), key_val.end());

	if(dict.find(key_val) == dict.end() || dict.at(key_val).size() < 2)
		return vector<string>();
	else
    	return dict.at(key_val);
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
	vector<vector<string>> word_list;
	
	for(auto &key_val : dict)
	{
		vector<string> v = get_anagrams(key_val.first);
		if(v.size() >= 2)
			word_list.push_back(v);
	}

    return word_list;
}
