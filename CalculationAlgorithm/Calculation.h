#ifndef _CALCULATION_H_
#define _CALCULATION_H_

#include <stack>
#include <queue>
#include "ExpressionToken.h"

namespace s21 {
    class Calculation {
    public:
        using ETypes = ExpressionTypes;
        
        virtual ~Calculation() = default;

        virtual std::queue<ExpressionToken> toPostfix(std::stack<ExpressionToken>& expression);
        virtual double calculate(std::queue<ExpressionToken>& postfix_expression);
    
    };
}

#endif  // _CALCULATION_H_
