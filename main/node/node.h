#pragma once

#include <iostream>
#include <vector>
#include "../operation/operation.h"

class Node
{
	private:
		Node *parent;
		double threshold = MAXFLOAT;
		int noChildren;
		std::vector<Node> children;
		OperationType operation;

	public:
		Node();

		void generateInnerNode();

		int getNoChildren() { return noChildren; };
		double getThreshold() { return threshold; };
		std::vector<Node> getChildren() { return children; };
		OperationType getOperationType() { return operation; };

		void setNoChildren(int noChildren);
		void setThreshold(double threshold);
		void setChildren(std::vector<Node> children);
		void setOperationType(OperationType operation);
};
