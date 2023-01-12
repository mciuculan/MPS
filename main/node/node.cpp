#include "node.h"

Node::Node() 
{
	this->threshold = 0;
	this->value = 0;
}
Node::Node(double threshold) : threshold(threshold) {}

void Node::setOperationType(OperationType operation)
{
	this->operation = operation;
}

void Node::setValue(double value)
{
	this->value = value;
}

void Node::setThreshold(double threshold)
{
	this->threshold = threshold;
}

void Node::printNode()
{
	std::cout << "Operation: " << Operation::convertToString(this->getOperationType()) << "\n";
	std::cout << "Children: " << this->children.size() << "\n";
	for (int i = 0; i < (int) this->children.size(); ++i) {
		std::cout << this->children[i].threshold << " ";
	}
	std::cout << "\n";
}
