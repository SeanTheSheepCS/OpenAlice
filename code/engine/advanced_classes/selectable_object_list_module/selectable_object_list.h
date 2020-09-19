#ifndef SELECTABLE_OBJECT_LIST_H
#define SELECTABLE_OBJECT_LIST_H

#include "../../primitive_classes/drawable_object.h"
#include "../../primitive_classes/textured_object.h"
#include "selectable_object.h"
#include <vector>

class SelectableObjectList: public DrawableObject
{
    public:
        SelectableObjectList(int x, int y, unsigned int width, unsigned int height, unsigned int objectsPerPage);
        void draw(sf::RenderWindow& windowToDrawObjectIn);
    protected:
        //
    private:
        std::vector<SelectableObject> selectableObjectList;
        unsigned int numberOfSelectableObjectsPerPage;
        TexturedObject background;
};

#endif
