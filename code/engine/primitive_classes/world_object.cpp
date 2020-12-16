#include "world_object.h"

WorldObject::WorldObject():
	TexturedObject(0,0,0,0,nullptr),
	triggerZoneForObject(0,0,0,0,false),
	collisionBoxForObject(0,0,0,0,false)
{
	this->visibility = false;
}

WorldObject::WorldObject(int x, int y, unsigned int width, unsigned int height, const sf::Texture* texture):
	TexturedObject(x,y,width,height,texture),
	triggerZoneForObject(0,0,0,0,false),
	collisionBoxForObject(0,0,0,0,false)
{
	this->visibility = true;
}

WorldObject::WorldObject(TexturedObject parentObject):
	TexturedObject(parentObject),
	triggerZoneForObject(0,0,0,0,false),
	collisionBoxForObject(0,0,0,0,false)
{
	this->visibility = true;
}

std::vector<unsigned char> WorldObject::toWriteableForm() const
{
	std::vector<unsigned char> returnValue;

	std::vector<unsigned char> texturedObjectToWrite = TexturedObject::toWriteableForm();
	returnValue.insert(returnValue.end(), texturedObjectToWrite.begin(), texturedObjectToWrite.end());

	std::vector<unsigned char> triggerZoneToWrite = triggerZoneForObject.toWriteableForm();
	returnValue.insert(returnValue.end(), triggerZoneToWrite.begin(), triggerZoneToWrite.end());

	std::vector<unsigned char> collisionBoxToWrite = collisionBoxForObject.toWriteableForm();
	returnValue.insert(returnValue.end(), collisionBoxToWrite.begin(), collisionBoxToWrite.end());

	unsigned char visibilityCharacter = 0;
	if((this->visibility) == true)
	{
		visibilityCharacter = 1;
	}
	returnValue.push_back(visibilityCharacter);

	return returnValue;
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

void WorldObject::setCollisionBoxX(int newX)
{
	this->collisionBoxForObject.setX(newX);
}

void WorldObject::setCollisionBoxY(int newY)
{
	this->collisionBoxForObject.setY(newY);
}

void WorldObject::setCollisionBoxWidth(int newWidth)
{
	this->collisionBoxForObject.setWidth(newWidth);
}

void WorldObject::setCollisionBoxHeight(int newHeight)
{
	this->collisionBoxForObject.setHeight(newHeight);
}

void WorldObject::attachCollisionBox(CollisionBox collisionBoxToAttach)
{
	this->collisionBoxForObject = collisionBoxToAttach;
}

void WorldObject::detachCollisionBox()
{
	this->collisionBoxForObject = CollisionBox(0,0,0,0,false);
}

void WorldObject::pushDrawableObjectOutOfCollisionZoneIfItIntersects(DrawableObject& objectToPush) const
{
	if((this->collisionBoxForObject).isActive())
	{
		(this->collisionBoxForObject).pushDrawableObjectOutsideCollisionBoxIfItIsIntersecting(objectToPush);
	}
}

bool WorldObject::isDrawableObjectWithinCollisionBox(const DrawableObject& objectToCheck) const
{
	if(collisionBoxForObject.isActive() && collisionBoxForObject.isIntersecting(objectToCheck))
	{
		return true;
	}
	else
	{
		return false;
	}
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

void WorldObject::addWorldObjectProperty(const WorldObjectProperty property)
{
	properties.push_back(property);
}

void WorldObject::removeWorldObjectProperty(const WorldObjectProperty propertyToRemove)
{
	for(int i = 0; i < properties.size(); i++)
	{
		if(properties.at(i) == propertyToRemove)
		{
			properties.erase(properties.begin()+i);
		}
	}
}

const std::vector<WorldObjectProperty> WorldObject::getProperties() const
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
