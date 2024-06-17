#ifndef BINARY_TREE_NODE_H
#define BINARY_TREE_NODE_H

class BinaryTreeNode {
public:
    char data;
    long long int frequency;
    BinaryTreeNode* left;
    BinaryTreeNode* right;

    BinaryTreeNode(char data, int frequency) {
        this->data = data;
        this->frequency = frequency;
        left = nullptr;
        right = nullptr;
    }
    char getdata() {
        return data;
    }
    long long int getfrequency() {
        return frequency;
    }
};

#endif // BINARY_TREE_NODE_H
