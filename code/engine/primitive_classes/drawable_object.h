#ifndef DRAWABLE_OBJECT_H
#define DRAWABLE_OBJECT_H

#include <SFML/Graphics.hpp>

class DrawableObject
{
	public:
		DrawableObject(int x, int y, unsigned int width, unsigned int height);

		int getX() const;
		int getY() const;
		unsigned int getWidth() const;
		unsigned int getHeight() const;

		int getCentreX() const;
		int getCentreY() const;

		void setX(int newX);
		void setY(int newY);
		void setWidth(unsigned int newWidth);
		void setHeight(unsigned int newHeight);

		virtual void draw(sf::RenderWindow& windowToDrawObjectIn) = 0;
	protected:
		int x;
		int y;
		unsigned int width;
		unsigned int height;
	private:
		//
};

#endif
