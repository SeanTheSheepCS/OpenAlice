#include "credits_screen.h"

CreditsScreen::CreditsScreen(int x, int y, unsigned int width, unsigned int height):
    OAEScreen(x,y,width, height),
    background(x,y,width,height,nullptr),
    exitScreenButton(x,y,width,height,nullptr)
{

}

void CreditsScreen::handleEvent(sf::Event event)
{

}

void CreditsScreen::forceFullDraw(sf::RenderWindow& windowToDrawIn)
{
    background.draw(windowToDrawIn);
    exitScreenButton.draw(windowToDrawIn);
}

void CreditsScreen::update(sf::Int32 millisecondsElapsedSinceLastUpdate)
{

}
