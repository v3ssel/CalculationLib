#include <cmath>
#include "OperatorsHandler.h"
#include "../Utils.h"

namespace s21 {
HandleStatus s21::OperatorsHandler::handle(const std::string &expression, size_t &index, std::list<ExpressionToken> &list) {
    if (expression[index + 1] == '\0') {
        return HandleStatus{true, "Expression cannot ends on operator."};
    }

    if (expression[index] == '+' || expression[index] == '-') {
        if (index == 0 || (!list.empty() && !(list.back().type >= ETypes::PLUS && list.back().type <= ETypes::POWER))) { // need check!!
            if (index == 0 || expression[index - 1] == '(')
                list.push_back({ 0, 0, ETypes::NUMBER, false, false, nullptr });

            if (expression[index] == '-')
                list.push_back({ 0, 1, ETypes::MINUS, true, false, reinterpret_cast<void*>(Utils::minus) });
            else
                list.push_back({ 0, 1, ETypes::PLUS, true, false, reinterpret_cast<void*>(Utils::plus) });
        } else {
            return HandleStatus{true, "Plus or minus cannot be preceded by another operator"};
        }

        return HandleStatus{false, ""};
    }

    if (expression[index] == '*' || expression[index] == '/') {
        if (!list.empty() && (!(list.back().type >= ETypes::OPEN_BRACKET && list.back().type <= ETypes::POWER) || list.back().type == ETypes::CLOSED_BRACKET)) { // need check!!
            if (expression[index] == '*')
                list.push_back({ 0, 2, ETypes::MULT, true, false, reinterpret_cast<void*>(Utils::multiply) });
            else
                list.push_back({ 0, 2, ETypes::DIV, true, false, reinterpret_cast<void*>(Utils::divide) });

        } else {
            return HandleStatus{true, "Multiply or division cannot be preceded by another operator"};
        }

        return HandleStatus{false, ""};
    }

    if (expression[index] == '^') {
        if (!list.empty() && (!(list.back().type >= ETypes::OPEN_BRACKET && list.back().type <= ETypes::POWER) || list.back().type == ETypes::CLOSED_BRACKET)) {
            double (*fnc)(double, double) = std::pow;
            list.push_back({ 0, 3, ETypes::POWER, true, false, reinterpret_cast<void*>(fnc) });
        } else {
            return HandleStatus{true, "Power cannot be preceded by another operator"};
        }
        
        return HandleStatus{false, ""};
    }

    if (expression[index] == 'm') {
        if (expression[index + 1] == 'o' && expression[index + 2] == 'd' && !list.empty()) { // what? why it works?
            double (*fnc)(double, double) = std::fmod;
            list.push_back({ 0, 2, ETypes::MOD, true, false, reinterpret_cast<void*>(fnc) });
        } else {
            return HandleStatus{true, "Modulus cannot be preceded by another operator"};
        }
            
        index += 2;
        return HandleStatus{false, ""};
    }

    return ExpressionHandler::handle(expression, index, list);
}
}
