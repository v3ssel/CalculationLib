#include "Calculation.h"

namespace s21 {
std::queue<ExpressionToken> Calculation::toPostfix(std::stack<ExpressionToken> &expression) {
    std::stack<ExpressionToken> operators;
    std::queue<ExpressionToken> output;

    while (!expression.empty()) {
        if (expression.top().type == ETypes::CLOSED_BRACKET) {
            expression.pop();
            while (operators.top().type != ETypes::OPEN_BRACKET) {
                output.push(operators.top());
                operators.pop();
            }

            operators.pop();
            if (!operators.empty() && operators.top().priority == 4) {
                output.push(operators.top());
                operators.pop();
            }

        } else if (expression.top().type == ETypes::NUMBER) {
            output.push(expression.top());
            expression.pop();

        } else if (expression.top().type != ETypes::NUMBER && expression.top().type != ETypes::CLOSED_BRACKET) {
            while (!operators.empty()) {
                if (expression.top().priority != -1 &&
                   ((expression.top().priority == 3 && expression.top().priority <  operators.top().priority) || 
                    (expression.top().priority != 3 && expression.top().priority <= operators.top().priority))) {
                        
                    output.push(operators.top());
                    operators.pop();
                } else {
                    break;
                }
            }

            operators.push(expression.top());
            expression.pop();
        }
    }

    while (!operators.empty()) {
        output.push(operators.top());
        operators.pop();
    }

    return output;
}

double Calculation::calculate(std::queue<ExpressionToken> &postfix_expression) {
    double val1 = 0., val2 = 0.;
    std::stack<ExpressionToken> calculated;

    while (!postfix_expression.empty()) {
        if (postfix_expression.front().is_operator) {
            auto function = reinterpret_cast<double(*)(double, double)>(postfix_expression.front().function);
            postfix_expression.pop();

            val1 = calculated.top().value, calculated.pop();
            val2 = calculated.top().value, calculated.pop();
            
            calculated.push({ function(val2, val1), 0, ETypes::NUMBER, false, false, nullptr });
        } else if (postfix_expression.front().is_function) {
            auto function = reinterpret_cast<double(*)(double)>(postfix_expression.front().function);
            postfix_expression.pop();
            val1 = calculated.top().value, calculated.pop();

            calculated.push({ function(val1), 0, ETypes::NUMBER, false, false, nullptr });
        } else if (postfix_expression.front().type == ETypes::NUMBER) {
            calculated.push(postfix_expression.front());
            postfix_expression.pop();
        }
    }

    return calculated.top().value;
}
}
