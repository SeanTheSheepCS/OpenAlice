#include "market_offer_list.h"

MarketOfferList::MarketOfferList(int x, int y, unsigned int width, unsigned int height, unsigned int offersPerPage):
    DrawableObject(x, y, width, height),
    background(x, y, width, height, nullptr)
{
    this->numberOfMarketOffersPerPage = offersPerPage;
}

void MarketOfferList::draw(sf::RenderWindow& windowToDrawObjectIn)
{
    background.draw(windowToDrawObjectIn);
}
