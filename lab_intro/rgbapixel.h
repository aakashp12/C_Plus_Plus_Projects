#ifndef RGBAPIXEL_H
#define RGBAPIXEL_H

#include <cstdint>
using std::uint8_t;

class RGBAPixel
{

	public:
		
		uint8_t red;
		uint8_t green;
		uint8_t blue;
		uint8_t alpha;
		
		/*
		*	a default pizel is completely opaque and white. alpha = 255
		*/
		RGBAPixel();
		
		/*
		*	Byte for the red component of the pixel
		*/
		RGBAPixel(uint8_t red, uint8_t green, uint8_t blue);
		
};
#endif
