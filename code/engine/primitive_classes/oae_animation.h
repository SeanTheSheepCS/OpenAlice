#ifndef OAE_ANIMATION_H
#define OAE_ANIMATION_H

#include <SFML/Graphics.hpp>

class OAEAnimation
{
    public:
        OAEAnimation(unsigned int speedInMillisecondsPerAdvanceFrame);
        unsigned int getFrameVectorSize() const;
        void setAnimationSpeedInMillisecondsPerAdvanceFrame(unsigned int newSpeed);
        const sf::Texture* getFrameAtSpecifiedMilliseconds(unsigned int specifiedMilliseconds) const;
        unsigned int getTotalMillisecondCountForAnimation() const;
        void appendTextureToAnimation(const sf::Texture* textureToAppend);
    protected:
        //
    private:
        std::vector<const sf::Texture*> frameVector;
        unsigned int animationSpeedInMillisecondsToAdvanceFrame;
};

#endif
