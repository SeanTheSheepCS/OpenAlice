#ifndef MARKET_OFFER_H
#define MARKET_OFFER_H

#include "../engine/primitive_classes/drawable_object.h"
#include "../engine/primitive_classes/textured_object.h"
#include "../engine/primitive_classes/textured_button_object.h"
#include "../engine/advanced_classes/number_display_module/number_display_module.h"

enum TradeableCommodityEnum
{
	TRADEABLE_COMMODITY_ENUM_NOT_SPECIFIED = 0,
	TRADEABLE_COMMODITY_ENUM_MONEY = 1,
	TRADEABLE_COMMODITY_ENUM_TOMATO_CRATE = 2,
	TRADEABLE_COMMODITY_ENUM_CUCUMBER_CRATE = 3,
	TRADEABLE_COMMODITY_ENUM_CARROT_CRATE = 4,
	TRADEABLE_COMMODITY_ENUM_TOMATO_SEEDS = 5,
	TRADEABLE_COMMODITY_ENUM_CUCUMBER_SEEDS = 6,
	TRADEABLE_COMMODITY_ENUM_CARROT_SEEDS = 7
};

class MarketOffer: public DrawableObject
{
	public:
		MarketOffer();
		MarketOffer(int x, int y, unsigned int width, unsigned int height);

		void setXRecursiveWithinComponents(int newX);
		void setYRecursiveWithinComponents(int newY);
		void setWidthRecursiveWithinComponents(unsigned int newWidth);
		void setHeightRecursiveWithinComponents(unsigned int newHeight);

		void associateWithTexturesInBank(const TextureBank& textureBankToTakeFrom);

		bool isSelectButtonPressedBasedOnMouseXAndMouseY(int mouseX, int mouseY);

		bool isInvalid();

		void setCommodityToBeTraded(TradeableCommodityEnum newCommodityToBeTraded, unsigned int newAmountToBeTraded);
		void setCommodityToBeTradedFor(TradeableCommodityEnum newCommodityToBeTradedFor, unsigned int newAmountToBeTradedFor);

		TradeableCommodityEnum getCommodityToBeTraded();
		unsigned int getAmountTraded();
		TradeableCommodityEnum getCommodityToBeTradedFor();
		unsigned int getAmountTradedFor();

		void draw(sf::RenderWindow& windowToDrawObjectIn);
	protected:
		//
	private:
		TexturedObject background;
		TexturedObject commodityOneIcon;
		NumberDisplay commodityOneCountDisplay;
		TradeableCommodityEnum commodityToBeTraded;
		TexturedObject commodityTwoIcon;
		NumberDisplay commodityTwoCountDisplay;
		TradeableCommodityEnum commodityToBeTradedFor;
		TexturedButtonObject selectButton;
		const TextureBank* textureBankToTakeTexturesFrom;
};

#endif
