#include "ExpressionParser.h"

namespace s21 {
ExpressionParser::ExpressionParser(ExpressionHandler *handler) {
    m_handler_ = handler;
}

std::stack<ExpressionToken> ExpressionParser::parse(const std::string &expression) {
    
    return std::stack<ExpressionToken>();
}
}