#include <iostream>
#include "Table.h"
#include "DataBase.h"
#include <iostream>

void utest1(DataBase& dataBase){
    cout << "---Creation table test" << endl;
    if (dataBase.is_empty()){
        string query = "create test i int, d date";
        dataBase.exec(query);
        if (dataBase.is_empty()){
            cout << "error!! Expected: not empty database. Actual: database is empty" << endl;
        } else {
            cout << "Creation: ok" << endl;
            try {
                dataBase.exec(query);
            } catch ([[maybe_unused]]const invalid_argument e) {
                cout << "Handling double exception: ok" << endl;
                return;
            }
            cout << "error!! Expected: handling double exception. Actual: database cant handle it" << endl;
            return;
        }
    } else {
        cout << "error!! Expected: empty database. Actual: database isn`t empty" << endl;
    }
}

void utest2(DataBase& dataBase){
    cout << "---Handling creation errors table test" << endl;
    string query = "create test1 i";
    try {
        dataBase.exec(query);
    } catch ([[maybe_unused]]invalid_argument e) {
        cout << "Handling query without column type exception: ok" << endl;
        try {
            query = "create test1";
            dataBase.exec(query);
        } catch ([[maybe_unused]]invalid_argument e) {
            cout << "Handling query without columns exception: ok" << endl;
            return;
        }
        cout << "error!! Expected: Handling query without columns exception. Actual: database cant handle it" << endl;
        return;
    }
    cout << "error!! Expected: Handling query without column type exception. Actual: database cant handle it" << endl;
}

void utest3(DataBase& dataBase){
    cout << "---Insertion in  table errors test" << endl;
    string query = "insert in test 1 20.11.2015";
    try {
        dataBase.exec(query);
    } catch (invalid_argument e) {
        cout << "error!! Expected: Insert data in table 'test'. Actual: insertion error" << endl;
        cout << "-----Addition" << e.what() << endl;
    }
    cout << "Insertion data in table: ok" << endl;
    query = "insert in test 1";
    try {
        dataBase.exec(query);
    } catch ([[maybe_unused]]invalid_argument e) {
        cout << "Handling query without argument(s): ok" << endl;
        query = "insert in test 0.5 20.11.2015";
        try {
            dataBase.exec(query);
        } catch ([[maybe_unused]]invalid_argument e) {
            cout << "Handling query wrong argument(s) type -> double value to int column: ok" << endl;
            query = "insert in test 1 20.11.2";
            try {
                dataBase.exec(query);
            } catch ([[maybe_unused]] invalid_argument e) {
                cout << "Handling query with wrong date format: ok" << endl;
                return;
            }
            cout << "error!! Expected: Handling query with wrong date format. Actual: database cant handle it" << endl;
            return;
        }
        cout << "error!! Expected: Handling query wrong argument(s) type -> double value to int column. Actual: database cant handle it" << endl;
        return;
    }
    cout << "error!! Expected: Handle query without argument(s). Actual: database cant handle it" << endl;
}

void utest4(DataBase& dataBase){
    cout << "---Selection test" << endl;
    string query = "select from test";
    try {
        vector<Row> res = dataBase.select_result(query);
        if (res.empty()){
            cout << "error!! Expected: Query result must be not empty. Actual: Result empty" << endl;
            cout << "-----Expected value: 1 20.11.2015" << endl;
        } else if (res.size() != 1){
            cout << "error!! Expected: Query result size must be equals 1. Actual: Result size miss match" << endl;
            cout << "-----Expected value: 1 20.11.2015" << endl;
        } else {
            cout << "Selection all values from tables: ok" << endl;
            query = "insert in test 1 20.11.2018";
            dataBase.exec(query);
            query = "insert in test 2 05.10.2015";
            dataBase.exec(query);
            query = "insert in test 18 20.11.2020";
            dataBase.exec(query);
            query = "insert in test 12 19.11.2015";
            dataBase.exec(query);
            query = "select from test";
            res = dataBase.select_result(query);
            if (res.empty()){
                cout << "error!! Expected: Query result must be not empty. Actual: Result empty" << endl;
                cout << "-----Expected value: 1 20.11.2015" << endl;
                cout << "-----Expected value: 1 20.11.2018" << endl;
                cout << "-----Expected value: 2 05.10.2015" << endl;
                cout << "-----Expected value: 18 20.11.2020" << endl;
                cout << "-----Expected value: 12 19.11.2015" << endl;
            } else if (res.size() != 5){
                cout << "error!! Expected: Query result size must be equals 5. Actual: Result size miss match" << endl;
                cout << "-----Expected value: 1 20.11.2015" << endl;
                cout << "-----Expected value: 1 20.11.2018" << endl;
                cout << "-----Expected value: 2 05.10.2015" << endl;
                cout << "-----Expected value: 18 20.11.2020" << endl;
                cout << "-----Expected value: 12 19.11.2015" << endl;
            } else {
                cout << "Selection all values from tables (many values): ok" << endl;
                //TODO querys with 'where', 'sortby', 'sortby * where'
            }
        }
    } catch (invalid_argument e) {
        cout << "error!! Expected: Query selection result. Actual: Query selection error" << endl;
        cout << "-----Expected value: 1 20.11.2015" << endl;
        cout << "-----Addition: " << e.what() << endl;
    }
}

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
    /*string s = "create b i int";
    dataBase.exec(s);
    s = "insert in b 4";
    dataBase.exec(s);
    s = "insert in b 25";
    dataBase.exec(s);
     s = "insert in b 12";
    dataBase.exec(s);
    s = "select from b sortby i where i > 5";
    dataBase.exec(s);
   s = "remove from b";
    dataBase.exec(s);
    s = "select from b";
    dataBase.exec(s);*/
    /*while (true){
        string query;
        getline(cin,query);

        if (query == "exit") break;

        dataBase.exec(query);
    }
*/
    utest1(dataBase);
    utest2(dataBase);
    utest3(dataBase);
    utest4(dataBase);
    return 0;
}
