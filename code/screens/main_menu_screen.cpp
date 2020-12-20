#include "main_menu_screen.h"

MainMenuScreen::MainMenuScreen(int x, int y, unsigned int width, unsigned int height): 
	OAEScreen(x, y, width, height),
	backgroundWithTitle(x,y,width,height,nullptr),
	startGameButton(x+(width*0.1),y+(height*0.55), (width*0.8), (height*0.15), nullptr),
	creditsButton(x+(width*0.1),y+(height*0.70), (width*0.8), (height*0.15), nullptr),
	exitGameButton(x+(width*0.1),y+(height*0.85), (width*0.8), (height*0.15), nullptr),
	startGameScreenVar(x+(width*0.1),y+(height*0.1),(width*0.8),(height*0.8)),
	creditsScreenVar(x+(width*0.1),y+(height*0.1),(width*0.8),(height*0.8))
{
	this->subscreenState = NO_SUBSCREEN_ACTIVE;
	this->shouldLoadFlag = false;
	this->shouldDeleteFlag = false;
	this->savegameToLoadSetToZeroWhenNoSavegameHasBeenChosen = 0;
}

void MainMenuScreen::handleEvent(sf::Event event, sf::RenderWindow& window)
{
	switch(subscreenState)
	{
		case NO_SUBSCREEN_ACTIVE:
			switch(event.type)
			{
				case sf::Event::MouseButtonPressed:
					{
						sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
						int mouseX = mousePosition.x;
						int mouseY = mousePosition.y;
						if(startGameButton.theMouseHasBeenClickedAtTheSpecifiedCoordinatesHasTheButtonBeenClicked(mouseX, mouseY))
						{
							subscreenState = START_GAME_SUBSCREEN_ACTIVE;
							startGameScreenVar.forceFullDraw(window);
						}
						else if(creditsButton.theMouseHasBeenClickedAtTheSpecifiedCoordinatesHasTheButtonBeenClicked(mouseX, mouseY))
						{
							subscreenState = CREDITS_SUBSCREEN_ACTIVE;
							creditsScreenVar.forceFullDraw(window);
						}
						else if(exitGameButton.theMouseHasBeenClickedAtTheSpecifiedCoordinatesHasTheButtonBeenClicked(mouseX, mouseY))
						{
							window.close();
						}
					}
					break;
				default:
					break;
			}
			break;
		case START_GAME_SUBSCREEN_ACTIVE:
			startGameScreenVar.handleEvent(event, window);
			if(startGameScreenVar.hasCloseScreenRequestBeenMade())
			{
				startGameScreenVar.acknowledgeCloseScreenRequest();
				subscreenState = NO_SUBSCREEN_ACTIVE;
				forceFullDraw(window);
			}
			else if(startGameScreenVar.whichSaveGameHasBeenChosenReturnsZeroIfNoSavegameHasBeenChosen() != 0)
			{
				savegameToLoadSetToZeroWhenNoSavegameHasBeenChosen = startGameScreenVar.whichSaveGameHasBeenChosenReturnsZeroIfNoSavegameHasBeenChosen();
				if(startGameScreenVar.returnShouldLoadFlag() == true)
				{
					this->shouldLoadFlag = true;
					startGameScreenVar.acknowledgeShouldLoadFlag();
					startGameScreenVar.acknowledgeChosenSavegame();
				}
				if(startGameScreenVar.returnShouldDeleteFlag() == true)
				{
					this->shouldDeleteFlag = true;
					startGameScreenVar.acknowledgeShouldDeleteFlag();
					startGameScreenVar.acknowledgeChosenSavegame();
				}
			}
			break;
		case CREDITS_SUBSCREEN_ACTIVE:
			creditsScreenVar.handleEvent(event, window);
			if(creditsScreenVar.hasCloseScreenRequestBeenMade())
			{
				creditsScreenVar.acknowledgeCloseScreenRequest();
				subscreenState = NO_SUBSCREEN_ACTIVE;
				forceFullDraw(window);
			}
			break;
		default:
			break;
	}
}

void MainMenuScreen::forceFullDraw(sf::RenderWindow& windowToDrawIn)
{
	backgroundWithTitle.draw(windowToDrawIn);
	startGameButton.draw(windowToDrawIn);
	creditsButton.draw(windowToDrawIn);
	exitGameButton.draw(windowToDrawIn);
	switch (subscreenState)
	{
		case START_GAME_SUBSCREEN_ACTIVE:
			startGameScreenVar.forceFullDraw(windowToDrawIn);
			break;
		case CREDITS_SUBSCREEN_ACTIVE:
			creditsScreenVar.forceFullDraw(windowToDrawIn);
			break;
		default:
			break;
	}
}

void MainMenuScreen::associateWithTexturesInBank(const TextureBank& textureBankToTakeFrom)
{
	startGameScreenVar.associateWithTexturesInBank(textureBankToTakeFrom);
	creditsScreenVar.associateWithTexturesInBank(textureBankToTakeFrom);
	backgroundWithTitle.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_BACKGROUND));
	startGameButton.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_SELECT_GAME_BUTTON));
	creditsButton.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_CREDITS_BUTTON));
	exitGameButton.associateWithNewTexture(textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_EXIT_BUTTON));
}

void MainMenuScreen::update(sf::Int32 millisecondsElapsedSinceLastUpdate, sf::RenderWindow& window)
{
	switch(subscreenState)
	{
		case NO_SUBSCREEN_ACTIVE:
			//
			break;
		case START_GAME_SUBSCREEN_ACTIVE:
			startGameScreenVar.update(millisecondsElapsedSinceLastUpdate, window);
			break;
		case CREDITS_SUBSCREEN_ACTIVE:
			creditsScreenVar.update(millisecondsElapsedSinceLastUpdate, window);
			break;
		default:
			break;
	}
}

int MainMenuScreen::returnSavegameThatShouldBeLoadedReturnsZeroIfNoSavegameIsChosenYet()
{
	return savegameToLoadSetToZeroWhenNoSavegameHasBeenChosen;
}

void MainMenuScreen::acknowledgeSavegameChoice()
{
	savegameToLoadSetToZeroWhenNoSavegameHasBeenChosen = 0;    
}

bool MainMenuScreen::returnShouldLoadFlag()
{
	return shouldLoadFlag;
}

void MainMenuScreen::acknowledgeShouldLoadFlag()
{
	this->shouldLoadFlag = false;
}

bool MainMenuScreen::returnShouldDeleteFlag()
{
	return shouldDeleteFlag;
}

void MainMenuScreen::acknowledgeShouldDeleteFlag()
{
	this->shouldDeleteFlag = false;
}
