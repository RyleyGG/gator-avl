#include <string>
#include "GatorNode.h"

class GatorAVL {
    private:
        /* class attributes */
        GatorNode* rootNode;

        /* balance functions */
        void recalcBalanceFactors(GatorNode* curNode);
        void rebalanceTree(GatorNode* rootNode);
        void leftRot(GatorNode* node);
        void rightRot(GatorNode* node);

        /* helper functions */
        int getLevelCount(GatorNode *curNode, int level);
        GatorNode* findSuccessor(GatorNode *curNode);
    public:
        /* main methods for executing input commands */
        GatorAVL();
        void insertNode(std::string name, int id);
        GatorNode* removeNode(GatorNode* curNode, int id, bool& removeSuccess);
        void searchNode(int id);
        void searchNode(GatorNode* curNode, std::string name, int& matches);
        void inorderPrint(GatorNode* rootNode, std::string& outputStr);
        void preorderPrint(GatorNode* rootNode, std::string& outputStr);
        void postorderPrint(GatorNode* rootNode, std::string& outputStr);
        void levelCntPrint();
        GatorNode* inorderRemove(GatorNode* curNode, int& num, int& traversals, bool& removeSuccess);

        /* helper functions */
        void setRootNode(GatorNode* node);
        GatorNode* getRootNode();
};