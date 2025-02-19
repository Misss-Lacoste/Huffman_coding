#pragma once
#include "Node.h"

#ifndef COMPARATOR_H
#define COMPARATOR_H

struct Comparator {
    bool operator() (Node *left, Node *right) const {
        return left->value < right->value;
    }
};

#endif