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

#include <iostream>

unsigned int readUnsignedIntFromUnsignedCharIterator(std::istream_iterator<unsigned char>& iteratorToReadFrom)
{
	unsigned int returnValue = 0;
	for(unsigned int i = 0; i < 4; i++)
	{
		unsigned char currentValue = (*iteratorToReadFrom);
		unsigned char currentValueAsUnsignedInt = (((unsigned int)currentValue) << ((3-i) * 8));
		returnValue = (returnValue | currentValueAsUnsignedInt);
		iteratorToReadFrom++;
	}
	return returnValue;
}

int readIntFromUnsignedCharIterator(std::istream_iterator<unsigned char>& iteratorToReadFrom)
{
	int returnValue = 0;
	for(unsigned int i = 0; i < 4; i++)
	{
		unsigned char currentValue = (*iteratorToReadFrom);
		int currentValueAsInt = (((int)currentValue) << ((3-i) * 8));
		returnValue = (returnValue | currentValueAsInt);
		iteratorToReadFrom++;
	}
	return returnValue;
}
