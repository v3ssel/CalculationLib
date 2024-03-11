#ifndef _CALCULATIONALGORITHM_H_
#define _CALCULATIONALGORITHM_H_

#include <stack>

#include "BaseCalculationAlgorithm.h"
#include "ExpressionToken.h"
#include "ExpressionPreparator.h"
#include "ExpressionParser.h"

namespace s21 {
class CalculationAlgorithm : public BaseCalculationAlgorithm {
public:
    CalculationAlgorithm(ExpressionPreparator* preparator, ExpressionParser* handler);

    void prepareExpression(const std::string& x) override;
    void parseExpression() override;
    void shuntingYard() override;
    void calculation() override;
    double getResult() override;

private:
    std::stack<ExpressionToken> m_tokens_;

    ExpressionPreparator* m_preparator_;
    ExpressionParser* m_parser_;
};
}

#endif  // _CALCULATIONALGORITHM_H_
