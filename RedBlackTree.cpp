#include "RedBlackTree.h"
#include <iostream>

using namespace std;

RedBlackTree::RedBlackTree() {
    root = nullptr;
    numItems = 0;
}

RedBlackTree::RedBlackTree(const RedBlackTree& other) {
    if (other.root == nullptr) {
        root = nullptr;
    }

    numItems = other.numItems;
    root = new RBTNode;
    root->data = other.root->data;
    root->color = COLOR_BLACK;
    RBTNode* otherTmp = other.root;
    RBTNode* tmp = root;
    while (otherTmp != nullptr) {
        if (otherTmp->left != nullptr && tmp->left == nullptr) {
            RBTNode* node = new RBTNode;
            node->data = otherTmp->left->data;
            node->color = otherTmp->left->color;
            tmp->left = node;
            node->parent = tmp;

            otherTmp = otherTmp->left;
            tmp = tmp->left;
        }
        else if (otherTmp->right != nullptr && tmp->right == nullptr) {
            RBTNode* node = new RBTNode;
            node->data = otherTmp->right->data;
            node->color = otherTmp->right->color;
            tmp->right = node;
            node->parent = tmp;

            otherTmp = otherTmp->right;
            tmp = tmp->right;
        }
        else {
            otherTmp = otherTmp->parent;
            tmp = tmp->parent;
        }
    }
}

bool RedBlackTree::Contains(int val) {
    RBTNode* tmp = root;
    while (tmp != nullptr) {
        if (val == tmp->data) {
            return true;
        }
        else if (val < tmp->data) {
            tmp = tmp->left;
        }
        else {
            tmp = tmp->right;
        }
    }
    return false;
}

int RedBlackTree::GetMin() {
    if (root == nullptr) {
        throw "NullPointerException: tree is empty";
    }
    RBTNode* tmp = root;

    while (tmp->left != nullptr) {
        tmp = tmp->left;
    }
    return tmp->data;
}

int RedBlackTree::GetMax() {
    if (root == nullptr) {
        throw "NullPointerException: tree is empty";
    }
    RBTNode* tmp = root;

    while (tmp->right != nullptr) {
        tmp = tmp->right;
    }
    return tmp->data;
}

unsigned long long int RedBlackTree::Size() {
    return numItems;
}

string RedBlackTree::ToInfixString(RBTNode* node) const {
    if (node == nullptr) {
        return "";
    }

    string res = "";
    RBTNode* tmp = node;
    res += ToInfixString(tmp->left);
    if (tmp->color == COLOR_BLACK) {
        res += " B";
    }
    else {
        res += " R";
    }
    res += to_string(tmp->data) + " ";
    res += ToInfixString(tmp->right);

    return res;
}

string RedBlackTree::ToPrefixString(RBTNode* node) const {
    if (node == nullptr) {
        return "";
    }

    string res = "";
    RBTNode* tmp = node;
    if (tmp->color == COLOR_BLACK) {
        res += " B";
    }
    else {
        res += " R";
    }
    res += to_string(tmp->data) + " ";
    res += ToPrefixString(tmp->left);
    res += ToPrefixString(tmp->right);

    return res;
}

string RedBlackTree::ToPostfixString(RBTNode* node) const {
    if (node == nullptr) {
        return "";
    }

    string res = "";
    RBTNode* tmp = node;
    res += ToPostfixString(tmp->left);
    res += ToPostfixString(tmp->right);
    if (tmp->color == COLOR_BLACK) {
        res += " B";
    }
    else {
        res += " R";
    }
    res += to_string(tmp->data) + " ";

    return res;
}

void RedBlackTree::Recolor(RBTNode* node) {
    if (node == nullptr) {
        return;
    }

    // color parent black
    if (node->parent != nullptr) {
        node->parent->color = COLOR_BLACK;
    }

    // color parent sibling black
    RBTNode* parentSibling = GetParentSibling(node);
    if (parentSibling != nullptr) {
        parentSibling->color = COLOR_BLACK;
    }

    // color grandparent red
    RBTNode* grandparent = GetGrandparent(node);
    if (grandparent != nullptr) {
        grandparent->color = COLOR_RED;
    }

    // continue recolor starting from the grandparent
    Recheck(grandparent);
}

