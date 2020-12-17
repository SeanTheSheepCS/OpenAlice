#ifndef DRAWABLE_OBJECT_H
#define DRAWABLE_OBJECT_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "cartesian_object.h"

class DrawableObject: public CartesianObject
{
	public:
		DrawableObject(int x, int y, unsigned int width, unsigned int height);

		std::vector<unsigned char> toWriteableForm() const;
		void fillWithDataFromWriteableForm(std::vector<unsigned char>::iterator& writeableFormIterator);

		virtual void draw(sf::RenderWindow& windowToDrawObjectIn) = 0;
	protected:
		//
	private:
		//
};

#endif
