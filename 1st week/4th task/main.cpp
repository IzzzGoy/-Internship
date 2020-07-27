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
    pair<vector<string>::iterator, vector<string>::iterator> pair = make_pair(end,end);
    for (auto& iter = begin; iter != end; advance(iter, 1)){
        if (pair.first == end && (*iter)[0] == prefix){
            pair.first = iter;
        }
        if (pair.first != end && (*next(iter))[0] != prefix){
            pair.second = iter;
            return pair;
        }
    }
    return pair;
}

int main() {
    vector<string> v = { "dasdas", "mdsada","mkmsad", "sad"};
    sort(v.begin(),v.end());
    auto result = FindStartsWith(v.begin(),v.end(),'m');
    cout << *result.first << "  " << *result.second;
    return 0;
}
