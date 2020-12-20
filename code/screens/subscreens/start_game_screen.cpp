#include "start_game_screen.h"

StartGameScreen::StartGameScreen(int x, int y, unsigned int width, unsigned int height):
	OAEScreen(x,y,width,height),
	background(x,y,width,height,nullptr),
	exitScreenButton(x+(width*0.9),y,(width*0.1),(height*0.1),nullptr),
	selectFileOneButton(x+(width*0.1),y+(height*0.125),(width*0.8),(height*0.25),nullptr),
	deleteFileOneButton(x+(width*0.75),y+(height*0.2),(width*0.1),(height*0.1),nullptr),
	selectFileTwoButton(x+(width*0.1),y+(height*0.375),(width*0.8),(height*0.25),nullptr),
	deleteFileTwoButton(x+(width*0.75),y+(height*0.45),(width*0.1),(height*0.1),nullptr),
	selectFileThreeButton(x+(width*0.1),y+(height*0.625),(width*0.8),(height*0.25),nullptr),
	deleteFileThreeButton(x+(width*0.75),y+(height*0.7),(width*0.1),(height*0.1),nullptr),
	confirmationScreenVar(x+(width*0.20),y+(height*0.4),(width*0.6),(height*0.2))
{
	this->subscreenState = START_GAME_SCREEN_SUBSCREEN_STATE_NO_SUBSCREEN_ACTIVE;
	this->closeScreenRequestFlag = false;
	this->shouldLoadFlag = false;
	this->shouldDeleteFlag = false;
	this->chosenSavegameIsZeroIfNoSavegameHasBeenChosen = 0;
}

void StartGameScreen::handleEvent(sf::Event event, sf::RenderWindow& window)
{
	switch(this->subscreenState)
	{
		case START_GAME_SCREEN_SUBSCREEN_STATE_NO_SUBSCREEN_ACTIVE:
			switch(event.type)
			{
				case sf::Event::MouseButtonPressed:
					{
						sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
						int mouseX = mousePosition.x;
						int mouseY = mousePosition.y;
						if(deleteFileOneButton.theMouseHasBeenClickedAtTheSpecifiedCoordinatesHasTheButtonBeenClicked(mouseX, mouseY))
						{
							this->subscreenState = START_GAME_SCREEN_SUBSCREEN_STATE_CONFIRMATION_SCREEN_SUBSCREEN_ACTIVE;
							chosenSavegameIsZeroIfNoSavegameHasBeenChosen = 1;
							this->forceFullDraw(window);
						}
						else if(deleteFileTwoButton.theMouseHasBeenClickedAtTheSpecifiedCoordinatesHasTheButtonBeenClicked(mouseX, mouseY))
						{
							this->subscreenState = START_GAME_SCREEN_SUBSCREEN_STATE_CONFIRMATION_SCREEN_SUBSCREEN_ACTIVE;
							chosenSavegameIsZeroIfNoSavegameHasBeenChosen = 2;
							this->forceFullDraw(window);
						}
						else if(deleteFileThreeButton.theMouseHasBeenClickedAtTheSpecifiedCoordinatesHasTheButtonBeenClicked(mouseX, mouseY))
						{
							this->subscreenState = START_GAME_SCREEN_SUBSCREEN_STATE_CONFIRMATION_SCREEN_SUBSCREEN_ACTIVE;
							chosenSavegameIsZeroIfNoSavegameHasBeenChosen = 3;
							this->forceFullDraw(window);
						}
						else if(selectFileOneButton.theMouseHasBeenClickedAtTheSpecifiedCoordinatesHasTheButtonBeenClicked(mouseX, mouseY))
						{
							chosenSavegameIsZeroIfNoSavegameHasBeenChosen = 1;
							shouldLoadFlag = true;
						}
						else if(selectFileTwoButton.theMouseHasBeenClickedAtTheSpecifiedCoordinatesHasTheButtonBeenClicked(mouseX, mouseY))
						{
							chosenSavegameIsZeroIfNoSavegameHasBeenChosen = 2;
							shouldLoadFlag = true;
						}
						else if(selectFileThreeButton.theMouseHasBeenClickedAtTheSpecifiedCoordinatesHasTheButtonBeenClicked(mouseX, mouseY))
						{
							chosenSavegameIsZeroIfNoSavegameHasBeenChosen = 3;
							shouldLoadFlag = true;
						}
						else if(exitScreenButton.theMouseHasBeenClickedAtTheSpecifiedCoordinatesHasTheButtonBeenClicked(mouseX, mouseY))
						{
							closeScreenRequestFlag = true;
						}
					}
					break;
				default:
					break;
			}
		case START_GAME_SCREEN_SUBSCREEN_STATE_CONFIRMATION_SCREEN_SUBSCREEN_ACTIVE:
			confirmationScreenVar.handleEvent(event, window);
			if(confirmationScreenVar.hasYesChoiceBeenMade())
			{
				this->subscreenState = START_GAME_SCREEN_SUBSCREEN_STATE_NO_SUBSCREEN_ACTIVE;
				this->forceFullDraw(window);
				this->shouldDeleteFlag = true;
				confirmationScreenVar.acknowledgeYesChoice();
			}
			if(confirmationScreenVar.hasNoChoiceBeenMade())
			{
				this->subscreenState = START_GAME_SCREEN_SUBSCREEN_STATE_NO_SUBSCREEN_ACTIVE;
				this->forceFullDraw(window);
				this->chosenSavegameIsZeroIfNoSavegameHasBeenChosen = 0;
				confirmationScreenVar.acknowledgeNoChoice();
			}
			break;
	}
}

