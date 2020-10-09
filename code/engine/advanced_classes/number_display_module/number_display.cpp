#include "number_display.h"

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
    this->texturePackPointer = nullptr;
}

void NumberDisplay::draw(sf::RenderWindow& windowToDrawObjectIn)
{
    background.draw(windowToDrawObjectIn);
    for(unsigned int i = 0; i < digitCount; i++)
    {
        digits[i].draw(windowToDrawObjectIn);
    }
}

void NumberDisplay::decoupleNumberDisplayTexturePack()
{
    texturePackPointer = nullptr;
    background.decoupleObjectFromItsTexture();
    for(unsigned int i = 0; i < digitCount; i++)
    {
        digits[i].decoupleObjectFromItsTexture();
    }
}

void NumberDisplay::coupleWithNumberDisplayTexturePack(NumberDisplayTexturePack* texturePackPointerArg)
{
    if(texturePackPointerArg != nullptr)
    {
        texturePackPointer = texturePackPointerArg;
        background.associateWithNewTexture(texturePackPointerArg->getTexturePointerForBackground());
        for(unsigned int i = 0; i < digitCount; i++)
        {
            digits[i].associateWithNewTexture(texturePackPointerArg->getTexturePointerForSpecifiedTexture(getDigitIntegerFormAtIndex(i)));
        }
    }
}
void NumberDisplay::incrementNumberDisplayByAmount(unsigned int amount)
{
    digitAsInteger = digitAsInteger + amount;
    try
    {
        if(texturePackPointer != nullptr)
        {
            for(unsigned int i = 0; i < digitCount; i++)
            {
                digits[i].associateWithNewTexture(texturePackPointer->getTexturePointerForSpecifiedTexture(getDigitIntegerFormAtIndex(i)));
            }
        }
    }
    catch(std::exception& e)
    {

    }
}

void NumberDisplay::decrementNumberDisplayByAmount(unsigned int amount)
{
    digitAsInteger = digitAsInteger - amount;
    try
    {
        if(texturePackPointer != nullptr)
        {
            for(unsigned int i = 0; i < digitCount; i++)
            {
                digits[i].associateWithNewTexture(texturePackPointer->getTexturePointerForSpecifiedTexture(getDigitIntegerFormAtIndex(i)));
            }
        }
    }
    catch(std::exception& e)
    {

    }
}

void NumberDisplay::setNumberDisplayAmount(unsigned int amount)
{
    digitAsInteger = amount;
    try
    {
        if(texturePackPointer != nullptr)
        {
            for(unsigned int i = 0; i < digitCount; i++)
            {
                digits[i].associateWithNewTexture(texturePackPointer->getTexturePointerForSpecifiedTexture(getDigitIntegerFormAtIndex(i)));
            }
        }
    }
    catch(std::exception& e)
    {

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
