#ifndef OAE_ANIMATION_INSTANCE_H
#define OAE_ANIMATION_INSTANCE_H

#include "oae_animation.h"
#include <SFML/Graphics.hpp>

class OAEAnimationInstance
{
	public:
		OAEAnimationInstance(const OAEAnimation* animationToUseArg);
		void incrementMillisecondCountByAmount(unsigned int amountToIncrementBy);
		void setMillisecondCountToZero();
		unsigned int getMillisecondProgressInAnimation() const;
		const sf::Texture* getCurrentFrame() const;
	protected:
		//
	private:
		const OAEAnimation* animationToUse;
		unsigned int millisecondsProgressInAnimation;
};

#endif
