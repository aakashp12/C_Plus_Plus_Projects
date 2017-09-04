#include <iostream>
#include <string>

using namespace std;
int main()
{
	string word1 = "Aakash";
	string word2;
	string word3;

	if(word1.size() >= 2)
	{
		word2 = word1.substr(1,50);
		cout <<"Check: "  << word1.substr(0,1);
		word3 = word1.substr(0,1) + word1.substr(2,50);
	}

	cout << "Word1: " << word1 << endl;
	cout << "Word2: " << word2 << endl;
	cout << "Word3: " << word3 << endl;
}
