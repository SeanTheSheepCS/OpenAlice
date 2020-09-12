#include "textured_button_object.h"

TexturedButtonObject::TexturedButtonObject(int x, int y, int width, int height, sf::Texture* texture): TexturedObject(x, y, width, height, texture)
{

}

bool TexturedButtonObject::theMouseHasBeenClickedAtTheSpecifiedCoordinatesHasTheButtonBeenClicked(int mouseX, int mouseY)
{
    if((mouseX >= x) && (mouseX <= (x+width)) && (mouseY >= y) && (mouseY <= (y+height)))
    {
        return true;
    }
    else
    {
        return false;
    }
}
