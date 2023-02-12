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
    public:
        /* main methods for executing input commands */
        GatorAVL();
        void insertNode(std::string name, int id);
        void removeNode(int id);
        void searchNode(int id);
        void searchNode(std::string name);
        void inorderPrint(GatorNode* rootNode);
        void preorderPrint(GatorNode* rootNode);
        void postorderPrint(GatorNode* rootNode);
        void levelCntPrint();
        void inorderRemove(int num);

        /* helper functions */
        GatorNode* getRootNode();
};