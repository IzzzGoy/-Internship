//
// Created by Alex on 30.07.2020.
//

#ifndef INC_4_OPERATION_H
#define INC_4_OPERATION_H


#include "Node.h"

enum class OperationType {
    PLUS,
    MINUS,
    MULTIPLE,
    DIVISION
};

class Operation : public Node {
public:
    OperationType operationType;

    static bool isOperation(char c);

    explicit Operation(char c);

    void Simplify() override;
};

#endif //INC_4_OPERATION_H
