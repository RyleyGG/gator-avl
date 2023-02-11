#include <iostream>
#include <string>
#include "GatorAVL.h"
using namespace std;

GatorAVL::GatorAVL() {
    this->rootNode = nullptr;
};

void GatorAVL::insertNode(string name, int id) {
    cout << "Insert called" << endl;
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