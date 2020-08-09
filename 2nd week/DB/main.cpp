#include <iostream>
#include "Table.h"
#include "DataBase.h"
#include <iostream>

int main() {

    DataBase dataBase;
    /*vector<Header> headers;
    headers.emplace_back("Date",EntityType::DATE);
    headers.emplace_back("Name", EntityType::STRING);

    Row row;
    row.add_entity(Entity("24/05/2016", EntityType::DATE));
    row.add_entity(Entity("Mraz",EntityType::STRING));

    Table table(headers);
    table.add_row(row);
    vector<Row> finds = table.find(row);
    std::cout << "Hello, World!" << std::endl;

    cout << Entity::check_date("20.02.2011");*/
    string s = "create b i int, d double";
    dataBase.exec(s);
    s = "insert in b 4 6.3";
    dataBase.exec(s);
    s = "insert in b 5 6.3";
    dataBase.exec(s);
    s = "select from b";
    dataBase.exec(s);
    s = "remove from b";
    dataBase.exec(s);
    s = "select from b";
    dataBase.exec(s);
    /*while (true){
        string query;
        getline(cin,query);

        if (query == "exit") break;

        dataBase.exec(query);
    }*/


    return 0;
}
