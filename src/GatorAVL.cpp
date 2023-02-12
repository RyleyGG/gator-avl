#include <iostream>
#include <string>
#include <algorithm>
#include "GatorAVL.h"
using namespace std;

GatorAVL::GatorAVL() {
    this->rootNode = nullptr;
};

void GatorAVL::insertNode(string name, int id) {
    /* first, validate input */
    size_t spacePos = name.find(' ');
    if (spacePos == string::npos || spacePos == 0 || spacePos == name.length() - 1) {
        cout << "unsuccessful1" << endl;
        return;
    }
    for (int i = 0; i < name.length(); i++) {
        if (i != spacePos && !isalpha(name[i])) {
            cout << "unsuccessful2" << endl;
            return;
        }
    }

    int digitCnt = 0;
    int idIter = id;
    while (idIter != 0) {
        idIter = idIter / 10;
        digitCnt++;
    }
    if (digitCnt != 8) {
        cout << "unsuccessful3" << endl;
        return;
    }

    /* secondly, insert node into tree */
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
            else {
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
        }


        /*
            When a node is inserted, balance factors for all nodes are recalculated, starting with the newly added node.
            The recalc function will recursively 1) rebalance is BF out of bounds and then 2) set BF's for all parents ascending up the tree
        */
        if (nodeStatus != "") {
            this->recalcBalanceFactors(newNode);
            cout << "successful" << endl;
            return;
        }
        else {
            cout << "unsuccessful4" << endl;
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
            cout << "RL called" << endl;
            this->rightRot(rootNode->getRightChild());
            this->leftRot(rootNode);
        }
        else {
            cout << "L called" << endl;
            this->leftRot(rootNode);
        }
    }
    else if (rootNode->getBalanceFactor() < 0) {
        if (rootNode->getLeftChild()->getBalanceFactor() > 0) {
            cout << "LR called" << endl;
            this->leftRot(rootNode->getLeftChild());
            this->rightRot(rootNode);
        }
        else {
            cout << "R called" << endl;
            this->rightRot(rootNode);
        }
    }
}

void GatorAVL::removeNode(int id) {
    cout << "Remove called" << endl;
}

void GatorAVL::searchNode(string name) {
    cout << "Search by name called" << endl;
}

void GatorAVL::searchNode(int id) {
    cout << "Search by id called" << endl;
}

void GatorAVL::inorderPrint(GatorNode* rootNode) {
    if (rootNode == nullptr) return;
    
    preorderPrint(rootNode->getLeftChild());
    cout << "Name: " << rootNode->getName() << ", Id: " << rootNode->getId() << endl;
    preorderPrint(rootNode->getRightChild());
}

void GatorAVL::preorderPrint(GatorNode* rootNode) {
    if (rootNode == nullptr) return;
    
    cout << "Name: " << rootNode->getName() << ", Id: " << rootNode->getId() << endl;
    preorderPrint(rootNode->getLeftChild());
    preorderPrint(rootNode->getRightChild());
}

void GatorAVL::postorderPrint(GatorNode* rootNode) {
    if (rootNode == nullptr) return;
    
    preorderPrint(rootNode->getLeftChild());
    preorderPrint(rootNode->getRightChild());
    cout << "Name: " << rootNode->getName() << ", Id: " << rootNode->getId() << endl;
}

void GatorAVL::levelCntPrint() {
    int levelCnt = 0;

    GatorNode *curNode = this->rootNode;
    if (!curNode) {
        cout << "Level Count: " << 0 << endl;
        return;
    }

    levelCnt = getLevelCount(curNode, 1);
    cout << "Level Count: " << levelCnt << endl;
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

    node->setBalanceFactor(node->getBalanceFactor() - 1 - max(0, newNode->getBalanceFactor()));
    newNode->setBalanceFactor(newNode->getBalanceFactor() - 1 + min(0, node->getBalanceFactor()));
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

    node->setBalanceFactor(node->getBalanceFactor() - 1 - max(0, newNode->getBalanceFactor()));
    newNode->setBalanceFactor(newNode->getBalanceFactor() - 1 + min(0, node->getBalanceFactor()));
}

void GatorAVL::inorderRemove(int num) {
    cout << "Inorder Remove called" << endl;
}

int GatorAVL::getLevelCount(GatorNode *curNode, int level) {
    if (!curNode) return level - 1;

    int leftLevel = getLevelCount(curNode->getLeftChild(), level + 1);
    int rightLevel = getLevelCount(curNode->getRightChild(), level + 1);

    return max(leftLevel, rightLevel);
}

GatorNode* GatorAVL::getRootNode() {
    return this->rootNode;
}