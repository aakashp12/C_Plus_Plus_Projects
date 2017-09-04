/**
 * @file quadtree.cpp
 * Quadtree class implementation.
 * @date Spring 2008
 */
#include "quadtree.h"
Quadtree::Quadtree()
{
	root = NULL; // only have to return NULL, no creation of new objects
}

Quadtree::Quadtree(PNG const& source, int resolution)
{
	root = NULL;
	buildTree(source, resolution); //just have to build a tree, so call this function.
}

Quadtree::Quadtree(Quadtree const& other)
{
	if(other.root == NULL)	// if other's root == NULL then yourr job got easy! dont do anything
	{
		root = NULL;
		return;	
	}
	root = copy(other.root);	//if not, then stary copying into this from other
}
Quadtree const& Quadtree::operator= (Quadtree const& other)
{
	if(root != other.root)
	{
		clear(root);
		root = copy(other.root);
	}
	return *this;
}	

Quadtree::QuadtreeNode* Quadtree::copy(QuadtreeNode* other_root) //passed the root for other and this is going 
{															//to be recursive
	if(other_root == NULL)	//again if NULL make the other one NULL too
	{
		return NULL;
	}

	QuadtreeNode* n_root = new QuadtreeNode(other_root->x, other_root->y, other_root->res); // create a new node

	n_root->element = other_root->element;	//set this's node to value of element
	//root->x = other_root->x;	// copy the x and  y
	//root->y = other_root->y;
	//root->res = other_root->res; // copy the resolution

	n_root->nwChild = copy(other_root->nwChild); // copy the NW child's
	n_root->swChild = copy(other_root->swChild); // copy the SW child's
	n_root->neChild = copy(other_root->neChild); // copy the NE child's
	n_root->seChild = copy(other_root->seChild); // copy the SE child's
	return n_root;
}

Quadtree::~Quadtree()
{
	clear(root);
}

void Quadtree::clear(QuadtreeNode*& r_t)
{
	if(r_t == NULL)
	{
		return;
	}
	clear(r_t->nwChild); // copy the NW child's
	clear(r_t->swChild); // copy the SW child's
	clear(r_t->neChild); // copy the NE child's
	clear(r_t->seChild); // copy the SE child's
		
	delete r_t;
	r_t = NULL;
	return;
}

//------------------------------------------------------------------------------//

void Quadtree::buildTree(PNG const& source, int resolution)
{
	clear(root); //deletes the current contents of this Quadtree object
	root = new QuadtreeNode(0 ,0, resolution);
	build(source, resolution, root);
	return;
}	

void Quadtree::build(PNG const& source, int resolution, QuadtreeNode* root)
{
	if(resolution == 1)
	{
		root->element = *(source(root->x, root->y));// put things in leaf nodes if resolution == 1
		return;
	}
									//(int x, int y, int resolution)
	root->nwChild = new QuadtreeNode(root->x, root->y, resolution / 2);
	root->swChild = new QuadtreeNode(root->x, root->y + resolution / 2, resolution / 2);
	root->neChild = new QuadtreeNode(root->x + resolution / 2, root->y, resolution / 2);
	root->seChild = new QuadtreeNode(root->x + resolution / 2, root->y + resolution / 2, resolution / 2);

	build(source, resolution / 2, root->nwChild);
	build(source, resolution / 2, root->swChild);
	build(source, resolution / 2, root->neChild);
	build(source, resolution / 2, root->seChild);

	uint8_t r_d = (root->nwChild->element.red + root->swChild->element.red + root->neChild->element.red + root->seChild->element.red) / 4;
	uint8_t g_n = (root->nwChild->element.green + root->swChild->element.green + root->neChild->element.green + root->seChild->element.green) / 4;
	uint8_t b_e = (root->nwChild->element.blue + root->swChild->element.blue + root->neChild->element.blue + root->seChild->element.blue) / 4;

	root->element.red = r_d;
	root->element.green = g_n;
	root->element.blue = b_e;
	return;
}

RGBAPixel Quadtree::getPixel(int x, int y)	const
{
	return get_pix_time(x, y, root);
}

RGBAPixel Quadtree::get_pix_time(int x, int y, QuadtreeNode* r_t) const
{
	if( (r_t->x == x && r_t->y == y && r_t->res == 1) || r_t->nwChild == NULL) //if one is null then rest are null
	{
		return r_t->element;
	}
	//put in return default PIXEL
	if(get_pix_valid(x, y, r_t->nwChild)) //call helper function to check if we should go into NW 
	{
		return get_pix_time(x, y, r_t->nwChild);
	}
	else if(get_pix_valid(x, y, r_t->swChild)) //call helper function to check if we should go into SW
	{
		return get_pix_time(x, y, r_t->swChild);
	}
	else if(get_pix_valid(x, y, r_t->neChild)) //call helper function to check if we should go into NE 
	{
		return get_pix_time(x, y, r_t->neChild);
	}
	else //then this is SE
	{
		return get_pix_time(x, y, r_t->seChild);
	}
}

bool Quadtree::get_pix_valid(int x, int y, QuadtreeNode* r_t) const
{
	int x_val = r_t->x + r_t->res;
	int y_val = r_t->y + r_t->res;

	return ( (x < x_val &&  x >= r_t->x ) && (y < y_val && y >= r_t->y) );
}

PNG Quadtree::decompress() const
{
	if(root == NULL) // there was nothing in here
	{
		PNG yourPNG;
		return yourPNG; //return default PNG
	}

	int res = root->res;
	PNG myPNG(res, res);

	deComp(myPNG, res, root);
	return myPNG;
}

