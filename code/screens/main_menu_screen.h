#ifndef MAIN_MENU_SCREEN_H
#define MAIN_MENU_SCREEN_H

#include <SFML/Graphics.hpp>
#include "oae_screen.h"
#include "../engine/primitive_classes/textured_object.h"

class MainMenuScreen: public OAEScreen
{
    public:
        MainMenuScreen(int x, int y, unsigned int width, unsigned int height);
        void handleEvent(sf::Event event); 
        void forceFullDraw();
        void update(sf::Int32 millisecondsElapsedSinceLastUpdate);
    protected:
        //
    private:
        TexturedObject title;
};

#endif
