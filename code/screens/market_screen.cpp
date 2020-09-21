#include "market_screen.h"

MarketScreen::MarketScreen(int x, int y, unsigned int width, unsigned int height):
    OAEScreen(x, y, width, height),
    background(x, y, width, height, nullptr),
    displaysTheWordDay(x, y, (width*0.2), height*0.1, nullptr),
    dayNumberDisplay(x+(width*0.2), y, (width*0.4), height*0.1, 4),
    displaysAMoneySign(x+(width*0.6), y, (width*0.1), height*0.1, nullptr),
    moneyDisplay(x+(width*0.7), y, width*0.3, (height*0.1), 8),
    returnToFarmButton(x+(width*0.04), y+(height*0.1), width*0.2, height*0.1, nullptr),
    tomatoIcon(x+(width*0.24), y+(height*0.1), (width*0.12), (height*0.1), nullptr),
    tomatoCount(x+(width*0.36), y+(height*0.1), (width*0.12), (height*0.1), 2),
    zucchiniIcon(x+(width*0.48), y+(height*0.1), (width*0.12), (height*0.1), nullptr),
    zucchiniCount(x+(width*0.60), y+(height*0.1), (width*0.12), (height*0.1), 2),
    carrotIcon(x+(width*0.72), y+(height*0.1), (width*0.12), (height*0.1), nullptr),
    carrotCount(x+(width*0.84), y+(height*0.1), (width*0.12), (height*0.1), 2),
    sellWord(x+(width*0.02), y+(height*0.3), (width*0.35), (height*0.1), nullptr),
    itemsForSale(x+(width*0.02), y+(height*0.45), (width*0.35), (height*0.5), 3),
    buyWord(x+(width*0.4), y+(height*0.3), (width*0.35), (height*0.1), nullptr),
    itemsToBuy(x+(width*0.4), y+(height*0.45), (width*0.35), (height*0.5), 3)
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

    displaysTheWordDay.draw(windowToDrawIn);
    dayNumberDisplay.draw(windowToDrawIn);
    displaysAMoneySign.draw(windowToDrawIn);
    moneyDisplay.draw(windowToDrawIn);

    tomatoIcon.draw(windowToDrawIn);
    tomatoCount.draw(windowToDrawIn);
    zucchiniIcon.draw(windowToDrawIn);
    zucchiniCount.draw(windowToDrawIn);
    carrotIcon.draw(windowToDrawIn);
    carrotCount.draw(windowToDrawIn);

    sellWord.draw(windowToDrawIn);
    itemsForSale.draw(windowToDrawIn);
    buyWord.draw(windowToDrawIn);
    itemsToBuy.draw(windowToDrawIn);
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