RBTNode* RedBlackTree::GetGrandparent(RBTNode* node) {
    if (node != nullptr && node->parent != nullptr) {
        return node->parent->parent;
    }
    else {
        return nullptr;
    }
}

RBTNode* RedBlackTree::GetParentSibling(RBTNode* node) {
    RBTNode* grandparent = GetGrandparent(node);
    if (grandparent == nullptr) {
        return nullptr;
    }

    if (grandparent->left == node->parent) {
        return grandparent->right;
    }
    else {
        return grandparent->left;
    }

}

void RedBlackTree::SwapColor(RBTNode* node1, RBTNode* node2) {
    int tmpColor = node1->color;
    node1->color = node2->color;
    node2->color = tmpColor;
}

void RedBlackTree::RotateRight(RBTNode* node) {
    RBTNode* leftChild = node->left;
    RBTNode* leftRightGrandchild = node->left->right;

    // switch child of child to be child
    node->left = leftRightGrandchild;
    if (leftRightGrandchild != nullptr) {
        leftRightGrandchild->parent = node;
    }

    // switch node to be child of child
    leftChild->right = node;

    // if node not root
    if (node->parent != nullptr) {
        if (node->parent->left == node) {
            node->parent->left = leftChild;
        }
        else {
            node->parent->right = leftChild;
        }
        leftChild->parent = node->parent;
    }
    else {
        root = leftChild;
        root->parent = nullptr;
    }
    node->parent = leftChild;
}

void RedBlackTree::RotateLeft(RBTNode* node) {
    RBTNode* rightChild = node->right;
    RBTNode* rightLeftGrandchild = node->right->left;

    // switch child of child to be child
    node->right = rightLeftGrandchild;
    if (rightLeftGrandchild != nullptr) {
        rightLeftGrandchild->parent = node;
    }

    // switch node to be child of child
    rightChild->left = node;

    // if node not root
    if (node->parent != nullptr) {
        if (node->parent->left == node) {
            node->parent->left = rightChild;
        }
        else {
            node->parent->right = rightChild;
        }
        rightChild->parent = node->parent;
    }
    else {
        root = rightChild;
        root->parent = nullptr;
    }
    node->parent = rightChild;
}

void RedBlackTree::Recheck(RBTNode* node) {
    if (node == nullptr) {
        return;
    }

    if (node->parent == nullptr) {
        node->color = COLOR_BLACK;
        return;
    }

    if (node->parent->color == COLOR_BLACK) {
        return;
    }
    else {
        RBTNode* parentSibling = GetParentSibling(node);
        if (parentSibling != nullptr && parentSibling->color == COLOR_RED) {
            // cout << "red sibling" << endl;
            // red sibling case
            Recolor(node);
            if (root->color == COLOR_RED) {
                root->color = COLOR_BLACK;
            }
        }
        else {
            // cout << "null or black sibling" << endl;
            // null or black sibling case
            RBTNode* grandparent = GetGrandparent(node);
            RBTNode* parent = node->parent;
            // left
            if (grandparent->left == parent) {
                // left-left
                if (parent->left == node) {
                    // cout << "left-left" << endl;
                    RotateRight(grandparent);
                    SwapColor(parent, grandparent);
                }
                // left-right
                else {
                    // cout << "left-right" << endl;
                    RotateLeft(parent);
                    RotateRight(grandparent);
                    SwapColor(grandparent, node);
                }
            }
            // right
            else {
                // right-right
                // cout << "right-right" << endl;
                if (parent->right == node) {
                    RotateLeft(grandparent);
                    SwapColor(grandparent, parent);  
                }
                // right-left
                else {
                    // cout << "right-left" << endl;
                    RotateRight(parent);
                    RotateLeft(grandparent);
                    SwapColor(grandparent, node);
                }
            }   
        }
    }
}

// takes about 1-2 microseconds
void RedBlackTree::Insert(int val) {
    // cout << "inserting " << val << endl;
    RBTNode* node = new RBTNode;
    node->data = val;

    // empty tree case
    if (root == nullptr) {
        root = node;
        node->color = COLOR_BLACK;
        numItems++;
        return;
    }
    else {
        node->color = COLOR_RED;
        RBTNode* tmp = root;
        RBTNode* parent;
        while (tmp != nullptr) {
            parent = tmp;
            if (val == tmp->data) {
                return;
            }
            else if (val < tmp->data) {
                tmp = tmp->left;
            }
            else {
                tmp = tmp->right;
            }
        }
        
        // insert node as normal
        if (val < parent->data) {
            parent->left = node;
        }
        else if (val > parent->data) {
            parent->right = node;
        } 
        node->parent = parent;
        numItems++;

        Recheck(node);
    }
}

