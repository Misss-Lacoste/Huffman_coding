#include "Node.h"
#include "functions.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>


std::vector<bool> code;
std::map<char, std::vector<bool> > table;


int main() {
    std::string str = "it is my striiiiing!!!!";

    std::map<char, int> map;
    frequency(map, str);

    std::list<Node*> list;

    build_map(list, map);

    Node *root = create_tree(list);
    build_table(root, code, table);

    for (int i = 0; i < str.length(); i++) {
        char c = str[i];
        std::vector<bool> v = table[c];

        for (int j = 0; j < v.size(); j++) {
            std::cout << v[j];
        }
    }

    std::cout << std::endl;

    print_table(table);
    
    // IMPORTANT:  Memory cleanup to prevent memory leaks

    // Add root to list
    std::list<Node*> nodesToDelete;
    nodesToDelete.push_back(root);

    while(!nodesToDelete.empty()){
        Node* current = nodesToDelete.front();
        nodesToDelete.pop_front();

        if(current->left){
            nodesToDelete.push_back(current->left);
        }
        if(current->right){
            nodesToDelete.push_back(current->right);
        }
        delete current;
    }
    return 0;

}
