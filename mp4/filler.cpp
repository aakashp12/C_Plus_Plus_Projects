/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace. Heavily based on
 * old MP4 by CS225 Staff, Fall 2010.
 *
 * @author Chase Geigle
 * @date Fall 2012
 */
#include "filler.h"

animation filler::dfs::fillSolid(PNG& img, int x, int y, RGBAPixel fillColor,
                                 int tolerance, int frameFreq)
{
    /**
     * @todo Your code here! You should replace the following line with a
     * correct call to fill with the correct colorPicker parameter.
     */
     solidColorPicker solid(fillColor);
    return filler::dfs::fill(img, x , y, solid, tolerance, frameFreq);
}

animation filler::dfs::fillGrid(PNG& img, int x, int y, RGBAPixel gridColor,
                                int gridSpacing, int tolerance, int frameFreq)
{
    /**
     * @todo Your code here! You should replace the following line with a
     * correct call to fill with the correct colorPicker parameter.
     */
     gridColorPicker grid(gridColor, gridSpacing);
    return filler::dfs::fill(img, x, y, grid, tolerance, frameFreq);
}

animation filler::dfs::fillGradient(PNG& img, int x, int y,
                                    RGBAPixel fadeColor1, RGBAPixel fadeColor2,
                                    int radius, int tolerance, int frameFreq)
{
    /**
     * @todo Your code here! You should replace the following line with a
     * correct call to fill with the correct colorPicker parameter.
     */
     gradientColorPicker gradient(fadeColor1, fadeColor2, radius, x, y);
    return filler::dfs::fill(img, x, y, gradient, tolerance, frameFreq);
}

animation filler::dfs::fill(PNG& img, int x, int y, colorPicker& fillColor,
                            int tolerance, int frameFreq)
{
    /**
     * @todo Your code here! You should replace the following line with a
     * correct call to filler::fill with the correct template parameter
     * indicating the ordering structure to be used in the fill.
     */
    return filler::fill<Stack>(img, x, y, fillColor, tolerance, frameFreq);
}

animation filler::bfs::fillSolid(PNG& img, int x, int y, RGBAPixel fillColor,
                                 int tolerance, int frameFreq)
{
    /**
     * @todo Your code here! You should replace the following line with a
     * correct call to fill with the correct colorPicker parameter.
     */
     solidColorPicker solid(fillColor);
    return filler::bfs::fill(img, x, y, solid, tolerance, frameFreq);
}

animation filler::bfs::fillGrid(PNG& img, int x, int y, RGBAPixel gridColor,
                                int gridSpacing, int tolerance, int frameFreq)
{
    /**
     * @todo Your code here! You should replace the following line with a
     * correct call to fill with the correct colorPicker parameter.
     */
     gridColorPicker grid(gridColor, gridSpacing);
    return filler::bfs::fill(img, x, y, grid, tolerance, frameFreq);
}

animation filler::bfs::fillGradient(PNG& img, int x, int y,
                                    RGBAPixel fadeColor1, RGBAPixel fadeColor2,
                                    int radius, int tolerance, int frameFreq)
{
    /**
     * @todo Your code here! You should replace the following line with a
     * correct call to fill with the correct colorPicker parameter.
     */
     gradientColorPicker gradient(fadeColor1, fadeColor2, radius, x, y);
    return filler::bfs::fill(img, x, y, gradient, tolerance, frameFreq);
}

animation filler::bfs::fill(PNG& img, int x, int y, colorPicker& fillColor,
                            int tolerance, int frameFreq)
{
    /**
     * @todo Your code here! You should replace the following line with a
     * correct call to filler::fill with the correct template parameter
     * indicating the ordering structure to be used in the fill.
     */
     animation Anime = filler::fill<Queue>(img, x, y, fillColor, tolerance, frameFreq);
    return Anime;
}

template <template <class T> class OrderingStructure>
animation filler::fill(PNG& img, int x, int y, colorPicker& fillColor,
                       int tolerance, int frameFreq)
{
    //BFS- QUEUE, DFS- STACK
    int height = img.height();
    int width = img.width();

    int **check = new int*[height]; //we'll use this to keep track and see if we already took care of this pixel
    for(int i = 0; i < height; i++)
    {
        check[i] = new int[width];
    }

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            check[i][j] = 0;
        }
    }

    OrderingStructure<int> Xcoords; //create structure for co-ordinates
    OrderingStructure<int> Ycoords; 

    Xcoords.add(x);
    Ycoords.add(y);

    RGBAPixel pixel_val = *(img(x,y)); //get the pixel information from img co-ordinates x, y
    int origRed = pixel_val.red;
    int origGreen = pixel_val.green;
    int origBlue = pixel_val.blue;
	
    animation Anime; 
    int F_count = 0; // frame counter

    while( (Xcoords.isEmpty() != true) && (Ycoords.isEmpty() != true))
    {
        int currX = Xcoords.remove(); //get the curent x and y co-ordinates
        int currY = Ycoords.remove();

		RGBAPixel pixel_temp2 = *(img(currX, currY));
        int currRed = pixel_temp2.red; //get the current pixel position's colors
        int currGreen = pixel_temp2.green;
        int currBlue = pixel_temp2.blue;

        int tolRed = (currRed - origRed) * (currRed - origRed); //square the difference of curr - original
        int tolGreen = (currGreen - origGreen) * (currGreen - origGreen);
        int tolBlue = (currBlue- origBlue) * (currBlue- origBlue);

        int tolTotal = tolRed + tolGreen + tolBlue; //add them to get the total

        if(check[currY][currX] == 0 && (tolTotal <= tolerance)) //check if it HAS NOT been 
        {                                               //processed and if <= tolerance
            check[currY][currX] = 1; //mark it as processed
            *(img(currX, currY)) = fillColor(currX, currY);

            if(currX + 1 < width)
            {
                Xcoords.add(currX + 1); //add the right pixel into the mix
                Ycoords.add(currY);
            }
            
            if(currY + 1 < height)
            {
                Ycoords.add(currY + 1); //add the bottom pixel into the mix
                Xcoords.add(currX);
            }           

            if(currX - 1 >= 0)
            {
                Xcoords.add(currX - 1); //add the left pixel into the mix
                Ycoords.add(currY);
            }
            
            if(currY - 1 >= 0)
            {
                Ycoords.add(currY - 1); //add the upper pixel into the mix
                Xcoords.add(currX);
            }

            F_count ++; //add the frame counter, and when it hits the frameFreq we can animate it.
            
            if(F_count % frameFreq == 0)
            {
                Anime.addFrame(img);
            }
        }
        else if(check[currY][currX] == 0 && (tolTotal > tolerance) )
        	check[currY][currX] = 1;
    }

    for(int i = 0; i < height; i++)
        delete [] check[i];
    delete []check;

    return Anime;
}
