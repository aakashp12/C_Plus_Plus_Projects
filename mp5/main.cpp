/**
 * @file main.cpp
 * Contains code to test your Quadtree implementation.
 */

#include <iostream>
#include "png.h"
#include "quadtree.h"

using std::cout;
using std::endl;

int main()
{
    /*
    PNG imgIn, imgOut;
    imgIn.readFromFile("in.png");
//test getPixel 
    Quadtree halfTree(imgIn, 128);
    for(size_t i=0; i< 128; i++){
        for(size_t j=0; j < 128; j++){
            int red = (halfTree.getPixel(j,i)).red;
            int r = (*imgIn(j,i)).red;
            std::cout << "getpixel " << red << " png" << r << std::endl;
        }
    }
    */

//---------------------------------------------------------------//
    //xxxxx's test!!!
    /*
    PNG imgIn, imgOut;
    imgIn.readFromFile("in.png");

    // test constructor, decompress
    //Quadtree halfTree(imgIn, 128);
    
    
    //added test getPixel/ decompress / copy /assignment

    Quadtree halfTree(imgIn, 128);
   // halfTree.printTree(); // added
    RGBAPixel yo = halfTree.getPixel(3, 3);
    cout <<  "Red: " << (int)yo.red << " Green: " << (int)yo.green << " Blue: " << (int)yo.blue << endl;
    cout <<  "Red: " << (int)imgIn(3, 3)->red << " Green: " << (int)imgIn(3, 3)->green << " Blue: " << (int)imgIn(3, 3)->blue << endl;
    imgOut = halfTree.decompress();    
    imgOut.writeToFile("outHalf.png");
    cout<< "Width IMG IN: " << imgIn.width() << " Height IMG IN: " << imgIn.height() << endl;
    cout<< "Width IMG OUT: " << imgOut.width() << " Height IMG OUT: " << imgOut.height() << endl;

    Quadtree ntree(halfTree); //has W: 128, H:128
    PNG nimgOut, x;
    nimgOut = ntree.decompress(); //checking for copy and assignment overload
    nimgOut.writeToFile("noutHalf.png");
    
    Quadtree xi;
    xi = ntree;
    x =  xi.decompress();
    x.writeToFile("mout.png");
    */
//----------------------------------------------------------------//
    //GIVEN CODE
    PNG imgIn, imgOut;
    imgIn.readFromFile("in.png");

    // test constructor, decompress
    Quadtree halfTree(imgIn, 128);
    imgOut = halfTree.decompress();
    imgOut.writeToFile("outHalf.png");

    // now for the real tests
    Quadtree fullTree;
    fullTree.buildTree(imgIn, 256);

    // you may want to experiment with different commands in this section

    // test pruneSize and idealPrune (slow in valgrind, so you may want to
    // comment these out when doing most of your testing for memory leaks)

    cout << "fullTree.pruneSize(0) = "      << fullTree.pruneSize(0) << endl;
    cout << "fullTree.pruneSize(100) = "    << fullTree.pruneSize(100) << endl;
    cout << "fullTree.pruneSize(1000) = "   << fullTree.pruneSize(1000) << endl;
    cout << "fullTree.pruneSize(100000) = " << fullTree.pruneSize(100000) << endl;

    cout << "fullTree.idealPrune(1000) = "  << fullTree.idealPrune(1000) << endl;
    cout << "fullTree.idealPrune(10000) = " << fullTree.idealPrune(10000) << endl;

    // Test some creation/deletion functions
    Quadtree fullTree2;
    fullTree2 = fullTree;
    imgOut = fullTree2.decompress();
    imgOut.writeToFile("outCopy.png");

    // test clockwiseRotate
    fullTree.clockwiseRotate();
    imgOut = fullTree.decompress();
    imgOut.writeToFile("outRotated.png");
    std::cout << "File made:" << std::endl;


    // test prune
    fullTree = fullTree2;
    fullTree.prune(1000);
    imgOut = fullTree.decompress();
    imgOut.writeToFile("outPruned.png");

    // test several functions in succession
    Quadtree fullTree3(fullTree2);
    fullTree3.clockwiseRotate();
    fullTree3.prune(10000);
    fullTree3.clockwiseRotate();
    fullTree3.clockwiseRotate();
    fullTree3.clockwiseRotate();
    imgOut = fullTree3.decompress();
    imgOut.writeToFile("outEtc.png");

    // ensure that printTree still works
    Quadtree tinyTree(imgIn, 32);
    cout << "Printing tinyTree:\n";
    tinyTree.prune(100);
    tinyTree.printTree();

    return 0;
}
