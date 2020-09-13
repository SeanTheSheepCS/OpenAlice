#include "farm_screen.h"

FarmScreen::FarmScreen(int x, int y, unsigned int width, unsigned int height): 
    OAEScreen(x, y, width, height),
    background(x, y, width, height, nullptr)
{

}

void FarmScreen::handleEvent(sf::Event event, sf::RenderWindow& window)
{
    
}

void FarmScreen::forceFullDraw(sf::RenderWindow& windowToDrawIn)
{
    background.draw(windowToDrawIn);
}

void FarmScreen::update(sf::Int32 millisecondsElapsedSinceLastUpdate)
{

}
