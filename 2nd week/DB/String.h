//
// Created by Alex on 10.08.2020.
//

#ifndef DB_STRING_H
#define DB_STRING_H


#include "Entity.h"

class String : public Entity {
public:
    String(const string& value);

    String(const Entity& entity);
};


#endif //DB_STRING_H
