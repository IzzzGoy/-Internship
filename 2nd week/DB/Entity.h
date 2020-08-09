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

    Entity(string  value, const EntityType& entityType);

    bool compare(const Entity& entity) const;
    static bool check_date(const string& candidate);
    static bool check_int(const string& candidate);
    static bool check_double(const string& candidate);

    string get_as_string() const ;
    int get_as_int() const ;
    double get_as_double() const ;

    void set_value(const string& new_value);

private:
    string value;
};




#endif //DB_ENTITY_H
