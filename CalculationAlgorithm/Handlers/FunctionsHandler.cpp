#include <cmath>
#include "FunctionsHandler.h"
#include "../Utils.h"

namespace s21 {
HandleStatus s21::FunctionsHandler::handle(const std::string &expression, size_t &index, std::list<ExpressionToken> &list) {
    if (expression[index] == 's') {
        if (expression[index + 1] == 'i' && expression[index + 2] == 'n') {
            if (!list.empty() && list.back().type == ETypes::NUMBER) {
                list.push_back({ 0, 2, ETypes::MULT, true, false, reinterpret_cast<void*>(Utils::multiply) });
            }

            double (*fnc)(double) = std::sin;
            list.push_back({ 0, 4, ETypes::SIN, false, true, reinterpret_cast<void*>(fnc) });

            index += 2;
        } else if (expression[index + 1] == 'q' && expression[index + 2] == 'r' && expression[index + 3] == 't') {
            double (*fnc)(double) = std::sqrt;
            list.push_back({ 0, 4, ETypes::SQRT, false, true, reinterpret_cast<void*>(fnc) });

            index += 3;
        } else {
            return HandleStatus{true, "Unexpected token, expected sin/sqrt."};
        }

        return HandleStatus{false, ""};
    }

    if (expression[index] == 'c') {
        if (expression[index + 1] == 'o' && expression[index + 2] == 's') {
            if (!list.empty() && list.back().type == ETypes::NUMBER) {
                list.push_back({ 0, 2, ETypes::MULT, true, false, reinterpret_cast<void*>(Utils::multiply) });
            }

            double (*fnc)(double) = std::cos;
            list.push_back({ 0, 4, ETypes::COS, false, true, reinterpret_cast<void*>(fnc) });

            index += 2;
        } else {
            return HandleStatus{true, "Unexpected token, expected cos."};
        }

        return HandleStatus{false, ""};
    }

    if (expression[index] == 't') {
        if (expression[index + 1] == 'a' && expression[index + 2] == 'n') {
            if (!list.empty() && list.back().type == ETypes::NUMBER) {
                list.push_back({ 0, 2, ETypes::MULT, true, false, reinterpret_cast<void*>(Utils::multiply) });
            }
            
            double (*fnc)(double) = std::tan;
            list.push_back({ 0, 4, ETypes::TAN, false, true, reinterpret_cast<void*>(fnc) });

            index += 2;
        } else {
            return HandleStatus{true, "Unexpected token, expected tan."};
        }

        return HandleStatus{false, ""};
    }


    if (expression[index] == 'a') {
        if (expression[index + 1] == 's' && expression[index + 2] == 'i' && expression[index + 3] == 'n') {
            if (!list.empty() && list.back().type == ETypes::NUMBER) {
                list.push_back({ 0, 2, ETypes::MULT, true, false, reinterpret_cast<void*>(Utils::multiply) });
            }

            double (*fnc)(double) = std::asin;
            list.push_back({ 0, 4, ETypes::ASIN, false, true, reinterpret_cast<void*>(fnc) });

            index += 3;
        } else if (expression[index + 1] == 'c' && expression[index + 2] == 'o' && expression[index + 3] == 's') {
            if (!list.empty() && list.back().type == ETypes::NUMBER) {
                list.push_back({ 0, 2, ETypes::MULT, true, false, reinterpret_cast<void*>(Utils::multiply) });
            }

            double (*fnc)(double) = std::acos;
            list.push_back({ 0, 4, ETypes::ACOS, false, true, reinterpret_cast<void*>(fnc) });
            
            index += 3;
        } else if (expression[index + 1] == 't' && expression[index + 2] == 'a' && expression[index + 3] == 'n') {
            if (!list.empty() && list.back().type == ETypes::NUMBER) {
                list.push_back({ 0, 2, ETypes::MULT, true, false, reinterpret_cast<void*>(Utils::multiply) });
            }

            double (*fnc)(double) = std::atan;
            list.push_back({ 0, 4, ETypes::ATAN, false, true, reinterpret_cast<void*>(fnc) });
            
            index += 3;
        } else {
            return HandleStatus{true, "Unexpected token, expected asin/acos/atan."};
        }

        return HandleStatus{false, ""};
    }

    if (expression[index] == 'l') {
        if (expression[index + 1] == 'n') {
            if (!list.empty() && list.back().type == ETypes::NUMBER) {
                list.push_back({ 0, 2, ETypes::MULT, true, false, reinterpret_cast<void*>(Utils::multiply) });
            }

            double (*fnc)(double) = std::log;
            list.push_back({ 0, 4, ETypes::LN, false, true, reinterpret_cast<void*>(fnc) });
            
            index += 1;
        } else if (expression[index + 1] == 'o' && expression[index + 2] == 'g') {
            if (!list.empty() && list.back().type == ETypes::NUMBER) {
                list.push_back({ 0, 2, ETypes::MULT, true, false, reinterpret_cast<void*>(Utils::multiply) });
            }
            
            double (*fnc)(double) = std::log10;
            list.push_back({ 0, 4, ETypes::LOG, false, true, reinterpret_cast<void*>(fnc) });

            index += 2;
        } else {
            return HandleStatus{true, "Unexpected token, expected ln/log."};
        }

        return HandleStatus{false, ""};
    }

    return ExpressionHandler::handle(expression, index, list);
}
}