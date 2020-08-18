//
// Created by Alex on 10.08.2020.
//

#include "Double.h"

bool Double::check_format(const string &candidate) {
    try {
        stod(candidate);
    } catch (...) {
        return false;
    }
    return true;
}

Double::Double(const string &value) : Entity(value, EntityType::DOUBLE), d_value(stod(value)) {

}

bool Double::operator==(Entity &entity) {
    return static_cast<Double>(entity).d_value == d_value;
}

bool Double::operator!=(Entity &entity) {
    return static_cast<Double>(entity).d_value != d_value;
}

bool Double::operator<(Entity &entity) {
    return static_cast<Double>(entity).d_value > d_value;
}

bool Double::operator>(Entity &entity) {
    return static_cast<Double>(entity).d_value < d_value;
}

bool Double::operator<=(Entity &entity) {
    return static_cast<Double>(entity).d_value >= d_value;
}

bool Double::operator>=(Entity &entity) {
    return static_cast<Double>(entity).d_value <= d_value;
}

Double::Double(const Entity& entity) : Entity(entity.get(), EntityType::DOUBLE), d_value(stod(entity.get())){

}

