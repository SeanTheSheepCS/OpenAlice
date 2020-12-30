#include "alice.h"

bool AliceAnimationAndTextureDecisionFactors::operator ==(const AliceAnimationAndTextureDecisionFactors& rhs) const
{
	if(((this->heldWorldObjectReferenceNumber) == rhs.heldWorldObjectReferenceNumber) &&
		((this->xMovementAmount) == rhs.xMovementAmount) &&
		((this->yMovementAmount) == rhs.yMovementAmount))
	{
		return true;
	}
	else
	{
		return false;
	}
}
		
bool AliceAnimationAndTextureDecisionFactors::operator <(const AliceAnimationAndTextureDecisionFactors& rhs) const
{
	//PRIORITY ONE: WorldObjectReferenceNumber
	if((this->heldWorldObjectReferenceNumber) < (rhs.heldWorldObjectReferenceNumber))
	{
		return true;
	}
	else if((this->heldWorldObjectReferenceNumber) > (rhs.heldWorldObjectReferenceNumber))
	{
		return false;
	}
	//PRIORITY TWO: xMovementAmount
	if((this->xMovementAmount) < (rhs.xMovementAmount))
	{
		return true;
	}
	else if((this->xMovementAmount) > (rhs.xMovementAmount))
	{
		return false;
	}
	//PRIORITY THREE: xMovementAmount
	if((this->yMovementAmount) < (rhs.yMovementAmount))
	{
		return true;
	}
	else
	{
		return false;
	}
}

Alice::Alice(int x, int y, unsigned int width, unsigned int height): PlayerObject(x,y,width,height)
{
	this->deleteHeldWorldObject();
	this->initializeDecisionFactorsToTextureBankRefNumberMap();
	this->initializeDecisionFactorsToAnimationBankRefNumberMap();
}

void Alice::pickUpObject(WorldObjectReferenceNumber referenceNumberOfObjectToPickUp, TileMap& tileMapYouPickedItUpFrom)
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
		this->deleteHeldWorldObject();
	}
}

