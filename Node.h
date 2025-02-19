#pragma once

#ifndef NODE_H
#define NODE_H

class Node {
public:
    int value;
    char letter;
    Node *left, *right;
    Node() {}
    Node(Node *left, Node *right) {
        this->left = left;
        this->right = right;
        value = this->left->value + this->right->value;
    }
};

#endif