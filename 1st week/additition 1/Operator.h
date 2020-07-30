//
// Created by Alex on 30.07.2020.
//

#ifndef ADDITITION_1_OPERATOR_H
#define ADDITITION_1_OPERATOR_H


#include "Node.h"

class Operator : public Node{
public:
    char op;
    explicit Operator(char op);
    int Calculate() override;
    static bool isHighPriority(char c);

    static bool isOperator(char c);
};


#endif //ADDITITION_1_OPERATOR_H
