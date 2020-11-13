#ifndef TEXTURED_OBJECT
#define TEXTURED_OBJECT

#include <SFML/Graphics.hpp>
#include <math.h>
#include "drawable_object.h"

#ifndef PI
#define PI 3.14159265
#endif

class TexturedObject: public DrawableObject
{
	public:
		TexturedObject(int x, int y, unsigned int width, unsigned int height, const sf::Texture* texturePointerArg);
		void decoupleObjectFromItsTexture(); //Makes the texture this object is associated to null, this is important in case the texture ever leaves the scope.
		void associateWithNewTexture(const sf::Texture* newTextureToAssociateWith);
		const sf::Texture* getCurrentTexturePointer() const;
		void rotateAroundCentreThisManyDegrees(float degrees);
		void setRotationAroundCentre(float degrees);
		void addPeriodicRotation(int numberOfMillisecondsToCompleteOneRotation);
		void setDegreeInterval(float degreeIntervalToAdd);
	        void draw(sf::RenderWindow& windowToDrawObjectIn);
		void draw(sf::RenderWindow& windowToDrawObjectIn, unsigned int numberOfMillisecondsSinceLastDraw);
	protected:
		static bool isDefaultTextureInitialized;
		static sf::Texture defaultTexture;
		const sf::Texture* texturePointer;
	private:
	        float rotationFactor;
		float degreeInterval;
		int rotationPeriod;
};


#endif
