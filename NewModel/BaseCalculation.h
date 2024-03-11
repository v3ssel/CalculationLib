#ifndef _BASECALCULATION_H_
#define _BASECALCULATION_H_

#include <string>

class BaseCalculation {
public:
    double calculate(const std::string& exp, const std::string& x);

    virtual void prepareExpression(const std::string& x) = 0;
    virtual void parseExpression() = 0;
    virtual void shuntingYard() = 0;
    virtual void calculation() = 0;
    virtual double getResult() = 0;

protected:
    std::string expression_;
};

#endif  // _BASECALCULATION_H_
