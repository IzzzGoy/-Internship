//
// Created by Alex on 03.08.2020.
//

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include "DataBase.h"

void DataBase::exec(string &query) {
    trim(query);
    int word_end = query.find(' ');
    string word = query.substr(0,word_end);
    if (word == "insert"){
        /*reformat_query(query,word_end);
        word_end = query.find(' ');
        word = query.substr(0,word_end);
        if(word != "in"){
            cout << "Missing keyword 'in'" << endl;
            return;
        }
        reformat_query(query,word_end);
        word_end = query.find(' ');
        word = query.substr(0,word_end);
        if (tables.find(word) == tables.end()){
            cout << "There is not table " << word << endl;
            return;
        }
        const vector<Header> header = tables.at(word).get_headers();
        string arg;
        Row row;
        for (int i = 0; i < header.size(); ++i) {
            if (word_end == -1){
                cout << "Unexpected end of query in " << query;
                return;
            }
            reformat_query(query,word_end);
            word_end = query.find(' ');
            arg = query.substr(0,word_end);
            if (header[i].type == EntityType::INT){
                if (!Entity::check_int(arg)){
                    cout << "Wrong type of " << arg << endl;
                    return;
                } else {
                    row.add_entity(Entity(arg,EntityType::INT));
                }
            } else if (header[i].type == EntityType::DOUBLE) {
                if (!Entity::check_double(arg)){
                    cout << "Wrong type of " << arg << endl;
                    return;
                } else {
                    row.add_entity(Entity(arg,EntityType::DOUBLE));
                }
            } else if (header[i].type == EntityType::DATE){
                if (!Entity::check_date(arg)){
                    cout << "Wrong type of " << arg << endl;
                    return;
                } else {
                    row.add_entity(Entity(arg,EntityType::DATE));
                }
            } else {
                row.add_entity(Entity(arg,EntityType::STRING));
            }
        }
        if (query.find(' ') != -1)
        {
            cout << "Unexpected end of query in " << query;
            return;
        }
        tables.at(word).add_row(row);*/
        insert(query,word_end);
    }
    else if (word == "select"){
        select(query,word_end);
    } else if (word == "remove"){
        remove(query,word_end);
    } else if (word == "create"){
        create(query,word_end);
    } else {
        throw invalid_argument("Unexpected token " + word + " in " + query);
    }
}

void DataBase::trim(string &line) {
    line.erase(line.begin(), find_if(line.begin(), line.end(), [](int ch) {
        return !isspace(ch);
    }));
}

void DataBase::reformat_query(string& query,int pos) { ///Необходим, чтобы выделить ещё необработанную часть запроса
    if (pos == -1){
        query = query.substr(0, query.length());
    } else {
        query = query.substr(pos, query.length());
    }
    trim(query);
}

void DataBase::create(string &query, int word_end) {
    reformat_query(query,word_end);
    word_end = query.find(' ');
    string table_name = query.substr(0,word_end);
    reformat_query(query,word_end);
    vector<Header> head;
    if (query.empty()){
        throw invalid_argument("Unexpected end of query in " + query);
    }
    while (!query.empty()){
        word_end = query.find(' ');
        string cname = query.substr(0,word_end);
        reformat_query(query,word_end);
        if (word_end == -1){
            throw invalid_argument("Unexpected end of query in " + query);
        }
        word_end = query.find(' ');
        string ctype = query.substr(0,word_end);
        reformat_query(query,word_end);
        bool isEnd = true;
        if (ctype[ctype.length() - 1] == ','){
            isEnd = false;
            ctype.erase(ctype.length() - 1);
        }
        if (ctype == "int")             head.emplace_back(cname,EntityType::INT);
        else if (ctype == "double")     head.emplace_back(cname,EntityType::DOUBLE);
        else if (ctype == "string")     head.emplace_back(cname,EntityType::STRING);
        else if (ctype == "date")       head.emplace_back(cname,EntityType::DATE);
        else {
            throw invalid_argument("Unknown type " + ctype);
        }
        if (isEnd) break;
    }
    tables.emplace(table_name,Table(head));
}

void DataBase::select(string &query, int word_end) {
    reformat_query(query,word_end);
    word_end = query.find(' ');
    string word = query.substr(0,word_end);
    if(word != "from"){
        throw invalid_argument("Missing keyword 'from'");
    }
    reformat_query(query,word_end);
    word_end = query.find(' ');
    string table_name = query.substr(0,word_end);
    if (tables.find(table_name) == tables.end()){
        throw invalid_argument("There is not table " + word);
    }
    reformat_query(query,word_end);
    word_end = query.find(' ');
    word = query.substr(0,word_end);
    vector<Row> res;
    if (word != "where"){
         res = tables.at(table_name).find(create_qrow(query, table_name, word_end, false));
    } else {
        res = tables.at(table_name).find(create_qrow(query,table_name, word_end, true));
    }

    for (const auto &item : res) {
        for (const auto &e : item.entities) {
            cout << e.get_as_string() << " ";
        }
        cout << endl;
    }
}

