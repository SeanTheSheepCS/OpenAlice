#ifndef MAIN_MENU_SCREEN_H
#define MAIN_MENU_SCREEN_H

#include <SFML/Graphics.hpp>
#include "oae_screen.h"
#include "../engine/primitive_classes/textured_object.h"
#include "../engine/primitive_classes/textured_button_object.h"
#include "subscreens/start_game_screen.h"
#include "subscreens/credits_screen.h"
#include "subscreens/language_screen.h"

enum MainMenuScreenSubscreenState
{
	NO_SUBSCREEN_ACTIVE = 0,
	START_GAME_SUBSCREEN_ACTIVE = 1,
	CREDITS_SUBSCREEN_ACTIVE = 2,
	LANGUAGE_SUBSCREEN_ACTIVE = 3
};

class MainMenuScreen: public OAEScreen
{
	public:
		MainMenuScreen(int x, int y, unsigned int width, unsigned int height);
		void handleEvent(sf::Event event, sf::RenderWindow& window);
		void forceFullDraw(sf::RenderWindow& windowToDrawIn);
		void update(sf::Int32 millisecondsElapsedSinceLastUpdate, sf::RenderWindow& window);

		void associateWithTexturesInBank(const TextureBank& textureBankToTakeFrom);

		//Function to signal when savegame should be loaded.
		int returnSavegameThatShouldBeLoadedReturnsZeroIfNoSavegameIsChosenYet();
		void acknowledgeSavegameChoice();

		bool returnShouldLoadFlag();
		void acknowledgeShouldLoadFlag();

		bool returnShouldDeleteFlag();
		void acknowledgeShouldDeleteFlag();

	protected:
		//
	private:
		//Base title screen components
		TexturedObject backgroundWithTitle;
		TexturedButtonObject startGameButton;
		TexturedButtonObject creditsButton;
		TexturedButtonObject exitGameButton;
		TexturedButtonObject languageButton;

		//For signals when savegame is loaded or deleted.
		int savegameToLoadSetToZeroWhenNoSavegameHasBeenChosen;
		bool shouldLoadFlag;
		bool shouldDeleteFlag;

		//For subscreens
		MainMenuScreenSubscreenState subscreenState;
		StartGameScreen startGameScreenVar;
		CreditsScreen creditsScreenVar;
		LanguageScreen languageScreenVar;
};

#endif
