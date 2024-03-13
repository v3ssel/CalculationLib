#include "CalculationAlgorithmWithXWrapper.h"

namespace s21 {
CalculationAlgorithmWithXWrapper::CalculationAlgorithmWithXWrapper(BaseCalculationAlgorithm *algorithm, ExpressionPreparator *preparator) {
    m_algorithm_  = std::unique_ptr<BaseCalculationAlgorithm>(algorithm);
    m_preparator_ = std::unique_ptr<ExpressionPreparator>(preparator);
}

double CalculationAlgorithmWithXWrapper::calculate(const std::string &expression, const std::string &x) {
    std::string prepared = m_preparator_->prepare(expression, x);

    return m_algorithm_->calculate(prepared);
}
}
