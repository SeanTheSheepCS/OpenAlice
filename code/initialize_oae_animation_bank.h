#ifndef INITIALIZE_OAE_ANIMATION_BANK_H
#define INITIALIZE_OAE_ANIMATION_BANK_H

#ifndef DEFAULT_ANIMATION_SPEED
#define DEFAULT_ANIMATION_SPEED 300
#endif

#include "reference_number_enums.h"
#include "oae_animation_bank.h"
#include "texture_bank.h"

OAEAnimationBank initializeOAEAnimationBank(const TextureBank& textureBankToUse);

#endif
