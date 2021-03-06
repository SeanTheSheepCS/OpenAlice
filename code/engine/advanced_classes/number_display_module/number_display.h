#ifndef NUMBER_DISPLAY_H
#define NUMBER_DISPLAY_H

#include <SFML/Graphics.hpp>
#include <math.h>
#include <exception>
#include "../../primitive_classes/drawable_object.h"
#include "../../primitive_classes/textured_object.h"
#include "../../../texture_bank.h"
#include "../../../reference_number_enums.h"
#include "number_display_texture_pack.h"

class NumberDisplay: public DrawableObject
{
	public:
		NumberDisplay(int x, int y, unsigned int width, unsigned int height, unsigned int digitCountArg);

		void associateWithTexturesInBank(const TextureBank& textureBankToTakeFrom);

		void incrementNumberDisplayByAmount(unsigned int amount);
		void decrementNumberDisplayByAmount(unsigned int amount);
		void setNumberDisplayAmount(unsigned int amount);

		unsigned int getNumber() const;

		void setXRecursiveWithinComponents(int newX);
		void setYRecursiveWithinComponents(int newY);
		void setWidthRecursiveWithinComponents(unsigned int newWidth);
		void setHeightRecursiveWithinComponents(unsigned int newHeight);

		void updateDigitTextures();

		void draw(sf::RenderWindow& windowToDrawObjectIn);
	protected:
		//
	private:
		//helper function
		unsigned int getDigitIntegerFormAtIndex(unsigned int index);

		//member variables
		unsigned int digitCount;
		unsigned int digitAsInteger;
		TexturedObject background;
		std::vector<TexturedObject> digits;
		NumberDisplayTexturePackStruct texturePack;
};

#endif
