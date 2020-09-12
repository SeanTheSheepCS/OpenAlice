#ifndef MAIN_MENU_SCREEN_H
#define MAIN_MENU_SCREEN_H

#include <SFML/Graphics.hpp>
#include "oae_screen.h"
#include "../engine/primitive_classes/textured_object.h"
#include "../engine/primitive_classes/textured_button_object.h"
#include "subscreens/start_game_screen.h"
#include "subscreens/credits_screen.h"

enum MainMenuScreenSubscreenState
{
    NO_SUBSCREEN_ACTIVE = 0,
    START_GAME_SUBSCREEN_ACTIVE = 1,
    CREDITS_SUBSCREEN_ACTIVE = 2
};

class MainMenuScreen: public OAEScreen
{
    public:
        MainMenuScreen(int x, int y, unsigned int width, unsigned int height);
        void handleEvent(sf::Event event); 
        void forceFullDraw(sf::RenderWindow& windowToDrawIn);
        void update(sf::Int32 millisecondsElapsedSinceLastUpdate);
    protected:
        //
    private:
        //Base title screen components
        TexturedObject backgroundWithTitle;
        TexturedButtonObject startGameButton;
        TexturedButtonObject creditsButton;
        TexturedButtonObject exitGameButton;

        //For subscreens
        MainMenuScreenSubscreenState subscreenState;
        StartGameScreen startGameScreenVar;
        CreditsScreen creditsScreenVar;
};

#endif
