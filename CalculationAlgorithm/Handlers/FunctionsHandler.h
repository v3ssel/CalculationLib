#ifndef _FUNCTIONSHANDLER_H_
#define _FUNCTIONSHANDLER_H_

#include "ExpressionHandler.h"

namespace s21 {
class FunctionsHandler : public ExpressionHandler {
public:
    HandleStatus handle(const std::string& expression, size_t& index, std::list<ExpressionToken>& list) override;

private:
    void silenceMultiply(std::list<ExpressionToken>& list);
};
}

#endif  // _FUNCTIONSHANDLER_H_
