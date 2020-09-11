#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>

class Screen
{
    public:
        Screen(int width, int height);
        virtual void handleEvent(sf::Event) = 0;
        virtual void forceFullDraw() = 0;
        virtual void update(sf::Int32 millisecondsElapsedSinceLastUpdate) = 0;
    protected:
        //
    private:
        unsigned int width;
        unsigned int height;
}

#endif
