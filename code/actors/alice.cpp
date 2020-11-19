#include "alice.h"

Alice::Alice(int x, int y, unsigned int width, unsigned int height): PlayerObject(x,y,width,height)
{
	this->referenceNumberOfHeldWorldObject = WORLD_OBJECT_REF_NUMBER_INVALID;
	this->heldWorldObject = WorldObject();
}

void Alice::pickUpObject(int referenceNumberOfObjectToPickUp, TileMap& tileMapYouPickedItUpFrom)
{
	referenceNumberOfHeldWorldObject = referenceNumberOfObjectToPickUp; 
	heldWorldObject = tileMapYouPickedItUpFrom.getWorldObjectWithReferenceNumber(referenceNumberOfObjectToPickUp);
	tileMapYouPickedItUpFrom.removeWorldObjectWithReferenceNumber(referenceNumberOfObjectToPickUp);
}

void Alice::putDownObject(TileMap& tileMapToPutItDownIn)
{
	if(((this->heldWorldObject).isInvalid()) || (this->referenceNumberOfHeldWorldObject == WORLD_OBJECT_REF_NUMBER_INVALID))
	{
		return;
	}
	else
	{
		tileMapToPutItDownIn.addWorldObjectWithReferenceNumber(referenceNumberOfHeldWorldObject, heldWorldObject, this->x, this->y);
		this->referenceNumberOfHeldWorldObject = WORLD_OBJECT_REF_NUMBER_INVALID;
		this->heldWorldObject = WorldObject();
	}
}

bool Alice::isHoldingObject() const
{
	if(((this->heldWorldObject).isInvalid()) || (referenceNumberOfHeldWorldObject == WORLD_OBJECT_REF_NUMBER_INVALID))
	{
		return false;
	}
	else
	{
		return true;
	}
}

int Alice::returnReferenceNumberOfHeldObject() const
{
	return referenceNumberOfHeldWorldObject;
}

const std::vector<WorldObjectProperty> Alice::returnPropertiesOfHeldWorldObject() const
{
	return heldWorldObject.getProperties();
}

void Alice::removeWorldObjectPropertyFromHeldWorldObject(const WorldObjectProperty propertyToRemove)
{
	heldWorldObject.removeWorldObjectProperty(propertyToRemove);
}

void Alice::addWorldObjectPropertyToHeldWorldObject(const WorldObjectProperty propertyToAdd)
{
	heldWorldObject.addWorldObjectProperty(propertyToAdd);
}

const int Alice::returnCapacityOfHeldWorldObject() const //Returns -1 on failure.
{
	const std::vector<WorldObjectProperty> propertiesOfHeldObject = heldWorldObject.getProperties();
	for(unsigned int i = 0; i < propertiesOfHeldObject.size(); i++)
	{
		switch(propertiesOfHeldObject.at(i))
		{
			case WORLD_OBJECT_PROPERTY_CAPACITY_10:
				return 10;
				break;
			default:
				//Continue...
				break;
		}
	}
	return -1;
}

const int Alice::returnFilledAmountPropertyOfHeldWorldObject() const //Returns -1 on failure.
{
	const std::vector<WorldObjectProperty> propertiesOfHeldObject = heldWorldObject.getProperties();
	for(unsigned int i = 0; i < propertiesOfHeldObject.size(); i++)
	{
		switch(propertiesOfHeldObject.at(i))
		{
			case WORLD_OBJECT_PROPERTY_FILLED_WITH_0:
				return 0;
				break;
			case WORLD_OBJECT_PROPERTY_FILLED_WITH_1:
				return 1;
				break;
			case WORLD_OBJECT_PROPERTY_FILLED_WITH_2:
				return 2;
				break;
			case WORLD_OBJECT_PROPERTY_FILLED_WITH_3:
				return 3;
				break;
			case WORLD_OBJECT_PROPERTY_FILLED_WITH_4:
				return 4;
				break;
			case WORLD_OBJECT_PROPERTY_FILLED_WITH_5:
				return 5;
				break;
			case WORLD_OBJECT_PROPERTY_FILLED_WITH_6:
				return 6;
				break;
			case WORLD_OBJECT_PROPERTY_FILLED_WITH_7:
				return 7;
				break;
			case WORLD_OBJECT_PROPERTY_FILLED_WITH_8:
				return 8;
				break;
			case WORLD_OBJECT_PROPERTY_FILLED_WITH_9:
				return 9;
				break;
			case WORLD_OBJECT_PROPERTY_FILLED_WITH_10:
				return 10;
				break;
			default:
				//Continue...
				break;
		}
	}
	return -1;
}

void Alice::incrementFilledAmountPropertyOfHeldWorldObject()
{
	const std::vector<WorldObjectProperty> propertiesOfHeldObject = heldWorldObject.getProperties();
	for(unsigned int i = 0; i < propertiesOfHeldObject.size(); i++)
	{
		WorldObjectProperty currentProperty = propertiesOfHeldObject.at(i);
		if((currentProperty >= WORLD_OBJECT_PROPERTY_FILLED_WITH_0) && (currentProperty < WORLD_OBJECT_PROPERTY_FILLED_WITH_10))
		{
			heldWorldObject.removeWorldObjectProperty(currentProperty);
			WorldObjectProperty propertyToWrite = WORLD_OBJECT_PROPERTY_FILLED_WITH_0; 
			switch(currentProperty)
			{
				case WORLD_OBJECT_PROPERTY_FILLED_WITH_0:
					propertyToWrite = WORLD_OBJECT_PROPERTY_FILLED_WITH_1;
					break;
				case WORLD_OBJECT_PROPERTY_FILLED_WITH_1:
					propertyToWrite = WORLD_OBJECT_PROPERTY_FILLED_WITH_2;
					break;
				case WORLD_OBJECT_PROPERTY_FILLED_WITH_2:
					propertyToWrite = WORLD_OBJECT_PROPERTY_FILLED_WITH_3;
					break;
				case WORLD_OBJECT_PROPERTY_FILLED_WITH_3:
					propertyToWrite = WORLD_OBJECT_PROPERTY_FILLED_WITH_4;
					break;
				case WORLD_OBJECT_PROPERTY_FILLED_WITH_4:
					propertyToWrite = WORLD_OBJECT_PROPERTY_FILLED_WITH_5;
					break;
				case WORLD_OBJECT_PROPERTY_FILLED_WITH_5:
					propertyToWrite = WORLD_OBJECT_PROPERTY_FILLED_WITH_6;
					break;
				case WORLD_OBJECT_PROPERTY_FILLED_WITH_6:
					propertyToWrite = WORLD_OBJECT_PROPERTY_FILLED_WITH_7;
					break;
				case WORLD_OBJECT_PROPERTY_FILLED_WITH_7:
					propertyToWrite = WORLD_OBJECT_PROPERTY_FILLED_WITH_8;
					break;
				case WORLD_OBJECT_PROPERTY_FILLED_WITH_8:
					propertyToWrite = WORLD_OBJECT_PROPERTY_FILLED_WITH_9;
					break;
				case WORLD_OBJECT_PROPERTY_FILLED_WITH_9:
					propertyToWrite = WORLD_OBJECT_PROPERTY_FILLED_WITH_10;
					break;
			}
			heldWorldObject.addWorldObjectProperty(propertyToWrite);
			break;
		}
	}
}
