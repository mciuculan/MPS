#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>
#include <queue>
#include <stack>

#include "../node/node.h"
#include "../operation/operation.h"

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
		void printTree(Node node);
		void applyOp(Node *node);
};
