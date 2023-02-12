#include <iostream>
#include <string>
#include "GatorAVL.h"
using namespace std;

GatorAVL::GatorAVL() {
    this->rootNode = nullptr;
};

bool GatorAVL::insertNode(string name, int id) {
    /* first, validate input */
    size_t spacePos = name.find(' ');
    if (spacePos == string::npos || spacePos == 0 || spacePos == name.length() - 1) {
        cout << "unsuccessful1" << endl;
        return false;
    }
    for (int i = 0; i < name.length(); i++) {
        if (i != spacePos && !isalpha(name[i])) {
            cout << "unsuccessful2" << endl;
            return false;
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
        return false;
    }

    /* secondly, insert node into tree */
    GatorNode *newNode = new GatorNode(name, id);
    
    /* check for easy initial case of root node being empty */
    if (this->rootNode) {
        /* iterate though nodes until finding a case where 1) newNode < curNode & leftChild free or 2) newNode > curNode & rightChild free */
        GatorNode *curNode = this->rootNode;
        bool nodeSet = false;

        while (curNode) {
            if (newNode->getId() < curNode->getId()) {
                if (curNode->getLeftChild() == nullptr) {
                    curNode->setLeftChild(newNode);
                    newNode->setParent(curNode);
                    nodeSet = true;
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
                    nodeSet = true;
                    break;
                }
                else {
                    curNode = curNode->getRightChild();
                }
            }
        }

        if (nodeSet) {
            cout << "successful" << endl;
            return true;
        }
        else {
            cout << "unsuccessful4" << endl;
            return false;
        }
    }
    else {
        this->rootNode = newNode;
        cout << "successful" << endl;
        return true;
    }


    return true;
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

void GatorAVL::inorderPrint() {
    cout << "Inorder Print called" << endl;
}

void GatorAVL::preorderPrint() {
    cout << "Preorder Print called" << endl;
}

void GatorAVL::postorderPrint() {
    cout << "Postorder Print called" << endl;
}

void GatorAVL::levelCntPrint() {
    cout << "Level Count Print called" << endl;
}

void GatorAVL::inorderRemove(int num) {
    cout << "Inorder Remove called" << endl;
}