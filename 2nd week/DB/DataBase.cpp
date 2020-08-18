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
    auto* operations = new uint8_t[tables.at(table_name).get_headers().size()];
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
    res = tables.at(table_name).find(create_qrow(query, table_name, word_end, word == "where", operations), operations);
    if (need_sort) Table::sort(res, sort_col);
    delete [] operations;
    return  res;
    /*for (const auto &item : res) {
        for (const auto &e : item.entities) {
            cout << e.get() << " ";
        }
        cout << endl;
    }*/
}

Row DataBase::create_qrow(string &query, string &table_name, int word_end, bool with_where, uint8_t operations[]) {
    Row row;
    for (int i = 0; i < tables.at(table_name).get_headers().size(); ++i) {
        row.add_entity(Entity("",EntityType::NOTHING));
        operations[i] = 128;
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
            if (word == "="){
                operations[column_num] = 0;
            } else if (word == "!="){
                operations[column_num] = 1;
            } else if (word == "<"){
                operations[column_num] = 2;
            } else if (word == ">"){
                operations[column_num] = 3;
            } else if (word == "<"){
                operations[column_num] = 4;
            } else if (word == ">"){
                operations[column_num] = 5;
            } else {
                throw invalid_argument("Miss operator " + word );
            }
            reformat_query(query,word_end);
            word_end = query.find(' ');
            word = query.substr(0,word_end);
            if (tables.at(table_name).get_column_type(column_num) == EntityType::INT && Integer::check_format(word)){
                row.entities.erase(row.entities.begin() + column_num);
                row.entities.insert(row.entities.begin() + column_num, Integer(word));
            } else if (tables.at(table_name).get_column_type(column_num) == EntityType::DOUBLE && Double::check_format(word)) {
                row.entities.erase(row.entities.begin() + column_num);
                row.entities.insert(row.entities.begin() + column_num, Double(word));
            } else if (tables.at(table_name).get_column_type(column_num) == EntityType::DATE && Date::check_format(word)){
                row.entities.erase(row.entities.begin() + column_num);
                row.entities.insert(row.entities.begin() + column_num, Date(word));
            } else if (tables.at(table_name).get_column_type(column_num) == EntityType::STRING){
                row.entities.erase(row.entities.begin() + column_num);
                row.entities.insert(row.entities.begin() + column_num, String(word));
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
    vector<Row> res;
    uint8_t* operations = new uint8_t[tables.at(table_name).get_headers().size()];
    if (word != "where"){
        tables.at(table_name).remove_row(create_qrow(query, table_name, word_end, false, operations), operations);
    } else {
        tables.at(table_name).remove_row(create_qrow(query,table_name, word_end, true, operations), operations);
    }
    delete [] operations;
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
