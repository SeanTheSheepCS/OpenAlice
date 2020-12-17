#ifndef CARTESIAN_OBJECT_H
#define CARTESIAN_OBJECT_H

#include <vector>
#include "../utilities/utilities.h"

class CartesianObject
{
	public:
		CartesianObject(int x, int y, unsigned int width, unsigned int height);

		std::vector<unsigned char> toWriteableForm() const;
		void fillWithDataFromWriteableForm(std::vector<unsigned char>::iterator& writeableFormIterator);

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

	protected:
		int x;
		int y;
		unsigned int width;
		unsigned int height;
	private:
		//
};

#endif
