#ifndef _CALCULATIONALGORITHM_H_
#define _CALCULATIONALGORITHM_H_

#include <stack>
#include <memory>

#include "BaseCalculationAlgorithm.h"
#include "ExpressionToken.h"
#include "ExpressionParser.h"
#include "Calculation.h"

namespace s21 {
class CalculationAlgorithm : public BaseCalculationAlgorithm {
public:
    CalculationAlgorithm(ExpressionParser* handler,
                         Calculation* calculation);

protected:
    void parseExpression() override;
    void calculation() override;
    double getResult() override;

private:
    std::stack<ExpressionToken> m_tokens_;
    double m_last_result_;

    std::unique_ptr<ExpressionParser> m_parser_;
    std::unique_ptr<Calculation> m_calculation_;
};
}

#endif  // _CALCULATIONALGORITHM_H_
