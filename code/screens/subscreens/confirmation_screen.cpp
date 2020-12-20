#include "confirmation_screen.h"

ConfirmationScreen::ConfirmationScreen(int x, int y, unsigned int width, unsigned int height):
	OAEScreen(x,y,width, height),
	background(x,y,width,height,nullptr),
	yesButton(x+(width*0.70),y+(height*0.55),(width*0.1),(height*0.4),nullptr),
	noButton(x+(width*0.85),y+(height*0.55),(width*0.1),(height*0.4),nullptr)
{
	this->yesChoiceFlag = false;
	this->noChoiceFlag = false;
}

void ConfirmationScreen::handleEvent(sf::Event event, sf::RenderWindow& window)
{
	switch(event.type)
	{
		case sf::Event::MouseButtonPressed:
			{
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
				int mouseX = mousePosition.x;
				int mouseY = mousePosition.y;
				if(yesButton.theMouseHasBeenClickedAtTheSpecifiedCoordinatesHasTheButtonBeenClicked(mouseX, mouseY))
				{
					this->yesChoiceFlag = true;
				}
				if(noButton.theMouseHasBeenClickedAtTheSpecifiedCoordinatesHasTheButtonBeenClicked(mouseX, mouseY))
				{
					this->noChoiceFlag = true;
				}
			}
			break;
		default:
			break;
	}
}

void ConfirmationScreen::forceFullDraw(sf::RenderWindow& windowToDrawIn)
{
	background.draw(windowToDrawIn);
	yesButton.draw(windowToDrawIn);
	noButton.draw(windowToDrawIn);
}

void ConfirmationScreen::update(sf::Int32 millisecondsElapsedSinceLastUpdate, sf::RenderWindow& window)
{

}

void ConfirmationScreen::associateWithTexturesInBank(const TextureBank& textureBankToTakeFrom)
{
	background.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CONFIRMATION_SCREEN_BACKGROUND));
	noButton.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_WINDOW_X));
	yesButton.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CHECK_ICON));
}

bool ConfirmationScreen::hasYesChoiceBeenMade()
{
	return yesChoiceFlag;
}

void ConfirmationScreen::acknowledgeYesChoice()
{
	this->yesChoiceFlag = false;
}

bool ConfirmationScreen::hasNoChoiceBeenMade()
{
	return noChoiceFlag;
}

void ConfirmationScreen::acknowledgeNoChoice()
{
	this->noChoiceFlag = false;
}
