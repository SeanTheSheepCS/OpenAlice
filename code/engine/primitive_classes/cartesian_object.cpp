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

	unsigned char charOneOfXArg = (((unsigned char)(x >> 24)) & 0xFF);
	unsigned char charTwoOfXArg = (((unsigned char)(x >> 16)) & 0xFF);
	unsigned char charThreeOfXArg = (((unsigned char)(x >> 8)) & 0xFF);
	unsigned char charFourOfXArg = (((unsigned char)(x >> 0)) & 0xFF);
	returnValue.push_back(charOneOfXArg);
	returnValue.push_back(charTwoOfXArg);
	returnValue.push_back(charThreeOfXArg);
	returnValue.push_back(charFourOfXArg);

	unsigned char charOneOfYArg = (((unsigned char)(y >> 24)) & 0xFF);
	unsigned char charTwoOfYArg = (((unsigned char)(y >> 16)) & 0xFF);
	unsigned char charThreeOfYArg = (((unsigned char)(y >> 8)) & 0xFF);
	unsigned char charFourOfYArg = (((unsigned char)(y >> 0)) & 0xFF);
	returnValue.push_back(charOneOfYArg);
	returnValue.push_back(charTwoOfYArg);
	returnValue.push_back(charThreeOfYArg);
	returnValue.push_back(charFourOfYArg);

	unsigned char charOneOfWidth = (((unsigned char)(width >> 24)) & 0xFF);
	unsigned char charTwoOfWidth = (((unsigned char)(width >> 16)) & 0xFF);
	unsigned char charThreeOfWidth = (((unsigned char)(width >> 8)) & 0xFF);
	unsigned char charFourOfWidth = (((unsigned char)(width >> 0)) & 0xFF);
	returnValue.push_back(charOneOfWidth);
	returnValue.push_back(charTwoOfWidth);
	returnValue.push_back(charThreeOfWidth);
	returnValue.push_back(charFourOfWidth);

	unsigned char charOneOfHeight = (((unsigned char)(height >> 24)) & 0xFF);
	unsigned char charTwoOfHeight = (((unsigned char)(height >> 16)) & 0xFF);
	unsigned char charThreeOfHeight = (((unsigned char)(height >> 8)) & 0xFF);
	unsigned char charFourOfHeight = (((unsigned char)(height >> 0)) & 0xFF);
	returnValue.push_back(charOneOfHeight);
	returnValue.push_back(charTwoOfHeight);
	returnValue.push_back(charThreeOfHeight);
	returnValue.push_back(charFourOfHeight);

	return returnValue;
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
