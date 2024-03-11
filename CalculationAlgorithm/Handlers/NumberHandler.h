#ifndef _NUMBERHANDLER_H_
#define _NUMBERHANDLER_H_

#include "ExpressionHandler.h"

namespace s21 {
class NumberHandler : public ExpressionHandler {
public:
    virtual ExpressionHandler* setNext(ExpressionHandler* handler) = 0;
    virtual HandleStatus handle(const std::string& expression, size_t& index, std::stack<ExpressionToken>& stack) = 0;
};
}

#endif  // _NUMBERHANDLER_H_
