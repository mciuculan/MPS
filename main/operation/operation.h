#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <bits/stdc++.h>

enum OperationType
{
	GEOMETRIC_MEAN,
	ARITHMETIC_MEAN,
	MULTIPLICATION,
	MIN,
	MAX
};


class Operation
{
	private:

	public:
		Operation();

		static double applyOperation(int opIndex, std::vector<double>& array);
		static double applyGeometricMean(std::vector<double>& array);
		static double applyArithmeticMean(std::vector<double>& array);
		static double applyMultiplication(std::vector<double>& array);
		static double applyMin(std::vector<double>& array);
		static double applyMax(std::vector<double>& array);
		static std::string convertToString(int opIndex);
};