void Alice::associateWithCorrectAnimation()
{
	AliceAnimationAndTextureDecisionFactors key;
	key.heldWorldObjectReferenceNumber = this->returnReferenceNumberOfHeldObject();

	if((this->getXMovementAmount()) == 0)
	{
		key.xMovementAmount = 0;
	}
	else if((this->getXMovementAmount()) > 0)
	{
		key.xMovementAmount = 1;
	}
	else
	{
		key.xMovementAmount = -1;
	}

	if((this->getYMovementAmount()) == 0)
	{
		key.yMovementAmount = 0;
	}
	else if((this->getYMovementAmount()) > 0)
	{
		key.yMovementAmount = 1;
	}
	else
	{
		key.yMovementAmount = -1;
	}

	this->setCurrentTextureReferenceNumber(decisionFactorsToTextureBankRefNumberMap.at(key));
	this->setCurrentAnimationInstanceReferenceNumber(decisionFactorsToAnimationBankRefNumberMap.at(key));
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

WorldObjectReferenceNumber Alice::returnReferenceNumberOfHeldObject() const
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

void Alice::decrementFilledAmountPropertyOfHeldWorldObject()
{
	const std::vector<WorldObjectProperty> propertiesOfHeldObject = heldWorldObject.getProperties();
	for(unsigned int i = 0; i < propertiesOfHeldObject.size(); i++)
	{
		WorldObjectProperty currentProperty = propertiesOfHeldObject.at(i);
		if((currentProperty >= WORLD_OBJECT_PROPERTY_FILLED_WITH_0) && (currentProperty <= WORLD_OBJECT_PROPERTY_FILLED_WITH_10))
		{
			heldWorldObject.removeWorldObjectProperty(currentProperty);
			WorldObjectProperty propertyToWrite = WORLD_OBJECT_PROPERTY_FILLED_WITH_0; 
			switch(currentProperty)
			{
				case WORLD_OBJECT_PROPERTY_FILLED_WITH_1:
					{
					    bool shouldRemoveTheWorldObjectFilledWithZeroProperty = false;
					    for(unsigned int j = 0; j < propertiesOfHeldObject.size(); j++)
					    {
					    	if(propertiesOfHeldObject.at(j) == WORLD_OBJECT_PROPERTY_DELETES_WHEN_FILLED_WITH_0)
					    	{
					    		shouldRemoveTheWorldObjectFilledWithZeroProperty = true;
					    	}
					    }
					    if(shouldRemoveTheWorldObjectFilledWithZeroProperty == true)
					    {
					    	this->deleteHeldWorldObject();
					    }
					    else
					    {
					    	propertyToWrite = WORLD_OBJECT_PROPERTY_FILLED_WITH_0;
					    }
					}
					break;
				case WORLD_OBJECT_PROPERTY_FILLED_WITH_2:
					propertyToWrite = WORLD_OBJECT_PROPERTY_FILLED_WITH_1;
					break;
				case WORLD_OBJECT_PROPERTY_FILLED_WITH_3:
					propertyToWrite = WORLD_OBJECT_PROPERTY_FILLED_WITH_2;
					break;
				case WORLD_OBJECT_PROPERTY_FILLED_WITH_4:
					propertyToWrite = WORLD_OBJECT_PROPERTY_FILLED_WITH_3;
					break;
				case WORLD_OBJECT_PROPERTY_FILLED_WITH_5:
					propertyToWrite = WORLD_OBJECT_PROPERTY_FILLED_WITH_4;
					break;
				case WORLD_OBJECT_PROPERTY_FILLED_WITH_6:
					propertyToWrite = WORLD_OBJECT_PROPERTY_FILLED_WITH_5;
					break;
				case WORLD_OBJECT_PROPERTY_FILLED_WITH_7:
					propertyToWrite = WORLD_OBJECT_PROPERTY_FILLED_WITH_6;
					break;
				case WORLD_OBJECT_PROPERTY_FILLED_WITH_8:
					propertyToWrite = WORLD_OBJECT_PROPERTY_FILLED_WITH_7;
					break;
				case WORLD_OBJECT_PROPERTY_FILLED_WITH_9:
					propertyToWrite = WORLD_OBJECT_PROPERTY_FILLED_WITH_8;
					break;
				case WORLD_OBJECT_PROPERTY_FILLED_WITH_10:
					propertyToWrite = WORLD_OBJECT_PROPERTY_FILLED_WITH_9;
					break;
			}
			if(!(heldWorldObject.isInvalid()))
			{
                heldWorldObject.addWorldObjectProperty(propertyToWrite);
			}
			break;
		}
	}
}

void Alice::deleteHeldWorldObject()
{
	this->referenceNumberOfHeldWorldObject = WORLD_OBJECT_REF_NUMBER_INVALID;
	this->heldWorldObject = WorldObject();
}

void Alice::fillHeldWorldObjectToCapacity()
{
    const int capacity = this->returnCapacityOfHeldWorldObject();
    if(capacity != -1)
    {
		const std::vector<WorldObjectProperty> propertiesOfHeldObject = this->returnPropertiesOfHeldWorldObject();
	    for(unsigned int i = 0; i < propertiesOfHeldObject.size(); i++)
	    {
	    	const WorldObjectProperty currentProperty = propertiesOfHeldObject.at(i);
	    	if((currentProperty >= WORLD_OBJECT_PROPERTY_FILLED_WITH_0) && (currentProperty <= WORLD_OBJECT_PROPERTY_FILLED_WITH_10))
	    	{
				const WorldObjectProperty capacityProperty = currentProperty;
	            switch(capacity)
	            {
	            	case 10:
	            		heldWorldObject.removeWorldObjectProperty(capacityProperty);
						heldWorldObject.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_FILLED_WITH_10);
					    break;
	            }
			}
        }
	}
}

