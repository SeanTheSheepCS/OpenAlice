#include "texture_bank.h"
#include <iostream>

TextureBank::TextureBank()
{
	//
}

void TextureBank::saveTextureWithReferenceNumber(int referenceNumber, sf::Texture textureToSave) 
{
	referenceNumberToTextureMap.insert(std::pair<int,sf::Texture>(referenceNumber, textureToSave));
}

const sf::Texture* TextureBank::getTextureAssociatedWithReferenceNumber(int referenceNumber) const
{
	try
	{
		return &(referenceNumberToTextureMap.at(referenceNumber));
	}
	catch(std::exception& e)
	{
		std::cout << "Failed to access texture in texture bank with reference number " << referenceNumber << "." << std::endl;
		return nullptr;
	}
}

void TextureBank::deleteTextureWithReferenceNumber(int referenceNumber)
{
	referenceNumberToTextureMap.erase(referenceNumber);
}
