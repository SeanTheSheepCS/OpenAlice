#include "market_offer_list.h"

MarketOfferList::MarketOfferList(int x, int y, unsigned int width, unsigned int height, unsigned int offersPerPage):
    DrawableObject(x, y, width, height),
    background(x, y, width, height, nullptr)
{
    this->numberOfMarketOffersPerPage = offersPerPage;
}

void MarketOfferList::appendMarketOffer(MarketOffer marketOfferToAppend)
{
	MarketOffer marketOfferToAppendWithDimensionsCorrected = marketOfferToAppend;
	marketOfferToAppendWithDimensionsCorrected.setXRecursiveWithinComponents(x);
	marketOfferToAppendWithDimensionsCorrected.setYRecursiveWithinComponents(y + ((marketOfferVector.size())*(height / numberOfMarketOffersPerPage)));
	marketOfferToAppendWithDimensionsCorrected.setWidthRecursiveWithinComponents(width);
	marketOfferToAppendWithDimensionsCorrected.setHeightRecursiveWithinComponents(height / numberOfMarketOffersPerPage);
	marketOfferVector.push_back(marketOfferToAppendWithDimensionsCorrected);
}

void MarketOfferList::draw(sf::RenderWindow& windowToDrawObjectIn)
{
    background.draw(windowToDrawObjectIn);
    for(int i = 0; i <  marketOfferVector.size(); i++)
	{
		marketOfferVector.at(i).draw(windowToDrawObjectIn);
	}
}
