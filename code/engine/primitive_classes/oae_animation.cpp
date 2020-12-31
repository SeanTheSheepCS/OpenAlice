#include "oae_animation.h"
#include <iostream>

OAEAnimation::OAEAnimation()
{
	//
}

void OAEAnimation::setLingerAmountVector(std::vector<unsigned int> newAmountsToLinger)
{
	animationNumberOfMillisecondsToLingerOnEachFrame = newAmountsToLinger;
}

unsigned int OAEAnimation::getFrameVectorSize() const
{
	return frameVector.size();
}

const sf::Texture* OAEAnimation::getFrameAtSpecifiedMilliseconds(unsigned int specifiedMilliseconds) const
{
	unsigned int frameIndexToUse = 0;
	unsigned int totalNumberOfMillisecondsOfAnimation = this->getTotalMillisecondCountForAnimation();
	specifiedMilliseconds = specifiedMilliseconds % totalNumberOfMillisecondsOfAnimation;
	unsigned int millisecondCounter = 0;
	for(unsigned int i = 0; i < animationNumberOfMillisecondsToLingerOnEachFrame.size(); i++)
	{
		if((specifiedMilliseconds >= millisecondCounter) && (specifiedMilliseconds <= (millisecondCounter+animationNumberOfMillisecondsToLingerOnEachFrame.at(i))))
		{
			return frameVector.at(i);
		}
		millisecondCounter += animationNumberOfMillisecondsToLingerOnEachFrame.at(i);
	}
	//It should never get here, but this is here just in case so that it at least returns a valid value.
	return frameVector.at(0);
}

unsigned int OAEAnimation::getTotalMillisecondCountForAnimation() const
{
	unsigned int totalNumberOfMillisecondsOfAnimation = 0;
	for(unsigned int i = 0; i < animationNumberOfMillisecondsToLingerOnEachFrame.size(); i++)
	{
		totalNumberOfMillisecondsOfAnimation += animationNumberOfMillisecondsToLingerOnEachFrame.at(i);
	}
	return totalNumberOfMillisecondsOfAnimation;
}

void OAEAnimation::appendTextureToAnimation(const sf::Texture* textureToAppend, unsigned int millisecondsToLinger)
{
	frameVector.push_back(textureToAppend);
	animationNumberOfMillisecondsToLingerOnEachFrame.push_back(millisecondsToLinger);
}
