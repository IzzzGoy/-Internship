//
// Created by Alex on 30.07.2020.
//

#ifndef INC_4_BRACKET_H
#define INC_4_BRACKET_H


#include "Node.h"

class Bracket : public Node {
public:
    static bool isBracket(char c);

    explicit Bracket(char c);

    void Simplify() override;
};


#endif //INC_4_BRACKET_H
