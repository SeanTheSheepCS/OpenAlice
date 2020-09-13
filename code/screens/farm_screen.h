#ifndef FARM_SCREEN_H
#define FARM_SCREEN_H

#include <SFML/Graphics.hpp>
#include "oae_screen.h"
#include "../engine/primitive_classes/textured_object.h"
#include "../engine/primitive_classes/textured_button_object.h"
#include "../engine/advanced_classes/number_display_module/number_display_module.h"

class FarmScreen: public OAEScreen
{
    public:
        FarmScreen(int x, int y, unsigned int width, unsigned int height);
        void handleEvent(sf::Event event, sf::RenderWindow& window); 
        void forceFullDraw(sf::RenderWindow& windowToDrawIn);
        void update(sf::Int32 millisecondsElapsedSinceLastUpdate);
    protected:
        //
    private:
        TexturedObject background;
};

#endif
