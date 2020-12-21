#ifndef LANGUAGE_SCREEN_H
#define LANGUAGE_SCREEN_H

#include <SFML/Graphics.hpp>
#include "../oae_screen.h"
#include "../../reference_number_enums.h"
#include "../../texture_bank.h"
#include "../../engine/primitive_classes/textured_object.h"
#include "../../engine/primitive_classes/textured_button_object.h"
#include "confirmation_screen.h"

class LanguageScreen: public OAEScreen
{
	public:
		LanguageScreen(int x, int y, unsigned int width, unsigned int height);
		void handleEvent(sf::Event event, sf::RenderWindow& window);
		void forceFullDraw(sf::RenderWindow& windowToDrawIn);
		void update(sf::Int32 millisecondsElapsedSinceLastUpdate, sf::RenderWindow& window);

		//Functions for a start game screen specifically
		bool hasCloseScreenRequestBeenMade();
		void acknowledgeCloseScreenRequest();

		void associateWithTexturesInBank(const TextureBank& textureBankToTakeFrom);

		bool hasADisplayLanguageBeenChosen();
		DisplayLanguage returnChosenDisplayLanguage();
		void acknowledgeChosenDisplayLanguage();
	protected:
		//
	private:
		TexturedObject background;
		TexturedButtonObject xButton;
		TexturedButtonObject englishButton;
		TexturedObject englishIcon;
		TexturedObject englishText;
		TexturedButtonObject frenchButton;
		TexturedObject frenchIcon;
		TexturedObject frenchText;

		bool hasADisplayLanguageBeenChosenFlag;
		DisplayLanguage chosenDisplayLanguage;
		bool hasCloseScreenRequestBeenMadeFlag;
};

#endif
