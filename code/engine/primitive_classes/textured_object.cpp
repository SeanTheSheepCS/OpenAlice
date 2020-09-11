#include "textured_object.h"

TexturedObject::TexturedObject(int xArg, int yArg, int widthArg, int heightArg, sf::Texture* texturePointerArg): DrawableObject(xArg,yArg,widthArg,heightArg)
{
    this->texturePointer = texturePointerArg;
}

TexturedObject::draw()
{
    //
}
