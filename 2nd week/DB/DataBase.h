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
private:
    static void trim(string& line);
    void reformat_query(string & query, int pos);
    map<string,Table> tables;
};


#endif //DB_DATABASE_H
