#ifndef SELECTABLE_OBJECT_H
#define SELECTABLE_OBJECT_H

#include "../../primitive_classes/drawable_object.h"
#include "../../primitive_classes/textured_object.h"
#include "../../primitive_classes/textured_button_object.h"

class SelectableObject: public DrawableObject
{
    public:
        SelectableObject(int x, int y, unsigned int width, unsigned int height);
        void draw(sf::RenderWindow& windowToDrawObjectIn);
    protected:
        //
    private:
        TexturedObject background;
        TexturedObject text;
        TexturedButtonObject selectButton;
};

#endif
