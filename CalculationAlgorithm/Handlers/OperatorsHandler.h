#ifndef _OPERATORSHANDLER_H_
#define _OPERATORSHANDLER_H_

#include "ExpressionHandler.h"

namespace s21 {
class OperatorsHandler : public ExpressionHandler {
public:
    HandleStatus handle(const std::string& expression, size_t& index, std::list<ExpressionToken>& stack) override;
};
}

#endif  // _OPERATORSHANDLER_H_
