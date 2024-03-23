#ifndef _EXPRESSIONPARSER_H_
#define _EXPRESSIONPARSER_H_

#include <string>
#include <stack>

#include "ExpressionToken.h"
#include "Handlers/ExpressionHandler.h"

namespace s21 {
class ExpressionParser {
public:
    ExpressionParser(ExpressionHandler* handler);
    virtual ~ExpressionParser() = default;

    virtual std::stack<ExpressionToken> parse(const std::string& expression);
private:
    ExpressionHandler* m_handler_;
};
}

#endif  //  _EXPRESSIONPARSER_H_