void Quadtree::deComp(PNG & source, int resolution, QuadtreeNode* r_t) const
{
	if(r_t->nwChild == NULL && r_t->res != 1) //meaing r_t is leaf
	{
		for(int i = 0; i < resolution; i++)
		{
			for(int j = 0; j < resolution; j++)
			{
				*source(i + r_t->x, j + r_t->y) = r_t->element;
			}
		}
	}
	else if(r_t->nwChild == NULL && r_t->res == 1)
	{
		*source(r_t->x, r_t->y) = r_t->element;
	}

	else
	{
	//if(r_t->nwChild != NULL)
		deComp(source, resolution / 2, r_t->nwChild);
	//if(r_t->swChild != NULL)
		deComp(source, resolution / 2, r_t->swChild);
	//if(r_t->neChild != NULL)
		deComp(source, resolution / 2, r_t->neChild);
	//if(r_t->seChild != NULL)
		deComp(source, resolution / 2, r_t->seChild);
	}	
	return;
}

//------------------------------------------------------------------------------//

void Quadtree::clockwiseRotate()
{
	rotate(root); //call the helper function
	return;
}

void Quadtree::rotate(QuadtreeNode*& r_t)
{
	if(r_t->nwChild == NULL) //if we are at a leaf node don't do anything
		return;

	//std::cout << "Comes here?" << std::endl;
	QuadtreeNode* temp_nw = r_t->nwChild; //temp to hold just one of the childs

	r_t->nwChild = r_t->swChild; //sw
	r_t->swChild = r_t->seChild; //se
	r_t->seChild = r_t->neChild; //ne
	r_t->neChild = temp_nw; //nw

	r_t->nwChild->x = r_t->x; //update the X and Y values since we moved them
	r_t->nwChild->y = r_t->y;

	r_t->swChild->x = r_t->x;
	r_t->swChild->y = r_t->y + (r_t->res / 2);

	r_t->neChild->x = r_t->x + (r_t->res / 2);
	r_t->neChild->y = r_t->y;

	r_t->seChild->x = r_t->x + (r_t->res / 2);
	r_t->seChild->y = r_t->y + (r_t->res / 2);

	rotate(r_t->nwChild);
	rotate(r_t->neChild);
	rotate(r_t->seChild);
	rotate(r_t->swChild);
}

void Quadtree::prune(int tolerance)
{
	prune(root, tolerance); //helper function
	return;
}

void Quadtree::prune(QuadtreeNode*& r_t, int tolerance) 
{
	if(r_t == NULL)
		return;
	
	if(r_t->nwChild == NULL) //if at leaf don't do anything
		return;

	if(check_prune(r_t, r_t, tolerance)) //check the current node's avg value against it's child nodes 
	{	
		//std::cout << "HERE" << std::endl;						 //returns true if we can prune it
		clear(r_t->nwChild);	 //delete the subtrees
		clear(r_t->swChild);
		clear(r_t->neChild);
		clear(r_t->seChild);

		r_t->nwChild = NULL;
		r_t->swChild = NULL;
		r_t->neChild = NULL;
		r_t->seChild = NULL;
		return;
	}
	prune(r_t->nwChild, tolerance);
	prune(r_t->swChild, tolerance);
	prune(r_t->neChild, tolerance);
	prune(r_t->seChild, tolerance);
	return;
}

bool Quadtree::check_prune(QuadtreeNode* to_check, QuadtreeNode* avg, int tolerance) const
{
	//std::cout << "HERE" << endl;
	if(to_check == NULL) //useless statement
	{
		//std::cout << "HERE" << endl;
		return true;
	}
	if(to_check->nwChild == NULL) //meaning its at leaf node
	{
		if(diff(to_check->element, avg->element) > tolerance)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else if(to_check->nwChild != NULL)
	{
		if( check_prune(to_check->nwChild, avg, tolerance) && check_prune(to_check->swChild, avg, tolerance) 
			&& check_prune(to_check->neChild, avg, tolerance) && check_prune(to_check->seChild, avg, tolerance))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return true;
}

int Quadtree::diff(RGBAPixel to_check, RGBAPixel avg) const
{
	int total = 0;
	total += (to_check.red - avg.red) * (to_check.red - avg.red);
	total += (to_check.green - avg.green) * (to_check.green - avg.green);
	total += (to_check.blue - avg.blue) * (to_check.blue - avg.blue);
	return total; 
}

int Quadtree::pruneSize(int tolerance) const
{
	return pS(root, tolerance);

}

int Quadtree::pS(QuadtreeNode* r_t, int tolR) const
{
	if(r_t->nwChild == NULL)
	{
		return 1;
	}
	if(check_prune(r_t, r_t, tolR))
	{
		return 1;
	}
	
	return pS(r_t->nwChild, tolR) + pS(r_t->swChild, tolR) + pS(r_t->neChild, tolR) + pS(r_t->seChild, tolR);
}

int Quadtree::idealPrune(int numLeaves) const
{
	int begin = 0; //start at zero obiviously
	int end = (255*255) * 3; //end will be the highest number of nodes
	int current = (begin + end) / 2;
	if(pruneSize(begin) == numLeaves)
	{
		return begin;
	}
	else
	{
		return iPrune(numLeaves, begin, current, end);
	}
}

int Quadtree::iPrune(int numLeaves, int begin, int current, int end) const
{
	int ret_val = current;
	while(true)
	{
		if(pruneSize(current) <= numLeaves && pruneSize(current - 1) > numLeaves)
		{
			break;
		}
		if(pruneSize(current) <= numLeaves && pruneSize(current - 1) <= numLeaves)
		{
			end = current;
			current = (begin + current) / 2;
		}
		else if(pruneSize(current) > numLeaves)
		{
			begin = current;
			current = (end + current) / 2;
		}
	}
	return current;
}
