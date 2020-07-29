#include <iostream>

double minus(double a, double b){return a - b;}

double sum(double a,double b) {return a + b;}

double div(double a,double b){return a / b;}

double mult(double a, double b){return a * b;}

double calculate(double a, double b, double (*action)(double, double )){
    return action(a,b);
}

int main() {
    double a = 16, b = 10;
    std::cout << calculate(a, b, minus) << std::endl << calculate(a,b,sum) << std::endl << calculate(a,b,div) << std::endl << calculate(a,b,mult);
    return 0;
}
