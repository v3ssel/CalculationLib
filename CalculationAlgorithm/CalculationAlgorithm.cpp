#include <algorithm>
#include <stdexcept>

#include "CalculationAlgorithm.h"

namespace s21 {
    CalculationAlgorithm::CalculationAlgorithm(ExpressionPreparator* preparator, ExpressionParser* handler) {
        m_preparator_ = preparator;
        m_parser_ = handler;
    }

    void CalculationAlgorithm::prepareExpression(const std::string &x) {
        expression_ = m_preparator_->prepare(expression_, x);
    }
    
    void CalculationAlgorithm::parseExpression() {
        m_tokens_ = m_parser_->parse(expression_);
    }
    
    void CalculationAlgorithm::shuntingYard() {

    }

    void CalculationAlgorithm::calculation() {
        
    }
    
    double CalculationAlgorithm::getResult() {
        return m_tokens_.top().value;
    }
}
