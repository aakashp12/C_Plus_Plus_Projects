/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "avltree.h"
#include <cmath>

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else 
    {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
    Node* temp = t->right; //create the temp nodes for the necessary nodes

    t->right = temp->left; //modify the nodes
    temp->left = t;
    t = temp;

    t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    // cout << "T : " << t->height << endl;
    temp = t->left;
    temp->height = 1 + max(heightOrNeg1(temp->left), heightOrNeg1(temp->right));
    // cout << "Temp : " << temp->height << endl;
    return;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
    Node* temp = t->left; //create the appropiate nodes

    t->left = temp->right; //modify nodes
    temp->right = t;
    t = temp; //assign the new "root"

    t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
   // cout << "T : " << t->height << endl;
    temp = t->right;
    temp->height = 1 + max(heightOrNeg1(temp->left), heightOrNeg1(temp->right));
   // cout << "Temp : " << temp->height << endl;
    return;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);

    //t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    // cout << "Temp : " << t->height << endl;
}

template <class K, class V>
bool AVLTree<K,V>::heightBalance()
{
    return heightBalance(root);
}

template <class K, class V>
bool AVLTree<K,V>::heightBalance(Node* root)
{
    /*if(root == NULL)
        return true;

    int left = heightOrNeg1(root->left);
    int right = heightOrNeg1(root->right);

    if(abs(left - right) != 0 || abs(left - right) != 1)
    {
        return false;
    }
    else
        return heightBalance(root->left) && heightBalance(root->right);
    */

    if(root == NULL)
    {
        return true;
    }

    int bal = heightOrNeg1(root->right) - heightOrNeg1(root->left);

    if(bal == 1 || bal == -1 || bal == 0)
        return (heightBalance(root->right) && heightBalance(root->left));
    else if(bal > 1 || bal < -1)
        return false;
    return false;
}
//given a node find all the levaves that are smaller than it. void 
template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    int H_t; //we'll get the height difference of childs.
    if(subtree == NULL) //if leaf set h_t to 0;
        H_t = 0;    
    else
    {
        H_t = heightOrNeg1(subtree->left) - heightOrNeg1(subtree->right); //get the difference of left and right
    }

    if(H_t < -1)
    {
        int H_tl = heightOrNeg1(subtree->right->left);
        int H_tr = heightOrNeg1(subtree->right->right);
        if(H_tl - H_tr == 1)
        {
            rotateRightLeft(subtree);
            return;
        }
        rotateLeft(subtree);
    }
    else if(H_t > 1)//&& subtree->key > subtree->left->key)
    {
        int H_tl = heightOrNeg1(subtree->left->left);
        int H_tr = heightOrNeg1(subtree->left->right);
        if(H_tr - H_tl == 1)
        {
            rotateLeftRight(subtree);
            return;
        }
        rotateRight(subtree);
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value); //recursive helper function to insert a node
    return;
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree == NULL) //if you are at NULL, make a new node with the key and value
    {
        subtree = new Node(key, value);
        return;
    }

    else if(key < subtree->key) //if key is LESS than subTree's key then go left
    {
        insert(subtree->left, key, value); //recursive call
        //subtree->height = 1 + max(subtree); //set the height to 1 + max of it's child's height
    }
    else                        //otherwise go to the right
    {
        insert(subtree->right, key, value);
        //subtree->height = 1 + max(subtree);
    }
    //rebalance(subtree);
    subtree->height = 1 + max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)); //set the height to 1 + max of it's child's height
    return;
}

/*template <class K, class V>
int AVLTree<K, V>::max(Node* subRoot)
{
    if(subRoot == NULL) //if subRoot is null then return height as 0
        return 0;

    int x = 0;
    int y = 0;
    if(subRoot->left != NULL) //if left isnt NULL then assign x a height
        x =subRoot->left->height;
    if(subRoot->right != NULL) //if right isnt NULL then assign y a height
        y = subRoot->right->height;
 
    if(x > y) //compare heights and return the largest value
        return x;
    else
        return y;
}
*/
template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    //cout << "Removing: " << key << endl;
    if (subtree == NULL)
        return;

    if (key < subtree->key) 
    {
        // your code here
        remove(subtree->left, key);
    } 
    else if (key > subtree->key) 
    {
        // your code here
        remove(subtree->right, key);
    } 
    else 
    {
        //cout << "Removed: " << subtree->key << endl;
        if (subtree->left == NULL && subtree->right == NULL) 
        {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } 
        else if (subtree->left != NULL && subtree->right != NULL) 
        {
            /* two-child remove */
            // your code here
            Node* IN_p = find_P(subtree->left);
            swap(subtree, IN_p); //the values get switched. delete IN_p
            remove(subtree->left, IN_p->key);
            //rebalance(subtree);
        } 
        else 
        {
            /* one-child remove */
            // your code here
            Node* t_temp = subtree;
            Node* temp = subtree;

            if(subtree->left == NULL)
            {
                temp = subtree->right;
            }
            else if(subtree->right == NULL)
            {
                temp = subtree->left;
            }

            subtree = temp;
            delete t_temp;
            //rebalance(subtree);
        }
        // your code here
        // /rebalance(subtree);
        return;
    }
    rebalance(subtree);
}

template <class K, class V>
typename AVLTree<K, V>::Node* AVLTree<K, V>::find_P(Node*& subRoot)
{
    if(subRoot != NULL)
    {
        Node* temp = subRoot;
        while(temp->right != NULL)
        {
            temp = temp->right;
        }
        return temp;
    }
    return NULL;
}
template <class K, class V>
void AVLTree<K, V>::delete_P(Node*& subRoot)
{
    if(subRoot != NULL)
    {
        Node* temp = subRoot;
        while(temp->right != NULL)
        {
            temp = temp->right;
        }
        delete temp;
        temp = NULL;
        return;
    }
}