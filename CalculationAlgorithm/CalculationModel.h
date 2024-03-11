#ifndef _CALCULATIONMODEL_H_
#define _CALCULATIONMODEL_H_

#include <stack>

#include "BaseCalculation.h"
#include "CalculationData.h"

namespace s21 {
class CalculationModel : public BaseCalculation {
public:
    CalculationModel(const std::string& expression);

    void prepareExpression(const std::string& x) override;
    void parseExpression() override;
    void shuntingYard() override;
    void calculation() override;
    double getResult() override;

private:
    void replaceX(std::string& str, const std::string &x);

    std::stack<CalculationData> m_stack_;
};
}

#endif  // _CALCULATIONMODEL_H_
