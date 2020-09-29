#include "world_object.h"

WorldObject::WorldObject(int x, int y, unsigned int width, unsigned int height, const sf::Texture* texture):
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

void WorldObject::setWidth(unsigned int newWidth)
{
    this->width = newWidth;
}

void WorldObject::setHeight(unsigned int newHeight)
{
    this->height = newHeight;
}

bool WorldObject::isDrawableObjectWithinTriggerZone(const DrawableObject& objectToCheck)
{
    if(triggerZoneForObject.isIntersecting(objectToCheck) && triggerZoneForObject.isActive())
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

void WorldObject::setVisibility(bool visibilityArg)
{
    this->visibility = visibilityArg;
}

bool WorldObject::getVisibility()
{
    return this->visibility;
}

void WorldObject::draw(sf::RenderWindow& windowToDrawObjectIn)
{
    if((this->visibility) == true)
    {
        TexturedObject::draw(windowToDrawObjectIn);
    }
}
