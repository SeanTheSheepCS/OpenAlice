#include "oae_animated_object.h"
#include <iostream>

OAEAnimatedObject::OAEAnimatedObject()
{
    currentAnimationInstanceReferenceNumber = 0;
}

void OAEAnimatedObject::associateReferenceNumberWithAnimationInstance(int referenceNumber, const OAEAnimationInstance animationInstance)
{
    referenceNumberToAnimationInstanceMap.insert(std::pair<int, OAEAnimationInstance>(referenceNumber, animationInstance));
}

void OAEAnimatedObject::deassociateAnimationInstanceWithSpecificReferenceNumber(int referenceNumber)
{
    referenceNumberToAnimationInstanceMap.erase(referenceNumber);
}

void OAEAnimatedObject::setCurrentAnimationInstanceReferenceNumber(int currentAnimationInstanceReferenceNumberArg)
{
    try
    {
        referenceNumberToAnimationInstanceMap.at(currentAnimationInstanceReferenceNumber).setMillisecondCountToZero();
    }
    catch(std::exception& e)
    {

    }
    currentAnimationInstanceReferenceNumber = currentAnimationInstanceReferenceNumberArg;
}
