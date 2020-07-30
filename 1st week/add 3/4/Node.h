//
// Created by Alex on 30.07.2020.
//

#ifndef INC_4_NODE_H
#define INC_4_NODE_H

#include <memory>

using namespace std;

enum class NodeType {
    NUMBER,
    OPERATION_HIGH_PRIORITY,
    OPERATION_LOW_PRIORITY,
    OPEN_BRACKET,
    CLOSE_BRACKET,
    BEGIN,
    END
};

class Node {
public:
    Node *prev;
    Node *next;
    NodeType type;

    virtual void Simplify() = 0;

    void addNode(Node *newNode);

    ~Node();
};


#endif //INC_4_NODE_H
