#include "sale_event.h"

SaleEvent::SaleEvent(WorldObjectReferenceNumber suggestedSoldWorldObjectReferenceNumberArg)
{
	this->suggestedSoldWorldObjectReferenceNumber = suggestedSoldWorldObjectReferenceNumberArg;
}

WorldObjectReferenceNumber SaleEvent::getSuggestedSoldWorldObjectReferenceNumber()
{
	return (this->suggestedSoldWorldObjectReferenceNumber);
}
