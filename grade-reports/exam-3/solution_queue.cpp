#include "common.h"
#include <iostream>
#include <queue>

/*
  As a reminder, useful STL queue methods include:
  empty : Test whether container is empty (public member function)
  size : Return size (public member function)
  front : Access next element (public member function)
  push : Insert element (public member function)
  pop : Remove next element (public member function)
*/

using namespace std;

int removeAt(queue<int> &q, int pos)
{
	// YOUR CODE HERE!
	if(pos < 0 || pos >= q.size())
	{
		return-1;
	}
	
	int x = q.size() - 1;
	cout << "size: " << x << endl;
	int retval = 0;
	int temp = 0;
	
	if(pos == q.size() - 1)
	{
		for(int i = 0; i <= x; i++)
		{
			if(i == pos)
			{
				retval = q.front();
				q.pop();
				return retval;
			}
		temp = q.front();
		q.pop();
		q.push(temp);
		}
	}
	
	for(int i = 0; i < x; i++)
	{
		if(i == pos)
		{
			retval = q.front();
			q.pop();
		}
		temp = q.front();
		q.pop();
		q.push(temp);
	}
	return retval;
}
