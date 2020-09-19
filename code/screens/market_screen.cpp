#include "market_screen.h"

MarketScreen::MarketScreen(int x, int y, unsigned int width, unsigned int height):
    OAEScreen(x, y, width, height),
    background(x, y, width, height, nullptr),
    returnToFarmButton(x, y, width*0.3, height*0.1, nullptr)
{
    shouldSwitchToFarmScreenFlag = false;
}

void MarketScreen::handleEvent(sf::Event event, sf::RenderWindow& window)
{
    switch(event.type)
    {
        case sf::Event::MouseButtonPressed:
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                int mouseX = mousePosition.x;
                int mouseY = mousePosition.y;
                if(returnToFarmButton.theMouseHasBeenClickedAtTheSpecifiedCoordinatesHasTheButtonBeenClicked(mouseX, mouseY))
                {
                    this->shouldSwitchToFarmScreenFlag = true;
                }
            }
            break;
        default:
            //
            break;
    }
}

void MarketScreen::forceFullDraw(sf::RenderWindow& windowToDrawIn)
{
    background.draw(windowToDrawIn);
    returnToFarmButton.draw(windowToDrawIn);
}

bool MarketScreen::returnIfShouldSwitchToFarmScreen()
{
    return shouldSwitchToFarmScreenFlag;
}

void MarketScreen::acknowledgeShouldSwitchToFarmScreen()
{
    shouldSwitchToFarmScreenFlag = false;
}

void MarketScreen::update(sf::Int32 millisecondsElapsedSinceLastUpdate, sf::RenderWindow& window)
{

}
