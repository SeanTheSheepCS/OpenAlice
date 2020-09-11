#ifndef FARM_SCREEN_H
#define FARM_SCREEN_H

#include <SFML/Graphics.hpp>
#include "screen.h"

class FarmScreen: public Screen
{
    public:
        FarmScreen(int width, int height);
        void handleEvent(sf::Event); 
        void forceFullDraw();
        void update(sf::Int32 millisecondsElapsedSinceLastUpdate);
    protected:
        //
    private:
        //
};

#endif
