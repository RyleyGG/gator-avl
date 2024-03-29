#include <iostream>
#include <string>
#include <algorithm>
#include "GatorAVL.h"
using namespace std;

GatorAVL::GatorAVL() {
    this->rootNode = nullptr;
};

void GatorAVL::insertNode(string name, int id) {
    GatorNode *newNode = new GatorNode(name, id);
    
    if (this->rootNode) {
        /* iterate though nodes until finding a case where 1) newNode < curNode & leftChild free or 2) newNode > curNode & rightChild free */
        GatorNode *curNode = this->rootNode;
        string nodeStatus = "";
        int iterations = 0; /* used to recalculate heights */

        while (curNode) {
            iterations++;
            if (newNode->getId() < curNode->getId()) {
                if (curNode->getLeftChild() == nullptr) {
                    curNode->setLeftChild(newNode);
                    newNode->setParent(curNode);
                    nodeStatus = "left";
                    break;
                }
                else {
                    curNode = curNode->getLeftChild();
                }
            }
            else if (newNode->getId() > curNode->getId()) {
                if (curNode->getRightChild() == nullptr) {
                    curNode->setRightChild(newNode);
                    newNode->setParent(curNode);
                    nodeStatus = "right";
                    break;
                }
                else {
                    curNode = curNode->getRightChild();
                }
            }
            else {
                nodeStatus = "duplicate";
                break;
            }
        }


        /*
            When a node is inserted, balance factors for all nodes are recalculated, starting with the newly added node.
            The recalc function will recursively 1) rebalance is BF out of bounds and then 2) set BF's for all parents ascending up the tree
        */
        if (nodeStatus == "left" || nodeStatus == "right") {
            this->recalcBalanceFactors(newNode);
            cout << "successful" << endl;
            return;
        }
        else {
            cout << "unsuccessful" << endl;
            return;
        }
    }
    else {
        this->rootNode = newNode;
        cout << "successful" << endl;
        return;
    }


    return;
}

void GatorAVL::recalcBalanceFactors(GatorNode* curNode) {
    if (curNode->getBalanceFactor() < -1 || curNode->getBalanceFactor() > 1) {
        this->rebalanceTree(curNode);
        return;
    }

    if (curNode->getParent()) {
        if (curNode->getParent()->getLeftChild() && curNode->getParent()->getLeftChild()->getId() == curNode->getId()) {
            curNode->getParent()->setBalanceFactor(curNode->getParent()->getBalanceFactor() - 1);
        }

        if (curNode->getParent()->getRightChild() && curNode->getParent()->getRightChild()->getId() == curNode->getId()) {
            curNode->getParent()->setBalanceFactor(curNode->getParent()->getBalanceFactor() + 1);
        }

        if (curNode->getParent()->getBalanceFactor() != 0) {
            this->recalcBalanceFactors(curNode->getParent());
        }
    }
}

void GatorAVL::rebalanceTree(GatorNode* rootNode) {
    if (rootNode->getBalanceFactor() > 0) {
        if (rootNode->getRightChild()->getBalanceFactor() < 0) {
            this->rightRot(rootNode->getRightChild());
            this->leftRot(rootNode);
        }
        else {
            this->leftRot(rootNode);
        }
    }
    else if (rootNode->getBalanceFactor() < 0) {
        if (rootNode->getLeftChild()->getBalanceFactor() > 0) {
            this->leftRot(rootNode->getLeftChild());
            this->rightRot(rootNode);
        }
        else {
            this->rightRot(rootNode);
        }
    }
}

