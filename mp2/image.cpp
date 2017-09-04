#include "image.h"

void Image::flipleft()
{
	size_t Width = this->width(); //holds Width
	//cout << "Width: " << Width << endl;
	size_t Height = this->height(); //holds Height
	//cout << "Height: " << Height << endl;
	size_t A_Center = (Width / 2) - 1; //holds ARRAY center
	//cout << "A_Center: " << A_Center << endl;

	//RGBAPixel RGBA = *(*this)(3,2); // temp Pixel that holds R G B A values
	//cout << "RGBA: " << RGBA << endl;	
	//size_t value = (*this)(3,2)->red;
	//cout << "Value: " << value << endl;
	if(Width % 2 == 0)
	{
		for(size_t y = 0; y < Height; y++)
		{
			size_t R_Center = (Width / 2); //holds ACTUAL center
			for(size_t x = 0; x <= A_Center; x++)
			{	
				uint8_t R = (*this)(x,y)->red;
				uint8_t G = (*this)(x,y)->green;
				uint8_t B = (*this)(x,y)->blue;

				(*this)(x,y)->red = (*this)(R_Center + A_Center, y)->red;
				(*this)(x,y)->green = (*this)(R_Center + A_Center, y)->green;
				(*this)(x,y)->blue = (*this)(R_Center + A_Center, y)->blue;

				(*this)(R_Center + A_Center, y)->red = R;
				(*this)(R_Center + A_Center, y)->green = G;
				(*this)(R_Center + A_Center, y)->blue = B;

				R_Center--;
			}
		}

	}
	else
	{
		for(size_t y = 0; y < Height; y++)
		{
			size_t R_Center = (Width / 2); //holds ACTUAL center
			for(size_t x = 0; x <= A_Center; x++)
			{	
				uint8_t R = (*this)(x,y)->red;
				uint8_t G = (*this)(x,y)->green;
				uint8_t B = (*this)(x,y)->blue;

				(*this)(x,y)->red = (*this)(R_Center + A_Center + 1, y)->red;
				(*this)(x,y)->green = (*this)(R_Center + A_Center + 1, y)->green;
				(*this)(x,y)->blue = (*this)(R_Center + A_Center + 1, y)->blue;

				(*this)(R_Center + A_Center + 1, y)->red = R;
				(*this)(R_Center + A_Center + 1, y)->green = G;
				(*this)(R_Center + A_Center + 1, y)->blue = B;
			
				R_Center--;
			}	
		}
	
	}

}

void Image::adjustbrightness(int r, int g, int b)
{
	size_t Width = this->width();
	size_t Height = this->height();

	for(size_t x = 0; x < Width; x++)
	{
		for(size_t y = 0; y < Height; y++)
		{		
			int R = (*this)(x,y)->red; // make the pixel values into int
			int G = (*this)(x,y)->green;
			int B = (*this)(x,y)->blue;

			//cout << R << endl;	//debug
		
			if(R + r < 0) { (*this)(x,y)->red = 0;} // who knew C++ had if, else if, else like Python
			else if(R + r > 255) { (*this)(x,y)->red = 255;} //made code way way shorter
			else{ (*this)(x,y)->red += r;} 
			
			if(G + g < 0){ (*this)(x,y)->green = 0;} //Basically compare the current amount + adjustmend
			else if(G + g > 255) { (*this)(x,y)->green = 255;} //if less then 0 or greater than 255
			else { (*this)(x,y)->green += g;} // then cap it otherwise add it up and make it the actual value

			if(B + b < 0){ (*this)(x,y)->blue = 0;}
			else if(B + b > 255) { (*this)(x,y)->blue = 255;}
			else { (*this)(x,y)->blue += b;}

			//*(*this)(x,y) = RGBA;		
		}
	}
}

void Image::invertcolors()
{
	size_t Width = this->width();
	size_t Height = this->height();

	for(size_t y = 0; y < Height; y++)
	{
		for(size_t x = 0; x < Width; x++)
		{	
			uint8_t R = (*this)(x,y)->red;
			uint8_t G = (*this)(x,y)->green;
			uint8_t B = (*this)(x,y)->blue;
			
			(*this)(x,y)->red = 255 - R;
			(*this)(x,y)->green = 255 - G;
			(*this)(x,y)->blue = 255 - B;
		}
	}
}
