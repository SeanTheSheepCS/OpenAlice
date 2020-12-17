#ifndef OAE_ENGINE_UTILITIES_H
#define OAE_ENGINE_UTILITIES_H

#include <vector>

std::vector<unsigned char> unsignedIntToUnsignedCharVector(unsigned int integerToConvert);
std::vector<unsigned char> intToUnsignedCharVector(int integerToConvert);
unsigned int unsignedCharVectorToUnsignedInt(std::vector<unsigned char>::iterator& vectorToConvertIterator);
int unsignedCharVectorToInt(std::vector<unsigned char>::iterator& vectorToConvertIterator);

#endif
