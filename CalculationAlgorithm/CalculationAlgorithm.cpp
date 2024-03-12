#include <algorithm>
#include <stdexcept>

#include "CalculationAlgorithm.h"

namespace s21 {
    CalculationAlgorithm::CalculationAlgorithm(ExpressionPreparator* preparator,
                                               ExpressionParser* handler,
                                               Calculation* calculation) {
        m_last_result_ = 0;
        m_preparator_ = preparator;
        m_parser_ = handler;
        m_calculation_ = calculation;
    }

    void CalculationAlgorithm::prepareExpression(const std::string &x) {
        expression_ = m_preparator_->prepare(expression_, x);
    }
    
    void CalculationAlgorithm::parseExpression() {
        m_tokens_ = m_parser_->parse(expression_);
    }
    
    void CalculationAlgorithm::calculation() {
        auto output_q = m_calculation_->toPostfix(m_tokens_);
        m_last_result_ = m_calculation_->calculate(output_q);
    }
    
    double CalculationAlgorithm::getResult() {
        return m_last_result_;
    }
}
