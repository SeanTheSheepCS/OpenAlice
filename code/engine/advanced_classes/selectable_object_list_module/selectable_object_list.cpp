#include "selectable_object_list.h"

SelectableObjectList::SelectableObjectList(int x, int y, unsigned int width, unsigned int height, unsigned int objectsPerPage):
    DrawableObject(x, y, width, height),
    background(x, y, width, height, nullptr)
{
    this->numberOfSelectableObjectsPerPage = objectsPerPage;
}

void SelectableObjectList::draw(sf::RenderWindow& windowToDrawObjectIn)
{
    background.draw(windowToDrawObjectIn);
}
