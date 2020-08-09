#include "library.h"

#include <iostream>

void hello() {
    std::cout << "Hello, World!" << std::endl;
}

int my_rand(){
    return 42;
}

void Hello::hello() {

}

int Hello::my_rand() {
    return 42;
}
