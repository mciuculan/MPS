#include "node.h"

Node::Node() {}

void Node::setNoChildren(int noChildren)
{
	this->noChildren = noChildren;
}

void Node::setThreshold(double threshold)
{
	this->threshold = threshold;
}


void Node::setChildren(std::vector<Node> children)
{
	this->children = children;
}


void Node::setOperationType(OperationType operation)
{
	this->operation = operation;
}
