#include "textured_and_animated_object.h"
#include <iostream>

TexturedAndAnimatedObject::TexturedAndAnimatedObject(int x, int y, unsigned width, unsigned int height):
	TexturedObject(x,y,width,height,nullptr),
	OAEAnimatedObject()
{
	//
}

void TexturedAndAnimatedObject::draw(sf::RenderWindow& windowToDrawObjectIn, unsigned int numberOfMillisecondsSinceLastUpdate)
{
	OAEAnimationInstance& animationToUse = referenceNumberToAnimationInstanceMap.at(currentAnimationInstanceReferenceNumber);
	animationToUse.incrementMillisecondCountByAmount(numberOfMillisecondsSinceLastUpdate);
	const sf::Texture* textureToUse = animationToUse.getCurrentFrame();
	const sf::Texture* originalTexture = texturePointer;
	this->associateWithNewTexture(textureToUse);
	TexturedObject::draw(windowToDrawObjectIn, numberOfMillisecondsSinceLastUpdate);
	this->associateWithNewTexture(originalTexture);
}

void TexturedAndAnimatedObject::draw(sf::RenderWindow& windowToDrawObjectIn)
{
	OAEAnimationInstance& animationToUse = referenceNumberToAnimationInstanceMap.at(currentAnimationInstanceReferenceNumber);
	const sf::Texture* textureToUse = animationToUse.getCurrentFrame();
	const sf::Texture* originalTexture = texturePointer;
	this->associateWithNewTexture(textureToUse);
	TexturedObject::draw(windowToDrawObjectIn);
	this->associateWithNewTexture(originalTexture);
}
