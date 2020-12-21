#ifndef INTIALIZE_TEXTURE_BANK_H
#define INTIALIZE_TEXTURE_BANK_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "texture_bank.h"
#include "reference_number_enums.h"

void addNonLanguageDependentTextureToTextureBank(int referenceNumber, std::string path, TextureBank* bankToWriteTo);
void addLanguageDependentTextureToTextureBank(int referenceNumber, const std::string& languageFolderPath, const std::string& pathToFile, TextureBank* bankToWriteTo);
TextureBank initializeTextureBank(DisplayLanguage languageToUse);
void fillTextureBankWithNonLanguageDependentTextures(TextureBank& textureBankToFill);
void fillTextureBankWithLanguageDependentTextures(TextureBank& textureBankToFill, DisplayLanguage languageToUse);

#endif
