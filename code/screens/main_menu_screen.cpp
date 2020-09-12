#include "main_menu_screen.h"

MainMenuScreen::MainMenuScreen(int x, int y, unsigned int width, unsigned int height): 
    OAEScreen(x, y, width, height),
    backgroundWithTitle(x,y,width,height,nullptr),
    startGameButton(x+(width*0.1),y+(height*0.55), (width*0.8), (height*0.15), nullptr),
    creditsButton(x+(width*0.1),y+(height*0.70), (width*0.8), (height*0.15), nullptr),
    exitGameButton(x+(width*0.1),y+(height*0.85), (width*0.8), (height*0.15), nullptr)
{
    //
}

void MainMenuScreen::handleEvent(sf::Event event)
{

}

void MainMenuScreen::forceFullDraw(sf::RenderWindow& windowToDrawIn)
{
    backgroundWithTitle.draw(windowToDrawIn);
    startGameButton.draw(windowToDrawIn);
    creditsButton.draw(windowToDrawIn);
    exitGameButton.draw(windowToDrawIn);
}

void MainMenuScreen::update(sf::Int32 millisecondsElapsedSinceLastUpdate)
{

}
