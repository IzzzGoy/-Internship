//
// Created by Alex on 10.08.2020.
//

#ifndef DB_DATE_H
#define DB_DATE_H
#include <string>
#include "Entity.h"

using namespace std;

class Date : public Entity {
public:

    Date(const string& value);

    Date(const Entity& entity);

    static bool check_format(const string& candidate);

    bool operator== ( Entity& entity) override;
    bool operator!= ( Entity& entity) override;
    bool operator< ( Entity& entity) override;
    bool operator> ( Entity& entity) override;
    bool operator<= ( Entity& entity) override;
    bool operator>= ( Entity& entity) override;

private:
    int year;
    int month;
    int day;
};


#endif //DB_DATE_H
