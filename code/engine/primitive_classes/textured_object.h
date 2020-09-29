#ifndef TEXTURED_OBJECT
#define TEXTURED_OBJECT

#include <SFML/Graphics.hpp>
#include "drawable_object.h"

class TexturedObject: public DrawableObject
{
    public:
	TexturedObject(int x, int y, unsigned int width, unsigned int height, const sf::Texture* texturePointerArg);
	void decoupleObjectFromItsTexture(); //Makes the texture this object is associated to null, this is important in case the texture ever leaves the scope.
	void associateWithNewTexture(const sf::Texture* newTextureToAssociateWith);
	const sf::Texture* getCurrentTexturePointer() const;
        virtual void draw(sf::RenderWindow& windowToDrawObjectIn) const;
    protected:
        static bool isDefaultTextureInitialized;
        static sf::Texture defaultTexture;
	const sf::Texture* texturePointer;
    private:
        //
};


#endif
