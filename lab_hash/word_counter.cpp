/**
 * @file word_counter.cpp
 * Implementation of the WordFreq class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Spring 2012
 */

using std::vector;
using std::pair;
using std::string;
using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;

template <template <class K, class V> class Dict>
WordFreq<Dict>::WordFreq(const string& infile)
    : filename(infile)
{
    /* nothing */
}

template <template <class K, class V> class Dict>
vector<pair<string, int>> WordFreq<Dict>::getWords(int threshold) const
{
    TextFile infile(filename);
    vector<pair<string, int>> ret;
    /**
     * @todo Implement this function.
     * @see char_counter.cpp if you're having trouble.
     */
    Dict<string, int> hashTable(256); //create a Dictionary/Hashtable. intialize size of 256
    while(infile.good()) //while the file has words
    {
        string word = infile.getNextWord(); // get the new word
        hashTable[word]++; //put it in the hashtable the first time, then everyother time increment the value
    }

    typename Dict<string, int>::iterator it; // iterator to go through the dictionary
    for(it = hashTable.begin(); it != hashTable.end(); it++) //going through the dictionary
    {
        if(it->second >= threshold) //if the value of the dictionary has a 
            ret.push_back(*it); //value same as/greater than then threshold push it to the vector
    }
    //(void) threshold; // prevent warnings... When you implement this function, remove this line.

    return ret;
}
