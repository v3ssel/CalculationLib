#ifndef _EXPRESSIONHANDLER_H_
#define _EXPRESSIONHANDLER_H_

#include <string>
#include <stack>
#include "ExpressionToken.h"
#include "HandleStatus.h"

namespace s21 {
class ExpressionHandler {
public:
    virtual ExpressionHandler* setNext(ExpressionHandler* handler) = 0;
    virtual HandleStatus handle(const std::string& expression, size_t& index, std::stack<ExpressionToken>& stack) = 0;

    size_t function_counter;
    
    size_t left_bracket_counter;
    size_t right_bracket_counter;

    size_t last_index_of_left_bracket;
    size_t last_index_of_right_bracket;
};
}

#endif  // _EXPRESSIONHANDLER_H_
