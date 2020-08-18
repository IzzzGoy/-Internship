//
// Created by Alex on 03.08.2020.
//

#ifndef DB_ENTITY_H
#define DB_ENTITY_H

#include <string>

using namespace std;

enum class EntityType{
    STRING,
    DATE,
    INT,
    DOUBLE,
    NOTHING
};

class Entity {
public:
    EntityType type;

    Entity(const string&  value, const EntityType& entityType);

    virtual bool operator== ( Entity& entity);
    virtual bool operator!= ( Entity& entity);
    virtual bool operator< ( Entity& entity);
    virtual bool operator> ( Entity& entity);
    virtual bool operator<= ( Entity& entity);
    virtual bool operator>= ( Entity& entity);

    /*static bool check_date(const string& candidate);
    static bool check_int(const string& candidate);
    static bool check_double(const string& candidate);*/

    /*string get_as_string() const;
    int get_as_int() const;
    double get_as_double() const;*/
    string get() const;

    //virtual void set_value(const string& new_value);

private:
    string value;
};




#endif //DB_ENTITY_H
