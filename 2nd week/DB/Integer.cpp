//
// Created by Alex on 10.08.2020.
//

#include "Integer.h"

bool Integer::check_format(const string &candidate) {
    double m, k;
    try {
        m = stoi(candidate);
        k = stod(candidate);
    } catch (...) {
        return false;
    }
    return m == k;
}

Integer::Integer(const string &value) : Entity(value, EntityType::INT), i_value(stoi(value)){}

bool Integer::operator==(Entity &entity) {
    return static_cast<Integer>(entity).i_value == i_value;
}

bool Integer::operator!=(Entity &entity) {
    return static_cast<Integer>(entity).i_value != i_value;
}

bool Integer::operator<(Entity &entity) {
    return static_cast<Integer>(entity).i_value > i_value;
}

bool Integer::operator>(Entity &entity) {
    return static_cast<Integer>(entity).i_value < i_value;
}

bool Integer::operator<=(Entity &entity) {
    return static_cast<Integer>(entity).i_value >= i_value;
}

bool Integer::operator>=(Entity &entity) {
    return static_cast<Integer>(entity).i_value <= i_value;
}

Integer::Integer(const Entity& entity) : Entity(entity.get(), EntityType::INT) , i_value(stoi(entity.get())){

}

