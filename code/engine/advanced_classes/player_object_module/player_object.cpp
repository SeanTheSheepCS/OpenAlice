#include "player_object.h"
#include <iostream>

PlayerObject::PlayerObject(int x, int y, unsigned int width, unsigned int height): DrawableObject(x, y, width, height) , OAEAnimatedObject(), ObjectWithTextureMap()
{
    xMovementAmount = 0;
    yMovementAmount = 0;
    xMovementCap = 1.0;
    yMovementCap = 1.0;
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

float PlayerObject::getXMovementAmount()
{
    return xMovementAmount;
}

float PlayerObject::getYMovementAmount()
{
    return yMovementAmount;
}


void PlayerObject::updateSprite(unsigned int millisecondsPassedSinceLastDraw)
{
    try
    {
        OAEAnimationInstance& animationInstanceToUse = referenceNumberToAnimationInstanceMap.at(currentAnimationInstanceReferenceNumber);
        animationInstanceToUse.incrementMillisecondCountByAmount(millisecondsPassedSinceLastDraw);
    }
    catch (std::exception& e)
    {

    }
}

void PlayerObject::draw(sf::RenderWindow& windowToDrawObjectIn)
{
    TexturedObject objectToDraw = TexturedObject(x, y, width, height, nullptr);
    if((xMovementAmount != 0) || (yMovementAmount != 0))
    {
        try
        {
            OAEAnimationInstance& animationInstanceToUse = referenceNumberToAnimationInstanceMap.at(currentAnimationInstanceReferenceNumber);
            objectToDraw.associateWithNewTexture(animationInstanceToUse.getCurrentFrame());
        }
        catch(std::exception& e)
        {
            objectToDraw.associateWithNewTexture(this->getCurrentTexture());
        }
    }
    else
    {
        objectToDraw.associateWithNewTexture(this->getCurrentTexture());
    }
    objectToDraw.draw(windowToDrawObjectIn);
}

void PlayerObject::drawAndUpdateSprite(sf::RenderWindow& windowToDrawObjectIn, unsigned int millisecondsPassedSinceLastDraw)
{
    TexturedObject objectToDraw = TexturedObject(x, y, width, height, nullptr);
    if((xMovementAmount != 0) || (yMovementAmount != 0))
    {
        try
        {
            OAEAnimationInstance& animationInstanceToUse = referenceNumberToAnimationInstanceMap.at(currentAnimationInstanceReferenceNumber);
            animationInstanceToUse.incrementMillisecondCountByAmount(millisecondsPassedSinceLastDraw);
            objectToDraw.associateWithNewTexture(animationInstanceToUse.getCurrentFrame());
        }
        catch(std::exception& e)
        {
            objectToDraw.associateWithNewTexture(this->getCurrentTexture());
        }
    }
    else
    {
        objectToDraw.associateWithNewTexture(this->getCurrentTexture());
    }
    objectToDraw.draw(windowToDrawObjectIn);
}
