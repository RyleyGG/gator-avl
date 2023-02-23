#include <iostream>
#include <string>
#include "GatorAVL.h"
using namespace std;

int main(int argc, char *argv[]) {
    GatorAVL avlTree = GatorAVL();
    GatorNode* rootNode = nullptr;
    avlTree.setRootNode(rootNode);

    int commandCnt;
    cin >> commandCnt;
    cin.ignore(1000, '\n');
    

    for (int i = 0; i < commandCnt; i++) {
        string cmd, firstWord;
        getline(cin, cmd);
        size_t spacePos = cmd.find(' ');
        firstWord = cmd.substr(0, spacePos);

        if (firstWord == "insert") {
            string name, idStr;
            int id;

            /* Verifying integrity of name */
            name = cmd.substr(spacePos + 1, cmd.length() - 1); /* includes whole command except for first word + first space */
            size_t nameEndPos = cmd.find("\" ");
            if (nameEndPos == string::npos) { /* if no quotes are found, exit */
                cout << "unsuccessful" << endl;
                continue;
            }

            /* if number of quotes != 2, exit */
            int quoteCnt = 0;
            for (int i = 0; i < cmd.length(); i++) {
                if (cmd[i] == '"') {
                    quoteCnt++;
                }
            }
            if (quoteCnt != 2) {
                cout << "unsuccessful" << endl;
                continue;
            }

            name = cmd.substr(spacePos + 2, nameEndPos - (spacePos + 2)); /* now includes solely the name, w/o quotes */
            /* if there is a space at the beginning or end of the name, exit */
            /* exclude cases where name is empty, as this should be accepted */
            size_t spacePos = name.find(' ');
            if ((spacePos == 0 || spacePos == name.length() - 1) && name.length() != 0) {
                cout << "unsuccessful" << endl;
                continue;
            }

            /* if name contains non-alpha or non-space character, exit */
            bool badCharFound = false;
            for (int i = 0; i < name.length(); i++) {
                if (!isspace(name[i]) && !isalpha(name[i])) {
                    badCharFound = true;
                    break;
                }
            }
            if (badCharFound) {
                cout << "unsuccessful" << endl;
                continue;
            }

            idStr = cmd.substr(nameEndPos + 2), cmd.length();
            if (idStr.length() != 8) {
                cout << "unsuccessful" << endl;
                continue;
            }
            try {
                id = stoi(idStr);
            }
            catch(const invalid_argument e) {
                cout << "unsuccessful" << endl;
                continue;
            }

            avlTree.insertNode(name, id);
        }
        else if (firstWord == "remove") {
            int id;
            string idStr;

            idStr = cmd.substr(spacePos + 1, cmd.length());
            if (idStr.length() != 8) {
                cout << "unsuccessful" << endl;
                continue;
            }
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
                if (searcher.length() != 8) {
                    cout << "unsuccessful" << endl;
                    continue;
                }
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
            cout << "unsuccessful" << endl;
        }
    }

    return 0;
}