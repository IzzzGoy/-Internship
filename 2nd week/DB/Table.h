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

struct QueryEntity{
    size_t column_numb;
    uint8_t op;
    Entity entity = Entity("",EntityType::NOTHING);
};

class Table {
public:
    explicit Table(vector<Header>  headers);

    bool add_row(const Row& row);
    vector<Row> find(const vector<QueryEntity>& recv);
    void remove_row(const vector<QueryEntity>& recv);

    void static sort(vector<Row>& row, const int& col_numb);


    const vector<Header>& get_headers();
    int get_column_number(const string& cname);
    EntityType get_column_type(const int& i);


    vector<Row> rows;
private:


    vector<Header> headers;
};


#endif //DB_TABLE_H
