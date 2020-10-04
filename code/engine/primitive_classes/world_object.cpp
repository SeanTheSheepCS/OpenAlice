#include "world_object.h"

WorldObject::WorldObject():
	TexturedObject(0,0,0,0,nullptr),
    triggerZoneForObject(0,0,0,0,false)
{
    this->visibility = false;
}

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

void WorldObject::setTriggerZoneX(int newX)
{
	this->triggerZoneForObject.setX(newX);
}

void WorldObject::setTriggerZoneY(int newY)
{
	this->triggerZoneForObject.setY(newY);
}

void WorldObject::setTriggerZoneWidth(unsigned int newWidth)
{
	this->triggerZoneForObject.setWidth(newWidth);
}

void WorldObject::setTriggerZoneHeight(unsigned int newHeight)
{
	this->triggerZoneForObject.setHeight(newHeight);
}

bool WorldObject::isInvalid() const
{
    if((this->width == 0) || (this->height == 0))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool WorldObject::isDrawableObjectWithinTriggerZone(const DrawableObject& objectToCheck) const
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

bool WorldObject::getVisibility() const
{
    return this->visibility;
}

void WorldObject::addWorldObjectProperty(WorldObjectProperty property)
{
	properties.push_back(property);
}

std::vector<WorldObjectProperty> WorldObject::getProperties() const
{
	return this->properties;
}

void WorldObject::draw(sf::RenderWindow& windowToDrawObjectIn)
{
    if((this->visibility) == true)
    {
        TexturedObject::draw(windowToDrawObjectIn);
    }
}
