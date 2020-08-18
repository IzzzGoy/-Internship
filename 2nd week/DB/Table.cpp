//
// Created by Alex on 03.08.2020.
//
#include <algorithm>
#include "Table.h"
#include "String.h"
#include "Integer.h"
#include "Date.h"
#include "Double.h"

Table::Table(vector<Header> headers) : headers(std::move(headers)){}

template<typename T>
bool make_coincidence(T elem2, T elem1, uint8_t op_byte){
    if (op_byte == 0 && elem1 == elem2){
        return  true;
    } else if (op_byte == 1 && elem1 != elem2){
        return  true;
    } else if (op_byte == 2 && elem1 < elem2){
        return  true;
    } else if (op_byte == 3 && elem1 > elem2){
        return  true;
    } else if (op_byte == 4 && elem1 <= elem2){
        return  true;
    } else return op_byte == 5 && elem1 >= elem2;
}

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

vector<Row> Table::find(const vector<QueryEntity>& recv) {
    vector<Row> res;
    for (auto & row : rows) {
        bool coincidence = true;
        for (auto & j : recv) {
            if (j.entity.type != EntityType::NOTHING){
                if (j.entity.type == EntityType::STRING){
                    coincidence = make_coincidence(static_cast<String>(j.entity), static_cast<String>(row.entities[j.column_numb]), j.op);
                } else if (j.entity.type == EntityType::INT){
                    coincidence = make_coincidence(static_cast<Integer>(j.entity),static_cast<Integer>(row.entities[j.column_numb]), j.op);
                } else if (j.entity.type == EntityType::DATE){
                    coincidence = make_coincidence(static_cast<Date>(j.entity), static_cast<Date>(row.entities[j.column_numb]), j.op);
                } else if (j.entity.type == EntityType::DOUBLE){
                    coincidence = make_coincidence(static_cast<Double>(j.entity), static_cast<Double>(row.entities[j.column_numb]), j.op);
                }
            }
        }
        if (coincidence){
            res.push_back(row);
        }
    }

    return res;
}

void Table::remove_row(const vector<QueryEntity>& recv) {
    for  (auto it = rows.begin(); it != rows.end(); it++) {
        bool coincidence = true;
        for (auto & j : recv) {
            if (j.entity.type != EntityType::NOTHING){
                if (j.entity.type == EntityType::STRING){
                    coincidence = make_coincidence(static_cast<String>(j.entity), static_cast<String>(it->entities[j.column_numb]), j.op);
                } else if (j.entity.type == EntityType::INT){
                    coincidence = make_coincidence(static_cast<Integer>(j.entity),static_cast<Integer>(it->entities[j.column_numb]), j.op);
                } else if (j.entity.type == EntityType::DATE){
                    coincidence = make_coincidence(static_cast<Date>(j.entity), static_cast<Date>(it->entities[j.column_numb]), j.op);
                } else if (j.entity.type == EntityType::DOUBLE){
                    coincidence = make_coincidence(static_cast<Double>(j.entity), static_cast<Double>(it->entities[j.column_numb]), j.op);
                }
            }
        }
        if (coincidence){
            rows.erase(it);
            --it;
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


template<typename T>
bool less_el(T el1, T el2){
    return el1 < el2;
}

void Table::sort(vector<Row> &row, const int &col_numb) {
    for (int i = 0; i < row.size(); ++i) {
        for (int j = i; j < row.size(); ++j) {
            if (row[i].entities[col_numb].type == EntityType::DOUBLE && row[j].entities[col_numb].type == EntityType::DOUBLE){
                if (less_el(static_cast<Double>(row[j].entities[col_numb]), static_cast<Double>(row[i].entities[col_numb]))){
                    swap(row[j],row[i]);
                }
            } else if (row[i].entities[col_numb].type == EntityType::INT && row[j].entities[col_numb].type == EntityType::INT){
                if (less_el(static_cast<Integer>(row[j].entities[col_numb]), static_cast<Integer>(row[i].entities[col_numb]))){
                    swap(row[j],row[i]);
                }
            } else if (row[i].entities[col_numb].type == EntityType::DATE && row[j].entities[col_numb].type == EntityType::DATE){
                if (less_el(static_cast<Date>(row[j].entities[col_numb]), static_cast<Date>(row[i].entities[col_numb]))){
                    swap(row[j],row[i]);
                }
            } else {
                if (less_el(row[j].entities[col_numb], row[i].entities[col_numb])){
                    swap(row[j],row[i]);
                }
            }
        }
    }
}



