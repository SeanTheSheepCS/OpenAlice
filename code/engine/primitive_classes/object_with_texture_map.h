#ifndef OBJECT_WITH_TEXTURE_MAP_H
#define OBJECT_WITH_TEXTURE_MAP_H

#include <SFML/Graphics.hpp>
#include <map>

class ObjectWithTextureMap
{
    public:
        ObjectWithTextureMap();

        void associateReferenceNumberWithTexturePointer(int referenceNumber, const sf::Texture* texturePointer);
        void deassociateTexturePointerWithSpecifiedReferenceNumber(int referenceNumber);

        void setCurrentTextureReferenceNumber(int newReferenceNumber);
        const sf::Texture* getCurrentTexture() const;
    protected:
        const sf::Texture* getTextureWithSpecificReferenceNumber(int referenceNumber) const;
    private:
        int currentTextureReferenceNumber;
        std::map<int, const sf::Texture*> refNumberToTexturePointerMap;
};

#endif
