#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>
#include <queue>
#include <stack>

#include "../node/node.h"

class RandomTree
{
	private:
		int depth;
		Node root;
		std::stack<Node> stack;

	public:
		RandomTree();

		void generateTree(int depth, Node *src, Node *parent);

		int getDepth() { return depth; }

};
