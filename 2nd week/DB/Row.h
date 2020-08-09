//
// Created by Alex on 03.08.2020.
//

#ifndef DB_ROW_H
#define DB_ROW_H

#include <vector>
#include "Entity.h"

using namespace std;

class Row {


public:
    void add_entity(const Entity& entity);
    vector<Entity> entities;
};


#endif //DB_ROW_H
