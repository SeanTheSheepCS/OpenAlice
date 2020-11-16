#include "object_with_texture_map.h"

ObjectWithTextureMap::ObjectWithTextureMap()
{
	currentTextureReferenceNumber = 0;
}

void ObjectWithTextureMap::associateReferenceNumberWithTexturePointer(int referenceNumber, const sf::Texture* texturePointer)
{
	refNumberToTexturePointerMap.insert(std::pair<int, const sf::Texture*>(referenceNumber, texturePointer));
}

void ObjectWithTextureMap::deassociateTexturePointerWithSpecifiedReferenceNumber(int referenceNumber)
{
	refNumberToTexturePointerMap.erase(referenceNumber);
}

void ObjectWithTextureMap::setCurrentTextureReferenceNumber(int newReferenceNumber)
{
	currentTextureReferenceNumber = newReferenceNumber;
}

const sf::Texture* ObjectWithTextureMap::getCurrentTexture() const 
{
	try
	{
		return refNumberToTexturePointerMap.at(currentTextureReferenceNumber);
	}
	catch(std::exception& e)
	{
		return nullptr;
	}
}

const sf::Texture* ObjectWithTextureMap::getTextureWithSpecificReferenceNumber(int referenceNumber) const
{
	return refNumberToTexturePointerMap.at(referenceNumber);
}
