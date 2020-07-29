#include <iostream>
#include <vector>
#include "square.h"
#include "template.h"

int main() {
    std::vector<int> v1 = {2 ,3 ,4};
    std::vector<double> v2 = {1.0, 2.0, 3.5};
    std::vector<char> v3 = {'a', 'b'};

    std::map<int,int> map;
    std::pair<int,int> p = std::make_pair(1,19);
    map[1] = 2;

    std::cout << v1 << " "<< v2 << " "<< v3 << std::endl;

    square(v1);
    square(v2);
    square(v3);

    std::cout << v1 << " "<< v2 << " "<< v3 << std::endl;

    std::cout << p << std::endl;
    square(p);
    std::cout << p << std::endl;

    std::cout << map << std::endl;
    square(map);
    std::cout << map << std::endl;
    return 0;
}
