//
// Created by Alex on 03.08.2020.
//

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include "DataBase.h"
#include "Date.h"
#include "Integer.h"
#include "Double.h"
#include "String.h"

void DataBase::exec(string &query) {
    trim(query);
    int word_end = query.find(' ');
    string word = query.substr(0,word_end);             ///Данная конструкция служит для перемещения текущего выбранного слова в запросе
    if (word == "insert"){                                  ///Запрос на вставку данных
        insert(query,word_end);
    }
    else if (word == "select"){                             ///Поиск данных, удовлетворяющих условию
        select(query,word_end);
    } else if (word == "remove"){                           ///Удаление данных по условию
        remove(query,word_end);
    } else if (word == "create"){                           ///Создание таблицы
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
    string table_name = query.substr(0,word_end);                           ///Выделение имени таблицы
    vector<Header> head;
    if (query == table_name){                                                   ///Проверка наличия аргументов
        throw invalid_argument("Unexpected end of query in " + query);
    }
    if (tables.find(table_name) != tables.end()){
        throw invalid_argument("Table already exists");
    }
    reformat_query(query,word_end);
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

vector<Row> DataBase::select(string &query, int word_end) {
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
    bool need_sort = false;
    int sort_col;
    vector<Row> res;
    if (word == "sortby"){
        need_sort = true;
        reformat_query(query,word_end);
        word_end = query.find(' ');
        word = query.substr(0,word_end);
        sort_col = tables.at(table_name).get_column_number(word);
        if (sort_col == -1) throw invalid_argument("wrong column name");
        reformat_query(query,word_end);
        word_end = query.find(' ');
        word = query.substr(0,word_end);
    }
    res = tables.at(table_name).find(create_qrow(query, table_name, word_end, word == "where"));
    if (need_sort) Table::sort(res, sort_col);
    return  res;
    /*for (const auto &item : res) {
        for (const auto &e : item.entities) {
            cout << e.get() << " ";
        }
        cout << endl;
    }*/
}

vector<QueryEntity> DataBase::create_qrow(string &query, string &table_name, int word_end, bool with_where) {
    vector<QueryEntity> queryEnt;
    word_end = query.find(' ');
    string word = query.substr(0,word_end);
    if (!with_where)return queryEnt;
    else {
        while (word_end != -1){
            reformat_query(query,word_end);
            word_end = query.find(' ');
            word = query.substr(0,word_end);
            int column_num = tables.at(table_name).get_column_number(word);
            if (column_num == -1){
                throw invalid_argument("There is no in table " + word);
            }
            queryEnt.push_back(QueryEntity());
            queryEnt.back().column_numb = column_num;
            reformat_query(query,word_end);
            word_end = query.find(' ');
            word = query.substr(0,word_end);
            if (word == "="){
                queryEnt.back().op = 0;
            } else if (word == "!="){
                queryEnt.back().op  = 1;
            } else if (word == "<"){
                queryEnt.back().op  = 2;
            } else if (word == ">"){
                queryEnt.back().op  = 3;
            } else if (word == "<"){
                queryEnt.back().op  = 4;
            } else if (word == ">"){
                queryEnt.back().op  = 5;
            } else {
                throw invalid_argument("Miss operator " + word );
            }
            reformat_query(query,word_end);
            word_end = query.find(' ');
            word = query.substr(0,word_end);
            if (tables.at(table_name).get_column_type(column_num) == EntityType::INT && Integer::check_format(word)){
                queryEnt.back().entity = Integer(word);
            } else if (tables.at(table_name).get_column_type(column_num) == EntityType::DOUBLE && Double::check_format(word)) {
                queryEnt.back().entity = Double(word);
            } else if (tables.at(table_name).get_column_type(column_num) == EntityType::DATE && Date::check_format(word)){
                queryEnt.back().entity = Date(word);
            } else if (tables.at(table_name).get_column_type(column_num) == EntityType::STRING){
                queryEnt.back().entity = String(word);
            } else {
                throw invalid_argument(
                        "unexpected value type " + word + "\n" +
                        "Int format : num \n" +
                        "Double format : num.num \n" +
                        "Date format : dd.mm.yyyy"
                        );
            }
        }
    }
    return queryEnt;
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
        }
        reformat_query(query,word_end);
        word_end = query.find(' ');
        arg = query.substr(0,word_end);
        if (i.type == EntityType::INT){
            if (!Integer::check_format(arg)){
                throw invalid_argument("Wrong type of " + arg);
            } else {
                row.add_entity(Entity(arg,EntityType::INT));
            }
        } else if (i.type == EntityType::DOUBLE) {
            if (!Double::check_format(arg)){
                throw invalid_argument("Wrong type of " + arg);
            } else {
                row.add_entity(Entity(arg,EntityType::DOUBLE));
            }
        } else if (i.type == EntityType::DATE){
            if (!Date::check_format(arg)){
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
    tables.at(table_name).remove_row(create_qrow(query,table_name, word_end, word != "where"));
}

bool DataBase::is_empty() const{
    return tables.empty();
}

vector<Row> DataBase::select_result(string &query) {
    trim(query);
    int word_end = query.find(' ');
    string word = query.substr(0,word_end);
    if (word == "select"){                             ///Поиск данных, удовлетворяющих условию
        return select(query,word_end);
    } else {
        throw invalid_argument("it is not select query");
    }
}
