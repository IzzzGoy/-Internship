//
// Created by Alex on 30.07.2020.
//

#include "Bracket.h"

Bracket::Bracket(char c) {
    if (c == '(') {
        type = NodeType::OPEN_BRACKET;
    } else if (c == ')') {
        type = NodeType::CLOSE_BRACKET;
    }
}

void Bracket::Simplify() {
    switch (type) {
        case NodeType::OPEN_BRACKET: {
            Node *it = next;
            while (it->type != NodeType::CLOSE_BRACKET) {
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
        }
        case NodeType::CLOSE_BRACKET: {
            Node *it = prev;
            while (it->type != NodeType::OPEN_BRACKET) {
                if (it->type == NodeType::OPERATION_LOW_PRIORITY) {
                    it = it->prev;
                    it->next->Simplify();
                } else {
                    it = it->prev;
                }
            }
            it->next->Simplify();
            return;
        }
    }
}

bool Bracket::isBracket(char c) {
    return (c == '(' || c == ')');
}
