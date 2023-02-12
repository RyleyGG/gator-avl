#include <string>
#include "GatorNode.h"

class GatorAVL {
    private:
        /* class attributes */
        GatorNode* rootNode;

        /* balance functions */
        void balanceTree();
        void subtreeHeight(GatorNode* rootNode);
        int balanceDiff(GatorNode* leftNode, GatorNode* rightNode);
        void leftRot();
        void rightRot();
        void leftRightRot();
        void rightLeftRot();
    public:
        /* main methods for executing input commands */
        GatorAVL();
        bool insertNode(std::string name, int id);
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