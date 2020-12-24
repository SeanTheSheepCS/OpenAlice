#ifndef ACTOR_ALICE_H
#define ACTOR_ALICE_H

#include "../reference_number_enums.h"
#include "../engine/advanced_classes/player_object_module/player_object_module.h"
#include "../engine/advanced_classes/tile_map_module/tile_map_module.h"
#include "../engine/primitive_classes/world_object.h"
#include <unordered_map>

class AliceAnimationAndTextureDecisionFactors
{
	public:
		WorldObjectReferenceNumber heldWorldObjectReferenceNumber; 
		int xMovementAmount;
		int yMovementAmount;
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
		void initializeEntryGroupInDecisionFactorToTextureBankRefNumberMap(WorldObjectReferenceNumber heldWorldObjectReferenceNumberArg, TextureBankReferenceNumber leftTexture, TextureBankReferenceNumber rightTexture, TextureBankReferenceNumber upTexture, TextureBankReferenceNumber downTexture);
		void initializeEntryInDecisionFactorToTextureBankRefNumberMap(WorldObjectReferenceNumber heldWorldObjectReferenceNumber, int xMovementAmount, int yMovementAmount, TextureBankReferenceNumber textureBankRefNumber);
		void initializeDecisionFactorsToAnimationBankRefNumberMap();
		void initializeEntryGroupInDecisionFactorToAnimationBankRefNumberMap(WorldObjectReferenceNumber heldWorldObjectReferenceNumberArg, AnimationBankReferenceNumber leftAnimation, AnimationBankReferenceNumber rightAnimation, AnimationBankReferenceNumber upAnimation, AnimationBankReferenceNumber downAnimation);
		void initializeEntryInDecisionFactorToAnimationBankRefNumberMap(WorldObjectReferenceNumber heldWorldObjectReferenceNumber, int xMovementAmount, int yMovementAmount, AnimationBankReferenceNumber AnimationBankRefNumber);

		WorldObjectReferenceNumber referenceNumberOfHeldWorldObject;
		WorldObject heldWorldObject;
		std::map<AliceAnimationAndTextureDecisionFactors,TextureBankReferenceNumber> decisionFactorsToTextureBankRefNumberMap;
		std::map<AliceAnimationAndTextureDecisionFactors,AnimationBankReferenceNumber> decisionFactorsToAnimationBankRefNumberMap;
};

#endif
