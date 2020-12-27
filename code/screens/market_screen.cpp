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
	cucumberIcon(x+(width*0.48), y+(height*0.1), (width*0.12), (height*0.1), nullptr),
	cucumberCount(x+(width*0.60), y+(height*0.1), (width*0.12), (height*0.1), 2),
	carrotIcon(x+(width*0.72), y+(height*0.1), (width*0.12), (height*0.1), nullptr),
	carrotCount(x+(width*0.84), y+(height*0.1), (width*0.12), (height*0.1), 2),
	sellWord(x+(width*0.4), y+(height*0.3), (width*0.35), (height*0.1), nullptr),
	sellOffers(x+(width*0.4), y+(height*0.45), (width*0.35), (height*0.5), 3),
	buyWord(x+(width*0.02), y+(height*0.3), (width*0.35), (height*0.1), nullptr),
	buyOffers(x+(width*0.02), y+(height*0.45), (width*0.35), (height*0.5), 3)
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

				//Check for events with sellOffers and buyOffers
				unsigned int indexOfSellOffer = sellOffers.returnIndexOfSelectedMarketOfferIfOneHasBeenSelectedElseReturnMinusOne(mouseX, mouseY);
				if(indexOfSellOffer != -1)
				{
					handleSale(indexOfSellOffer);
					sellOffers.draw(window);
				}

				unsigned int indexOfBuyOffer = buyOffers.returnIndexOfSelectedMarketOfferIfOneHasBeenSelectedElseReturnMinusOne(mouseX, mouseY);
				if(indexOfBuyOffer != -1)
				{
					handlePurchase(indexOfBuyOffer);
					buyOffers.draw(window);
				}

			}
			break;
		default:
			//
			break;
	}
}

void MarketScreen::handlePurchase(unsigned int indexOfBuyOffer)
{
	TradeableCommodityEnum commodityToBeTraded = buyOffers.returnMarketOfferAtIndex(indexOfBuyOffer).getCommodityToBeTraded();
	unsigned int amountToBeTraded = buyOffers.returnMarketOfferAtIndex(indexOfBuyOffer).getAmountTraded();
	TradeableCommodityEnum commodityToBeTradedFor = buyOffers.returnMarketOfferAtIndex(indexOfBuyOffer).getCommodityToBeTradedFor();
	unsigned int amountToBeTradedFor = buyOffers.returnMarketOfferAtIndex(indexOfBuyOffer).getAmountTradedFor();
	if((commodityToBeTraded == TRADEABLE_COMMODITY_ENUM_MONEY) && (amountToBeTraded <= moneyDisplay.getNumber()))
	{
		WorldObject worldObjectBought;
		WorldObjectReferenceNumber worldObjectBoughtSuggestedReferenceNumber;
		switch(commodityToBeTradedFor)
		{
			case TRADEABLE_COMMODITY_ENUM_TOMATO_SEEDS:
				worldObjectBoughtSuggestedReferenceNumber = WORLD_OBJECT_REF_NUMBER_TOMATO_SEED_PACKET_ONE;
				worldObjectBought.setX(2200);
				worldObjectBought.setY(2000);
				worldObjectBought.setWidth(40);
				worldObjectBought.setHeight(40);
				{
					TriggerZone worldObjectBoughtTriggerZone(2200,2000,40,40,true);
					worldObjectBought.attachTriggerZone(worldObjectBoughtTriggerZone);
					worldObjectBought.setVisibility(true);
					worldObjectBought.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_PICKUPABLE);
					worldObjectBought.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_ACTION_PLANT_SEEDS_TOMATO);
					worldObjectBought.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_CAPACITY_10);
					worldObjectBought.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_FILLED_WITH_10);
					worldObjectBought.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_DELETES_WHEN_FILLED_WITH_0);
				}
				break;
			case TRADEABLE_COMMODITY_ENUM_CUCUMBER_SEEDS:
				worldObjectBoughtSuggestedReferenceNumber = WORLD_OBJECT_REF_NUMBER_CUCUMBER_SEED_PACKET_ONE;
				worldObjectBought.setX(2300);
				worldObjectBought.setY(2000);
				worldObjectBought.setWidth(40);
				worldObjectBought.setHeight(40);
				{
					TriggerZone worldObjectBoughtTriggerZone(2300,2000,40,40,true);
					worldObjectBought.attachTriggerZone(worldObjectBoughtTriggerZone);
					worldObjectBought.setVisibility(true);
					worldObjectBought.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_PICKUPABLE);
					worldObjectBought.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_ACTION_PLANT_SEEDS_CUCUMBER);
					worldObjectBought.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_CAPACITY_10);
					worldObjectBought.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_FILLED_WITH_10);
					worldObjectBought.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_DELETES_WHEN_FILLED_WITH_0);
				}
				break;
			case TRADEABLE_COMMODITY_ENUM_CARROT_SEEDS:
				worldObjectBoughtSuggestedReferenceNumber = WORLD_OBJECT_REF_NUMBER_CARROT_SEED_PACKET_ONE;
				worldObjectBought.setX(2400);
				worldObjectBought.setY(2000);
				worldObjectBought.setWidth(40);
				worldObjectBought.setHeight(40);
				{
					TriggerZone worldObjectBoughtTriggerZone(2400,2000,40,40,true);
					worldObjectBought.attachTriggerZone(worldObjectBoughtTriggerZone);
					worldObjectBought.setVisibility(true);
					worldObjectBought.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_PICKUPABLE);
					worldObjectBought.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_ACTION_PLANT_SEEDS_CARROT);
					worldObjectBought.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_CAPACITY_10);
					worldObjectBought.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_FILLED_WITH_10);
					worldObjectBought.addWorldObjectProperty(WORLD_OBJECT_PROPERTY_DELETES_WHEN_FILLED_WITH_0);
				}
				break;
		}
		worldObjectsPurchased.push_back(worldObjectBought);
		worldObjectsPurchasedSuggestedReferenceNumbers.push_back(worldObjectBoughtSuggestedReferenceNumber);
		buyOffers.eraseOfferAtIndex(indexOfBuyOffer);
	}
}

