#ifndef OAE_ANIMATION_BANK_H
#define OAE_ANIMATION_BANK_H

#include "engine/primitive_classes/oae_animation.h"
#include "engine/primitive_classes/oae_animation_instance.h"
#include <map>

class OAEAnimationBank
{
	public:
		OAEAnimationBank();
		void saveOAEAnimationWithReferenceNumber(int referenceNumber, const OAEAnimation animationToSave);
		const OAEAnimation* getAnimationAssociatedWithReferenceNumber(int referenceNumber) const;
		void deleteAnimationWithReferenceNumber(int referenceNumber);
	protected:
		//
	private:
		std::map<int, const OAEAnimation> referenceNumberToAnimationMap;
};

#endif
