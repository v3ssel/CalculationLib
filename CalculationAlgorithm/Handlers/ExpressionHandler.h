#ifndef _EXPRESSIONHANDLER_H_
#define _EXPRESSIONHANDLER_H_

#include <string>
#include <list>
#include <memory>
#include "../ExpressionToken.h"
#include "HandleStatus.h"

namespace s21 {
class ExpressionHandler {
public:
    using ETypes = ExpressionTypes;

    ExpressionHandler();
    virtual ~ExpressionHandler() = default;
    
    virtual ExpressionHandler* setNext(ExpressionHandler* handler);
    virtual HandleStatus handle(const std::string& expression, size_t& index, std::list<ExpressionToken>& list);
    virtual void clean();


private:
    std::unique_ptr<ExpressionHandler> next_;
};
}

#endif  // _EXPRESSIONHANDLER_H_
