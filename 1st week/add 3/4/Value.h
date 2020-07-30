//
// Created by Alex on 30.07.2020.
//

#ifndef INC_4_VALUE_H
#define INC_4_VALUE_H


#include "Node.h"

class Value : public Node {
public:
    double value;

    explicit Value(double value);

    void Simplify() override;
};


#endif //INC_4_VALUE_H
