#ifndef COLLISION_BOX_H
#define COLLISION_BOX_H

#include <fstream>
#include <iterator>
#include "trigger_zone.h"
#include "drawable_object.h"

class CollisionBox: public TriggerZone
{
	public:
		CollisionBox(int x, int y, int width, int height, bool activeStatus);
		std::vector<unsigned char> toWriteableForm() const;
		void fillWithDataFromWriteableForm(std::istream_iterator<unsigned char>& writeableFormIterator);
		void pushDrawableObjectOutsideCollisionBoxIfItIsIntersecting(DrawableObject& objectToPush) const;
	protected:
		//
	private:
		//
};

#endif
