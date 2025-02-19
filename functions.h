#pragma once
#include <list>
#include <vector>
#include <map>
#include <string>
#include "Node.h"

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

Node *create_tree(std::list<Node *> &nodes);
void build_table(Node *root, std::vector<bool>& code, std::map<char, std::vector<bool> >& table);\
void frequency(std::map<char, int> &map, std::string str);
void build_map(std::list<Node *> &list, std::map<char, int> &map);
void print_table(std::map<char, std::vector<bool> > table);

#endif