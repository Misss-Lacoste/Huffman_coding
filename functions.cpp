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

void build_table(Node *root, std::vector<bool>& code, std::map<char, std::vector<bool> >& table) {
    if (root -> left != nullptr) {
        code.push_back(0);
        build_table(root -> left, code, table);
        code.pop_back(); //remove 0 after exploring the left subtree
    }

    if (root -> right != nullptr) {
        code.push_back(1);
        build_table(root -> right, code, table);
        code.pop_back(); //аналогично remove 1 after the left subtree
    }

    if (root->letter) {
        table[root->letter] = code;
    }

    //code.pop_back(); such piece of code has become unnecessary
}

void frequency(std::map<char, int> &map, std::string str) {
    for (int i = 0; i < str.length(); i++) {
        char c = str[i];
        map[c]++;
    }
}

void build_map( std::list<Node *> &list, std::map<char, int> &map) {
    std::map<char, int>::iterator i;
    for (i = map.begin(); i != map.end(); i++) {
        Node *p = new Node;
        p->letter = i->first;
        p->value = i->second;
        list.push_back(p);
    }
}

void print_table(std::map<char, std::vector<bool>> table) {
    std::map<char, std::vector<bool>>::iterator i;
    for (i = table.begin(); i != table.end(); i++) {
        std::cout << i->first << " : ";
        for (int j = 0; j < i->second.size(); j++) {
            std::cout << i->second[j];
        }
        std::cout << std::endl;
    }
}


