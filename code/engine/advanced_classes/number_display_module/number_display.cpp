#include "number_display.h"
#include <math.h>

NumberDisplay::NumberDisplay(int x, int y, unsigned int width, unsigned int height, unsigned int digitCountArg):
	DrawableObject(x, y, width, height),
	background(x, y, width, height, nullptr),
	digits{
		{x,y,width,height,nullptr},
		{x,y,width,height,nullptr},
		{x,y,width,height,nullptr},
		{x,y,width,height,nullptr},
		{x,y,width,height,nullptr},
		{x,y,width,height,nullptr},
		{x,y,width,height,nullptr},
		{x,y,width,height,nullptr},
		{x,y,width,height,nullptr},
		{x,y,width,height,nullptr}
	}
{
	if(digitCountArg > NUMBER_DISPLAY_MAXIMUM_DIGITS_COUNT)
	{
		digitCountArg = NUMBER_DISPLAY_MAXIMUM_DIGITS_COUNT;
	}
	this->digitCount = digitCountArg;

	int incrementAmountX = (width / digitCountArg);
	for(unsigned int i = 0; i < digitCountArg; i++)
	{
		digits[i] = TexturedObject(x+(i*incrementAmountX),y,incrementAmountX,height,nullptr);
	}

	this->digitAsInteger = 0;
	this->texturePack.numberDisplayZeroTexture = nullptr;
	this->texturePack.numberDisplayOneTexture = nullptr;
	this->texturePack.numberDisplayTwoTexture = nullptr;
	this->texturePack.numberDisplayThreeTexture = nullptr;
	this->texturePack.numberDisplayFourTexture = nullptr;
	this->texturePack.numberDisplayFiveTexture = nullptr;
	this->texturePack.numberDisplaySixTexture = nullptr;
	this->texturePack.numberDisplaySevenTexture = nullptr;
	this->texturePack.numberDisplayEightTexture = nullptr;
	this->texturePack.numberDisplayNineTexture = nullptr;
}

void NumberDisplay::associateWithTexturesInBank(const TextureBank& textureBankToTakeFrom)
{
	this->texturePack.numberDisplayZeroTexture = textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_NUMBER_DISPLAY_ZERO_TEXTURE);
	this->texturePack.numberDisplayOneTexture = textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_NUMBER_DISPLAY_ONE_TEXTURE);
	this->texturePack.numberDisplayTwoTexture = textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_NUMBER_DISPLAY_TWO_TEXTURE);
	this->texturePack.numberDisplayThreeTexture = textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_NUMBER_DISPLAY_THREE_TEXTURE);
	this->texturePack.numberDisplayFourTexture = textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_NUMBER_DISPLAY_FOUR_TEXTURE);
	this->texturePack.numberDisplayFiveTexture = textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_NUMBER_DISPLAY_FIVE_TEXTURE);
	this->texturePack.numberDisplaySixTexture = textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_NUMBER_DISPLAY_SIX_TEXTURE);
	this->texturePack.numberDisplaySevenTexture = textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_NUMBER_DISPLAY_SEVEN_TEXTURE);
	this->texturePack.numberDisplayEightTexture = textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_NUMBER_DISPLAY_EIGHT_TEXTURE);
	this->texturePack.numberDisplayNineTexture = textureBankToTakeFrom.getTextureAssociatedWithReferenceNumber(TEXTURE_BANK_REF_NUMBER_NUMBER_DISPLAY_NINE_TEXTURE);
	updateDigitTextures();
}

void NumberDisplay::draw(sf::RenderWindow& windowToDrawObjectIn)
{
	//background.draw(windowToDrawObjectIn);
	for(unsigned int i = 0; i < digitCount; i++)
	{
		digits[i].draw(windowToDrawObjectIn);
	}
}

void NumberDisplay::incrementNumberDisplayByAmount(unsigned int amount)
{
	digitAsInteger = digitAsInteger + amount;
	updateDigitTextures();
}

