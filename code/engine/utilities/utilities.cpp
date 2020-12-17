#include "utilities.h"

std::vector<unsigned char> unsignedIntToUnsignedCharVector(unsigned int integerToConvert)
{
	std::vector<unsigned char> returnValue;
	unsigned char firstCharToWrite = (((unsigned char)(integerToConvert >> 24)) & 0xFF);
	unsigned char secondCharToWrite = (((unsigned char)(integerToConvert >> 16)) & 0xFF);
	unsigned char thirdCharToWrite = (((unsigned char)(integerToConvert >> 8)) & 0xFF);
	unsigned char fourthCharToWrite = (((unsigned char)(integerToConvert >> 0)) & 0xFF);
	returnValue.push_back(firstCharToWrite);
	returnValue.push_back(secondCharToWrite);
	returnValue.push_back(thirdCharToWrite);
	returnValue.push_back(fourthCharToWrite);
	return returnValue;
}

std::vector<unsigned char> intToUnsignedCharVector(int integerToConvert)
{
	std::vector<unsigned char> returnValue;
	unsigned char firstCharToWrite = (((unsigned char)(integerToConvert >> 24)) & 0xFF);
	unsigned char secondCharToWrite = (((unsigned char)(integerToConvert >> 16)) & 0xFF);
	unsigned char thirdCharToWrite = (((unsigned char)(integerToConvert >> 8)) & 0xFF);
	unsigned char fourthCharToWrite = (((unsigned char)(integerToConvert >> 0)) & 0xFF);
	returnValue.push_back(firstCharToWrite);
	returnValue.push_back(secondCharToWrite);
	returnValue.push_back(thirdCharToWrite);
	returnValue.push_back(fourthCharToWrite);
	return returnValue;
}

unsigned int unsignedCharVectorToUnsignedInt(std::vector<unsigned char>::iterator& vectorToConvertIterator)
{
	unsigned int returnValue = 0;
	for(unsigned int i = 0; i < 4; i++)
	{
		unsigned int currentValue = (*vectorToConvertIterator);
		currentValue = (currentValue << (i * 8));
		returnValue = (returnValue | currentValue);
		vectorToConvertIterator++;
	}
	return returnValue;
}

int unsignedCharVectorToInt(std::vector<unsigned char>::iterator& vectorToConvertIterator)
{
	int returnValue = 0;
	for(unsigned int i = 0; i < 4; i++)
	{
		int currentValue = (*vectorToConvertIterator);
		currentValue = (currentValue << (i * 8));
		returnValue = (returnValue | currentValue);
		vectorToConvertIterator++;
	}
	return returnValue;
}
