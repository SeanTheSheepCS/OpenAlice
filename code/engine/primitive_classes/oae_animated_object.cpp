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
	if(currentAnimationInstanceReferenceNumber != currentAnimationInstanceReferenceNumberArg)
	{
		try
		{
			referenceNumberToAnimationInstanceMap.at(currentAnimationInstanceReferenceNumber).setMillisecondCountToZero();
			currentAnimationInstanceReferenceNumber = currentAnimationInstanceReferenceNumberArg;
		}
		catch(std::exception& e)
		{

		}
	}
}
