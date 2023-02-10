#include <string>
#include "GatorNode.h"

class GatorAVL {
    private:
        GatorNode* rootNode;
    public:
        /* main commands */
        void insertNode(std::string name, int id);
        void removeNode(int id);
        void searchNode(int id);
        void searchNode(std::string name);
        void inorderPrint();
        void preorderPrint();
        void postorderPrint();
        void levelCntPrint();
        void inorderRemove(int num);

        /* helper functions */
        void balanceTree();
};