#include "credits_screen.h"

CreditsScreen::CreditsScreen(int x, int y, unsigned int width, unsigned int height):
	OAEScreen(x,y,width, height),
	background(x,y,width,height,nullptr),
	exitScreenButton(x+(width*0.9),y,(width*0.1),(height*0.1),nullptr)
{
	closeScreenRequestFlag = false;
}

void CreditsScreen::handleEvent(sf::Event event, sf::RenderWindow& window)
{
	switch(event.type)
	{
		case sf::Event::MouseButtonPressed:
			{
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
				int mouseX = mousePosition.x;
				int mouseY = mousePosition.y;
				if(exitScreenButton.theMouseHasBeenClickedAtTheSpecifiedCoordinatesHasTheButtonBeenClicked(mouseX, mouseY))
				{
					closeScreenRequestFlag = true;
				}
			}
			break;
		default:
			break;
	}
}

void CreditsScreen::forceFullDraw(sf::RenderWindow& windowToDrawIn)
{
	background.draw(windowToDrawIn);
	exitScreenButton.draw(windowToDrawIn);
}

void CreditsScreen::update(sf::Int32 millisecondsElapsedSinceLastUpdate, sf::RenderWindow& window)
{

}

void CreditsScreen::associateWithTexturesInBank(const TextureBank& textureBankToTakeFrom)
{
	background.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CREDITS_SCREEN_BACKGROUND_TEXTURE));
	exitScreenButton.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_WINDOW_X));
}

bool CreditsScreen::hasCloseScreenRequestBeenMade()
{
	return closeScreenRequestFlag;
}

void CreditsScreen::acknowledgeCloseScreenRequest()
{
	closeScreenRequestFlag = false;
}
