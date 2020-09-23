#include "oae_animation.h"

OAEAnimation::OAEAnimation(unsigned int animationSpeedInMillisecondsToAdvanceFrameArg)
{
    currentMillisecondCount = 0;
    animationSpeedInMillisecondsToAdvanceFrame = animationSpeedInMillisecondsToAdvanceFrameArg;
}

void OAEAnimation::setAnimationSpeedInMillisecondsPerAdvanceFrame(unsigned int newSpeed)
{
    animationSpeedInMillisecondsToAdvanceFrame = newSpeed;
}

unsigned int OAEAnimation::getFrameVectorSize()
{
    return frameVector.size();
}

void OAEAnimation::setMillisecondCountToZero()
{
    currentMillisecondCount = 0;
}

void OAEAnimation::incrementMillisecondCountByAmount(unsigned int millisecondsToAdd)
{
    currentMillisecondCount += millisecondsToAdd;
}

sf::Texture* OAEAnimation::getCurrentFrame()
{
    unsigned int currentIndex = ((currentMillisecondCount / animationSpeedInMillisecondsToAdvanceFrame) % frameVector.size());
    return frameVector.at(currentIndex);
}
