#include "selectable_object.h"

SelectableObject::SelectableObject(int x, int y, unsigned int width, unsigned int height):
    DrawableObject(x, y, width, height),
    background(x, y, width, height, nullptr),
    text(x+(width*0.05), y+(height*0.3), width*0.6, height*0.4, nullptr),
    selectButton(x+(width*0.7), y+(height*0.3), width*0.25, height*0.4, nullptr)
{

}

void SelectableObject::draw(sf::RenderWindow& windowToDrawObjectIn)
{
    background.draw(windowToDrawObjectIn);
    text.draw(windowToDrawObjectIn);
    selectButton.draw(windowToDrawObjectIn);
}
