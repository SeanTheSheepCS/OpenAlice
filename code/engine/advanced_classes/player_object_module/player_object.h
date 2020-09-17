#ifndef PLAYER_OBJECT_H
#define PLAYER_OBJECT_H

#include "../../primitive_classes/textured_object.h"

class PlayerObject: public TexturedObject
{
    public:
        PlayerObject(int x, int y, unsigned int width, unsigned int height, const sf::Texture* texture);
        void setXMovementAmount(float newXMovementAmount);
        void setYMovementAmount(float newYMovementAmount);
        float getXMovementAmount();
        float getYMovementAmount();
    protected:
        //
    private:
        float xMovementAmount;
        float yMovementAmount;
};

#endif
