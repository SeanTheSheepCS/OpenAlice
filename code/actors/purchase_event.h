#ifndef PURCHASE_EVENT_H
#define PURCHASE_EVENT_H

#include "../reference_number_enums.h"
#include "../engine/primitive_classes/world_object.h"

class PurchaseEvent
{
	public:
		PurchaseEvent(WorldObjectReferenceNumber suggestedPurchasedWorldObjectReferenceNumberArg, WorldObject worldObjectPurchasedArg);
		WorldObjectReferenceNumber getSuggestedPurchasedObjectReferenceNumber() const;
		WorldObject getPurchasedWorldObject() const;
	protected:
		//
	private:
		WorldObjectReferenceNumber suggestedPurchasedWorldObjectReferenceNumber;
		WorldObject worldObjectPurchased;
};

#endif
