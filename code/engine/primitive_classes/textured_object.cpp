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
	this->degreeInterval = 1.0;
}

std::vector<unsigned char> TexturedObject::toWriteableForm() const
{
	std::vector<unsigned char> returnValue;

	std::vector<unsigned char> drawableObjectToWrite = DrawableObject::toWriteableForm();
	returnValue.insert(returnValue.end(), drawableObjectToWrite.begin(), drawableObjectToWrite.end());

	//NOTE: THIS DOES NOT SAVE THE TEXTURE TO BE USED FOR THE OBJECT, OR EVEN ITS REFERENCE NUMBER!!!!!
	
	//NOTE: THIS DOES NOT SAVE THE ROTATION FACTOR, ROTATION PERIOD, OR DEGREE INTERVAL!!!!!!
	
	return returnValue;
}

void fillWithDataFromWriteableForm(std::vector<unsigned char>::iterator& writeableFormIterator)
{
	DrawableObject::fillWithDataFromWriteableForm(writeableFormIterator);

	//NOTE: THIS DOES NOT LOAD THE TEXTURE TO BE USED FOR THE OBJECT, OR EVEN ITS REFERENCE NUMBER!!!!!
	
	//NOTE: THIS DOES NOT LOAD THE ROTATION FACTOR, ROTATION PERIOD, OR DEGREE INTERVAL!!!!!!
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
		float rotationFactorButWithIntervalTakenIntoAccount = ((int)(rotationFactor / degreeInterval))*degreeInterval;
		rectangleToTexture.setRotation(rotationFactorButWithIntervalTakenIntoAccount);
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

void TexturedObject::setDegreeInterval(float degreeIntervalToAdd)
{
	this->degreeInterval = degreeIntervalToAdd;
}
