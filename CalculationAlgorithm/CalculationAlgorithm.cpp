#include <algorithm>
#include <stdexcept>

#include "CalculationAlgorithm.h"

namespace s21 {
    CalculationAlgorithm::CalculationAlgorithm(ExpressionParser* handler,
                                               Calculation* calculation) {
        m_last_result_ = 0;
        m_parser_ = std::unique_ptr<ExpressionParser>(handler);
        m_calculation_ = std::unique_ptr<Calculation>(calculation);
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
