/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
#include <math.h>
template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if(first[curDim] == second[curDim])
    {
        if(first < second)
            return true;
        else 
            return false;
    }
    else
    {
        if(first[curDim] < second[curDim])
            return true;
        else
            return false;

    }
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double curr = 0;
    double potent = 0;
    for(int i = 0; i < Dim; i++)
    {
        curr += pow(target[i] - currentBest[i], 2);
        potent += pow(target[i] - potential[i], 2);
    }
    if(potent < curr)
        return true;
    else if (potent > curr)
        return false;
    else
        return potential < currentBest;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    if(newPoints.empty())
        return;// vector<Point<Dim>>();
    int size = int(newPoints.size()); //get the size of the vector
    points = newPoints; // points is defined in the .h file
    KDCtor(0, size - 1, 0);
}


template <int Dim>
void KDTree<Dim>::KDCtor(int left, int right, int k)
{
    if(left >= right)
        return;
    int median = floor((left + right) / 2);
    select(k, left, right, median); //k is dimension, med is median
    if(left < median)
        KDCtor(left, median - 1, (k + 1) % Dim); // (K + 1) % dim gets you the dim
    if(right > median)
        KDCtor(median + 1, right, (k + 1) % Dim);
}

template <int Dim>
void KDTree<Dim>::select(int k, int left, int right, int median)
{
    if(left == right)
        return; // if left and right are at the same place, this is the median
    int pivot = partition(k, left, right, median); // median is the pivot index

    if(median == pivot)
        return; //return if the pivot was found to be the median we sent in
    else if(median < pivot)
        select(k, left, pivot - 1, median);
    else
        select(k, pivot + 1, right, median);
}

template <int Dim>
int KDTree<Dim>::partition(int k, int left, int right, int median)
{
    if(left >= right)
        return left;

    auto pivot_value = points[median];
    swap(median, right); //swap the values of median and right
    int index = left;

    for(int i = left; i < right; i++)
    {
        if(smallerDimVal(points[i], pivot_value, k) || points[i] == pivot_value)
        {
            swap(index, i);
            index++;
        }
    }
    swap(right, index);
    return index;
}


template <int Dim>
void KDTree<Dim>::swap(int pos1, int pos2)
{
    auto temp = points[pos1];
    points[pos1] = points[pos2];
    points[pos2] = temp;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    if(points.empty()) //if the points vector is empty then we cant find the nearest neighbor
        return Point<Dim>(); 
    int size = int(points.size());
    if(size == 1)
        return points[0];

    Point<Dim> retVal = points[(size-1) / 2]; //create a new point, which we will return
    nearNeighbor(query, retVal, 0, size - 1, 0);
    return retVal;
}

template <int Dim>
void KDTree<Dim>::nearNeighbor(const Point<Dim>& query, Point<Dim>& retVal, int left, int right, int k) const
{
    int median = (left + right) / 2;

    if(left > right || right >= int(points.size()) || left < 0)
        return;

    if(median < 0 || median >= int(points.size()) )
        return;

    if(left == right)
    {
        if(shouldReplace(query, retVal, points[left]))
            retVal = points[left];
        return;
    }


    if(smallerDimVal(points[median], query, k))
    {
        nearNeighbor(query, retVal, median + 1, right, (k + 1) % Dim);
        if(shouldReplace(query, retVal, points[median]))
                retVal = points[median];
        if(splitChecker(query, points[median], retVal, k))
        {
            //nearNeighbor(query, retVal, median + 1, right, (k + 1) % Dim);
            nearNeighbor(query, retVal, left, median - 1, (k + 1) % Dim);
        }
    }
    else
    {
        nearNeighbor(query, retVal, left, median - 1, (k + 1) % Dim);
        if(shouldReplace(query, retVal, points[median]))
                retVal = points[median];
        if(splitChecker(query, points[median], retVal, k))
        {
            //nearNeighbor(query, retVal, left, median - 1, (k + 1) % Dim);
            nearNeighbor(query, retVal, median + 1, right, (k + 1) % Dim);
        }
    }
}


template <int Dim>
bool KDTree<Dim>::splitChecker(const Point<Dim>& query, Point<Dim> split, Point<Dim> best, int k) const
{
    int bestDistance = 0;
    int splitDistance = 0;

    for(int i = 0; i < Dim; i++)
    {
        bestDistance += pow(best[i] - query[i], 2); //curent best 
    }
    splitDistance += pow(split[k] - query[k], 2);// median
    return splitDistance <= bestDistance;
}