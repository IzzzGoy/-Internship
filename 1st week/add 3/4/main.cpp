#include <iostream>
#include <memory>
#include "Node.h"
#include "Border.h"
#include "Bracket.h"
#include "Value.h"
#include "Operation.h"

using namespace std;

int main() {
    Border begin(NodeType::BEGIN), end(NodeType::END);
    Node *tmp = &begin;
    string formula;
    string Xname = "";
    int X;
    cin >> formula;
    for (int j = 0; j < formula.length(); ++j) {
        if (!isdigit(formula[j]) && !Bracket::isBracket(formula[j]) && !Operation::isOperation(formula[j])) {
            Xname = formula[j];
        }
    }
    if (!Xname.empty()) {
        cin >> X;
        for (int j = 0; j < formula.length(); ++j) {
            if (formula[j] == Xname[0]) {
                formula.erase(j, 1);
                formula.insert(j, to_string(X));
            }
        }
    }
    if (formula[0] == '(') {
        formula.insert(0, "1*");
    }
    for (int i = 0; i < formula.length(); ++i) {
        if (Bracket::isBracket(formula[i]) || Operation::isOperation(formula[i])) {
            if (Bracket::isBracket(formula[i])) {
                tmp->addNode(new Bracket(formula[i]));
                tmp = tmp->next;
            } else {
                tmp->addNode(new Operation(formula[i]));
                tmp = tmp->next;
            }
        } else if (isdigit(formula[i])) {
            string number;
            while (isdigit(formula[i])) {
                number += formula[i];
                i++;
            }
            tmp->addNode(new Value(stoi(number)));
            tmp = tmp->next;
            i--;
        }
    }
    tmp->addNode(&end);

    /*tmp->addNode(new Value(6));
    tmp = tmp->next;
    tmp->addNode(new Operation('+'));
    tmp = tmp->next;
    tmp->addNode(new Value(5));
    tmp = tmp->next;
    tmp->addNode(new Operation('*'));
    tmp = tmp->next;
    tmp->addNode(new Bracket(NodeType::OPEN_BRACKET));
    tmp = tmp->next;
    tmp->addNode(new Value(6));
    tmp = tmp->next;
    tmp->addNode(new Operation('+'));
    tmp = tmp->next;
    tmp->addNode(new Value(5));
    tmp = tmp->next;
    tmp->addNode(new Operation('-'));
    tmp = tmp->next;
    tmp->addNode(new Bracket(NodeType::OPEN_BRACKET));
    tmp = tmp->next;
    tmp->addNode(new Value(12));
    tmp = tmp->next;
    tmp->addNode(new Operation('*'));
    tmp = tmp->next;
    tmp->addNode(new Value(5));
    tmp = tmp->next;
    tmp->addNode(new Bracket(NodeType::CLOSE_BRACKET));
    tmp = tmp->next;
    tmp->addNode(new Bracket(NodeType::CLOSE_BRACKET));
    tmp = tmp->next;
    tmp->addNode(&end);
*/
    begin.Simplify();

    return 0;
}