RBTNode* RedBlackTree::GetSuccessor(RBTNode* node) {
    if (node == nullptr || node->right == nullptr) {
        return nullptr;
    }

    RBTNode* tmp = node->right;
    while (tmp->left != nullptr) {
        tmp = tmp->left;
    }
    return tmp;
}

void RedBlackTree::ReplaceAndDeleteNode(RBTNode* deleteNode, RBTNode* replaceNode) {
    if (deleteNode->parent == nullptr) {
        root = replaceNode;
        replaceNode->parent = nullptr;
    }
    else {
        if (deleteNode->parent->left == deleteNode) {
            deleteNode->parent->left = replaceNode;
        }
        else {
            deleteNode->parent->right = replaceNode;
        }

        replaceNode->parent = deleteNode->parent;
    }
    
    delete deleteNode;
}

RBTNode* RedBlackTree::GetSibling(RBTNode* node) {
    if (node == nullptr) {
        return nullptr;
    }

    if (node->parent->left == node) {
        return node->parent->right;
    }
    else {
        return node->parent->left;
    }
}

void RedBlackTree::FixDoubleBlack(RBTNode* node) {
    if (node == root) {
        node->color = COLOR_BLACK;
        return;
    }

    RBTNode* parent = node->parent;
    RBTNode* sibling = GetSibling(node);
    if (sibling == nullptr) {
        return;
    }
    if (sibling->color == COLOR_BLACK) {
        // sibling has only black children
        if ((sibling->left == nullptr || sibling->left->color == COLOR_BLACK) && (sibling->right == nullptr || sibling->right->color == COLOR_BLACK)) {
            // cout << "only black" << endl;
            sibling->color = COLOR_RED;
            node->color = COLOR_BLACK;
            // parent's color cancels
            if (parent->color == COLOR_RED) {
                parent->color = COLOR_BLACK;
                
                return;
            }
            else {
                parent->color = COLOR_DOUBLE_BLACK;
                FixDoubleBlack(parent);
            }

        }
        // has 1 red, divide case
        else {
            // right
            if (parent->right == sibling) {
                // right right or 2 children
                if (sibling->right != nullptr) {
                    // cout << "right right" << endl;
                    RBTNode* rightChild = sibling->right;
                    RotateLeft(parent);
                    rightChild->color = sibling->color;
                    sibling->color = parent->color;
                    parent->color = COLOR_BLACK;
                    // if (node->isNullNode) {
                    //     parent->left = nullptr;
                    //     delete node;
                    // }
                    // else {
                    //     node->color = COLOR_BLACK;
                    // }
                }
                // right left
                else {
                    // cout << "right left" << endl;
                    RBTNode* leftChild = sibling->left;
                    RotateRight(sibling);
                    SwapColor(leftChild, sibling);
                    RotateLeft(parent);
                    SwapColor(leftChild, parent);
                    sibling->color = COLOR_BLACK;
                    // if (node->isNullNode) {
                    //     parent->left = nullptr;
                    //     delete node;
                    // }
                    // else {
                    //     node->color = COLOR_BLACK;
                    // }
                }
            }
            // left
            else {
                // left left
                if (sibling->left != nullptr) {
                    // cout << "left left" << endl;
                    RBTNode* leftChild = sibling->left;
                    RotateRight(parent);
                    leftChild->color = sibling->color;
                    sibling->color = parent->color;
                    parent->color = COLOR_BLACK;
                    // if (node->isNullNode) {
                    //     parent->right = nullptr;
                    //     delete node;
                    // }
                    // else {
                    //     node->color = COLOR_BLACK;
                    // }
                }
                // left right
                else {
                    // cout << "left right" << endl;
                    RBTNode* rightChild = sibling->right;
                    RotateLeft(sibling);
                    SwapColor(rightChild, sibling);
                    RotateRight(parent);
                    SwapColor(rightChild, parent);
                    sibling->color = COLOR_BLACK;
                    // if (node->isNullNode) {
                    //     parent->right = nullptr;
                    //     delete node;
                    // }
                    // else {
                    //     node->color = COLOR_BLACK;
                    // }
                }
            }
        }
    }
    // sibling color is red
    else {
        // cout << "red sibling" << endl;
        parent->color = COLOR_RED;
        sibling->color = COLOR_BLACK;
        if (parent->left == sibling) {
            RotateRight(parent);
        }
        else {
            RotateLeft(parent);
        }
        FixDoubleBlack(node);
    }
}

