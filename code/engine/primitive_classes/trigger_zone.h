#ifndef TRIGGER_ZONE_H
#define TRIGGER_ZONE_H

#include "drawable_object.h"

class TriggerZone
{
    public:
        TriggerZone(int x, int y, int width, int height, bool activeStatus);

	    void setX(int newX);
	    int getX() const;
	    void setY(int newY);
	    int getY() const;
	    void setWidth(int newWidth);
	    unsigned int getWidth() const;
	    void setHeight(int newHeight);
	    unsigned int getHeight() const;

	    void setActive(bool activeStatus);
	    bool isActive() const;

        bool isIntersecting(const DrawableObject& objectToCompareWith) const;

    protected:
        //
    private:
	    int x;
	    int y;
	    unsigned int width;
	    unsigned int height;

        bool activeStatus;
};

#endif
