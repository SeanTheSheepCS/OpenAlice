#ifndef ACTOR_ALICE_H
#define ACTOR_ALICE_H

#include "../reference_number_enums.h"
#include "../engine/advanced_classes/player_object_module/player_object_module.h"
#include "../engine/advanced_classes/tile_map_module/tile_map_module.h"
#include "../engine/primitive_classes/world_object.h"

class Alice: public PlayerObject
{
	public:
		Alice(int x, int y, unsigned int width, unsigned int height);
		void pickUpObject(int referenceNumberOfObjectToPickUp, TileMap& tileMapYouPickedItUpFrom);
		void putDownObject(TileMap& tileMapToPutItDownIn);
		void removeWorldObjectPropertyFromHeldWorldObject(const WorldObjectProperty propertyToRemove);
		void addWorldObjectPropertyToHeldWorldObject(const WorldObjectProperty propertyToAdd);

		bool isHoldingObject() const;
		int returnReferenceNumberOfHeldObject() const;
		const std::vector<WorldObjectProperty> returnPropertiesOfHeldWorldObject() const;

		const int returnCapacityOfHeldWorldObject() const; //Returns -1 on failure.
		const int returnFilledAmountPropertyOfHeldWorldObject() const; //Returns -1 on failure.
		void incrementFilledAmountPropertyOfHeldWorldObject();
		void decrementFilledAmountPropertyOfHeldWorldObject();
		void fillHeldWorldObjectToCapacity();

		void deleteHeldWorldObject();

		void setReferenceNumberOfHeldWorldObject(int newReferenceNumberOfHeldWorldObject);
	protected:
		//
	private:
		int referenceNumberOfHeldWorldObject;
		WorldObject heldWorldObject;
};

#endif