const Row DataBase::create_qrow(string &query, string &table_name, int word_end, bool with_where) {
    Row row;
    for (int i = 0; i < tables.at(table_name).get_headers().size(); ++i) {
        row.add_entity(Entity("",EntityType::NOTHING));
    }
    word_end = query.find(' ');
    string word = query.substr(0,word_end);
    if (!with_where)return row;
    else {
        while (word_end != -1){
            reformat_query(query,word_end);
            word_end = query.find(' ');
            word = query.substr(0,word_end);
            int column_num = tables.at(table_name).get_column_number(word);
            if (column_num == -1){
                throw invalid_argument("There is no in table " + word);
            }
            reformat_query(query,word_end);
            word_end = query.find(' ');
            word = query.substr(0,word_end);
            if (word != "="){
                throw invalid_argument("Miss '=' " + word );
            }
            reformat_query(query,word_end);
            word_end = query.find(' ');
            word = query.substr(0,word_end);
            if (tables.at(table_name).get_column_type(column_num) == EntityType::INT && Entity::check_int(word)){
                row.entities[column_num].type = EntityType::INT;
                row.entities[column_num].set_value(word);
            } else if (tables.at(table_name).get_column_type(column_num) == EntityType::DOUBLE && Entity::check_double(word)) {
                row.entities[column_num].type = EntityType::DOUBLE;
                row.entities[column_num].set_value(word);
            } else if (tables.at(table_name).get_column_type(column_num) == EntityType::DATE && Entity::check_date(word)){
                row.entities[column_num].type = EntityType::DATE;
                row.entities[column_num].set_value(word);
            } else if (tables.at(table_name).get_column_type(column_num) == EntityType::STRING){
                row.entities[column_num].type = EntityType::STRING;
                row.entities[column_num].set_value(word);
            } else {
                throw invalid_argument("unexpected value type " + word);
            }
        }
    }
    return row;
}

void DataBase::insert(string &query, int word_end) {
    reformat_query(query,word_end);
    word_end = query.find(' ');
    string word = query.substr(0,word_end);
    if(word != "in"){
        throw invalid_argument("Missing keyword 'in'");
    }
    reformat_query(query,word_end);
    word_end = query.find(' ');
    word = query.substr(0,word_end);
    if (tables.find(word) == tables.end()){
        throw invalid_argument("There is not table " + word);
    }
    const vector<Header> header = tables.at(word).get_headers();
    string arg;
    Row row;
    for (const auto & i : header) {
        if (word_end == -1){
            throw invalid_argument("Unexpected end of query in " + query);
            return;
        }
        reformat_query(query,word_end);
        word_end = query.find(' ');
        arg = query.substr(0,word_end);
        if (i.type == EntityType::INT){
            if (!Entity::check_int(arg)){
                throw invalid_argument("Wrong type of " + arg);
            } else {
                row.add_entity(Entity(arg,EntityType::INT));
            }
        } else if (i.type == EntityType::DOUBLE) {
            if (!Entity::check_double(arg)){
                throw invalid_argument("Wrong type of " + arg);
            } else {
                row.add_entity(Entity(arg,EntityType::DOUBLE));
            }
        } else if (i.type == EntityType::DATE){
            if (!Entity::check_date(arg)){
                throw invalid_argument("Wrong type of " + arg);
            } else {
                row.add_entity(Entity(arg,EntityType::DATE));
            }
        } else {
            row.add_entity(Entity(arg,EntityType::STRING));
        }
    }
    if (query.find(' ') != -1)
    {
        throw invalid_argument("Unexpected end of query in " + query);
        return;
    }
    tables.at(word).add_row(row);
}

void DataBase::remove(string &query, int word_end) {
    reformat_query(query,word_end);
    word_end = query.find(' ');
    string word = query.substr(0,word_end);
    if(word != "from"){
        throw invalid_argument("Missing keyword 'from'");
    }
    reformat_query(query,word_end);
    word_end = query.find(' ');
    string table_name = query.substr(0,word_end);
    if (tables.find(table_name) == tables.end()){
        throw invalid_argument("There is not table " + word);
    }
    reformat_query(query,word_end);
    vector<Row> res;
    if (word != "where"){
        tables.at(table_name).remove_row(create_qrow(query, table_name, word_end, false));
    } else {
        tables.at(table_name).remove_row(create_qrow(query,table_name, word_end, true));
    }
}
