/* Your code here! */
#include "dsets.h"


void DisjointSets::addelements(int num)
{
	int size = myVec.size();
	myVec.resize(size + num);
	for(size_t i = size; i < myVec.size(); i++)
	{
		myVec[i] = -1;
	}
	//std::cout << "Works here" << std::endl;
}

int DisjointSets::find(int elem)
{
	if(myVec[elem] < 0)
		return elem; // elem == ROOT
	else
	{
		myVec[elem] = find(myVec[elem]); //path compression
		return myVec[elem];
	}
	//std::cout << "Works here" << std::endl;
}

void DisjointSets::setunion(int a , int b)
{
	int RootA = find(a); //index of root1, hold value -1
	int RootB = find(b); //index of root2, hold value -1
	//std::cout << "Works here" << std::endl;
	if(RootA == RootB)
		return;
	else
	{
		int newSize = myVec[RootA] + myVec[RootB];
		if(myVec[RootA] > myVec[RootB])
		{
			myVec[RootA] = RootB;
			myVec[RootB] = newSize;
			return;
		}
		else
		{
			myVec[RootB] = RootA;
			myVec[RootA] = newSize;
			return;
		}
	}
}

int DisjointSets::Depth(int root)
{
	static int depth = 0;
	if(myVec[root] < 0)
		return depth;
	depth++;
	return Depth(myVec[root]);
}

