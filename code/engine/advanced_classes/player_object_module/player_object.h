#ifndef PLAYER_OBJECT_H
#define PLAYER_OBJECT_H

#include "../../primitive_classes/textured_object.h"
#include "../../primitive_classes/oae_animation.h"
#include "../../primitive_classes/oae_animation_instance.h"
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

        void associateReferenceNumberWithAnimationInstance(int referenceNumber, const OAEAnimationInstance animationInstance);
        void deassociateAnimationInstanceWithSpecificReferenceNumber(int referenceNumber);

        void setCurrentAnimationInstanceReferenceNumber(int currentAnimationInstanceReferenceNumber);

        float getXMovementAmount();
        float getYMovementAmount();

        void updateSprite(unsigned int millisecondsPassedSinceLastDraw);
        void draw(sf::RenderWindow& windowToDrawObjectIn);
        void drawAndUpdateSprite(sf::RenderWindow& windowToDrawObjectIn, unsigned int millisecondsPassedSinceLastDraw);
    protected:
        //
    private:
        float xMovementAmount;
        float yMovementAmount;
        float xMovementCap;
        float yMovementCap;

        int currentAnimationInstanceReferenceNumber;

        std::map<int, OAEAnimationInstance> referenceNumberToAnimationInstanceMap;
};

#endif
