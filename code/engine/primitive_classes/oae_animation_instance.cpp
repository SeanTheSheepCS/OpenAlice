#include "oae_animation_instance.h"
#include <iostream>

OAEAnimationInstance::OAEAnimationInstance(const OAEAnimation* animationToUseArg)
{
    animationToUse = animationToUseArg;
    millisecondsProgressInAnimation = 0;
}

void OAEAnimationInstance::incrementMillisecondCountByAmount(unsigned int amountToIncrementBy)
{
    millisecondsProgressInAnimation = ((millisecondsProgressInAnimation + amountToIncrementBy) % (animationToUse->getTotalMillisecondCountForAnimation()));
}

void OAEAnimationInstance::setMillisecondCountToZero()
{
    millisecondsProgressInAnimation = 0;
}

unsigned int OAEAnimationInstance::getMillisecondProgressInAnimation() const
{
    return millisecondsProgressInAnimation;
}

const sf::Texture* OAEAnimationInstance::getCurrentFrame()
{
    if(animationToUse != nullptr)
    {
        return animationToUse->getFrameAtSpecifiedMilliseconds(millisecondsProgressInAnimation);
    }
    else
    {
        return nullptr;
    }
}
