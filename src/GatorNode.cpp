#include <string>
#include "GatorNode.h"
using namespace std;

GatorNode::GatorNode() {
    this->id = 0;
    this->balanceFactor = 0;
    this->name = "";
    this->parent = nullptr;
    this->leftChild = nullptr;
    this->rightChild = nullptr;
}

GatorNode::GatorNode(string name, int id) {
    this->id = id;
    this->name = name;
    this->parent = nullptr;
    this->leftChild = nullptr;
    this->rightChild = nullptr;
}

void GatorNode::setParent(GatorNode* parent) {
    this->parent = parent;
}

void GatorNode::setLeftChild(GatorNode* child) {
    this->leftChild = child;
}

void GatorNode::setRightChild(GatorNode* child) {
    this->rightChild = child;
}

int GatorNode::getBalanceFactor() {
    return this->balanceFactor;
}

void GatorNode::setBalanceFactor(int bf) {
    this->balanceFactor = bf;
}

int GatorNode::getId() {
    return this->id;
}

void GatorNode::setId(int id) {
    this->id = id;
}

string GatorNode::getName() {
    return this->name;
}

void GatorNode::setName(string name) {
    this->name = name;
}

GatorNode* GatorNode::getLeftChild() {
    return this->leftChild;
}

GatorNode* GatorNode::getRightChild() {
    return this->rightChild;
}

GatorNode* GatorNode::getParent() {
    return this->parent;
}