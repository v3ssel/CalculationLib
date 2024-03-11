#include "BracketsHandler.h"
#include "../Utils.h"

namespace s21 {
HandleStatus BracketsHandler::handle(const std::string &expression, size_t &index, std::list<ExpressionToken> &list) {
    if (expression[index] == '(') {
        left_bracket_counter_++;
        if (!list.empty() && list.back().type == ETypes::NUMBER) {
            list.push_back({ 0, 2, ETypes::MULT, true, false, reinterpret_cast<void*>(Utils::multiply) });
        }

        list.push_back({ 0, -1, ETypes::OPEN_BRACKET, false, false, nullptr });
        last_index_of_left_bracket_ = index;

        if (checkBracketsBalance()) {
            return HandleStatus{true, "Brackets must be in correct order."};
        }

        return HandleStatus{false, ""};
    }
    
    if (expression[index] == ')') {
        right_bracket_counter_++;

        if (!list.empty() && list.back().type == ETypes::OPEN_BRACKET) {
            return HandleStatus{true, "Brackets must contain a value."};
        }

        list.push_back({ 0, -1, ETypes::CLOSED_BRACKET, false, false, nullptr });
        last_index_of_right_bracket_ = index;

        if (checkBracketsBalance()) {
            return HandleStatus{true, "Brackets must be in correct order."};
        }

        return HandleStatus{false, ""};
    }

    return ExpressionHandler::handle(expression, index, list);
}

void BracketsHandler::clean() {
    left_bracket_counter_ = 0;
    right_bracket_counter_ = 0;
    last_index_of_left_bracket_ = 0;
    last_index_of_right_bracket_ = 0;
  
    ExpressionHandler::clean();
}

bool BracketsHandler::checkBracketsBalance() {
    return (last_index_of_right_bracket_ < last_index_of_left_bracket_ && 
           (left_bracket_counter_ + right_bracket_counter_) % 2 == 0   &&
           (left_bracket_counter_ == right_bracket_counter_));
}   
}
