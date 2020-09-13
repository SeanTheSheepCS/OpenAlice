#ifndef NUMBER_DISPLAY_TEXTURE_PACK
#define NUMBER_DISPLAY_TEXTURE_PACK

#include <SFML/Graphics.hpp>

class NumberDisplayTexturePack
{
    public:
        NumberDisplayTexturePack();

	    void decoupleBackgroundTexture();
	    void coupleWithBackgroundTexture(sf::Texture* backgroundTexture);

        void decoupleNumberTextureArray();
        void coupleWithNumberTextureArray(sf::Texture** numberTextureArray);

        sf::Texture* getTexturePointerForBackground();
        sf::Texture* getTexturePointerForSpecifiedTexture(int number);
    protected:
        //
    private:
        sf::Texture* numberDisplayBackgroundTexturePointer;
        sf::Texture** arrayOfTexturePointersEachIndexStoresAPointerToTheNumberTheTextureRepresents;
};

#endif
