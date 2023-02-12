#include <string>

class GatorNode {
    private:
        GatorNode* parent;
        GatorNode* leftChild;
        GatorNode* rightChild;
        int id;
        std::string name;
    public:
        GatorNode();
        GatorNode(std::string name, int id);

        /* helper functions */
        int getId();
        std::string getName();
        GatorNode* getLeftChild();
        GatorNode* getRightChild();
        GatorNode* getParent();
        void setParent(GatorNode* parent);
        void setLeftChild(GatorNode* child);
        void setRightChild(GatorNode* child);
};