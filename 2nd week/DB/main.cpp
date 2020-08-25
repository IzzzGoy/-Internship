#include <iostream>
#include "Table.h"
#include "DataBase.h"
#include "Integer.h"
#include "Date.h"
#include <iostream>

void utest1(DataBase& dataBase){
    cout << "---Creation table test" << endl;
    if (dataBase.is_empty()){
        string query = "create test i int, d date";
        dataBase.exec(query);
        if (dataBase.is_empty()){
            cout << "error!! Expected: not empty database. Actual: database is empty" << endl;
        } else {
            if (dataBase.tables.find("test") == dataBase.tables.end()){
                cout << "error!! Expected: Table with name 'test'. Actual: There isn`t table 'test'" << endl;
                return;
            } else {
                if(dataBase.tables.at("test").get_headers()[0].type != EntityType::INT){
                    cout << "error!! Expected: First column must be int. Actual: Other type" << endl;
                    return;
                }
                if(dataBase.tables.at("test").get_headers()[1].type != EntityType::DATE){
                    cout << "error!! Expected: Second column must be date. Actual: Other type" << endl;
                    return;
                }
                if(dataBase.tables.at("test").get_headers()[0].name != "i"){
                    cout << "error!! Expected: First column name must be i. Actual: Other name" << endl;
                    return;
                }
                if(dataBase.tables.at("test").get_headers()[1].name != "d"){
                    cout << "error!! Expected: Second column name must be d. Actual: Other name" << endl;
                    return;
                }
                cout << "Creation: ok" << endl;
                try {
                    dataBase.exec(query);
                } catch ([[maybe_unused]]const invalid_argument e) {
                    cout << "Handling double exception: ok" << endl;
                    return;
                }
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
        return;
    }
    Integer i("1");
    Date d("20.11.2015");
    if (dataBase.tables.at("test").rows[0].entities[0].type != EntityType::INT){
        cout << "error!! Expected: First entity must be int. Actual: Other type" << endl;
        return;
    } else if(Integer(dataBase.tables.at("test").rows[0].entities[0].get()) != i){
        cout << "error!! Expected: First entity must be equals 1. Actual: Other entity value" << endl;
        return;
    }
    if (dataBase.tables.at("test").rows[0].entities[1].type != EntityType::DATE){
        cout << "error!! Expected: First entity must be date. Actual: Other type" << endl;
        return;
    } else if(Date(dataBase.tables.at("test").rows[0].entities[1].get()) != d){
        cout << "error!! Expected: First entity must be equals 20.11.2015. Actual: Other entity value" << endl;
        return;
    }
    cout << "Insertion data in table: ok" << endl;
    query = "insert in test 1";
    try {
        dataBase.exec(query);
    } catch ([[maybe_unused]]invalid_argument e) {
        if (dataBase.tables.at("test").rows.size() != 1){
            cout << "error!! Expected: One row in the table. Actual: Un expected quantity of rows" << endl;
            return;
        }
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
            if (dataBase.tables.at("test").rows.size() != 5){
                cout << "error!! Expected: Table must contain 5 rows. Actual: Rows quantity miss match" << endl;
                cout << "-----Expected value: 5" << endl;
            }
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
                query = "select from test where i > 2";
                res = dataBase.select_result(query);
                for (auto& i : res) {
                    if (Integer(i.entities[0]).get_value() <= 2){
                        cout << "error!! Expected: Result element must be more then 2. Actual: It less or equal" << endl;
                        return;
                    }
                }
                query = "select from test where i = 1";
                res = dataBase.select_result(query);
                for (auto& i : res) {
                    if (Integer(i.entities[0]).get_value() != 1){
                        cout << "error!! Expected: Result element must be equals 1. Actual: It less or more" << endl;
                        return;
                    }
                }
                query = "select from test where i < 18";
                res = dataBase.select_result(query);
                for (auto& i : res) {
                    if (Integer(i.entities[0]).get_value() >= 18){
                        cout << "error!! Expected: Result element must be less then 18. Actual: It equals or less" << endl;
                        return;
                    }
                }
                cout << "Query, with 'when' expression : ok" << endl;
                query = "select from test sortby i";
                res = dataBase.select_result(query);
                if (Integer(res.back().entities[0]).get_value() != 18){
                    cout << "error!! Expected: Last element must be equal 18. Actual: It isn`t equals" << endl;
                    return;
                }
                for (std::size_t i = 1; i < res.size(); ++i) {
                    if (Integer(res[i - 1].entities[0]).get_value() > Integer(res[i].entities[0]).get_value()){
                        cout << "error!! Expected: Previous element must be less then this element. Actual: Result is unsorted" << endl;
                        return;
                    }
                }
                query = "select from test sortby d";
                res = dataBase.select_result(query);
                if (res.back().entities[1].get() != "20.11.2020"){
                    cout << "error!! Expected: Last element must be equal 20.11.2020. Actual: It isn`t equals" << endl;
                    return;
                }
                for (std::size_t i = 1; i < res.size(); ++i) {
                    Date f = Date(res[i - 1].entities[1]);
                    Date s = Date(res[i].entities[1]);
                    if ( f > s){
                        cout << "error!! Expected: Previous element must be less then this element. Actual: Result is unsorted" << endl;
                        return;
                    }
                }
                query = "select from test sortby d where i = 1";
                res = dataBase.select_result(query);
                if (res.back().entities[1].get() != "20.11.2018"){
                    cout << "error!! Expected: Last element must be equal 20.11.2018. Actual: It isn`t equals" << endl;
                    return;
                }
                cout << "Query, with 'sortby': ok" << endl;
            }
        }
    } catch (invalid_argument& e) {
        cout << "error!! Expected: Query selection result. Actual: Query selection error" << endl;
        cout << "-----Expected value: 1 20.11.2015" << endl;
        cout << "-----Addition: " << e.what() << endl;
    }
}

void utest5(DataBase& dataBase){
    cout << "---Deleting test" << endl;
    string query = "remove from test where i = 2";
    try {
        dataBase.exec(query);
    } catch (invalid_argument& e) {
        cout << "error!! Expected: Deleting element. Actual: Exception" << endl;
        cout << "-----Addition: " << e.what() << endl;
    }
    for (auto& i : dataBase.tables.at("test").rows) {
        if (i.entities[0].get() == "2"){
            cout << "error!! Expected: Deleting element. Actual: Element was not deleted" << endl;
            return;
        }
    }
    cout << "Deleting element from table: ok" << endl;
    query = "remove from test";
    dataBase.exec(query);
    if (dataBase.tables.at("test").rows.empty()){
        cout << "Clearing table: ok" << endl;
    } else {
        cout << "error!! Expected: Clearing table. Actual: Table isn`t clear" << endl;
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
    utest5(dataBase);
    return 0;
}
