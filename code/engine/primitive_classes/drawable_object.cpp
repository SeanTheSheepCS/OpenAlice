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

int DrawableObject::getCentreX() const
{
	return (x+(width/2));
}

int DrawableObject::getCentreY() const
{
	return (y+(height/2));
}

void DrawableObject::setX(int newX)
{
	this->x = newX;
}

void DrawableObject::setY(int newY)
{
	this->y = newY;
}

void DrawableObject::setWidth(unsigned int newWidth)
{
	this->width = newWidth;
}

void DrawableObject::setHeight(unsigned int newHeight)
{
	this->height = newHeight;
}

