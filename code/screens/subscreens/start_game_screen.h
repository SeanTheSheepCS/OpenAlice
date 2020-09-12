#ifndef START_GAME_SCREEN_H
#define START_GAME_SCREEN_H

#include <SFML/Graphics.hpp>
#include "../oae_screen.h"
#include "../../engine/primitive_classes/textured_object.h"
#include "../../engine/primitive_classes/textured_button_object.h"

class StartGameScreen: public OAEScreen
{
    public:
        StartGameScreen(int x, int y, unsigned int width, unsigned int height);
        void handleEvent(sf::Event event); 
        void forceFullDraw(sf::RenderWindow& windowToDrawIn);
        void update(sf::Int32 millisecondsElapsedSinceLastUpdate);
    protected:
        //
    private:
        TexturedObject background;
        TexturedButtonObject exitScreenButton;
        TexturedButtonObject selectFileOneButton;
        TexturedButtonObject deleteFileOneButton;
        TexturedButtonObject selectFileTwoButton;
        TexturedButtonObject deleteFileTwoButton;
        TexturedButtonObject selectFileThreeButton;
        TexturedButtonObject deleteFileThreeButton;
};

#endif
