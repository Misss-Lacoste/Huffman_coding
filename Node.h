#pragma once

class Node {
public:
    int value;
    char letter;
    Node* left, * right;
    Node() : value(0), letter(0), left(nullptr), right(nullptr) {}
    Node(Node* left, Node* right) {
        this->left = left;
        this->right = right;
        this->letter = 0;
        value = this->left->value + this->right->value;
    }
};
