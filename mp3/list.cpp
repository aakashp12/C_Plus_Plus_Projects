#include <iostream>
/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List()
{
    /// @todo Graded in MP3.1
    clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
    /// @todo Graded in MP3.1
    if(empty())
        return;
    ListNode* ptr = head;
	while(head != NULL)
    {
        ptr = head->next;
        delete head;
        head = ptr;
    }
    tail = NULL;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata)
{
    /// @todo Graded in MP3.1
    ListNode* temp = new ListNode(ndata);

    if(head == NULL)
    {  
        temp->next = NULL;
        temp->prev = NULL;
        head = temp;
        tail = temp;
        length = 1;
    }
    
    else
    {
        temp->next = head;
        temp->prev = NULL;
        head->prev = temp;
        head = temp;
        length += 1;
    }
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata)
{
    /// @todo Graded in MP3.1
    ListNode* temp = new ListNode(ndata);
    if(tail == NULL)
    {
        temp->next = NULL;
        temp->prev = NULL;
        tail = temp;
        head = temp;
        length = 1;
    }

    else
    {
        temp->next = NULL;
        temp->prev = tail;
        tail->next = temp;
        tail = temp;
        length += 1;
    }
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
//	std::cout << "R(2,7): " << endl; // WORKS IF WHILE CONDITION IS STARTPOINT
//	reverse(head->next, tail->prev);
//	std::cout << "R(1,8): " << endl; // WORKS IF WHILE CONDITION IS ENDPOINT
	reverse(head,tail);
//	std::cout << "R(2,8): " << endl; // WORKS IF WHILE CONDITION IS ENDPOINT
//	reverse(head->next, tail);
//	std::cout << "R(1,7): " << endl; //
//	reverse(head, tail->prev);

}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint)
{
    /// @todo Graded in MP3.1 
    if(empty())
        return;
    ListNode* curr = startPoint;
    ListNode* curr_next = startPoint->next;
    ListNode* temp_SP = startPoint->prev; // startPoint's prev
    ListNode* temp_EN = endPoint->next; // endPoint's next

    while(curr != endPoint) 
    {
        curr->next = curr->prev;
        curr->prev = curr_next; // current's previous points to current->next
        curr = curr_next; // current now points to current next.
        curr_next = curr->next; // current next points to current->next
    }
	curr->next = curr->prev;
	curr->prev = curr_next; 

    ListNode* temp_P = endPoint->prev;
    
    endPoint->prev = temp_SP;  // endPoints->prev = startP->next;
    startPoint->next = temp_EN; // startPoint->next = end->next;

	if (temp_SP != NULL) // if startPoint->prev != NULL then we have to assign the pointers correctly
	{
		temp_SP->next = endPoint;	// we make the appropiate connection by making startPoint->prev->nect point to endPoint
	}
	if(temp_EN != NULL)	// Similarly we need to make appropriate changes here as well
	{
		temp_EN->prev = startPoint;
	}

    endPoint = startPoint; //change the start and end point here
    startPoint = curr;
    
 
// startPoint is now the end of the old list(beginning of new)
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n)
{
    /// @todo Graded in MP3.1
    if(empty()) //if list is empty, dont do anything
        return;
    if(n >= length) //if N is the same as lenght or greater than, then just reverse(head, tail)
    {
        reverse(head, tail);
        return;
    }
    ListNode *start = head; // we pass this value in as the startPoint 
    ListNode *end = head; // we pass this value in as the endPoint
    int check = length;

	while(end != NULL)
	{
		for(int i = 1; i < n; i++) // we need to traverse to get the endPoint everytime
		{
			if(end->next != NULL) //as long as end->next != null we traverse
		    {
		    	end = end->next;
		    }
		    else				// otherwise we stop and pass the end value as endPoint
		    {
                break;
		    }
		}
		
		reverse(start, end);	// Reverse (startPoint, endPoint)
		
		if(length == check)		// we need to assign head correctly here
		{
			head = start;
			check--;
		}
		
        if(end->next != NULL)
        {
            start = end->next;      // get the appropriate values as startPoint
            end = start;            // get the appropriate values at endPoint
        }
        else break;
	}
    tail = end;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
    /// @todo Graded in MP3.1
    if(empty())
        return;
    ListNode *mover; //this pointer will be the one we move to the end
    ListNode *skip = head; //we will skip using this pointer
    ListNode *current; //use this to move around
    ListNode *temp = tail; //we'll use this to check if we are at the end

    while(skip->next != tail)
    {
        mover = skip->next; //we move the mover to the end
        temp = skip; //we make temp point to skip
        skip = mover->next;  //we skip the one thats next to mover
        temp->next = skip; //make temp's next point to skip
        skip->prev = temp; //make skip's previous point to temp
        current = mover; //current is mover. 

        //insertBack(mover->data);
        tail->next = mover;
        mover->prev = tail;
        mover->next = NULL;
        tail = mover;
    }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head) {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    } else {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL) {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint)
{
    /// @todo Graded in MP3.2
    ListNode* curr = start;
    ListNode* new_list = start;
    int temp = splitPoint;
    if(start == NULL)
        return NULL;

    while(temp != 1)
    {
        curr = curr->next;
        temp--;
    }
    if(curr->next != NULL)
    {
    	new_list = curr->next;
        new_list->prev = NULL;
    	curr->next = NULL;
	}
    return new_list; // change me!
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if (tail != NULL) {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second)
{
    /// @todo Graded in MP3.2
    ListNode * temp; //this is going to be the list that we play around with
    ListNode * temp2; //another temp to play with
    ListNode * list1 = first; // used to traverse the first list
    ListNode * list2 = second; // used to traverse the second list
 
    if ( list2->data < list1->data ) //if list2's first node is greater than list1's node
    {                               // then list2 becomes the main list we return
        temp = list2; //make your temp same as second aka list2
        list2 = list2->next; //make your list2 point to list2's next
    }
    else
    {
        temp = list1; //if list1 is smaller then, same as above comments
        list1 = list1->next; 
    }
 
    while ( list2 != NULL || list1 != NULL ) //checking to see if either of them are NULL
    {                                       //if not NULL continue
        if ( list2 == NULL || ( list1 != NULL && list1->data < list2->data ))
        {
            temp->next = list1;
            temp2 = temp->next;
            temp2->prev = temp;
 
            temp = temp->next;
 
            list1 = list1->next;
        }
        else
        {
            temp->next = list2;
            temp2 = temp->next;
            temp2->prev = temp;
 
            temp = temp->next;
            list2 = list2->next;
        }
    }
  
    if (second->data < first->data)
        return second;
 
    return first;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength)
{
    /// @todo Graded in MP3.2
    if(chainLength <= 1)
        return start;
    
	int middle = chainLength / 2;

	ListNode* new_right = split(start, middle); // send start list to split to split it into two different lists;
	ListNode* new_left = start; // we'll change the start, so we save it a new temp here
    
   	new_right = mergesort(new_right, chainLength-middle ); // recursive call to itself
	start = mergesort(new_left, middle); //recursive call to itsle to the other part.
	return merge(new_right, start);
}