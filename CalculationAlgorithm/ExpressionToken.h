#ifndef _EXPRESSIONTOKEN_H_
#define _EXPRESSIONTOKEN_H_

#include "ExpressionTypes.h"

namespace s21 {
struct ExpressionToken {
    double value;
    short priority;
    ExpressionTypes type;

    bool is_operator;
    bool is_function;
    void *function;
};
}

#endif  // _EXPRESSIONTOKEN_H_
