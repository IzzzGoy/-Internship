//
// Created by Alex on 30.07.2020.
//

#include "Operation.h"
#include "Value.h"

Operation::Operation(char c) {
    switch (c) {
        case '+':
            operationType = OperationType::PLUS;
            type = NodeType::OPERATION_LOW_PRIORITY;
            break;
        case '-':
            operationType = OperationType::MINUS;
            type = NodeType::OPERATION_LOW_PRIORITY;
            break;
        case '*':
            operationType = OperationType::MULTIPLE;
            type = NodeType::OPERATION_HIGH_PRIORITY;
            break;
        case '/':
            operationType = OperationType::DIVISION;
            type = NodeType::OPERATION_HIGH_PRIORITY;
            break;
    }
}

void Operation::Simplify() {
    if (type == NodeType::OPERATION_LOW_PRIORITY) {
        if (next->type == NodeType::NUMBER) {
            Value *tmp = dynamic_cast<Value *>(prev);
            if (operationType == OperationType::MINUS) {
                tmp->value -= dynamic_cast<Value *>(next)->value;
            } else if (operationType == OperationType::PLUS) {
                tmp->value += dynamic_cast<Value *>(next)->value;
            }
            next->next->prev = tmp;
            tmp->next = next->next;
            tmp = nullptr;
            delete next;
            delete this;
        }
    } else if (type == NodeType::OPERATION_HIGH_PRIORITY) {
        if (next->type == NodeType::NUMBER) {
            Value *tmp = dynamic_cast<Value *>(next);
            if (operationType == OperationType::MULTIPLE) {
                tmp->value *= dynamic_cast<Value *>(prev)->value;
            } else if (operationType == OperationType::DIVISION) {
                tmp->value = dynamic_cast<Value *>(prev)->value / tmp->value;
            }
            prev->prev->next = tmp;
            tmp->prev = prev->prev;

            delete prev;
            delete this;

        }
    }
}

bool Operation::isOperation(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}
