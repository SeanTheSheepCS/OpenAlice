#include "drawable_object.h"

DrawableObject::DrawableObject(int xArg, int yArg, unsigned int widthArg, unsigned int heightArg)
{
    this->x = xArg;
    this->y = yArg;
    this->width = widthArg;
    this->height = heightArg;
}

int DrawableObject::getX() const
{
    return x;
}

int DrawableObject::getY() const
{
    return y;
}

unsigned int DrawableObject::getWidth() const
{
    return width;
}

unsigned int DrawableObject::getHeight() const
{
    return height;
}
