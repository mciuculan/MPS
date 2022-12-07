#pragma once

#include <iostream>
#include <vector>
#include <cmath>

enum OperationType
{
	GEOMETRIC_MEAN,
	ARITHMETIC_MEAN,
	MULTIPLICATION
};


class Operation
{
	private:

	public:
		Operation();

		static double applyOperation(int opIndex, std::vector<double> array);
		static double applyGeometricMean(std::vector<double> array);
		static double applyArithmeticMean(std::vector<double> array);
		static double applyMultiplication(std::vector<double> array);
};
