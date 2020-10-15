#ifndef ACTOR_ALICE_H
#define ACTOR_ALICE_H

#include "../reference_number_enums.h"
#include "../engine/advanced_classes/player_object_module/player_object_module.h"
#include "../engine/advanced_classes/tile_map_module/tile_map_module.h"
#include "../engine/primitive_classes/world_object.h"

enum HeldObjectReferenceNumber
{
    HELD_OBJECT_REF_NUMBER_NONE = 0,
    HELD_OBJECT_REF_NUMBER_WATERING_CAN = 1,
    HELD_OBJECT_REF_NUMBER_HOE = 2,
    HELD_OBJECT_REF_NUMBER_TOMATO_SEEDS = 3,
    HELD_OBJECT_REF_NUMBER_TOMATO_CRATE = 4,
    HELD_OBJECT_REF_NUMBER_ZUCCHINI_SEEDS = 5,
    HELD_OBJECT_REF_NUMBER_ZUCCHINI_CRATE = 6,
    HELD_OBJECT_REF_NUMBER_CARROTS_SEEDS = 7,
    HELD_OBJECT_REF_NUMBER_CARROTS_CRATE = 8
};

class Alice: public PlayerObject
{
    public:
        Alice(int x, int y, unsigned int width, unsigned int height);
        void pickUpObject(int referenceNumberOfObjectToPickUp, TileMap& tileMapYouPickedItUpFrom);
        void putDownObject(TileMap& tileMapToPutItDownIn);
        bool isHoldingObject() const;
       	int returnReferenceNumberOfHeldObject() const;
		const std::vector<WorldObjectProperty> returnPropertiesOfHeldWorldObject() const;
    protected:
        //
    private:
        int referenceNumberOfHeldWorldObject;
        WorldObject heldWorldObject;
};

#endif
