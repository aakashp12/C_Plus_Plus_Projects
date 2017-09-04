#include "scene.h"


Scene::Scene(int max_arg)
{
	max = max_arg;
	layers = new Image* [max];//the double ** creates an array of pointers
	
	xcord = new int[max]; //x is pointer to array of x COORDINATEs
	ycord = new int[max]; //y is pointer to array of y COORDINATEs

	for(int k = 0; k < max; k++) //for loop that intializes each image poiinter to NULL
	{
		layers[k] = NULL;
		xcord[k] = 0;
		ycord[k] = 0;
	}
}

Scene::~Scene()
{
	clear();
}

void Scene::copy(const Scene& other)
{
	max = other.max;
	layers = new Image*[max];
	xcord = new int[max];
	ycord = new int[max];
	for(int k = 0; k < max; k++)
	{
		if(other.layers[k] == NULL)
			layers[k] = NULL;
		else
			layers[k] = new Image( *(other.layers[k]));
		xcord[k] = other.xcord[k];
		ycord[k] = other.ycord[k];
	}
}

void Scene::clear()
{
	for(int k = 0; k < max; k++)
	{
		delete layers[k];
	}
	delete [] layers;
	delete [] xcord;
	delete [] ycord;
}

Scene::Scene( const Scene & source)
{
	copy(source);
}

const Scene& Scene::operator=( const Scene & source)
{
	if(this != &source)
	{
		clear();
		copy(source);
	}
	return *this;
}

void Scene::changemaxlayers(int newmax)
{
	if(newmax < max) //if newmax = 3, and max = 5. check if the index 3 and 4 are non-null
	{
		for(int k = newmax; k < max; k++) //checking if index newmax to max are non-null
		{
			if(layers[k] != NULL)
			{
				cout << "invalid newmax" << endl;
				return;
			}
		}
	}

	if(newmax < max)
	{
		Image** l_copy = new Image*[newmax]; //create a temporary layer array
		int* x_copy = new int[newmax]; //create a temporary xcord array
		int* y_copy = new int[newmax]; //createa a temporary ycord array

		for(int k = 0; k < newmax; k++)
		{
			l_copy[k] = layers[k]; //copy the info from layers to temp
			x_copy[k] = xcord[k]; //copy the co-ordinates 
			y_copy[k] = ycord[k];
		}

		delete [] layers; // delete layers
		delete [] xcord; //delete co-ordinates
		delete [] ycord;

		layers = new Image*[newmax]; //create layers with new size
		xcord = new int[newmax]; //create co-ordinates with new size
		ycord = new int[newmax];

		for(int k = 0; k < newmax; k++)
		{
			layers[k] = l_copy[k]; //copied the info back into the new layers
			xcord[k] = x_copy[k]; //copied the co-ordinates into new arrays
			ycord[k] = y_copy[k];
		}

		delete [] l_copy; //delete the copies we made so no memory leak
		delete [] x_copy;
		delete [] y_copy;
	}
	else
	{
		Image** l_copy = new Image*[max]; //create a temporary layer array size of max if newmax > max
		int* x_copy = new int[max]; //create a temporary xcord array
		int* y_copy = new int[max]; //createa a temporary ycord array

		for(int k = 0; k < max; k++) //copy from 0 to max, because newmax > max
		{
			l_copy[k] = layers[k]; //copy the info from layers to temp
			x_copy[k] = xcord[k]; //copy the co-ordinates 
			y_copy[k] = ycord[k];
		}

		delete [] layers; // delete layers
		delete [] xcord; //delete co-ordinates
		delete [] ycord;

		layers = new Image*[newmax]; //create layers with new size
		xcord = new int[newmax]; //create co-ordinates with new size
		ycord = new int[newmax];

		for(int k = 0; k < max; k++)
		{
			layers[k] = l_copy[k]; //copied the info back into the new layers
			xcord[k] = x_copy[k]; //copied the co-ordinates into new arrays
			ycord[k] = y_copy[k];
		}

		for(int k = max; k < newmax; k++)
		{
			layers[k] = NULL;
			xcord[k] = 0;
			ycord[k] = 0;
		}

		delete [] l_copy; //delete the copies we made so no memory leak
		delete [] x_copy;
		delete [] y_copy;
	}
}

