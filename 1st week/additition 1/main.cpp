#include <iostream>
#include <vector>
#include "Value.h"
#include "Operator.h"
#include "Variable.h"

using namespace std;

vector<Value*> values;
vector<Operator> operators;

void doAction(){
    while (!operators.empty()){
        if (Operator::isHighPriority(operators.back().op)){

        }
    }
}

int main() {
    string formula;
    vector<Value*> values;
    vector<Operator> operators;
    auto* var = new Variable();
    int X;
    bool wasHighPriorityAction = false;

    cin >> formula;
    for (int i = 0; i < formula.length(); ++i) {
        if (Operator::isOperator(formula[i])){
            operators.push_back(Operator(formula[i]));
        }
        else if (isdigit(formula[i])){
            string number;
            while (isdigit(formula[i])){
                number += formula[i];
                i++;
            }
            values.push_back(new Value(stoi(number)));
            i--;
        } else {
            if (var->name.empty()){
                var->name = formula[i];
                values.push_back(var);
            }
        }
    }
    if(!var->name.empty()){
        cin >> X;
        var->value = X;
    }

    for (auto & value : values) {
        delete value;
    }
    return 0;
}
