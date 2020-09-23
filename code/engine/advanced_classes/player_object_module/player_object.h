#ifndef PLAYER_OBJECT_H
#define PLAYER_OBJECT_H

#include "../../primitive_classes/textured_object.h"
#include "../../primitive_classes/oae_animation.h"
#include <exception>
#include <map>

class PlayerObject: public TexturedObject
{
    public:
        PlayerObject(int x, int y, unsigned int width, unsigned int height, const sf::Texture* texture);
        void setXMovementAmount(float newXMovementAmount);
        void setYMovementAmount(float newYMovementAmount);
        void changeXMovementAmountByAmount(float amountToChangeXMovementAmountBy);
        void changeYMovementAmountByAmount(float amountToChangeYMovementAmountBy);

        void associateReferenceNumberWithAnimation(int referenceNumber, OAEAnimation animation);
        void deassociateAnimationWithSpecificReferenceNumber(int referenceNumber);

        void setCurrentAnimationReferenceNumber(int currentAnimationReferenceNumber);

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

        int currentAnimationReferenceNumber;

        std::map<int, OAEAnimation> referenceNumberToAnimationMap;
};

#endif