void Alice::initializeDecisionFactorsToTextureBankRefNumberMap()
{
	initializeEntryGroupInDecisionFactorToTextureBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_HOE, TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_HOE, TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_HOE, TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_HOE, TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_HOE);

	initializeEntryGroupInDecisionFactorToTextureBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_WATERING_CAN, TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_WATERING_CAN, TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_WATERING_CAN, TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_WATERING_CAN, TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_WATERING_CAN);

	//TOMATO CRATE TEXTURES
	initializeEntryGroupInDecisionFactorToTextureBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_TOMATO_CRATE_ONE, TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_TOMATO_CRATE, TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_TOMATO_CRATE, TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_TOMATO_CRATE, TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_TOMATO_CRATE);
	initializeEntryGroupInDecisionFactorToTextureBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_TOMATO_CRATE_TWO, TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_TOMATO_CRATE, TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_TOMATO_CRATE, TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_TOMATO_CRATE, TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_TOMATO_CRATE);
	initializeEntryGroupInDecisionFactorToTextureBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_TOMATO_CRATE_THREE, TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_TOMATO_CRATE, TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_TOMATO_CRATE, TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_TOMATO_CRATE, TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_TOMATO_CRATE);
	initializeEntryGroupInDecisionFactorToTextureBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_TOMATO_CRATE_ONE_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_TOMATO_CRATE_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_TOMATO_CRATE_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_TOMATO_CRATE_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_TOMATO_CRATE_FILLED);
	initializeEntryGroupInDecisionFactorToTextureBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_TOMATO_CRATE_TWO_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_TOMATO_CRATE_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_TOMATO_CRATE_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_TOMATO_CRATE_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_TOMATO_CRATE_FILLED);
	initializeEntryGroupInDecisionFactorToTextureBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_TOMATO_CRATE_THREE_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_TOMATO_CRATE_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_TOMATO_CRATE_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_TOMATO_CRATE_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_TOMATO_CRATE_FILLED);

	//CUCUMBER CRATE TEXTURES
	initializeEntryGroupInDecisionFactorToTextureBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CUCUMBER_CRATE_ONE, TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CUCUMBER_CRATE, TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CUCUMBER_CRATE, TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CUCUMBER_CRATE, TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CUCUMBER_CRATE);
	initializeEntryGroupInDecisionFactorToTextureBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CUCUMBER_CRATE_TWO, TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CUCUMBER_CRATE, TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CUCUMBER_CRATE, TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CUCUMBER_CRATE, TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CUCUMBER_CRATE);
	initializeEntryGroupInDecisionFactorToTextureBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CUCUMBER_CRATE_THREE, TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CUCUMBER_CRATE, TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CUCUMBER_CRATE, TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CUCUMBER_CRATE, TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CUCUMBER_CRATE);
	initializeEntryGroupInDecisionFactorToTextureBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CUCUMBER_CRATE_ONE_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CUCUMBER_CRATE_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CUCUMBER_CRATE_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CUCUMBER_CRATE_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CUCUMBER_CRATE_FILLED);
	initializeEntryGroupInDecisionFactorToTextureBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CUCUMBER_CRATE_TWO_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CUCUMBER_CRATE_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CUCUMBER_CRATE_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CUCUMBER_CRATE_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CUCUMBER_CRATE_FILLED);
	initializeEntryGroupInDecisionFactorToTextureBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CUCUMBER_CRATE_THREE_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CUCUMBER_CRATE_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CUCUMBER_CRATE_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CUCUMBER_CRATE_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CUCUMBER_CRATE_FILLED);
	
	//CARROT CRATE TEXTURES
	initializeEntryGroupInDecisionFactorToTextureBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CARROT_CRATE_ONE, TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CARROT_CRATE, TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CARROT_CRATE, TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CARROT_CRATE, TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CARROT_CRATE);
	initializeEntryGroupInDecisionFactorToTextureBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CARROT_CRATE_TWO, TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CARROT_CRATE, TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CARROT_CRATE, TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CARROT_CRATE, TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CARROT_CRATE);
	initializeEntryGroupInDecisionFactorToTextureBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CARROT_CRATE_THREE, TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CARROT_CRATE, TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CARROT_CRATE, TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CARROT_CRATE, TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CARROT_CRATE);
	initializeEntryGroupInDecisionFactorToTextureBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CARROT_CRATE_ONE_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CARROT_CRATE_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CARROT_CRATE_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CARROT_CRATE_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CARROT_CRATE_FILLED);
	initializeEntryGroupInDecisionFactorToTextureBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CARROT_CRATE_TWO_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CARROT_CRATE_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CARROT_CRATE_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CARROT_CRATE_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CARROT_CRATE_FILLED);
	initializeEntryGroupInDecisionFactorToTextureBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CARROT_CRATE_THREE_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CARROT_CRATE_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CARROT_CRATE_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CARROT_CRATE_FILLED, TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CARROT_CRATE_FILLED);

	//TOMATO SEED PACKET TEXTURES
	initializeEntryGroupInDecisionFactorToTextureBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_TOMATO_SEED_PACKET_ONE, TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_TOMATO_SEEDS, TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_TOMATO_SEEDS, TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_TOMATO_SEEDS, TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_TOMATO_SEEDS);
	initializeEntryGroupInDecisionFactorToTextureBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_TOMATO_SEED_PACKET_TWO, TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_TOMATO_SEEDS, TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_TOMATO_SEEDS, TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_TOMATO_SEEDS, TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_TOMATO_SEEDS);
	initializeEntryGroupInDecisionFactorToTextureBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_TOMATO_SEED_PACKET_THREE, TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_TOMATO_SEEDS, TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_TOMATO_SEEDS, TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_TOMATO_SEEDS, TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_TOMATO_SEEDS);
	
	//CUCUMBER SEED PACKET TEXTURES
	initializeEntryGroupInDecisionFactorToTextureBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CUCUMBER_SEED_PACKET_ONE, TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CUCUMBER_SEEDS, TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CUCUMBER_SEEDS, TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CUCUMBER_SEEDS, TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CUCUMBER_SEEDS);
	initializeEntryGroupInDecisionFactorToTextureBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CUCUMBER_SEED_PACKET_TWO, TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CUCUMBER_SEEDS, TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CUCUMBER_SEEDS, TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CUCUMBER_SEEDS, TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CUCUMBER_SEEDS);
	initializeEntryGroupInDecisionFactorToTextureBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CUCUMBER_SEED_PACKET_THREE, TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CUCUMBER_SEEDS, TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CUCUMBER_SEEDS, TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CUCUMBER_SEEDS, TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CUCUMBER_SEEDS);

	//CARROT SEED PACKET TEXTURES
	initializeEntryGroupInDecisionFactorToTextureBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CARROT_SEED_PACKET_ONE, TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CARROT_SEEDS, TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CARROT_SEEDS, TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CARROT_SEEDS, TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CARROT_SEEDS);
	initializeEntryGroupInDecisionFactorToTextureBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CARROT_SEED_PACKET_TWO, TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CARROT_SEEDS, TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CARROT_SEEDS, TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CARROT_SEEDS, TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CARROT_SEEDS);
	initializeEntryGroupInDecisionFactorToTextureBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CARROT_SEED_PACKET_THREE, TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CARROT_SEEDS, TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CARROT_SEEDS, TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CARROT_SEEDS, TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CARROT_SEEDS);

	//NO HELD WORLD OBJECT
	initializeEntryGroupInDecisionFactorToTextureBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_INVALID, TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE, TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE, TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE, TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE);
}

