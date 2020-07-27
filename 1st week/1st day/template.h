//
// Created by Alex on 27.07.2020.
//

#ifndef INC_1ST_WEEK_TEMPLATE_H
#define INC_1ST_WEEK_TEMPLATE_H

#include <ostream>
#include <vector>
#include <string>
#include <map>

template<typename T>
std::ostream& operator<<(std::ostream &out, const std::vector<T> &vi){
    out << '[';
    for (const auto &it : vi){
        out << it << ' ';
    }
    out << ']';
    return out;
}

template<typename F, typename S>
std::ostream& operator<<(std::ostream &out, const std::pair<F,S> pair){
    out << "{ " << pair.first << " : " << pair.second << " }";
    return out;
}

template<typename K,typename V>
std::ostream& operator<<(std::ostream &out, const std::map<K,V> &map){
    out << '{';
    for (const auto &it : map) {
        out << it;
    }
    out << '}';
    return out;
}
#endif //INC_1ST_WEEK_TEMPLATE_H
