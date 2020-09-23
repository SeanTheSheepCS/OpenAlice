#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

class OAEAnimation
{
    public:
        OAEAnimation(unsigned int speedInMillisecondsPerAdvanceFrame);
        unsigned int getFrameVectorSize();
        void setAnimationSpeedInMillisecondsPerAdvanceFrame(unsigned int newSpeed);
        void incrementMillisecondCountByAmount(unsigned int amountToIncrementBy);
        void setMillisecondCountToZero();
        sf::Texture* getCurrentFrame();
    protected:
        //
    private:
        std::vector<sf::Texture*> frameVector;
        unsigned int currentMillisecondCount;
        unsigned int animationSpeedInMillisecondsToAdvanceFrame;
};

#endif
