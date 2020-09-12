#ifndef MAIN_MENU_SCREEN_H
#define MAIN_MENU_SCREEN_H

#include <SFML/Graphics.hpp>
#include "oae_screen.h"

class MainMenuScreen: public OAEScreen
{
    public:
        MainMenuScreen(int width, int height);
        void handleEvent(sf::Event); 
        void forceFullDraw();
        void update(sf::Int32 millisecondsElapsedSinceLastUpdate);
    protected:
        //
    private:
        //
};

#endif
