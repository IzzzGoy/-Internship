//
// Created by Alex on 03.08.2020.
//

#ifndef DB_TABLE_H
#define DB_TABLE_H

#include <map>
#include <utility>
#include <vector>
#include "Entity.h"
#include "Row.h"

using namespace std;

struct Header{
    Header(string  name,const EntityType& type) :name(std::move(name)), type(type){}
    string name;
    EntityType type;
};

class Table {
public:
    explicit Table(vector<Header>  headers);

    bool add_row(const Row& row);
    vector<Row> find(const Row& example);
    void remove_row(const Row& example);


    const vector<Header>& get_headers();
    int get_column_number(const string& cname);
    EntityType get_column_type(const int& i);
private:

    vector<Row> rows;
    vector<Header> headers;
};


#endif //DB_TABLE_H
