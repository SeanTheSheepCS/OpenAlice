#ifndef TEXTURED_OBJECT
#define TEXTURED_OBJECT

#include <SFML/Graphics.hpp>
#include "drawable_object.h"

class TexturedObject: public DrawableObject
{
    public:
	    TexturedObject(int x, int y, unsigned int width, unsigned int height, sf::Texture* texturePointerArg);
	    //Makes the texture this object is associated to null, this is important in case the texture ever leaves the scope.
	    void decoupleObjectFromItsTexture();
	    void associateWithNewTexture(sf::Texture* newTextureToAssociateWith);
        void draw(sf::RenderWindow& windowToDrawObjectIn);
    protected:
	    //
    private:
        static bool isDefaultTextureInitialized;
        static sf::Texture defaultTexture;
	    sf::Texture* texturePointer;
};


#endif
