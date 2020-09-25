#include "oae_animation.h"
#include <iostream>

OAEAnimation::OAEAnimation(unsigned int animationSpeedInMillisecondsToAdvanceFrameArg)
{
    animationSpeedInMillisecondsToAdvanceFrame = animationSpeedInMillisecondsToAdvanceFrameArg;
}

void OAEAnimation::setAnimationSpeedInMillisecondsPerAdvanceFrame(unsigned int newSpeed)
{
    animationSpeedInMillisecondsToAdvanceFrame = newSpeed;
}

unsigned int OAEAnimation::getFrameVectorSize() const
{
    return frameVector.size();
}

const sf::Texture* OAEAnimation::getFrameAtSpecifiedMilliseconds(unsigned int specifiedMilliseconds) const
{
    unsigned int currentIndex = ((specifiedMilliseconds / animationSpeedInMillisecondsToAdvanceFrame) % frameVector.size());
    return frameVector.at(currentIndex);
}

unsigned int OAEAnimation::getTotalMillisecondCountForAnimation() const
{
    return animationSpeedInMillisecondsToAdvanceFrame*(frameVector.size());
}

void OAEAnimation::appendTextureToAnimation(const sf::Texture* textureToAppend)
{
    frameVector.push_back(textureToAppend);
}
