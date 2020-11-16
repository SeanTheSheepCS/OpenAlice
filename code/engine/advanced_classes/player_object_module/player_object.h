#ifndef PLAYER_OBJECT_H
#define PLAYER_OBJECT_H

#include "../../primitive_classes/textured_object.h"
#include "../../primitive_classes/oae_animated_object.h"
#include "../../primitive_classes/object_with_texture_map.h"
#include <exception>
#include <map>

class PlayerObject: public DrawableObject, public OAEAnimatedObject, public ObjectWithTextureMap
{
	public:
		PlayerObject(int x, int y, unsigned int width, unsigned int height);
		void setXMovementAmount(float newXMovementAmount);
		void setYMovementAmount(float newYMovementAmount);
		void changeXMovementAmountByAmount(float amountToChangeXMovementAmountBy);
		void changeYMovementAmountByAmount(float amountToChangeYMovementAmountBy);

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
};

#endif