RBTNode* RedBlackTree::GetReplaceNode(RBTNode* node) {
    if (node == nullptr) {
        return nullptr;
    }

    if (node->left != nullptr) {
        // cout << "replace w left" << endl;
        return node->left;
    }
    else if (node->right != nullptr) {
        // cout << "replace w right" << endl;
        return node->right;
    }
    else {
        // cout << "replace w null" << endl;
        RBTNode* rep = new RBTNode;
        rep->color = COLOR_BLACK;
        rep->isNullNode = true;
        return rep;
    }
}

void RedBlackTree::DeleteNode(RBTNode* deleteNode) {
    if (deleteNode == nullptr) {
        return;
    }

    RBTNode* replaceNode = GetReplaceNode(deleteNode);

    if (deleteNode->color == COLOR_RED) {
        // cout << "delete node is red " << deleteNode->data << endl;
        replaceNode->color = COLOR_BLACK;
        ReplaceAndDeleteNode(deleteNode, replaceNode);
        if (replaceNode->isNullNode) {
            if (replaceNode->parent->left == replaceNode) {
                replaceNode->parent->left = nullptr;
            }
            else {
                replaceNode->parent->right = nullptr;
            }
            delete replaceNode;
        }
    }
    else if (replaceNode->color == COLOR_RED) {
        // cout << "replace node is red " << replaceNode->data << endl;
        replaceNode->color = COLOR_BLACK;
        ReplaceAndDeleteNode(deleteNode, replaceNode);
        if (replaceNode->isNullNode) {
            if (replaceNode->parent->left == replaceNode) {
                replaceNode->parent->left = nullptr;
            }
            else {
                replaceNode->parent->right = nullptr;
            }
            delete replaceNode;
        }
    }
    else {
        // cout << "double black case" << endl;
        // double black
        replaceNode->color = COLOR_DOUBLE_BLACK;
        ReplaceAndDeleteNode(deleteNode, replaceNode);
        
        FixDoubleBlack(replaceNode);
        if (replaceNode->isNullNode) {
            if (replaceNode->parent->left == replaceNode) {
                replaceNode->parent->left = nullptr;
            }
            else {
                replaceNode->parent->right = nullptr;
            }
            delete replaceNode;
        }
    }
}

// takes about 4-6 microseconds
void RedBlackTree::Remove(int val) {
    if (val == root->data && numItems == 1) {
        // cout << "root is " << root->data << endl;
        delete root;
        root = nullptr;
        numItems = 0;
        return;
    }
    RBTNode* toBeDeleted = nullptr;
    RBTNode* tmp = root;
    while (tmp != nullptr) {
        if (val < tmp->data) {
            tmp = tmp->left;
        }
        else if (val > tmp->data) {
            tmp = tmp->right;
        }
        else {
            toBeDeleted = tmp;
            tmp = nullptr;
        }
    }

    // node does not exist
    if (toBeDeleted == nullptr) {
        return;
    }

    if (toBeDeleted->left != nullptr && toBeDeleted->right != nullptr) {
        // cout << "get successor" << endl;
        RBTNode* successor = GetSuccessor(toBeDeleted);
        // cout << successor->data << endl;
        toBeDeleted->data = successor->data;
        toBeDeleted = successor;
    }

    // cout << "start delete node " << toBeDeleted->data << endl;
    DeleteNode(toBeDeleted);
    numItems--;
}

// void RedBlackTree::DeleteTree(RBTNode* node) {
//     if (node == nullptr) {
//         return;
//     }

//     DeleteTree(node->left);
//     DeleteTree(node->right);

//     Remove(node->data);
// }

RedBlackTree::~RedBlackTree() {
    // if (root == nullptr) {
    //     cout << "null" << endl;
    // }

    while (root != nullptr) {
        Remove(root->data);
        // numItems--;
    }

    // if (root == nullptr) {
    //     root = new RBTNode;
    // }
    // delete root;
    // cout << "end deconstructor" << endl;
}