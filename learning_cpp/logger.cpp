#include <iostream>
#include "logger.h"

namespace logger
{

	void printResults(IntResult* result)
	{
		std::cout << "\nProduct: " << result->product << "\n";
		std::cout << "Sum: " << result->sum << "\n";
		std::cout << "Quotient: " << result->quotient << "\n";
		std::cout << "Difference: " << result->difference << "\n\n";
	}

	void printResults(FloatResult* result)
	{
		std::cout << "\nProduct: " << result->product << "\n";
		std::cout << "Sum: " << result->sum << "\n";
		std::cout << "Quotient: " << result->quotient << "\n";
		std::cout << "Difference: " << result->difference << "\n\n";
	}

	void printResults(BoolResult* result)
	{
		std::cout << std::boolalpha;
		std::cout << "\nBoolean AND gate: " << result->boolAnd << "\n";
		std::cout << "Boolean OR gate: " << result->boolOr << "\n";
		std::cout << "Boolean EQUALS gate: " << result->boolEqu << "\n\n";
		std::cout << std::noboolalpha;
}
}