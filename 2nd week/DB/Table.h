//
// Created by Alex on 03.08.2020.
//

#ifndef DB_TABLE_H
#define DB_TABLE_H

#include <map>
#include <vector>
#include "Entity.h"

using namespace std;

class Table {
public:
    Table();
    bool add_column(const string& column_name, const EntityType& type);
    bool add_row(const vector<pair<string,Entity>>& row_elements);
private:
    bool check_column_type(const string& column_name, const EntityType& type);
    bool add_entity(const string& column_name, const Entity& entity);
    map<string,pair<EntityType,vector<Entity>>> rows;
};


#endif //DB_TABLE_H
