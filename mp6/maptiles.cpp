/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{
    /**
     * @todo Implement this function!
     */
    vector< Point<3>> convert ; //we'll need this to convert from tileImage to x,y,z co-ods
    map<Point<3>, TileImage> image; //make the key = converted RGBAPixel, value = theTiles

    auto row_num = theSource.getRows();
    auto col_num = theSource.getColumns();
    auto tile_size = theTiles.size();

    MosaicCanvas::MosaicCanvas* new_pic = new MosaicCanvas(row_num, col_num); //dynamically allocated MosaicCanvas

    for(unsigned long i = 0; i < tile_size; i++)
    {
		RGBAPixel temp_tile = theTiles.at(i).getAverageColor(); //get the RGBAPixel values
		Point<3> temp(temp_tile.red, temp_tile.green, temp_tile.blue); //put them in Point<3>
		//we converted from RGBAPixel to Point<3>
		image[temp] = theTiles.at(i);//since we made a MAP, the key is Point<3> and value is a tile
		convert.push_back(temp); //push 
    }

    KDTree<3>::KDTree newpic(convert);

    for(int i = 0; i < row_num; i++)
    {
        for(int j = 0; j < col_num; j++)
        {
            RGBAPixel temp_source = theSource.getRegionColor(i,j); //get the region color from theSource
            //once you get the region avg of a certain x,y co-od conver it to Point<3>
            Point<3> regionavg(temp_source.red, temp_source.green, temp_source.blue); //covert to Point<3>
            //then find the nearestNeighbor that matches the regionAvg
            Point<3> NN = newpic.findNearestNeighbor(regionavg);
            //once you find that, get the tile co-responding to that Point<3> value
            TileImage temp = image[NN]; //this gives you a tile(another image, that matches the regionavg)
            //now we got the co-responding tile, we send all the info to canvas
            new_pic->setTile(i, j, temp);
            //we should be done
        }
    }
    return new_pic;
}

