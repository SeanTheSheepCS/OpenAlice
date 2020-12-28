#ifndef SALE_EVENT_H
#define SALE_EVENT_H

#include "../reference_number_enums.h"

class SaleEvent
{
	public:
		SaleEvent(WorldObjectReferenceNumber suggestedSoldWorldObjectReferenceNumberArg);
		WorldObjectReferenceNumber getSuggestedSoldWorldObjectReferenceNumber();
	protected:
		//
	private:
		WorldObjectReferenceNumber suggestedSoldWorldObjectReferenceNumber;
};

#endif
