#include <string>

class GatorNode {
    private:
        GatorNode* parent;
        GatorNode* leftChild;
        GatorNode* rightChild;
        int id;
        int balanceFactor;
        std::string name;
    public:
        GatorNode();
        GatorNode(std::string name, int id);

        /* helper functions */
        int getId();
        void setId(int id);
        std::string getName();
        void setName(std::string name);
        int getBalanceFactor();
        void setBalanceFactor(int bf);
        GatorNode* getLeftChild();
        GatorNode* getRightChild();
        GatorNode* getParent();
        void setParent(GatorNode* parent);
        void setLeftChild(GatorNode* child);
        void setRightChild(GatorNode* child);
};