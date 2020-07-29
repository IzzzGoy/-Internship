#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "template.h"



using namespace std;


pair<vector<string>::iterator, vector<string>::iterator> FindStartsWith(
        std::vector<string>::iterator begin,
        const std::vector<string>::iterator& end,
        const char& prefix
        ){
    pair<vector<string>::iterator, vector<string>::iterator> pair = make_pair(end,end);         ///Инициализируем пару итераторами конца набора
    for (auto& iter = begin; iter != end; iter++){
        if (pair.first == end && (*iter)[0] == prefix){                     ///Находим первое совпадение
            pair.first = iter;
        }
        if (pair.first != end && (*iter)[0] != prefix){                     ///Находим второе совпадение
            pair.second = iter;
            return pair;
        }
    }
    return pair;                                                            ///В случае, если совпадения не найдены, оба итератора будат указывать на конец
}

pair<vector<string>::iterator, vector<string>::iterator> FindStartsWith(
        std::vector<string>::iterator begin,
        const std::vector<string>::iterator& end,
        const string& prefix
){
    pair<vector<string>::iterator, vector<string>::iterator> pair = make_pair(end,end);
    for (auto& iter = begin; iter != end; iter++){
        if (pair.first == end && (*iter).find(prefix) == 0){
            pair.first = iter;
        }
        if (pair.first != end && (*iter).find(prefix) != 0){
            pair.second = iter;
            return pair;
        }
    }
    return pair;
}

int main() {
    vector<string> v = { "dasdas", "mdsada","mkmsad", "mkpoo", "sad"};
    sort(v.begin(),v.end());
    auto result = FindStartsWith(v.begin(),v.end(),"m");
    for (auto i = result.first; i != result.second ; ++i) {
        cout << *i << " ";
    }
    return 0;
}