void Alice::initializeEntryGroupInDecisionFactorToTextureBankRefNumberMap(WorldObjectReferenceNumber heldWorldObjectReferenceNumberArg, TextureBankReferenceNumber leftTexture, TextureBankReferenceNumber rightTexture, TextureBankReferenceNumber upTexture, TextureBankReferenceNumber downTexture)
{
	this->initializeEntryInDecisionFactorToTextureBankRefNumberMap(heldWorldObjectReferenceNumberArg,-1,-1,rightTexture);
	this->initializeEntryInDecisionFactorToTextureBankRefNumberMap(heldWorldObjectReferenceNumberArg,-1,0,rightTexture);
	this->initializeEntryInDecisionFactorToTextureBankRefNumberMap(heldWorldObjectReferenceNumberArg,-1,1,rightTexture);
	this->initializeEntryInDecisionFactorToTextureBankRefNumberMap(heldWorldObjectReferenceNumberArg,0,-1,downTexture);
	this->initializeEntryInDecisionFactorToTextureBankRefNumberMap(heldWorldObjectReferenceNumberArg,0,0,downTexture);
	this->initializeEntryInDecisionFactorToTextureBankRefNumberMap(heldWorldObjectReferenceNumberArg,0,1,upTexture);
	this->initializeEntryInDecisionFactorToTextureBankRefNumberMap(heldWorldObjectReferenceNumberArg,1,-1,leftTexture);
	this->initializeEntryInDecisionFactorToTextureBankRefNumberMap(heldWorldObjectReferenceNumberArg,1,0,leftTexture);
	this->initializeEntryInDecisionFactorToTextureBankRefNumberMap(heldWorldObjectReferenceNumberArg,1,1,leftTexture);
}

