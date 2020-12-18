#include "textured_and_animated_object.h"

TexturedAndAnimatedObject::TexturedAndAnimatedObject(int x, int y, unsigned width, unsigned int height):
	TexturedObject(x,y,width,height,nullptr),
	OAEAnimatedObject()
{
	//
}

void TexturedAndAnimatedObject::draw(sf::RenderWindow& windowToDrawObjectIn, unsigned int numberOfMillisecondsSinceLastUpdate)
{
	OAEAnimationInstance animationToUse = referenceNumberToAnimationInstanceMap.at(currentAnimationInstanceReferenceNumber);
	animationToUse.incrementMillisecondCountByAmount(numberOfMillisecondsSinceLastUpdate);
	const sf::Texture* textureToUse = animationToUse.getCurrentFrame();
	const sf::Texture* originalTexture = texturePointer;
	this->decoupleObjectFromItsTexture();
	this->associateWithNewTexture(textureToUse);
	TexturedObject::draw(windowToDrawObjectIn, numberOfMillisecondsSinceLastUpdate);
	this->decoupleObjectFromItsTexture();
	this->associateWithNewTexture(originalTexture);
}
