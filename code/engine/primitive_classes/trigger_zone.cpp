#include "trigger_zone.h"

TriggerZone::TriggerZone(int xArg, int yArg, int widthArg, int heightArg, bool activeStatusArg)
{
    this->x = xArg;
    this->y = yArg;
    this->width = widthArg;
    this->height = heightArg;
    this->activeStatus = activeStatusArg;
}

void TriggerZone::setX(int newX)
{
    this->x = newX;
}

int TriggerZone::getX()
{
    return this->x;
}

void TriggerZone::setY(int newY)
{
    this->y = newY;
}

int TriggerZone::getY()
{
    return this->y;
}

void TriggerZone::setWidth(int newWidth)
{
    this->width = newWidth;
}

unsigned int TriggerZone::getWidth()
{
    return this->width;
}

void TriggerZone::setHeight(int newHeight)
{
    this->height = newHeight;
}

unsigned int TriggerZone:: getHeight()
{
    return this->height;
}

void TriggerZone::setActive(bool activeStatusArg)
{
    this->activeStatus = activeStatusArg;
}

bool TriggerZone::isActive()
{
    return activeStatus;
}

bool TriggerZone::isIntersecting(const DrawableObject& objectToCompareWith)
{
    if(((this->x >= objectToCompareWith.getX()) && (this->x <= objectToCompareWith.getX())) ||
       ((objectToCompareWith.getX() >= this->x) && (objectToCompareWith.getX() <= this->x)) ||
       ((this->y >= objectToCompareWith.getY()) && (this->y <= objectToCompareWith.getY())) ||
       ((objectToCompareWith.getY() >= this->y) && (objectToCompareWith.getY() <= this->y)))
    {
        return true;
    }
    return false;
}
