//
// Created by Alex on 03.08.2020.
//

#ifndef DB_DATABASE_H
#define DB_DATABASE_H

#include <string>
#include "Table.h"

using namespace std;

class DataBase {
public:
    void exec (string& query);
    [[nodiscard]] bool is_empty() const;
    vector<Row> select_result(string& query);
    map<string,Table> tables;
private:
    static void trim(string& line);
    void reformat_query(string & query, int pos);
    void create(string& query, int word_end);
    vector<Row> select(string& query, int word_end);
    void insert(string& query, int word_end);
    void remove(string& query, int word_end);
    Row create_qrow(string &query, string &table_name, int word_end, bool with_where, uint8_t operations[]);
};


#endif //DB_DATABASE_H
