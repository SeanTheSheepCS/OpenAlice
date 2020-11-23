#include "market_offer.h"

MarketOffer::MarketOffer():
	MarketOffer(0,0,0,0)
{

}

MarketOffer::MarketOffer(int x, int y, unsigned int width, unsigned int height):
	DrawableObject(x, y, width, height),
	background(x, y, width, height, nullptr),
	commodityOneIcon(x+(width*0.04), y+(height*0.05), width*0.2, height*0.4, nullptr),
	commodityOneCountDisplay(x+(width*0.26), y+(height*0.05), width*0.4, height, 2),
	commodityTwoIcon(x+(width*0.04), y+(height*0.55), width*0.2, height*0.4, nullptr),
	commodityTwoCountDisplay(x+(width*0.26), y+(height*0.55), width*0.4, height, 2),
	selectButton(x+(width*0.7), y+(height*0.3), width*0.25, height*0.4, nullptr)
{

}

void MarketOffer::setXRecursiveWithinComponents(int newX)
{
	this->x = newX;
	background.setX(newX);
	commodityOneIcon.setX(newX+(width*0.04));
	commodityOneCountDisplay.setXRecursiveWithinComponents(newX+(width*0.26));
	commodityTwoIcon.setX(newX+(width*0.04));
	commodityTwoCountDisplay.setXRecursiveWithinComponents(newX+(width*0.26));
	selectButton.setX(newX+(width*0.7));
}

void MarketOffer::setYRecursiveWithinComponents(int newY)
{
	this->y = newY;
	background.setY(newY);
	commodityOneIcon.setY(newY+(height*0.05));
	commodityOneCountDisplay.setYRecursiveWithinComponents(newY+(height*0.05));
	commodityTwoIcon.setY(newY+(height*0.55));
	commodityTwoCountDisplay.setYRecursiveWithinComponents(newY+(height*0.55));
	selectButton.setY(newY+(height*0.3));
}

void MarketOffer::setWidthRecursiveWithinComponents(unsigned int newWidth)
{
	this->width = newWidth;
	background.setWidth(newWidth);
	commodityOneIcon.setWidth(newWidth*0.2);
	commodityOneCountDisplay.setWidthRecursiveWithinComponents(newWidth*0.4);
	commodityTwoIcon.setWidth(newWidth*0.2);
	commodityTwoCountDisplay.setWidthRecursiveWithinComponents(newWidth*0.4);
	selectButton.setWidth(newWidth*0.25);

	//background.setX(x);
	commodityOneIcon.setX(x+(width*0.04));
	commodityOneCountDisplay.setXRecursiveWithinComponents(x+(width*0.26));
	commodityTwoIcon.setX(x+(width*0.04));
	commodityTwoCountDisplay.setXRecursiveWithinComponents(x+(width*0.26));
	selectButton.setX(x+(width*0.7));
}

void MarketOffer::setHeightRecursiveWithinComponents(unsigned int newHeight)
{
	this->height = newHeight;
	background.setHeight(newHeight);
	commodityOneIcon.setHeight(newHeight*0.4);
	commodityOneCountDisplay.setHeightRecursiveWithinComponents(newHeight*0.4);
	commodityTwoIcon.setHeight(newHeight*0.4);
	commodityTwoCountDisplay.setHeightRecursiveWithinComponents(newHeight*0.4);
	selectButton.setHeight(newHeight*0.4);

	//background.setY(y);
	commodityOneIcon.setY(y+(height*0.05));
	commodityOneCountDisplay.setYRecursiveWithinComponents(y+(height*0.05));
	commodityTwoIcon.setY(y+(height*0.55));
	commodityTwoCountDisplay.setYRecursiveWithinComponents(y+(height*0.55));
	selectButton.setY(y+(height*0.3));
}

bool MarketOffer::isInvalid()
{
	if((this->height == 0) || (this->width == 0))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void MarketOffer::associateWithTexturesInBank(const TextureBank& textureBankToTakeFrom)
{
	background.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_MARKET_OFFER_BACKGROUND));
	commodityOneCountDisplay.associateWithTexturesInBank(textureBankToTakeFrom);
	commodityTwoCountDisplay.associateWithTexturesInBank(textureBankToTakeFrom);
	selectButton.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CHECK_ICON));
}

bool MarketOffer::isSelectButtonPressedBasedOnMouseXAndMouseY(int mouseX, int mouseY)
{
	return selectButton.theMouseHasBeenClickedAtTheSpecifiedCoordinatesHasTheButtonBeenClicked(mouseX, mouseY);
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
