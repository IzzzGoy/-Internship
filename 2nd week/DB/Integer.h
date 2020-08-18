//
// Created by Alex on 10.08.2020.
//

#ifndef DB_INTEGER_H
#define DB_INTEGER_H


#include "Entity.h"

class Integer : public Entity{
public:
    explicit Integer(const string& value);

    Integer(const Entity &entity);

    static bool check_format(const string& candidate);

    bool operator== ( Entity& entity) override;
    bool operator!= ( Entity& entity) override;
    bool operator< ( Entity& entity) override;
    bool operator> ( Entity& entity) override;
    bool operator<= ( Entity& entity) override;
    bool operator>= ( Entity& entity) override;

private:
    int i_value;
};


#endif //DB_INTEGER_H
