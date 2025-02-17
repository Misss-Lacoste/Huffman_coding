#include "Node.h"
#include "functions.cpp"
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
    return 0;
}
