#ifndef _NUMBERHANDLER_H_
#define _NUMBERHANDLER_H_

#include "ExpressionHandler.h"

namespace s21 {
class NumberHandler : public ExpressionHandler {
public:
    HandleStatus handle(const std::string& expression, size_t& index, std::list<ExpressionToken>& stack) override;

private:
    double getNumber(const std::string& expression, size_t& index, bool& dots_error);
};
}

#endif  // _NUMBERHANDLER_H_
