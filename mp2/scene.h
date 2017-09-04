#ifndef SCENE_H
#define SCENE_H

#include "image.h"

class Scene
{
	public :

	Scene( int max_arg); //contructor
	~Scene(); //destructor
	Scene( const Scene & source); //copy constructor
	
	const Scene & operator=(const Scene & source); //aasignment operator
	void changemaxlayers(int newmax); //
	void addpicture( const char* FileName, int index, int x, int y);
	void changelayer( int index, int newindex);
	void translate( int index, int xcoord, int ycoord);
	void deletepicture( int index);
	Image *getpicture( int index) const;
	Image drawscene() const;

	private :
	Image** layers;
	int max;
	int *xcord; 
	int *ycord;
	void clear();
	void copy(const Scene & other);
};

#endif
