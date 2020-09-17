#include "player_object.h"

PlayerObject::PlayerObject(int x, int y, unsigned int width, unsigned int height, const sf::Texture* texture): TexturedObject(x, y, width, height, texture)
{
    xMovementAmount = 0;
    yMovementAmount = 0;
}

void PlayerObject::setXMovementAmount(float newXMovementAmount)
{
    xMovementAmount = newXMovementAmount;
}

void PlayerObject::setYMovementAmount(float newYMovementAmount)
{
    yMovementAmount = newYMovementAmount;
}

float getXMovementAmount()
{
    return xMovementAmount;
}

float getYMovementAmount()
{
    return yMovementAmount;
}
