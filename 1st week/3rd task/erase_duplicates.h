//
// Created by Alex on 27.07.2020.
//

#ifndef INC_3RD_TASK_ERASE_DUPLICATES_H
#define INC_3RD_TASK_ERASE_DUPLICATES_H

#include <vector>
#include <algorithm>
#include <set>

template<typename T>
void erase_duplicates(std::vector<T>& vector){
    std::sort(vector.begin(), vector.end());
    vector.erase( std::unique( vector.begin(), vector.end() ), vector.end() );
}

template<typename T>
void erase_duplicates_set_use(std::vector<T>& vector){
    std::set<int> s( vector.begin(), vector.end() );
    vector.assign( s.begin(), s.end() );
}
#endif //INC_3RD_TASK_ERASE_DUPLICATES_H
