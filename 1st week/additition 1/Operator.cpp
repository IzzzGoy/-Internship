//
// Created by Alex on 30.07.2020.
//

#include "Operator.h"

Operator::Operator(char op) : op(op){}

bool Operator::isOperator(char c) {
    return (c == '+' || c == '-' || c == '(' || c == ')' || c == '*' || c == '/');
}

int Operator::Calculate() {
    return 0;
}

bool Operator::isHighPriority(char c) {
    return c == '*' || c == '/';
}
