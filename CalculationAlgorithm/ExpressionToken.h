#ifndef _EXPRESSIONTOKEN_H_
#define _EXPRESSIONTOKEN_H_

#include "ExpressionTypes.h"

namespace s21 {
struct ExpressionToken {
    ExpressionToken() {
        value = 0;
        priority = 0;
        type = ExpressionTypes::NUMBER;
        is_operator = false;
        is_function = false;
        function = nullptr;
    }

    double value;
    short priority;
    ExpressionTypes type;

    bool is_operator;
    bool is_function;
    void *function;
};
}

#endif  // _EXPRESSIONTOKEN_H_