void MarketScreen::handleSale(unsigned int indexOfSaleOffer)
{
	//TODO
	sellOffers.eraseOfferAtIndex(indexOfSaleOffer);
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
	cucumberIcon.draw(windowToDrawIn);
	cucumberCount.draw(windowToDrawIn);
	carrotIcon.draw(windowToDrawIn);
	carrotCount.draw(windowToDrawIn);

	sellWord.draw(windowToDrawIn);
	sellOffers.draw(windowToDrawIn);
	buyWord.draw(windowToDrawIn);
	buyOffers.draw(windowToDrawIn);
}

void MarketScreen::associateWithTexturesInBank(const TextureBank& textureBankToTakeFrom)
{
	background.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_MARKET_SCREEN_BACKGROUND));
	dayNumberDisplay.associateWithTexturesInBank(textureBankToTakeFrom);
	moneyDisplay.associateWithTexturesInBank(textureBankToTakeFrom);
	displaysTheWordDay.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_DISPLAYS_THE_WORD_DAY_TEXTURE));
	displaysAMoneySign.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_MONEY_SIGN_DISPLAY_TEXTURE));
	returnToFarmButton.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_BACK_TO_FARM_BUTTON_TEXTURE));
	tomatoCount.associateWithTexturesInBank(textureBankToTakeFrom);
	cucumberCount.associateWithTexturesInBank(textureBankToTakeFrom);
	carrotCount.associateWithTexturesInBank(textureBankToTakeFrom);
	tomatoIcon.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_TOMATO_CRATE_ICON_TEXTURE));
	cucumberIcon.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CUCUMBER_CRATE_ICON_TEXTURE));
	carrotIcon.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CARROT_CRATE_ICON_TEXTURE));
	sellOffers.associateWithTexturesInBank(textureBankToTakeFrom);
	buyOffers.associateWithTexturesInBank(textureBankToTakeFrom);
	sellWord.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_DISPLAYS_THE_WORD_SELL));
	buyWord.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_DISPLAYS_THE_WORD_BUY));
}

void MarketScreen::populateMarketWithSellOffer(MarketOffer sellOffer)
{
	sellOffers.appendMarketOffer(sellOffer);
}

void MarketScreen::populateMarketWithBuyOffer(MarketOffer buyOffer)
{
	buyOffers.appendMarketOffer(buyOffer);
}

void MarketScreen::populateMarketWithGarbageData()
{
	populateMarketWithSellOffer(MarketOffer(0,0,0,0));
	populateMarketWithSellOffer(MarketOffer(0,0,0,0));
	populateMarketWithSellOffer(MarketOffer(0,0,0,0));
	populateMarketWithBuyOffer(MarketOffer(0,0,0,0));
	populateMarketWithBuyOffer(MarketOffer(0,0,0,0));
	populateMarketWithBuyOffer(MarketOffer(0,0,0,0));
}

