#include <algorithm>
#include <stdexcept>

#include "ExpressionPreparator.h"
#include "Utils.h"

namespace s21 {
std::string ExpressionPreparator::prepare(const std::string &expression, const std::string &x) {
    if (x.find('x') != std::string::npos || x.find('X') != std::string::npos) {
        throw std::invalid_argument("X cannot contain another x.");
    }

    std::string prepared = expression;

    auto prepare = [this](std::string& str) {
        str.erase(std::remove(str.begin(), str.end(), ' '), str.end());

        std::transform(str.begin(), str.end(), str.begin(),
                    [](unsigned char c) { return std::tolower(c); });

        Utils::stringReplace(str, ",", ".");
        replaceE(str);
    };
    
    prepare(prepared);

    if (!x.empty()) {
        std::string prepared_x = x;
        prepare(prepared_x);

        replaceX(prepared, prepared_x);
    }
    
    return prepared;
}

void ExpressionPreparator::replaceX(std::string &prepared, const std::string &x) {
    size_t x_pos = std::string::npos;

    while ((x_pos = prepared.find('x')) != std::string::npos) {
        std::string to_insert = x;

        if (x_pos != 0 && std::isdigit(prepared[x_pos - 1]))
            to_insert.insert(to_insert.begin(), '*');

        prepared.replace(x_pos, 1, to_insert);
    }
}

void ExpressionPreparator::replaceE(std::string& str) {
    size_t x_pos = std::string::npos;

    while ((x_pos = str.find('e')) != std::string::npos) {
        std::string to_insert = "*10^";
        size_t replace_count = 1;

        if (x_pos != str.length() - 1) {
            if (str[x_pos + 1] == '-') {
                to_insert[0] = '/';
                replace_count++;
            } else if (str[x_pos + 1] == '+') {
                replace_count++;
            }
        }

        str.replace(x_pos, replace_count, to_insert);
    }
}
}
