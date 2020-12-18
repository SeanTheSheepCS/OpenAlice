#ifndef OAE_ANIMATED_OBJECT
#define OAE_ANIMATED_OBJECT

#include "oae_animation_instance.h"
#include <map>

class OAEAnimatedObject
{
	public:
		OAEAnimatedObject();
		void associateReferenceNumberWithAnimationInstance(int referenceNumber, const OAEAnimationInstance animationInstance);
		void deassociateAnimationInstanceWithSpecificReferenceNumber(int referenceNumber);
		void setCurrentAnimationInstanceReferenceNumber(int currentAnimationInstanceReferenceNumber);
	protected:
		int currentAnimationInstanceReferenceNumber;
		std::map<int, OAEAnimationInstance> referenceNumberToAnimationInstanceMap;
	private:
		//
};

#endif
