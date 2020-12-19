#ifndef TEXTURED_AND_ANIMATED_OBJECT_H
#define TEXTURED_AND_ANIMATED_OBJECT_H

#include "oae_animated_object.h"
#include "textured_object.h"
class TexturedAndAnimatedObject: public OAEAnimatedObject, public TexturedObject
{
	public:
		TexturedAndAnimatedObject(int x, int y, unsigned width, unsigned int height);
		void draw(sf::RenderWindow& windowToDrawObjectIn, unsigned int numberOfMillisecondsSinceLastUpdate);
		void draw(sf::RenderWindow& windowToDrawObjectIn);
	protected:
		//
	private:
		//
};
#endif
