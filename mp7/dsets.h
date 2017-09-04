/* Your code here! */
#include <vector>
#include <iostream>
class DisjointSets
{
	public:
		void addelements(int num);
		int find(int elem);
		void setunion(int a , int b);
		int Depth(int root);
	private:
		std::vector<int> myVec;
};