GatorNode* GatorAVL::removeNode(GatorNode* curNode, int id,  bool& removeSuccess) {
    if (!curNode) return curNode;
    else if (id < curNode->getId()) curNode->setLeftChild(this->removeNode(curNode->getLeftChild(), id, removeSuccess));
    else if (id > curNode->getId()) curNode->setRightChild(this->removeNode(curNode->getRightChild(), id, removeSuccess));
    else {
        removeSuccess = true;
        if (curNode->getLeftChild() == nullptr && curNode->getRightChild() == nullptr) { /* Node has no children */
            if (curNode->getParent()) {
                if (curNode->getParent()->getLeftChild()) {
                    if (curNode->getParent()->getLeftChild()->getId() == curNode->getId()) {
                        curNode->getParent()->setLeftChild(nullptr);
                        return nullptr;
                    }
                }
                if (curNode->getParent()->getRightChild()) {
                    if (curNode->getParent()->getRightChild()->getId() == curNode->getId()) {
                        curNode->getParent()->setRightChild(nullptr);
                        return nullptr;
                    }
                }
            }
        }
        else if (curNode->getLeftChild() == nullptr) { /* Node only has one child */
            GatorNode* temp = curNode;
            curNode = curNode->getRightChild();
            curNode->setParent(temp->getParent());
        }
        else if (curNode->getRightChild() == nullptr) { /* Node only has one child */
            GatorNode* temp = curNode;
            curNode = curNode->getLeftChild();
            curNode->setParent(temp->getParent());
        }
        else { /* Node has both children */
            GatorNode* temp = this->findSuccessor(curNode->getRightChild());
            curNode->setId(temp->getId());
            curNode->setName(temp->getName());
            curNode->setRightChild(this->removeNode(curNode->getRightChild(), temp->getId(), removeSuccess));
            curNode->getRightChild()->setParent(curNode);
        }
    }

    return curNode;
}

GatorNode* GatorAVL::findSuccessor(GatorNode* curNode) {
    GatorNode* curTemp = curNode;
    while (curTemp->getLeftChild()) {
        curTemp = curTemp->getLeftChild();
    }
    return curTemp;
}

void GatorAVL::searchNode(GatorNode* curNode, string name, int& matches) {
    if (curNode == nullptr) return;
    
    if (curNode->getName() == name) {
        matches++;
        cout << curNode->getId() << endl;
    }

    this->searchNode(curNode->getLeftChild(), name, matches);
    this->searchNode(curNode->getRightChild(), name, matches);
}

void GatorAVL::searchNode(int id) {
    GatorNode *curNode = this->rootNode;
    while (curNode) {
        if (curNode->getId() == id) {
            cout << curNode->getName() << endl;
            return;
        }
        else if (curNode->getId() > id) {
            curNode = curNode->getLeftChild();
        }
        else {
            curNode = curNode->getRightChild();
        }
    }
    cout << "unsuccessful" << endl;
}

GatorNode* GatorAVL::inorderRemove(GatorNode* curNode, int& num, int& traversals, bool& removeSuccess) {
    if (curNode == nullptr) return curNode;
    
    this->inorderRemove(curNode->getLeftChild(), num, traversals, removeSuccess);
    traversals++;
    if (traversals == num) {
        removeSuccess = true;
        if (curNode->getLeftChild() == nullptr && curNode->getRightChild() == nullptr) { /* Node has no children */
            if (curNode->getParent()) {
                if (curNode->getParent()->getLeftChild()->getId() == curNode->getId()) {
                    curNode->getParent()->setLeftChild(nullptr);
                }
                else if (curNode->getParent()->getRightChild()->getId() == curNode->getId()) {
                    curNode->getParent()->setRightChild(nullptr);
                }
            }
        }
        else if (curNode->getLeftChild() == nullptr) { /* Node only has one child */
            GatorNode* temp = curNode;
            curNode = curNode->getRightChild();
            curNode->setParent(temp->getParent());
        }
        else if (curNode->getRightChild() == nullptr) { /* Node only has one child */
            GatorNode* temp = curNode;
            curNode = curNode->getLeftChild();
            curNode->setParent(temp->getParent());
        }
        else { /* Node has both children */
            GatorNode* temp = this->findSuccessor(curNode->getRightChild());
            curNode->setId(temp->getId());
            curNode->setName(temp->getName());
            curNode->setRightChild(this->inorderRemove(curNode->getRightChild(), num, traversals, removeSuccess));
            curNode->getRightChild()->setParent(curNode);
        }
    }
    this->inorderRemove(curNode->getRightChild(), num, traversals, removeSuccess);

    return curNode;
}

