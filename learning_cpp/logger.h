#ifndef LOGGER_H
#define LOGGER_H

namespace logger
{
	struct IntResult
	{
		int product{};
		int sum{};
		int quotient{};
		int difference{};
	};

	struct FloatResult
	{
		float product{};
		float sum{};
		float quotient{};
		float difference{};
	};

	struct BoolResult
	{
		bool boolAnd{};
	};


	void printResults(IntResult result);

	void printResults(FloatResult result);

	void printResults(BoolResult result);

}

#endif 

