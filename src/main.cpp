#include <iostream>
#include <string>
#include "GatorAVL.h"
using namespace std;

int main(int argc, char *argv[]) {
    GatorAVL avlTree = GatorAVL();

    cout << "Enter number of commands you will execute: ";
    int commandCnt;
    cin >> commandCnt;
    

    for (int i = 0; i < commandCnt; i++) {
        cout << "Enter command: ";
        string cmd;
        cin >> cmd;

        if (cmd == "insert") {
            string name;
            int id;
            cin >> name >> id;
            name = name.substr(1, name.length() - 2);

            avlTree.insertNode(name, id);
        }
        else if (cmd == "remove") {
            int id;
            cin >> id;

            avlTree.removeNode(id);
        }
        else if (cmd == "search") {
            string searcher;
            cin >> searcher;
            string::const_iterator it = searcher.begin();
            while (it != searcher.end() && isdigit(*it)) ++it;
            
            if (!searcher.empty() && it == searcher.end()) {
                int searchInt = stoi(searcher);
                avlTree.searchNode(searchInt);
            }
            else {
                searcher = searcher.substr(1, searcher.length() - 2);
                avlTree.searchNode(searcher);
            }
        }
        else if (cmd == "printInorder") {
            avlTree.inorderPrint();
        }
        else if (cmd == "printPreorder") {
            avlTree.preorderPrint();
        }
        else if (cmd == "printPostorder") {
            avlTree.postorderPrint();
        }
        else if (cmd == "printLevelCount") {
            avlTree.levelCntPrint();
        }
        else if (cmd == "removeInorder") {
            int removeNum;
            cin >> removeNum;

            avlTree.inorderRemove(removeNum);
        }
    }

    return 0;
}