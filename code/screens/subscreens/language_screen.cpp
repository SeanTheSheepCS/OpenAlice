#include "language_screen.h"

LanguageScreen::LanguageScreen(int x, int y, unsigned int width, unsigned int height):
	OAEScreen(x,y,width,height),
	background(x,y,width,height,nullptr),
	xButton(x+(width*0.85),y+(height*0.05),width*0.1,height*0.1,nullptr),
	englishIcon(x+(width*0.1),y+(height*0.25),width*0.2,height*0.2,nullptr),
	englishText(x+(width*0.3),y+(height*0.275),width*0.5,height*0.15,nullptr),
	englishButton(x+(width*0.8125),y+(height*0.30),width*0.1,height*0.1,nullptr),
	frenchIcon(x+(width*0.1),y+(height*0.55),width*0.2,height*0.2,nullptr),
	frenchText(x+(width*0.3),y+(height*0.575),width*0.5,height*0.15,nullptr),
	frenchButton(x+(width*0.8125),y+(height*0.6),width*0.1,height*0.1,nullptr)
{
	this->hasCloseScreenRequestBeenMadeFlag = false;
	this->hasADisplayLanguageBeenChosenFlag = false;
	chosenDisplayLanguage = DISPLAY_LANGUAGE_ENGLISH; //This initial value does not matter, we should not access it unless hasADisplayLanguageBeenChosenFlag is true.
}

void LanguageScreen::handleEvent(sf::Event event, sf::RenderWindow& window)
{
	switch(event.type)
	{
		case sf::Event::MouseButtonPressed:
			{
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
				int mouseX = mousePosition.x;
				int mouseY = mousePosition.y;
				if(xButton.theMouseHasBeenClickedAtTheSpecifiedCoordinatesHasTheButtonBeenClicked(mouseX, mouseY))
				{
					this->hasCloseScreenRequestBeenMadeFlag = true;
				}
				if(englishButton.theMouseHasBeenClickedAtTheSpecifiedCoordinatesHasTheButtonBeenClicked(mouseX, mouseY))
				{
					//Don't change the order of these, if the screens are multithreaded race conditions might happen if you do.
					this->chosenDisplayLanguage = DISPLAY_LANGUAGE_ENGLISH;
					this->hasADisplayLanguageBeenChosenFlag = true;
				}
				if(frenchButton.theMouseHasBeenClickedAtTheSpecifiedCoordinatesHasTheButtonBeenClicked(mouseX, mouseY))
				{
					//Don't change the order of these, if the screens are multithreaded race conditions might happen if you do.
					this->chosenDisplayLanguage = DISPLAY_LANGUAGE_FRENCH;
					this->hasADisplayLanguageBeenChosenFlag = true;
				}
			}
			break;
		default:
			break;
	}
}

void LanguageScreen::forceFullDraw(sf::RenderWindow& windowToDrawIn)
{
	background.draw(windowToDrawIn);
	xButton.draw(windowToDrawIn);
	englishText.draw(windowToDrawIn);
	englishIcon.draw(windowToDrawIn);
	englishButton.draw(windowToDrawIn);
	frenchText.draw(windowToDrawIn);
	frenchIcon.draw(windowToDrawIn);
	frenchButton.draw(windowToDrawIn);
}

void LanguageScreen::update(sf::Int32 millisecondsElapsedSinceLastUpdate, sf::RenderWindow& window)
{
	//
}

bool LanguageScreen::hasCloseScreenRequestBeenMade()
{
	return hasCloseScreenRequestBeenMadeFlag;
}

void LanguageScreen::acknowledgeCloseScreenRequest()
{
	this->hasCloseScreenRequestBeenMadeFlag = false;
}

void LanguageScreen::associateWithTexturesInBank(const TextureBank& textureBankToTakeFrom)
{
	background.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_LANGUAGE_SCREEN_BACKGROUND_TEXTURE));
	xButton.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_WINDOW_X));
	englishText.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ENGLISH_TEXT_TEXTURE));
	englishIcon.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_ENGLISH_ICON_TEXTURE));
	englishButton.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CHECK_ICON));
	frenchText.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_FRENCH_TEXT_TEXTURE));
	frenchIcon.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_FRENCH_ICON_TEXTURE));
	frenchButton.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_CHECK_ICON));
}

bool LanguageScreen::hasADisplayLanguageBeenChosen()
{
	return hasADisplayLanguageBeenChosenFlag;
}

DisplayLanguage LanguageScreen::returnChosenDisplayLanguage()
{
	return chosenDisplayLanguage;
}

void LanguageScreen::acknowledgeChosenDisplayLanguage()
{
	this->hasADisplayLanguageBeenChosenFlag = false;
}
