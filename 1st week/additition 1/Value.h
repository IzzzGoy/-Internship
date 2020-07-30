//
// Created by Alex on 30.07.2020.
//

#ifndef ADDITITION_1_VALUE_H
#define ADDITITION_1_VALUE_H


#include "Node.h"

class Value : public Node {
public:
    int Calculate() override;
    explicit Value(int value);
};


#endif //ADDITITION_1_VALUE_H
