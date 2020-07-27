//
// Created by Alex on 27.07.2020.
//

#ifndef INC_2ND_DAY_SQUARE_H
#define INC_2ND_DAY_SQUARE_H

#include <vector>
#include <map>

template<typename T>
void square(std::vector<T>& vector){
    for (auto& item : vector) {
        item *= item;
    }
}

template<typename F,typename S>
void square(std::pair<F,S>& pair){
    pair.first *= pair.first;
    pair.second *= pair.second;
}

template<typename K,typename V>
void square(std::map<K,V>& map){
    for (auto& item : map) {
        item.second *= item.second;
    }
}
#endif //INC_2ND_DAY_SQUARE_H
