#ifndef TEXTURED_OBJECT
#define TEXTURED_OBJECT

class TexturedObject: public DrawableObject
{
    public:
	TexturedObject(int x, int y, int width, int height, sf::Texture* texturePointerArg);
	//Makes the texture this object is associated to null, this is important in case the texture ever leaves the scope.
	void decoupleObjectFromItsTexture();
	void associateWithNewTexture(sf::Texture* newTextureToAssociateWith);
	void draw();
    protected:
	//
    private:
	sf::Texture texturePointer;
};

#endif
