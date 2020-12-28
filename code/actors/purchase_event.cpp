#include "purchase_event.h"

PurchaseEvent::PurchaseEvent(WorldObjectReferenceNumber suggestedPurchasedWorldObjectReferenceNumberArg, WorldObject worldObjectPurchasedArg)
{
	this->suggestedPurchasedWorldObjectReferenceNumber = suggestedPurchasedWorldObjectReferenceNumberArg;
	this->worldObjectPurchased = worldObjectPurchasedArg;
}

WorldObjectReferenceNumber PurchaseEvent::getSuggestedPurchasedObjectReferenceNumber() const
{
	return (this->suggestedPurchasedWorldObjectReferenceNumber);
}

WorldObject PurchaseEvent::getPurchasedWorldObject() const
{
	return (this->worldObjectPurchased);
}
