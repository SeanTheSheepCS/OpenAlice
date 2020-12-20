#include "cartesian_object.h"

CartesianObject::CartesianObject(int xArg, int yArg, unsigned int widthArg, unsigned int heightArg)
{
	this->x = xArg;
	this->y = yArg;
	this->width = widthArg;
	this->height = heightArg;
}

std::vector<unsigned char> CartesianObject::toWriteableForm() const
{
	std::vector<unsigned char> returnValue;

	std::vector<unsigned char> xAsUnsignedCharArray = unsignedIntToUnsignedCharVector(x);
	returnValue.insert(returnValue.end(), xAsUnsignedCharArray.begin(), xAsUnsignedCharArray.end());

	std::vector<unsigned char> yAsUnsignedCharArray = unsignedIntToUnsignedCharVector(y);
	returnValue.insert(returnValue.end(), yAsUnsignedCharArray.begin(), yAsUnsignedCharArray.end());

	std::vector<unsigned char> widthAsUnsignedCharArray = unsignedIntToUnsignedCharVector(width);
	returnValue.insert(returnValue.end(), widthAsUnsignedCharArray.begin(), widthAsUnsignedCharArray.end());

	std::vector<unsigned char> heightAsUnsignedCharArray = unsignedIntToUnsignedCharVector(height);
	returnValue.insert(returnValue.end(), heightAsUnsignedCharArray.begin(), heightAsUnsignedCharArray.end());

	return returnValue;
}

void CartesianObject::fillWithDataFromWriteableForm(std::istream_iterator<unsigned char>& writeableFormIterator)
{
	this->x = readIntFromUnsignedCharIterator(writeableFormIterator);
	this->y = readIntFromUnsignedCharIterator(writeableFormIterator);
	this->width = readUnsignedIntFromUnsignedCharIterator(writeableFormIterator);
	this->height = readUnsignedIntFromUnsignedCharIterator(writeableFormIterator);
}

int CartesianObject::getX() const
{
	return x;
}

int CartesianObject::getY() const
{
	return y;
}

unsigned int CartesianObject::getWidth() const
{
	return width;
}

unsigned int CartesianObject::getHeight() const
{
	return height;
}

int CartesianObject::getCentreX() const
{
	return (x+(width/2));
}

int CartesianObject::getCentreY() const
{
	return (y+(height/2));
}

void CartesianObject::setX(int newX)
{
	this->x = newX;
}

void CartesianObject::setY(int newY)
{
	this->y = newY;
}

void CartesianObject::setWidth(unsigned int newWidth)
{
	this->width = newWidth;
}

void CartesianObject::setHeight(unsigned int newHeight)
{
	this->height = newHeight;
}
