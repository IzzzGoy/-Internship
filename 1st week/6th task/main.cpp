#include <iostream>
#include "Cfraction.h"

using namespace std;

int main() {
    Cfraction c = Cfraction();
    Cfraction c1 = Cfraction(14,16);
    Cfraction c2 = Cfraction(7,8);

    cout << c << " " << c1 << " " << c2 << " " << c * c2 << " " << c1 / c2 << " ";
    c += c1;
    cout << c << endl;
    c(2);
    cout << c << endl;
    cout << (c2 == c1);
    c = c;
    c = c1;
    return 0;
}
