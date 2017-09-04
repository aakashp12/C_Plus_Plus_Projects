#include <cstdlib>
#include "png.h"

using namespace std;
//
// sets up the output image
PNG* setupOutput(int w, int h)
{
    PNG* image = new PNG(w, h);
    return image;
}

// Returns my favorite color
RGBAPixel* myFavoriteColor(int intensity)
{
    RGBAPixel* color = new RGBAPixel();
    color->red   = 0;
    color->green = intensity / 2;
    color->blue  = intensity;
    return color;
}

void sketchify()
{
    // Load in.png
    PNG* original = new PNG();

   // cout << __LINE__<< endl;
   
    original->readFromFile("in.png");
    int width = original->width();
    int height = original->height();
   // cout << __LINE__  << endl;
    // Create out.png
    PNG* output;
    cout << __LINE__ << endl;
   // cout << __LINE__ << endl;
    output = setupOutput(width, height);
    
   // cout << __LINE__ << endl;
    // Load our favorite color to color the outline
    RGBAPixel* myPixel = myFavoriteColor(192);
    cout << __LINE__ << endl;
    // Go over the whole image, and if a pixel differs from that to its upper
    // left, color it my favorite color in the output
    for (int y = 1; y < height; y++) {
    for (int x = 1; x < width; x++) {
            // Calculate the pixel difference
        //    cout << __LINE__ << endl;
	    RGBAPixel* prev = (*original)(x - 1, y - 1);
	//    cout << __LINE__ << endl;
            RGBAPixel* curr = (*original)(x, y);
	//    cout << __LINE__ << endl;
            int diff = abs(curr->red - prev->red)
                       + abs(curr->green - prev->green)
                       + abs(curr->blue - prev->blue);

            // If the pixel is an edge pixel,
            // color the output pixel with my favorite color
            RGBAPixel* currOutPixel = (*output)(x, y);
            if (diff > 100)
	    {
	   	currOutPixel->red = myPixel->red;
		currOutPixel->green = myPixel->green;
		currOutPixel->blue = myPixel->blue;
            }
        }
    }

    // Save the output file
    output->writeToFile("out.png");

    // Clean up memory
   // delete myPixel;
    delete myPixel;
    delete output;
    delete original;
}
