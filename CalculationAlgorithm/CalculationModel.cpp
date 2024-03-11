#include <algorithm>
#include <stdexcept>

#include "CalculationModel.h"
#include "Utils.h"

namespace s21 {
    CalculationModel::CalculationModel(const std::string& expression) {
        expression_ = expression;
    }

    void CalculationModel::prepareExpression(const std::string &x) {
        if (x.find('x') != std::string::npos || x.find('X') != std::string::npos) {
            throw std::invalid_argument("X cannot contain another x.");
        }

        std::string prepared = expression_;

        auto prepare = [](std::string& str) {
            str.erase(std::remove(str.begin(), str.end(), ' '), str.end());

            std::transform(str.begin(), str.end(), str.begin(),
                        [](unsigned char c) { return std::tolower(c); });

            Utils::stringReplace(str, ",", ".");
            Utils::stringReplace(str, "e-", "/10^");
            Utils::stringReplace(str, "e+", "*10^");
            Utils::stringReplace(str, "e", "*10^");
        };
        
        prepare(prepared);

        if (!x.empty()) {
            std::string prepared_x = x;
            prepare(prepared_x);

            replaceX(prepared, prepared_x);
        }
        
        expression_ = prepared;
    }
    
    void CalculationModel::parseExpression() {

    }
    
    void CalculationModel::shuntingYard() {

    }

    void CalculationModel::calculation() {
        
    }
    
    double CalculationModel::getResult() {
        return m_stack_.top().value;
    }
    
    void CalculationModel::replaceX(std::string &prepared, const std::string &x) {
        size_t x_pos = std::string::npos;
        while ((x_pos = prepared.find('x')) != std::string::npos) {
            std::string to_insert = x;

            if (x_pos != 0 && std::isdigit(prepared[x_pos - 1]))
                to_insert.insert(to_insert.begin(), '*');

            prepared.replace(x_pos, 1, to_insert);
        }
    }
}