void Alice::initializeEntryInDecisionFactorToTextureBankRefNumberMap(WorldObjectReferenceNumber heldWorldObjectReferenceNumberArg, int xMovementAmountArg, int yMovementAmountArg, TextureBankReferenceNumber textureBankRefNumberArg)
{
	AliceAnimationAndTextureDecisionFactors keyToAdd;
	keyToAdd.heldWorldObjectReferenceNumber = heldWorldObjectReferenceNumberArg;
	keyToAdd.xMovementAmount = xMovementAmountArg;
	keyToAdd.yMovementAmount = yMovementAmountArg;
	if(decisionFactorsToTextureBankRefNumberMap.count(keyToAdd) == 1)
	{
		decisionFactorsToTextureBankRefNumberMap.erase(keyToAdd);
	}
	decisionFactorsToTextureBankRefNumberMap.insert(std::pair<AliceAnimationAndTextureDecisionFactors, TextureBankReferenceNumber>(keyToAdd, textureBankRefNumberArg));
}

void Alice::initializeDecisionFactorsToAnimationBankRefNumberMap()
{
	//HOE TEXTURES
	initializeEntryGroupInDecisionFactorToAnimationBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_HOE, ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_HOE, ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_HOE, ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_HOE, ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_HOE);

	//WATERING CAN TEXTURES
	initializeEntryGroupInDecisionFactorToAnimationBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_WATERING_CAN, ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_WATERING_CAN, ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_WATERING_CAN, ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_WATERING_CAN, ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_WATERING_CAN);

	//TOMATO CRATE TEXTURES
	initializeEntryGroupInDecisionFactorToAnimationBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_TOMATO_CRATE_ONE, ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_TOMATO_CRATE, ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_TOMATO_CRATE, ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_TOMATO_CRATE, ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_TOMATO_CRATE);
	initializeEntryGroupInDecisionFactorToAnimationBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_TOMATO_CRATE_TWO, ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_TOMATO_CRATE, ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_TOMATO_CRATE, ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_TOMATO_CRATE, ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_TOMATO_CRATE);
	initializeEntryGroupInDecisionFactorToAnimationBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_TOMATO_CRATE_THREE, ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_TOMATO_CRATE, ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_TOMATO_CRATE, ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_TOMATO_CRATE, ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_TOMATO_CRATE);
	initializeEntryGroupInDecisionFactorToAnimationBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_TOMATO_CRATE_ONE_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_TOMATO_CRATE_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_TOMATO_CRATE_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_TOMATO_CRATE_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_TOMATO_CRATE_FILLED);
	initializeEntryGroupInDecisionFactorToAnimationBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_TOMATO_CRATE_TWO_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_TOMATO_CRATE_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_TOMATO_CRATE_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_TOMATO_CRATE_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_TOMATO_CRATE_FILLED);
	initializeEntryGroupInDecisionFactorToAnimationBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_TOMATO_CRATE_THREE_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_TOMATO_CRATE_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_TOMATO_CRATE_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_TOMATO_CRATE_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_TOMATO_CRATE_FILLED);

	//CUCUMBER CRATE TEXTURES
	initializeEntryGroupInDecisionFactorToAnimationBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CUCUMBER_CRATE_ONE, ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CUCUMBER_CRATE, ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CUCUMBER_CRATE, ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CUCUMBER_CRATE, ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CUCUMBER_CRATE);
	initializeEntryGroupInDecisionFactorToAnimationBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CUCUMBER_CRATE_TWO, ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CUCUMBER_CRATE, ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CUCUMBER_CRATE, ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CUCUMBER_CRATE, ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CUCUMBER_CRATE);
	initializeEntryGroupInDecisionFactorToAnimationBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CUCUMBER_CRATE_THREE, ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CUCUMBER_CRATE, ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CUCUMBER_CRATE, ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CUCUMBER_CRATE, ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CUCUMBER_CRATE);
	initializeEntryGroupInDecisionFactorToAnimationBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CUCUMBER_CRATE_ONE_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CUCUMBER_CRATE_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CUCUMBER_CRATE_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CUCUMBER_CRATE_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CUCUMBER_CRATE_FILLED);
	initializeEntryGroupInDecisionFactorToAnimationBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CUCUMBER_CRATE_TWO_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CUCUMBER_CRATE_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CUCUMBER_CRATE_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CUCUMBER_CRATE_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CUCUMBER_CRATE_FILLED);
	initializeEntryGroupInDecisionFactorToAnimationBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CUCUMBER_CRATE_THREE_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CUCUMBER_CRATE_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CUCUMBER_CRATE_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CUCUMBER_CRATE_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CUCUMBER_CRATE_FILLED);

	//CARROT CRATE TEXTURES
	initializeEntryGroupInDecisionFactorToAnimationBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CARROT_CRATE_ONE, ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CARROT_CRATE, ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CARROT_CRATE, ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CARROT_CRATE, ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CARROT_CRATE);
	initializeEntryGroupInDecisionFactorToAnimationBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CARROT_CRATE_TWO, ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CARROT_CRATE, ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CARROT_CRATE, ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CARROT_CRATE, ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CARROT_CRATE);
	initializeEntryGroupInDecisionFactorToAnimationBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CARROT_CRATE_THREE, ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CARROT_CRATE, ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CARROT_CRATE, ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CARROT_CRATE, ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CARROT_CRATE);
	initializeEntryGroupInDecisionFactorToAnimationBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CARROT_CRATE_ONE_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CARROT_CRATE_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CARROT_CRATE_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CARROT_CRATE_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CARROT_CRATE_FILLED);
	initializeEntryGroupInDecisionFactorToAnimationBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CARROT_CRATE_TWO_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CARROT_CRATE_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CARROT_CRATE_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CARROT_CRATE_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CARROT_CRATE_FILLED);
	initializeEntryGroupInDecisionFactorToAnimationBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CARROT_CRATE_THREE_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CARROT_CRATE_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CARROT_CRATE_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CARROT_CRATE_FILLED, ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CARROT_CRATE_FILLED);

	//TOMATO SEED PACKET TEXTURES
	initializeEntryGroupInDecisionFactorToAnimationBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_TOMATO_SEED_PACKET_ONE, ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_TOMATO_SEEDS, ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_TOMATO_SEEDS, ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_TOMATO_SEEDS, ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_TOMATO_SEEDS);
	initializeEntryGroupInDecisionFactorToAnimationBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_TOMATO_SEED_PACKET_TWO, ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_TOMATO_SEEDS, ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_TOMATO_SEEDS, ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_TOMATO_SEEDS, ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_TOMATO_SEEDS);
	initializeEntryGroupInDecisionFactorToAnimationBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_TOMATO_SEED_PACKET_THREE, ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_TOMATO_SEEDS, ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_TOMATO_SEEDS, ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_TOMATO_SEEDS, ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_TOMATO_SEEDS);

	//CUCUMBER SEED PACKET TEXTURES
	initializeEntryGroupInDecisionFactorToAnimationBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CUCUMBER_SEED_PACKET_ONE, ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CUCUMBER_SEEDS, ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CUCUMBER_SEEDS, ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CUCUMBER_SEEDS, ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CUCUMBER_SEEDS);
	initializeEntryGroupInDecisionFactorToAnimationBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CUCUMBER_SEED_PACKET_TWO, ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CUCUMBER_SEEDS, ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CUCUMBER_SEEDS, ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CUCUMBER_SEEDS, ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CUCUMBER_SEEDS);
	initializeEntryGroupInDecisionFactorToAnimationBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CUCUMBER_SEED_PACKET_THREE, ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CUCUMBER_SEEDS, ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CUCUMBER_SEEDS, ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CUCUMBER_SEEDS, ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CUCUMBER_SEEDS);

	//CARROT SEED PACKET TEXTURES
	initializeEntryGroupInDecisionFactorToAnimationBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CARROT_SEED_PACKET_ONE, ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CARROT_SEEDS, ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CARROT_SEEDS, ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CARROT_SEEDS, ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CARROT_SEEDS);
	initializeEntryGroupInDecisionFactorToAnimationBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CARROT_SEED_PACKET_TWO, ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CARROT_SEEDS, ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CARROT_SEEDS, ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CARROT_SEEDS, ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CARROT_SEEDS);
	initializeEntryGroupInDecisionFactorToAnimationBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_CARROT_SEED_PACKET_THREE, ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CARROT_SEEDS, ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CARROT_SEEDS, ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CARROT_SEEDS, ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CARROT_SEEDS);

	//NO HELD WORLD OBJECT
	initializeEntryGroupInDecisionFactorToAnimationBankRefNumberMap(WORLD_OBJECT_REF_NUMBER_INVALID, ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK, ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK, ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK, ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK);
}

