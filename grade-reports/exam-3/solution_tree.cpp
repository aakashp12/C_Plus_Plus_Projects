#include "common.h"
#include <iostream>

using namespace std;

void updateSum(Node<int> *&root)
{
	// YOUR CODE HERE!
    if(root == NULL)
    {
        return;
    }   
	updateSum(root->left);
	updateSum(root->right);
	
	if(root->left == NULL && root->right == NULL)
	{
		return;
	}
	if(root->left != NULL && root->right == NULL)
	{
		root->data = root->data + root->left->data;
    }
    if(root->left == NULL && root->right != NULL)
    {
    	root->data = root->data + root->right->data;
    }
    if(root->left != NULL && root->right != NULL)
    {
    	root->data = root->data + root->left->data + root->right->data;
	}
	return;
}
