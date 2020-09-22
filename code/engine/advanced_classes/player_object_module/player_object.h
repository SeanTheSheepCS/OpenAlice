#ifndef PLAYER_OBJECT_H
#define PLAYER_OBJECT_H

#include "../../primitive_classes/textured_object.h"

class PlayerObject: public TexturedObject
{
    public:
        PlayerObject(int x, int y, unsigned int width, unsigned int height, const sf::Texture* texture);
        void setXMovementAmount(float newXMovementAmount);
        void setYMovementAmount(float newYMovementAmount);
        void changeXMovementAmountByAmount(float amountToChangeXMovementAmountBy);
        void changeYMovementAmountByAmount(float amountToChangeYMovementAmountBy);

	    void associateReferenceNumberWithTexture(int referenceNumber, const sf::Texture* texture);
        void deassociateTextureWithSpecificReferenceNumber(int referenceNumber);

        float getXMovementAmount();
        float getYMovementAmount();

        void draw(sf::RenderWindow& windowToDrawObjectIn, int referenceNumberForTexture);
    protected:
        //
    private:
        float xMovementAmount;
        float yMovementAmount;
        float xMovementCap;
        float yMovementCap;

        std::map<int, const sf::Texture*> referenceNumberToTexturePointerMap;
};

#endif
