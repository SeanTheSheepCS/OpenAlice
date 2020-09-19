#ifndef MARKET_SCREEN_H
#define MARKET_SCREEN_H

#include <SFML/Graphics.hpp>
#include "oae_screen.h"
#include "../engine/primitive_classes/textured_object.h"
#include "../engine/primitive_classes/textured_button_object.h"

class MarketScreen: public OAEScreen
{
    public:
        MarketScreen(int x, int y, unsigned int width, unsigned int height);
        void handleEvent(sf::Event event, sf::RenderWindow& window); 
        void forceFullDraw(sf::RenderWindow& windowToDrawIn);
        void update(sf::Int32 millisecondsElapsedSinceLastUpdate, sf::RenderWindow& window);
        bool returnIfShouldSwitchToFarmScreen();
        void acknowledgeShouldSwitchToFarmScreen();
    protected:
        //
    private:
        bool shouldSwitchToFarmScreenFlag;
        TexturedObject background;
        TexturedButtonObject returnToFarmButton;
};

#endif
