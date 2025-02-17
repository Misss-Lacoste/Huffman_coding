#include "Node.h"
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
    for (int i = 0; i < str.length(); i++) {
        char c = str[i];
        map[c]++;
    }

    std::list<Node*> list;

    std::map<char, int>::iterator i;
    for (i = map.begin(); i != map.end(); i++) {
        Node *p = new Node;
        p->letter = i->first;
        p->value = i->second;
        list.push_back(p);
    }

    while (list.size() != 1) {
        list.sort();

    }
    return 0;
}