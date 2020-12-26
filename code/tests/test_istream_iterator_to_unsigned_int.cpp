#include "test_istream_iterator_to_unsigned_int.h"

void runTestIstreamIteratorToUnsignedIntTests()
{
	runTestIstreamIteratorToUnsignedIntTestOne();
	runTestIstreamIteratorToUnsignedIntTestTwo();
	runTestIstreamIteratorToUnsignedIntTestThree();
	runTestIstreamIteratorToUnsignedIntTestFour();
}

void runTestIstreamIteratorToUnsignedIntTestOne()
{
	unsigned int expectedValue = 200;
	std::ifstream fileToReadFrom("test_istream_iterator_to_unsigned_int_test_file_one.bin", std::ifstream::binary);
	fileToReadFrom >> std::noskipws; //See the runLoadProcedure in FarmScreen for a complete explanation of why this line is necessary.
	std::istream_iterator<unsigned char> iteratorToReadFrom(fileToReadFrom);
	unsigned int actualValue = readUnsignedIntFromUnsignedCharIterator(iteratorToReadFrom);
	if(actualValue == expectedValue)
	{
		std::cout << "runTestIstreamIteratorToUnsignedIntTestOne PASS" << std::endl;
	}
	else
	{
		std::cout << "runTestIstreamIteratorToUnsignedIntTestOne FAIL. Expected: " << expectedValue << " Actual: " << actualValue << std::endl;
	}
}

void runTestIstreamIteratorToUnsignedIntTestTwo()
{
	unsigned int expectedValue = 300;
	std::ifstream fileToReadFrom("test_istream_iterator_to_unsigned_int_test_file_two.bin", std::ifstream::binary);
	fileToReadFrom >> std::noskipws; //See the runLoadProcedure in FarmScreen for a complete explanation of why this line is necessary.
	std::istream_iterator<unsigned char> iteratorToReadFrom(fileToReadFrom);
	unsigned int actualValue = readUnsignedIntFromUnsignedCharIterator(iteratorToReadFrom);
	if(actualValue == expectedValue)
	{
		std::cout << "runTestIstreamIteratorToUnsignedIntTestTwo PASS" << std::endl;
	}
	else
	{
		std::cout << "runTestIstreamIteratorToUnsignedIntTestTwo FAIL. Expected: " << expectedValue << " Actual: " << actualValue << std::endl;
	}
}

void runTestIstreamIteratorToUnsignedIntTestThree()
{
	unsigned int expectedValue = 202020;
	std::ifstream fileToReadFrom("test_istream_iterator_to_unsigned_int_test_file_three.bin", std::ifstream::binary);
	fileToReadFrom >> std::noskipws; //See the runLoadProcedure in FarmScreen for a complete explanation of why this line is necessary.
	std::istream_iterator<unsigned char> iteratorToReadFrom(fileToReadFrom);
	unsigned int actualValue = readUnsignedIntFromUnsignedCharIterator(iteratorToReadFrom);
	if(actualValue == expectedValue)
	{
		std::cout << "runTestIstreamIteratorToUnsignedIntTestThree PASS" << std::endl;
	}
	else
	{
		std::cout << "runTestIstreamIteratorToUnsignedIntTestThree FAIL. Expected: " << expectedValue << " Actual: " << actualValue << std::endl;
	}
}

void runTestIstreamIteratorToUnsignedIntTestFour()
{
	unsigned int expectedValue = 99999999;
	std::ifstream fileToReadFrom("test_istream_iterator_to_unsigned_int_test_file_four.bin", std::ifstream::binary);
	fileToReadFrom >> std::noskipws; //See the runLoadProcedure in FarmScreen for a complete explanation of why this line is necessary.
	std::istream_iterator<unsigned char> iteratorToReadFrom(fileToReadFrom);
	unsigned int actualValue = readUnsignedIntFromUnsignedCharIterator(iteratorToReadFrom);
	if(actualValue == expectedValue)
	{
		std::cout << "runTestIstreamIteratorToUnsignedIntTestFour PASS" << std::endl;
	}
	else
	{
		std::cout << "runTestIstreamIteratorToUnsignedIntTestFour FAIL. Expected: " << expectedValue << " Actual: " << actualValue << std::endl;
	}
}
