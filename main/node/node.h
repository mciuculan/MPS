#pragma once

#include <iostream>
#include <vector>
#include "../operation/operation.h"

class Node
{
	private:
		std::vector<Node> children;
		OperationType operation;
		double value;
		double threshold;

	public:
		Node();
		Node(double threshold);

		std::vector<Node> & getChildren() { return children; };
		OperationType getOperationType() { return operation; };
		double getValue() { return value; };
		double getThreshold() { return threshold; };

		void setThreshold(double threshold);
		void setValue(double value);
		void setOperationType(OperationType operation);
		void printNode();
};
