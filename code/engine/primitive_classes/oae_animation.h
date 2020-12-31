#ifndef OAE_ANIMATION_H
#define OAE_ANIMATION_H

#include <SFML/Graphics.hpp>
#include <vector>

class OAEAnimation
{
	public:
		OAEAnimation();
		void setLingerAmountVector(std::vector<unsigned int> newAmountsToLinger);
		unsigned int getFrameVectorSize() const;
		const sf::Texture* getFrameAtSpecifiedMilliseconds(unsigned int specifiedMilliseconds) const;
		unsigned int getTotalMillisecondCountForAnimation() const;
		void appendTextureToAnimation(const sf::Texture* textureToAppend, unsigned int millisecondsToLinger);
	protected:
		//
	private:
		std::vector<const sf::Texture*> frameVector;
		std::vector<unsigned int> animationNumberOfMillisecondsToLingerOnEachFrame;
};

#endif
