#ifndef CONFIRMATION_SCREEN_H
#define CONFIRMATION_SCREEN_H

#include <SFML/Graphics.hpp>
#include "../oae_screen.h"
#include "../../reference_number_enums.h"
#include "../../texture_bank.h"
#include "../../engine/primitive_classes/textured_object.h"
#include "../../engine/primitive_classes/textured_button_object.h"

class ConfirmationScreen: public OAEScreen
{
	public:
		ConfirmationScreen(int x, int y, unsigned int width, unsigned int height);
		void handleEvent(sf::Event event, sf::RenderWindow& window);
		void forceFullDraw(sf::RenderWindow& windowToDrawIn);
		void update(sf::Int32 millisecondsElapsedSinceLastUpdate, sf::RenderWindow& window);

		void associateWithTexturesInBank(const TextureBank& textureBankToTakeFrom);

		bool hasYesChoiceBeenMade();
		void acknowledgeYesChoice();

		bool hasNoChoiceBeenMade();
		void acknowledgeNoChoice();
	protected:
		//
	private:
		TexturedObject background;
		TexturedButtonObject yesButton;
		TexturedButtonObject noButton;

		bool yesChoiceFlag;
		bool noChoiceFlag;
};

#endif
