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

int TriggerZone::getX() const
{
    return this->x;
}

void TriggerZone::setY(int newY)
{
    this->y = newY;
}

int TriggerZone::getY() const
{
    return this->y;
}

void TriggerZone::setWidth(int newWidth)
{
    this->width = newWidth;
}

unsigned int TriggerZone::getWidth() const
{
    return this->width;
}

void TriggerZone::setHeight(int newHeight)
{
    this->height = newHeight;
}

unsigned int TriggerZone::getHeight() const
{
    return this->height;
}

void TriggerZone::setActive(bool activeStatusArg)
{
    this->activeStatus = activeStatusArg;
}

bool TriggerZone::isActive() const
{
    return activeStatus;
}
#include <iostream>

bool TriggerZone::isIntersecting(const DrawableObject& objectToCompareWith) const
{
	std::cout << "Object: (" << this->x << "," << this->y << ")" << std::endl;
	std::cout << "Alice: (" << objectToCompareWith.getX() << "," << objectToCompareWith.getY() << ")" << std::endl;
    if(((this->x >= objectToCompareWith.getX()) && (this->x <= (objectToCompareWith.getX()+((int)objectToCompareWith.getWidth())))) ||
       ((objectToCompareWith.getX() >= this->x) && (objectToCompareWith.getX() <= ((this->x)+((int) this->width)))) ||
       ((this->y >= objectToCompareWith.getY()) && (this->y <= (objectToCompareWith.getY()+((int)objectToCompareWith.getHeight())))) ||
       ((objectToCompareWith.getY() >= this->y) && (objectToCompareWith.getY() <= ((this->y)+((int) this->height)))))
    {
        return true;
    }
    return false;
}
