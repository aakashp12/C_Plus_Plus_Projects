/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include <iostream>
#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of "StringTriples" (a typedef'd std::tuple, see top of
 * cartalk_puzzle.h). Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<StringTriple> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    /* Your code goes here! */
    //cout << "1.HERE" << endl;
    ifstream words(word_list_fname);
    vector<string> out;
    vector<StringTriple> y;
    //cout << "2.HERE" << endl;
    if (words.is_open()) 
    {
        //cout << "3.HERE" << endl;
        std::istream_iterator<string> word_iter(words);
        while (!words.eof()) 
        {
            //cout << "4.HERE" << endl;
            string B = *word_iter;
            if(B.length() == 5)
            {
                out.push_back(B);
            }
            ++word_iter;
        }
    }

    for(auto & word1 : out)
    {
        string word2 = word1.substr(1,4);
        string word3 = word1;
        word3.erase(1,1);
        if(d.homophones(word1, word2) && d.homophones(word1, word3))
        {
            y.push_back({word1, word2, word3});
        }
    }
	return y;
}
/*
string remove_punct(const string& str)
{
    string ret;
    std::remove_copy_if(str.begin(), str.end(), std::back_inserter(ret),
                        std::ptr_fun<int, int>(&std::ispunct));
    return ret;
}
*/