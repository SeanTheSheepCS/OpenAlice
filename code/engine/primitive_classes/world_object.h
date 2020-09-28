#ifndef WORLD_OBJECT_H
#define WORLD_OBJECT_H

#include <SFML/Graphics.hpp>
#include "textured_object.h"

class WorldObject: public TexturedObject
{
    public:
        WorldObject(int x, int y, unsigned int width, unsigned int height, sf::Texture* texture);
	WorldObject(TexturedObject parentObject);

	void setX(int newX);
	void setY(int newY);
	int getX();
	int getY();

	void setWidth(unsigned int newWidth);
	void setHeight(unsigned int newHeight);
	unsigned int getWidth();
	unsigned int getHeight();

	void attachTriggerZone(TriggerZone zoneToAttach);
	void detachTriggerZone();
	bool isDrawableObjectWithinTriggerZone(DrawableObject objectToCheck);

	void setVisible(bool visibility);
	bool getVisibility();

    protected:
        //
    private:
	bool visibility;

	TriggerZone triggerZoneForObject;
};

#endif
