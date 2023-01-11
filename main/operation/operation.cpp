#include "operation.h"

std::vector<OperationType> operations {OperationType::GEOMETRIC_MEAN, OperationType::ARITHMETIC_MEAN, OperationType::MULTIPLICATION};

Operation::Operation() {}

double Operation::applyArithmeticMean(std::vector<double> array)
{
	double sum = 0.0;

	for (auto i : array) {
		sum += i;
	}

	return sum / array.size();
}

double Operation::applyMultiplication(std::vector<double> array)
{
	auto result = 1.0;

	for (auto i : array) {
		result *= i;
	}

	return result;
}

double Operation::applyGeometricMean(std::vector<double> array)
{
	auto multiplication = Operation::applyMultiplication(array);

	return pow(multiplication, (double)1 / array.size());
}

double Operation::applyOperation(int opIndex, std::vector<double> array)
{
	switch (opIndex)
	{
	case GEOMETRIC_MEAN:
		return applyGeometricMean(array);
	
	case ARITHMETIC_MEAN:
		return applyArithmeticMean(array);

	case MULTIPLICATION:
		return applyMultiplication(array);

	};
}

std::string Operation::convertToString(int opIndex)
{
	switch (opIndex)
	{
	case GEOMETRIC_MEAN:
		return "gm";
	
	case ARITHMETIC_MEAN:
		return "am";

	case MULTIPLICATION:
		return "*";

	};
}