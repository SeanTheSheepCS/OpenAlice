#ifndef TRIGGER_ZONE_H
#define TRIGGER_ZONE_H

class TriggerZone
{
    public:
        TriggerZone(int x, int y, int width, int height);

	void setX(int newX);
	int getX();
	void setY(int newY);
	int getY();
	void setWidth(int newWidth);
	unsigned int getWidth();
	void setHeight(int newHeight);
	unsigned int getHeight();

	void setActive(bool activeStatus);
	bool isActive();

	bool isIntersecting(DrawableObject objectToCompareWith);
    protected:
        //
    private:
	int x;
	int y;
	unsigned int width;
	unsigned int height;

        bool activeStatus;
}

#endif
