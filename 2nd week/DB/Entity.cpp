//
// Created by Alex on 03.08.2020.
//

#include "Entity.h"

#include <utility>
#include <regex>

Entity::Entity(const string& value, const EntityType& entityType) : value(std::move(value)), type(entityType){
}

/*string Entity::get_as_string() const {
    return value;
}

int Entity::get_as_int() const {
    return stoi(value);
}

bool Entity::compare(const Entity &entity) const {
    return entity.value == value;
}

double Entity::get_as_double() const {
    return stod(value);
}

bool Entity::check_date(const string &candidate) {
    regex rs {R"((0[1-9]|[12][0-9]|3[01])[- /.](0[1-9]|1[012])[- /.](19|20)\d\d)"};
    return regex_match(candidate,rs);
   *//* bool isDay = true, isMonth, isYear;
    string num;
    for (int i = 0; i < candidate.length(); ++i) {
        if (isdigit(candidate[i])){
            num.push_back(candidate[i]);
        } else if (candidate[i] == '.'){

        }
    }*//*
}

bool Entity::check_int(const string &candidate) {
    try {
        stoi(candidate);
    } catch (...) {
        return false;
    }
    return true;
}

bool Entity::check_double(const string &candidate) {
    try {
        stod(candidate);
    } catch (...) {
        return false;
    }
    return true;
}

void Entity::set_value(const string &new_value) {
    this->value = new_value;
}*/

string Entity::get() const {
    return value;
}

bool Entity::operator==(Entity &entity) {
    return this->value == entity.value;
}

bool Entity::operator!=(Entity &entity) {
    return this->value != entity.value;
}

bool Entity::operator<(Entity &entity) {
    return this->value.length() < entity.value.length();
}

bool Entity::operator>(Entity &entity) {
    return this->value.length() > entity.value.length();
}

bool Entity::operator<=(Entity &entity) {
    return this->value.length() <= entity.value.length();
}

bool Entity::operator>=(Entity &entity) {
    return this->value.length() >= entity.value.length();
}
