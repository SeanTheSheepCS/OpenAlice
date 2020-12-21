#include "oae_animated_object.h"

OAEAnimatedObject::OAEAnimatedObject()
{
	currentAnimationInstanceReferenceNumber = 0;
}

void OAEAnimatedObject::associateReferenceNumberWithAnimationInstance(int referenceNumber, const OAEAnimationInstance animationInstance)
{
	if(referenceNumberToAnimationInstanceMap.count(referenceNumber) == 1)
	{
		referenceNumberToAnimationInstanceMap.erase(referenceNumber);
	}
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
		}
		catch(std::exception& e)
		{

		}
	}
	currentAnimationInstanceReferenceNumber = currentAnimationInstanceReferenceNumberArg;
}
