#ifndef START_GAME_SCREEN_H
#define START_GAME_SCREEN_H

#include <SFML/Graphics.hpp>
#include "../oae_screen.h"
#include "../../reference_number_enums.h"
#include "../../texture_bank.h"
#include "../../engine/primitive_classes/textured_object.h"
#include "../../engine/primitive_classes/textured_button_object.h"
#include "confirmation_screen.h"

enum StartGameScreenSubscreenState
{
	START_GAME_SCREEN_SUBSCREEN_STATE_NO_SUBSCREEN_ACTIVE = 0,
	START_GAME_SCREEN_SUBSCREEN_STATE_CONFIRMATION_SCREEN_SUBSCREEN_ACTIVE = 1
};

class StartGameScreen: public OAEScreen
{
	public:
		StartGameScreen(int x, int y, unsigned int width, unsigned int height);
		void handleEvent(sf::Event event, sf::RenderWindow& window);
		void forceFullDraw(sf::RenderWindow& windowToDrawIn);
		void update(sf::Int32 millisecondsElapsedSinceLastUpdate, sf::RenderWindow& window);

		//Functions for a start game screen specifically
		bool hasCloseScreenRequestBeenMade();
		void acknowledgeCloseScreenRequest();

		void associateWithTexturesInBank(const TextureBank& textureBankToTakeFrom);

		int whichSaveGameHasBeenChosenReturnsZeroIfNoSavegameHasBeenChosen();
		void acknowledgeChosenSavegame();

		bool returnShouldLoadFlag();
		void acknowledgeShouldLoadFlag();

		bool returnShouldDeleteFlag();
		void acknowledgeShouldDeleteFlag();

	protected:
		//
	private:
		TexturedObject background;
		TexturedButtonObject exitScreenButton;
		TexturedButtonObject selectFileOneButton;
		TexturedButtonObject deleteFileOneButton;
		TexturedButtonObject selectFileTwoButton;
		TexturedButtonObject deleteFileTwoButton;
		TexturedButtonObject selectFileThreeButton;
		TexturedButtonObject deleteFileThreeButton;

		bool shouldLoadFlag;
		bool shouldDeleteFlag;

		bool closeScreenRequestFlag;
		int chosenSavegameIsZeroIfNoSavegameHasBeenChosen;
		
		//FOR SUBSCREENS
		StartGameScreenSubscreenState subscreenState;
		ConfirmationScreen confirmationScreenVar;
};

#endif
