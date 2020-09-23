#include "player_object.h"

PlayerObject::PlayerObject(int x, int y, unsigned int width, unsigned int height, const sf::Texture* texture): TexturedObject(x, y, width, height, texture)
{
    xMovementAmount = 0;
    yMovementAmount = 0;
    xMovementCap = 1.0;
    yMovementCap = 1.0;
    currentAnimationReferenceNumber = 0;
}

void PlayerObject::associateReferenceNumberWithAnimation(int referenceNumber, OAEAnimation animation)
{
    referenceNumberToAnimationMap.insert(std::pair<int, OAEAnimation>(referenceNumber, animation));
}

void PlayerObject::deassociateAnimationWithSpecificReferenceNumber(int referenceNumber)
{
    referenceNumberToAnimationMap.erase(referenceNumber);
}

void PlayerObject::setXMovementAmount(float newXMovementAmount)
{
    if((xMovementAmount >= -xMovementCap) && (xMovementAmount <= xMovementCap))
    {
        xMovementAmount = newXMovementAmount;
    }
    else
    {
        if(xMovementAmount < 0)
        {
            xMovementAmount = -xMovementCap;
        }
        else
        {
            xMovementAmount = xMovementCap;
        }
    }
}

void PlayerObject::setYMovementAmount(float newYMovementAmount)
{
    if((yMovementAmount >= -yMovementCap) && (yMovementAmount <= yMovementCap))
    {
        yMovementAmount = newYMovementAmount;
    }
    else
    {
        if(yMovementAmount < 0)
        {
            yMovementAmount = -yMovementCap;
        }
        else
        {
            yMovementAmount = yMovementCap;
        }
    }
}

void PlayerObject::changeXMovementAmountByAmount(float amountToChangeXMovementAmountBy)
{
    this->setXMovementAmount(xMovementAmount + amountToChangeXMovementAmountBy);
}

void PlayerObject::changeYMovementAmountByAmount(float amountToChangeYMovementAmountBy)
{
    this->setYMovementAmount(yMovementAmount + amountToChangeYMovementAmountBy);
}

void PlayerObject::setCurrentAnimationReferenceNumber(int currentAnimationReferenceNumberArg)
{
    try
    {
        referenceNumberToAnimationMap.at(currentAnimationReferenceNumberArg).setMillisecondCountToZero();
    }
    catch(std::exception& e)
    {

    }
    currentAnimationReferenceNumber = currentAnimationReferenceNumberArg;
}

float PlayerObject::getXMovementAmount()
{
    return xMovementAmount;
}

float PlayerObject::getYMovementAmount()
{
    return yMovementAmount;
}

void PlayerObject::draw(sf::RenderWindow& windowToDrawObjectIn, int millisecondsPassedSinceLastDraw)
{
    TexturedObject objectToDraw = TexturedObject(x, y, width, height, nullptr);
    OAEAnimation animationToUse = referenceNumberToAnimationMap.at(currentAnimationReferenceNumber);
    animationToUse.incrementMillisecondCountByAmount(millisecondsPassedSinceLastDraw);
    objectToDraw.associateWithNewTexture(animationToUse.getCurrentFrame());
    objectToDraw.draw(windowToDrawObjectIn);
}
