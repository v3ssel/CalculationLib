#include <stdexcept>

#include "ExpressionParser.h"
#include "Utils.h"

namespace s21 {
ExpressionParser::ExpressionParser(ExpressionHandler *handler) {
    m_handler_ = handler;
}

std::stack<ExpressionToken> ExpressionParser::parse(const std::string &expression) {
    if (expression.empty())
        throw std::invalid_argument("Expression is empty.");

    std::stack<ExpressionToken> tokens;
    std::list<ExpressionToken> token_list;
    
    try {
    for (size_t i = 0; i < expression.length(); i++) {
        HandleStatus status = m_handler_->handle(expression, i, token_list);

        if (status.is_error) {
            throw std::invalid_argument("Invalid expression. " + status.error_message);
        }
    }

    token_list.push_back({ 0, 1, ExpressionTypes::PLUS, true, false, reinterpret_cast<void*>(Utils::plus) });
    token_list.push_back({ 0, 0, ExpressionTypes::NUMBER, false, false, nullptr });

    size_t function_counter = 0, left_brackets = 0, right_brackets = 0;
    for (auto token = token_list.rbegin(); token != token_list.rend(); token++) {
        if (token->type == ExpressionTypes::OPEN_BRACKET)
            left_brackets++;

        if (token->type == ExpressionTypes::CLOSED_BRACKET)
            right_brackets++;
        
        if (token->is_function)
            function_counter++;

        tokens.push(*token);
    }

    if (left_brackets != right_brackets) {
        throw std::invalid_argument("Invalid expression. Bracket missing.");
    }
    if ((function_counter * 2) > (left_brackets + right_brackets)) {
        throw std::invalid_argument("Invalid expression. Every function must contain open-closed bracket pair.");
    }

    } catch (...) {
        m_handler_->clean();
        throw;
    }
    
    m_handler_->clean();
    return tokens;
}
}
