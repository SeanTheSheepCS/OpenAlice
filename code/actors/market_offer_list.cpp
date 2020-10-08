#include "market_offer_list.h"

MarketOfferList::MarketOfferList(int x, int y, unsigned int width, unsigned int height, unsigned int offersPerPage):
    DrawableObject(x, y, width, height),
    background(x, y, width, height, nullptr)
{
    this->numberOfMarketOffersPerPage = offersPerPage;
}

void MarketOfferList::eraseOfferAtIndex(int index)
{
	marketOfferVector.erase(marketOfferVector.begin() + index);
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

int MarketOfferList::returnIndexOfSelectedMarketOfferIfOneHasBeenSelectedElseReturnMinusOne(int mouseX, int mouseY)
{
    for(int i = 0; i <  marketOfferVector.size(); i++)
	{
		if (marketOfferVector.at(i).isSelectButtonPressedBasedOnMouseXAndMouseY(mouseX, mouseY))
		{
			return i;
		}
	}
	return -1;
}

void MarketOfferList::draw(sf::RenderWindow& windowToDrawObjectIn)
{
    background.draw(windowToDrawObjectIn);
    for(int i = 0; i <  marketOfferVector.size(); i++)
	{
		marketOfferVector.at(i).draw(windowToDrawObjectIn);
	}
}
