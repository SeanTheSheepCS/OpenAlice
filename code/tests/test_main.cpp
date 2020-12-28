#include "test_main.h"

int main()
{
	runAllTests();
	std::cout << "PRESS ENTER TO ACKNOWLEDGE TEST RESULTS" << std::endl;
	std::cin.ignore();
}

void runAllTests()
{
	runTestUnsignedIntToCharVectorTests();
	runTestIstreamIteratorToUnsignedIntTests();
}
