#ifndef RBT_H
#define RBT_H
#define COLOR_BLACK 0
#define COLOR_RED 1
#define COLOR_DOUBLE_BLACK 2

#include <string>

using namespace std;

struct RBTNode
{
    int data;
    unsigned short int color;
    RBTNode* left = nullptr;
    RBTNode* right = nullptr;
    RBTNode* parent = nullptr;
    bool isNullNode = false;
};

class RedBlackTree {
    public:
        ~RedBlackTree();
        RedBlackTree();
        RedBlackTree(const RedBlackTree& other);
        void Insert(int val);
        void Remove(int val);
        bool Contains(int val);
        int GetMin();
        int GetMax();
        unsigned long long int Size();
        string ToInfixString() const {return ToInfixString(root);};
        string ToPrefixString() const {return ToPrefixString(root);};
        string ToPostfixString() const {return ToPostfixString(root);};

    private:
        RBTNode* root;
        unsigned long long int numItems;
        string ToInfixString(RBTNode* node) const;
        string ToPrefixString(RBTNode* node) const;
        string ToPostfixString(RBTNode* node) const;
        RBTNode* GetParentSibling(RBTNode* node);
        RBTNode* GetGrandparent(RBTNode* node);
        void Recolor(RBTNode* node);
        void RotateLeft(RBTNode* node);
        void RotateRight(RBTNode* node);
        void SwapColor(RBTNode* node1, RBTNode* node2);
        void Recheck(RBTNode* node);
        RBTNode* GetSuccessor(RBTNode* node);
        void DeleteNode(RBTNode* node);
        void FixDoubleBlack(RBTNode* node);
        void ReplaceAndDeleteNode(RBTNode* deleteNode, RBTNode* replaceNode);
        RBTNode* GetSibling(RBTNode* node);
        RBTNode* GetReplaceNode(RBTNode* node);
        void DeleteTree(RBTNode* node);
};

#endif