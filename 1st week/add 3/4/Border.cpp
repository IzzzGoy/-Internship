//
// Created by Alex on 30.07.2020.
//

#include <iostream>
#include "Border.h"
#include "Value.h"

Border::Border(NodeType t) {
    if (t == NodeType::BEGIN) {
        prev = nullptr;
    } else if (t == NodeType::END) {
        next = nullptr;
    }
    type = t;
}

void Border::Simplify() {
    if (type == NodeType::BEGIN) {
        Node *it = next;
        while (it->type != NodeType::END) {
            if (it->next->type == NodeType::OPEN_BRACKET) {
                it->next->Simplify();
            }
            if (it->type == NodeType::OPERATION_HIGH_PRIORITY) {
                it = it->next;
                it->prev->Simplify();
            } else {
                it = it->next;
            }
        }
        it->Simplify();
        return;
    } else if (type == NodeType::END) {
        Node *it = prev;
        while (it->type != NodeType::BEGIN) {
            if (it->type == NodeType::OPERATION_LOW_PRIORITY) {
                it = it->prev;
                it->next->Simplify();
            } else {
                it = it->prev;
            }
        }
        cout << dynamic_cast<Value *>(it->next)->value << endl;
        return;
    }
}
