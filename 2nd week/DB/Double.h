//
// Created by Alex on 10.08.2020.
//

#ifndef DB_DOUBLE_H
#define DB_DOUBLE_H
#include "Entity.h"

class Double : public Entity {
public:
    Double(const string& value);
    Double(const Entity& entity);

    static bool check_format(const string& candidate);

    bool operator== ( Entity& entity) override;
    bool operator!= ( Entity& entity) override;
    bool operator< ( Entity& entity) override;
    bool operator> ( Entity& entity) override;
    bool operator<= ( Entity& entity) override;
    bool operator>= ( Entity& entity) override;

private:
    double d_value;
};


#endif //DB_DOUBLE_H
