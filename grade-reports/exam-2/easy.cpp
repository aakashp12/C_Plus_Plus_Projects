#include "linkedlist.h"
#include <iostream>
using namespace std;

bool addAt(LinkedList &mylist, int pos, int newdata)
{
	// YOUR CODE HERE!
         int i = 1;
        LinkedList* temp = mylist;
        while(i != pos)
        {
            temp = temp->next;
            if(temp == NULL)
                return 0;
            i++;
        }
        LinkedList* temp2 = temp->next;
        LinkedList* add = new LinkedList(newdata);
    
        temp->next = add;
        add->next = temp2;
        return 1;


