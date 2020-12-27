#ifndef MARKET_SCREEN_H
#define MARKET_SCREEN_H

#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include "oae_screen.h"
#include "farm_screen.h"
#include "../engine/primitive_classes/textured_object.h"
#include "../engine/primitive_classes/world_object.h"
#include "../engine/primitive_classes/textured_button_object.h"
#include "../engine/advanced_classes/number_display_module/number_display_module.h"
#include "../actors/market_offer.h"
#include "../actors/market_offer_list.h"

class MarketScreen: public OAEScreen
{
	public:
		MarketScreen(int x, int y, unsigned int width, unsigned int height);

		void handleEvent(sf::Event event, sf::RenderWindow& window); 
		void forceFullDraw(sf::RenderWindow& windowToDrawIn);
		void update(sf::Int32 millisecondsElapsedSinceLastUpdate, sf::RenderWindow& window);

		void associateWithTexturesInBank(const TextureBank& textureBankToTakeFrom);

		void populateMarketWithSellOffer(MarketOffer sellOffer);
		void populateMarketWithBuyOffer(MarketOffer buyOffer);

		void populateMarketWithGarbageData();
		void populateMarketWithRandomOffers();

		bool returnIfShouldSwitchToFarmScreen();
		void acknowledgeShouldSwitchToFarmScreen();

		unsigned int getDay() const;
		unsigned int getMoneyAmount() const;

		void setMoneyDisplayAmount(unsigned int moneyDisplayAmount);
		void setDayDisplayAmount(unsigned int dayDisplayAmount);

		void setTradeableTomatoCount(unsigned int newTradeableTomatoCount);
		void setTradeableCucumberCount(unsigned int newTradeableCucumberCount);
		void setTradeableCarrotCount(unsigned int newTradeableCarrotCount);

		std::vector<WorldObject> getWorldObjectsPurchased();
		std::vector<WorldObjectReferenceNumber> getSuggestedWorldObjectReferenceNumbersForWorldObjectsPurchased();
		void acknowledgePurchasedWorldObjects();

		std::vector<WorldObjectReferenceNumber> getSuggestedReferenceNumbersOfCratesWhoseContentsWereSold();
		void acknowledgeSuggestedReferenceNumbersOfCratesWhoseContentsWereSold();
	protected:
		//
	private:
		void handlePurchase(unsigned int indexOfSaleOffer);
		void handleSale(unsigned int indexOfBuyOffer);

		bool shouldSwitchToFarmScreenFlag;

		//For giving information to the farm screen so that it can update appropriately.
		std::vector<WorldObject> worldObjectsPurchased;
		std::vector<WorldObjectReferenceNumber> worldObjectsPurchasedSuggestedReferenceNumbers;
		std::vector<WorldObjectReferenceNumber> suggestedReferenceNumbersOfCratesWhoseContentsWereSold;

		//Shared with farm screen
		TexturedObject displaysTheWordDay;
		NumberDisplay dayNumberDisplay;
		TexturedObject displaysAMoneySign;
		NumberDisplay moneyDisplay;

		//Icons for stock
		TexturedObject tomatoIcon;
		NumberDisplay tomatoCount;
		TexturedObject cucumberIcon;
		NumberDisplay cucumberCount;
		TexturedObject carrotIcon;
		NumberDisplay carrotCount;

		//Buy/Sell UI
		TexturedObject sellWord;
		MarketOfferList sellOffers;
		TexturedObject buyWord;
		MarketOfferList buyOffers;

		//Misc stuff
		TexturedObject background;
		TexturedButtonObject returnToFarmButton;
};

#endif
