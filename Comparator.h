#pragma once
#include "Node.h"

struct Comparator {
    bool operator() (Node *left, Node *right) const {
        return left->value > right->value;
    }
};
