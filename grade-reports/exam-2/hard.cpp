#include "linkedlist.h"

void intersection(LinkedList* lst1,
           LinkedList* lst2,
           LinkedList &intersect)
{
	// YOUR CODE HERE!
	if(lst1 == NULL)
	    return;
	if(lst2 == NULL)
	    return;
	
	LinkedList* temp = lst1;
	LinkedList* temp2 = lst2;
	
	while(temp2 != NULL)
	{
	    temp = lst1;
	    while(temp != NULL)
	    {
	        if(temp->data == temp2->data)
	        {
	                if(intersect == NULL)
	                {
	                    intersect->head = temp;
	                    head->next->next = NULL;
	                    head = temp;
	                }
	                head->next = temp;
	                head = temp;       
	        }
	        else
	        {
	            temp= temp->next;
	        }
	    }
	    temp2 = temp2->next;
	}
	return;
}
