#include "textured_object.h"
#include <iostream>

bool TexturedObject::isDefaultTextureInitialized = false;
sf::Texture TexturedObject::defaultTexture;

TexturedObject::TexturedObject(int xArg, int yArg, unsigned int widthArg, unsigned int heightArg, const sf::Texture* texturePointerArg): DrawableObject(xArg,yArg,widthArg,heightArg)
{
    this->texturePointer = texturePointerArg;
	this->rotationFactor = 0.0f;
	this->rotationPeriod = -1;
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
	if(rotationFactor != 0)
	{
		rectangleToTexture.setOrigin(((this->width)/2),((this->height)/2));
		rectangleToTexture.setRotation(this->rotationFactor);
		rectangleToTexture.setPosition(this->x+(((int)this->width)/2), this->y+(((int)this->height)/2));
	}
	else
	{
		rectangleToTexture.setPosition(this->x, this->y);
	}
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

void TexturedObject::draw(sf::RenderWindow& windowToDrawObjectIn, unsigned int numberOfMillisecondsSinceLastDraw)
{
	if(rotationPeriod > 0)
	{
		rotateAroundCentreThisManyDegrees(numberOfMillisecondsSinceLastDraw*(360.0/((float)rotationPeriod)));
	}
	this->draw(windowToDrawObjectIn);
}

const sf::Texture* TexturedObject::getCurrentTexturePointer() const
{
    return texturePointer;
}

void TexturedObject::rotateAroundCentreThisManyDegrees(float degrees)
{
	this->rotationFactor += degrees;
	if((this->rotationFactor) >= 360)
	{
		this->rotationFactor = this->rotationFactor - 360;
	}
	if((this->rotationFactor) <= -360)
	{
		this->rotationFactor = this->rotationFactor + 360;
	}
}

void TexturedObject::setRotationAroundCentre(float degrees)
{
	this->rotationFactor = degrees;
}

void TexturedObject::addPeriodicRotation(int numberOfMillisecondsToCompleteOneRotation)
{
	this->rotationPeriod = numberOfMillisecondsToCompleteOneRotation;
}
