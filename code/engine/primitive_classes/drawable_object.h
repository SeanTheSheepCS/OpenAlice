#ifndef DRAWABLE_OBJECT_H
#define DRAWABLE_OBJECT_H

#include <SFML/Graphics.hpp>

class DrawableObject
{
    public:
	    DrawableObject(int x, int y, unsigned int width, unsigned int height);
        virtual void draw(sf::RenderWindow& windowToDrawObjectIn) = 0;
    protected:
	    int x;
	    int y;
	    unsigned int width;
	    unsigned int height;
    private:
	    //
};

#endif
