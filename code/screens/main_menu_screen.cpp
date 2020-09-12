#include "main_menu_screen.h"

MainMenuScreen::MainMenuScreen(int x, int y, int width, int height): OAEScreen(x, y, width, height)
{
    this->title = TexturedObject(x,y,width,(height*0.4),nullptr);
}

void MainMenuScreen::handleEvent(sf::Event event)
{

}

void MainMenuScreen::forceFullDraw(sf::RenderWindow& windowToDrawIn)
{
    
}

void MainMenuScreen::update(sf::Int32 millisecondsElapsedSinceLastUpdate)
{

}
