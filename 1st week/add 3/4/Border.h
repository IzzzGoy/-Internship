//
// Created by Alex on 30.07.2020.
//

#ifndef INC_4_BORDER_H
#define INC_4_BORDER_H


#include "Node.h"

class Border : public Node {
public:
    explicit Border(NodeType t);

    void Simplify() override;
};


#endif //INC_4_BORDER_H
