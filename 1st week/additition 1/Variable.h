//
// Created by Alex on 30.07.2020.
//

#ifndef ADDITITION_1_VARIABLE_H
#define ADDITITION_1_VARIABLE_H


#include <string>
#include "Value.h"

using namespace std;

class Variable : public Value{
public:
    string name;

    Variable();
    int Calculate() override;
    int value;
};


#endif //ADDITITION_1_VARIABLE_H
