#ifndef _CALCULATIONALGORITHM_H_
#define _CALCULATIONALGORITHM_H_

#include <stack>
#include <memory>

#include "BaseCalculationAlgorithm.h"
#include "ExpressionToken.h"
#include "ExpressionPreparator.h"
#include "ExpressionParser.h"
#include "Calculation.h"

namespace s21 {
class CalculationAlgorithm : public BaseCalculationAlgorithm {
public:
    CalculationAlgorithm(ExpressionPreparator* preparator,
                         ExpressionParser* handler,
                         Calculation* calculation);

    void prepareExpression(const std::string& x) override;
    void parseExpression() override;
    void calculation() override;
    double getResult() override;

private:
    std::stack<ExpressionToken> m_tokens_;
    double m_last_result_;

    std::unique_ptr<ExpressionPreparator> m_preparator_;
    std::unique_ptr<ExpressionParser> m_parser_;
    std::unique_ptr<Calculation> m_calculation_;
};
}

#endif  // _CALCULATIONALGORITHM_H_
