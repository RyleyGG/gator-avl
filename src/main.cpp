#include <iostream>
#include <string>
#include "GatorAVL.h"
using namespace std;

int main(int argc, char *argv[]) {
    GatorAVL avlTree = GatorAVL();
    GatorNode* rootNode = nullptr;
    avlTree.setRootNode(rootNode);

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

            bool removeSuccess = false;
            avlTree.removeNode(avlTree.getRootNode(), id, removeSuccess);
            if (removeSuccess) {
                cout << "successful" << endl;
            }
            else {
                cout << "unsuccessful" << endl;
            }
        }
        else if (firstWord == "search") {
            string searcher;
            searcher = cmd.substr(spacePos + 1, cmd.length());

            string::const_iterator it = searcher.begin();
            while (it != searcher.end() && isdigit(*it)) ++it;
            
            if (!searcher.empty() && it == searcher.end()) {
                int searchInt = stoi(searcher);
                avlTree.searchNode(searchInt);
            }
            else {
                searcher = searcher.substr(1, searcher.length() - 2);
                int matches = 0;
                avlTree.searchNode(avlTree.getRootNode(), searcher, matches);

                if (matches == 0) {
                    cout << "unsuccessful" << endl;
                }
            }
        }
        else if (firstWord == "printInorder") {
            string outputStr = "";
            avlTree.inorderPrint(avlTree.getRootNode(), outputStr);
            outputStr = outputStr.substr(0, outputStr.length() - 2);
            cout << outputStr << endl;
        }
        else if (firstWord == "printPreorder") {
            string outputStr = "";
            avlTree.preorderPrint(avlTree.getRootNode(), outputStr);
            outputStr = outputStr.substr(0, outputStr.length() - 2);
            cout << outputStr << endl;
        }
        else if (firstWord == "printPostorder") {
            string outputStr = "";
            avlTree.postorderPrint(avlTree.getRootNode(), outputStr);
            outputStr = outputStr.substr(0, outputStr.length() - 2);
            cout << outputStr << endl;
        }
        else if (cmd == "printLevelCount") {
            avlTree.levelCntPrint();
        }
        else if (firstWord == "removeInorder") {
            int removeNum;
            int traversals = -1;
            bool removeSuccess = false;
            string removeStr;

            removeStr = cmd.substr(spacePos, cmd.length());
            try {
                removeNum = stoi(removeStr);
            }
            catch(const invalid_argument e) {
                cout << "unsuccessful" << endl;
                continue;
            }

            avlTree.inorderRemove(avlTree.getRootNode(), removeNum, traversals, removeSuccess);
            if (removeSuccess) {
                cout << "successful" << endl;
            }
            else {
                cout << "unsuccessful" << endl;
            }
        }
        else {
            cout << "unsuccessful8" << endl;
        }
    }

    return 0;
}