#ifndef WORLD_OBJECT_H
#define WORLD_OBJECT_H

#include <SFML/Graphics.hpp>
#include "textured_object.h"
#include "trigger_zone.h"
#include "collision_box.h"
#include "world_object_properties.h"

class WorldObject: public TexturedObject
{
	public:
		WorldObject();
		WorldObject(int x, int y, unsigned int width, unsigned int height, const sf::Texture* texture);
		WorldObject(TexturedObject parentObject);

		void setTriggerZoneX(int newX);
		void setTriggerZoneY(int newY);
		void setTriggerZoneWidth(unsigned int newWidth);
		void setTriggerZoneHeight(unsigned int newHeight);

		void setCollisionBoxX(int newX);
		void setCollisionBoxY(int newY);
		void setCollisionBoxWidth(int newWidth);
		void setCollisionBoxHeight(int newHeight);

		void attachCollisionBox(CollisionBox collisionBoxToAttach);
		void detachCollisionBox();
		void pushDrawableObjectOutOfCollisionZoneIfItIntersects(DrawableObject& objectToPush) const;
		bool isDrawableObjectWithinCollisionBox(const DrawableObject& objectToCheck) const;

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
		CollisionBox collisionBoxForObject;
		std::vector<WorldObjectProperty> properties;
};

#endif
