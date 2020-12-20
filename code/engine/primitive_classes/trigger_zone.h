#ifndef TRIGGER_ZONE_H
#define TRIGGER_ZONE_H

#include "cartesian_object.h"
#include <vector>

class TriggerZone: public CartesianObject
{
	public:
		TriggerZone(int x, int y, int width, int height, bool activeStatus);

		std::vector<unsigned char> toWriteableForm() const;
		void fillWithDataFromWriteableForm(std::istream_iterator<unsigned char>& writeableFormIterator);

		void setActive(bool activeStatus);
		bool isActive() const;

		bool isIntersecting(const CartesianObject& objectToCompareWith) const;

	protected:
		bool activeStatus;
	private:
		//
};

#endif
