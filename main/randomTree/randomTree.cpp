#include "randomTree.h"


RandomTree::RandomTree() {}


void RandomTree::generateTreeHierarchy(std::queue<std::pair<int, OperationType>> choices, std::vector<int> leavesOrder)
{
	for (auto i : leavesOrder) {
		leavesQueue.push(leafSet[i]);
	}

	Node newNode;
	while (leavesQueue.size() > 1) {
		std::pair<int, OperationType> choice = choices.front();
		choices.pop();

		newNode = Node();
		newNode.setOperationType(choice.second);
		for (int i = 0; i < choice.first; ++i) {

			newNode.getChildren().push_back(leavesQueue.front());
			leavesQueue.pop();
		}

		leavesQueue.push(newNode);
	}
}

void RandomTree::printTree(Node node)
{
	if (node.getChildren().size() == 0) {
		std::cout << "[" << node.getThreshold() << "], ";
		return;
	}

	std::cout << Operation::convertToString(node.getOperationType()) << " ";

	for (int i = 0; i < (int) node.getChildren().size(); ++i) {
		if (node.getChildren()[i].getChildren().size() != 0) {
			printTree(node.getChildren()[i]);
		} else {
			std::cout << "[" << node.getChildren()[i].getThreshold() << "], ";
		}
	}
}

void RandomTree::applyOp(Node *node)
{
	if (node->getChildren().size() == 0) {
		node->setValue(node->getThreshold());
		return;
	}

	for (int i = 0; i < (int) node->getChildren().size(); ++i) {
		if (node->getChildren()[i].getChildren().size() != 0) {
			applyOp(&node->getChildren()[i]);
		}
	}

	std::vector<double> values;
	for (int i = 0; i < (int) node->getChildren().size(); ++i) {
		if (!node->getChildren()[i].getChildren().size()) {
			values.push_back(node->getChildren()[i].getThreshold());
		} else {
			values.push_back(node->getChildren()[i].getValue());
		}
	}

	node->setValue(Operation::applyOperation(node->getOperationType(), values));

}
