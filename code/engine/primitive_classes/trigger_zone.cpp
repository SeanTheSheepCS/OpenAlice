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

bool TriggerZone::isIntersecting(const DrawableObject& objectToCompareWith) const
{
	if(((this->x)+((int)this->width)) <= objectToCompareWith.getX())
	{
		return false;
	}
	else if((this->x) >= (objectToCompareWith.getX()+((int)objectToCompareWith.getWidth())))
	{
		return false;
	}
	else if(((this->y)+((int)this->height)) <= objectToCompareWith.getY())
	{
		return false;
	}
	else if((this->y) >= (objectToCompareWith.getY()+((int)objectToCompareWith.getHeight())))
	{
		return false;
	}
	else
	{
    	return true;
	}
}
