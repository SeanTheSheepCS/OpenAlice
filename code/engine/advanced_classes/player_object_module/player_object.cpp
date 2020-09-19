#include "player_object.h"

PlayerObject::PlayerObject(int x, int y, unsigned int width, unsigned int height, const sf::Texture* texture): TexturedObject(x, y, width, height, texture)
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
