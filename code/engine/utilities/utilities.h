#ifndef OAE_ENGINE_UTILITIES_H
#define OAE_ENGINE_UTILITIES_H

#include <vector>
#include <fstream>
#include <iterator>

std::vector<unsigned char> unsignedIntToUnsignedCharVector(unsigned int integerToConvert);
std::vector<unsigned char> intToUnsignedCharVector(int integerToConvert);
unsigned int readUnsignedIntFromUnsignedCharIterator(std::istream_iterator<unsigned char>& iteratorToReadFrom);
int readIntFromUnsignedCharIterator(std::istream_iterator<unsigned char>& iteratorToReadFrom);

#endif
