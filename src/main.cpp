#include <iostream>
#include <string>
#include "GatorAVL.h"
using namespace std;

int main(int argc, char *argv[]) {
    GatorAVL avlTree = GatorAVL();

    cout << "Enter number of commands you will execute: ";
    int commandCnt;
    cin >> commandCnt;
    cin.ignore(1000, '\n');
    

    for (int i = 0; i < commandCnt; i++) {
        cout << "Enter command: ";
        string cmd, firstWord;
        getline(cin, cmd);
        size_t spacePos = cmd.find(' ');
        firstWord = cmd.substr(0, spacePos);

        if (firstWord == "insert") {
            string name, idStr;
            int id;
            name = cmd.substr(spacePos + 1, cmd.length() - 1);
            size_t nameEndPos = cmd.find("\" ");
            if (nameEndPos == string::npos) {
                cout << "unsuccessful5" << endl;
                continue;
            }

            name = cmd.substr(spacePos + 2, nameEndPos - (spacePos + 2));
            idStr = cmd.substr(nameEndPos + 2), cmd.length();
            try {
                id = stoi(idStr);
            }
            catch(const invalid_argument e) {
                cout << "unsuccessful6" << endl;
                continue;
            }

            avlTree.insertNode(name, id);
        }
        else if (firstWord == "remove") {
            int id;
            string idStr;

            idStr = cmd.substr(spacePos, cmd.length());
            try {
                id = stoi(idStr);
            }
            catch(const invalid_argument e) {
                cout << "unsuccessful" << endl;
                continue;
            }

            avlTree.removeNode(id);
        }
        else if (firstWord == "search") {
            string searcher;
            searcher = cmd.substr(spacePos, cmd.length());

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
        else if (firstWord == "printInorder") {
            avlTree.inorderPrint(avlTree.getRootNode());
        }
        else if (firstWord == "printPreorder") {
            avlTree.preorderPrint(avlTree.getRootNode());
        }
        else if (firstWord == "printPostorder") {
            avlTree.postorderPrint(avlTree.getRootNode());
        }
        else if (cmd == "printLevelCount") {
            avlTree.levelCntPrint();
        }
        else if (firstWord == "removeInorder") {
            int removeNum;
            string removeStr;

            removeStr = cmd.substr(spacePos, cmd.length());
            try {
                removeNum = stoi(removeStr);
            }
            catch(const invalid_argument e) {
                cout << "unsuccessful" << endl;
                continue;
            }

            avlTree.inorderRemove(removeNum);
        }
        else {
            cout << "unsuccessful8" << endl;
        }
    }

    return 0;
}