void Scene::addpicture(const char*FileName, int index, int x, int y)
{
	if(index < 0 || index > (max-1))
	{
		cout << "index out of bounds" << endl;
	}
	
	else
	{
		Image *img_ptr = new Image();
		img_ptr->readFromFile(FileName);
		//cout << "img_ptr" <<img_ptr << endl; //debug
		layers[index]= img_ptr;
		xcord[index] = x;
		ycord[index] = y;
	}
}

void Scene::changelayer(int index, int newindex)
{
	if(index == newindex)
	{
		return;
	}
	else if( index > (max - 1) || index < 0 || newindex > (max - 1) || newindex < 0)
	{
		cout << "invalid index" << endl;
	}	
	else
	{
		if(layers[newindex] != NULL)
		{	
			delete layers[newindex];
			layers[newindex] = NULL;
		}
			layers[newindex] = layers[index]; // defrence layers[index] and assign the value to newindex
			layers[index] = NULL;

			xcord[newindex] = xcord[index];
			ycord[newindex] = ycord[index];
			xcord[index] = 0;
			ycord[index] = 0;
		}
}

void Scene::translate(int index, int xcoord, int ycoord)
{
	if(index > (max - 1) || index < 0 || layers[index] == NULL)
	{
		cout << "invalid index" << endl;
	}

	else
	{
		xcord[index] = xcoord; //xcord[index] holds the current x co-ordinate
		ycord[index] = ycoord;// ycord[index] holds the current y co-ordinate
	}
}
void Scene::deletepicture(int index)
{
	if(index > max-1 || index < 0 || layers[index] == NULL)
	{
		cout << "invalid index" << endl;
	}

	else
	{
		delete layers[index]; //deletes the pointer point at the image
		layers[index] = NULL;
		xcord[index] = 0;
		ycord[index] = 0;
	}
}

Image* Scene::getpicture(int index) const
{
	if(index > (max-1) || index < 0 || layers[index] == NULL)
	{
		cout << "Invalid Index" << endl;
		return NULL;
	}

	return layers[index];
}

Image Scene::drawscene() const
{
	size_t w = 0; //using these variables and for loop
	size_t h = 0; //to get values for height and width
	//cout << "works untill here" << endl;
	for(int k = 0; k < max; k++)
	{
		if(layers[k] != NULL)
		{
			if(h < layers[k]->height() + ycord[k]) //check for the biggest height and make it your size
				h = layers[k]->height() + ycord[k];
			if(w < layers[k]->width() + xcord[k]) //check for the biggest width and make it your size
				w = layers[k]->width() + xcord[k];
		}
	}	

	Image new_pic; //create a new image
	new_pic.resize(w,h); //resize it to the size we found before hand 
	//cout << "Works here" << endl; //debug
 	for(int k = 0; k < max; k++) //go through different layers starting from 0 to max-1
	{
		//cout << "Works for" << k << endl; //debug
		if(layers[k] != NULL)
		{
			for(size_t x = 0; x < layers[k]->width(); x++) //from 0 to width of the layer
			{
				for(size_t y = 0; y < layers[k]->height(); y++) //from 0 to height of the layer
				{
					new_pic(x + xcord[k], y + ycord[k])->red = (*layers[k])(x,y)->red; // pass the values over
					new_pic(x + xcord[k], y + ycord[k])->green = (*layers[k])(x,y)->green; //x + xcord gets you the specific place 
					new_pic(x + xcord[k], y + ycord[k])->blue = (*layers[k])(x,y)->blue; //to start putting the pixels in 
				}
			}
		}
	}
	return new_pic;
}

