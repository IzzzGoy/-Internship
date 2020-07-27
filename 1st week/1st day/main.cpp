#include <iostream>
#include "template.h"

using namespace std;

int main() {

    vector<double> v = {1.5, 2, 3};

    cout << v << endl;

    map<int, double> m = {{1, 2.5}, {2, 5}};

    cout << m << endl;

    vector<vector<int>> vv = {{1, 2}, {3, 4}};

    cout << vv << endl;

    return 0;

}