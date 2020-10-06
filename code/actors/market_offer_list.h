#ifndef MARKET_OFFER_LIST_H
#define MARKET_OFFER_LIST_H

#include "market_offer.h"
#include "../engine/primitive_classes/drawable_object.h"

class MarketOfferList: public DrawableObject
{
	public:
        MarketOfferList(int x, int y, unsigned int width, unsigned int height, unsigned int objectsPerPage);
		void appendMarketOffer(MarketOffer marketOfferToAppend);
        void draw(sf::RenderWindow& windowToDrawObjectIn);
    protected:
        //
    private:
        std::vector<MarketOffer> marketOfferVector;
        unsigned int numberOfMarketOffersPerPage;
        TexturedObject background;
};

#endif
