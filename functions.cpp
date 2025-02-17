#include "functions.h"
#include <list>
#include <vector>
#include <map>
#include <iostream>
#include "Comparator.h"

Node *create_tree(std::list<Node *> &nodes) {
    while (nodes.size() != 1) {
        nodes.sort(Comparator());

        Node *childLeft = nodes.front();
        nodes.pop_front();
        Node *childRight = nodes.front();
        nodes.pop_front();

        Node *parent = new Node(childLeft, childRight);
        nodes.push_back(parent);
    }
    return nodes.front();
}

void build_map(Node *root, std::vector<bool>& code, std::map<char, std::vector<bool> >& table) {
    if (root -> left != nullptr) {
        code.push_back(0);
        build_map(root -> left, code, table);
    }

    if (root -> right != nullptr) {
        code.push_back(1);
        build_map(root -> right, code, table);
    }

    if (root->letter) {
        table[root->letter] = code;
    }

    code.pop_back();
}