#ifndef MARKET_OFFER_LIST_H
#define MARKET_OFFER_LIST_H

#include "market_offer.h"
#include "../engine/primitive_classes/drawable_object.h"

class MarketOfferList: public DrawableObject
{
	public:
		MarketOfferList(int x, int y, unsigned int width, unsigned int height, unsigned int objectsPerPage);

		void appendMarketOffer(MarketOffer marketOfferToAppend);
		void eraseOfferAtIndex(int index);
		void clearMarketOffers();

		void associateWithTexturesInBank(const TextureBank& textureBankToTakeFrom);

		unsigned int returnIndexOfSelectedMarketOfferIfOneHasBeenSelectedElseReturnMinusOne(int mouseX, int mouseY);
		MarketOffer returnMarketOfferAtIndex(unsigned int index);

		void draw(sf::RenderWindow& windowToDrawObjectIn);
	protected:
		//
	private:
		std::vector<MarketOffer> marketOfferVector;
		unsigned int numberOfMarketOffersPerPage;
		TexturedObject background;
		const TextureBank* textureBankToAssociateMarketOffersWithAsTheyComeIn;
};

#endif
