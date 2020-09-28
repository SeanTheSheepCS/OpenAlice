#include "world_object.h"

WorldObject::WorldObject(int x, int y, unsigned int width, unsigned int height, sf::Texture* texture):
    TexturedObject(x,y,width,height,texture),
    triggerZoneForObject(0,0,0,0,false)
{
    this->visibility = true;
}

WorldObject::WorldObject(TexturedObject parentObject):
    TexturedObject(parentObject),
    triggerZoneForObject(0,0,0,0,false)
{
    this->visibility = true;
}

void WorldObject::setX(int newX)
{
    this->x = newX;
}

void WorldObject::setY(int newY)
{
    this->y = newY;
}

int WorldObject::getX()
{
    return this->x;
}

int WorldObject::getY()
{
    return this->y;
}

void WorldObject::setWidth(unsigned int newWidth)
{
    this->width = newWidth;
}

void WorldObject::setHeight(unsigned int newHeight)
{
    this->height = newHeight;
}

unsigned int WorldObject::getWidth()
{
    return this->width;
}

unsigned int WorldObject::getHeight()
{
    return this->height;
}

bool WorldObject::isDrawableObjectWithinTriggerZone(DrawableObject objectToCheck)
{
    if(triggerZoneForObject.isIntersecting(objectToCompareWith) && triggerZoneForObject.isActive())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void WorldObject::attachTriggerZone(TriggerZone zoneToAttach)
{
    triggerZoneForObject = zoneToAttach;
}

void WorldObject::detachTriggerZone()
{
    triggerZoneForObject = TriggerZone(0,0,0,0,false);
}

void WorldObject::setVisible(bool visibilityArg)
{
    this->visibility = visibilityArg;
}

bool WorldObject::getVisibility()
{
    return this->visibility;
}
