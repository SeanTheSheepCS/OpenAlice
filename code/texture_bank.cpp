#include "texture_bank.h"

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
    return &(referenceNumberToTextureMap.at(referenceNumber));
}

void TextureBank::deleteTextureWithReferenceNumber(int referenceNumber)
{
    referenceNumberToTextureMap.erase(referenceNumber);
}
