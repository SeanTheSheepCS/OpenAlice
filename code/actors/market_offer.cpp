#include "market_offer.h"

MarketOffer::MarketOffer(int x, int y, unsigned int width, unsigned int height):
    DrawableObject(x, y, width, height),
    background(x, y, width, height, nullptr),
    commodityOneIcon(x, y, width, height, nullptr),
    commodityOneCountDisplay(x, y, width, height, 2),
    commodityTwoIcon(x, y, width, height, nullptr),
    commodityTwoCountDisplay(x, y, width, height, 2),
    selectButton(x+(width*0.7), y+(height*0.3), width*0.25, height*0.4, nullptr)
{

}

void MarketOffer::draw(sf::RenderWindow& windowToDrawObjectIn)
{
    background.draw(windowToDrawObjectIn);
    commodityOneIcon.draw(windowToDrawObjectIn);
    commodityOneCountDisplay.draw(windowToDrawObjectIn);
    commodityTwoIcon.draw(windowToDrawObjectIn);
    commodityTwoCountDisplay.draw(windowToDrawObjectIn);
    selectButton.draw(windowToDrawObjectIn);
}
