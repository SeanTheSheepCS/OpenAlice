#ifndef FARM_SCREEN_H
#define FARM_SCREEN_H

#include <SFML/Graphics.hpp>
#include "oae_screen.h"

class FarmScreen: public OAEScreen
{
    public:
        FarmScreen(int x, int y, unsigned int width, unsigned int height);
        void handleEvent(sf::Event event); 
        void forceFullDraw();
        void update(sf::Int32 millisecondsElapsedSinceLastUpdate);
    protected:
        //
    private:
        //
};

#endif
