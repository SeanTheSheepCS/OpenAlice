#include "drawable_object.h"

DrawableObject::DrawableObject(int xArg, int yArg, unsigned int widthArg, unsigned int heightArg): CartesianObject(xArg, yArg, widthArg, heightArg)
{
	
}

std::vector<unsigned char> DrawableObject::toWriteableForm() const
{
	std::vector<unsigned char> returnValue;
	
	std::vector<unsigned char> cartesianObjectToWrite = CartesianObject::toWriteableForm();
	returnValue.insert(returnValue.end(), cartesianObjectToWrite.begin(), cartesianObjectToWrite.end());

	return returnValue;
}

void DrawableObject::fillWithDataFromWriteableForm(std::vector<unsigned char>::iterator& writeableFormIterator)
{
	CartesianObject::fillWithDataFromWriteableForm(writeableFormIterator);
}
