//
// Created by Alex on 30.07.2020.
//

#include "Node.h"

void Node::addNode(Node *newNode) {
    if (newNode->type != NodeType::BEGIN || newNode->type != NodeType::END) {
        next = newNode;
        newNode->prev = this;
    }
}

Node::~Node() {
    next = nullptr;
    prev = nullptr;
}