void StartGameScreen::forceFullDraw(sf::RenderWindow& windowToDrawIn)
{
	background.draw(windowToDrawIn);
	exitScreenButton.draw(windowToDrawIn);
	selectFileOneButton.draw(windowToDrawIn);
	deleteFileOneButton.draw(windowToDrawIn);
	selectFileTwoButton.draw(windowToDrawIn);
	deleteFileTwoButton.draw(windowToDrawIn);
	selectFileThreeButton.draw(windowToDrawIn);
	deleteFileThreeButton.draw(windowToDrawIn);
	switch(subscreenState)
	{
		case START_GAME_SCREEN_SUBSCREEN_STATE_CONFIRMATION_SCREEN_SUBSCREEN_ACTIVE:
			confirmationScreenVar.forceFullDraw(windowToDrawIn);
			break;
		case START_GAME_SCREEN_SUBSCREEN_STATE_NO_SUBSCREEN_ACTIVE:
			break;
	}
}

void StartGameScreen::associateWithTexturesInBank(const TextureBank& textureBankToTakeFrom)
{
	background.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_SELECT_GAME_BACKGROUND));
	exitScreenButton.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_WINDOW_X));
	selectFileOneButton.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_SAVE_GAME_ONE_BACKGROUND_TEXTURE));
	deleteFileOneButton.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_DELETE_SAVE_GAME_ICON_TEXTURE));
	selectFileTwoButton.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_SAVE_GAME_TWO_BACKGROUND_TEXTURE));
	deleteFileTwoButton.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_DELETE_SAVE_GAME_ICON_TEXTURE));
	selectFileThreeButton.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_SAVE_GAME_THREE_BACKGROUND_TEXTURE));
	deleteFileThreeButton.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_DELETE_SAVE_GAME_ICON_TEXTURE));
	confirmationScreenVar.associateWithTexturesInBank(textureBankToTakeFrom);
}

void StartGameScreen::update(sf::Int32 millisecondsElapsedSinceLastUpdate, sf::RenderWindow& window)
{
}

bool StartGameScreen::hasCloseScreenRequestBeenMade()
{
	return closeScreenRequestFlag;
}

void StartGameScreen::acknowledgeCloseScreenRequest()
{
	closeScreenRequestFlag = false;
}

int StartGameScreen::whichSaveGameHasBeenChosenReturnsZeroIfNoSavegameHasBeenChosen()
{
	return chosenSavegameIsZeroIfNoSavegameHasBeenChosen;
}

void StartGameScreen::acknowledgeChosenSavegame()
{
	chosenSavegameIsZeroIfNoSavegameHasBeenChosen = 0;
}

bool StartGameScreen::returnShouldLoadFlag()
{
	return shouldLoadFlag;
}

void StartGameScreen::acknowledgeShouldLoadFlag()
{
	this->shouldLoadFlag = false;
}

bool StartGameScreen::returnShouldDeleteFlag()
{
	return shouldDeleteFlag;
}

void StartGameScreen::acknowledgeShouldDeleteFlag()
{
	this->shouldDeleteFlag = false;
}