/* print functions */
void GatorAVL::inorderPrint(GatorNode* rootNode, string& outputStr) {
    if (rootNode == nullptr) return;
    
    this->inorderPrint(rootNode->getLeftChild(), outputStr);
    outputStr = outputStr + rootNode->getName() + ", ";
    this->inorderPrint(rootNode->getRightChild(), outputStr);
}

void GatorAVL::preorderPrint(GatorNode* rootNode, string& outputStr) {
    if (rootNode == nullptr) return;
    
    outputStr = outputStr + rootNode->getName() + ", ";
    this->preorderPrint(rootNode->getLeftChild(), outputStr);
    this->preorderPrint(rootNode->getRightChild(), outputStr);
}

void GatorAVL::postorderPrint(GatorNode* rootNode, string& outputStr) {
    if (rootNode == nullptr) return;
    
    this->postorderPrint(rootNode->getLeftChild(), outputStr);
    this->postorderPrint(rootNode->getRightChild(), outputStr);
    outputStr = outputStr + rootNode->getName() + ", ";
}

void GatorAVL::levelCntPrint() {
    int levelCnt = 0;

    GatorNode *curNode = this->rootNode;
    if (!curNode) {
        cout << 0 << endl;
        return;
    }

    levelCnt = getLevelCount(curNode, 1);
    cout << levelCnt << endl;
}


/* balance functions */
void GatorAVL::leftRot(GatorNode* node) {
    GatorNode* newNode = node->getRightChild();
    node->setRightChild(newNode->getLeftChild());

    if (newNode->getLeftChild()) {
        newNode->getLeftChild()->setParent(node);
    }
    newNode->setParent(node->getParent());

    if (node->getParent() == nullptr) {
        this->rootNode = newNode;
    }
    else if (node == node->getParent()->getLeftChild()) {
        node->getParent()->setLeftChild(newNode);
    }
    else {
        node->getParent()->setRightChild(newNode);
    }

    newNode->setLeftChild(node);
    node->setParent(newNode);

    node->setBalanceFactor(calcBalanceFactor(node, 0));
    newNode->setBalanceFactor(calcBalanceFactor(newNode, 0));
}

void GatorAVL::rightRot(GatorNode *node) {
    GatorNode* newNode = node->getLeftChild();
    node->setLeftChild(newNode->getRightChild());

    if (newNode->getRightChild()) {
        newNode->getRightChild()->setParent(node);
    }
    newNode->setParent(node->getParent());

    if (node->getParent() == nullptr) {
        this->rootNode = newNode;
    }
    else if (node == node->getParent()->getRightChild()) {
        node->getParent()->setRightChild(newNode);
    }
    else {
        node->getParent()->setLeftChild(newNode);
    }

    newNode->setRightChild(node);
    node->setParent(newNode);

    node->setBalanceFactor(calcBalanceFactor(node, 0));
    newNode->setBalanceFactor(calcBalanceFactor(newNode, 0));
}


/* helper functions */
int GatorAVL::getLevelCount(GatorNode *curNode, int level) {
    if (!curNode) return level - 1;

    int leftLevel = getLevelCount(curNode->getLeftChild(), level + 1);
    int rightLevel = getLevelCount(curNode->getRightChild(), level + 1);

    return max(leftLevel, rightLevel);
}

int GatorAVL::calcBalanceFactor(GatorNode *curNode, int level) {
    if (!curNode) return level - 1;

    int leftLevel = getLevelCount(curNode->getLeftChild(), level + 1);
    int rightLevel = getLevelCount(curNode->getRightChild(), level + 1);

    return rightLevel - leftLevel;
}

void GatorAVL::setRootNode(GatorNode *node) {
    this->rootNode = node;
}

GatorNode* GatorAVL::getRootNode() {
    return this->rootNode;
}