//
// Created by Alex on 03.08.2020.
//

#include "Table.h"

Table::Table(vector<Header> headers) : headers(std::move(headers)){}

bool Table::add_row(const Row &row) {
    for (size_t i = 0; i < row.entities.size(); ++i) {
        if (headers[i].type != row.entities[i].type) {
            perror("Some entities miss match type");
            return false;
        }
    }
    rows.push_back(row);
    return true;
}

vector<Row> Table::find(const Row &example) {
    vector<Row> res;
    for (auto & row : rows) {
        bool coincidence = true;
        for (int j = 0; j < example.entities.size(); ++j) {
            if (example.entities[j].type != EntityType::NOTHING && !example.entities[j].compare(row.entities[j])){
                coincidence = false;
            }
        }
        if (coincidence){
            res.push_back(row);
        }
    }

    return res;
}

void Table::remove_row(const Row &example) {
    for  (auto it = rows.begin(); it != rows.end(); it++) {
        bool coincidence = true;
        for (int j = 0; j < example.entities.size(); ++j) {
            if (example.entities[j].type != EntityType::NOTHING && !example.entities[j].compare(it->entities[j])){
                coincidence = false;
            }
        }
        if (coincidence){
            rows.erase(it);
        }
    }
}

const vector<Header> &Table::get_headers() {
    return headers;
}

int Table::get_column_number(const string &cname) {
    for (int i = 0; i < headers.size(); ++i) {
        if (headers[i].name == cname) return i;
    }
    return -1;
}

EntityType Table::get_column_type(const int &i) {
    return headers[i].type;
}