void MarketScreen::populateMarketWithRandomOffers()
{
	sellOffers.clearMarketOffers();
	buyOffers.clearMarketOffers();

	srand(time(NULL));

	MarketOffer tomatoCrateForMoney = MarketOffer(0,0,0,0);
	tomatoCrateForMoney.setCommodityToBeTraded(TRADEABLE_COMMODITY_ENUM_TOMATO_CRATE, 1);
	unsigned int tomatoCratePrice = (rand() % 20)+40;
	tomatoCrateForMoney.setCommodityToBeTradedFor(TRADEABLE_COMMODITY_ENUM_MONEY, tomatoCratePrice);
	sellOffers.appendMarketOffer(tomatoCrateForMoney);

	MarketOffer cucumberCrateForMoney = MarketOffer(0,0,0,0);
	cucumberCrateForMoney.setCommodityToBeTraded(TRADEABLE_COMMODITY_ENUM_CUCUMBER_CRATE, 1);
	unsigned int cucumberCratePrice = (rand() % 29)+70;
	cucumberCrateForMoney.setCommodityToBeTradedFor(TRADEABLE_COMMODITY_ENUM_MONEY, cucumberCratePrice);
	sellOffers.appendMarketOffer(cucumberCrateForMoney);

	MarketOffer carrotCrateForMoney = MarketOffer(0,0,0,0);
	carrotCrateForMoney.setCommodityToBeTraded(TRADEABLE_COMMODITY_ENUM_CARROT_CRATE, 1);
	unsigned int carrotCratePrice = (rand() % 10)+10;
	carrotCrateForMoney.setCommodityToBeTradedFor(TRADEABLE_COMMODITY_ENUM_MONEY, carrotCratePrice);
	sellOffers.appendMarketOffer(carrotCrateForMoney);

	MarketOffer moneyForTomatoSeeds = MarketOffer(0,0,0,0);
	unsigned int tomatoSeedsPrice = (rand() % 20)+20;
	moneyForTomatoSeeds.setCommodityToBeTraded(TRADEABLE_COMMODITY_ENUM_MONEY, tomatoSeedsPrice);
	moneyForTomatoSeeds.setCommodityToBeTradedFor(TRADEABLE_COMMODITY_ENUM_TOMATO_SEEDS, 1);
	buyOffers.appendMarketOffer(moneyForTomatoSeeds);

	MarketOffer moneyForCucumberSeeds = MarketOffer(0,0,0,0);
	unsigned int cucumberSeedsPrice = (rand() % 40)+30;
	moneyForCucumberSeeds.setCommodityToBeTraded(TRADEABLE_COMMODITY_ENUM_MONEY, cucumberSeedsPrice);
	moneyForCucumberSeeds.setCommodityToBeTradedFor(TRADEABLE_COMMODITY_ENUM_CUCUMBER_SEEDS, 1);
	buyOffers.appendMarketOffer(moneyForCucumberSeeds);

	MarketOffer moneyForCarrotSeeds = MarketOffer(0,0,0,0);
	unsigned int carrotSeedsPrice = (rand() % 5)+5;
	moneyForCarrotSeeds.setCommodityToBeTraded(TRADEABLE_COMMODITY_ENUM_MONEY, carrotSeedsPrice);
	moneyForCarrotSeeds.setCommodityToBeTradedFor(TRADEABLE_COMMODITY_ENUM_CARROT_SEEDS, 1);
	buyOffers.appendMarketOffer(moneyForCarrotSeeds);
}

bool MarketScreen::returnIfShouldSwitchToFarmScreen()
{
	return shouldSwitchToFarmScreenFlag;
}

void MarketScreen::acknowledgeShouldSwitchToFarmScreen()
{
	shouldSwitchToFarmScreenFlag = false;
}

unsigned int MarketScreen::getDay() const
{
	return dayNumberDisplay.getNumber();
}

unsigned int MarketScreen::getMoneyAmount() const
{
	return moneyDisplay.getNumber();
}	

void MarketScreen::setMoneyDisplayAmount(unsigned int moneyDisplayAmount)
{
	moneyDisplay.setNumberDisplayAmount(moneyDisplayAmount);
}

void MarketScreen::setDayDisplayAmount(unsigned int dayDisplayAmount)
{
	dayNumberDisplay.setNumberDisplayAmount(dayDisplayAmount);
}

void MarketScreen::update(sf::Int32 millisecondsElapsedSinceLastUpdate, sf::RenderWindow& window)
{
}

std::vector<WorldObject> MarketScreen::getWorldObjectsPurchased()
{
	return worldObjectsPurchased;
}

std::vector<WorldObjectReferenceNumber> MarketScreen::getSuggestedWorldObjectReferenceNumbersForWorldObjectsPurchased()
{
	return worldObjectsPurchasedSuggestedReferenceNumbers;
}

void MarketScreen::acknowledgePurchasedWorldObjects()
{
	worldObjectsPurchased.clear();
	worldObjectsPurchasedSuggestedReferenceNumbers.clear();
}

std::vector<WorldObjectReferenceNumber> MarketScreen::getSuggestedReferenceNumbersOfCratesWhoseContentsWereSold()
{
	return suggestedReferenceNumbersOfCratesWhoseContentsWereSold;
}

void MarketScreen::acknowledgeSuggestedReferenceNumbersOfCratesWhoseContentsWereSold()
{
	suggestedReferenceNumbersOfCratesWhoseContentsWereSold.clear();
}
