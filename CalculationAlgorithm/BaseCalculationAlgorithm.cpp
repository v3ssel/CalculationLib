#include "BaseCalculationAlgorithm.h"

namespace s21 {
double BaseCalculationAlgorithm::calculate(const std::string &exp) {
    this->expression_ = exp;
    
    this->parseExpression();
    this->calculation();

    return this->getResult();
}

const std::string &BaseCalculationAlgorithm::getExpression() const {
    return expression_;
}
}
