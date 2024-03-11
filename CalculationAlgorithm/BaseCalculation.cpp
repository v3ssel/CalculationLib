#include "BaseCalculation.h"

double BaseCalculation::calculate(const std::string &exp, const std::string &x) {
    this->expression_ = exp;
    
    this->prepareExpression(x);
    this->parseExpression();
    this->shuntingYard();
    this->calculation();

    return this->getResult();
}

const std::string &BaseCalculation::getExpression() const {
    return expression_;
}
