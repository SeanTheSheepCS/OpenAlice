#include "test_unsigned_int_to_char_vector.h"

void runTestUnsignedIntToCharVectorTests()
{
	runTestUnsignedIntToCharVectorTestOne();
	runTestUnsignedIntToCharVectorTestTwo();
	runTestUnsignedIntToCharVectorTestThree();
	runTestUnsignedIntToCharVectorTestFour();
}

void runTestUnsignedIntToCharVectorTestOne()
{
	std::vector<unsigned char> expectedValue;
	expectedValue.push_back(0x00);
	expectedValue.push_back(0x00);
	expectedValue.push_back(0x07);
	expectedValue.push_back(0x08);
	std::vector<unsigned char> actualValue = unsignedIntToUnsignedCharVector(1800);
	bool hasTestPassed = true;
	for(int i = 0; i < 4; i ++)
	{
		if(expectedValue.at(i) != actualValue.at(i))
		{
			hasTestPassed = false;
		}
	}
	if(hasTestPassed)
	{
		std::cout << "runTestUnsignedIntToCharVectorTestOne PASS" << std::endl;
	}
	else
	{
		std::cout << "runTestUnsignedIntToCharVectorTestOne FAIL. Expected: " << std::hex << "0x" << expectedValue.at(0) << ", 0x"<< expectedValue.at(1) << ", 0x" << expectedValue.at(2) << ", 0x" <<  expectedValue.at(3) << " Actual: "<< std::hex << "0x" << actualValue.at(0) << ", 0x" << actualValue.at(1) << ", 0x" << actualValue.at(2) << ", 0x" << actualValue.at(3) << ", 0x" << actualValue.at(4) << std::dec << std::endl;
	}
}

void runTestUnsignedIntToCharVectorTestTwo()
{
	std::vector<unsigned char> expectedValue;
	expectedValue.push_back(0x00);
	expectedValue.push_back(0x00);
	expectedValue.push_back(0x00);
	expectedValue.push_back(0x01);
	std::vector<unsigned char> actualValue = unsignedIntToUnsignedCharVector(1);
	bool hasTestPassed = true;
	for(int i = 0; i < 4; i ++)
	{
		if(expectedValue.at(i) != actualValue.at(i))
		{
			hasTestPassed = false;
		}
	}
	if(hasTestPassed)
	{
		std::cout << "runTestUnsignedIntToCharVectorTestTwo PASS" << std::endl;
	}
	else
	{
		std::cout << "runTestUnsignedIntToCharVectorTestTwo FAIL. Expected: " << std::hex << "0x" << expectedValue.at(0) << ", 0x"<< expectedValue.at(1) << ", 0x" << expectedValue.at(2) << ", 0x" <<  expectedValue.at(3) << " Actual: "<< std::hex << "0x" << actualValue.at(0) << ", 0x" << actualValue.at(1) << ", 0x" << actualValue.at(2) << ", 0x" << actualValue.at(3) << ", 0x" << actualValue.at(4) << std::dec << std::endl;
	}
}

void runTestUnsignedIntToCharVectorTestThree()
{
	std::vector<unsigned char> expectedValue;
	expectedValue.push_back(0x00);
	expectedValue.push_back(0x00);
	expectedValue.push_back(0x00);
	expectedValue.push_back(0x32);
	std::vector<unsigned char> actualValue = unsignedIntToUnsignedCharVector(50);
	bool hasTestPassed = true;
	for(int i = 0; i < 4; i ++)
	{
		if(expectedValue.at(i) != actualValue.at(i))
		{
			hasTestPassed = false;
		}
	}
	if(hasTestPassed)
	{
		std::cout << "runTestUnsignedIntToCharVectorTestThree PASS" << std::endl;
	}
	else
	{
		std::cout << "runTestUnsignedIntToCharVectorTestThree FAIL. Expected: " << std::hex << "0x" << expectedValue.at(0) << ", 0x"<< expectedValue.at(1) << ", 0x" << expectedValue.at(2) << ", 0x" <<  expectedValue.at(3) << " Actual: "<< std::hex << "0x" << actualValue.at(0) << ", 0x" << actualValue.at(1) << ", 0x" << actualValue.at(2) << ", 0x" << actualValue.at(3) << ", 0x" << actualValue.at(4) << std::dec << std::endl;
	}
}

void runTestUnsignedIntToCharVectorTestFour()
{
	std::vector<unsigned char> expectedValue;
	expectedValue.push_back(0x00);
	expectedValue.push_back(0x00);
	expectedValue.push_back(0x01);
	expectedValue.push_back(0xF4);
	std::vector<unsigned char> actualValue = unsignedIntToUnsignedCharVector(500);
	bool hasTestPassed = true;
	for(int i = 0; i < 4; i ++)
	{
		if(expectedValue.at(i) != actualValue.at(i))
		{
			hasTestPassed = false;
		}
	}
	if(hasTestPassed)
	{
		std::cout << "runTestUnsignedIntToCharVectorTestFour PASS" << std::endl;
	}
	else
	{
		std::cout << "runTestUnsignedIntToCharVectorTestFour FAIL. Expected: " << std::hex << "0x" << expectedValue.at(0) << ", 0x"<< expectedValue.at(1) << ", 0x" << expectedValue.at(2) << ", 0x" <<  expectedValue.at(3) << " Actual: "<< std::hex << "0x" << actualValue.at(0) << ", 0x" << actualValue.at(1) << ", 0x" << actualValue.at(2) << ", 0x" << actualValue.at(3) << ", 0x" << actualValue.at(4) << std::dec << std::endl;
	}
}
