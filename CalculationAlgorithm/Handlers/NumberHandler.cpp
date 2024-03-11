#include "NumberHandler.h"

namespace s21 {
HandleStatus NumberHandler::handle(const std::string &expression, size_t &index, std::list<ExpressionToken> &list) {
    if (std::isdigit(expression[index])) {
        if (index == 0 || ((!list.empty() && list.back().type == ETypes::OPEN_BRACKET) || (list.back().type >= ETypes::PLUS && list.back().type <= ETypes::POWER))) {
            bool dots_error = false;
            double num = getNumber(expression, index, dots_error);

            if (dots_error) {
                return HandleStatus{true, "Number cannot contain more than one dot."};
            }

            list.push_back(ExpressionToken{num, 0, ETypes::NUMBER, false, false, nullptr});
            return HandleStatus{false, ""};
        } else {
            return HandleStatus{true, "Number must be preceded by an operator or an open bracket."};
        }
    }

    return ExpressionHandler::handle(expression, index, list);
}

double NumberHandler::getNumber(const std::string &expression, size_t &index, bool& dots_error) {
    std::string num;
    size_t dot_counter = 0;

    for (; index < expression.length(); ++index) {
        if (expression[index] == '.')
            dot_counter++;
            
        if (std::isdigit(expression[index]) || expression[index] == '.') {
            num += expression[index];
        } else {
            --index;
            break;
        }
    }

    if (dot_counter > 1) {
        dots_error = true;
        return 0;
    }

    return std::stold(num);
}
}
