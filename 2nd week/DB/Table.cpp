//
// Created by Alex on 03.08.2020.
//

#include "Table.h"

bool Table::add_column(const string &column_name, const EntityType &type) {
    if (rows.find(column_name) == rows.end()){
        rows[column_name] = make_pair(type,vector<Entity>());
        return true;
    } else {
        return false;
    }
}

bool Table::add_entity(const string &column_name, const Entity &entity) {
    if (rows.find(column_name) != rows.end()){
        if (rows[column_name].first == entity.type){
            rows[column_name].second.push_back(entity);
            return true;
        }
    }
    return false;
}

bool Table::check_column_type(const string &column_name, const EntityType &type) {
    return rows[column_name].first == type;
}

bool Table::add_row(const vector<pair<string,Entity>> &row_elements) {
    if (rows.size() == row_elements.size()) return false;
    for (const auto& p : row_elements) {
        if (!check_column_type(p.first,p.second.type))return false;
    }

    for(const auto& element : row_elements){
        add_entity(element.first,element.second);
    }
    return true;
}
