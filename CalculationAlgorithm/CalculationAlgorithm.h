#ifndef _CALCULATIONALGORITHM_H_
#define _CALCULATIONALGORITHM_H_

#include <stack>

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

    ExpressionPreparator* m_preparator_;
    ExpressionParser* m_parser_;
    Calculation* m_calculation_;
};
}

#endif  // _CALCULATIONALGORITHM_H_
