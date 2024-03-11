#include "ExpressionHandler.h"

namespace s21 {
ExpressionHandler::ExpressionHandler()
    : next_(nullptr)
    // , function_counter(0)
    // , left_bracket_counter(0)
    // , right_bracket_counter(0)
    // , last_index_of_left_bracket(0)
    // , last_index_of_right_bracket(0) 
    {}

ExpressionHandler* ExpressionHandler::setNext(ExpressionHandler *handler) {
    next_ = std::unique_ptr<ExpressionHandler>(handler);
    return next_.get();
}

HandleStatus ExpressionHandler::handle(const std::string &expression, size_t &index, std::list<ExpressionToken> &list) {
    if (next_) {
        return next_->handle(expression, index, list);
    }
    
    return HandleStatus{ true, "Handler not found." };
}

void ExpressionHandler::clean() {
    if (next_) {
        next_->clean();
    }
}
}
