#ifndef _BASECALCULATIONALGORITHM_H_
#define _BASECALCULATIONALGORITHM_H_

#include <string>

namespace s21 {
class BaseCalculationAlgorithm {
public:
    double calculate(const std::string& exp);
    const std::string& getExpression() const;
    
    virtual ~BaseCalculationAlgorithm() = default;

protected:
    virtual void parseExpression() = 0;
    virtual void calculation() = 0;
    virtual double getResult() = 0;

    std::string expression_;
};
}

#endif  // _BASECALCULATIONALGORITHM_H_
