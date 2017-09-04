#ifndef RGBAPixel_H
#define RGBAPixel_H

#include <cstdint>
using std::uint8_t

class RGBAPixel
{
	public:
		uint8_t red;
		uint8_t green;		
		uint8_t blue;
		uint8_t alpha;

	       /*
 		* Default constructor 
		*/

		RGBAPixel();

	       /*
 		* Assign values from beginning
 		*/

		RGBAPixel(uint8_t r, uint8_t g, uint8_t b);
};
#endif



