#include "number_display_texture_pack.h"

NumberDisplayTexturePack::NumberDisplayTexturePack()
{
    numberDisplayBackgroundTexturePointer = nullptr;
    arrayOfTexturePointersEachIndexStoresAPointerToTheNumberTheTextureRepresents = nullptr;
}

void NumberDisplayTexturePack::decoupleBackgroundTexture()
{
    numberDisplayBackgroundTexturePointer = nullptr;
}

void NumberDisplayTexturePack::coupleWithBackgroundTexture(sf::Texture* backgroundTexture)
{
    numberDisplayBackgroundTexturePointer = backgroundTexture;
}

void NumberDisplayTexturePack::decoupleNumberTextureArray()
{
    arrayOfTexturePointersEachIndexStoresAPointerToTheNumberTheTextureRepresents = nullptr;
}

void NumberDisplayTexturePack::coupleWithNumberTextureArray(sf::Texture** numberTextureArray)
{
    arrayOfTexturePointersEachIndexStoresAPointerToTheNumberTheTextureRepresents = numberTextureArray;
}

sf::Texture* NumberDisplayTexturePack::getTexturePointerForBackground()
{
    return numberDisplayBackgroundTexturePointer;
}

sf::Texture* NumberDisplayTexturePack::getTexturePointerForSpecifiedTexture(int number)
{
    return arrayOfTexturePointersEachIndexStoresAPointerToTheNumberTheTextureRepresents[number];
}
