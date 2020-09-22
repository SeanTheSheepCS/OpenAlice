#include "animation.h"

OAEAnimation::OAEAnimation(unsigned int animationSpeedInFramesAdvancedPerMillisecondArg);
{
    currentMillisecondCount = 0;
    animationSpeedInFramesAdvancedPerMillisecond = animationSpeedInFramesAdvancedPerMillisecondArg;
}

void OAEAnimation::setAnimationSpeedInFramesAdvancedPerMillisecond(unsigned int newSpeed)
{
    animationSpeedInFramesAdvancedPerMillisecond = newSpeed;
}

unsigned int OAEAnimation::getFrameVectorSize()
{
    return frameVector.size();
}

void OAEAnimation::incrementMillisecondCountByAmount(unsigned int millisecondsToAdd)
{
    currentMillisecondCount += millisecondsToAdd;
}

sf::Texture* OAEAnimation::getCurrentFrame()
{
    unsigned int currentIndex = ((currentMillisecondCount / animationSpeedInFramesAdvancedPerMillisecond) % frameVector.size());
    return frameVector.at(currentIndex);
}
