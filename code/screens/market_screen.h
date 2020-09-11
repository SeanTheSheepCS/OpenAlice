#ifndef MARKET_SCREEN_H
#define MARKET_SCREEN_H

#include <SFML/Graphics.hpp>
#include "screen.h"

class MarketScreen: public Screen
{
    public:
        MarketScreen(int width, int height);
        void handleEvent(sf::Event); 
        void forceFullDraw();
        void update(sf::Int32 millisecondsElapsedSinceLastUpdate);
    protected:
        //
    private:
        //
};

#endif
