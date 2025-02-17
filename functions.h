#pragma once
#include <list>
#include <vector>
#include <map>
#include <iostream>
#include "Comparator.h"

#include "Node.h"

Node *create_tree(std::list<Node *> &nodes);

void build_map(Node *root, std::vector<bool>& code, std::map<char, std::vector<bool> >& table);
