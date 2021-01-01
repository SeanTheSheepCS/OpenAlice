#ifndef ACTOR_ALICE_H
#define ACTOR_ALICE_H

#include "../reference_number_enums.h"
#include "../engine/advanced_classes/player_object_module/player_object_module.h"
#include "../engine/advanced_classes/tile_map_module/tile_map_module.h"
#include "../engine/primitive_classes/world_object.h"
#include <map>

class AliceAnimationAndTextureDecisionFactors
{
	public:
		AliceAnimationAndTextureDecisionFactors();
		WorldObjectReferenceNumber heldWorldObjectReferenceNumber; 
		int xMovementAmount;
		int yMovementAmount;
		int capacityOfObject; //-1 denotes that the capacity is irrelevant.
		bool operator ==(const AliceAnimationAndTextureDecisionFactors& rhs) const;
		bool operator <(const AliceAnimationAndTextureDecisionFactors& rhs) const;
	protected:
		//
	private:
		//
};

class Alice: public PlayerObject
{
	public:
		Alice(int x, int y, unsigned int width, unsigned int height);
		void pickUpObject(WorldObjectReferenceNumber referenceNumberOfObjectToPickUp, TileMap& tileMapYouPickedItUpFrom);
		void putDownObject(TileMap& tileMapToPutItDownIn);
		void removeWorldObjectPropertyFromHeldWorldObject(const WorldObjectProperty propertyToRemove);
		void addWorldObjectPropertyToHeldWorldObject(const WorldObjectProperty propertyToAdd);

		void associateWithCorrectAnimation();

		bool isHoldingObject() const;
		WorldObjectReferenceNumber returnReferenceNumberOfHeldObject() const;
		const std::vector<WorldObjectProperty> returnPropertiesOfHeldWorldObject() const;

		const int returnCapacityOfHeldWorldObject() const; //Returns -1 on failure.
		const int returnFilledAmountPropertyOfHeldWorldObject() const; //Returns -1 on failure.
		void incrementFilledAmountPropertyOfHeldWorldObject();
		void decrementFilledAmountPropertyOfHeldWorldObject();
		void fillHeldWorldObjectToCapacity();

		void deleteHeldWorldObject();

		void setReferenceNumberOfHeldWorldObject(WorldObjectReferenceNumber newReferenceNumberOfHeldWorldObject);
	protected:
		//
	private:
		void initializeDecisionFactorsToTextureBankRefNumberMap();
		void initializeEntryGroupInDecisionFactorToTextureBankRefNumberMap(WorldObjectReferenceNumber heldWorldObjectReferenceNumberArg, TextureBankReferenceNumber leftTexture, TextureBankReferenceNumber rightTexture, TextureBankReferenceNumber upTexture, TextureBankReferenceNumber downTexture, int capacity = -1);
		void initializeEntryInDecisionFactorToTextureBankRefNumberMap(WorldObjectReferenceNumber heldWorldObjectReferenceNumber, int xMovementAmount, int yMovementAmount, int capacity, TextureBankReferenceNumber textureBankRefNumber);

		void initializeDecisionFactorsToAnimationBankRefNumberMap();
		void initializeEntryGroupInDecisionFactorToAnimationBankRefNumberMap(WorldObjectReferenceNumber heldWorldObjectReferenceNumberArg, AnimationBankReferenceNumber leftAnimation, AnimationBankReferenceNumber rightAnimation, AnimationBankReferenceNumber upAnimation, AnimationBankReferenceNumber downAnimation, int capacity = -1);
		void initializeEntryInDecisionFactorToAnimationBankRefNumberMap(WorldObjectReferenceNumber heldWorldObjectReferenceNumber, int xMovementAmount, int yMovementAmount, int capacity, AnimationBankReferenceNumber AnimationBankRefNumber);

		WorldObjectReferenceNumber referenceNumberOfHeldWorldObject;
		WorldObject heldWorldObject;
		std::map<AliceAnimationAndTextureDecisionFactors,TextureBankReferenceNumber> decisionFactorsToTextureBankRefNumberMap;
		std::map<AliceAnimationAndTextureDecisionFactors,AnimationBankReferenceNumber> decisionFactorsToAnimationBankRefNumberMap;
};

#endif
