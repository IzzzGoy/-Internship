#include <iostream>
#include "erase_duplicates.h"
#include "template.h"

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5, 1, 8, 7, 4};
    std::vector<int> v1 = {1, 2, 3, 4, 5, 1, 8, 7, 4};

    std::cout << v << std::endl;
    erase_duplicates_set_use(v);
    std::cout << v <<std::endl;

    std::cout << v1 << std::endl;
    erase_duplicates_set_use(v1);
    std::cout << v1 <<std::endl;
    return 0;
}
