/**
 * @file quadtree.h
 * Quadtree class definition.
 * @date Spring 2008
 */

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

/**
 * A tree structure that is used to compress PNG images.
 */
class Quadtree
{
  public:
    Quadtree(); // no parameter constructor
    Quadtree(PNG const& source, int resolution); // constructor with parameters

    Quadtree(Quadtree const& other); // copy constructor
    const Quadtree& operator= (Quadtree const& other); //assignment overload operator
    ~Quadtree(); //destructor

    void buildTree(PNG const& source, int resolution); //builds a tree given the parameters
    RGBAPixel getPixel(int x, int y) const; //gets RGBA pixel @ the (x,y) coordinates.
    PNG decompress() const; // returns the underlying PNG object by Quadtree
    void clockwiseRotate(); //rotate the image by 90 degrees
    void prune(int tolerance); 
    int pruneSize(int tolerance) const;
    int idealPrune(int numLeaves) const;
  private:
    /**
     * A simple class representing a single node of a Quadtree.
     * You may want to add to this class; in particular, it could
     * probably use a constructor or two...
     */
    class QuadtreeNode
    {
      public:
        QuadtreeNode* nwChild; /**< pointer to northwest child */
        QuadtreeNode* neChild; /**< pointer to northeast child */
        QuadtreeNode* swChild; /**< pointer to southwest child */
        QuadtreeNode* seChild; /**< pointer to southeast child */

        RGBAPixel element; /**< the pixel stored as this node's "data" */
        int x;
        int y;
        int res;

        QuadtreeNode(int x_cord, int y_cord, int resolution)
        {
          x = x_cord;
          y = y_cord;
          res = resolution;
          neChild = NULL; nwChild = NULL; 
          seChild = NULL; swChild = NULL;
        }

        QuadtreeNode()
        {
          x = 0; 
          y = 0;
          res = 0;
          neChild = NULL; nwChild = NULL;
          seChild = NULL; swChild = NULL;
        }
    };

    QuadtreeNode* root; /**< pointer to root of quadtree */

    QuadtreeNode* copy(QuadtreeNode* other_root); //makes a copy of the tree passed into it
    void clear(QuadtreeNode*& r_t); //deletes a tree passed into it

    //PRIVATE HELPER FNXS... SSSSHHHHH 
    void build(PNG const& source, int resolution, QuadtreeNode* root);
    RGBAPixel get_pix_time(int x, int y, QuadtreeNode* r_t)const;
    bool get_pix_valid(int x, int y, QuadtreeNode* r_t) const;
    void deComp(PNG & source, int resolution, QuadtreeNode* r_t) const;
    void rotate(QuadtreeNode*& r_t);
    void prune(QuadtreeNode*& r_t, int tolerance);
    bool check_prune(QuadtreeNode* to_check, QuadtreeNode* avg, int tolerance) const;
    int diff(RGBAPixel to_check, RGBAPixel avg) const;
    int pS(QuadtreeNode* r_t, int tolR) const;
    int iPrune(int numLeaves, int begin, int current, int end) const;




/**** Functions for testing/grading                      ****/
/**** Do not remove this line or copy its contents here! ****/
#include "quadtree_given.h"
};

#endif
