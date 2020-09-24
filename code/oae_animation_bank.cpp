#include "oae_animation_bank.h"

OAEAnimationBank::OAEAnimationBank()
{

}

void OAEAnimationBank::saveOAEAnimationWithReferenceNumber(int referenceNumber, OAEAnimation animationToSave)
{
    referenceNumberToAnimationMap.insert(std::pair<int, OAEAnimation>(referenceNumber, animationToSave));
}

const OAEAnimation* OAEAnimationBank::getAnimationAssociatedWithReferenceNumber(int referenceNumber) const
{
    return &(referenceNumberToAnimationMap.at(referenceNumber));
}

void OAEAnimationBank::deleteAnimationWithReferenceNumber(int referenceNumber)
{
    referenceNumberToAnimationMap.erase(referenceNumber);
}
