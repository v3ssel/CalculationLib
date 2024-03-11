#ifndef _BRACKETSHANDLER_H_
#define _BRACKETSHANDLER_H_

#include "ExpressionHandler.h"

namespace s21 {
class BracketsHandler : public ExpressionHandler {
public:
    virtual ExpressionHandler* setNext(ExpressionHandler* handler) = 0;
    virtual HandleStatus handle(const std::string& expression, size_t& index, std::stack<ExpressionToken>& stack) = 0;
};
}

#endif  // _BRACKETSHANDLER_H_
