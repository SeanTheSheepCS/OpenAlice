#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

class OAEAnimation
{
    public:
        OAEAnimation();
        unsigned int getFrameVectorSize();
        void setAnimationSpeedInFramesAdvancedPerMillisecond(unsigned int newSpeed);
        void incrementMillisecondCountByAmount(unsigned int amountToIncrementBy);
        sf::Texture* getCurrentFrame();
    protected:
        //
    private:
        std::vector<sf::Texture*> frameVector;
        unsigned int currentMillisecondCount;
        unsigned int animationSpeedInFramesAdvancedPerMillisecond;
};

#endif
