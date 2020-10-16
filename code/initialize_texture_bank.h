#ifndef INTIALIZE_TEXTURE_BANK_H
#define INTIALIZE_TEXTURE_BANK_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "texture_bank.h"
#include "reference_number_enums.h"

void addTextureToTextureBank(int referenceNumber, std::string path, TextureBank* bankToWriteTo);
TextureBank initializeTextureBank();

#endif
