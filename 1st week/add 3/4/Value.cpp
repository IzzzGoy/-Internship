//
// Created by Alex on 30.07.2020.
//

#include "Value.h"

void Value::Simplify() {
    if (prev->type == NodeType::OPEN_BRACKET && next->type == NodeType::CLOSE_BRACKET) {
        Node *tmp = prev;
        prev = prev->prev;
        tmp->prev->next = tmp->next;
        tmp->next = nullptr;
        tmp->prev = nullptr;
        delete tmp;

        tmp = next;
        next = tmp->next;
        next->prev = tmp->prev;
        tmp->next = nullptr;
        tmp->prev = nullptr;
        delete tmp;
    }
}

Value::Value(double value) : value(value) {
    type = NodeType::NUMBER;
}
