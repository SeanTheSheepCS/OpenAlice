#include "trigger_zone.h"

TriggerZone::TriggerZone(int xArg, int yArg, int widthArg, int heightArg, bool activeStatusArg):
	CartesianObject(xArg, yArg, widthArg, heightArg)
{
	this->activeStatus = activeStatusArg;
}

std::vector<unsigned char> TriggerZone::toWriteableForm() const
{
	std::vector<unsigned char> returnValue;

	std::vector<unsigned char> cartesianObjectToWrite = CartesianObject::toWriteableForm();
	returnValue.insert(returnValue.end(), cartesianObjectToWrite.begin(), cartesianObjectToWrite.end());

	unsigned char activeStatusChar = 0x01;
	if(activeStatus == false)
	{
		activeStatusChar = 0;
	}
	returnValue.push_back(activeStatusChar);

	return returnValue;
}

void TriggerZone::fillWithDataFromWriteableForm(std::istream_iterator<unsigned char>& writeableFormIterator)
{
	CartesianObject::fillWithDataFromWriteableForm(writeableFormIterator);
	
	unsigned char activeStatusChar = (*writeableFormIterator);
	writeableFormIterator++;
	if(activeStatusChar == 0)
	{
		this->activeStatus = false;
	}
	else
	{
		this->activeStatus = true;
	}
}

void TriggerZone::setActive(bool activeStatusArg)
{
	this->activeStatus = activeStatusArg;
}

bool TriggerZone::isActive() const
{
	return activeStatus;
}

bool TriggerZone::isIntersecting(const CartesianObject& objectToCompareWith) const
{
	if(((this->x)+((int)this->width)) <= objectToCompareWith.getX())
	{
		return false;
	}
	else if((this->x) >= (objectToCompareWith.getX()+((int)objectToCompareWith.getWidth())))
	{
		return false;
	}
	else if(((this->y)+((int)this->height)) <= objectToCompareWith.getY())
	{
		return false;
	}
	else if((this->y) >= (objectToCompareWith.getY()+((int)objectToCompareWith.getHeight())))
	{
		return false;
	}
	else
	{
		return true;
	}
}
