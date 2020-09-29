#include "textured_object.h"
#include <iostream>

bool TexturedObject::isDefaultTextureInitialized = false;
sf::Texture TexturedObject::defaultTexture;

TexturedObject::TexturedObject(int xArg, int yArg, unsigned int widthArg, unsigned int heightArg, const sf::Texture* texturePointerArg): DrawableObject(xArg,yArg,widthArg,heightArg)
{
    this->texturePointer = texturePointerArg;
    if(isDefaultTextureInitialized == false)
    {
        if(defaultTexture.loadFromFile("../sprites/invalid_texture.png"))
        {
            isDefaultTextureInitialized = true;
        }
        else
        {
            std::cout << "Failed to load texture: ../sprites/invalid_texture.png" << std::endl;
        }
    }
}

void TexturedObject::decoupleObjectFromItsTexture()
{
    this->texturePointer = nullptr;
}

void TexturedObject::associateWithNewTexture(const sf::Texture* newTextureToAssociateWith)
{
    this->texturePointer = newTextureToAssociateWith;
}

void TexturedObject::draw(sf::RenderWindow& windowToDrawObjectIn)
{
    sf::RectangleShape rectangleToTexture(sf::Vector2f(this->width,this->height));
    rectangleToTexture.setPosition(this->x, this->y);
    try
    {
        if((this->texturePointer)!= nullptr) 
        {
            rectangleToTexture.setTexture(this->texturePointer);
        }
        else
        {
            rectangleToTexture.setTexture(&defaultTexture);
        }
    }
    catch(const std::exception& e)
    {
        rectangleToTexture.setTexture(&defaultTexture);
    }
    windowToDrawObjectIn.draw(rectangleToTexture);
}

const sf::Texture* TexturedObject::getCurrentTexturePointer() const
{
    return texturePointer;
}
