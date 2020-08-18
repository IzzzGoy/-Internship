//
// Created by Alex on 10.08.2020.
//

#include "Date.h"
#include <regex>

bool Date::check_format(const string &candidate) {
    regex rs {R"((0[1-9]|[12][0-9]|3[01])[- /.](0[1-9]|1[012])[- /.](19|20)\d\d)"};
    return regex_match(candidate,rs);
}

Date::Date(const string& value) : Entity(value,EntityType::DATE) {
    if (!check_format(value)){
        throw invalid_argument("String isn`t date!");
    }
    string num;
    bool t = true;
    for (char i : value) {
        if (isdigit(i)){
            num += i;
        } else {
            if (t){
                this->day = stoi(num);
                num = "";
                t = !t;
            } else {
                this->month = stoi(num);
                num = "";
            }
        }
    }
    this->year = stoi(num);
}


bool Date::operator!=( Entity& entity) {
    return !(*this == entity);
}

bool Date::operator==(Entity &entity) {
    const Date t = static_cast<Date>(entity);
    return this->year == t.year && this->month == t.month && this->day == t.day;
}

bool Date::operator<(Entity &entity) {
    Date t = static_cast<Date>(entity);
    if (this->year < t.year){
        return true;
    } else if (this->year > t.year){
        return false;
    } else {
        if (this->month < t.month){
            return true;
        } else if (this->month > t.month){
            return false;
        } else {
            return this->day < t.day;
        }
    }
}

bool Date::operator>(Entity &entity) {
    Date t = static_cast<Date>(entity);
    if (this->year > t.year){
        return true;
    } else if (this->year < t.year){
        return false;
    } else {
        if (this->month > t.month){
            return true;
        } else if (this->month < t.month){
            return false;
        } else {
            return this->day > t.day;
        }
    }
}

bool Date::operator<=(Entity &entity) {
    return !(*this > entity);
}

bool Date::operator>=(Entity &entity) {
    return !(*this < entity);
}

Date::Date(const Entity &entity) : Entity(entity.get(),EntityType::DATE) {
    if (!check_format(entity.get())){
        throw invalid_argument("String isn`t date!");
    }
    string num;
    bool t = true;
    for (char i : entity.get()) {
        if (isdigit(i)){
            num += i;
        } else {
            if (t){
                this->day = stoi(num);
                num = "";
                t = !t;
            } else {
                this->month = stoi(num);
                num = "";
            }
        }
    }
    this->year = stoi(num);
}


