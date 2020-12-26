#include "test_main.h"

int main()
{
	runAllTests();
}

void runAllTests()
{
	runTestUnsignedIntToCharVectorTests();
	runTestIstreamIteratorToUnsignedIntTests();
}
