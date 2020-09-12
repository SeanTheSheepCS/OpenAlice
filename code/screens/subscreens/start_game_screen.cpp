#include "start_game_screen.h"

StartGameScreen::StartGameScreen(int x, int y, unsigned int width, unsigned int height):
    OAEScreen(x,y,width,height),
    background(x,y,width,height,nullptr),
    exitScreenButton(x+(width*0.9),y,(width*0.1),(height*0.1),nullptr),
    selectFileOneButton(x+(width*0.1),y+(height*0.125),(width*0.8),(height*0.25),nullptr),
    deleteFileOneButton(x+(width*0.65),y+(height*0.2),(width*0.1),(height*0.1),nullptr),
    selectFileTwoButton(x+(width*0.1),y+(height*0.375),(width*0.8),(height*0.25),nullptr),
    deleteFileTwoButton(x+(width*0.65),y+(height*0.45),(width*0.1),(height*0.1),nullptr),
    selectFileThreeButton(x+(width*0.1),y+(height*0.625),(width*0.8),(height*0.25),nullptr),
    deleteFileThreeButton(x+(width*0.65),y+(height*0.7),(width*0.1),(height*0.1),nullptr)
{

}

void StartGameScreen::handleEvent(sf::Event event)
{
    
}

void StartGameScreen::forceFullDraw(sf::RenderWindow& windowToDrawIn)
{
    background.draw(windowToDrawIn);
    exitScreenButton.draw(windowToDrawIn);
    selectFileOneButton.draw(windowToDrawIn);
    deleteFileOneButton.draw(windowToDrawIn);
    selectFileTwoButton.draw(windowToDrawIn);
    deleteFileTwoButton.draw(windowToDrawIn);
    selectFileThreeButton.draw(windowToDrawIn);
    deleteFileThreeButton.draw(windowToDrawIn);
}

void StartGameScreen::update(sf::Int32 millisecondsElapsedSinceLastUpdate)
{

}

