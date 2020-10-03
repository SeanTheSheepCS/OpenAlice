#ifndef WORLD_OBJECT_H
#define WORLD_OBJECT_H

#include <SFML/Graphics.hpp>
#include "textured_object.h"
#include "trigger_zone.h"
#include "world_object_properties.h"

class WorldObject: public TexturedObject
{
    public:
        WorldObject();
        WorldObject(int x, int y, unsigned int width, unsigned int height, const sf::Texture* texture);
	    WorldObject(TexturedObject parentObject);

	    void setX(int newX);
	    void setY(int newY);
	    void setWidth(unsigned int newWidth);
	    void setHeight(unsigned int newHeight);

	    void attachTriggerZone(TriggerZone zoneToAttach);
	    void detachTriggerZone();
	    bool isDrawableObjectWithinTriggerZone(const DrawableObject& objectToCheck) const;

	    void setVisibility(bool visibility);
	    bool getVisibility() const;
        bool isInvalid() const;

		void addWorldObjectProperty(WorldObjectProperty property);
		std::vector<WorldObjectProperty> getProperties() const;

        void draw(sf::RenderWindow& windowToDrawObjectIn);
    protected:
        //
    private:
	    bool visibility;

	    TriggerZone triggerZoneForObject;
		std::vector<WorldObjectProperty> properties;
};

#endif
