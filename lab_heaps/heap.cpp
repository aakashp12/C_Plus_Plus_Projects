/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    /// @todo Update to return the index you are choosing to be your root.
    //bool check = true;
    //if(check)
    //    return 1; //always choose index to be 0
    return 0;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the left child.
    int returnVal = currentIdx;
    returnVal = (2 * returnVal) + 1;
    return returnVal;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the right child.
    int returnVal = currentIdx;
    returnVal = (2 * returnVal) + 2;
    return returnVal;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    /// @todo Update to return the index of the parent.
    int returnVal = currentIdx - 1;
    returnVal = returnVal / 2;
    return returnVal;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    /// @todo Update to return whether the given node has a child
    if(empty())
        return false;
    size_t left = leftChild(currentIdx);
    size_t right = rightChild(currentIdx);
    size_t size = _elems.size();

    if(left > (size - 1))
        return false;
    return true;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    size_t a = leftChild(currentIdx); //left child
    size_t b = rightChild(currentIdx); //right child
    if((currentIdx * 2) + 2 < _elems.size())
    {
        if(higherPriority(_elems[a], _elems[b]))
            return a;
        return b;
    }
    return a; //return the left
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    /// @todo Implement the heapifyDown algorithm.
    if(hasAChild(currentIdx))
    {
        size_t left = leftChild(currentIdx); //left child
        size_t right = rightChild(currentIdx); //right child


        if(_elems.size() > right ) //if the size is greater than right child node
        {
            if(higherPriority(_elems[left], _elems[right])) //left child is smaller
            {
                if(higherPriority(_elems[left], _elems[currentIdx])) //left is smaller than current
                {
                    std::swap(_elems[currentIdx], _elems[left]); //swap left and current
                    heapifyDown(leftChild(currentIdx));
                }
            }
            else if(higherPriority(_elems[right], _elems[currentIdx])) //right is smaller than current
            {
                    std::swap(_elems[currentIdx], _elems[right]); //swap left and current
                    heapifyDown(rightChild(currentIdx));
            }
        }
        else
        {
            if(higherPriority(_elems[left], _elems[currentIdx])) //left is smaller than current
            {
                std::swap(_elems[currentIdx], _elems[left]); //swap left and current
                //heapifyDown(left);
            }
        }
    }    
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    /// @todo Depending on your implementation, this function may or may
    ///   not need modifying
    //_elems.push_back(-1); // initial position of 0 will have -1 as the value... start after that
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    /// @todo Construct a heap using the buildHeap algorithm
    for(int i = 0; i < int(elems.size()); i++)
    {
        _elems.push_back(elems[i]); //elems 0 is our 1
    }
    for(int i = elems.size() - 1; i > 0; i--)
    {
        heapifyDown(i);
    }
    heapifyDown(0);
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    /// @todo Remove, and return, the element with highest priority
    T retVal = _elems[0]; //get the current value

    _elems[0] = _elems[_elems.size() - 1]; //get the right most node
    _elems[_elems.size() - 1] = retVal;
    _elems.pop_back();

    heapifyDown(0);
    return retVal;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    /// @todo Return, but do not remove, the element with highest priority
    if(!empty())
    {
        T retVal = _elems[0];
        return retVal;
    }
    return T();
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    /// @todo Add elem to the heap
    _elems.push_back(elem); //push value to the last available space
    heapifyUp(_elems.size() - 1); //last node
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    /// @todo Determine if the heap is empty
    return _elems.empty();
}
