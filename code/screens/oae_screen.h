#ifndef OAE_SCREEN_H
#define OAE_SCREEN_H

#include <SFML/Graphics.hpp>

class OAEScreen
{
    public:
        OAEScreen(int x, int y, unsigned int width, unsigned int height);
        virtual void handleEvent(sf::Event event, sf::RenderWindow& window) = 0;
        virtual void forceFullDraw(sf::RenderWindow& windowToDrawIn) = 0;
        virtual void update(sf::Int32 millisecondsElapsedSinceLastUpdate, sf::RenderWindow& window) = 0;
    protected:
        //
    private:
        int x;
        int y;
        unsigned int width;
        unsigned int height;
};

#endif