void Alice::initializeEntryGroupInDecisionFactorToAnimationBankRefNumberMap(WorldObjectReferenceNumber heldWorldObjectReferenceNumberArg, AnimationBankReferenceNumber leftAnimation, AnimationBankReferenceNumber rightAnimation, AnimationBankReferenceNumber upAnimation, AnimationBankReferenceNumber downAnimation)
{
	this->initializeEntryInDecisionFactorToAnimationBankRefNumberMap(heldWorldObjectReferenceNumberArg,-1,-1,rightAnimation);
	this->initializeEntryInDecisionFactorToAnimationBankRefNumberMap(heldWorldObjectReferenceNumberArg,-1,0,rightAnimation);
	this->initializeEntryInDecisionFactorToAnimationBankRefNumberMap(heldWorldObjectReferenceNumberArg,-1,1,rightAnimation);
	this->initializeEntryInDecisionFactorToAnimationBankRefNumberMap(heldWorldObjectReferenceNumberArg,0,-1,downAnimation);
	this->initializeEntryInDecisionFactorToAnimationBankRefNumberMap(heldWorldObjectReferenceNumberArg,0,0,downAnimation);
	this->initializeEntryInDecisionFactorToAnimationBankRefNumberMap(heldWorldObjectReferenceNumberArg,0,1,upAnimation);
	this->initializeEntryInDecisionFactorToAnimationBankRefNumberMap(heldWorldObjectReferenceNumberArg,1,-1,leftAnimation);
	this->initializeEntryInDecisionFactorToAnimationBankRefNumberMap(heldWorldObjectReferenceNumberArg,1,0,leftAnimation);
	this->initializeEntryInDecisionFactorToAnimationBankRefNumberMap(heldWorldObjectReferenceNumberArg,1,1,leftAnimation);
}

