#ifndef CREDITS_SCREEN_H
#define CREDITS_SCREEN_H

#include <SFML/Graphics.hpp>
#include "../oae_screen.h"
#include "../../engine/primitive_classes/textured_object.h"
#include "../../engine/primitive_classes/textured_button_object.h"

class CreditsScreen: public OAEScreen
{
    public:
        CreditsScreen(int x, int y, unsigned int width, unsigned int height);
        void handleEvent(sf::Event event); 
        void forceFullDraw(sf::RenderWindow& windowToDrawIn);
        void update(sf::Int32 millisecondsElapsedSinceLastUpdate);
    protected:
        //
    private:
        TexturedObject background;
        TexturedButtonObject exitScreenButton;
};

#endif
