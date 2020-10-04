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
        tileMapToPutItDownIn.addWorldObjectWithReferenceNumber(referenceNumberOfHeldWorldObject, heldWorldObject);
        this->referenceNumberOfHeldWorldObject = WORLD_OBJECT_REF_NUMBER_INVALID;
        this->heldWorldObject = WorldObject();
    }
}

bool Alice::isHoldingObject()
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

int Alice::returnReferenceNumberOfHeldObject()
{
    return referenceNumberOfHeldWorldObject;
}
