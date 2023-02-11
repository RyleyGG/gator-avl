#include <string>
#include "GatorNode.h"

class GatorAVL {
    private:
        /* class attributes */
        GatorNode* rootNode;

        /* helper functions */
        void balanceTree();
    public:
        /* main methods for executing input commands */
        GatorAVL();
        void insertNode(std::string name, int id);
        void removeNode(int id);
        void searchNode(int id);
        void searchNode(std::string name);
        void inorderPrint();
        void preorderPrint();
        void postorderPrint();
        void levelCntPrint();
        void inorderRemove(int num);
};