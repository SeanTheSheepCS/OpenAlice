#ifndef WORLD_OBJECT_H
#define WORLD_OBJECT_H

#include <SFML/Graphics.hpp>
#include "textured_object.h"
#include "trigger_zone.h"

class WorldObject: public TexturedObject
{
    public:
        WorldObject(int x, int y, unsigned int width, unsigned int height, const sf::Texture* texture);
	    WorldObject(TexturedObject parentObject);

	    void setX(int newX);
	    void setY(int newY);

	    void setWidth(unsigned int newWidth);
	    void setHeight(unsigned int newHeight);

	    void attachTriggerZone(TriggerZone zoneToAttach);
	    void detachTriggerZone();
	    bool isDrawableObjectWithinTriggerZone(const DrawableObject& objectToCheck);

	    void setVisibility(bool visibility);
	    bool getVisibility();

        void draw(sf::RenderWindow& windowToDrawObjectIn);
    protected:
        //
    private:
	    bool visibility;

	    TriggerZone triggerZoneForObject;
};

#endif