void NumberDisplay::decrementNumberDisplayByAmount(unsigned int amount)
{
	digitAsInteger = digitAsInteger - amount;
	updateDigitTextures();
}

void NumberDisplay::setNumberDisplayAmount(unsigned int amount)
{
	digitAsInteger = amount;
	updateDigitTextures();
}

void NumberDisplay::updateDigitTextures()
{
	for(unsigned int i = 0; i < digitCount; i++)
	{
		try
		{
			unsigned int digitAsIntegerTemp = (this->digitAsInteger / pow(10, i));
			switch(digitAsIntegerTemp % 10)
			{
				case 0:
					digits[i].associateWithNewTexture(texturePack.numberDisplayZeroTexture);
					break;
				case 1:
					digits[i].associateWithNewTexture(texturePack.numberDisplayOneTexture);
					break;
				case 2:
					digits[i].associateWithNewTexture(texturePack.numberDisplayTwoTexture);
					break;
				case 3:
					digits[i].associateWithNewTexture(texturePack.numberDisplayThreeTexture);
					break;
				case 4:
					digits[i].associateWithNewTexture(texturePack.numberDisplayFourTexture);
					break;
				case 5:
					digits[i].associateWithNewTexture(texturePack.numberDisplayFiveTexture);
					break;
				case 6:
					digits[i].associateWithNewTexture(texturePack.numberDisplaySixTexture);
					break;
				case 7:
					digits[i].associateWithNewTexture(texturePack.numberDisplaySevenTexture);
					break;
				case 8:
					digits[i].associateWithNewTexture(texturePack.numberDisplayEightTexture);
					break;
				case 9:
					digits[i].associateWithNewTexture(texturePack.numberDisplayNineTexture);
					break;
			}
		}
		catch(std::exception& e)
		{
			//
		}
	}
}

void NumberDisplay::setXRecursiveWithinComponents(int newX)
{
	this->x = newX;
	this->background.setX(newX);
	int incrementAmountX = (width / digitCount);
	for(unsigned int i = 0; i < digitCount; i++)
	{
		digits[i] = TexturedObject(newX+(i*incrementAmountX),y,incrementAmountX,height,nullptr);
	}
	this->setNumberDisplayAmount(digitAsInteger);
}

void NumberDisplay::setYRecursiveWithinComponents(int newY)
{
	this->y = newY;
	this->background.setY(newY);
	int incrementAmountX = (width / digitCount);
	for(unsigned int i = 0; i < digitCount; i++)
	{
		digits[i] = TexturedObject(x+(i*incrementAmountX),newY,incrementAmountX,height,nullptr);
	}
	this->setNumberDisplayAmount(digitAsInteger);
}

void NumberDisplay::setWidthRecursiveWithinComponents(unsigned int newWidth)
{
	this->width = newWidth;
	this->background.setWidth(newWidth);
	int incrementAmountX = (newWidth / digitCount);
	for(unsigned int i = 0; i < digitCount; i++)
	{
		digits[i] = TexturedObject(x+(i*incrementAmountX),y,incrementAmountX,height,nullptr);
	}
	this->setNumberDisplayAmount(digitAsInteger);
}

void NumberDisplay::setHeightRecursiveWithinComponents(unsigned int newHeight)
{
	this->height = newHeight;
	this->background.setHeight(newHeight);
	int incrementAmountX = (width / digitCount);
	for(unsigned int i = 0; i < digitCount; i++)
	{
		digits[i] = TexturedObject(x+(i*incrementAmountX),y,incrementAmountX,newHeight,nullptr);
	}
	this->setNumberDisplayAmount(digitAsInteger);
}

/* private */ unsigned int NumberDisplay::getDigitIntegerFormAtIndex(unsigned int index)
{
	unsigned int powerOfTenPlace = digitCount - index;
	return (((unsigned int)(digitAsInteger / pow(10, powerOfTenPlace))) % 10);
}
