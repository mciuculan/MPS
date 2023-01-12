#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>
#include <queue>
#include <stack>

#include "../node/node.h"
#include "../operation/operation.h"

enum PixelType
{
	TRUE_POSITIVE,
	FALSE_POSITIVE,
	TRUE_NEGATIVE,
	FALSE_NEGATIVE
};

class RandomTree
{
	private:
		std::vector<Node> leafSet;
		std::queue<Node> leavesQueue;
		
	public:
		RandomTree();

		std::vector<Node> & getLeafSet() { return leafSet; };
		std::queue<Node> & getLeavesQueue() { return leavesQueue; };

		void generateTreeHierarchy(std::queue<std::pair<int, OperationType>> choices, std::vector<int> leavesOrder);

		static void printSequenceOp(std::queue<std::pair<int, OperationType>> choices);
		static PixelType getPixelType(double value, int pixelClass);
		void printTree(Node node);
		void applyOp(Node *node);
};
