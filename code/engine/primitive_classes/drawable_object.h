#ifndef DRAWABLE_OBJECT_H
#define DRAWABLE_OBJECT_H

#include <SFML/Graphics.hpp>

class DrawableObject
{
    public:
	    DrawableObject(int x, int y, int width, int height);
    protected:
	    int x;
	    int y;
	    int width;
	    int height;
    private:
	    //
};

#endif