void Alice::initializeEntryInDecisionFactorToAnimationBankRefNumberMap(WorldObjectReferenceNumber heldWorldObjectReferenceNumberArg, int xMovementAmount, int yMovementAmount, AnimationBankReferenceNumber animationBankRefNumberArg)
{
	AliceAnimationAndTextureDecisionFactors keyToAdd;
	keyToAdd.heldWorldObjectReferenceNumber = heldWorldObjectReferenceNumberArg;
	keyToAdd.xMovementAmount = xMovementAmount;
	keyToAdd.yMovementAmount = yMovementAmount;
	if(decisionFactorsToTextureBankRefNumberMap.count(keyToAdd) == 1)
	{
		decisionFactorsToAnimationBankRefNumberMap.erase(keyToAdd);
	}
	decisionFactorsToAnimationBankRefNumberMap.insert(std::pair<AliceAnimationAndTextureDecisionFactors, AnimationBankReferenceNumber>(keyToAdd, animationBankRefNumberArg));
}

void Alice::setReferenceNumberOfHeldWorldObject(WorldObjectReferenceNumber newReferenceNumberOfHeldWorldObject)
{
	if((this->referenceNumberOfHeldWorldObject) != WORLD_OBJECT_REF_NUMBER_INVALID)
	{
		this->referenceNumberOfHeldWorldObject = newReferenceNumberOfHeldWorldObject;
	}
}

