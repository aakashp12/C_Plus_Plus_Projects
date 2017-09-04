#include <iostream>
#include <algorithm>

#include "png.h"
#include "rgbapixel.h"

using  namespace std;

PNG rotate(PNG image);
/*
 * We'll use this function to open the image and call functions
 */
int main()
{
	PNG image("in.png"); // open the file and store the info into image
	image = rotate(image); // store the returned image into image
	image.writeToFile("out.png"); // write out a out.png file
	
	return 0;
}

/*
 *  Rotate funtion take a image and rotates it 180 degrees
 *  I make a copy of the image that needs to be rotated and save it in a temp
 *  Data of both the PNG variable are the same
 *  Data from the out_image is copied into image
 *  Hence, the image file is being rotated
 *  In the end, image is rotated and then I returned image 
 */
PNG rotate(PNG image)
{
	PNG out_image(image);
	//Y is height
	for(size_t x = 0; x < image.width(); x++)
	{
		//X is width
		for(size_t y = 0; y < image.height(); y++)
		{
			image(image.width()-1-x, image.height()-1-y)->red = out_image(x,y)->red;
			image(image.width()-1-x, image.height()-1-y)->green = out_image(x,y)->green;
			image(image.width()-1-x, image.height()-1-y)->blue = out_image(x,y)->blue;			}
	}
	return image;
}
